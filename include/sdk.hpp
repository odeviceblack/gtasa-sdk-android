#pragma once

#define SDK_API __attribute__((visibility("default")))

namespace sdk::internal { class Context; }

namespace sdk {

SDK_API internal::Context& GetContext();

SDK_API bool Init();

}