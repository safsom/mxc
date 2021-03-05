#ifndef MXC_H
#define MXC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* Vector implementation */
typedef struct {
    size_t len;
    size_t type;
    size_t index;
    void *data;
} vector_t;

vector_t *vec_init(size_t type, size_t len) {
    void *data = malloc(type * len);
    if (data == NULL) {
        return NULL;
    }
    vector_t *vec = malloc(sizeof(vector_t));
    if (vec == NULL) {
        return NULL;
    }
    vec->len = len;
    vec->type = type;
    vec->index = 0;
    vec->data = data;
    return vec;
}

void *vec_at(vector_t *vec, size_t index) {
    if (index > vec->index) {
        return NULL;
    }
    return (vec->data + (index * vec->type));
}

int vec_append(vector_t *vec, void *v) {
    if (vec->index != vec->len) {
        memcpy(vec->data + (vec->index * vec->type), v, vec->type);
        vec->index += 1;
    } else {
        void *data_location = vec->data;
        data_location = realloc(vec->data, vec->len + (vec->len / 2));
        if (data_location == NULL) {
            return -1;
        }
        vec->data = data_location;
        vec->len += (vec->len / 2);
        memcpy(vec->data + (vec->index * vec->type), v, vec->type);
        vec->index += 1;
    }
    return 0;
}

int vec_append_char(vector_t *vec, char x) {
    if (vec->type != sizeof(char)) {
        return -1;
    }
    return vec_append(vec, &x);
}

int vec_append_short(vector_t *vec, short x) {
    if (vec->type != sizeof(short)){
        return -1;
    }
    return vec_append(vec, &x);
}

int vec_append_int(vector_t *vec, int x) {
    if (vec->type != sizeof(int)) {
        return -1;
    }
    return vec_append(vec, &x);
}

int vec_insert(vector_t *vec, size_t index, void *v) {
    if (index > vec->index) {
        return vec_append(vec, v);
    }
    void *starting_point = vec->data + (index * vec->type); 
    void *endpoint = starting_point + vec->type;
    if (memmove(endpoint, starting_point, vec->index - index) == NULL) {
        return -1;
    }
    if (memcpy(starting_point, v, vec->type) == NULL) {
        return -1;
    }
    return 0;
}

int vec_insert_char(vector_t *vec, size_t index, char x) {
    if (vec->type != sizeof(char)) {
        return -1;
    } 
    return vec_insert(vec, index, &x);
}

short vec_insert_short(vector_t *vec, size_t index, short x) {
    if (vec->type != sizeof(short)) {
        return -1;
    } 
    return vec_insert(vec, index, &x);
}

int vec_insert_int(vector_t *vec, size_t index, int x) {
    if (vec->type != sizeof(int)) {
        return -1;
    } 
    return vec_insert(vec, index, &x);
}

int vec_replace(vector_t *vec, size_t index, void *v) {
    if (index > vec->len) {
        return -1;
    } else if (index > vec->index) {
        memset(vec->data + (vec->type * index), 0, index - vec->index);
        vec->index = index;
    }
    void *replacement = memcpy(vec->data + (vec->type * index), v, vec->type);
    if (replacement == NULL) {
        return -1;
    }
    return 0;
}

int vec_replace_char(vector_t *vec, char x, char y) {
    if (vec->type != sizeof(char)) {
        return -1;
    }
    for (int i = 0; i < vec->index; i++) {
        if (*((char *)(vec->data + i)) == x) {
            vec_replace(vec, i, &y);
        }
    }
    return 0;
}

int vec_replace_short(vector_t *vec, short x, short y) {
    if (vec->type != sizeof(short)) {
        return -1;
    }
    for (int i = 0; i < vec->index; i++) {
        if (*((short *)(vec->data + (i * vec->type))) == x) {
            vec_replace(vec, i, &y);
        }
    }
    return 0;
}

int vec_replace_int(vector_t *vec, int x, int y) {
    if (vec->type != sizeof(int)) {
        return -1;
    }
    for (int i = 0; i < vec->index; i++) {
        if (*((int *)(vec->data + (i * vec->type))) == x) {
            vec_replace(vec, i, &y);
        }
    }
    return 0;
}

