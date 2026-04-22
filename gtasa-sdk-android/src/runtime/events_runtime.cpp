#include <internal/event_caller.hpp>
#include <internal/memory.hpp>

namespace sdk::runtime {

/** --- Game Events --- **/

DECL_HOOK(bool, CGame_InitializeGame) {
	bool result = CGame_InitializeGame();
	sdk::internal::events::emit(sdk::events::EVENT_GAME_INIT);
	return result;
}

DECL_HOOK(void, CGame_ReInitGameObjectVariables) {
	CGame_ReInitGameObjectVariables();
	sdk::internal::events::emit(sdk::events::EVENT_RESTART_GAME);
}

DECL_HOOK(void, CGame_Process) {
	CGame_Process();
	sdk::internal::events::emit(sdk::events::EVENT_GAME_PROCESS);
}

/** --- Draw Events --- **/

DECL_HOOK(void, Render2dStuff) {
	Render2dStuff();
	sdk::internal::events::emit(sdk::events::EVENT_DRAWING);
}

DECL_HOOK(void, Render2dStuffAfterFade) {
	Render2dStuffAfterFade();
	sdk::internal::events::emit(sdk::events::EVENT_DRAW_AFTER_FADE);
}

DECL_HOOK(void, CHud_Draw) {
	CHud_Draw();
	sdk::internal::events::emit(sdk::events::EVENT_DRAW_HUD);
}

/** --- RW Events --- **/

DECL_HOOK(void, CGame_InitialiseRenderWare) {
	CGame_InitialiseRenderWare();
	sdk::internal::events::emit(sdk::events::EVENT_RENDERWARE_INIT);
}

/** --- Core Runtime --- **/

bool InitializeEvents() {
	bool success = true;

	// Hooks: Game
	success &= INSTALL_HOOK("_Z14InitialiseGamev", CGame_InitializeGame);
	success &= INSTALL_HOOK("_ZN5CGame25ReInitGameObjectVariablesEv", CGame_ReInitGameObjectVariables);
	success &= INSTALL_HOOK("_ZN5CGame7ProcessEv", CGame_Process);
	
	// Hooks: Draw
	success &= INSTALL_HOOK("_Z13Render2dStuffv", Render2dStuff);
	success &= INSTALL_HOOK("_Z22Render2dStuffAfterFadev", Render2dStuffAfterFade);
	success &= INSTALL_HOOK("_ZN4CHud4DrawEv", CHud_Draw);

	// Hooks: RW
	success &= INSTALL_HOOK("_ZN5CGame20InitialiseRenderWareEv", CGame_InitialiseRenderWare);

	return success;
}

} // namespace sdk::runtime