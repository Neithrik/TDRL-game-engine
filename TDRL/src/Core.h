#pragma once

#ifdef TDRL_PLATFORM_WINDOWS
	#ifdef TDRL_BUILD_DLL
		#define TDRL_API __declspec(dllexport)
	#else
		#define TDRL_API __declspec(dllimport)
	#endif
#else
	#error TDRL only supports Windows!
#endif

#ifdef TDRL_ENABLE_ASSERT
	#define TDRL_ASSERT(x, ...) { if(!(x)) { TDRL_ERROR("Assertion failed: {0}", __VA_ARGS__); } }
	#define TDRL_CORE_ASSERT(x, ...) { if(!(x)) { TDRL_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); } }
#else
	#define TDRL_ASSERT(x, ...)
	#define TDRL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
