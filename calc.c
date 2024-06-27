#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPRESSION_LENGTH 1024

int main(int argc, char *argv[]) {
    int option;
    bool use_advanced_math = true;

    while ((option = getopt(argc, argv, "hm")) != -1) {
        switch (option) {
        case 'm': use_advanced_math = false; break;
        case 'h': printf(USAGE, argv[0]); return 0;
        case '?': break;
        }
    }

    while (true) {
        char expression[MAX_EXPRESSION_LENGTH];
        char *token;
        bool has_error = false;
        double value;

        fprintf(stderr, "> ");
        if (fgets(expression, sizeof(expression), stdin) == NULL) {
            return 0;
        }

        expression[strcspn(expression, "\n")] = '\0';

        token = strtok(expression, " ");

        while (token != NULL && !has_error) {
            int is_binary = 0, is_unary = 0;
            size_t token_length = strlen(token);

            for (int i = 0; i < 256; i++) {
                if (binary_operators[i] != NULL && i == (unsigned char) *token
                    && token_length == 1) {
                    is_binary = 1;
                    break;
                }
            }

            for (int i = 0; i < 256; i++) {
                if (my_unary_operators[i] != NULL && i == (unsigned char) *token
                    && token_length == 1) {
                    is_unary = 1;
                    break;
                }
            }

            if (!parse_double(token, &value) && is_binary == 0 && is_unary == 0) {
                if (token_length == 1) {
                    fprintf(stderr, ERROR_BAD_CHAR, *token);
                } else {
                    fprintf(stderr, ERROR_BAD_STRING, token);
                }
                has_error = true;
            }

            if (parse_double(token, &value)) {
                if (!stack_push(value)) {
                    has_error = true;
                }
            }

            if (is_binary == 1) {
                if (!apply_binary_operator(binary_operators[(unsigned char) *token])) {
                    fprintf(stderr, ERROR_BINARY_OPERATOR);
                    has_error = true;
                }
            }

            if (is_unary == 1) {
                if ((use_advanced_math
                        && !apply_unary_operator(my_unary_operators[(unsigned char) *token]))
                    || (!use_advanced_math
                        && !apply_unary_operator(libm_unary_operators[(unsigned char) *token]))) {
                    fprintf(stderr, ERROR_UNARY_OPERATOR);
                    has_error = true;
                }
            }

            token = strtok(NULL, " ");
        }

        if (!has_error) {
            stack_print();
            putchar('\n');
        }

        stack_clear();
    }

    return 0;
}
