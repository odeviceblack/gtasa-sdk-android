#include "events.hpp"
#include "memory.hpp"

namespace sdk::runtime {

// Game Events

DECL_HOOK(bool, CGame_InitializeGame) {
	bool result = CGame_InitializeGame();
	sdk::Events::initGameEvent.emit();
	return result;
}

DECL_HOOK(void, CGame_ReInitGameObjectVariables) {
	CGame_ReInitGameObjectVariables();
	sdk::Events::restartGameEvent.emit();
}

DECL_HOOK(void, CGame_Process) {
	CGame_Process();
	sdk::Events::gameProcessEvent.emit();
}

// Draw Events

DECL_HOOK(void, Render2dStuff) {
	Render2dStuff();
	sdk::Events::drawingEvent.emit();
}

DECL_HOOK(void, Render2dStuffAfterFade) {
	Render2dStuffAfterFade();
	sdk::Events::drawAfterFadeEvent.emit();
}

DECL_HOOK(void, CHud_Draw) {
	CHud_Draw();
	sdk::Events::drawHudEvent.emit();
}

// RW Events

DECL_HOOK(void, CGame_InitialiseRenderWare) {
	CGame_InitialiseRenderWare();
	sdk::Events::initRwEvent.emit();
}

void InitializeEvents() {
	auto& ctx = sdk::GetContext();

	// Game Events
	INSTALL_HOOK(ctx, "_Z14InitialiseGamev", CGame_InitializeGame);
	INSTALL_HOOK(ctx, "_ZN5CGame25ReInitGameObjectVariablesEv", CGame_ReInitGameObjectVariables);
	INSTALL_HOOK(ctx, "_ZN5CGame7ProcessEv", CGame_Process);
	
	// Draw Events
	INSTALL_HOOK(ctx, "_Z13Render2dStuffv", Render2dStuff);
	INSTALL_HOOK(ctx, "_Z22Render2dStuffAfterFadev", Render2dStuffAfterFade);
	INSTALL_HOOK(ctx, "_ZN4CHud4DrawEv", CHud_Draw);

	// RW Events
	INSTALL_HOOK(ctx, "_ZN5CGame20InitialiseRenderWareEv", CGame_InitialiseRenderWare);
}

}
