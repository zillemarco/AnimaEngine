//
//  AnimaLight.cpp
//  Anima
//
//  Created by Marco Zille on 26/11/14.
//
//

#include "AnimaLight.h"
#include "AnimaDataGeneratorsManager.h"
#include "AnimaShaderProgram.h"
#include "AnimaShadersManager.h"
#include "AnimaMath.h"
#include "AnimaFrustum.h"

#ifndef min
#	define min(a,b) (a < b ? a : b)
#endif

#ifndef max
#	define max(a,b) (a > b ? a : b)
#endif

BEGIN_ANIMA_ENGINE_NAMESPACE

//----------------------------------------------------------------
//						ANIMA LIGHT
//----------------------------------------------------------------
AnimaLight::AnimaLight(AnimaAllocator* allocator, AnimaDataGeneratorsManager* dataGeneratorManager, const AnimaString& name)
	: AnimaSceneObject(name, dataGeneratorManager, allocator)
{
	IMPLEMENT_ANIMA_CLASS(AnimaLight);

	ComputeLightMatrix(nullptr);
	UpdateLightGeometryMatrix();

	SetExtension(AnimaVertex3f(1.0f, 1.0f, 1.0f));
	AnimaSceneObject::SetColor("Color", 1.0f, 1.0f, 1.0f);
	AnimaSceneObject::SetFloat("Intensity", 1.0f);
	AnimaSceneObject::SetBoolean("CastShadows", false);
	
	_shaderSource = ASDSO_LIGHT;
}

AnimaLight::AnimaLight(const AnimaLight& src)
	: AnimaSceneObject(src)
{
	UpdateLightGeometryMatrix();
}

AnimaLight::AnimaLight(AnimaLight&& src)
	: AnimaSceneObject(src)
{
	UpdateLightGeometryMatrix();
}

AnimaLight::~AnimaLight()
{
}

AnimaLight& AnimaLight::operator=(const AnimaLight& src)
{
	if (this != &src)
	{
		AnimaSceneObject::operator=(src);
		UpdateLightGeometryMatrix();
	}
	return *this;
}

AnimaLight& AnimaLight::operator=(AnimaLight&& src)
{
	if (this != &src)
	{
		AnimaSceneObject::operator=(src);
		UpdateLightGeometryMatrix();
	}
	return *this;
}

ptree AnimaLight::GetObjectTree(bool saveName) const
{
	ptree tree;
	
	if (saveName)
		tree.add("AnimaLight.Name", GetName());
	
	tree.add_child("AnimaLight.SceneObject", AnimaSceneObject::GetObjectTree(false));
	
	return tree;
}

bool AnimaLight::ReadObject(const ptree& objectTree, AnimaScene* scene, bool readName)
{
	try
	{
		if (readName)
			SetName(objectTree.get<AnimaString>("AnimaLight.Name"));
		
		ptree sceneObjectTree = objectTree.get_child("AnimaLight.SceneObject");
		return AnimaSceneObject::ReadObject(sceneObjectTree, scene, false);
	}
	catch (boost::property_tree::ptree_bad_path& exception)
	{
		AnimaLogger::LogMessageFormat("ERROR - Error parsing light: %s", exception.what());
		return false;
	}
	catch (boost::property_tree::ptree_bad_data& exception)
	{
		AnimaLogger::LogMessageFormat("ERROR - Error parsing light: %s", exception.what());
		return false;
	}
}

void AnimaLight::SetExtension(const AnimaVertex3f& extension)
{
	AnimaSceneObject::SetVector("Extension", extension);
}

AnimaVertex3f AnimaLight::GetExtension() const
{
	return AnimaSceneObject::GetVector3f("Extension");
}

void AnimaLight::UpdateLightGeometryMatrix()
{
	AnimaLight::SetMatrix("LightGeometryMatrix", AnimaMatrix());
}

