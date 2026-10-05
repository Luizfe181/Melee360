#ifndef MELEE360_RANDOM_PLATFORM_H
#define MELEE360_RANDOM_PLATFORM_H
/* Adapter for the integrated HSD core, not the full Dolphin runtime. */
#include <stddef.h>
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef signed char s8;
typedef int enum_t;
typedef void (*Event)(void);
typedef double f64;
typedef unsigned __int64 u64;
typedef signed __int64 s64;
typedef volatile float vf32;
typedef volatile double vf64;
#define ATTRIBUTE_ALIGN(value) __declspec(align(value))
#define AT_ADDRESS(value)
#define UNUSED
#define SDATA
#define DATA
#define WEAK
#define ARRAY_SIZE(value) (sizeof(value) / sizeof((value)[0]))
#define U8_MAX 0xFFu
#define U16_MAX 0xFFFFu
#define U32_MAX 0xFFFFFFFFu
#define S32_MAX 0x7FFFFFFF
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define ABS(x) ((x) < 0 ? -(x) : (x))
#define SQ(x) ((x) * (x))
#define SAT_ADD(a,b,max) (((a)+(b)>(max))?(max):(a)+(b))
#define SIGNF(x) ((x)>0.0f?1.0f:-1.0f)
#define RETURN_IF(cond) do { if(cond) return; } while(0)
#define FLT_EPSILON 1.00000001335e-10F
typedef signed int s32;
typedef float f32;
typedef unsigned int uintptr_t;
typedef int intptr_t;
typedef int ssize_t;
#define ATTRIBUTE_NORETURN __declspec(noreturn)
#define ASSERT_SIZE(type, size) typedef char MELEE360_JOIN(size_check_,__COUNTER__)[(sizeof(type) == (size)) ? 1 : -1]
#define MELEE360_JOIN_IMPL(a,b) a##b
#define MELEE360_JOIN(a,b) MELEE360_JOIN_IMPL(a,b)
#define STATIC_ASSERT(condition) typedef char MELEE360_JOIN(static_check_,__LINE__)[(condition) ? 1 : -1]
#define ASSERT_OFFSET(type, member, offset) STATIC_ASSERT(offsetof(type, member) == (offset))
typedef char check_u32_width[(sizeof(u32) == 4) ? 1 : -1];
typedef char check_pointer_width[(sizeof(void*) == 4) ? 1 : -1];
#ifndef __cplusplus
typedef unsigned char bool;
#define true 1
#define false 0
#define inline __inline
#endif
typedef bool (*Predicate)(void);
#endif
