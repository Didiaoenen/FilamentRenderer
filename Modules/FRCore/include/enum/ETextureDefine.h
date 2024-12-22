#pragma once

#include <EnumOpt.h>
#include <filament/Texture.h>
#include <filament/TextureSampler.h>

namespace FR::ETexture
{
	enum class ESampler : uint8_t
	{
		SAMPLER_2D,             //!< 2D texture
		SAMPLER_2D_ARRAY,       //!< 2D array texture
		SAMPLER_CUBEMAP,        //!< Cube map texture
		SAMPLER_EXTERNAL,       //!< External texture
		SAMPLER_3D,             //!< 3D texture
		SAMPLER_CUBEMAP_ARRAY,  //!< Cube map array texture (feature level 2)
	};

	static filament::Texture::Sampler ConvertEnum(ESampler pSampler)
	{
		return static_cast<filament::Texture::Sampler>(pSampler);
	}

	enum class EType : uint8_t
	{
		UBYTE,                //!< unsigned byte
		BYTE,                 //!< signed byte
		USHORT,               //!< unsigned short (16-bit)
		SHORT,                //!< signed short (16-bit)
		UINT,                 //!< unsigned int (32-bit)
		INT,                  //!< signed int (32-bit)
		HALF,                 //!< half-float (16-bit float)
		FLOAT,                //!< float (32-bits float)
		COMPRESSED,           //!< compressed pixels, @see CompressedPixelDataType
		UINT_10F_11F_11F_REV, //!< three low precision floating-point numbers
		USHORT_565,           //!< unsigned int (16-bit), encodes 3 RGB channels
		UINT_2_10_10_10_REV,  //!< unsigned normalized 10 bits RGB, 2 bits alpha
	};

	static filament::Texture::Type ConvertEnum(EType pType)
	{
		return static_cast<filament::Texture::Type>(pType);
	}

	enum class EUsage : uint16_t
	{
		NONE = 0x0000,
		COLOR_ATTACHMENT = 0x0001,            //!< Texture can be used as a color attachment
		DEPTH_ATTACHMENT = 0x0002,            //!< Texture can be used as a depth attachment
		STENCIL_ATTACHMENT = 0x0004,            //!< Texture can be used as a stencil attachment
		UPLOADABLE = 0x0008,            //!< Data can be uploaded into this texture (default)
		SAMPLEABLE = 0x0010,            //!< Texture can be sampled (default)
		SUBPASS_INPUT = 0x0020,            //!< Texture can be used as a subpass input
		BLIT_SRC = 0x0040,            //!< Texture can be used the source of a blit()
		BLIT_DST = 0x0080,            //!< Texture can be used the destination of a blit()
		PROTECTED = 0x0100,            //!< Texture can be used for protected content
		DEFAULT = UPLOADABLE | SAMPLEABLE,   //!< Default texture usage
		ALL_ATTACHMENTS = COLOR_ATTACHMENT | DEPTH_ATTACHMENT | STENCIL_ATTACHMENT | SUBPASS_INPUT,   //!< Mask of all attachments
	};

	ENUM_OPT(EUsage)

	static filament::Texture::Usage ConvertEnum(EUsage pUsage)
	{
		return static_cast<filament::Texture::Usage>(pUsage);
	}

	enum class EFormat : uint8_t
	{
		R,                  //!< One Red channel, float
		R_INTEGER,          //!< One Red channel, integer
		RG,                 //!< Two Red and Green channels, float
		RG_INTEGER,         //!< Two Red and Green channels, integer
		RGB,                //!< Three Red, Green and Blue channels, float
		RGB_INTEGER,        //!< Three Red, Green and Blue channels, integer
		RGBA,               //!< Four Red, Green, Blue and Alpha channels, float
		RGBA_INTEGER,       //!< Four Red, Green, Blue and Alpha channels, integer
		UNUSED,             // used to be rgbm
		DEPTH_COMPONENT,    //!< Depth, 16-bit or 24-bits usually
		DEPTH_STENCIL,      //!< Two Depth (24-bits) + Stencil (8-bits) channels
		ALPHA               //! One Alpha channel, float
	};

	static filament::Texture::Format ConvertEnum(EFormat pFormat)
	{
		return static_cast<filament::Texture::Format>(pFormat);
	}

	enum class EInternalFormat : uint16_t
	{
		// 8-bits per element
		R8, R8_SNORM, R8UI, R8I, STENCIL8,

		// 16-bits per element
		R16F, R16UI, R16I,
		RG8, RG8_SNORM, RG8UI, RG8I,
		RGB565,
		RGB9_E5, // 9995 is actually 32 bpp but it's here for historical reasons.
		RGB5_A1,
		RGBA4,
		DEPTH16,

		// 24-bits per element
		RGB8, SRGB8, RGB8_SNORM, RGB8UI, RGB8I,
		DEPTH24,

		// 32-bits per element
		R32F, R32UI, R32I,
		RG16F, RG16UI, RG16I,
		R11F_G11F_B10F,
		RGBA8, SRGB8_A8, RGBA8_SNORM,
		UNUSED, // used to be rgbm
		RGB10_A2, RGBA8UI, RGBA8I,
		DEPTH32F, DEPTH24_STENCIL8, DEPTH32F_STENCIL8,

