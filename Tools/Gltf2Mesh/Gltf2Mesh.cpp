#include <ozzmesh.h>
#include <ozz/base/log.h>
#include <ozz/base/io/stream.h>
#include <ozz/base/io/archive.h>
#include <ozz/base/maths/math_ex.h>
#include <ozz/base/maths/simd_math.h>
#include <ozz/base/memory/allocator.h>
#include <ozz/base/containers/map.h>
#include <ozz/base/containers/vector.h>

#include <ozz/options/options.h>
#include <ozz/animation/runtime/skeleton.h>

#include <tiny_gltf.h>

#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>

// Declares command line options.
OZZ_OPTIONS_DECLARE_STRING(file, "Specifies input file.", "", true)
OZZ_OPTIONS_DECLARE_STRING(mesh, "Specifies ozz mesh output file.", "", true)
OZZ_OPTIONS_DECLARE_STRING(skeleton, "Specifies the skeleton that the skin is bound to.", "", true)

static std::map<int, int> GLTF_ACCESSOR_TYPE_LOOKUP =
{
	{ TINYGLTF_TYPE_SCALAR, 1 },
	{ TINYGLTF_TYPE_VEC2, 2 },
	{ TINYGLTF_TYPE_VEC3, 3 },
	{ TINYGLTF_TYPE_VEC4, 4 },
	{ TINYGLTF_TYPE_MAT2, 4 },
	{ TINYGLTF_TYPE_MAT3, 9 },
	{ TINYGLTF_TYPE_MAT4, 16 }
};

ozz::math::Float4x4 ConvertMatrix(const float* pMat)
{
	const ozz::math::Float4x4 m = { {
		ozz::math::simd_float4::Load(static_cast<float>(pMat[0]), static_cast<float>(pMat[1]), static_cast<float>(pMat[2]), static_cast<float>(pMat[3])),
		ozz::math::simd_float4::Load(static_cast<float>(pMat[4]), static_cast<float>(pMat[5]), static_cast<float>(pMat[6]), static_cast<float>(pMat[7])),
		ozz::math::simd_float4::Load(static_cast<float>(pMat[8]), static_cast<float>(pMat[9]), static_cast<float>(pMat[10]), static_cast<float>(pMat[11])),
		ozz::math::simd_float4::Load(static_cast<float>(pMat[12]), static_cast<float>(pMat[13]), static_cast<float>(pMat[14]), static_cast<float>(pMat[15])),
	} };
	return m;
}

