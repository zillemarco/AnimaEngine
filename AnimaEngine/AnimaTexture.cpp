#include "AnimaTexture.h"
#include "AnimaTools.h"
#include "AnimaXmlTranslators.h"

BEGIN_ANIMA_ENGINE_NAMESPACE

AFloat Clamp(const AFloat& value, const AFloat& low, const AFloat& high)
{
	return value < low ? low : (value > high ? high : value);
}

AnimaTexture::AnimaTexture(AnimaAllocator* allocator, const AnimaString& sourceFileName)
	: AnimaNamedObject(AnimaString("AnimaTexture"), allocator)
{
	IMPLEMENT_ANIMA_CLASS(AnimaTexture);

	_mipMapLevels = 0;
	_width = 0;
	_height = 0;
	_depth = 0;
	_textureID = 0;

	_textureTarget	= TEXTURE_TARGET_NONE;
	_minFilter		= TEXTURE_MIN_FILTER_MODE_LINEAR_MIPMAP_LINEAR;
	_magFilter		= TEXTURE_MAG_FILTER_MODE_LINEAR;
	_internalFormat = TEXTURE_INTERNAL_FORMAT_RGB;
	_format			= TEXTURE_FORMAT_RGB;
	_dataType		= TEXTURE_DATA_TYPE_UNSIGNED_BYTE;
	_clampS			= TEXTURE_CLAMP_REPEAT;
	_clampT			= TEXTURE_CLAMP_REPEAT;
	_clampR			= TEXTURE_CLAMP_REPEAT;
	_attachment		= TEXTURE_ATTACHMENT_NONE;
	
	_sourceFileName = sourceFileName;

	_borderColor = AnimaColor4f(0.0f);
	_generateMipMaps = false;	
	_renderTargetsReady = false;
	_texturesReady = false;
	_needsResize = false;
	_frameBuffer = 0;
	_renderBuffer = 0;
}


AnimaTexture::AnimaTexture(AnimaAllocator* allocator, const AnimaString& name, AUint width, AUint height, const AnimaString& sourceFileName)
	: AnimaNamedObject(name, allocator)
{
	IMPLEMENT_ANIMA_CLASS(AnimaTexture);
	
	_textureTarget	= TEXTURE_TARGET_NONE;
	_minFilter		= TEXTURE_MIN_FILTER_MODE_LINEAR_MIPMAP_LINEAR;
	_magFilter		= TEXTURE_MAG_FILTER_MODE_LINEAR;
	_internalFormat = TEXTURE_INTERNAL_FORMAT_RGB;
	_format			= TEXTURE_FORMAT_RGB;
	_dataType		= TEXTURE_DATA_TYPE_UNSIGNED_BYTE;
	_clampS			= TEXTURE_CLAMP_REPEAT;
	_clampT			= TEXTURE_CLAMP_REPEAT;
	_clampR			= TEXTURE_CLAMP_REPEAT;
	_attachment		= TEXTURE_ATTACHMENT_NONE;
	
	_sourceFileName = sourceFileName;
	
	_borderColor = AnimaColor4f(0.0f);
	_generateMipMaps = false;
	
	_name = name;

	_width = width;
	_height = height;
	_depth = 0;
	_mipMapLevels = 0;
	_texturesReady = false;
	_needsResize = false;
	_renderTargetsReady = false;

	_textureID = 0;
	_frameBuffer = 0;
	_renderBuffer = 0;
}


AnimaTexture::AnimaTexture(AnimaAllocator* allocator, const AnimaString& name, AUint width, AUint height, AUint depth, const AnimaString& sourceFileName)
	: AnimaNamedObject(name, allocator)
{
	IMPLEMENT_ANIMA_CLASS(AnimaTexture);
	
	_textureTarget	= TEXTURE_TARGET_NONE;
	_minFilter		= TEXTURE_MIN_FILTER_MODE_LINEAR_MIPMAP_LINEAR;
	_magFilter		= TEXTURE_MAG_FILTER_MODE_LINEAR;
	_internalFormat = TEXTURE_INTERNAL_FORMAT_RGB;
	_format			= TEXTURE_FORMAT_RGB;
	_dataType		= TEXTURE_DATA_TYPE_UNSIGNED_BYTE;
	_clampS			= TEXTURE_CLAMP_REPEAT;
	_clampT			= TEXTURE_CLAMP_REPEAT;
	_clampR			= TEXTURE_CLAMP_REPEAT;
	_attachment		= TEXTURE_ATTACHMENT_NONE;
	
	_sourceFileName = sourceFileName;
	
	_borderColor = AnimaColor4f(0.0f);
	
	_name = name;

	_width = width;
	_height = height;
	_depth = depth;
	_mipMapLevels = 0;
	_texturesReady = false;
	_needsResize = false;
	_renderTargetsReady = false;
	_generateMipMaps = false;

	_textureID = 0;
	_frameBuffer = 0;
	_renderBuffer = 0;
}

AnimaTexture::AnimaTexture(AnimaAllocator* allocator, const AnimaString& name, AUint width, AUint height, AUchar* data, AUint dataSize, const AnimaString& sourceFileName)
	: AnimaNamedObject(name, allocator)
{
	IMPLEMENT_ANIMA_CLASS(AnimaTexture);

	SetData(data, dataSize, 0);
	
	_textureTarget	= TEXTURE_TARGET_NONE;
	_minFilter		= TEXTURE_MIN_FILTER_MODE_LINEAR_MIPMAP_LINEAR;
	_magFilter		= TEXTURE_MAG_FILTER_MODE_LINEAR;
	_internalFormat = TEXTURE_INTERNAL_FORMAT_RGB;
	_format			= TEXTURE_FORMAT_RGB;
	_dataType		= TEXTURE_DATA_TYPE_UNSIGNED_BYTE;
	_clampS			= TEXTURE_CLAMP_REPEAT;
	_clampT			= TEXTURE_CLAMP_REPEAT;
	_clampR			= TEXTURE_CLAMP_REPEAT;
	_attachment		= TEXTURE_ATTACHMENT_NONE;
	
	_sourceFileName = sourceFileName;
	
	_borderColor = AnimaColor4f(0.0f);
	
	_name = name;
		
	_width = width;
	_height = height;
	_depth = 0;
	_mipMapLevels = 0;
	_texturesReady = false;
	_needsResize = false;
	_renderTargetsReady = false;
	_generateMipMaps = false;

	_textureID = 0;
	_frameBuffer = 0;
	_renderBuffer = 0;
}

AnimaTexture::AnimaTexture(AnimaAllocator* allocator, const AnimaString& name, AUint width, AUint height, AUint depth, AUchar* data, AUint dataSize, const AnimaString& sourceFileName)
	: AnimaNamedObject(name, allocator)
{
	IMPLEMENT_ANIMA_CLASS(AnimaTexture);

	SetData(data, dataSize, 0);
	
	_textureTarget	= TEXTURE_TARGET_NONE;
	_minFilter		= TEXTURE_MIN_FILTER_MODE_LINEAR_MIPMAP_LINEAR;
	_magFilter		= TEXTURE_MAG_FILTER_MODE_LINEAR;
	_internalFormat = TEXTURE_INTERNAL_FORMAT_RGB;
	_format			= TEXTURE_FORMAT_RGB;
	_dataType		= TEXTURE_DATA_TYPE_UNSIGNED_BYTE;
	_clampS			= TEXTURE_CLAMP_REPEAT;
	_clampT			= TEXTURE_CLAMP_REPEAT;
	_clampR			= TEXTURE_CLAMP_REPEAT;
	_attachment		= TEXTURE_ATTACHMENT_NONE;
	
	_sourceFileName = sourceFileName;
	
	_borderColor = AnimaColor4f(0.0f);
	
	_name = name;

	_width = width;
	_height = height;
	_depth = depth;
	_mipMapLevels = 0;
	_texturesReady = false;
	_needsResize = false;
	_renderTargetsReady = false;
	_generateMipMaps = false;

	_textureID = 0;
	_frameBuffer = 0;
	_renderBuffer = 0;
}

