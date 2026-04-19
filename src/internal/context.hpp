#pragma once

#include <cstdint>
#include <Gloss.h>

namespace sdk::internal {

class Context {
public:
	Context() noexcept = default;
	explicit Context(const char* lib_name);

	~Context();

	Context(const Context&) = delete;
	Context& operator=(const Context&) = delete;

	Context(Context&& other) noexcept;
	Context& operator=(Context&& other) noexcept;

	GHandle handle() const noexcept;
	uintptr_t base() const noexcept;

	explicit operator bool() const noexcept;

private:
	GHandle m_handle = nullptr;
	uintptr_t m_base = 0;

	void load(const char* lib_name);
	void unload();
};

}