bool BuildMesh(tinygltf::Model& model, ozz::vector<ozz::sample::Mesh>& meshes)
{
	const int num_meshes = model.meshes.size();
	meshes.resize(model.meshes.size());

	for (int m = 0; m < num_meshes; ++m)
	{
		tinygltf::Mesh& mesh = model.meshes[m];

		// Allocates output mesh.
		ozz::sample::Mesh& output_mesh = meshes[m];
		output_mesh.parts.resize(1);

		// Reserve vertex buffers. Real size is unknown as redundant vertices will be
		// rejected.
		ozz::sample::Mesh::Part& part = output_mesh.parts[0];

		// name
		part.names.resize(mesh.name.size());
		for (uint32_t i = 0; i < mesh.name.size(); i++)
		{
			part.names[i] = static_cast<uint8_t>(mesh.name[i]);
		}

		for (int p = 0; p < mesh.primitives.size(); ++p)
		{
			// TODO FIX
			if (p > 0) { continue; }

			auto primitive = mesh.primitives[p];

			for (auto& attribute : primitive.attributes)
			{
				auto& accessor = model.accessors.at(attribute.second);
				auto& bufferView = model.bufferViews.at(accessor.bufferView);
				auto& buffer = model.buffers.at(bufferView.buffer);
				int byteStride = accessor.ByteStride(bufferView);

				if (attribute.first == "POSITION")
				{
					switch (accessor.componentType)
					{
					case TINYGLTF_COMPONENT_TYPE_FLOAT:
					{
						auto componentCount = GLTF_ACCESSOR_TYPE_LOOKUP[accessor.type];

						part.positions.reserve(accessor.count * componentCount);
						auto* base = &buffer.data.at(bufferView.byteOffset + accessor.byteOffset);
						for (size_t v_pos = 0; v_pos < accessor.count; v_pos++)
						{
							const float* data = reinterpret_cast<const float*>(base + byteStride * v_pos);
							for (size_t i = 0; i < componentCount; i++)
							{
								part.positions.push_back(data[i]);
							}
						}
					}
					break;
					default:
						break;
					}
				}
				else if (attribute.first == "NORMAL")
				{
					switch (accessor.componentType)
					{
					case TINYGLTF_COMPONENT_TYPE_FLOAT:
					{
						auto componentCount = GLTF_ACCESSOR_TYPE_LOOKUP[accessor.type];

						part.normals.reserve(accessor.count * componentCount);
						auto* base = &buffer.data.at(bufferView.byteOffset + accessor.byteOffset);
						for (size_t v_pos = 0; v_pos < accessor.count; v_pos++)
						{
							const float* data = reinterpret_cast<const float*>(base + byteStride * v_pos);
							for (size_t i = 0; i < componentCount; i++)
							{
								part.normals.push_back(data[i]);
							}
						}
					}
					break;
					default:
						break;
					}
				}
				else if (attribute.first == "TEXCOORD_0")
				{
					switch (accessor.componentType)
					{
					case TINYGLTF_COMPONENT_TYPE_FLOAT:
					{
						auto componentCount = GLTF_ACCESSOR_TYPE_LOOKUP[accessor.type];

						part.uvs.reserve(accessor.count * componentCount);
						auto* base = &buffer.data.at(bufferView.byteOffset + accessor.byteOffset);
						for (size_t v_pos = 0; v_pos < accessor.count; v_pos++)
						{
							const float* data = reinterpret_cast<const float*>(base + byteStride * v_pos);
							for (size_t i = 0; i < componentCount; i++)
							{
								part.uvs.push_back(data[i]);
							}
						}
					}
					break;
					default:
						break;
					}
				}
				else if (attribute.first == "TEXCOORD_1")
				{
					switch (accessor.componentType)
					{
					case TINYGLTF_COMPONENT_TYPE_FLOAT:
						break;
					default:
						break;
					}
				}
				else if (attribute.first == "COLOR_0")
				{
					switch (accessor.componentType)
					{
					case TINYGLTF_COMPONENT_TYPE_FLOAT:
					{
						auto componentCount = GLTF_ACCESSOR_TYPE_LOOKUP[accessor.type];

						part.colors.reserve(accessor.count * componentCount);
						auto* base = &buffer.data.at(bufferView.byteOffset + accessor.byteOffset);
						for (size_t v_pos = 0; v_pos < accessor.count; v_pos++)
						{
							const float* data = reinterpret_cast<const float*>(base + byteStride * v_pos);
							for (size_t i = 0; i < componentCount; i++)
							{
								part.colors.push_back(data[i]);
							}
						}
					}
					break;
					default:
						break;
					}
				}
				else if (attribute.first == "TANGENT")
				{
					switch (accessor.componentType)
					{
					case TINYGLTF_COMPONENT_TYPE_FLOAT:
					{
						auto componentCount = GLTF_ACCESSOR_TYPE_LOOKUP[accessor.type];

						part.tangents.reserve(accessor.count * componentCount);
						auto* base = &buffer.data.at(bufferView.byteOffset + accessor.byteOffset);
						for (size_t v_pos = 0; v_pos < accessor.count; v_pos++)
						{
							const float* data = reinterpret_cast<const float*>(base + byteStride * v_pos);
							for (size_t i = 0; i < componentCount; i++)
							{
								part.tangents.push_back(data[i]);
							}
						}
					}
					break;
					default:
						break;
					}
				}
				else if (attribute.first == "WEIGHTS_0")
				{
					std::vector<float> weights;

					switch (accessor.componentType)
					{
					case TINYGLTF_COMPONENT_TYPE_FLOAT:
					{
						auto componentCount = GLTF_ACCESSOR_TYPE_LOOKUP[accessor.type];

						part.joint_weights.reserve(accessor.count * componentCount);
						auto* base = &buffer.data.at(bufferView.byteOffset + accessor.byteOffset);
						for (size_t v_pos = 0; v_pos < accessor.count; v_pos++)
						{
							const float* data = reinterpret_cast<const float*>(base + byteStride * v_pos);

							weights.clear();
							float sum = 0.f;
							for (size_t i = 0; i < componentCount; i++)
							{
								sum += data[i];
								weights.push_back(data[i]);
							}
							for (auto& weight : weights)
							{
								weight *= (1.f / sum);
								part.joint_weights.push_back(weight);
							}
						}
					}
					break;
					default:
						break;
					}
				}
				else if (attribute.first == "JOINTS_0")
				{
					switch (accessor.componentType)
					{
					case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
					{
						auto componentCount = GLTF_ACCESSOR_TYPE_LOOKUP[accessor.type];

						part.joint_indices.reserve(accessor.count * componentCount);
						auto* base = &buffer.data.at(bufferView.byteOffset + accessor.byteOffset);
						for (size_t v_pos = 0; v_pos < accessor.count; v_pos++)
						{
							const uint8_t* data = reinterpret_cast<const uint8_t*>(base + byteStride * v_pos);
							for (size_t i = 0; i < componentCount; i++)
							{
								part.joint_indices.push_back(data[i]);
							}
						}

						auto local_indices = part.joint_indices;
						std::sort(local_indices.begin(), local_indices.end());
						local_indices.erase(std::unique(local_indices.begin(), local_indices.end()), local_indices.end());
						output_mesh.joint_remaps = local_indices;
					}
					break;
					case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
						break;
					case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
						break;
						break;
					default:
						break;
					}
				}
			}

			if (primitive.indices >= 0)
			{
				auto& indexAccessor = model.accessors.at(primitive.indices);
				auto& indexBufferView = model.bufferViews.at(indexAccessor.bufferView);
				auto& indexBuffer = model.buffers.at(indexBufferView.buffer);
				int byteStride = indexAccessor.ByteStride(indexBufferView);

				switch (indexAccessor.componentType)
				{
				case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
					break;
				case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
				{
					auto componentCount = GLTF_ACCESSOR_TYPE_LOOKUP[indexAccessor.type];

					output_mesh.triangle_indices.resize(indexAccessor.count);
					const uint8_t* base = &indexBuffer.data.at(indexBufferView.byteOffset + indexAccessor.byteOffset);
					for (size_t iCount = 0; iCount < indexAccessor.count; iCount++)
					{
						const uint16_t* data = reinterpret_cast<const uint16_t*>(base);
						output_mesh.triangle_indices[iCount] = data[iCount];
					}
				}
					break;
				case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
					break;
				default:
					break;
				}
			}
		}
	}

	return true;
}

