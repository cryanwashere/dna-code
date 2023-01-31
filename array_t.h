#include <stdlib.h>
#include <string.h>

typedef struct {
    char **array_ptr;
    int array_len;
    int string_len;
} array_t;

array_t*
array_string_new(int array_len, int string_len)
{
    int i;
    char **array_ptr = (char **) malloc(array_len * sizeof(char**));

    for (i = 0; i < array_len; i++) {
        array_ptr[i] = (char*) malloc(string_len * sizeof(char));
    }

    array_t *array = (array_t*) malloc(sizeof(array_t*));
    array->array_ptr = array_ptr;
    array->array_len = array_len;
    array->string_len = string_len;
    
    return array;
}
int 
array_string_set(array_t *array, int index, char *string)
{
    strncpy(array->array_ptr[index], string, array->string_len);
    return 0;
}
char* 
array_string_get(array_t *array, int index) {
    return array->array_ptr[index];
}
int 
array_string_len(array_t *array)
{
    return array->array_len;
}
int 
array_string_free(array_t *array)
{
    int i;
    for(i = 0; i < array->array_len; i++) {
        free(array->array_ptr[i]);
    }
    free(array->array_ptr);
    return 0;
}