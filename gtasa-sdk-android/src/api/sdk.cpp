#include "sdk.hpp"
#include "Gloss.h"

#include "context.hpp"
#include "bootstrap.hpp"

namespace sdk {

SDK_API internal::Context& GetContext() {
	static internal::Context ctx("libGTASA.so");
	return ctx;
}

bool IsContextValid() {
	return static_cast<bool>(GetContext());
}

SDK_API bool Init() {
	GlossInit(false);

	if(!IsContextValid())
		return false;

	runtime::InitializeEvents();
	return true;
}

}