#pragma once

#include <memory>

#include "Core.h"
#include "include/spdlog/spdlog.h"

namespace tdrl {

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {
			return s_CoreLogger;
		}

		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() {
			return s_ClientLogger;
		}

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

} // namespace tdrl

// Core log macros.
#define TDRL_CORE_TRACE(...)  ::tdrl::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define TDRL_CORE_INFO(...)   ::tdrl::Log::GetCoreLogger()->info(__VA_ARGS__);
#define TDRL_CORE_WARN(...)   ::tdrl::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define TDRL_CORE_ERROR(...)  ::tdrl::Log::GetCoreLogger()->error(__VA_ARGS__);
#define TDRL_CORE_FATAL(...)  ::tdrl::Log::GetCoreLogger()->fatal(__VA_ARGS__);

// Client log macros.
#define TDRL_TRACE(...)  ::tdrl::Log::GetClientLogger()->trace(__VA_ARGS__);
#define TDRL_INFO(...)   ::tdrl::Log::GetClientLogger()->info(__VA_ARGS__);
#define TDRL_WARN(...)   ::tdrl::Log::GetClientLogger()->warn(__VA_ARGS__);
#define TDRL_ERROR(...)  ::tdrl::Log::GetClientLogger()->error(__VA_ARGS__);
#define TDRL_FATAL(...)  ::tdrl::Log::GetClientLogger()->fatal(__VA_ARGS__);