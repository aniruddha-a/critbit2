
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include "critbit.h"

/* Given the string in a lib, get the data associated with it
 * s - string given by critbit 
 * v - our data pointer 
 */
#define CB_GET_DATA_STR(s,v)  memcpy(&v, s+strlen(s)+1, sizeof(void*))
int cbk (const char *e, void *p)
{
    int *v;
    CB_GET_DATA_STR(e, v);
    printf ("\n ToFree PTRs: p [%s], %p, =%d=", e, (v) , *v);
    free(v);
    return 1;
}

int main()
{
    critbit0_tree tree = { 0 };
    
    int *v;
    int i;

    static const char *elems[] =
       { "10.10.1.0", "10.10.255.0", "10.10.12.0", NULL};

    for (i = 0; elems[i]; ++i) {
        v = malloc(sizeof(int));
        *v = 10+strlen(elems[i]);
        printf ("\n Insert %s = %d at %p\n", elems[i],  *v, v );
	critbit0_insert(&tree, elems[i], v);
    }

    int x;
    uintptr_t p;

    for (i = 0; elems[i]; ++i) {
        if (critbit0_contains(&tree, elems[i], &p)) {
            x = *(int*)p;
            printf ("\n Contains: %s %"PRIxPTR", > %d\n",elems[i], p, x);
        }
    }

#if 0 
    for (i = 0; elems[i]; ++i) {
        if (critbit0_delete(&tree, elems[i], &p)) {
            x = *(int*)p;
            printf ("\n Deleted: %s %"PRIxPTR", > %d\n",elems[i], p, x);
            free((int*)p);
        }
    }
#endif 

    critbit0_allprefixed(&tree, "", cbk, NULL); // to free all nodes 
    critbit0_clear(&tree);

    printf ("\n\n");
    return 0;

}
