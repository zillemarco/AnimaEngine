//
//  AnimaNode.h
//  Anima
//
//  Created by Marco Zille on 26/11/14.
//
//

#ifndef __Anima__AnimaNode__
#define __Anima__AnimaNode__

#include "AnimaEngine.h"
#include "AnimaVertex.h"
#include "AnimaTypes.h"
#include "AnimaSceneObject.h"
#include "AnimaMaterial.h"
#include "AnimaMappedArray.h"
#include "AnimaGeometry.h"
#include "AnimaAnimation.h"

#include <btBulletDynamicsCommon.h>

BEGIN_ANIMA_ENGINE_NAMESPACE

class ANIMA_ENGINE_EXPORT AnimaNode : public AnimaSceneObject
{
	DECLARE_ANIMA_CLASS(AnimaNode);

	friend class AnimaNodeInstancesManager;
	friend class AnimaGeometryInstancesManager;

public:
	AnimaNode(const AnimaString& name, AnimaDataGeneratorsManager* dataGeneratorsManager, AnimaAllocator* allocator);
	AnimaNode(const AnimaNode& src);
	AnimaNode(AnimaNode&& src);
	~AnimaNode();
	
	AnimaNode& operator=(const AnimaNode& src);
	AnimaNode& operator=(AnimaNode&& src);

public:
	ptree GetObjectTree(bool saveName = true) const override;
	bool ReadObject(const ptree& objectTree, AnimaScene* scene, bool readName = true) override;
	bool FinalizeAfterRead(AnimaScene* scene) override;

public:
	void SetMaterial(AnimaMaterial* material);
	AnimaMaterial* GetMaterial();

	AInt GetGeometriesCount() const;
	AInt AddGeometry(AnimaGeometry* geometry);
	AnimaGeometry* GetGeometry(AInt index);
	AnimaGeometry* GetGeometryFromName(const AnimaString& name);

	AInt GetAnimationsCount() const;
	void SetAnimations(AnimaArray<AnimaAnimation*>* animations);
	AInt AddAnimation(AnimaAnimation* animation);
	AnimaAnimation* GetAnimation(AInt index);

	void SetOriginFileName(const AnimaString& fileName);
	AnimaString GetAnimaOriginFileName() const;

	void SetAnimationNodeName(const AnimaString& animationNodeName);
	AnimaString GetAnimaAnimationNodeName() const;

	AnimaMappedArray<AnimaGeometryBoneInfo*>* GetGeometriesBonesInfo();
	void SetGeometriesBonesInfo(const AnimaMappedArray<AnimaGeometryBoneInfo*>* geometriesBonesInfo);
	void ClearGeometriesBonesInfo();

	void UpdateAnimation(AFloat animationTime);
	void SetActiveAnimation(AInt animationIndex);
	void StopAnimation();

	void ComputeBoundingBox();
	AnimaVertex3f GetBoundingBoxMin() const;
	AnimaVertex3f GetBoundingBoxMax() const;
	AnimaVertex3f GetBoundingBoxCenter() const;

	void GetAllGeometries(AnimaArray<AnimaGeometry*> *geometries);
	
	virtual void SetIsAsset(bool isAsset) { _isAsset = isAsset; }
	virtual bool IsAsset() const { return _isAsset; }

protected:	
	void UpdateChildrenTransformation() override;

protected:
	AnimaMaterial*	_material;
	AnimaString		_materialName;
	AnimaString		_animationNodeName;
	AnimaString		_originFileName;

	AnimaVertex3f	_boundingBoxMin;
	AnimaVertex3f	_boundingBoxMax;
	AnimaVertex3f	_boundingBoxCenter;
	
	bool _isAsset;

	AnimaMappedArray<AnimaGeometry*> _geometries;
	AnimaMappedArray<AnimaGeometryBoneInfo*> _geometriesBonesInfo;
	
	AnimaArray<AnimaAnimation*> _animations;
	AInt _activeAnimation;
	
	btMotionState* _physMotionState;
	btRigidBody* _physRigidBody;
};

END_ANIMA_ENGINE_NAMESPACE

#endif /* defined(__Anima__AnimaNode__) */
