
FetchContent_Declare(filament
  GIT_REPOSITORY https://github.com/google/filament.git
  GIT_TAG main
)

set(BUILD_TESTING OFF CACHE BOOL "Don't build testing")
set(FILAMENT_SKIP_SAMPLES ON CACHE BOOL "Don't build samples")
set(FILAMENT_SHORTEN_MSVC_COMPILATION OFF CACHE BOOL "Shorten compile-time in Visual Studio")

set(THIRD_PARTY_LIB_PREFIX "${CMAKE_SOURCE_DIR}/build/_deps")
set(THIRD_PARTY_LIB_SOURCE_DIR "${THIRD_PARTY_LIB_PREFIX}/filament-src")

FetchContent_MakeAvailable(filament)

set_target_properties(
    core_tables
    enum_string_mapping
    extinst_tables
    meshoptimizer
    PROPERTIES FOLDER "Third-party/filament"
)

set_target_properties(
    filament
    backend
    PROPERTIES FOLDER "Third-party/filament/Filament"
)

set_target_properties(
    shaders
    PROPERTIES FOLDER "Third-party/filament/Filament/Shaders"
)

set_target_properties(
    vkshaders
    PROPERTIES FOLDER "Third-party/filament/Filament/Generated"
)

set_target_properties(
    bluegl
    camutils
    filabridge
    filaflat
    filagui
    filamat
    filament-iblprefilter
    filameshio
    geometry
    gltfio
    gltfio_core
    ibl
    ibl-lite
    image
    imageio
    ktxreader
    matdbg
    matdbg_resources
    math
    mathio
    mikktspace
    uberarchive
    uberz_file
    uberzlib
    utils
    viewer
    PROPERTIES FOLDER "Third-party/filament/Libs"
)

set_target_properties(
    test_bluegl
    test_camutils
    test_cmgen
    test_filamat
    test_filameshio
    test_glslminifier
    test_image
    test_ktxreader
    test_matc
    test_material_parser
    test_math
    test_settings
    test_tangent_space_mesh
    test_transcoder
    test_utils

    test_gltfio_files

    PROPERTIES FOLDER "Third-party/filament/Tests"
)

set_target_properties(
    cmgen
    cso-lut
    filamesh
    glslminifier
    matc
    matinfo
    matlang
    mipgen
    normal-blending
    resgen
    rgb-to-lmsr
    roughness-prefilter
    specular-color
    uberz
    PROPERTIES FOLDER "Third-party/filament/Tools"
)

set_target_properties(
    OSDependent
    PROPERTIES FOLDER "Third-party/filament/GLSLang"
)

set_target_properties(
    assimp
    basis_encoder
    basis_transcoder
    basisu
    benchmark
    benchmark_main
    civetweb
    getopt
    gtest
    imgui
    png
    sdl2
    sdl2main
    smol-v
    spirv-cross-core
    spirv-cross-glsl
    spirv-cross-msl
    stb
    tinyexr
    z
    zstd
    PROPERTIES FOLDER "Third-party/filament/ThirdParty"
)

set_target_properties(
    draco_animation
    draco_animation_dec
    draco_animation_enc
    draco_attributes
    draco_compression_attributes_dec
    draco_compression_attributes_enc
    draco_compression_attributes_pred_schemes_dec
    draco_compression_attributes_pred_schemes_enc
    draco_compression_bit_coders
    draco_compression_decode
    draco_compression_encode
    draco_compression_entropy
    draco_compression_mesh_dec
    draco_compression_mesh_enc
    draco_compression_mesh_traverser
    draco_compression_point_cloud_dec
    draco_compression_point_cloud_enc
    draco_core
    draco_dec_config
    draco_enc_config
    draco_io
    draco_mesh
    draco_metadata
    draco_metadata_dec
    draco_metadata_enc
    draco_point_cloud
    draco_points_dec
    draco_points_enc
    dracodec
    PROPERTIES FOLDER "Third-party/filament/ThirdParty/draco"
)

set_target_properties(
    glslang
    OGLCompiler
    SPIRV
    PROPERTIES FOLDER "Third-party/filament/ThirdParty/glslang"
)

set_target_properties(
    benchmark_filament
    benchmark_math
    benchmark_utils
    benchmark_utils_callee
    PROPERTIES FOLDER "Third-party/filament/Benchmarks"
)

set_target_properties(
    spirv-tools-build-version
    spirv-tools-header-DebugInfo
    spirv-tools-header-NonSemanticShaderDebugInfo100
    spirv-tools-header-OpenCLDebugInfo100
    spv-tools-cldi100
    spv-tools-clspvreflection
    spv-tools-debuginfo
    spv-tools-shdi100
    spv-tools-spv-amd-gs
    spv-tools-spv-amd-sb
    spv-tools-spv-amd-sevp
    spv-tools-spv-amd-stm
    PROPERTIES FOLDER "Third-party/filament/SPIRV-Tools build"
)

set_target_properties(
    spirv-tools-vimsyntax
    PROPERTIES FOLDER "Third-party/filament/SPIRV-Tools utilities"
)

set_target_properties(
    SPIRV-Tools-diff
    SPIRV-Tools-link
    SPIRV-Tools-lint
    SPIRV-Tools-opt
    SPIRV-Tools-reduce
    SPIRV-Tools-static
    PROPERTIES FOLDER "Third-party/filament/SPIRV-Tools libraries"
)

set_target_properties(
    filament
    backend
    PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)