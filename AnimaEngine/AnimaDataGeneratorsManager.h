//
//  AnimaDataGeneratorsManager.h
//  Anima
//
//  Created by Marco Zille on 14/01/15.
//
//

#ifndef __Anima__AnimaDataGeneratorsManager__
#define __Anima__AnimaDataGeneratorsManager__

#include "AnimaEngineCore.h"
#include "AnimaAllocators.h"
#include "AnimaTypes.h"
#include "AnimaEngine.h"
#include "AnimaString.h"
#include "AnimaColorGenerator.h"
#include "AnimaVectorGenerator.h"
#include "AnimaTextureGenerator.h"
#include "AnimaDataGenerator.h"
#include "AnimaArray.h"
#include "AnimaMappedArray.h"
#include "AnimaTypeMappedArray.h"

BEGIN_ANIMA_ENGINE_NAMESPACE

class AnimaEngine;
class AnimaScene;

class ANIMA_ENGINE_EXPORT AnimaDataGeneratorsManager
{
public:
	AnimaDataGeneratorsManager(AnimaScene* scene, AnimaEngine* engine = nullptr);
	~AnimaDataGeneratorsManager();
		
	template<class T> AnimaArray<AnimaDataGenerator*>* GetDataGeneratorsArrayOfType();
	template<class T> T* GetDataGeneratorOfTypeFromName(const AnimaString& name);
	
	AnimaColorGenerator* CreateColorGenerator(const AnimaString& name);
	AnimaVectorGenerator* CreateVectorGenerator(const AnimaString& name);
	AnimaTextureGenerator* CreateTextureGenerator(const AnimaString& name);

	bool RemoveGenerator(const AnimaString& name);
	bool RemoveGenerator(AnimaDataGenerator* generator);

	AnimaDataGenerator* GetGenerator(const AnimaString& name);
	
	AInt GetTotalDataGeneratorsCount();
	
	AnimaTypeMappedArray<AnimaDataGenerator*>* GetDataGeneratorsTypeMappedArray();
	
	void UpdateValues(AFloat elapsedTime);

private:
	void ClearGenerators();
	
private:
	AnimaScene* _scene;
	AnimaEngine* _engine;

	AnimaTypeMappedArray<AnimaDataGenerator*> _dataGenerators;
};

template<class T>
AnimaArray<AnimaDataGenerator*>* AnimaDataGeneratorsManager::GetDataGeneratorsArrayOfType()
{
	return _dataGenerators.GetMappedArrayArrayOfType<T*>();
}

template<class T>
T* AnimaDataGeneratorsManager::GetDataGeneratorOfTypeFromName(const AnimaString& name)
{
	return _dataGenerators.GetWithNameAndType<T*>(name);
}

END_ANIMA_ENGINE_NAMESPACE

#endif /* defined(__Anima__AnimaDataGeneratorsManager__) */