void AnimaLight::SetColor(const AnimaColor3f& color)
{
	AnimaSceneObject::SetColor("Color", color);
}

void AnimaLight::SetColor(AFloat r, AFloat g, AFloat b)
{
	AnimaSceneObject::SetColor("Color", r, g, b);
}

void AnimaLight::SetIntensity(AFloat intensity)
{
	AnimaSceneObject::SetFloat("Intensity", intensity);
}

void AnimaLight::SetDirection(const AnimaVertex3f& direction)
{
	ANIMA_ASSERT(false);
}

void AnimaLight::SetDirection(AFloat x, AFloat y, AFloat z)
{
	ANIMA_ASSERT(false);
}

AnimaColor3f AnimaLight::GetColor()
{
	return AnimaSceneObject::GetColor3f("Color");
}

AFloat AnimaLight::GetIntensity()
{
	return AnimaSceneObject::GetFloat("Intensity");
}

AnimaVertex3f AnimaLight::GetDirection()
{
	ANIMA_ASSERT(false);
	return AnimaVertex3f();
}

void AnimaLight::SetConstantAttenuation(AFloat attenuation)
{
	ANIMA_ASSERT(false);
}

void AnimaLight::SetLinearAttenuation(AFloat attenuation)
{
	ANIMA_ASSERT(false);
}

void AnimaLight::SetExponentAttenuation(AFloat attenuation)
{
	ANIMA_ASSERT(false);
}

AFloat AnimaLight::GetConstantAttenuation()
{
	ANIMA_ASSERT(false);
	return 0.0f;
}

AFloat AnimaLight::GetLinearAttenuation()
{
	ANIMA_ASSERT(false);
	return 0.0f;
}

AFloat AnimaLight::GetExponentAttenuation()
{
	ANIMA_ASSERT(false);
	return 0.0f;
}

void AnimaLight::SetRange(AFloat range)
{
	ANIMA_ASSERT(false);
}

AFloat AnimaLight::GetRange()
{
	ANIMA_ASSERT(false);
	return 0.0f;
}

void AnimaLight::SetCutoff(AFloat c)
{
	ANIMA_ASSERT(false);
}

AFloat AnimaLight::GetCutoff()
{
	ANIMA_ASSERT(false);
	return 0.0f;
}

AnimaMatrix AnimaLight::GetViewMatrix()
{
	return AnimaSceneObject::GetMatrix("ViewMatrix");
}

AnimaMatrix AnimaLight::GetProjectionMatrix()
{
	return AnimaSceneObject::GetMatrix("ProjectionMatrix");
}

AnimaMatrix AnimaLight::GetProjectionViewMatrix()
{
	return AnimaSceneObject::GetMatrix("ProjectionViewMatrix");
}

void AnimaLight::ComputeLightMatrix(AnimaCamera* activeCamera)
{
	AnimaSceneObject::SetMatrix("ViewMatrix", AnimaMatrix());
	AnimaSceneObject::SetMatrix("ProjectionMatrix", AnimaMatrix());
	AnimaSceneObject::SetMatrix("ProjectionViewMatrix", AnimaMatrix());
}

AnimaFrustum* AnimaLight::GetFrustum()
{
	return &_frustum;
}

//----------------------------------------------------------------
//						ANIMA DIRECTIONAL LIGHT
//----------------------------------------------------------------
AnimaDirectionalLight::AnimaDirectionalLight(AnimaAllocator* allocator, AnimaDataGeneratorsManager* dataGeneratorManager, const AnimaString& name)
	: AnimaLight(allocator, dataGeneratorManager, name)
{
	IMPLEMENT_ANIMA_CLASS(AnimaDirectionalLight);
	AnimaLight::SetVector("Direction", AnimaVertex3f(-1.0f, -1.0f, -1.0f).Normalized());
	AnimaLight::SetVector("ShadowMapTexelSize", AnimaVertex2f(1.0f / 1024.0f));
	AnimaLight::SetFloat("ShadowMapBias", 1.0f / 1024.0f);
	AnimaLight::SetBoolean("CastShadows", true);

	SetExtension(AnimaVertex3f(100.0f, 100.0f, 100.0f));

	ComputeLightMatrix(nullptr);
	UpdateLightGeometryMatrix();
}

