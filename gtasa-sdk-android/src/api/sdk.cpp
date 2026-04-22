#include <sdk.hpp>
#include <internal/context.hpp>
#include <runtime/events_runtime.hpp>

namespace sdk {

/** --- Inicialização Global --- **/

SDK_API bool Init() {
	GlossInit(false);

	if(!internal::Context::Init())
		return false;

	return runtime::InitializeEvents();
}

} // namespace sdk