AnimaTexture::AnimaTexture(const AnimaTexture& src)
	: AnimaNamedObject(src)
{
	SetMinFilter(src._minFilter);
	SetMagFilter(src._magFilter);
	SetFormat(src._format);
	SetInternalFormat(src._internalFormat);
	SetDataType(src._dataType);
	SetClampS(src._clampS);
	SetClampT(src._clampT);
	SetClampR(src._clampR);
	SetAttachment(src._attachment);
	SetBorderColor(src._borderColor);
	SetSourceFileName(src._sourceFileName);
	
	_textureID = 0;
	_frameBuffer = 0;
	_renderBuffer = 0;

	_mipMapLevels = src._mipMapLevels;
	_generateMipMaps = src._generateMipMaps;
	_textureTarget = src._textureTarget;
	_width = src._width;
	_height = src._height;
	_depth = src._depth;
	_texturesReady = false;
	_needsResize = false;
	_renderTargetsReady = false;

	CopyData(src);
}

AnimaTexture::AnimaTexture(AnimaTexture&& src)
	: AnimaNamedObject(src)
{
	SetMinFilter(src._minFilter);
	SetMagFilter(src._magFilter);
	SetFormat(src._format);
	SetInternalFormat(src._internalFormat);
	SetDataType(src._dataType);
	SetClampS(src._clampS);
	SetClampT(src._clampT);
	SetClampR(src._clampR);
	SetAttachment(src._attachment);
	SetBorderColor(src._borderColor);
	SetSourceFileName(src._sourceFileName);

	_textureID = 0;
	_frameBuffer = 0;
	_renderBuffer = 0;

	_mipMapLevels = src._mipMapLevels;
	_generateMipMaps = src._generateMipMaps;
	_textureTarget = src._textureTarget;
	_width = src._width;
	_height = src._height;
	_depth = src._depth;
	_texturesReady = false;
	_needsResize = false;
	_renderTargetsReady = false;

	CopyData(src);
}

AnimaTexture::~AnimaTexture()
{
	Unload();
}

AnimaTexture& AnimaTexture::operator=(const AnimaTexture& src)
{
	if (this != &src)
	{
		Unload();
		
		AnimaNamedObject::operator=(src);

		SetMinFilter(src._minFilter);
		SetMagFilter(src._magFilter);
		SetFormat(src._format);
		SetInternalFormat(src._internalFormat);
		SetDataType(src._dataType);
		SetClampS(src._clampS);
		SetClampT(src._clampT);
		SetClampR(src._clampR);
		SetAttachment(src._attachment);
		SetBorderColor(src._borderColor);
		SetSourceFileName(src._sourceFileName);
		
		_textureID = 0;
		_frameBuffer = 0;
		_renderBuffer = 0;
		
		_mipMapLevels = src._mipMapLevels;
		_generateMipMaps = src._generateMipMaps;
		_textureTarget = src._textureTarget;
		_width = src._width;
		_height = src._height;
		_depth = src._depth;
		_texturesReady = false;
		_needsResize = false;
		_renderTargetsReady = false;

		CopyData(src);
	}
	return *this;
}

AnimaTexture& AnimaTexture::operator=(AnimaTexture&& src)
{
	if (this != &src)
	{
		Unload();

		AnimaNamedObject::operator=(src);

		SetMinFilter(src._minFilter);
		SetMagFilter(src._magFilter);
		SetFormat(src._format);
		SetInternalFormat(src._internalFormat);
		SetDataType(src._dataType);
		SetClampS(src._clampS);
		SetClampT(src._clampT);
		SetClampR(src._clampR);
		SetAttachment(src._attachment);
		SetBorderColor(src._borderColor);
		SetSourceFileName(src._sourceFileName);

		_textureID = 0;
		_frameBuffer = 0;
		_renderBuffer = 0;
		
		_mipMapLevels = src._mipMapLevels;
		_generateMipMaps = src._generateMipMaps;
		_textureTarget = src._textureTarget;
		_width = src._width;
		_height = src._height;
		_depth = src._depth;
		_texturesReady = false;
		_needsResize = false;
		_renderTargetsReady = false;

		CopyData(src);
	}
	return *this;
}

ptree AnimaTexture::GetObjectTree(bool saveName) const
{
	ptree tree;
	
	if(saveName)
	{
		tree.add("AnimaTexture.Name", GetName());
	}
	
	namespace fs = boost::filesystem;
	
	tree.add("AnimaTexture.Width", GetWidth());
	tree.add("AnimaTexture.Height", GetHeight());
	tree.add("AnimaTexture.Depth", GetDepth());
	tree.add("AnimaTexture.Target", GetTextureTarget());
	tree.add("AnimaTexture.Format", GetFormat());
	tree.add("AnimaTexture.InternalFormat", GetInternalFormat());
	tree.add("AnimaTexture.MinFilter", GetMinFilter());
	tree.add("AnimaTexture.MagFilter", GetMagFilter());
	tree.add("AnimaTexture.Attachment", GetAttachment());
	tree.add("AnimaTexture.DataType", GetDataType());
	tree.add("AnimaTexture.ClampS", GetClampS());
	tree.add("AnimaTexture.ClampT", GetClampT());
	tree.add("AnimaTexture.ClampR", GetClampR());
	tree.add("AnimaTexture.MipMapLevels", GetMipMapLevels());
	tree.add("AnimaTexture.BorderColor", GetBorderColor());
	tree.add("AnimaTexture.GenerateMipMaps", IsGenerateMipMap());
	
//	AnimaString textureSourceFileName = GetSourceFileName();
//	if(textureSourceFileName.empty() || GetTextureTarget() == TEXTURE_TARGET_CUBE)
//	{
		AUint mipMapLevels = fmax(GetMipMapLevels(), 1);
		
		if(GetTextureTarget() == TEXTURE_TARGET_CUBE)
		{
			ptree cubeTree;
			for(AInt cubeIndex = 0; cubeIndex < 6; cubeIndex++)
			{
				AnimaTextureCubeIndex textureCubeIndex = (AnimaTextureCubeIndex)cubeIndex;
				ptree cubeFaceTree;
				cubeFaceTree.add("Index", textureCubeIndex);
				
				ptree surfacesTree;
				
				for(AUint mipIndex = 0; mipIndex < mipMapLevels; mipIndex++)
				{
					const AnimaArray<AUchar>* data = GetDataAsArray(textureCubeIndex, mipIndex);
					
					if(data != nullptr)
					{
						AnimaString base64Data = AnimaTools::Base64Encode(*data);
						surfacesTree.add("Surface", base64Data);
					}
					else
					{
						surfacesTree.add("Surface", "");
					}
				}
				cubeFaceTree.add_child("Surfaces", surfacesTree);
				
				cubeTree.add_child("CubeFace", cubeFaceTree);
			}
			tree.add_child("AnimaTexture.CubeFaces", cubeTree);
		}
		else
		{
			ptree surfacesTree;
			
			for(AInt mipIndex = 0; mipIndex < mipMapLevels; mipIndex++)
			{
				const AnimaArray<AUchar>* data = GetDataAsArray(mipIndex);
				
				if(data != nullptr)
				{
					AnimaString base64Data = AnimaTools::Base64Encode(*data);
					surfacesTree.add("Surface", base64Data);
				}
				else
				{
					surfacesTree.add("Surface", "");
				}
			}
			
			tree.add_child("AnimaTexture.Surfaces", surfacesTree);
		}
//	}
//	else
//	{
//		fs::path sourcePath(textureSourceFileName);
//		AnimaString destinationFileName = (fs::path(GetSavingDirectory()) / sourcePath.filename()).string();
//		
//		fs::copy_file(fs::path(textureSourceFileName), fs::path(destinationFileName), fs::copy_option::overwrite_if_exists);
//		tree.add("AnimaTexture.FileName", destinationFileName);
//	}
	
	tree.add_child("AnimaTexture.NamedObject", AnimaNamedObject::GetObjectTree(false));
	
	return tree;
}

