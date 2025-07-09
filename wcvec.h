#ifndef WC_WCVEC_HEADER
#define WC_WCVEC_HEADER

#include <stdbool.h>
#include <stddef.h>

#include "wciterator.h"

// Types
/*--------------------------------------------------------*/
typedef struct wcvec_t{
    void* data;
    size_t cap;
    size_t siz;
    size_t dsiz;
} wcvec_t;

// Constructor / Destructor
/*--------------------------------------------------------*/
int wcvec_init(wcvec_t* vec, size_t dsiz);
void wcvec_free(wcvec_t* vec);

// Element Access
/*--------------------------------------------------------*/
void wcvec_get(wcvec_t* vec, size_t pos, void* out);
int wcvec_at(wcvec_t* vec, size_t pos, void* out);
void wcvec_front(wcvec_t* vec, void* out);
void wcvec_back(wcvec_t* vec, void* out);
void* wcvec_get_ref(wcvec_t* vec, size_t pos);
void* wcvec_at_ref(wcvec_t* vec, size_t pos);
void* wcvec_front_ref(wcvec_t* vec);
void* wcvec_back_ref(wcvec_t* vec);
void* wcvec_data(wcvec_t* vec);

// Capacity
/*--------------------------------------------------------*/
bool wcvec_empty(wcvec_t* vec);
size_t wcvec_size(wcvec_t* vec);
int wcvec_reserve(wcvec_t* vec, size_t cap);
size_t wcvec_capacity(wcvec_t* vec);
int wcvec_shrink_to_fit(wcvec_t* vec);

// Modifiers
/*--------------------------------------------------------*/
void wcvec_clear(wcvec_t* vec);
int wcvec_insert(wcvec_t* vec, size_t pos, void* in);
int wcvec_erase(wcvec_t* vec, size_t pos);
int wcvec_push_back(wcvec_t* vec, void* in);
void wcvec_pop_back(wcvec_t* vec, void* out);
int wcvec_resize(wcvec_t* vec, size_t siz);

// Iterators
/*--------------------------------------------------------*/
wcit_t wcvec_begin(const wcvec_t* vec);
wcit_t wcvec_end(const wcvec_t* vec);

#endif
