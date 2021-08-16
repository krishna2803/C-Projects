/*
MIT License

Copyright (c) 2021 krishna2803

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef DICTIONARY_H_INCLUDED
#define DICTIONARY_H_INCLUDED

// maximum string size a `key` can store
#ifndef DICT_MAX_STRING_SIZE
    #define DICT_MAX_STRING_SIZE 32 // defaults to 32 should be enough for most of the tasks
#endif

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

/**
 * @brief A structure to store keys and integer values
 * @param keys pointer to store keys
 * @param values pointer to store integer values
 * @param size size of dictionary (current number of elements)
 * @param heap_size dynamic size of dictionary
 */
typedef struct dictionary {
    /*@{*/
    char **keys;
    int   *values;
    unsigned int size;
    unsigned int heap_size;
    /*@}*/
} dictionary;

/**
 * @brief creates the dictionary
 * @param init_size the default size of dictionary i.e. number of keys it can store
 */
dictionary dictionary_create(unsigned int init_size) {
    return (dictionary) {
        malloc(init_size*DICT_MAX_STRING_SIZE), // assuming that each string key appended will have size LESS THAN DICT_MAX_STRING_SIZE
        malloc(4*init_size),
        0,
        init_size
    };
}

/**
 * @brief Add a key to the end of a dictionary
 * if the `size` extends or equates `heap_size` then reallocates memory to the twice
 * so that it'll be called less often to improve performance
 * 
 * @param dict dictionary to add key into
 * @param key key to be added
 * @param value integer value of the key
 */
void dictionary_push(dictionary *dict, char* key, int value) {
    if (strlen(key) > DICT_MAX_STRING_SIZE) return;

    if (dict->size >= dict->heap_size) {
        dict->keys   = (char**)         realloc(dict->keys, (dict->heap_size*2*DICT_MAX_STRING_SIZE));
        dict->values = (unsigned int*)  realloc(dict->values, sizeof(int)*(dict->heap_size*=2));
    }

    dict->keys[dict->size]   = key;
    dict->values[dict->size] = value;
    dict->size++;
}

/**
 * @brief Add a key to a dictionary
 * 
 * @param dict dictionary to add key into
 * @param index index of the key to be added int the dictionary
 * @param key key to be added
 * @param value integer value of the key
 */
void dictionary_add(dictionary *dict, unsigned int index, char* key, int value) {
    if (index >= dict->size || strlen(key) > DICT_MAX_STRING_SIZE) return;
    dictionary_push(dict, '\0', 0);
    for(unsigned int i = dict->size; i > index; i--) {
        dict->keys[i]   = dict->keys[i-1];
        dict->values[i] = dict->values[i-1];
    }
    dict->keys[index]   = key;
    dict->values[index] = value;
}

/** 
 * @brief Find for a key in the dict
 * 
 * @param dictionary dictionary to search into
 * @param key string to be searched for
 * @return index of the first string similar to key found in the dictionary
 * if no similar string is found, return -1
 */
int dictionary_find(dictionary dict, char* key) {
    for (unsigned int i=0; i<dict.size; i++) 
        if (!strcmp(dict.keys[i], key)) return i;
    return -1;
}

/**
 * @brief Get the value of key by searching it's string value
 * 
 * @param dict dictionary to get the value of key from
 * @param key string to be searched for
 * @return value of the first string similar to key found in the dictionary
 * if no similar string is found, return 0
*/
int dictionary_get_key_value(dictionary dict, char* key) {
    for (unsigned int i=0; i<dict.size; i++) 
        if (!strcmp(dict.keys[i], key)) return dict.values[i];
    return 0;
}
/**
 * @brief Print the dictionary to stdout.
 * 
 * @param dict dict to be printed
*/
void dictionary_print(dictionary dict) {
    printf("{\n");
    for (unsigned int i=0; i < dict.size; i++) {
        printf("  '%s': %d\n", dict.keys[dict.size-1], dict.values[dict.size-1]);
    }
    printf("}\n");
}

/**
 * @brief Remove and element by index from the dictionary
 * 
 * @param dict dict to remove the element from 
 * @param index index to the element to be removed
*/
void dictionary_remove_index(dictionary* dict, unsigned int index) {
    if (index >= dict->size) return;
    for(int i = index; i < dict->size-1; i++) {
        dict->values[i] = dict->values[i+1];
        dict->keys[i]   = dict->keys[i+1];
    }
    dict->values[dict->size-1] = 0;
    dict->keys[dict->size-1]   = 0;
}

/**
 * @brief Free the allocated memory and reset size and heap_size
 * 
 * @param dict dict to be destroyed
*/
void dictionary_destroy(dictionary *dict) {
    free(dict->keys);
    free(dict->values);

    dict->heap_size = 0;
    dict->size = 0;
}


#endif // DICTIONARY_H_INCLUDED
