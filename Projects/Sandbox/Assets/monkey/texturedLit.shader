material {
    name : LitTextured,
    requires : [
        uv0
    ],
    shadingModel : lit,
    parameters : [
        {
            type : sampler2d,
            name : albedo
        },
        {
            type : sampler2d,
            name : roughness
        },
        {
            type : sampler2d,
            name : metallic
        },
        {
            type : sampler2d,
            name : normal
        },
        {
            type : sampler2d,
            name : ao
        },
        {
            type : float,
            name : clearCoat
        },
        {
            type : float,
            name : testFloat1
        },
        {
            type : float,
            name : testFloat2
        }
    ],
}

fragment {
    void material(inout MaterialInputs material) {
        material.normal = texture(materialParams_normal, getUV0()).xyz * 2.0 - 1.0;
        prepareMaterial(material);
        material.baseColor = texture(materialParams_albedo, getUV0());
        material.roughness = texture(materialParams_roughness, getUV0()).r;
        material.metallic = texture(materialParams_metallic, getUV0()).r;
        material.clearCoat = materialParams.clearCoat * materialParams.testFloat1 * materialParams.testFloat2;
        material.ambientOcclusion = texture(materialParams_ao, getUV0()).r;
    }
}
