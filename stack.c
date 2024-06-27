//stack.c

#include "stack.h"

#include "messages.h"

#include <stdbool.h>
#include <stdio.h>

#define STACK_CAPACITY 64

static int top = -1;
double stack[STACK_CAPACITY] = { 0 };
int stack_size = 0;

bool stack_push(double item) {
    if (stack_size >= STACK_CAPACITY) {
        fprintf(stderr, ERROR_NO_SPACE, item);
        return false;
    } else {
        stack_size++;
        top++;
        stack[top] = item;
        return true;
    }
}

bool stack_pop(double *item) {
    if (stack_size == 0) {
        return false;
    } else {
        *item = stack[top];
        top--;
        stack_size--;
        return true;
    }
}

bool stack_peek(double *item) {
    if (stack_size == 0) {
        return false;
    } else {
        *item = stack[top];
        return true;
    }
}

void stack_clear(void) {
    stack_size = 0;
    top = -1;
}

//function by Professor Veenstra asgn5 pg 8

void stack_print(void) {
    if (stack_size == 0) {
        return;
    }

    printf("%.10f", stack[0]);
    for (int i = 1; i < stack_size; i++) {
        printf(" %.10f", stack[i]);
    }
}
