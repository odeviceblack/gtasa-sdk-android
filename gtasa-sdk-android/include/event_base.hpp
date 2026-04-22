#pragma once

#include <cstdint>
#include <cstddef>

namespace sdk::events {

/** --- Definições de Identificadores --- **/

using EventId = uint32_t;

enum : EventId {
	EVENT_GAME_INIT = 1,
	EVENT_RESTART_GAME,
	EVENT_GAME_PROCESS,

	EVENT_DRAWING,
	EVENT_DRAW_AFTER_FADE,
	EVENT_DRAW_HUD,

	EVENT_RENDERWARE_INIT,

	EVENT_COUNT
};

/** --- Estruturas de Dados --- **/

struct EventData {
	void* data;
	size_t size;
};

} // namespace sdk::events