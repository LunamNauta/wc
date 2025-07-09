#include "wciterator.h"

void wcit_advnace(wcit_t* it, ssize_t n){
    assert(it->tags & WCIT_ADVANCE_TAG); 
    it->vtable->advance(it, n);
}
wcit_t wcit_next(const wcit_t* it, size_t n){
    assert(it->tags & WCIT_NEXT_TAG);
    return it->vtable->next(it, n);
}
wcit_t wcit_prev(const wcit_t* it, size_t n){
    assert(it->tags & WCIT_PREV_TAG);
    return it->vtable->prev(it, n);
}
wcit_t wcit_pre_inc(wcit_t* it){
    assert(it->tags & WCIT_INC_TAG);
    wcit_t tmp = *it; 
    it->vtable->inc(it); 
    return tmp;
}
wcit_t wcit_pre_dec(wcit_t* it){
    assert(it->tags & WCIT_DEC_TAG);
    wcit_t tmp = *it;
    it->vtable->dec(it);
    return tmp;
}
wcit_t wcit_post_inc(wcit_t* it){
    assert(it->tags & WCIT_INC_TAG);
    it->vtable->inc(it);
    return *it;
}
wcit_t wcit_post_dec(wcit_t* it){
    assert(it->tags & WCIT_DEC_TAG);
    it->vtable->dec(it);
    return *it;
}

bool wcit_eq(wcit_t* it1, wcit_t* it2){
    return it1->data == it2->data;
}
bool wcit_neq(wcit_t* it1, wcit_t* it2){
    return it1->data != it2->data;
}

size_t wcit_distance(const wcit_t* it1, const wcit_t* it2){
    return it1->vtable->dist(it1, it2);
}
