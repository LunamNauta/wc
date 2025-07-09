#include <stdbool.h>
#include <stdio.h>

#include "wcvec.h"

int main(){
    float tmp;
    wcvec_t vec;
    wcvec_init(&vec, sizeof(float));
    wcvec_push_back(&vec, (tmp = 10, &tmp));
    wcvec_push_back(&vec, (tmp = 123.32, &tmp));
    wcvec_push_back(&vec, (tmp = 3.32, &tmp));
    wcvec_insert(&vec, 1, (tmp = 3.15, &tmp));
    wcvec_erase(&vec, 2);

    printf("%zu\n", vec.cap);

    wcit_t beg = wcvec_begin(&vec);
    wcit_t end = wcvec_end(&vec);
    /*
    for (wcit_t it = beg; wcit_neq(&it, &end); wcit_pre_inc(&it)){

    }
    */

    /*
    wcvec_iterator(float) it = wcvec_begin(vec);
    */
    /*
    wcvec_iterator(float) end = wcvec_end(vec);
    for (wcvec_iterator(float) it = wcvec_begin(vec); wciterator_ne(it, end); ){
        //printf("test");
        printf("%f\n", wciterator_cpy(it, float));
        //it.it.it.data = (char*)it.it.it.data + sizeof(float);
        wcvec_iterator_next((wcf_iterator_t*)&it);
        //wciterator_next(it);
        //printf("%f\n", *(float*)it.ref.ptr);
    }
    */

    /*
    printf("%zu\n", wcvec_size(&vec));
    size_t siz = wcvec_size(&vec);
    for (size_t a = 0; a < siz; a++){
        wcvec_at(&vec, a, &tmp);
        printf("%f\n", tmp);
        wcvec_erase(&vec, wcvec_size(&vec)-1);
    }
    */
}



