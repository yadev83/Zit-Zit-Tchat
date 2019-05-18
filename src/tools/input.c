#include <stdio.h>
#include <stdlib.h>

#include "input.h"

void getMessage(String msg){
    printf("> ");
    fgets(msg, STRING_SIZE, stdin);
    int i = 0;
    while(msg[i] != '\n'){
        ++i;
    }
    msg[i] = '\0';
}