bool AnimaTexture::ReadObject(const ptree& objectTree, AnimaScene* scene, bool readName)
{
	try
	{
		if(readName)
			SetName(objectTree.get<AnimaString>("AnimaTexture.Name"));
		
		SetWidth(objectTree.get<AFloat>("AnimaTexture.Width", 0.0f));
		SetHeight(objectTree.get<AFloat>("AnimaTexture.Height", 0.0f));
		SetDepth(objectTree.get<AFloat>("AnimaTexture.Depth", 0.0f));
		SetTextureTarget(objectTree.get<AnimaTextureTarget>("AnimaTexture.Target", TEXTURE_TARGET_NONE));
		SetFormat(objectTree.get<AnimaTextureFormat>("AnimaTexture.Format", TEXTURE_FORMAT_RGB));
		SetInternalFormat(objectTree.get<AnimaTextureInternalFormat>("AnimaTexture.InternalFormat", TEXTURE_INTERNAL_FORMAT_RG8));
		SetMinFilter(objectTree.get<AnimaTextureMinFilterMode>("AnimaTexture.MinFilter", TEXTURE_MIN_FILTER_MODE_LINEAR_MIPMAP_LINEAR));
	 	SetMagFilter(objectTree.get<AnimaTextureMagFilterMode>("AnimaTexture.MagFilter", TEXTURE_MAG_FILTER_MODE_LINEAR));
		SetAttachment(objectTree.get<AnimaTextureAttachment>("AnimaTexture.Attachment", TEXTURE_ATTACHMENT_NONE));
		SetDataType(objectTree.get<AnimaTextureDataType>("AnimaTexture.DataType", TEXTURE_DATA_TYPE_UNSIGNED_BYTE));
		SetClampS(objectTree.get<AnimaTextureClampMode>("AnimaTexture.ClampS", TEXTURE_CLAMP_REPEAT));
	 	SetClampT(objectTree.get<AnimaTextureClampMode>("AnimaTexture.ClampT", TEXTURE_CLAMP_REPEAT));
		SetClampR(objectTree.get<AnimaTextureClampMode>("AnimaTexture.ClampR", TEXTURE_CLAMP_REPEAT));
		SetMipMapLevels(objectTree.get<AUint>("AnimaTexture.MipMapLevels", 0));
		SetBorderColor(objectTree.get<AnimaColor4f>("AnimaTexture.BorderColor", AnimaColor4f(0.0f)));
		SetGenerateMipMap(objectTree.get<bool>("AnimaTexture.GenerateMipMaps", false));
		
		if(GetTextureTarget() == TEXTURE_TARGET_CUBE)
		{
			AUint faceIndex = 0;
			for(auto& cubeFace : objectTree.get_child("AnimaTexture.CubeFaces"))
			{
				if(cubeFace.first == "CubeFace")
				{
					AnimaTextureCubeIndex cubeIndex = (AnimaTextureCubeIndex)faceIndex;
					AUint surfaceIndex = 0;
					for(auto& surface : cubeFace.second.get_child("Surfaces"))
					{
						if(surface.first == "Surface")
						{
							AnimaString stringData = surface.second.get_value<AnimaString>("");
							
							if(stringData.empty())
								return false;
							
							AnimaArray<AUchar> data = AnimaTools::Base64Decode(stringData);
							SetData(&data[0], data.size(), cubeIndex, surfaceIndex);
							surfaceIndex++;
						}
					}
					
					faceIndex++;
				}
			}
		}
		else
		{
			AUint surfaceIndex = 0;
			for(auto& surface : objectTree.get_child("AnimaTexture.Surfaces"))
			{
				if(surface.first == "Surface")
				{
					AnimaString stringData = surface.second.get_value<AnimaString>("");
					
					if(stringData.empty())
						return false;
					
					AnimaArray<AUchar> data = AnimaTools::Base64Decode(stringData);
					SetData(&data[0], data.size(), surfaceIndex);
					surfaceIndex++;
				}
			}
		}
		
		ptree namedObjectTree = objectTree.get_child("AnimaTexture.NamedObject");
		return AnimaNamedObject::ReadObject(namedObjectTree, scene, false);
	}
	catch (boost::property_tree::ptree_bad_path& exception)
	{
		AnimaLogger::LogMessageFormat("ERROR - Error parsing texture: %s", exception.what());
		return false;
	}
	catch (boost::property_tree::ptree_bad_data& exception)
	{
		AnimaLogger::LogMessageFormat("ERROR - Error parsing texture: %s", exception.what());
		return false;
	}
	
	return true;
}

AUint AnimaTexture::GetID(AUint index) const
{
	return _textureID;
}

void AnimaTexture::SetWidth(AUint width)
{
	_width = width;
}

AUint AnimaTexture::GetWidth() const
{
	return _width;
}

void AnimaTexture::SetHeight(AUint height)
{
	_height = height;
}

AUint AnimaTexture::GetHeight() const
{
	return _height;
}

void AnimaTexture::SetDepth(AUint depth)
{
	_depth = depth;
}

AUint AnimaTexture::GetDepth() const
{
	return _depth;
}

void AnimaTexture::SetMipMapLevels(AUint levels)
{
	_mipMapLevels = fmin((AUint)TEXUTRE_MAX_SURFACES, levels);

	AInt count = _faces.size();
	for (AInt i = 0; i < count; i++)
	{
		_faces[i].resize(TEXUTRE_MAX_SURFACES);

		AUint w = _width;
		AUint h = _height;

		for (AUint j = 1; j <= TEXUTRE_MAX_SURFACES; j++)
		{
			_faces[i][j - 1].SetWidth(w);
			_faces[i][j - 1].SetHeight(h);

			w = fmax(1, w / 2);
			h = fmax(1, h / 2);
		}
	}
}

AUint AnimaTexture::GetMipMapLevels() const
{
	return _mipMapLevels;
}

void AnimaTexture::SetGenerateMipMap(bool generate)
{
	_generateMipMaps = generate;
}

bool AnimaTexture::IsGenerateMipMap() const
{
	return _generateMipMaps;
}

void AnimaTexture::SetFormat(AnimaTextureFormat format)
{
	_format = format;
}

AnimaTextureFormat AnimaTexture::GetFormat() const
{
	return _format;
}

void AnimaTexture::SetMinFilter(AnimaTextureMinFilterMode filter)
{
	_minFilter = filter;
}

AnimaTextureMinFilterMode AnimaTexture::GetMinFilter() const
{
	return _minFilter;
}

void AnimaTexture::SetMagFilter(AnimaTextureMagFilterMode filter)
{
	_magFilter = filter;
}

AnimaTextureMagFilterMode AnimaTexture::GetMagFilter() const
{
	return _magFilter;
}

void AnimaTexture::SetAttachment(AnimaTextureAttachment attachment)
{
	_attachment = attachment;
}

AnimaTextureAttachment AnimaTexture::GetAttachment() const
{
	return _attachment;
}

void AnimaTexture::SetInternalFormat(AnimaTextureInternalFormat internalFormat)
{
	_internalFormat = internalFormat;
}

