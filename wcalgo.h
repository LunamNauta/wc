#include <stdbool.h>

#include "wciterator.h"

typedef bool(*wcalgo_binarypred_t)(void*, void*);
typedef void(*wcalgo_binaryfunc_t)(void*, void*);
typedef bool(*wcalgo_unarypred_t)(void*);
typedef void(*wcalgo_unaryfunc_t)(void*);

// Non-Modifying
/*-----------------------------------------------------*/
bool wcalgo_none_of(wci_iterator_t beg, wci_iterator_t end, wcalgo_unarypred_t pred);
bool wcalgo_all_of(wci_iterator_t beg, wci_iterator_t end, wcalgo_unarypred_t pred);
bool wcalgo_any_of(wci_iterator_t beg, wci_iterator_t end, wcalgo_unarypred_t pred);

void wcalgo_for_each(wci_iterator_t beg, wci_iterator_t end, wcalgo_unaryfunc_t pred);
void wcalgo_for_each_n(wci_iterator_t beg, wci_iterator_t end, size_t n, wcalgo_unaryfunc_t pred);

size_t wcalgo_count(wci_iterator_t beg, wci_iterator_t end, void* val, wcalgo_binarypred_t comp);
size_t wcalgo_count_if(wci_iterator_t beg, wci_iterator_t end, wcalgo_unarypred_t pred);

wci_iterator_t wcalgo_find(wci_iterator_t beg, wci_iterator_t end, wcalgo_binarypred_t comp);
wci_iterator_t wcalgo_find_if(wci_iterator_t beg, wci_iterator_t end, wcalgo_unarypred_t pred);
wci_iterator_t wcalgo_find_if_not(wci_iterator_t beg, wci_iterator_t end, wcalgo_unarypred_t pred);

// Modifying
/*-----------------------------------------------------*/
wco_iterator_t wcalgo_copy(wci_iterator_t beg, wci_iterator_t end, wco_iterator_t obeg, wcalgo_binaryfunc_t copy);
wco_iterator_t wcalgo_copy_if(wci_iterator_t beg, wci_iterator_t end, wco_iterator_t obeg, wcalgo_unarypred_t pred, wcalgo_binaryfunc_t copy);
wco_iterator_t wcalgo_copy_n(wci_iterator_t beg, size_t n, wco_iterator_t obeg, wcalgo_binaryfunc_t copy);
wcbd_iterator_t wcalgo_copy_backward(wcbd_iterator_t beg, wcbd_iterator_t end, wcbd_iterator_t obeg, wcalgo_binaryfunc_t copy);

void wcalgo_fill(wcf_iterator_t beg, wcf_iterator_t end, void* val, wcalgo_binaryfunc_t copy);
void wcalgo_fill_n(wcf_iterator_t beg, size_t n, void* val, wcalgo_binaryfunc_t copy);

wco_iterator_t wcalgo_transform(wci_iterator_t beg, wci_iterator_t end, wco_iterator_t obeg, wcalgo_unaryfunc_t op);
wco_iterator_t wcalgo_transform_2(wci_iterator_t beg1, wci_iterator_t end1, wci_iterator_t beg2, wco_iterator_t obeg, wcalgo_binaryfunc_t op);
