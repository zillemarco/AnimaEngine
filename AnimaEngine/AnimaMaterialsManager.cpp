//
//  AnimaMaterialsManager.cpp
//  Anima
//
//  Created by Marco Zille on 14/01/15.
//
//

#include "AnimaMaterialsManager.h"
#include "AnimaXmlTranslators.h"
#include "AnimaShadersManager.h"
#include "AnimaScene.h"

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

BEGIN_ANIMA_ENGINE_NAMESPACE

AnimaMaterial* AnimaMaterialsManager::_defaultMaterial = nullptr;
AInt AnimaMaterialsManager::_instancesCount = 0;

AnimaMaterialsManager::AnimaMaterialsManager(AnimaScene* scene, AnimaTexturesManager* texturesManager)
{
	ANIMA_ASSERT(texturesManager != nullptr);
	_scene = scene;
	_texturesManager = texturesManager;

	if (_defaultMaterial == nullptr)
	{
		_defaultMaterial = AnimaAllocatorNamespace::AllocateNew<AnimaMaterial>(*(_scene->GetMaterialsAllocator()), _scene->GetMaterialsAllocator(), _scene->GetDataGeneratorsManager(), "defaultMaterial");
		
		_defaultMaterial->SetColor("Albedo", 1.0, 1.0, 1.0, 1.0);
		_defaultMaterial->SetFloat("ReflectionIntensity", 0.1);
		_defaultMaterial->SetFloat("Metallic", 0.0);
		_defaultMaterial->SetFloat("Roughness", 0.8);
		_defaultMaterial->SetFloat("Specular", 0.5);
	}

	_instancesCount++;
}

AnimaMaterialsManager::~AnimaMaterialsManager()
{
	ClearMaterials();
	ClearLastMaterialsIndexMap();

	_instancesCount--;

	if (_instancesCount == 0 && _defaultMaterial != nullptr)
	{
		AnimaAllocatorNamespace::DeallocateObject(*(_scene->GetMaterialsAllocator()), _defaultMaterial);
		_defaultMaterial = nullptr;
	}
}

AnimaMaterial* AnimaMaterialsManager::CreateMaterial(const AnimaString& name)
{
	AInt materialIndex = _materials.Contains(name);
	if (materialIndex >= 0)
		return nullptr;

	ANIMA_ASSERT(_scene != nullptr);
	AnimaMaterial* newMaterial = AnimaAllocatorNamespace::AllocateNew<AnimaMaterial>(*(_scene->GetMaterialsAllocator()), _scene->GetMaterialsAllocator(), _scene->GetDataGeneratorsManager(), name);
	_materials.Add(name, newMaterial);

	return newMaterial;
}

void AnimaMaterialsManager::ClearMaterials()
{
	AInt count = _materials.GetSize();
	for (AInt i = 0; i < count; i++)
	{
		AnimaMaterial* material = _materials[i];
		AnimaAllocatorNamespace::DeallocateObject(*(_scene->GetMaterialsAllocator()), material);
		material = nullptr;
	}
	
	_materials.RemoveAll();
}

AnimaMaterial* AnimaMaterialsManager::GetMaterial(AInt index)
{
	return _materials.Get(index);
}

AnimaMaterial* AnimaMaterialsManager::GetMaterialFromName(const AnimaString& name)
{
	return _materials.GetWithName(name);
}

AInt AnimaMaterialsManager::GetMaterialsCount()
{
	return _materials.GetSize();
}

AnimaMappedArray<AnimaMaterial*>* AnimaMaterialsManager::GetMaterials()
{
	return &_materials;
}