AnimaDirectionalLight::~AnimaDirectionalLight()
{
}

ptree AnimaDirectionalLight::GetObjectTree(bool saveName) const
{
	ptree tree;
	
	if (saveName)
		tree.add("AnimaDirectionalLight.Name", GetName());
	
	tree.add_child("AnimaDirectionalLight.Light", AnimaLight::GetObjectTree(false));
	
	return tree;
}

bool AnimaDirectionalLight::ReadObject(const ptree& objectTree, AnimaScene* scene, bool readName)
{
	try
	{
		if (readName)
			SetName(objectTree.get<AnimaString>("AnimaDirectionalLight.Name"));
		
		ptree lightTree = objectTree.get_child("AnimaDirectionalLight.Light");
		return AnimaLight::ReadObject(lightTree, scene, false);
	}
	catch (boost::property_tree::ptree_bad_path& exception)
	{
		AnimaLogger::LogMessageFormat("ERROR - Error parsing directional light: %s", exception.what());
		return false;
	}
	catch (boost::property_tree::ptree_bad_data& exception)
	{
		AnimaLogger::LogMessageFormat("ERROR - Error parsing directional light: %s", exception.what());
		return false;
	}
}

void AnimaDirectionalLight::UpdateLightGeometryMatrix()
{
	AnimaLight::SetMatrix("LightGeometryMatrix", AnimaMatrix::MakeRotationDeg(1.0f, 0.0, 0.0, 90.0));
}

void AnimaDirectionalLight::SetDirection(const AnimaVertex3f& direction)
{
	AnimaSceneObject::SetVector("Direction", direction.Normalized());
	ComputeLightMatrix(nullptr);	// TODO
}

void AnimaDirectionalLight::SetDirection(AFloat x, AFloat y, AFloat z)
{
	AnimaSceneObject::SetVector("Direction", AnimaVertex3f(x, y, z).Normalized());
	ComputeLightMatrix(nullptr);	// TODO
}

AnimaVertex3f AnimaDirectionalLight::GetDirection()
{
	return AnimaSceneObject::GetVector3f("Direction");
}