bool BuildSkin(tinygltf::Model& model, ozz::vector<ozz::sample::Mesh::InversBindPoses>& poses, const ozz::animation::Skeleton& skeleton)
{
	const int num_skins = model.skins.size();
	poses.resize(num_skins);

	std::vector<float> matrix;
	for (int s = 0; s < num_skins; s++)
	{
		tinygltf::Skin& skin = model.skins[s];

		// Builds joints names map.
		typedef ozz::cstring_map<uint16_t> JointsMap;
		JointsMap joints_map;
		for (int i = 0; i < skeleton.num_joints(); ++i)
		{
			joints_map[skeleton.joint_names()[i]] = static_cast<uint16_t>(i);
		}

		// Resize inverse bind pose matrices and set all to identity.
		ozz::sample::Mesh::InversBindPoses& inverse_bind_poses = poses[s];
		inverse_bind_poses.resize(skeleton.num_joints());
		for (int i = 0; i < skeleton.num_joints(); ++i)
		{
			inverse_bind_poses[i] = ozz::math::Float4x4::identity();
		}

		if (skin.inverseBindMatrices != -1)
		{
			auto& skinAccessors = model.accessors[skin.inverseBindMatrices];
			auto& skinBufferView = model.bufferViews.at(skinAccessors.bufferView);
			auto& skinBuffer = model.buffers.at(skinBufferView.buffer);
			int byteStride = skinAccessors.ByteStride(skinBufferView);

			switch (skinAccessors.componentType)
			{
			case TINYGLTF_COMPONENT_TYPE_FLOAT:
			{
				auto componentCount = GLTF_ACCESSOR_TYPE_LOOKUP[skinAccessors.type];

				auto* base = &skinBuffer.data.at(skinBufferView.byteOffset + skinAccessors.byteOffset);
				for (size_t v_pos = 0; v_pos < skinAccessors.count; v_pos++)
				{
					matrix.clear();
					const float* data = reinterpret_cast<const float*>(base + byteStride * v_pos);
					for (size_t i = 0; i < componentCount; i++)
					{
						matrix.push_back(data[i]);
					}
					inverse_bind_poses[v_pos] = ConvertMatrix(matrix.data());
				}
			}
				break;
			default:
				break;
			}
		}
	}

	return true;
}

