//
// Created by Vojta on 23.02.2024.
//

#pragma once

#include "core/PlatformDetection.h"

#ifdef R8GE_WINDOWS
	#ifndef NOMINMAX
		// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
		#define NOMINMAX
	#endif
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "core/Core.h"

#include "core/Logger.h"

#ifdef R8GE_WINDOWS
	#include <Windows.h>
#endif