bool AnimaMaterialsManager::LoadMaterialsFromNode(const aiScene* scene, const AnimaString& nodeName)
{
//	ClearLastMaterialsIndexMap();
//
//	for (AUint i = 0; i < scene->mNumMaterials; i++)
//	{
//		const aiMaterial* material = scene->mMaterials[i];
//		AnimaMaterial* newMaterial = nullptr;
//
//		AnimaString materialName;
//		int nameOffset = 0;
//		while (newMaterial == nullptr)
//		{
//			materialName = FormatString("%s.material%d", nodeName.c_str(), i + nameOffset);
//			newMaterial = CreateMaterial(materialName);
//			nameOffset++;
//		}
//		
//		int ret1, ret2;
//		aiColor4D diffuse;
//		aiColor4D specular;
//		aiColor4D ambient;
//		aiColor4D emission;
//		float shininess, strength;
//		unsigned int max;
//		int two_sided;
//
//		if (aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse) == AI_SUCCESS)
//			newMaterial->AddColor("DiffuseColor", diffuse.r, diffuse.g, diffuse.b, diffuse.a);
//		else
//			newMaterial->AddColor("DiffuseColor", 0.8f, 0.8f, 0.8f, 1.0f);
//
//		if (aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specular) == AI_SUCCESS)
//			newMaterial->AddColor("SpecularColor", specular.r, specular.g, specular.b, specular.a);
//		else
//			newMaterial->AddColor("SpecularColor", 0.0f, 0.0f, 0.0f, 1.0f);
//
//		if (aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambient) == AI_SUCCESS)
//			newMaterial->AddColor("AmbientColor", ambient.r, ambient.g, ambient.b, ambient.a);
//		else
//			newMaterial->AddColor("AmbientColor", 0.2f, 0.2f, 0.2f, 1.0f);
//
//		if (aiGetMaterialColor(material, AI_MATKEY_COLOR_EMISSIVE, &emission) == AI_SUCCESS)
//			newMaterial->AddColor("EmissionColor", emission.r, emission.g, emission.b, emission.a);
//		else
//			newMaterial->AddColor("EmissionColor", 0.0f, 0.0f, 0.0f, 1.0f);
//
//		max = 1;
//		ret1 = aiGetMaterialFloatArray(material, AI_MATKEY_SHININESS, &shininess, &max);
//		if (ret1 == AI_SUCCESS)
//		{
//			max = 1;
//			ret2 = aiGetMaterialFloatArray(material, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
//
//			if (ret2 == AI_SUCCESS)
//				newMaterial->AddFloat("Shininess", shininess * strength);
//			else
//				newMaterial->AddFloat("Shininess", shininess);
//		}
//		else
//		{
//			newMaterial->AddFloat("Shininess", 0.0f);
//			newMaterial->SetColor("SpecularColor", 0.0f, 0.0f, 0.0f, 1.0f);
//		}
//
//		max = 1;
//		if ((aiGetMaterialIntegerArray(material, AI_MATKEY_TWOSIDED, &two_sided, &max) == AI_SUCCESS) && two_sided)
//			newMaterial->AddBoolean("TwoSided", true);
//		else
//			newMaterial->AddBoolean("TwoSided", false);
//
//		aiString path;
//		if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
//		{
//			AnimaString txtCompletePath(ANIMA_ENGINE_NODES_PATH);
//			AnimaString txtPath(path.C_Str());
//			txtCompletePath += txtPath;
//			std::replace(txtCompletePath.begin(), txtCompletePath.end(), ' ', '~');
//
//			newMaterial->SetTexture("DiffuseTexture", _texturesManager->LoadTextureFromFile(txtCompletePath, txtPath));
//		}
//
//		if (material->GetTexture(aiTextureType_SPECULAR, 0, &path) == AI_SUCCESS)
//		{
//			AnimaString txtCompletePath(ANIMA_ENGINE_NODES_PATH);
//			AnimaString txtPath(path.C_Str());
//			txtCompletePath += txtPath;
//			std::replace(txtCompletePath.begin(), txtCompletePath.end(), ' ', '~');
//
//			AnimaTexture* texture = _texturesManager->LoadTextureFromFile(txtCompletePath, txtPath);
//
//			if (texture != nullptr)
//			{
//				newMaterial->SetTexture("SpecularTexture", texture);
//				newMaterial->SetBoolean("HasSpecular", true);
//			}
//			else
//			{
////				ANIMA_ASSERT(false);
//			}
//		}
//
//		if (material->GetTexture(aiTextureType_AMBIENT, 0, &path) == AI_SUCCESS)
//		{
//			AnimaString txtCompletePath(ANIMA_ENGINE_NODES_PATH);
//			AnimaString txtPath(path.C_Str());
//			txtCompletePath += txtPath;
//			std::replace(txtCompletePath.begin(), txtCompletePath.end(), ' ', '~');
//
//			AnimaTexture* texture = _texturesManager->LoadTextureFromFile(txtCompletePath, txtPath);
//
//			if (texture != nullptr)
//			{
//				newMaterial->SetTexture("AmbientTexture", texture);
//			}
//			else
//			{
////				ANIMA_ASSERT(false);
//			}
//		}
//		if (material->GetTexture(aiTextureType_EMISSIVE, 0, &path) == AI_SUCCESS)
//		{
//			AnimaString txtCompletePath(ANIMA_ENGINE_NODES_PATH);
//			AnimaString txtPath(path.C_Str());
//			txtCompletePath += txtPath;
//			std::replace(txtCompletePath.begin(), txtCompletePath.end(), ' ', '~');
//
//			AnimaTexture* texture = _texturesManager->LoadTextureFromFile(txtCompletePath, txtPath);
//
//			if (texture != nullptr)
//			{
//				newMaterial->SetTexture("EmissiveTexture", texture);
//			}
//			else
//			{
////				ANIMA_ASSERT(false);
//			}
//		}
//		if (material->GetTexture(aiTextureType_HEIGHT, 0, &path) == AI_SUCCESS)
//		{
//			AnimaString txtCompletePath(ANIMA_ENGINE_NODES_PATH);
//			AnimaString txtPath(path.C_Str());
//			txtCompletePath += txtPath;
//			std::replace(txtCompletePath.begin(), txtCompletePath.end(), ' ', '~');
//
//			AnimaTexture* texture = _texturesManager->LoadTextureFromFile(txtCompletePath, txtPath);
//
//			if (texture != nullptr)
//			{
//				newMaterial->SetTexture("BumpTexture", texture);
//				newMaterial->SetBoolean("HasBump", true);
//			}
//			else
//			{
////				ANIMA_ASSERT(false);
//			}
//		}
//		if (material->GetTexture(aiTextureType_NORMALS, 0, &path) == AI_SUCCESS)
//		{
//			AnimaString txtCompletePath(ANIMA_ENGINE_NODES_PATH);
//			AnimaString txtPath(path.C_Str());
//			txtCompletePath += txtPath;
//			std::replace(txtCompletePath.begin(), txtCompletePath.end(), ' ', '~');
//
//			AnimaTexture* texture = _texturesManager->LoadTextureFromFile(txtCompletePath, txtPath);
//
//			if (texture != nullptr)
//			{
//				newMaterial->SetTexture("BumpTexture", texture);
//				newMaterial->SetBoolean("HasBump", true);
//			}
//			else
//			{
////				ANIMA_ASSERT(false);
//			}
//		}
//		if (material->GetTexture(aiTextureType_SHININESS, 0, &path) == AI_SUCCESS)
//		{
//			ANIMA_ASSERT(false);
//			AnimaString txtCompletePath(ANIMA_ENGINE_NODES_PATH);
//			AnimaString txtPath(path.C_Str());
//			txtCompletePath += txtPath;
//			std::replace(txtCompletePath.begin(), txtCompletePath.end(), ' ', '~');
//
//			AnimaTexture* texture = _texturesManager->LoadTextureFromFile(txtCompletePath, txtPath);
//
//			if (texture != nullptr)
//			{
//				newMaterial->SetTexture("ShininessTexture", texture);
//			}
//			else
//			{
////				ANIMA_ASSERT(false);
//			}
//		}
//		if (material->GetTexture(aiTextureType_OPACITY, 0, &path) == AI_SUCCESS)
//		{
//			AnimaString txtCompletePath(ANIMA_ENGINE_NODES_PATH);
//			AnimaString txtPath(path.C_Str());
//			txtCompletePath += txtPath;
//			std::replace(txtCompletePath.begin(), txtCompletePath.end(), ' ', '~');
//
//			AnimaTexture* texture = _texturesManager->LoadTextureFromFile(txtCompletePath, txtPath);
//
//			if (texture != nullptr)
//			{
//				newMaterial->SetTexture("OpacityTexture", texture);
//				newMaterial->SetBoolean("HasOpacity", true);
//			}
//			else
//			{
////				ANIMA_ASSERT(false);
//			}
//		}
//		if (material->GetTexture(aiTextureType_DISPLACEMENT, 0, &path) == AI_SUCCESS)
//		{
//			AnimaString txtCompletePath(ANIMA_ENGINE_NODES_PATH);
//			AnimaString txtPath(path.C_Str());
//			txtCompletePath += txtPath;
//			std::replace(txtCompletePath.begin(), txtCompletePath.end(), ' ', '~');
//
//			AnimaTexture* texture = _texturesManager->LoadTextureFromFile(txtCompletePath, txtPath);
//
//			if (texture != nullptr)
//			{
//				newMaterial->SetTexture("DisplacementTexture", texture);
//			}
//			else
//			{
////				ANIMA_ASSERT(false);
//			}
//		}
//		if (material->GetTexture(aiTextureType_LIGHTMAP, 0, &path) == AI_SUCCESS)
//		{
//			AnimaString txtCompletePath(ANIMA_ENGINE_NODES_PATH);
//			AnimaString txtPath(path.C_Str());
//			txtCompletePath += txtPath;
//			std::replace(txtCompletePath.begin(), txtCompletePath.end(), ' ', '~');
//
//			AnimaTexture* texture = _texturesManager->LoadTextureFromFile(txtCompletePath, txtPath);
//
//			if (texture != nullptr)
//			{
//				newMaterial->SetTexture("LightMapTexture", texture);
//			}
//			else
//			{
////				ANIMA_ASSERT(false);
//			}
//		}
//		if (material->GetTexture(aiTextureType_REFLECTION, 0, &path) == AI_SUCCESS)
//		{
//			ANIMA_ASSERT(false);
//			AnimaString txtCompletePath(ANIMA_ENGINE_NODES_PATH);
//			AnimaString txtPath(path.C_Str());
//			txtCompletePath += txtPath;
//			std::replace(txtCompletePath.begin(), txtCompletePath.end(), ' ', '~');
//
//			AnimaTexture* texture = _texturesManager->LoadTextureFromFile(txtCompletePath, txtPath);
//			if (texture != nullptr)
//			{
//				newMaterial->SetTexture("ReflectionTexture", texture);
//			}
//			else
//			{
////				ANIMA_ASSERT(false);
//			}
//		}
//
//		_lastMaterialsIndexMap.push_back(materialName);
//	}

	return true;
}

