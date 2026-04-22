#pragma once

/** --- Utilitários de Plataforma / ABI --- **/

#define SDK_API __attribute__((visibility("default")))

#if defined(__aarch64__)
	#define ARCH_SELECT(a, b) (a)
#elif defined(__arm__)
	#define ARCH_SELECT(a, b) (b)
#else
	#error "Unsupported architecture"
#endif

/** --- Helpers de Validação --- **/

#define VALIDATE_SIZE(type, expected) \
	static_assert(sizeof(type) == (expected), "Size mismatch: " #type " must be " #expected " bytes")