void AnimaDirectionalLight::ComputeLightMatrix(AnimaCamera* activeCamera)
{
	if (activeCamera == nullptr)
		return;

	//AnimaFrustum* cameraFrustum = activeCamera->GetFrustum();

	//AnimaVertex3f direction = GetDirection();												// asse z
	//AnimaVertex3f perpVec1 = (direction ^ AnimaVertex3f(0.0f, 0.0f, 1.0f)).Normalized();	// asse y
	//AnimaVertex3f perpVec2 = (direction ^ perpVec1).Normalized();							// asse x

	//AnimaMatrix rotMat;	
	//rotMat.m[0] = perpVec2.x;	rotMat.m[1] = perpVec1.x;	rotMat.m[2] =	direction.x;
	//rotMat.m[4] = perpVec2.y;	rotMat.m[5] = perpVec1.y;	rotMat.m[6] =	direction.y;
	//rotMat.m[8] = perpVec2.z;	rotMat.m[9] = perpVec1.z;	rotMat.m[10] =	direction.z;
	//
	//AnimaVertex3f frustumVertices[8];
	//cameraFrustum->GetFrustumVertices(frustumVertices);
	//
	//for (AInt i = 0; i < 8; i++)
	//	frustumVertices[i] = rotMat * frustumVertices[i];

	//AnimaVertex3f minV = frustumVertices[0], maxV = frustumVertices[0];
	//for (AInt i = 1; i < 8; i++)
	//{
	//	minV.x = min(minV.x, frustumVertices[i].x);
	//	minV.y = min(minV.y, frustumVertices[i].y);
	//	minV.z = min(minV.z, frustumVertices[i].z);
	//	maxV.x = max(maxV.x, frustumVertices[i].x);
	//	maxV.y = max(maxV.y, frustumVertices[i].y);
	//	maxV.z = max(maxV.z, frustumVertices[i].z);
	//}

	//AnimaVertex3f extends = maxV - minV;
	//extends *= 0.5f;
	
	//AnimaMatrix viewMatrix = AnimaMatrix::MakeLookAt(cameraFrustum->GetBoundingBoxCenter(), direction, perpVec1);
	//AnimaMatrix projectionMatrix = AnimaMatrix::MakeOrtho(-extends.x, extends.x, -extends.y, extends.y, -extends.z, extends.z);
	//AnimaMatrix projectionViewMatrix = projectionMatrix * viewMatrix;

	AnimaVertex3f direction = GetDirection();											// asse z
	AnimaVertex3f yAxis = (direction ^ AnimaVertex3f(0.0f, 0.0f, 1.0f)).Normalized();	// asse y
	AnimaVertex3f extension = GetExtension();

	AnimaMatrix viewMatrix = AnimaMatrix::MakeLookAt(activeCamera->GetPosition(), direction, yAxis);
	AnimaMatrix projectionMatrix = AnimaMatrix::MakeOrtho(-extension.x, extension.x, -extension.y, extension.y, -extension.z, extension.z);
	AnimaMatrix projectionViewMatrix = projectionMatrix * viewMatrix;
	
	AnimaSceneObject::SetMatrix("ViewMatrix", viewMatrix);
	AnimaSceneObject::SetMatrix("ProjectionMatrix", projectionMatrix);
	AnimaSceneObject::SetMatrix("ProjectionViewMatrix", projectionViewMatrix);

	_frustum.ComputeFrustum(projectionViewMatrix);
}

void AnimaDirectionalLight::UpdateCullFace(AnimaCamera* activeCamera)
{
}

const char* AnimaDirectionalLight::GetShaderName()
{
	return "directional-light";
}

bool AnimaDirectionalLight::CreateShader(AnimaShadersManager* shadersManager)
{
	if (shadersManager->GetProgramFromName("directional-light"))
		return true;

	ANIMA_ASSERT(false);
	return false;
}

//----------------------------------------------------------------
//						ANIMA POINT LIGHT
//----------------------------------------------------------------
AnimaPointLight::AnimaPointLight(AnimaAllocator* allocator, AnimaDataGeneratorsManager* dataGeneratorManager, const AnimaString& name)
	: AnimaLight(allocator, dataGeneratorManager, name)
{
	IMPLEMENT_ANIMA_CLASS(AnimaPointLight);
	AnimaSceneObject::SetFloat("ConstantAttenuation", 0.0f);
	AnimaSceneObject::SetFloat("LinearAttenuation", 0.0f);
	AnimaSceneObject::SetFloat("ExponentAttenuation", 1.0f);
	AnimaSceneObject::SetFloat("Range", 20.0f);

	UpdateLightGeometryMatrix();
}

AnimaPointLight::~AnimaPointLight()
{
}

ptree AnimaPointLight::GetObjectTree(bool saveName) const
{
	ptree tree;
	
	if (saveName)
		tree.add("AnimaPointLight.Name", GetName());
	
	tree.add_child("AnimaPointLight.Light", AnimaLight::GetObjectTree(false));
	
	return tree;
}

