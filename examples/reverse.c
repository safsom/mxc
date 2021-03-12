#include "../mxc.h"

int main(int argc, char *argv[]) {
    string_t *input = str_init("tom: 80, hanks: 90");

    stack_t *reversed = stack_init(sizeof(char));
    int slice = str_substr_cstr(input, "tom");
    
    int len = str_length(input);
    for (int i = slice; i < len - (len - 3); i++) {
        stack_pushchar(reversed, str_at(input, i));
    }
    for (int i = slice; i < len - (len - 3); i++) {
        putc(stack_popchar(reversed), stdout);
    }
    putc('\n', stdout);

    str_free(input);
    stack_free(reversed);
    return 0;
}
