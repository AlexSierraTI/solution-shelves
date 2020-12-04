#pragma once

#include "Engine/Core/PlatformDetection.h"

#ifdef SS_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif
#endif

#include <iostream>
#include <memory>
#include <thread>
#include <utility>
#include <algorithm>
#include <functional>
#include <optional>
#include <cstdint>

#include <string>
#include <sstream>
#include <mutex>
#include <deque>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Engine/Core/Base.h"

#include "Engine/Core/Log.h"

#include "Engine/Profiling/Instrumentor.h"

#ifdef SS_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