bool AnimaPointLight::ReadObject(const ptree& objectTree, AnimaScene* scene, bool readName)
{
	try
	{
		if (readName)
			SetName(objectTree.get<AnimaString>("AnimaPointLight.Name"));
		
		ptree lightTree = objectTree.get_child("AnimaPointLight.Light");
		return AnimaLight::ReadObject(lightTree, scene, false);
	}
	catch (boost::property_tree::ptree_bad_path& exception)
	{
		AnimaLogger::LogMessageFormat("ERROR - Error parsing point light: %s", exception.what());
		return false;
	}
	catch (boost::property_tree::ptree_bad_data& exception)
	{
		AnimaLogger::LogMessageFormat("ERROR - Error parsing point light: %s", exception.what());
		return false;
	}
}

void AnimaPointLight::UpdateLightGeometryMatrix()
{
	AFloat range = GetRange();
	AnimaVertex3f position = GetPosition();

	AnimaSceneObject::SetMatrix("LightGeometryMatrix", AnimaMatrix::MakeTranslation(position) * AnimaMatrix::MakeScale(range, range, range, 1.0));
}

void AnimaPointLight::SetConstantAttenuation(AFloat attenuation)
{
	AnimaSceneObject::SetFloat("ConstantAttenuation", attenuation);
}

void AnimaPointLight::SetLinearAttenuation(AFloat attenuation)
{
	AnimaSceneObject::SetFloat("LinearAttenuation", attenuation);
}

void AnimaPointLight::SetExponentAttenuation(AFloat attenuation)
{
	AnimaSceneObject::SetFloat("ExponentAttenuation", attenuation);
}

void AnimaPointLight::SetRange(AFloat range)
{
	AnimaSceneObject::SetFloat("Range", range);
	UpdateLightGeometryMatrix();
}

void AnimaPointLight::SetPosition(AFloat x, AFloat y, AFloat z)
{
	AnimaSceneObject::SetPosition(x, y, z);
	UpdateLightGeometryMatrix();
}

AFloat AnimaPointLight::GetConstantAttenuation()
{
	return AnimaSceneObject::GetFloat("ConstantAttenuation");
}

AFloat AnimaPointLight::GetLinearAttenuation()
{
	return AnimaSceneObject::GetFloat("LinearAttenuation");
}

AFloat AnimaPointLight::GetExponentAttenuation()
{
	return AnimaSceneObject::GetFloat("ExponentAttenuation");
}

AFloat AnimaPointLight::GetRange()
{
	return AnimaSceneObject::GetFloat("Range");
}

void AnimaPointLight::UpdateCullFace(AnimaCamera* activeCamera)
{
	if (AnimaMath::PointInsideSphere(activeCamera->GetPosition(), GetPosition(), GetRange()))
		glCullFace(GL_FRONT);
	else
		glCullFace(GL_BACK);
}

const char* AnimaPointLight::GetShaderName()
{
	return "point-light";
}

bool AnimaPointLight::CreateShader(AnimaShadersManager* shadersManager)
{
	if (shadersManager->GetProgramFromName("point-light"))
		return true;

	ANIMA_ASSERT(false);
	return false;
}

//----------------------------------------------------------------
//						ANIMA SPOT LIGHT
//----------------------------------------------------------------
AnimaSpotLight::AnimaSpotLight(AnimaAllocator* allocator, AnimaDataGeneratorsManager* dataGeneratorManager,  const AnimaString& name)
	: AnimaPointLight(allocator, dataGeneratorManager, name)
{
	IMPLEMENT_ANIMA_CLASS(AnimaSpotLight);

	AnimaSceneObject::SetVector("Direction", AnimaVertex3f(0.0f, -1.0f, 0.0f).Normalized());
	AnimaSceneObject::SetFloat("Cutoff", 0.7f);
}

AnimaSpotLight::~AnimaSpotLight()
{
}

ptree AnimaSpotLight::GetObjectTree(bool saveName) const
{
	ptree tree;
	
	if (saveName)
		tree.add("AnimaSpotLight.Name", GetName());
	
	tree.add_child("AnimaSpotLight.PointLight", AnimaPointLight::GetObjectTree(false));
	
	return tree;
}