AnimaArray<AnimaString>* AnimaMaterialsManager::GetLastMaterialsIndexMap()
{
	return &_lastMaterialsIndexMap;
}

void AnimaMaterialsManager::ClearLastMaterialsIndexMap()
{
	_lastMaterialsIndexMap.clear();
}

bool AnimaMaterialsManager::LoadMaterials(const AnimaString& materialsPath)
{
	namespace fs = boost::filesystem;
	fs::path directory(materialsPath);
	
	if (fs::exists(directory) && fs::is_directory(directory))
	{
		fs::directory_iterator endIterator;
		for (fs::directory_iterator directoryIterator(directory); directoryIterator != endIterator; directoryIterator++)
		{
			if (directoryIterator->path().extension().string() == ".amaterial")
			{
				if(LoadMaterialFromFile(directoryIterator->path().string()) == nullptr)
					return false;
			}
		}
	}

	return true;
}

AnimaMaterial* AnimaMaterialsManager::LoadMaterialFromFile(const AnimaString& materialFilePath)
{
	std::ifstream fileStream(materialFilePath);
	AnimaString xml((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
	fileStream.close();

	return LoadMaterialFromXml(xml);
}

AnimaMaterial* AnimaMaterialsManager::LoadMaterialFromXml(const AnimaString& materialXmlDefinition)
{
	AnimaMaterial* material = nullptr;

	using boost::property_tree::ptree;
	ptree pt;
	
	std::stringstream ss(materialXmlDefinition);
	boost::property_tree::read_xml(ss, pt);

	AnimaString name = pt.get<AnimaString>("AnimaMaterial.Name");

	material = CreateMaterial(name);

	if (material)
	{
#if !defined SAVE_SCENE
		material->ReadObject(pt, _scene, false);
#else		
		for (auto& prop : pt.get_child("AnimaMaterial.Properties"))
		{
			if (prop.first == "Property")
			{
				AnimaString propName = prop.second.get<AnimaString>("Name");
				AnimaString propType = prop.second.get<AnimaString>("Type");

				if (propType.compare("color") == 0 || propType.compare("vector") == 0)
					material->SetColor(propName.c_str(), prop.second.get<AnimaVertex4f>("Value"));
				else if (propType.compare("float") == 0)
					material->SetFloat(propName.c_str(), prop.second.get<AFloat>("Value"));
				else if (propType.compare("bool") == 0)
					material->SetBoolean(propName.c_str(), prop.second.get<bool>("Value"));
				else if (propType.compare("texture") == 0)
				{
					AnimaTexture* texture = nullptr;
					
					AnimaString textureName = prop.second.get<AnimaString>("TextureName", "");
					if(!textureName.empty())
					{
						texture = _texturesManager->GetTextureFromName(textureName);
					}
					else
					{
						texture = _texturesManager->LoadTextureFromXml(prop.second.get_child("Value"));
					}
					
					material->SetTexture(propName.c_str(), texture);
				}
			}
		}

		for (auto& shader : pt.get_child("AnimaMaterial.Shaders"))
		{
			if (shader.first == "Shader")
			{
				AnimaString shaderName = shader.second.get<AnimaString>("Name");
				material->AddShader(shaderName);
			}
		}
#endif
	}

	return material;
}


void AnimaMaterialsManager::SaveMaterialToFile(const AnimaString& materialName, const AnimaString& destinationPath, bool createFinalPath)
{
	return SaveMaterialToFile(GetMaterialFromName(materialName), destinationPath, createFinalPath);
}

void AnimaMaterialsManager::SaveMaterialToFile(AnimaMaterial* material, const AnimaString& destinationPath, bool createFinalPath)
{
	if(material == nullptr)
		return;
	
	namespace fs = boost::filesystem;
	
	AnimaString saveFileName = destinationPath;
	
	if(createFinalPath)
	{
		fs::path firstPart(destinationPath);
		fs::path secondPart(material->GetName() + ".amaterial");
		fs::path completePath = firstPart / secondPart;
		
		saveFileName = completePath.string();
	}
	
	material->SaveObject(saveFileName);
}

void AnimaMaterialsManager::SaveMaterials(const AnimaString& destinationPath)
{
	AInt count = _materials.GetSize();
	for(AInt i = 0; i < count; i++)
	{
		SaveMaterialToFile(_materials[i], destinationPath, true);
	}
}

bool AnimaMaterialsManager::FinalizeObjectsAfterRead()
{
	AInt count = _materials.GetSize();
	for (AInt i = 0; i < count; i++)
		_materials[i]->FinalizeAfterRead(_scene);

	return true;
}

END_ANIMA_ENGINE_NAMESPACE