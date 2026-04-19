#pragma once

#include "context.hpp"
#include <cstdint>

namespace sdk::internal {

class Memory {
public:
	static inline uintptr_t GetSymbol(Context& ctx, const char* name) noexcept {
		if (!ctx) return 0;
		return GlossSymbol(ctx.handle(), name, nullptr);
	}

	template<typename T>
	static inline T Resolve(Context& ctx, const char* name) noexcept {
		return reinterpret_cast<T>(GetSymbol(ctx, name));
	}

	template<typename T>
	static inline bool Hook(Context& ctx, const char* name, T hook, T& original) noexcept {
		uintptr_t addr = GetSymbol(ctx, name);

		if (!addr)
			return false;

		GlossHook(
			reinterpret_cast<void*>(addr),
			reinterpret_cast<void*>(hook),
			reinterpret_cast<void**>(&original)
		);

		return true;
	}
};

}

// Macros
/*
#define DECL_RESOLVE(ret, name, ...)		\
	using name##_t = ret(*)(__VA_ARGS__);	\
	inline name##_t name = nullptr;

#define INSTALL_RESOLVE(ctx, sym, name)	\
	name = sdk::detail::Memory::Resolve<name##_t>(ctx, sym)
*/

#define DECL_HOOK(ret, name, ...)			\
	using name##_t = ret(*)(__VA_ARGS__);	\
	inline name##_t name = nullptr;			\
	ret name##_hook(__VA_ARGS__)

#define INSTALL_HOOK(ctx, sym, name)	\
	sdk::internal::Memory::Hook(ctx, sym, name##_hook, name)


