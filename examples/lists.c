#include "../mxc.h"

int main(int argc, char *argv[]) {
    int x = 4;
    int y = 8;
    int z = 12;
    int a = 16;

    list_t *l = list_init(sizeof(int), &x);
    list_append(l, &y);
    list_append(l, &z);
    list_insert(&l, 3, &a);
    list_del_tail(&l);

    for (int i = 0; i < list_length(l); i++) {
        printf("%d\n", *((int *)list_at(l, i)));
    }

    list_free(l);
}