#ifndef WC_WCITERATOR_HEADER
#define WC_WCITERATOR_HEADER

#include <stdbool.h>
#include <stddef.h>
#include <assert.h>

#include <unistd.h>

enum wcit_type_t{
    WCIT_INPUT_TAG = 1,
    WCIT_OUTPUT_TAG = 2,
    WCIT_FORWARD_TAG = 4,
    WCIT_BIDIRECTIONAL_TAG = 8,
    WCIT_RANDOM_ACCESS_TAG = 16,
    WCIT_CONTIGUOUS_TAG = 32
};

enum wcit_tag_t{
    WCIT_ADVANCE_TAG = 1,
    WCIT_NEXT_TAG = 4,
    WCIT_PREV_TAG = 8,
    WCIT_INC_TAG = 16,
    WCIT_DEC_TAG = 32
};

struct wcit_t;

typedef struct wcit_vtable_t{
    void (*advance)(struct wcit_t*, ssize_t);
    struct wcit_t (*next)(const struct wcit_t*, size_t);
    struct wcit_t (*prev)(const struct wcit_t*, size_t);
    void (*inc)(struct wcit_t*);
    void (*dec)(struct wcit_t*);
    size_t (*dist)(const struct wcit_t*, const struct wcit_t*);
} wcit_vtable_t;

typedef struct wcit_t{
    void* data;
    size_t dsiz;
    wcit_vtable_t* vtable;
    enum wcit_tag_t tags;
} wcit_t;

void wcit_advnace(wcit_t* it, ssize_t n); //assert(it->tags & WCIT_ADVANCE_TAG); it->vtable->advance(it, n);
wcit_t wcit_next(const wcit_t* it, size_t n); //assert(it->tags & WCIT_NEXT_TAG); return it->vtable->next(it, n);
wcit_t wcit_prev(const wcit_t* it, size_t n); //assert(it->tags & WCIT_PREV_TAG); return it->vtable->prev(it, n);
wcit_t wcit_pre_inc(wcit_t* it); //assert(it->tags & WCIT_INC_TAG); wcit_t tmp = it; it->vtable->inc(it); return tmp;
wcit_t wcit_pre_dec(wcit_t* it); //assert(it->tags & WCIT_DEC_TAG); wcit_t tmp = it; it->vtable->dec(it); return tmp;
wcit_t wcit_post_inc(wcit_t* it); //assert(it->tags & WCIT_INC_TAG); it->vtable->inc(it); return it;
wcit_t wcit_post_dec(wcit_t* it); //assert(it->tags & WCIT_DEC_TAG); it->vtable->dec(it); return it;

bool wcit_eq(wcit_t* it1, wcit_t* it2);
bool wcit_neq(wcit_t* it1, wcit_t* it2);

size_t wcit_distance(const wcit_t* it1, const wcit_t* it2); //return it->vtable->dist(it1, it2);

#define wcit_ref(it) (it->data)
#define wcit_cpy(it, out) (memcpy(out, it->data, it->dsiz))

#endif