AnimaTextureInternalFormat AnimaTexture::GetInternalFormat() const
{
	return _internalFormat;
}

void AnimaTexture::SetDataType(AnimaTextureDataType dataType)
{
	_dataType = dataType;
}

AnimaTextureDataType AnimaTexture::GetDataType() const
{
	return _dataType;
}

bool AnimaTexture::SetData(AUchar* data, AUint dataSize, AUint mipMapIndex)
{
	if (_textureTarget == TEXTURE_TARGET_2D)
	{
		if (_faces.size() != 1)
		{
			_faces.clear();
			_faces.resize(1);
			_faces[0].resize(TEXUTRE_MAX_SURFACES);

			AUint w = _width;
			AUint h = _height;

			for (AUint i = 1; i <= TEXUTRE_MAX_SURFACES; i++)
			{
				AnimaTextureSurface surface;
				surface.SetWidth(w);
				surface.SetWidth(h);

				_faces[0][i - 1] = surface;

				w = fmax(1, w / 2);
				h = fmax(1, h / 2);
			}
		}

		_faces[0][mipMapIndex].SetData(data, dataSize);

		return true;
	}

	return false;
}

bool AnimaTexture::SetData(AUchar* data, AUint dataSize, AnimaTextureCubeIndex index, AUint mipMapIndex)
{
	if (_textureTarget == TEXTURE_TARGET_CUBE)
	{
		// se l'array ha un solo elemento al momento vuol dire che prima la texture non era 3D
		// e quindi vado a ripulire tutto e importare l'array per avere 6 elementi
		if (_faces.size() != 6)
		{
			_faces.clear();
			_faces.resize(6);

			for (AInt i = 0; i < 6; i++)
			{
				_faces[i].resize(TEXUTRE_MAX_SURFACES);

				AUint w = _width;
				AUint h = _height;

				for (AUint j = 1; j <= TEXUTRE_MAX_SURFACES; j++)
				{
					AnimaTextureSurface surface;
					surface.SetWidth(w);
					surface.SetWidth(h);

					_faces[i][j - 1] = surface;

					w = fmax(1, w / 2);
					h = fmax(1, h / 2);
				}
			}
		}
		
		_faces[index][mipMapIndex].SetData(data, dataSize);

		return true;
	}

	return false;
}

const AUchar* AnimaTexture::GetData(AUint surfaceIndex) const
{
	// Posso tornare il valore solamente se la texture � di tipo 2D e l'array di buffer ha un solo elemento
	if (_textureTarget == TEXTURE_TARGET_2D && _faces.size() == 1)
	{
		if (_faces[0].size() > 0)
			return _faces[0][surfaceIndex].GetData();
	}

	return nullptr;
}

const AnimaArray<AUchar>* AnimaTexture::GetDataAsArray(AUint surfaceIndex) const
{
	// Posso tornare il valore solamente se la texture � di tipo 2D e l'array di buffer ha un solo elemento
	if (_textureTarget == TEXTURE_TARGET_2D && _faces.size() == 1)
	{
		if (_faces[0].size() > 0)
			return _faces[0][surfaceIndex].GetDataAsArray();
	}
	
	return nullptr;
}

const AUchar* AnimaTexture::GetData(AnimaTextureCubeIndex index, AUint surfaceIndex) const
{
	// Posso tornare il valore solamente se la texture � di tipo 3D e l'array di buffer ha sei elementi
	if (_textureTarget == TEXTURE_TARGET_CUBE && _faces.size() == 6)
	{
		if (_faces[index].size() > 0)
			return _faces[index][surfaceIndex].GetData();
	}

	return nullptr;
}

const AnimaArray<AUchar>* AnimaTexture::GetDataAsArray(AnimaTextureCubeIndex index, AUint surfaceIndex) const
{
	// Posso tornare il valore solamente se la texture � di tipo 3D e l'array di buffer ha sei elementi
	if (_textureTarget == TEXTURE_TARGET_CUBE && _faces.size() == 6)
	{
		if (_faces[index].size() > 0)
			return _faces[index][surfaceIndex].GetDataAsArray();
	}
	
	return nullptr;
}

void AnimaTexture::SetTextureTarget(AnimaTextureTarget target)
{
	if (target != _textureTarget)
	{
		ANIMA_ASSERT(!IsReady());

		_faces.clear();

		if (target == TEXTURE_TARGET_2D)
			_faces.resize(1);
		else if (target == TEXTURE_TARGET_CUBE)
			_faces.resize(6);

		_textureTarget = target;
	}
}

AnimaTextureTarget AnimaTexture::GetTextureTarget() const
{
	return _textureTarget;
}

void AnimaTexture::SetClampS(AnimaTextureClampMode clamp)
{
	_clampS = clamp;
}

AnimaTextureClampMode AnimaTexture::GetClampS() const
{
	return _clampS;
}

void AnimaTexture::SetClampT(AnimaTextureClampMode clamp)
{
	_clampT = clamp;
}

AnimaTextureClampMode AnimaTexture::GetClampT() const
{
	return _clampT;
}

void AnimaTexture::SetClampR(AnimaTextureClampMode clamp)
{
	_clampR = clamp;
}

AnimaTextureClampMode AnimaTexture::GetClampR() const
{
	return _clampR;
}

void AnimaTexture::SetBorderColor(const AnimaColor4f& color)
{
	_borderColor = color;
}

void AnimaTexture::SetBorderColor(const AFloat& r, const AFloat& g, const AFloat& b, const AFloat& a)
{
	_borderColor = AnimaColor4f(r, g, b, a);
}

AnimaColor4f AnimaTexture::GetBorderColor() const
{
	return _borderColor;
}

void AnimaTexture::SetSourceFileName(const AnimaString& sourceFileName)
{
	_sourceFileName = sourceFileName;
}

AnimaString AnimaTexture::GetSourceFileName() const
{
	return _sourceFileName;
}

