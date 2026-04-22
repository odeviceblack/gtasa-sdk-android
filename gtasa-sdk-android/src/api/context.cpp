#include <internal/context.hpp>

namespace sdk::internal {

/** --- Ciclo de Vida --- **/

bool Context::Init() noexcept {
	if(m_handle)
		return true;

	m_handle = GlossOpen(LIB_NAME);

	if(m_handle) {
		m_base = GlossGetLibBiasEx(m_handle);
		return true;
	}

	m_base = 0;
	return false;
}

void Context::Shutdown() noexcept {
	if(m_handle) {
		GlossClose(m_handle, false);
		m_handle = nullptr;
		m_base = 0;
	}
}

/** --- Acessores de Estado --- **/

GHandle Context::Handle() noexcept {
	return m_handle;
}

uintptr_t Context::Base() noexcept {
	return m_base;
}

bool Context::IsValid() noexcept {
	return m_handle != nullptr;
}

} // namespace sdk::internal