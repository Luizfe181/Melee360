/* Compile probe only: dolphin.h includes its own types.h using a quoted path,
 * so it bypasses the adapter include directory. Restore the XDK alignment
 * spelling after that SDK header has been processed. No decoder stub here. */
#include <Runtime/platform.h>
#include <dolphin.h>
#undef ATTRIBUTE_ALIGN
#define ATTRIBUTE_ALIGN(value) __declspec(align(value))
