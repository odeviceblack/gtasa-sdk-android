#pragma once

#include <vector>
#include <cstdint>

#include <sdk.hpp>

namespace sdk {

template<typename... Args>
class Event {
public:
	using Callback = void(*)(Args...);
	using Id = uint32_t;

	Id subscribe(Callback cb) noexcept {
		Id id = ++m_lastId;
		m_entries.push_back({ id, cb });
		return id;
	}

	void unsubscribe(Id id) noexcept {
		for(size_t i = 0; i < m_entries.size(); ++i) {
			if(m_entries[i].id == id) {
				m_entries.erase(m_entries.begin() + i);
				return;
			}
		}
	}

	void emit(Args... args) noexcept {
		for(auto& e : m_entries) {
			e.cb(args...);
		}
	}

	void clear() noexcept {
		m_entries.clear();
	}

private:
	struct Entry {
		Id id;
		Callback cb;
	};

	std::vector<Entry> m_entries;
	Id m_lastId = 0;
};

struct Events {
	// Game Events
	SDK_API static Event<> initGameEvent;
	SDK_API static Event<> restartGameEvent;
	SDK_API static Event<> gameProcessEvent;
	
	// Draw Events
	SDK_API static Event<> drawingEvent;
	SDK_API static Event<> drawAfterFadeEvent;
	SDK_API static Event<> drawHudEvent;

	// RW Events
	SDK_API static Event<> initRwEvent;
};

}
