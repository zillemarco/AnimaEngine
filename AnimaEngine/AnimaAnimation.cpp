//
//  AnimaAnimation.cpp
//  Anima
//
//  Created by Marco Zille on 26/11/14.
//
//

#include "AnimaAnimation.h"
#include "AnimaNode.h"

BEGIN_ANIMA_ENGINE_NAMESPACE

AnimaAnimation::AnimaAnimation(const AnimaString& name, AnimaAllocator* allocator)
	: AnimaNamedObject(name, allocator)
{
	IMPLEMENT_ANIMA_CLASS(AnimaAnimation);

	_duration = 0.0f;
	_ticksPerSecond = 0.0f;
}

AnimaAnimation::AnimaAnimation(const AnimaAnimation& src)
	: AnimaNamedObject(src)
	, _animationNodes(src._animationNodes)
{
	_duration = src._duration;
	_ticksPerSecond = src._ticksPerSecond;
}

AnimaAnimation::AnimaAnimation(AnimaAnimation&& src)
	: AnimaNamedObject(src)
	, _animationNodes(src._animationNodes)
{
	_duration = src._duration;
	_ticksPerSecond = src._ticksPerSecond;
}

AnimaAnimation::~AnimaAnimation()
{
	ClearAnimationNodes();
}

AnimaAnimation& AnimaAnimation::operator=(const AnimaAnimation& src)
{
	if (this != &src)
	{
		AnimaNamedObject::operator=(src);

		ClearAnimationNodes();
		_animationNodes.Copy(src._animationNodes);

		_duration = src._duration;
		_ticksPerSecond = src._ticksPerSecond;
	}
	
	return *this;
}

AnimaAnimation& AnimaAnimation::operator=(AnimaAnimation&& src)
{
	if (this != &src)
	{
		AnimaNamedObject::operator=(src);

		ClearAnimationNodes();
		_animationNodes.Copy(src._animationNodes);

		_duration = src._duration;
		_ticksPerSecond = src._ticksPerSecond;
	}
	
	return *this;
}

void AnimaAnimation::UpdateAnimation(AnimaNode* node, AFloat time)
{
	AFloat timeInTicks = time * _ticksPerSecond;
	AFloat animationTime = fmod(timeInTicks, _duration);

	AnimaMatrix globalInverseMatrix = node->GetTransformation()->GetAnimationGlobalInverseMatrix();
	globalInverseMatrix.Inverse();

	AnimaMappedArray<AnimaGeometryBoneInfo*>* geometriesBonesInfo = node->GetGeometriesBonesInfo();
	UpdateNodeNodesAnimation(node, animationTime, AnimaMatrix(), globalInverseMatrix, geometriesBonesInfo);

	AnimaArray<AnimaMatrix> matrices;
	AInt count = geometriesBonesInfo->GetSize();
	for (AInt i = 0; i < count; i++)
		matrices.push_back(geometriesBonesInfo->Get(i)->GetFinalTransformation());

	node->SetMatrixArray("BonesTransformations", &matrices);
}

