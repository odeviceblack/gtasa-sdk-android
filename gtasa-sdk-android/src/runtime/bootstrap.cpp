#include "sdk.hpp"
#include "events.hpp"
#include "memory.hpp"

namespace sdk::runtime {

DECL_HOOK(void, CGame_Process) {
	CGame_Process();
	sdk::Events::gameProcessEvent.emit();
}

void InitializeEvents() {
	auto& ctx = sdk::GetContext();
	INSTALL_HOOK(ctx, "_ZN5CGame7ProcessEv", CGame_Process);
}

}
