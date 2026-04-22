#pragma once

#include <tuple>
#include <utility>

#include <event_base.hpp>

namespace sdk::internal::events {

/** --- Engine de Emissão --- **/

void emitRaw(sdk::events::EventId id, void* data, size_t size);

template<typename... Args>
void emit(sdk::events::EventId id, Args&&... args) {
	auto data = std::make_tuple(std::forward<Args>(args)...);
	auto copy = data;

	emitRaw(id, &copy, sizeof(copy));
}

} // namespace sdk::internal::events