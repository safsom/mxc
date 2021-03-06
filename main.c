#include "mxc.h"

int main(int argc, char *argv[]) {
    char name[5] = "safal";
    stack_t *reversed = stack_init(sizeof(char));

    for (int i = 0; i < 5; i++) {
        stack_pushchar(reversed, name[i]);
    }
    for (int i = 0; i < 5; i++) {
        printf("%c", stack_popchar(reversed));
    }

    stack_free(reversed);
    return 0;
}