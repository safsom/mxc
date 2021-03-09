#include "mxc.h"

int main(int argc, char *argv[]) {
    string_t *input = str_init("Safal: 80, Somil: 90");
    int slice;

    stack_t *reversed = stack_init(sizeof(char));
    slice = str_substr_cstr(input, "Safal");
    
    int len = str_length(input);
    for (int i = slice; i < len - (len - 5); i++) {
        stack_pushchar(reversed, str_at(input, i));
    }
    for (int i = slice; i < len - (len - 5); i++) {
        printf("%c", stack_popchar(reversed));
    }

    str_free(input);
    stack_free(reversed);
    return 0;
}