bool AnimaSpotLight::ReadObject(const ptree& objectTree, AnimaScene* scene, bool readName)
{
	try
	{
		if (readName)
			SetName(objectTree.get<AnimaString>("AnimaSpotLight.Name"));
		
		ptree lightTree = objectTree.get_child("AnimaSpotLight.PointLight");
		return AnimaPointLight::ReadObject(lightTree, scene, false);
	}
	catch (boost::property_tree::ptree_bad_path& exception)
	{
		AnimaLogger::LogMessageFormat("ERROR - Error parsing spot light: %s", exception.what());
		return false;
	}
	catch (boost::property_tree::ptree_bad_data& exception)
	{
		AnimaLogger::LogMessageFormat("ERROR - Error parsing spot light: %s", exception.what());
		return false;
	}
}

void AnimaSpotLight::UpdateLightGeometryMatrix()
{
	AFloat range = GetRange();
	AFloat raggio = range * tanf(acosf(GetCutoff()) / 2.0f);
	AnimaVertex3f position = GetPosition();

	AnimaSceneObject::SetMatrix("LightGeometryMatrix",	AnimaMatrix::MakeTranslation(position) * 
													(AnimaMatrix::MakeRotationZRad(_coneRotation.x) * (AnimaMatrix::MakeRotationYRad(_coneRotation.y) * AnimaMatrix::MakeRotationXRad(_coneRotation.x))) * 
													AnimaMatrix::MakeScale(raggio, range, raggio, 1.0));
}

void AnimaSpotLight::SetDirection(const AnimaVertex3f& direction)
{
	AnimaSceneObject::SetVector("Direction", direction.Normalized());
	UpdateConeRotation();
}

void AnimaSpotLight::SetDirection(AFloat x, AFloat y, AFloat z)
{
	AnimaSceneObject::SetVector("Direction", AnimaVertex3f(x, y, z).Normalized());
	UpdateConeRotation();
}

void AnimaSpotLight::SetCutoff(AFloat c)
{
	AnimaSceneObject::SetFloat("Cutoff", c);
}

AnimaVertex3f AnimaSpotLight::GetDirection()
{
	return AnimaSceneObject::GetVector3f("Direction");
}

AFloat AnimaSpotLight::GetCutoff()
{
	return AnimaSceneObject::GetFloat("Cutoff");
}

void AnimaSpotLight::UpdateCullFace(AnimaCamera* activeCamera)
{
	if (AnimaMath::PointInsideCone(activeCamera->GetPosition(), GetPosition(), GetDirection(), GetRange(), acosf(GetCutoff()) / 2.0f))
		glCullFace(GL_FRONT);
	else
		glCullFace(GL_BACK);
}

void AnimaSpotLight::UpdateConeRotation()
{
	Anima::AnimaVertex3f A = GetDirection();
	
	// Questa è la direzione in cui punta i cono quando creato
	Anima::AnimaVertex3f B(0.0f, -1.0f, 0.0f);
	
	A.Normalize();
	
	Anima::AnimaVertex3f v = A ^ B;
	float s = v.Length2();
	float c = A * B;
	
	Anima::AnimaMatrix vx;
	vx.x[0] = 0.0f;	vx.x[1] = v.z;	vx.x[2] = -v.y;
	vx.y[0] = -v.z;	vx.y[1] = 0.0f;	vx.y[2] = v.x;
	vx.z[0] = v.y;	vx.z[1] = -v.x;	vx.z[2] = 0.0f;
	
	Anima::AnimaMatrix vx2 = vx * vx;
	
	Anima::AnimaMatrix m;
	m += vx + (vx2 * ((1 - c) / s));
	
	_coneRotation = m.GetRotationAxes();

	UpdateLightGeometryMatrix();
}

const char* AnimaSpotLight::GetShaderName()
{
	return "spot-light";
}