int vec_del_index(vector_t *vec, size_t index) {
    if (index > vec->len && index > vec->index) {
        return -1;
    }
    memset(vec->data + (index * vec->type), 0, vec->type);

    size_t n_after_index = vec->index - index - vec->type;

    if (memmove(vec->data + (index * vec->type), vec->data + (index * vec->type) + vec->type, n_after_index) != NULL) {
        vec->index -= 1;
        return 0;
    }
    return -1;
}

int vec_del_char(vector_t *vec, char x) {
    if (vec->type != sizeof(char)) {
        return -1;
    }
    for (int i = 0; i < vec->index; i++) {
        if (*((char *)(vec->data + i)) == x) {
            vec_del_index(vec, i);
        }
    }
    return 0;
}

int vec_del_short(vector_t *vec, short x) {
    if (vec->type != sizeof(short)) {
        return -1;
    }
    for (int i = 0; i < vec->index; i++) {
        if (*((short *)(vec->data + (i * vec->type))) == x) {
            vec_del_index(vec, i);
        }
    }
    return 0;
}

int vec_del_int(vector_t *vec, int x) {
    if (vec->type != sizeof(int)) {
        return -1;
    }
    for (int i = 0; i < vec->index; i++) {
        if (*((int *)(vec->data + (i * vec->type))) == x) {
            vec_del_index(vec, i);
        }
    }
    return 0;
}

int vec_del_tail(vector_t *vec) {
    if (vec->index == 0) {
        return -1;
    }
    memset(vec->data + (vec->index * vec->type) - vec->type, 0, vec->type);
    vec->index -= 1;
    return 0;
}

int vec_set(vector_t *vec, void *v, size_t n) {
    void *stat = memcpy(vec->data, v, n);
    if (stat == NULL) {
        return -1;
    }
    vec->len = n / vec->type;
    vec->index = n / vec->type;
    return 0;
}

void vec_clear(vector_t *vec) {
    vec->len = 1;
    memset(vec->data, 0, (vec->index * vec->type));
    vec->index = 0;
}

#define vec_len(x) x->index

void vec_free(vector_t *vec) {
    free(vec->data);
    free(vec);
}

/* String implementation */
typedef vector_t string_t;

string_t *str_init(char *str) {
    vector_t *vec = malloc(sizeof(vector_t));
    if (vec == NULL) {
        return NULL;
    }
    size_t len = strlen(str);
    vec = vec_init(sizeof(char), len);
    vec_set(vec, str, len);
    return vec;
}

int str_set_cstr(string_t *str, char *cstr) {
    return vec_set(str, cstr, strlen(cstr));
}

int str_set(string_t *dest, string_t *src) {
    void *data_location = dest->data;

    data_location = realloc(dest->data, src->len);
    if (data_location == NULL) {
        return -1;
    }
    dest->data = data_location;
    memcpy(dest->data, src->data, src->index);
    dest->index = src->index;
    dest->len = src->len;
    dest->type = src->type;
    return 0;
}

int str_join_cstr(string_t *dest, char *src) {
    size_t new_len = dest->len + strlen(src);
    void *data_location = dest->data;

    data_location = realloc(dest->data, new_len);
    if (data_location == NULL) {
        return -1;
    }
    dest->data = data_location;
    data_location = memcpy((dest->data + (dest->index * dest->type)), src, strlen(src));
    if (data_location == NULL) {
        return -1;
    }
    dest->len += strlen(src);
    dest->index += strlen(src);
    return 0;
}

int str_join(string_t *dest, string_t *src) {
    size_t new_len = dest->len + src->index;
    void *data_location = dest->data;

    data_location = realloc(dest->data, new_len);
    if (data_location == NULL) {
        return -1;
    }
    dest->data = data_location;
    data_location = memcpy((dest->data + (dest->index * dest->type)), src->data, (src->type * src->index));
    if (data_location == NULL) {
        return -1;
    }
    dest->len += src->len;
    dest->index += src->index;
    return 0;
}

