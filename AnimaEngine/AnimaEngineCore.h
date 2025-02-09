#ifndef _ANIMA_ENGINE_LIB_H
#define _ANIMA_ENGINE_LIB_H

#if defined ANIMA_ENGINE_EXPORT_ENABLED
#	if _MSC_VER
#		define ANIMA_ENGINE_EXPORT __declspec(dllexport)
#		define ANIMA_ENGINE_EXPIMP_TEMPLATE extern
#	else
#		define ANIMA_ENGINE_EXPORT __attribute__ ((visibility ("default")))
#		define ANIMA_ENGINE_EXPIMP_TEMPLATE
#	endif
#else
#	if _MSC_VER
#		define ANIMA_ENGINE_EXPORT __declspec(dllimport)
#		define ANIMA_ENGINE_EXPIMP_TEMPLATE
#	else
#		define ANIMA_ENGINE_EXPORT
#		define ANIMA_ENGINE_EXPIMP_TEMPLATE
#	endif
#endif

#define ANIMA_ENGINE_NAMESPACE Anima
#define BEGIN_ANIMA_ENGINE_NAMESPACE namespace Anima {
#define END_ANIMA_ENGINE_NAMESPACE }

#if defined _MSC_VER
#	define ANIMA_ENGINE_ALIGN_OF(a)	__alignof(a)
#else
#	define ANIMA_ENGINE_ALIGN_OF(a)	__alignof__(a)
#endif

#define ANIMA_ALLOCATOR_DEBUG

#if defined _MSC_VER
#	define _ANIMA_ENGINE_WIN32
#	define _ANIMA_ENGINE_WGL
#else
#	define _ANIMA_ENGINE_COCOA
#	define _ANIMA_ENGINE_NSGL
#	define _ANIMA_ENGINE_USE_MENUBAR
#	define _ANIMA_ENGINE_USE_RETINA
#endif

#define _ANIMA_ENGINE_USE_OPENGL

#define INDEXED_DRAWING

#define M_2PI	2.0f * (AFloat)M_PI

#if (ANIMA_ENGINE_USE_NVTOOLS) && (!defined ANIMA_FRAME_DEBUG)
#	include <nvToolsExt.h>
	extern "C" ANIMA_ENGINE_EXPORT void AnimaFrameDebugPush(const char* title);
	extern "C" ANIMA_ENGINE_EXPORT void AnimaFrameDebugPop();
#	define ANIMA_FRAME_PUSH(title)		AnimaFrameDebugPush(title);
#	define ANIMA_FRAME_POP()			AnimaFrameDebugPop();
#	define ANIMA_FRAME_DEBUG
#else
	extern "C" ANIMA_ENGINE_EXPORT void AnimaFrameDebugPush(const char* title);
	extern "C" ANIMA_ENGINE_EXPORT void AnimaFrameDebugPop();
#	define ANIMA_FRAME_PUSH(title)
#	define ANIMA_FRAME_POP()
#endif

#define _ANIMA_ENGINE_VERSION_MAJOR			0
#define _ANIMA_ENGINE_VERSION_MINOR			0
#define _ANIMA_ENGINE_VERSION_REVISION		0
#define _ANIMA_ENGINE_VERSION_NUMBER		"0.0.0"

#define RENDERER_PREFIX	"REN"
#define GBUFFER_PREFIX	"GB"

#include <vector>

#endif //_ANIMA_ENGINE_LIB_H