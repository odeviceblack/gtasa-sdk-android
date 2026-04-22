#pragma once

#include <internal/context.hpp>
#include <cstdint>
#include <android/log.h>

/** --- Configurações de Logging --- **/

#define LOG_TAG "GTASASdk"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

/** --- Macros de Hooking --- **/

#define DECL_HOOK(ret, name, ...)			\
	using name##_t = ret(*)(__VA_ARGS__);	\
	inline name##_t name = nullptr;			\
	ret name##_hook(__VA_ARGS__)

#define INSTALL_HOOK(sym, name)	\
	sdk::internal::Memory::Hook(sym, name##_hook, name)

namespace sdk::internal {

/** --- Manipulação de Memória e Símbolos --- **/

class Memory {
public:
	static inline uintptr_t GetSymbol(const char* name) noexcept {
		if(!Context::IsValid()) return 0;
		
		uintptr_t addr = GlossSymbol(Context::Handle(), name, nullptr);
		if(!addr) {
			LOGE("Failed to find symbol: %s", name);
		}
		return addr;
	}

	template<typename T>
	static inline T Resolve(const char* name) noexcept {
		return reinterpret_cast<T>(GetSymbol(name));
	}

	template<typename T>
	static inline bool Hook(const char* name, T hook, T& original) noexcept {
		GHook h = GlossHookByName(
			LIB_NAME, name,
			reinterpret_cast<void*>(hook),
			reinterpret_cast<void**>(&original),
			nullptr
		);

		if(!h) {
			LOGE("Failed to hook symbol: %s", name);
			return false;
		}

		LOGI("Successfully hooked symbol: %s", name);
		return true;
	}
};

} // namespace sdk::internal