		// 48-bits per element
		RGB16F, RGB16UI, RGB16I,

		// 64-bits per element
		RG32F, RG32UI, RG32I,
		RGBA16F, RGBA16UI, RGBA16I,

		// 96-bits per element
		RGB32F, RGB32UI, RGB32I,

		// 128-bits per element
		RGBA32F, RGBA32UI, RGBA32I,

		// compressed formats

		// Mandatory in GLES 3.0 and GL 4.3
		EAC_R11, EAC_R11_SIGNED, EAC_RG11, EAC_RG11_SIGNED,
		ETC2_RGB8, ETC2_SRGB8,
		ETC2_RGB8_A1, ETC2_SRGB8_A1,
		ETC2_EAC_RGBA8, ETC2_EAC_SRGBA8,

		// Available everywhere except Android/iOS
		DXT1_RGB, DXT1_RGBA, DXT3_RGBA, DXT5_RGBA,
		DXT1_SRGB, DXT1_SRGBA, DXT3_SRGBA, DXT5_SRGBA,

		// ASTC formats are available with a GLES extension
		RGBA_ASTC_4x4,
		RGBA_ASTC_5x4,
		RGBA_ASTC_5x5,
		RGBA_ASTC_6x5,
		RGBA_ASTC_6x6,
		RGBA_ASTC_8x5,
		RGBA_ASTC_8x6,
		RGBA_ASTC_8x8,
		RGBA_ASTC_10x5,
		RGBA_ASTC_10x6,
		RGBA_ASTC_10x8,
		RGBA_ASTC_10x10,
		RGBA_ASTC_12x10,
		RGBA_ASTC_12x12,
		SRGB8_ALPHA8_ASTC_4x4,
		SRGB8_ALPHA8_ASTC_5x4,
		SRGB8_ALPHA8_ASTC_5x5,
		SRGB8_ALPHA8_ASTC_6x5,
		SRGB8_ALPHA8_ASTC_6x6,
		SRGB8_ALPHA8_ASTC_8x5,
		SRGB8_ALPHA8_ASTC_8x6,
		SRGB8_ALPHA8_ASTC_8x8,
		SRGB8_ALPHA8_ASTC_10x5,
		SRGB8_ALPHA8_ASTC_10x6,
		SRGB8_ALPHA8_ASTC_10x8,
		SRGB8_ALPHA8_ASTC_10x10,
		SRGB8_ALPHA8_ASTC_12x10,
		SRGB8_ALPHA8_ASTC_12x12,

		// RGTC formats available with a GLES extension
		RED_RGTC1,              // BC4 unsigned
		SIGNED_RED_RGTC1,       // BC4 signed
		RED_GREEN_RGTC2,        // BC5 unsigned
		SIGNED_RED_GREEN_RGTC2, // BC5 signed

		// BPTC formats available with a GLES extension
		RGB_BPTC_SIGNED_FLOAT,  // BC6H signed
		RGB_BPTC_UNSIGNED_FLOAT,// BC6H unsigned
		RGBA_BPTC_UNORM,        // BC7
		SRGB_ALPHA_BPTC_UNORM,  // BC7 sRGB
	};

	static filament::Texture::InternalFormat ConvertEnum(EInternalFormat pInternalFormat)
	{
		return static_cast<filament::Texture::InternalFormat>(pInternalFormat);
	}

	enum class EMinFilter : uint8_t
	{
		// don't change the enums values
		NEAREST = 0,                //!< No filtering. Nearest neighbor is used.
		LINEAR = 1,                 //!< Box filtering. Weighted average of 4 neighbors is used.
		NEAREST_MIPMAP_NEAREST = 2, //!< Mip-mapping is activated. But no filtering occurs.
		LINEAR_MIPMAP_NEAREST = 3,  //!< Box filtering within a mip-map level.
		NEAREST_MIPMAP_LINEAR = 4,  //!< Mip-map levels are interpolated, but no other filtering occurs.
		LINEAR_MIPMAP_LINEAR = 5    //!< Both interpolated Mip-mapping and linear filtering are used.
	};

	static filament::TextureSampler::MinFilter ConvertEnum(EMinFilter pMinFilter)
	{
		return static_cast<filament::TextureSampler::MinFilter>(pMinFilter);
	}

	enum class EMagFilter : uint8_t
	{
		// don't change the enums values
		NEAREST = 0,                //!< No filtering. Nearest neighbor is used.
		LINEAR = 1,                 //!< Box filtering. Weighted average of 4 neighbors is used.
	};

	static filament::TextureSampler::MagFilter ConvertEnum(EMagFilter pMagFilter)
	{
		return static_cast<filament::TextureSampler::MagFilter>(pMagFilter);
	}

	enum class EWrapMode : uint8_t
	{
		CLAMP_TO_EDGE,      //!< clamp-to-edge. The edge of the texture extends to infinity.
		REPEAT,             //!< repeat. The texture infinitely repeats in the wrap direction.
		MIRRORED_REPEAT,    //!< mirrored-repeat. The texture infinitely repeats and mirrors in the wrap direction.
	};

	static filament::TextureSampler::WrapMode ConvertEnum(EWrapMode pWrapMode)
	{
		return static_cast<filament::TextureSampler::WrapMode>(pWrapMode);
	}
}