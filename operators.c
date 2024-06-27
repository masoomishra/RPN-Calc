#include "operators.h"

#include "stack.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool apply_binary_operator(binary_operator_fn op) {
    if (stack_size < 2) {
        return false;
    } else {
        double rhs;
        double lhs;

        if (!stack_pop(&rhs) || !stack_pop(&lhs)) {
            return false;
        }

        double result = op(lhs, rhs);

        if (!stack_push(result)) {
            return false;
        }
        return true;
    }
}

bool apply_unary_operator(unary_operator_fn op) {
    if (stack_size < 1) {
        return false;
    }
    double x;
    if (!stack_pop(&x)) {
        return false;
    }
    double result = op(x);
    if (!stack_push(result)) {
        return false;
    }
    return true;
}

double operator_add(double lhs, double rhs) {
    double result = lhs + rhs;
    return result;
}

double operator_sub(double lhs, double rhs) {
    double result = lhs - rhs;
    return result;
}

double operator_mul(double lhs, double rhs) {
    double result = lhs * rhs;
    return result;
}

double operator_div(double lhs, double rhs) {
    if (rhs == 0) {
        return nan("");
    }
    double result = lhs / rhs;
    return result;
}

//Function by Professor Veenstra asgn5 pg 6-7

bool parse_double(const char *s, double *d) {
    char *endptr;
    double result = strtod(s, &endptr);

    if (endptr != s) {
        *d = result;
        return true;
    } else {
        return false;
    }
}