bool AnimaTexture::Load()
{
	if (_texturesReady)
	{
		if (_needsResize)
			return ResizeTexture();
		return true;
	}
	
	if (glGetError() != GL_NO_ERROR)
		return false;

	AUint target = TargetToPlatform(_textureTarget);
	AUint clampS = ClampToPlatform(_clampS);
	AUint clampT = ClampToPlatform(_clampT);
	AUint clampR = ClampToPlatform(_clampR);
	AUint minFilter = MinFilterToPlatform(_minFilter);
	AUint magFilter = MagFilterToPlatform(_magFilter);
	AUint format = FormatToPlatform(_format);
	AUint internalFormat = InternalFormatToPlatform(_internalFormat);
	AUint dataType = DataTypeToPlatform(_dataType);
	
	glGenTextures(1, &_textureID);

	glBindTexture(target, _textureID);
	
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, magFilter);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minFilter);
	if (glGetError() != GL_NO_ERROR)
		return false;
	
	glTexParameterfv(target, GL_TEXTURE_BORDER_COLOR, _borderColor.vec);
	if (glGetError() != GL_NO_ERROR)
		return false;
	
	if (_textureTarget == TEXTURE_TARGET_2D)
	{
		glTexParameteri(target, GL_TEXTURE_WRAP_S, clampS);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, clampT);
		if (glGetError() != GL_NO_ERROR)
			return false;
		
		if (_mipMapLevels == 0 || _generateMipMaps)
		{
			const AUchar* data = nullptr;
			if (_faces.size() > 0 && _faces[0].size() > 0)
				data = _faces[0][0].GetData();

			glTexImage2D(target, 0, internalFormat, _width, _height, 0, format, dataType, data);
		}
		else if (_mipMapLevels > 0)
		{
			for (unsigned int level = 0; level < _mipMapLevels; level++)
			{
				AnimaTextureSurface* surface = &_faces[0][level];
				glTexImage2D(target, level, internalFormat, surface->GetWidth(), surface->GetHeight(), 0, format, dataType, surface->GetData());
			}
		}
		else
		{
			return false;
		}
	}
	else if (_textureTarget == TEXTURE_TARGET_CUBE)
	{
		glTexParameteri(target, GL_TEXTURE_WRAP_S, clampS);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, clampT);
		glTexParameteri(target, GL_TEXTURE_WRAP_R, clampR);

		if (glGetError() != GL_NO_ERROR)
			return false;

		glTexParameteri(target, GL_TEXTURE_CUBE_MAP_SEAMLESS, 1);
		if (glGetError() != GL_NO_ERROR)
		{
			glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
			if (glGetError() != GL_NO_ERROR)
				return false;
		}

		if (glGetError() != GL_NO_ERROR)
			return false;
		
		for (AInt i = 0; i < 6; i++)
		{
			if (_mipMapLevels == 0 || _generateMipMaps)
			{
				const AUchar* data = nullptr;
				if (_faces.size() > 0 && _faces[i].size() > 0)
					data = _faces[i][0].GetData();

				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalFormat, _width, _height, 0, format, dataType, data);
			}
			else if (_mipMapLevels > 0)
			{
				for (unsigned int level = 0; level < _mipMapLevels; level++)
				{
					AnimaTextureSurface* surface = &_faces[i][level];
					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, level, internalFormat, surface->GetWidth(), surface->GetHeight(), 0, format, dataType, surface->GetData());

					if (glGetError() != GL_NO_ERROR)
						return false;
				}

				glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, _mipMapLevels);

				if (glGetError() != GL_NO_ERROR)
					return false;
			}
			else
			{
				return false;
			}

			if (glGetError() != GL_NO_ERROR)
				return false;
		}
	}

	if (glGetError() != GL_NO_ERROR)
		return false;
	
	if (_generateMipMaps || 
		(_mipMapLevels == 0 && 
			(_minFilter == TEXTURE_MIN_FILTER_MODE_NEAREST_MIPMAP_NEAREST || _minFilter == TEXTURE_MIN_FILTER_MODE_NEAREST_MIPMAP_LINEAR || 
			_minFilter == TEXTURE_MIN_FILTER_MODE_LINEAR_MIPMAP_NEAREST || _minFilter == TEXTURE_MIN_FILTER_MODE_LINEAR_MIPMAP_LINEAR)))
	{
		glGenerateMipmap(target);

		AFloat maxAnisotropy;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
		glTexParameterf(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, Clamp(0.0f, 8.0f, maxAnisotropy));
	}
	else if (_mipMapLevels == 0)
	{ 
		glTexParameteri(target, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, 0);
	}

	if (glGetError() != GL_NO_ERROR)
		return false;

	glBindTexture(target, 0);

	_texturesReady = true;
	return true;
}

bool AnimaTexture::LoadRenderTargets()
{
	if (_renderTargetsReady && _texturesReady)
	{
		bool needsResize = _needsResize;
		bool loadResult = Load();

		if (loadResult && needsResize)
		{
			if (_renderBuffer != 0)
			{
				glBindRenderbuffer(GL_RENDERBUFFER, _renderBuffer);
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _width, _height);
			}
		}

		return loadResult;
	}

	AUint attachment = AttachmentToPlatform(_attachment);
	
	if (attachment == GL_NONE)
		return false;
	
	AUint drawBuffer;
	bool hasDepth = false;
	bool hasStencil = false;
	
	ANIMA_ASSERT(Load());

	if (attachment == GL_DEPTH_ATTACHMENT)
	{
		drawBuffer = GL_NONE;
		hasDepth = true;
	}
	else if (attachment == GL_STENCIL_ATTACHMENT)
	{
		drawBuffer = GL_NONE;
		hasStencil = true;
	}
	else if (attachment == GL_DEPTH_STENCIL_ATTACHMENT)
	{
		drawBuffer = GL_NONE;
		hasDepth = true;
		hasStencil = true;
	}
	else
		drawBuffer = attachment;
	
	if (_frameBuffer == 0)
	{
		glGenFramebuffers(1, &_frameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
	}
		
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, TargetToPlatform(_textureTarget), _textureID, 0);
	
	if (_frameBuffer == 0)
		return false;

	if (!hasDepth && !hasStencil)
	{
		glGenRenderbuffers(1, &_renderBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, _renderBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _renderBuffer);

		if (glGetError() != GL_NO_ERROR)
			return false;
	}
	else if (!hasDepth)
	{
		glGenRenderbuffers(1, &_renderBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, _renderBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _width, _height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _renderBuffer);

		if (glGetError() != GL_NO_ERROR)
			return false;
	}
	
	glDrawBuffers(1, &drawBuffer);

	if (glGetError() != GL_NO_ERROR)
		return false;

	AUint status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	switch (status)
	{
	case GL_FRAMEBUFFER_COMPLETE:
		break;
	case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
		printf("AnimaGBuffer error: unsupported extension\n");
		return false;
		break;
	default:
		printf("AnimaGBuffer error: unable to create the FBO\n");
		return false;
		break;
	}
	
	_renderTargetsReady = true;
	return true;
}

bool AnimaTexture::IsReady()
{
	return _texturesReady;
}

bool AnimaTexture::AreRenderTargetsReady()
{
	return _texturesReady && _renderTargetsReady;
}

void AnimaTexture::Unload()
{
	if (!IsReady())
		return;

	if (_textureID != 0)
	{
		glDeleteTextures(1, &_textureID);
		_textureID = 0;
	}

	if (AreRenderTargetsReady())
	{
		glDeleteFramebuffers(1, &_frameBuffer);
		glDeleteRenderbuffers(1, &_renderBuffer);
		_frameBuffer = 0;
		_renderBuffer = 0;
	}
		
	_texturesReady = false;
}

void AnimaTexture::Resize(AUint width, AUint height)
{
	if (width != _width || height != _height)
	{
		_width = width;
		_height = height;
		_needsResize = true;
	}
}

bool AnimaTexture::ResizeTexture()
{
	AUint target = TargetToPlatform(_textureTarget);
	AUint format = FormatToPlatform(_format);
	AUint internalFormat = InternalFormatToPlatform(_internalFormat);
	AUint dataType = DataTypeToPlatform(_dataType);

	glBindTexture(target, _textureID);

	if (_textureTarget == TEXTURE_TARGET_2D)
	{
		if (_mipMapLevels == 0 || _generateMipMaps)
		{
			const AUchar* data = nullptr;
			if (_faces.size() > 0 && _faces[0].size() > 0)
				data = _faces[0][0].GetData();

			glTexImage2D(target, 0, internalFormat, _width, _height, 0, format, dataType, data);
		}
		else if (_mipMapLevels > 0)
		{
			for (unsigned int level = 0; level < _mipMapLevels; level++)
			{
				AnimaTextureSurface* surface = &_faces[0][level];
				glTexImage2D(target, level, internalFormat, surface->GetWidth(), surface->GetHeight(), 0, format, dataType, surface->GetData());
			}
		}
		else
		{
			return false;
		}
	}
	else if (_textureTarget == TEXTURE_TARGET_CUBE)
	{
		for (AInt i = 0; i < 6; i++)
		{
			if (_mipMapLevels == 0 || _generateMipMaps)
			{
				const AUchar* data = nullptr;
				if (_faces.size() > 0 && _faces[i].size() > 0)
					data = _faces[i][0].GetData();

				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalFormat, _width, _height, 0, format, dataType, data);
			}
			else if (_mipMapLevels > 0)
			{
				for (unsigned int level = 0; level < _mipMapLevels; level++)
				{
					AnimaTextureSurface* surface = &_faces[i][level];
					glTexImage2D(target, level, internalFormat, surface->GetWidth(), surface->GetHeight(), 0, format, dataType, surface->GetData());
				}
			}
		}
	}

	if (glGetError() != GL_NO_ERROR)
	{
		glBindTexture(target, 0);
		return false;
	}

	glBindTexture(target, 0);
	_needsResize = false;

	return true;
}