void AnimaAnimation::UpdateNodeNodesAnimation(AnimaNode* node, AFloat animationTime, const AnimaMatrix& parentMatrix, const AnimaMatrix& globalInverseMatrix, AnimaMappedArray<AnimaGeometryBoneInfo*>* geometryeBonesInfo)
{
	AnimaString animatioNodeName = node->GetAnimaAnimationNodeName();
	AnimaMatrix nodeMatrix = node->GetTransformation()->GetAnimationGlobalInverseMatrix();
	AnimaAnimationNode* animationNode = _animationNodes[animatioNodeName];

	if (animationNode)
	{
		AnimaVertex4f scaling(animationNode->ComputeInterpolatedScaling(animationTime), 1.0f);
		AnimaQuaternion rotation = animationNode->ComputeInterpolatedRotation(animationTime);
		AnimaVertex3f position = animationNode->ComputeInterpolatedPosition(animationTime);

		AnimaMatrix scalingMatrix = AnimaMatrix::MakeScale(scaling);
		AnimaMatrix rotationMatrix = rotation.GetMatrix();
		AnimaMatrix translationMatrix = AnimaMatrix::MakeTranslation(position);

		nodeMatrix = translationMatrix * rotationMatrix * scalingMatrix;
	}

	AnimaMatrix globalTransformation = parentMatrix * nodeMatrix;

	AnimaGeometryBoneInfo* info = geometryeBonesInfo->GetWithName(animatioNodeName);
	if (info != nullptr)
		info->SetFinalTransformation(globalInverseMatrix * globalTransformation * info->GetBoneOffset());

	AInt childrenCount = node->GetChildrenCount();
	for (AInt nc = 0; nc < childrenCount; nc++)
		UpdateNodeNodesAnimation((AnimaNode*)node->GetChild(nc), animationTime, globalTransformation, globalInverseMatrix, geometryeBonesInfo);
}

AInt AnimaAnimation::GetAnimationNodesCount() const
{
	return _animationNodes.GetSize();
}

AnimaAnimationNode* AnimaAnimation::CreateAnimationNode(const AnimaString& name)
{
	AnimaAnimationNode* newNode = AnimaAllocatorNamespace::AllocateNew<AnimaAnimationNode>(*_allocator, name, _allocator);
	ANIMA_ASSERT(_animationNodes.Add(name, newNode) >= 0);
	return newNode;
}

AnimaAnimationNode* AnimaAnimation::GetAnimationNode(AInt index)
{
	return _animationNodes[index];
}

AnimaMappedArray<AnimaAnimationNode*>* AnimaAnimation::GetAnimationNodes()
{
	return &_animationNodes;
}

void AnimaAnimation::ClearAnimationNodes()
{
	AInt count = _animationNodes.GetSize();
	for (AInt i = 0; i < count; i++)
	{ 
		AnimaAnimationNode* animationNode = _animationNodes[i];
		AnimaAllocatorNamespace::DeallocateObject(*_allocator, animationNode);
	}

	_animationNodes.RemoveAll();
}

void AnimaAnimation::SetDuration(AFloat duration)
{
	_duration = duration;
}

AFloat AnimaAnimation::GetDuration() const
{
	return _duration;
}

void AnimaAnimation::SetTicksPerSecond(AFloat ticksPerSecond)
{
	_ticksPerSecond = ticksPerSecond == 0.0f ? 25.0f : ticksPerSecond;
}

AFloat AnimaAnimation::GetTicksPerSecond() const
{
	return _ticksPerSecond;
}

AnimaAnimationNode::AnimaAnimationNode(const AnimaString& name, AnimaAllocator* allocator)
	: AnimaNamedObject(name, allocator)
{
	IMPLEMENT_ANIMA_CLASS(AnimaAnimationNode);
	SetName(name);
}

AnimaAnimationNode::~AnimaAnimationNode()
{
	_positionKeys.clear();
	_rotationKeys.clear();
	_scalingKeys.clear();
}

AnimaVertex3f AnimaAnimationNode::ComputeInterpolatedScaling(AFloat animationTime) const
{
	if (_scalingKeys.size() <= 1)
		return _scalingKeys[0].GetValue();

	AInt scalingIndex = FindScaling(animationTime);
	AInt nextScalingIndex = scalingIndex + 1;

	ANIMA_ASSERT(nextScalingIndex < _scalingKeys.size());

	AnimaAnimationScalingKey scalingKey = _scalingKeys[scalingIndex];
	AnimaAnimationScalingKey nextScalingKey = _scalingKeys[nextScalingIndex];

	AFloat deltaTime = nextScalingKey.GetTime() - scalingKey.GetTime();
	AFloat factor = (animationTime - scalingKey.GetTime()) / deltaTime;
	
	ANIMA_ASSERT(factor >= 0.0f && factor <= 1.0f);
	
	AnimaVertex3f start = scalingKey.GetValue();
	AnimaVertex3f end = nextScalingKey.GetValue();
	AnimaVertex3f delta = end - start;

	return start + (factor * delta);
}

