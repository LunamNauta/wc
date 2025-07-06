#ifndef WC_WCSOURCE_LOCATION_HEADER
#define WC_WCSOURCE_LOCATION_HEADER

#include <stdint.h>

typedef struct wcsource_location_t{
    uint_least32_t line;
    uint_least32_t column;
    const char* file_name;
    const char* function_name;
} wcsource_location_t;

#define wcsource_location_current() ((wcsource_location_t){__LINE__, 0, __FILE__, __func__})

#endif
