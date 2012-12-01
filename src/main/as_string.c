#include "as_string.h"
#include <stdlib.h>
#include <string.h>


static const as_val AS_STRING_VAL;


/**
 * The `char *` passed as a parameter will be managed by the as_string going forward.
 * If you are going to continue to use the `char *`, then you probably should copy it first.
 */
as_string * as_string_new(char * s) {
    as_string * v = (as_string *) malloc(sizeof(as_string));
    as_string_init(v, s);
    return v;
}

extern inline int as_string_init(as_string * v, char * s) {
    v->_ = AS_STRING_VAL;
    v->value = s;
    v->len = 0;
    return 0;
}

int as_string_free(as_string * s) {
    if ( !s ) return 0;
    if ( s->value ) free(s->value);
    free(s);
    return 0;
}

char * as_string_tostring(const as_string * s) {
    if ( !s ) return NULL;
    return s->value;
}

size_t as_string_len(as_string * s) {
    if ( !s ) return 0;
    if ( !s->value ) return 0;
    if ( !s->len ) return (s->len = strlen(s->value));
    return s->len;
}


static uint32_t as_string_hash(as_string * s) {
    uint32_t hash = 0;
    int c;
    char * str = s->value;
    while ( (c = *str++) ) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

static int as_string_val_free(as_val * v) {
    return as_val_type(v) == AS_STRING ? as_string_free((as_string *) v) : 1;
}

static uint32_t as_string_val_hash(as_val * v) {
    return as_val_type(v) == AS_STRING ? as_string_hash((as_string *) v) : 0;
}

static char * as_string_val_tostring(as_val * v) {
    if ( as_val_type(v) != AS_STRING ) return NULL;
    as_string * s = (as_string *) v;
    size_t sl = as_string_len(s);
    size_t st = 2 + sl;
    char * str = (char *) malloc(sizeof(char) * st);
    bzero(str,st);
    strcpy(str, "\"");
    strcpy(str+1, s->value);
    strcpy(str+1+sl, "\"");
    return str;
}

static const as_val AS_STRING_VAL = {
    .type       = AS_STRING, 
    .size       = sizeof(as_string),
    .free       = as_string_val_free,
    .hash       = as_string_val_hash,
    .tostring   = as_string_val_tostring
};