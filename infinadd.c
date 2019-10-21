/*
** EPITECH PROJECT, 2019
** CPool_infinadd_2019
** File description:
** The file contain the main functions of the program.
*/

#include <stdio.h> // DEBUG
#include <unistd.h>
#include <stdlib.h>
#include "my.h"

char *create_res_str(char const *str1, char const *str2)
{
    int lenstr1 = my_strlen(str1);
    int lenstr2 = my_strlen(str2);
    int size = lenstr1;
    char *res;

    if (lenstr2 > lenstr1)
        size = lenstr2;
    res = malloc(sizeof(char) * (size + 3));
    if (res == NULL)
        return (NULL);
    return (res);
}

int is_pos_num(char c)
{
    if (c <= '9' && c >= '1')
        return (1);
    return (0);
}

int longest(char const *str1, char const *str2)
{
    if (my_strlen(str1) > my_strlen(str2)) {
        if (str1[0] != '-')
            return (my_strlen(str1) - 1);
        else
            return (my_strlen(str1) - 2);
    } else {
        if (str2[0] != '-')
            return (my_strlen(str2) - 1);
        else
            return (my_strlen(str2) - 2);
    }
}

void apply_carried_number(char *res, int *carriedNum, int *new_cn)
{
    if (*carriedNum != 0 && (*new_cn != 1 || *carriedNum > 1)) {
        if (*res + 1 <= '9') {
            *res += 1;
            (*carriedNum)--;
        } else {
            *res = '0';
        }
    }
}

void apply_symbol(char *res_symbol, char *str1, char *str2)
{/*
    if (str1[0] == '-' && str2[0] != '-') {
        if (my_strlen(str1[0]) - 1 > my_strlen(str2[0]))
    } else if (str2[0] == '-' && str1[0] != '-') {

    }*/
    *res_symbol = '+';
}

void treat_digit(char *res, char const *d1, char const *d2, int *carriedNum)
{
    int new_carriedNb = 0;

    if (!is_pos_num(*d1)) {
        *res = *d2;
    } else if (!is_pos_num(*d2)) {
        *res = *d1;
    } else {
        if (*d1 + (*d2 - '0') <= '9') {
            *res = *d1 + (*d2 - '0');
        } else {
            *carriedNum += 1;
            new_carriedNb = 1;
            *res = (*d1 + (*d2 - '0')) - 10;
        }
    }
    apply_carried_number(res, carriedNum, &new_carriedNb);
}

void calcul_add(char *res, char *str1, char *str2)
{
    int carriedNum = 0;
    char *cur1 = &str1[my_strlen(str1) - 1];
    char *cur2 = &str2[my_strlen(str2) - 1];
    int longestNb = longest(str1, str2);

    for (int i = 0; i <= longestNb; i++) {
        treat_digit(&res[longestNb - i + 2], (cur1 - i), (cur2 - i), &carriedNum);
    }
    if (carriedNum != 0)
        res[1] = '1';
    else
        res[1] = '*';
    res[longestNb + 3] = '\0';
    apply_symbol(&res[0], str1, str2);
}

void display_res(char *res)
{
    int first_digit = 0;
    my_putstr(res);my_putchar('\n'); // DEBUG
    for (int i = 0; i < my_strlen(res); i++) {
        if (first_digit == 0 && is_pos_num(res[i]))
            first_digit = 1;
        if (first_digit || res[i] == '-')
            my_putchar(res[i]);
    }
    my_putchar('\n');
}

void infinadd(char *str1, char *str2)
{
    char *res = create_res_str(str1, str2);

    if (res == NULL) {
        write(2, "ERROR: malloc res str\n", 22);
        return;
    }
    my_putstr("CALC RES\n"); // Debug
    calcul_add(res, str1, str2);
    my_putstr("Display RES\n"); // DEBUG
    display_res(res);
    free(res);
}
