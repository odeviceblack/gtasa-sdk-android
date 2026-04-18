#pragma once

namespace sdk {

namespace internal { class Context; }

internal::Context& GetContext();

bool Init();

}