void AnimaTexture::CopyData(const AnimaTexture& src)
{
	_faces = src._faces;
}

void AnimaTexture::Bind(AUint unit) const
{
	ANIMA_ASSERT(_texturesReady);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(TargetToPlatform(_textureTarget), _textureID);
}

void AnimaTexture::BindAsRenderTarget()
{
	ANIMA_ASSERT(LoadRenderTargets());
	
	glBindTexture(TargetToPlatform(_textureTarget), 0);
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
	glViewport(0, 0, _width, _height);
}

AUint AnimaTexture::TargetToPlatform(const AnimaTextureTarget& target)
{
	switch (target)
	{
	case TEXTURE_TARGET_2D:		return GL_TEXTURE_2D;
	case TEXTURE_TARGET_3D:		return GL_TEXTURE_3D;
	case TEXTURE_TARGET_CUBE:	return GL_TEXTURE_CUBE_MAP;
	default:					return GL_NONE;
	}
}

AUint AnimaTexture::ClampToPlatform(const AnimaTextureClampMode& clamp)
{
	switch (clamp)
	{
	case TEXTURE_CLAMP_REPEAT:			return GL_REPEAT;
	case TEXTURE_CLAMP_MIRRORED_REPEAT:	return GL_MIRRORED_REPEAT;
	case TEXTURE_CLAMP_TO_EDGE:			return GL_CLAMP_TO_EDGE;
	case TEXTURE_CLAMP_TO_BORDER:		return GL_CLAMP_TO_BORDER;
	default:							return GL_NONE;
	}
}

AUint AnimaTexture::MinFilterToPlatform(const AnimaTextureMinFilterMode& filter)
{
	switch (filter)
	{
	case TEXTURE_MIN_FILTER_MODE_NEAREST:					return GL_NEAREST;
	case TEXTURE_MIN_FILTER_MODE_LINEAR:					return GL_LINEAR;
	case TEXTURE_MIN_FILTER_MODE_NEAREST_MIPMAP_NEAREST:	return GL_NEAREST_MIPMAP_NEAREST;
	case TEXTURE_MIN_FILTER_MODE_NEAREST_MIPMAP_LINEAR:		return GL_NEAREST_MIPMAP_LINEAR;
	case TEXTURE_MIN_FILTER_MODE_LINEAR_MIPMAP_NEAREST:		return GL_LINEAR_MIPMAP_NEAREST;
	case TEXTURE_MIN_FILTER_MODE_LINEAR_MIPMAP_LINEAR:		return GL_LINEAR_MIPMAP_LINEAR;
	default:												return GL_NONE;
	}
}

AUint AnimaTexture::MagFilterToPlatform(const AnimaTextureMagFilterMode& filter)
{
	switch (filter)
	{
	case TEXTURE_MAG_FILTER_MODE_NEAREST:	return GL_NEAREST;
	case TEXTURE_MAG_FILTER_MODE_LINEAR:	return GL_LINEAR;
	default:								return GL_NONE;
	}
}

AUint AnimaTexture::CubeIndexToPlatform(const AnimaTextureCubeIndex& index)
{
	switch (index)
	{
	case POSITIVE_X:	return GL_TEXTURE_CUBE_MAP_POSITIVE_X;
	case NEGATIVE_X:	return GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
	case POSITIVE_Y:	return GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
	case NEGATIVE_Y:	return GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
	case POSITIVE_Z:	return GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
	case NEGATIVE_Z:	return GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
	default:			return GL_NONE;
	}
}

AUint AnimaTexture::FormatToPlatform(const AnimaTextureFormat& format)
{
	switch (format)
	{
	case TEXTURE_FORMAT_RED:							return GL_RED; break;
	case TEXTURE_FORMAT_GREEN:							return GL_GREEN; break;
	case TEXTURE_FORMAT_BLUE:							return GL_BLUE; break;
	case TEXTURE_FORMAT_RG:								return GL_RG; break;
	case TEXTURE_FORMAT_RGB:							return GL_RGB; break;
	case TEXTURE_FORMAT_RGBA:							return GL_RGBA; break;
	case TEXTURE_FORMAT_BGR:							return GL_BGR; break;
	case TEXTURE_FORMAT_BGRA:							return GL_BGRA; break;
	case TEXTURE_FORMAT_RED_INT:						return GL_RED_INTEGER; break;
	case TEXTURE_FORMAT_GREEN_INT:						return GL_GREEN_INTEGER; break;
	case TEXTURE_FORMAT_BLUE_INT:						return GL_BLUE_INTEGER; break;
	case TEXTURE_FORMAT_RG_INT:							return GL_RG_INTEGER; break;
	case TEXTURE_FORMAT_RGB_INT:						return GL_RGB_INTEGER; break;
	case TEXTURE_FORMAT_RGBA_INT:						return GL_RGBA_INTEGER; break;
	case TEXTURE_FORMAT_BGR_INT:						return GL_BGR_INTEGER; break;
	case TEXTURE_FORMAT_BGRA_INT:						return GL_BGRA_INTEGER; break;
	case TEXTURE_FORMAT_DEPTH:							return GL_DEPTH_COMPONENT; break;
	case TEXTURE_FORMAT_DEPTH_STENCIL:					return GL_DEPTH_STENCIL; break;
	case TEXTURE_FORMAT_STENCIL:						return GL_STENCIL_INDEX; break;
	case TEXTURE_FORMAT_COMPRESSED_RGBA_S3TC_DXT1_EXT:	return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; break;
	case TEXTURE_FORMAT_COMPRESSED_RGBA_S3TC_DXT3_EXT:	return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; break;
	case TEXTURE_FORMAT_COMPRESSED_RGBA_S3TC_DXT5_EXT:	return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; break;
	default:											return GL_NONE;
	}
}