bool AnimaSpotLight::CreateShader(AnimaShadersManager* shadersManager)
{
	if (shadersManager->GetProgramFromName("spot-light"))
		return true;
	
	ANIMA_ASSERT(false);
	return false;
}


//----------------------------------------------------------------
//						ANIMA HEMISPHERE LIGHT
//----------------------------------------------------------------
AnimaHemisphereLight::AnimaHemisphereLight(AnimaAllocator* allocator, AnimaDataGeneratorsManager* dataGeneratorManager, const AnimaString& name)
	: AnimaLight(allocator, dataGeneratorManager, name)
{
	IMPLEMENT_ANIMA_CLASS(AnimaHemisphereLight);

	AnimaSceneObject::SetColor("SkyColor", AnimaColor3f(1.0f, 1.0f, 1.0f));
	AnimaSceneObject::SetColor("GroundColor", AnimaColor3f(0.0f, 0.0f, 0.0f));

	UpdateLightGeometryMatrix();
}

AnimaHemisphereLight::~AnimaHemisphereLight()
{
}

ptree AnimaHemisphereLight::GetObjectTree(bool saveName) const
{
	ptree tree;
	
	if (saveName)
		tree.add("AnimaHemisphereLight.Name", GetName());
	
	tree.add_child("AnimaHemisphereLight.Light", AnimaLight::GetObjectTree(false));
	
	return tree;
}

bool AnimaHemisphereLight::ReadObject(const ptree& objectTree, AnimaScene* scene, bool readName)
{
	try
	{
		if (readName)
			SetName(objectTree.get<AnimaString>("AnimaHemisphereLight.Name"));
		
		ptree lightTree = objectTree.get_child("AnimaHemisphereLight.Light");
		return AnimaLight::ReadObject(lightTree, scene, false);
	}
	catch (boost::property_tree::ptree_bad_path& exception)
	{
		AnimaLogger::LogMessageFormat("ERROR - Error parsing hemisphere light: %s", exception.what());
		return false;
	}
	catch (boost::property_tree::ptree_bad_data& exception)
	{
		AnimaLogger::LogMessageFormat("ERROR - Error parsing hemisphere light: %s", exception.what());
		return false;
	}
}

void AnimaHemisphereLight::UpdateLightGeometryMatrix()
{
	AnimaSceneObject::SetMatrix("LightGeometryMatrix", AnimaMatrix::MakeRotationDeg(1.0f, 0.0, 0.0, 90.0));
}

void AnimaHemisphereLight::SetSkyColor(const AnimaColor3f& color)
{
	AnimaSceneObject::SetColor("SkyColor", color);
}

void AnimaHemisphereLight::SetSkyColor(AFloat r, AFloat g, AFloat b)
{
	AnimaSceneObject::SetColor("SkyColor", AnimaColor3f(r, g, b));
}

AnimaColor3f AnimaHemisphereLight::GetSkyColor()
{
	return AnimaSceneObject::GetColor3f("SkyColor");
}

void AnimaHemisphereLight::SetGroundColor(const AnimaColor3f& color)
{
	AnimaSceneObject::SetColor("GroundColor", color);
}

void AnimaHemisphereLight::SetGroundColor(AFloat r, AFloat g, AFloat b)
{
	AnimaSceneObject::SetColor("GroundColor", AnimaColor3f(r, g, b));
}

AnimaColor3f AnimaHemisphereLight::GetGroundColor()
{
	return AnimaSceneObject::GetColor3f("GroundColor");
}

void AnimaHemisphereLight::UpdateCullFace(AnimaCamera* activeCamera)
{
}

const char* AnimaHemisphereLight::GetShaderName()
{
	return "hemisphere-light";
}

bool AnimaHemisphereLight::CreateShader(AnimaShadersManager* shadersManager)
{
	if (shadersManager->GetProgramFromName("hemisphere-light"))
		return true;

	ANIMA_ASSERT(false);
	return false;
}

END_ANIMA_ENGINE_NAMESPACE