AnimaQuaternion AnimaAnimationNode::ComputeInterpolatedRotation(AFloat animationTime) const
{
	if (_rotationKeys.size() <= 1)
		return _rotationKeys[0].GetValue();

	AInt rotationIndex = FindRotation(animationTime);
	AInt nextRotationIndex = rotationIndex + 1;

	ANIMA_ASSERT(nextRotationIndex < _rotationKeys.size());

	AnimaAnimationRotationKey rotationKey = _rotationKeys[rotationIndex];
	AnimaAnimationRotationKey nextRotationKey = _rotationKeys[nextRotationIndex];

	AFloat deltaTime = nextRotationKey.GetTime() - rotationKey.GetTime();
	AFloat factor = (animationTime - rotationKey.GetTime()) / deltaTime;

	ANIMA_ASSERT(factor >= 0.0f && factor <= 1.0f);

	AnimaQuaternion start = rotationKey.GetValue();
	AnimaQuaternion end = nextRotationKey.GetValue();

	return start.Slerped(end, factor);
}

AnimaVertex3f AnimaAnimationNode::ComputeInterpolatedPosition(AFloat animationTime) const
{
	if (_positionKeys.size() <= 1)
		return _positionKeys[0].GetValue();

	AInt positionIndex = FindPosition(animationTime);
	AInt nextPositionIndex = positionIndex + 1;

	ANIMA_ASSERT(nextPositionIndex < _positionKeys.size());

	AnimaAnimationPositionKey positionKey = _positionKeys[positionIndex];
	AnimaAnimationPositionKey nextPositionKey = _positionKeys[nextPositionIndex];

	AFloat deltaTime = nextPositionKey.GetTime() - positionKey.GetTime();
	AFloat factor = (animationTime - positionKey.GetTime()) / deltaTime;
	
	ANIMA_ASSERT(factor >= 0.0f && factor <= 1.0f);
	
	AnimaVertex3f start = positionKey.GetValue();
	AnimaVertex3f end = nextPositionKey.GetValue();
	AnimaVertex3f delta = end - start;

	return start + (factor * delta);
}

AInt AnimaAnimationNode::FindScaling(AFloat animationTime) const
{
	AInt scalingKeysCount = _scalingKeys.size();
	for (AInt nsk = 0; nsk < scalingKeysCount - 1; nsk++)
	{
		if (animationTime < _scalingKeys[nsk + 1].GetTime())
			return nsk;
	}

	ANIMA_ASSERT(false);
	return 0;
}

AInt AnimaAnimationNode::FindRotation(AFloat animationTime) const
{
	AInt rotationKeysCount = _rotationKeys.size();
	for (AInt nrk = 0; nrk < rotationKeysCount - 1; nrk++)
	{
		if (animationTime < _rotationKeys[nrk + 1].GetTime())
			return nrk;
	}

	ANIMA_ASSERT(false);
	return 0;
}

AInt AnimaAnimationNode::FindPosition(AFloat animationTime) const
{
	AInt positionKeysCount = _positionKeys.size();
	for (AInt npk = 0; npk < positionKeysCount - 1; npk++)
	{
		if (animationTime < _rotationKeys[npk + 1].GetTime())
			return npk;
	}

	ANIMA_ASSERT(false);
	return 0;
}

AInt AnimaAnimationNode::GetPositionKeysCount() const
{
	return _positionKeys.size();
}

void AnimaAnimationNode::AddPositionKey(AnimaAnimationPositionKey key)
{
	_positionKeys.push_back(key);
}

AnimaAnimationPositionKey AnimaAnimationNode::GetPositionKey(AInt index) const
{
	return _positionKeys[index];
}

AnimaArray<AnimaAnimationPositionKey>* AnimaAnimationNode::GetPositionKeys()
{
	return &_positionKeys;
}

