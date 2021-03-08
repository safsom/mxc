#include "mxc.h"

int main(int argc, char *argv[]) {
    map_t *map = map_init(sizeof(int));
    int x = 5;
    map_insert_s(map, "Safal", &x);
    printf("%d\n", *((int *)map_at_s(map, "Safal")));
    int y = x + 3;
    map_insert_s(map, "Somil", &y);
    printf("%d\n", *((int *)map_at_s(map, "Somil")));
    
    
    vector_t *vec = vec_init(sizeof(int), 3);
    vec_append(vec, &x);
    printf("%d\n", *((int *)vec_at(vec, 0)));
    
    vec_free(vec);
    map_free(map);
    return 0;
}
