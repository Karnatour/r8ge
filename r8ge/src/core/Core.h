#pragma once

#include "PlatformDetection.h"

#include <memory>

#ifdef R8GE_DEBUG
	#if defined(R8GE_WINDOWS)
		#define R8GE_DEBUGBREAK() __debugbreak()
	#elif defined(R8GE_LINUX)
		#include <signal.h>
		#define R8GE_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
#else
	#define R8GE_DEBUGBREAK()
#endif