int main(int _argc, const char** _argv)
{
	ozz::options::ParseResult parse_result = ozz::options::ParseCommandLine(
		_argc, _argv, "1.1",
		"Imports a skin from a fbx file and converts it to ozz binary format");
	if (parse_result != ozz::options::kSuccess)
	{
		return parse_result == ozz::options::kExitSuccess ? EXIT_SUCCESS : EXIT_FAILURE;
	}

	ozz::animation::Skeleton skeleton;
	{
		ozz::log::Out() << "Loading skeleton archive " << OPTIONS_skeleton.value() << "." << std::endl;
		ozz::io::File file(OPTIONS_skeleton.value(), "rb");
		if (!file.opened())
		{
			ozz::log::Err() << "Failed to open skeleton file " << OPTIONS_skeleton.value() << "." << std::endl;
			return EXIT_FAILURE;
		}
		ozz::io::IArchive archive(&file);
		if (!archive.TestTag<ozz::animation::Skeleton>())
		{
			ozz::log::Err() << "Failed to load skeleton instance from file " << OPTIONS_skeleton.value() << "." << std::endl;
			return EXIT_FAILURE;
		}

		// Once the tag is validated, reading cannot fail.
		archive >> skeleton;
	}

	bool ret;
	std::string err;
	std::string warn;

	tinygltf::Model model;
	tinygltf::TinyGLTF loader;

	const char* separator = std::strrchr(OPTIONS_file, '.');
	const char* ext = separator != NULL ? separator + 1 : "";

	if (ext == "glb")
	{
		ret = tinygltf::TinyGLTF().LoadBinaryFromFile(&model, &err, &warn, std::string(OPTIONS_file));
	}
	else
	{
		ret = tinygltf::TinyGLTF().LoadASCIIFromFile(&model, &err, &warn, std::string(OPTIONS_file));
	}

	if (!err.empty())
	{
		return EXIT_FAILURE;
	}

	if (!warn.empty())
	{
		return EXIT_FAILURE;
	}

	if (!ret || model.scenes.empty())
	{
		return EXIT_FAILURE;
	}

	ozz::vector<ozz::sample::Mesh> meshes;

	if (!BuildMesh(model, meshes))
	{
		return EXIT_FAILURE;
	}

	ozz::vector<ozz::sample::Mesh::InversBindPoses> poses;

	if (!BuildSkin(model, poses, skeleton))
	{
		return EXIT_FAILURE;
	}

	//
	for (int n = 0; n < model.nodes.size(); n++)
	{
		tinygltf::Node& node = model.nodes[n];
		if (node.mesh != -1)
		{
			auto& mesh = meshes[node.mesh];
			if (node.skin != -1)
			{
				mesh.inverse_bind_poses = poses[node.skin];
				ozz::sample::Mesh::Part& in_part = mesh.parts.front();

				// Build mapping table of mesh original joints to the new ones. Unused joints
				// are set to 0.
				ozz::sample::Mesh::Part::JointIndices original_remap(mesh.num_joints(), 0);
				for (size_t i = 0; i < mesh.joint_remaps.size(); ++i)
				{
					original_remap[mesh.joint_remaps[i]] = static_cast<ozz::sample::Mesh::Part::JointIndices::value_type>(i);
				}

				// Reset all joints in the mesh.
				for (size_t i = 0; i < in_part.joint_indices.size(); ++i)
				{
					in_part.joint_indices[i] = original_remap[in_part.joint_indices[i]];
				}

				// Remaps bind poses and removes unused joints.
				for (size_t i = 0; i < mesh.joint_remaps.size(); ++i)
				{
					mesh.inverse_bind_poses[i] = mesh.inverse_bind_poses[mesh.joint_remaps[i]];
				}
				mesh.inverse_bind_poses.resize(mesh.joint_remaps.size());
			}
		}
	}

	// Opens output file.
	ozz::io::File mesh_file(OPTIONS_mesh, "wb");
	if (!mesh_file.opened())
	{
		ozz::log::Err() << "Failed to open output file: " << OPTIONS_mesh.value() << std::endl;
		return EXIT_FAILURE;
	}

	{
		// Serialize the partitioned meshes.
		// They aren't serialized as a vector/array as we don't know how they are
		// going to be read.
		ozz::io::OArchive archive(&mesh_file);
		for (size_t m = 0; m < meshes.size(); ++m)
		{
			archive << meshes[m];
		}
	}

	ozz::log::Log() << "Mesh binary archive successfully outputted for file " << OPTIONS_file.value() << "." << std::endl;

	return EXIT_SUCCESS;
}