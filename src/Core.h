#pragma once

#ifdef TDRL_ENABLE_ASSERT
	#define TDRL_ASSERT(x, ...) { if(!(x)) { TDRL_ERROR("Assertion failed: {0}", __VA_ARGS__); } }
	#define TDRL_CORE_ASSERT(x, ...) { if(!(x)) { TDRL_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); } }
#else
	#define TDRL_ASSERT(x, ...)
	#define TDRL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
