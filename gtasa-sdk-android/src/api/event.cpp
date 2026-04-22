#include <event.hpp>
#include <vector>
#include <algorithm>

namespace sdk::events {

/** --- Tipos Internos --- **/
struct Listener {
    EventHandle handle;
    RawCallback cb;
};

enum class OpType { Add, Remove };

struct Operation {
    OpType type;
    EventId id;
    Listener listener;
    EventHandle handle;
};

/** --- Estado do Sistema --- **/
static std::vector<Listener>  g_events[EVENT_COUNT];
static std::vector<Operation> g_pendingOps;
static EventHandle            g_lastHandle = 0;
static bool                   g_isEmitting = false;

// Inicialização estática para garantir reserva de memória
struct EventSystemInit {
    EventSystemInit() { g_pendingOps.reserve(32); }
} static g_eventSystemInit;

/** --- Funções Auxiliares(Internal Helpers) --- **/
static void flushOps() {
    for(auto& op : g_pendingOps) {
        if(op.id >= EVENT_COUNT) continue;

        auto& listeners = g_events[op.id];

        if(op.type == OpType::Add) {
            listeners.push_back(std::move(op.listener));
        } 
        else if(op.type == OpType::Remove) {
            auto it = std::remove_if(listeners.begin(), listeners.end(),
                [&](const Listener& l) { return l.handle == op.handle; });
            
            listeners.erase(it, listeners.end());
        }
    }
    g_pendingOps.clear();
}

/** --- API Pública --- **/

EventHandle subscribeRaw(EventId id, RawCallback cb) {
    if(id >= EVENT_COUNT) return 0;

    EventHandle handle = ++g_lastHandle;
    Listener listener{ handle, std::move(cb) };

    if(g_isEmitting) {
        g_pendingOps.push_back({ OpType::Add, id, std::move(listener), 0 });
    } else {
        g_events[id].push_back(std::move(listener));
    }

    return handle;
}

void unsubscribe(EventId id, EventHandle handle) {
    if(id >= EVENT_COUNT) return;

    if(g_isEmitting) {
        g_pendingOps.push_back({ OpType::Remove, id, {}, handle });
        return;
    }

    auto& listeners = g_events[id];
    auto it = std::remove_if(listeners.begin(), listeners.end(),
        [handle](const Listener& l) { return l.handle == handle; });

    listeners.erase(it, listeners.end());
}

} // namespace sdk::events

/** --- Motor de Emissão(Internal) --- **/
namespace sdk::internal::events {

void emitRaw(sdk::events::EventId id, void* data, size_t size) {
    using namespace sdk::events;

    if(id >= EVENT_COUNT) return;

    g_isEmitting = true;
    {
        EventData e{ data, size };
        const auto& listeners = g_events[id];

        for(const auto& l : listeners) {
            if(l.cb) l.cb(e);
        }
    }
    g_isEmitting = false;

    // Processa inscrições/cancelamentos feitos durante o loop de emissão
    flushOps();
}

} // namespace sdk::internal::events