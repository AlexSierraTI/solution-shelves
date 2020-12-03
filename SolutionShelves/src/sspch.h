#pragma once

#include "Engine/Core/PlatformDetection.h"

#ifdef SS_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif
	#ifdef _WIN32
		#define _WIN32_WINNT 0x0A00
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

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#ifdef SS_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