int str_insert_cstr(string_t *str, size_t index, char *v) {
    if (index > str->index) {
        return str_join_cstr(str, v);
    }
    void *starting_point = str->data + (index * str->type); 
    void *endpoint = starting_point + strlen(v);
    if (memmove(endpoint, starting_point, str->index - index) == NULL) {
        return -1;
    }
    if (memcpy(starting_point, v, strlen(v)) == NULL) {
        return -1;
    }
    str->index += strlen(v);
    return 0;
}

int str_insert(string_t *dest, size_t index, string_t *src) {
    if (index > dest->index) {
        return str_join(dest, src);
    }
    void *starting_point = dest->data + (index * dest->type); 
    void *endpoint = starting_point + src->index;
    if (memmove(endpoint, starting_point, dest->index - index) == NULL) {
        return -1;
    }
    if (memcpy(starting_point, src->data, src->index) == NULL) {
        return -1;
    }
    dest->index += src->index;
    return 0;
}

int str_substr_cstr(string_t *haystack, char *needle) {
    char initial = needle[0];
    char *data = (char *)haystack->data;

    for (int i = 0; i < haystack->index; i++) {
        if (data[i] == initial) {
            if (memcmp((data + i), needle, strlen(needle)) == 0) {
                return i;
            }
        }
    }

    return -1;
}

int str_substr(string_t *haystack, string_t *needle) {
    char initial = *((char *)needle->data);
    char *data = (char *)haystack->data;

    for (int i = 0; i < haystack->index; i++) {
        if (data[i] == initial) {
            if (memcmp((data + i), needle->data, needle->index) == 0) {
                return i;
            }
        }
    }

    return -1;
}

char str_at(string_t *str, size_t index) {
    if (index > str->index) {
        return -1;
    }
    return *((char *)vec_at(str, index));
}

int str_replace_index(string_t *str, size_t index, char x) {
    return vec_replace(str, index, &x);
}

int str_replace_char(string_t *str, char x, char y) {
    return vec_replace_char(str, x, y);
}

int str_replace_cregion(string_t *str, size_t index, size_t n, char *v) {
    if (index > str->index) {
        return -1;
    } 
    void *status = memcpy((str->data + index), v, n);
    if (status == NULL) {
        return -1;
    }
    return 0;
}

int str_replace_region(string_t *dest, size_t index, size_t n, string_t *src) {
    if (index > dest->index) {
        return -1;
    } 
    void *status = memcpy((dest->data + index), src->data, n);
    if (status == NULL) {
        return -1;
    }
    return 0;
}

int str_replace_cstr(string_t *str, char *to_replace, char *replacement) {
    int index = str_substr_cstr(str, to_replace);
    if (index == -1) {
        return -1;
    }
    if (strlen(to_replace) == strlen(replacement)) {
        return str_replace_cregion(str, index, strlen(to_replace), replacement);
    } else {
        int to_add = strlen(replacement) - strlen(to_replace);
        void *tmp = realloc(str->data, str->len + to_add);
        if (tmp == NULL) {
            return -1;
        }
        str->data = tmp;
        void *endpoint = str->data + index + strlen(to_replace) + to_add;
        void *starting_point = endpoint - to_add;
        memmove(endpoint, starting_point, str->index - index);
        str_replace_cregion(str, index, strlen(replacement), replacement);
        str->index += to_add;
        return 0;
    }
}

int str_cmp_cstr(string_t *str, char *cstr) {
    return str->index - strlen(cstr);
}

int str_cmp(string_t *l, string_t *r) {
    return l->index - r->index;
}

const char *str_slice(string_t *str, size_t begin, size_t end) {
    if (end > str->index) {
        return NULL;
    }
    return str->data + begin;
}

size_t str_length(string_t *str) {
    return str->index;
}

static inline char *cstr(string_t *str) {
    return str->data;
}

void str_free(string_t *str) {
    vec_free(str);
}

#endif