#include "mxc.h"

int main(int argc, char *argv[]) {
    string_t *str = str_init("Safal Aryal");
    
    puts(cstr(str));

    str_free(str);
    return 0;
}