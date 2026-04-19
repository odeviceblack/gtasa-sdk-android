#include "context.hpp"

namespace sdk::internal {

Context::Context(const char* lib_name) {
	load(lib_name);
}

Context::~Context() {
	unload();
}

void Context::load(const char* lib_name) {
	m_handle = GlossOpen(lib_name);

	if (m_handle) {
		m_base = GlossGetLibBiasEx(m_handle);
	} else {
		m_base = 0;
	}
}

void Context::unload() {
	if (m_handle) {
		GlossClose(m_handle, false);
		m_handle = nullptr;
		m_base = 0;
	}
}

Context::Context(Context&& other) noexcept {
	m_handle = other.m_handle;
	m_base = other.m_base;

	other.m_handle = nullptr;
	other.m_base = 0;
}

Context& Context::operator=(Context&& other) noexcept {
	if (this != &other) {
		unload();

		m_handle = other.m_handle;
		m_base = other.m_base;

		other.m_handle = nullptr;
		other.m_base = 0;
	}
	return *this;
}

GHandle Context::handle() const noexcept {
	return m_handle;
}

uintptr_t Context::base() const noexcept {
	return m_base;
}

Context::operator bool() const noexcept {
	return m_handle != nullptr;
}

}