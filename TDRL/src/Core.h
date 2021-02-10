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
