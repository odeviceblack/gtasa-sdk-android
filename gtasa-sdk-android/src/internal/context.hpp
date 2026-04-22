#pragma once

#include <cstdint>
#include <Gloss.h>

#define LIB_NAME "libGTASA.so"

namespace sdk::internal {

/** --- Gerenciamento de Contexto do SDK --- **/

class Context {
public:
	static bool Init() noexcept;
	static void Shutdown() noexcept;

	/** --- Getters --- **/
	static GHandle Handle() noexcept;
	static uintptr_t Base() noexcept;

	static bool IsValid() noexcept;

private:
	static inline GHandle m_handle = nullptr;
	static inline uintptr_t m_base = 0;
};

} // namespace sdk::internal