AUint AnimaTexture::InternalFormatToPlatform(const AnimaTextureInternalFormat& internalFormat)
{
	switch (internalFormat)
	{
	case TEXTURE_INTERNAL_FORMAT_R8:				return GL_R8; break;
	case TEXTURE_INTERNAL_FORMAT_R8_SNORM:			return GL_R8_SNORM; break;
	case TEXTURE_INTERNAL_FORMAT_R16:				return GL_R16; break;
	case TEXTURE_INTERNAL_FORMAT_R16_SNORM:			return GL_R16_SNORM; break;
	case TEXTURE_INTERNAL_FORMAT_RG8:				return GL_RG8; break;
	case TEXTURE_INTERNAL_FORMAT_RG8_SNORM:			return GL_RG8_SNORM; break;
	case TEXTURE_INTERNAL_FORMAT_RG16:				return GL_RG16; break;
	case TEXTURE_INTERNAL_FORMAT_RG16_SNORM:		return GL_RG16_SNORM; break;
	case TEXTURE_INTERNAL_FORMAT_R3_G3_B2:			return GL_R3_G3_B2; break;
	case TEXTURE_INTERNAL_FORMAT_RGB4:				return GL_RGB4; break;
	case TEXTURE_INTERNAL_FORMAT_RGB5:				return GL_RGB5; break;
	case TEXTURE_INTERNAL_FORMAT_RGB565:			return GL_RGB565; break;
	case TEXTURE_INTERNAL_FORMAT_RGB8:				return GL_RGB8; break;
	case TEXTURE_INTERNAL_FORMAT_RGB8_SNORM:		return GL_RGB8_SNORM; break;
	case TEXTURE_INTERNAL_FORMAT_RGB10:				return GL_RGB10; break;
	case TEXTURE_INTERNAL_FORMAT_RGB12:				return GL_RGB12; break;
	case TEXTURE_INTERNAL_FORMAT_RGB16:				return GL_RGB16; break;
	case TEXTURE_INTERNAL_FORMAT_RGB16_SNORM:		return GL_RGB16_SNORM; break;
	case TEXTURE_INTERNAL_FORMAT_RGBA2:				return GL_RGBA2; break;
	case TEXTURE_INTERNAL_FORMAT_RGBA4:				return GL_RGBA4; break;
	case TEXTURE_INTERNAL_FORMAT_RGB5_A1:			return GL_RGB5_A1; break;
	case TEXTURE_INTERNAL_FORMAT_RGBA8:				return GL_RGBA8; break;
	case TEXTURE_INTERNAL_FORMAT_RGBA8_SNORM:		return GL_RGBA8_SNORM; break;
	case TEXTURE_INTERNAL_FORMAT_RGB10_A2:			return GL_RGB10_A2; break;
	case TEXTURE_INTERNAL_FORMAT_RGB10_A2UI:		return GL_RGB10_A2UI; break;
	case TEXTURE_INTERNAL_FORMAT_RGBA12:			return GL_RGBA12; break;
	case TEXTURE_INTERNAL_FORMAT_RGBA16:			return GL_RGBA16; break;
	case TEXTURE_INTERNAL_FORMAT_RGBA16_SNORM:		return GL_RGBA16_SNORM; break;
	case TEXTURE_INTERNAL_FORMAT_SRGB8:				return GL_SRGB8; break;
	case TEXTURE_INTERNAL_FORMAT_SRGB8_A8:			return GL_SRGB8_ALPHA8; break;
	case TEXTURE_INTERNAL_FORMAT_R16F:				return GL_R16F; break;
	case TEXTURE_INTERNAL_FORMAT_RG16F:				return GL_RG16F; break;
	case TEXTURE_INTERNAL_FORMAT_RGB16F:			return GL_RGB16F; break;
	case TEXTURE_INTERNAL_FORMAT_RGBA16F:			return GL_RGBA16F; break;
	case TEXTURE_INTERNAL_FORMAT_R32F:				return GL_R32F; break;
	case TEXTURE_INTERNAL_FORMAT_RG32F:				return GL_RG32F; break;
	case TEXTURE_INTERNAL_FORMAT_RGB32F:			return GL_RGB32F; break;
	case TEXTURE_INTERNAL_FORMAT_RGBA32F:			return GL_RGBA32F; break;
	case TEXTURE_INTERNAL_FORMAT_R11F_G11F_B10F:	return GL_R11F_G11F_B10F; break;
	case TEXTURE_INTERNAL_FORMAT_RGB9_E5:			return GL_RGB9_E5; break;
	case TEXTURE_INTERNAL_FORMAT_R8I:				return GL_R8I; break;
	case TEXTURE_INTERNAL_FORMAT_R8UI:				return GL_R8UI; break;
	case TEXTURE_INTERNAL_FORMAT_R16I:				return GL_R16I; break;
	case TEXTURE_INTERNAL_FORMAT_R16UI:				return GL_R16UI; break;
	case TEXTURE_INTERNAL_FORMAT_R32I:				return GL_R32I; break;
	case TEXTURE_INTERNAL_FORMAT_R32UI:				return GL_R32UI; break;
	case TEXTURE_INTERNAL_FORMAT_RG8I:				return GL_RG8I; break;
	case TEXTURE_INTERNAL_FORMAT_RG8UI:				return GL_RG8UI; break;
	case TEXTURE_INTERNAL_FORMAT_RG16I:				return GL_RG16I; break;
	case TEXTURE_INTERNAL_FORMAT_RG16UI:			return GL_RG16UI; break;
	case TEXTURE_INTERNAL_FORMAT_RG32I:				return GL_RG32I; break;
	case TEXTURE_INTERNAL_FORMAT_RG32UI:			return GL_RG32UI; break;
	case TEXTURE_INTERNAL_FORMAT_RGB8I:				return GL_RGB8I; break;
	case TEXTURE_INTERNAL_FORMAT_RGB8UI:			return GL_RGB8UI; break;
	case TEXTURE_INTERNAL_FORMAT_RGB16I:			return GL_RGB16I; break;
	case TEXTURE_INTERNAL_FORMAT_RGB16UI:			return GL_RGB16UI; break;
	case TEXTURE_INTERNAL_FORMAT_RGB32I:			return GL_RGB32I; break;
	case TEXTURE_INTERNAL_FORMAT_RGB32UI:			return GL_RGB32UI; break;
	case TEXTURE_INTERNAL_FORMAT_RGBA8I:			return GL_RGBA8I; break;
	case TEXTURE_INTERNAL_FORMAT_RGBA8UI:			return GL_RGBA8UI; break;
	case TEXTURE_INTERNAL_FORMAT_RGBA16I:			return GL_RGBA16I; break;
	case TEXTURE_INTERNAL_FORMAT_RGBA16UI:			return GL_RGBA16UI; break;
	case TEXTURE_INTERNAL_FORMAT_RGBA32I:			return GL_RGBA32I; break;
	case TEXTURE_INTERNAL_FORMAT_RGBA32UI:			return GL_RGBA32UI; break;
	case TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT:	return GL_DEPTH_COMPONENT; break;
	case TEXTURE_INTERNAL_FORMAT_DEPTH_STENCIL:		return GL_DEPTH_STENCIL; break;
	case TEXTURE_INTERNAL_FORMAT_STENCIL:			return GL_STENCIL_INDEX; break;
	case TEXTURE_INTERNAL_FORMAT_DEPTH16:			return GL_DEPTH_COMPONENT16; break;
	case TEXTURE_INTERNAL_FORMAT_DEPTH24:			return GL_DEPTH_COMPONENT24; break;
	case TEXTURE_INTERNAL_FORMAT_DEPTH32:			return GL_DEPTH_COMPONENT32; break;
	case TEXTURE_INTERNAL_FORMAT_DEPTH32F:			return GL_DEPTH_COMPONENT32F; break;
	case TEXTURE_INTERNAL_FORMAT_DEPTH24_STENCIL8:	return GL_DEPTH24_STENCIL8; break;
	case TEXTURE_INTERNAL_FORMAT_DEPTH32F_STENCIL8:	return GL_DEPTH32F_STENCIL8; break;
	case TEXTURE_INTERNAL_FORMAT_STENCIL8:			return GL_STENCIL_INDEX8; break;
	case TEXTURE_INTERNAL_FORMAT_RED:				return GL_RED; break;
	case TEXTURE_INTERNAL_FORMAT_RG:				return GL_RG; break;
	case TEXTURE_INTERNAL_FORMAT_RGB:				return GL_RGB; break;
	case TEXTURE_INTERNAL_FORMAT_RGBA:				return GL_RGBA; break;
	case TEXTURE_INTERNAL_FORMAT_4:					return 4; break;
	case TEXTURE_INTERNAL_FORMAT_3:					return 3; break;
	case TEXTURE_INTERNAL_FORMAT_2:					return 2; break;
	case TEXTURE_INTERNAL_FORMAT_1:					return 1; break;
	default:										return GL_NONE;
	}
}

