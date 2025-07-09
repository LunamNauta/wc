#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "wcvec.h"

#define WCVEC_BASE_CAP 16

// Constructor / Destructor
/*--------------------------------------------------------*/
int wcvec_init(wcvec_t* vec, size_t dsiz){
    vec->data = malloc(WCVEC_BASE_CAP*dsiz);
    if (!vec->data) return -1;
    vec->cap = WCVEC_BASE_CAP;
    vec->dsiz = dsiz;
    return 0;
}
void wcvec_free(wcvec_t* vec){
    free(vec->data);
}

// Element Access
/*--------------------------------------------------------*/
void wcvec_get(wcvec_t* vec, size_t pos, void* out){
    memcpy(out, (char*)vec->data+pos*vec->dsiz, vec->dsiz);
}
int wcvec_at(wcvec_t* vec, size_t pos, void* out){
    if (pos >= vec->siz) return -1;
    wcvec_get(vec, pos, out);
    return 0;
}
void wcvec_front(wcvec_t* vec, void* out){
    memcpy(out, vec->data, vec->dsiz);
}
void wcvec_back(wcvec_t* vec, void* out){
    memcpy(out, (char*)vec->data+(vec->siz-1)*vec->dsiz, vec->dsiz);
}
void* wcvec_get_ref(wcvec_t* vec, size_t pos){
    return (char*)vec->data+pos*vec->dsiz;
}
void* wcvec_at_ref(wcvec_t* vec, size_t pos){
    if (pos >= vec->siz) return NULL;
    return (char*)vec->data+pos*vec->dsiz;
}
void* wcvec_front_ref(wcvec_t* vec){
    return vec->data;
}
void* wcvec_back_ref(wcvec_t* vec){
    return (char*)vec->data+(vec->siz-1)*vec->dsiz;
}
void* wcvec_data(wcvec_t* vec){
    return vec->data;
}

// Capacity
/*--------------------------------------------------------*/
bool wcvec_empty(wcvec_t* vec){
    return vec->siz == 0;
}
size_t wcvec_size(wcvec_t* vec){
    return vec->siz;
}
int wcvec_reserve(wcvec_t* vec, size_t cap){
    if (vec->cap >= cap) return 0;
    void* tmp = realloc(vec->data, cap*vec->dsiz);
    if (!tmp) return -1;
    vec->data = tmp;
    vec->cap = cap;
    return 0;
}
size_t wcvec_capacity(wcvec_t* vec){
    return vec->cap;
}
int wcvec_shrink_to_fit(wcvec_t* vec){
    if (vec->cap == vec->siz) return 0;
    void* tmp = realloc(vec->data, vec->siz*vec->dsiz);
    if (!tmp) return -1;
    vec->data = tmp;
    vec->cap = vec->siz;
    return 0;
}

// Modifiers
/*--------------------------------------------------------*/
void wcvec_clear(wcvec_t* vec){
    vec->siz = 0;
}
int wcvec_insert(wcvec_t* vec, size_t pos, void* in){
    if (vec->siz+1 > vec->cap){
        int tmp = wcvec_reserve(vec, vec->siz*3/2);
        if (tmp < 0) return tmp;
    }
    for (size_t a = 0; a < vec->siz - pos; a++){
        memcpy((char*)vec->data+(vec->siz-a)*vec->dsiz, (char*)vec->data+(vec->siz-a-1)*vec->dsiz, vec->dsiz);
    }
    memcpy((char*)vec->data+pos*vec->dsiz, in, vec->dsiz);
    vec->siz++;
    return 0;
}
int wcvec_erase(wcvec_t* vec, size_t pos){
    if (pos >= vec->siz) return -1;
    for (size_t a = pos; a < vec->siz-1; a++){
        memcpy((char*)vec->data+a*vec->dsiz, (char*)vec->data+(a+1)*vec->dsiz, vec->dsiz);
    }
    vec->siz--;
    return 0;
}
int wcvec_push_back(wcvec_t* vec, void* in){
    if (vec->siz+1 > vec->cap){
        int tmp = wcvec_reserve(vec, vec->siz*3/2);
        if (tmp < 0) return tmp;
    }
    memcpy((char*)vec->data+vec->siz*vec->dsiz, in, vec->dsiz);
    vec->siz++;
    return 0;

}
void wcvec_pop_back(wcvec_t* vec, void* out){
    if (out) memcpy(out, (char*)vec->data+(vec->siz-1)*vec->dsiz, vec->dsiz);
}
int wcvec_resize(wcvec_t* vec, size_t siz){
    if (siz <= vec->cap){
        vec->siz = siz;
        return 0;
    }
    int tmp = wcvec_reserve(vec, siz);
    if (tmp < 0) return tmp;
    vec->siz = siz;
    return 0;
}

// Iterators
/*--------------------------------------------------------*/
void wcvec_it_advance(wcit_t* it, ssize_t n){
    it->data = (char*)it->data+(ssize_t)it->dsiz*n;
}
wcit_t wcvec_it_next(const wcit_t* it, size_t n){
    wcit_t tmp = *it;
    tmp.data = (char*)tmp.data+tmp.dsiz*n;
    return tmp;
}
wcit_t wcvec_it_prev(const wcit_t* it, size_t n){
    wcit_t tmp = *it;
    tmp.data = (char*)tmp.data-tmp.dsiz*n;
    return tmp;
}
void wcvec_it_inc(wcit_t* it){
    it->data = (char*)it->data+it->dsiz;
}
void wcvec_it_dec(wcit_t* it){
    it->data = (char*)it->data-it->dsiz;
}
size_t wcvec_it_dist(const wcit_t* it1, const wcit_t* it2){
    if (it1 > it2) return it1 - it2;
    return it2 - it1;
}
wcit_vtable_t wcvec_it_vtable = {
    wcvec_it_advance,
    wcvec_it_next,
    wcvec_it_prev,
    wcvec_it_inc,
    wcvec_it_dec,
    wcvec_it_dist
};
enum wcit_tag_t wcvec_it_tags = WCIT_ADVANCE_TAG | WCIT_NEXT_TAG | WCIT_PREV_TAG | WCIT_INC_TAG | WCIT_DEC_TAG;

wcit_t wcvec_begin(const wcvec_t* vec){
    return (wcit_t){vec->data, vec->dsiz, &wcvec_it_vtable, wcvec_it_tags};
}
wcit_t wcvec_end(const wcvec_t* vec){
    return (wcit_t){(char*)vec->data+vec->siz*vec->dsiz, vec->dsiz, &wcvec_it_vtable, wcvec_it_tags};
}