void AnimaAnimationNode::ClearPositionKeys()
{
	_positionKeys.clear();
}

AInt AnimaAnimationNode::GetRotationKeysCount() const
{
	return _rotationKeys.size();
}

void AnimaAnimationNode::AddRotationKey(AnimaAnimationRotationKey key)
{
	_rotationKeys.push_back(key);
}

AnimaAnimationRotationKey AnimaAnimationNode::GetRotationKey(AInt index) const
{
	return _rotationKeys[index];
}

AnimaArray<AnimaAnimationRotationKey>* AnimaAnimationNode::GetRotationKeys()
{
	return &_rotationKeys;
}

void AnimaAnimationNode::ClearRotationKeys()
{
	_rotationKeys.clear();
}

AInt AnimaAnimationNode::GetScalingKeysCount() const
{
	return _scalingKeys.size();
}

void AnimaAnimationNode::AddScalingKey(AnimaAnimationScalingKey key)
{
	_scalingKeys.push_back(key);
}

AnimaAnimationScalingKey AnimaAnimationNode::GetScalingKey(AInt index) const
{
	return _scalingKeys[index];
}

AnimaArray<AnimaAnimationScalingKey>* AnimaAnimationNode::GetScalingKeys()
{
	return &_scalingKeys;
}

void AnimaAnimationNode::ClearScalingKeys()
{
	_scalingKeys.clear();
}

AnimaAnimationPositionKey::AnimaAnimationPositionKey()
{
	_time = 0.0f;
	_value.Fill(0.0f, 0.0f, 0.0f);
}

AnimaAnimationPositionKey::AnimaAnimationPositionKey(AFloat time, AnimaVertex3f value)
{
	_time = time;
	_value = value;
}

AnimaAnimationPositionKey::~AnimaAnimationPositionKey()
{
}

void AnimaAnimationPositionKey::SetTime(AFloat time)
{
	_time = time;
}

AFloat AnimaAnimationPositionKey::GetTime() const
{
	return _time;
}

void AnimaAnimationPositionKey::SetValue(AnimaVertex3f value)
{
	_value = value;
}

AnimaVertex3f AnimaAnimationPositionKey::GetValue() const
{
	return _value;
}

AnimaAnimationRotationKey::AnimaAnimationRotationKey()
{
	_time = 0.0f;
	_value.Set(0.0f, 0.0f, 0.0f, 0.0f);
}

AnimaAnimationRotationKey::AnimaAnimationRotationKey(AFloat time, AnimaQuaternion value)
{
	_time = time;
	_value = value;
}

AnimaAnimationRotationKey::~AnimaAnimationRotationKey()
{
}

void AnimaAnimationRotationKey::SetTime(AFloat time)
{
	_time = time;
}

AFloat AnimaAnimationRotationKey::GetTime() const
{
	return _time;
}

void AnimaAnimationRotationKey::SetValue(AnimaQuaternion value)
{
	_value = value;
}

AnimaQuaternion AnimaAnimationRotationKey::GetValue() const
{
	return _value;
}

AnimaAnimationScalingKey::AnimaAnimationScalingKey()
{
	_time = 0.0f;
	_value.Fill(0.0f, 0.0f, 0.0f);
}

AnimaAnimationScalingKey::AnimaAnimationScalingKey(AFloat time, AnimaVertex3f value)
{
	_time = time;
	_value = value;
}

AnimaAnimationScalingKey::~AnimaAnimationScalingKey()
{
}

void AnimaAnimationScalingKey::SetTime(AFloat time)
{
	_time = time;
}

AFloat AnimaAnimationScalingKey::GetTime() const
{
	return _time;
}

void AnimaAnimationScalingKey::SetValue(AnimaVertex3f value)
{
	_value = value;
}

AnimaVertex3f AnimaAnimationScalingKey::GetValue() const
{
	return _value;
}

END_ANIMA_ENGINE_NAMESPACE