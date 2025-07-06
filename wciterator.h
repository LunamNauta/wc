#include <stddef.h>

typedef struct wciterator_t{
    void* data;
    size_t dsiz;
} wciterator_t;

typedef wciterator_t wci_iterator_t;
typedef wciterator_t wco_iterator_t;
typedef wciterator_t wcf_iterator_t;
typedef wciterator_t wcbd_iterator_t;
typedef wciterator_t wcra_iterator_t;
