#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"

unsigned int fstring_length(fixstring s) {
    unsigned int l = 0;
    while (l < FIXSTRING_MAX){
        if (s[l] == '\0'){
            break;
        }
        l = l + 1;
    }
    return l;   
}

bool fstring_eq(fixstring s1, fixstring s2) {
    bool igual = true;
    if (fstring_length(s1) != fstring_length(s2)){
        return false;
    }
    
    for (int i = 0; i < FIXSTRING_MAX; i++){
        if (s1[i] != s2[i]){
            igual = false;
            break;
        }
    }
    return igual;
}

bool fstring_less_eq(fixstring s1, fixstring s2) {
    unsigned int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]){
        i++;
    }
    return s1[i] <= s2[i];
}