AUint AnimaTexture::AttachmentToPlatform(const AnimaTextureAttachment& attachment)
{
	switch (attachment)
	{
	case TEXTURE_ATTACHMENT_DEPTH:			return GL_DEPTH_ATTACHMENT; break;
	case TEXTURE_ATTACHMENT_STENCIL:		return GL_STENCIL_ATTACHMENT; break;
	case TEXTURE_ATTACHMENT_DEPTH_STENCIL:	return GL_DEPTH_STENCIL_ATTACHMENT; break;
	case TEXTURE_ATTACHMENT_COLOR0:			return GL_COLOR_ATTACHMENT0; break;
	case TEXTURE_ATTACHMENT_COLOR1:			return GL_COLOR_ATTACHMENT1; break;
	case TEXTURE_ATTACHMENT_COLOR2:			return GL_COLOR_ATTACHMENT2; break;
	case TEXTURE_ATTACHMENT_COLOR3:			return GL_COLOR_ATTACHMENT3; break;
	case TEXTURE_ATTACHMENT_COLOR4:			return GL_COLOR_ATTACHMENT4; break;
	case TEXTURE_ATTACHMENT_COLOR5:			return GL_COLOR_ATTACHMENT5; break;
	case TEXTURE_ATTACHMENT_COLOR6:			return GL_COLOR_ATTACHMENT6; break;
	case TEXTURE_ATTACHMENT_COLOR7:			return GL_COLOR_ATTACHMENT7; break;
	case TEXTURE_ATTACHMENT_COLOR8:			return GL_COLOR_ATTACHMENT8; break;
	case TEXTURE_ATTACHMENT_COLOR9:			return GL_COLOR_ATTACHMENT9; break;
	case TEXTURE_ATTACHMENT_COLOR10:		return GL_COLOR_ATTACHMENT10; break;
	case TEXTURE_ATTACHMENT_COLOR11:		return GL_COLOR_ATTACHMENT11; break;
	case TEXTURE_ATTACHMENT_COLOR12:		return GL_COLOR_ATTACHMENT12; break;
	case TEXTURE_ATTACHMENT_COLOR13:		return GL_COLOR_ATTACHMENT13; break;
	case TEXTURE_ATTACHMENT_COLOR14:		return GL_COLOR_ATTACHMENT14; break;
	case TEXTURE_ATTACHMENT_COLOR15:		return GL_COLOR_ATTACHMENT15; break;
	default:								return GL_NONE;
	}
}

AUint AnimaTexture::DataTypeToPlatform(const AnimaTextureDataType& dataType)
{
	switch (dataType)
	{
	case TEXTURE_DATA_TYPE_UNSIGNED_BYTE:				return GL_UNSIGNED_BYTE; break;
	case TEXTURE_DATA_TYPE_BYTE:						return GL_BYTE; break;
	case TEXTURE_DATA_TYPE_UNSIGNED_SHORT:				return GL_UNSIGNED_SHORT; break;
	case TEXTURE_DATA_TYPE_SHORT:						return GL_SHORT; break;
	case TEXTURE_DATA_TYPE_UNSIGNED_INT:				return GL_UNSIGNED_INT; break;
	case TEXTURE_DATA_TYPE_INT:							return GL_INT; break;
	case TEXTURE_DATA_TYPE_FLOAT:						return GL_FLOAT; break;
	case TEXTURE_DATA_TYPE_UNSIGNED_BYTE_3_3_2:			return GL_UNSIGNED_BYTE_3_3_2; break;
	case TEXTURE_DATA_TYPE_UNSIGNED_BYTE_2_3_3_REV:		return GL_UNSIGNED_BYTE_2_3_3_REV; break;
	case TEXTURE_DATA_TYPE_UNSIGNED_SHORT_5_6_5:		return GL_UNSIGNED_SHORT_5_6_5; break;
	case TEXTURE_DATA_TYPE_UNSIGNED_SHORT_5_6_5_REV:	return GL_UNSIGNED_SHORT_5_6_5_REV; break;
	case TEXTURE_DATA_TYPE_UNSIGNED_SHORT_4_4_4_4:		return GL_UNSIGNED_SHORT_4_4_4_4; break;
	case TEXTURE_DATA_TYPE_UNSIGNED_SHORT_4_4_4_4_REV:	return GL_UNSIGNED_SHORT_4_4_4_4_REV; break;
	case TEXTURE_DATA_TYPE_UNSIGNED_SHORT_5_5_5_1:		return GL_UNSIGNED_SHORT_5_5_5_1; break;
	case TEXTURE_DATA_TYPE_UNSIGNED_SHORT_1_5_5_5_REV:	return GL_UNSIGNED_SHORT_1_5_5_5_REV; break;
	case TEXTURE_DATA_TYPE_UNSIGNED_INT_8_8_8_8:		return GL_UNSIGNED_INT_8_8_8_8; break;
	case TEXTURE_DATA_TYPE_UNSIGNED_INT_8_8_8_8_REV:	return GL_UNSIGNED_INT_8_8_8_8_REV; break;
	case TEXTURE_DATA_TYPE_UNSIGNED_INT_10_10_10_2:		return GL_UNSIGNED_INT_10_10_10_2; break;
	case TEXTURE_DATA_TYPE_UNSIGNED_INT_2_10_10_10_REV:	return GL_UNSIGNED_INT_2_10_10_10_REV; break;
	case TEXTURE_DATA_TYPE_UNSIGNED_INT_24_8:			return GL_UNSIGNED_INT_24_8; break;
	default:											return GL_NONE;
	}
}

AnimaTextureSurface::AnimaTextureSurface()
{
	_width = 0;
	_height = 0;
}

AnimaTextureSurface::AnimaTextureSurface(AUint width, AUint height, AUchar* data, AUint dataSize)
{
	_width = width;
	_height = height;

	SetData(data, dataSize);
}

AnimaTextureSurface::AnimaTextureSurface(const AnimaTextureSurface& src)
{
	if (this != &src)
	{
		_width = src._width;
		_height = src._height;

		CopyData(src);
	}
}

AnimaTextureSurface::AnimaTextureSurface(AnimaTextureSurface&& src)
{
	if (this != &src)
	{
		_width = src._width;
		_height = src._height;

		CopyData(src);
	}
}

AnimaTextureSurface::~AnimaTextureSurface()
{
}

AnimaTextureSurface& AnimaTextureSurface::operator=(const AnimaTextureSurface& src)
{
	if (this != &src)
	{
		_width = src._width;
		_height = src._height;

		CopyData(src);
	}

	return *this;
}

AnimaTextureSurface& AnimaTextureSurface::operator=(AnimaTextureSurface&& src)
{
	if (this != &src)
	{
		_width = src._width;
		_height = src._height;

		CopyData(src);
	}

	return *this;
}

void AnimaTextureSurface::SetData(AUchar* data, AUint dataSize)
{
	AnimaArray<AUchar> newData;

	if (data != nullptr && dataSize > 0)
	{
		newData.resize(dataSize);
		newData.assign(data, data + dataSize);
	}

	_data = newData;
}

void AnimaTextureSurface::CopyData(const AnimaTextureSurface& src)
{
	_data.clear();
	_data = src._data;
}

const AUchar* AnimaTextureSurface::GetData() const
{
	if (_data.size() > 0)
		return &(_data)[0];
	return nullptr;
}

const AnimaArray<AUchar>* AnimaTextureSurface::GetDataAsArray() const
{
	return const_cast<AnimaArray<AUchar>*>(&_data);
}

void AnimaTextureSurface::SetWidth(AUint width)
{
	_width = width;
}

AUint AnimaTextureSurface::GetWidth() const
{
	return _width;
}

void AnimaTextureSurface::SetHeight(AUint height)
{
	_height = height;
}

AUint AnimaTextureSurface::GetHeight() const
{
	return _height;
}

END_ANIMA_ENGINE_NAMESPACE