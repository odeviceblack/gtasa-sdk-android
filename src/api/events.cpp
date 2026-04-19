#include "events.hpp"

namespace sdk {
	// Game Events
	SDK_API Event<> Events::initGameEvent;
	SDK_API Event<> Events::restartGameEvent;
	SDK_API Event<> Events::gameProcessEvent;
	
	// Draw Events
	SDK_API Event<> Events::drawingEvent;
	SDK_API Event<> Events::drawAfterFadeEvent;
	SDK_API Event<> Events::drawHudEvent;
	
	// RW Events
	SDK_API Event<> Events::initRwEvent;
}