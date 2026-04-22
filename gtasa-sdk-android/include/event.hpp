#pragma once

#include <functional>
#include <tuple>
#include <cstdint>

#include <platform.hpp>
#include <event_base.hpp>

namespace sdk::events {

/** --- Tipos e Definições --- **/

using EventHandle = uint32_t;
using RawCallback = std::function<void(const EventData&)>;

/** --- API de Subscrição --- **/

SDK_API EventHandle subscribeRaw(EventId id, RawCallback cb);
SDK_API void unsubscribe(EventId id, EventHandle handle);

/** --- Helpers de Template (Traits) --- **/

template<typename T>
struct function_traits : function_traits<decltype(&T::operator())> {};

template<typename C, typename R, typename... Args>
struct function_traits<R(C::*)(Args...)> {
	using args_tuple = std::tuple<Args...>;
};

template<typename R, typename... Args>
struct function_traits<R(*)(Args...)> {
	using args_tuple = std::tuple<Args...>;
};

/** --- API de Subscrição Tipada --- **/

template<typename Func>
EventHandle subscribe(EventId id, Func&& func) {
	using traits = function_traits<Func>;
	using ArgsTuple = typename traits::args_tuple;

	return subscribeRaw(id, [func](const EventData& e) {
		if(!e.data || e.size != sizeof(ArgsTuple))
			return;

		auto* data = reinterpret_cast<ArgsTuple*>(e.data);
		std::apply(func, *data);
	});
}

} // namespace sdk::events