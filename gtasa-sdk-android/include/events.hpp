#pragma once

#include <vector>
#include <cstdint>

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
        for (size_t i = 0; i < m_entries.size(); ++i) {
            if (m_entries[i].id == id) {
                m_entries.erase(m_entries.begin() + i);
                return;
            }
        }
    }

    void emit(Args... args) noexcept {
        for (auto& e : m_entries) {
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
    static Event<> initRwEvent;
    static Event<> gameProcessEvent;
};

}
