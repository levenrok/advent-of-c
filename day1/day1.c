#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF 256
#define MAX_REG_MATCHES 1

int main(void) {
    char buf[MAX_BUF];
    int current_rotation = 50;
    int password = 0;

    regex_t re_direction;
    regex_t re_rotation;
    regmatch_t match_direction[MAX_REG_MATCHES];
    regmatch_t match_rotation[MAX_REG_MATCHES];

    const char* direction_pattern = "^[A-Z]";
    const char* rotation_pattern = "[0-9]+";

    FILE* input = fopen("input.txt", "r");
    if (input == NULL) {
        fprintf(stderr, "\033[31mERROR:\033[0m cannot open input file!");
        goto err;
    }

    if (regcomp(&re_direction, direction_pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "\033[31mERROR:\033[0m regex compilation failed!");
        goto err;
    }

    if (regcomp(&re_rotation, rotation_pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "\033[31mERROR:\033[0m regex compilation failed!");
        goto err;
    }

    while (fgets(buf, MAX_BUF, input)) {
        int direction_result = regexec(&re_direction, buf, MAX_REG_MATCHES, match_direction, 0);
        int rotation_result = regexec(&re_rotation, buf, MAX_REG_MATCHES, match_rotation, 0);

        char direction = 0;
        int rotation = 0;

        if (!rotation_result) {
            int len = match_rotation[0].rm_eo - match_rotation[0].rm_so;
            char found_num_str[MAX_BUF];

            strncpy(found_num_str, buf + match_rotation[0].rm_so, len);
            found_num_str[len] = '\0';
            rotation = atoi(found_num_str);
        } else {
            fprintf(stderr, "\033[31mERROR:\033[0m regexec failed!");
            goto err;
        }

        if (!direction_result) {
            direction = buf[match_direction[0].rm_so];
        } else {
            fprintf(stderr, "\033[31mERROR:\033[0m regexec failed!");
            goto err;
        }

        switch (direction) {
            case 'R':
                current_rotation = (current_rotation + rotation) % 100;
                break;
            case 'L':
                current_rotation = (current_rotation - rotation % 100 + 100) % 100;
                break;
        }

        if (current_rotation == 0) {
            password++;
        }
    }

    printf("Password: %i\n", password);

    fclose(input);

    regfree(&re_direction);
    regfree(&re_rotation);

    return EXIT_SUCCESS;

err:
    if (input != NULL)
        fclose(input);

    regfree(&re_direction);
    regfree(&re_rotation);

    exit(EXIT_FAILURE);
}
