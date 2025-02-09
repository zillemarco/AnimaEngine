#pragma once

#include "AnimaEngineCore.h"
#include "AnimaAllocators.h"
#include "AnimaTypes.h"
#include "AnimaEngine.h"
#include "AnimaString.h"
#include "AnimaNamedObject.h"
#include "AnimaShaderData.h"
#include "AnimaShaderGroupData.h"
#include "AnimaMappedArray.h"

BEGIN_ANIMA_ENGINE_NAMESPACE

enum AnimaShaderType {
	INVALID = -1,
	VERTEX = GL_VERTEX_SHADER,
	TESSELLATION_CONTROL = GL_TESS_CONTROL_SHADER,
	TESSELLATION_EVALUATION = GL_TESS_EVALUATION_SHADER,
	GEOMETRY = GL_GEOMETRY_SHADER,
	FRAGMENT = GL_FRAGMENT_SHADER
};

class ANIMA_ENGINE_EXPORT AnimaShader : public AnimaNamedObject
{
	DECLARE_ANIMA_CLASS(AnimaShader);

public:
	AnimaShader(const AnimaString& name, AnimaAllocator* allocator);
	AnimaShader(const AnimaString& name, AnimaAllocator* allocator, AnimaString shaderText, AnimaShaderType type);
	AnimaShader(const AnimaShader& src);
	AnimaShader(AnimaShader&& src);
	~AnimaShader();
	
	AnimaShader& operator=(const AnimaShader& src);
	AnimaShader& operator=(AnimaShader&& src);

	bool operator==(const AnimaShader& left);
	bool operator!=(const AnimaShader& left);

public:	
	void SetText(AnimaString text);
	AnimaString GetText();

	void SetType(AnimaShaderType type);
	AnimaShaderType GetType();

	bool Create();
	bool Delete();
	bool Compile();

	bool IsCreated();
	bool IsCompiled();

	AInt GetID();

	void AddShaderData(const AnimaShaderData& data);
	AInt GetShaderDataCount() const;
	AnimaShaderData* GetShaderData(const AInt& index);
	AnimaShaderData* GetShaderData(const AnimaString& name);

	void AddShaderStaticGroupData(const AnimaShaderGroupData& groupData);
	AInt GetShaderStaticGroupDataCount() const;
	AnimaShaderGroupData* GetShaderStaticGroupData(const AInt& index);
	AnimaShaderGroupData* GetShaderStaticGroupData(const AnimaString& name);

	void AddShaderDynamicGroupData(const AnimaShaderGroupData& groupData);
	AInt GetShaderDynamicGroupDataCount() const;
	AnimaShaderGroupData* GetShaderDynamicGroupData(const AInt& index);
	AnimaShaderGroupData* GetShaderDynamicGroupData(const AnimaString& name);

private:
	AnimaShaderType _type;
	AnimaString		_text;

	AnimaMappedArray<AnimaShaderData> _data;
	AnimaMappedArray<AnimaShaderGroupData> _staticGroupData;
	AnimaMappedArray<AnimaShaderGroupData> _dynamicGroupData;

	AInt			_id;
	bool			_compiled;
};

END_ANIMA_ENGINE_NAMESPACE