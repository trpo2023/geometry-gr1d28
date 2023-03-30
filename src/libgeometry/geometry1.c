#include "libgeometry/geometry.h"
#include <math.h>

int cont(char* str, int i)
{
    while (str[i] == ' ')
        i++;
    return i;
}

int char_number(char x)
{
    if (x == '0' || x == '1' || x == '2' || x == '3' || x == '4' || x == '5'
        || x == '6' || x == '7' || x == '8' || x == '9' || x == '.')
        return 1;
    else
        return 0;
}

struct Object* figure_init(int quantity)
{
    struct Object* object;
    object = malloc(sizeof(struct Object*) * quantity);
    if (object)
        return object;
    printf("Ошибка выделения памяти!\n");
    return NULL;
}

struct Object* figure_realloc(struct Object* object, int capacity)
{
    int k = 2;
    object = realloc(object, sizeof(struct Object*) * capacity * k);
    if (object)
        return object;
    else {
        fprintf(stderr, "Ошибка перевыделения памяти\n");
        exit(EXIT_FAILURE);
    }
}

void error_locate(int column, char* str)
{
    printf("%s", str);
    while (column > 1) {
        printf(" ");
        column--;
    }
    printf("^\n");
}

void error_full(int num, int column, char* c, char* str, int mode)
{
    if (mode == 0) {
        error_locate(column, str);
        printf("Error at string %d, column %d: expected %s\n", num, column, c);
        exit(EXIT_FAILURE);
    }
    if (mode == 1) {
        error_locate(column, str);
        printf("Error at string %d, column %d: %s\n", num, column, c);
        exit(EXIT_FAILURE);
    }
}

void process_circle(struct Object* gcircle, int num, char* str)
{
    char *name, *key, number1[6], number2[6], rad[6];
    char op_br, com, cl_br;
    int i;
    float pi = 3.14;
    key = "circle";
    op_br = '(';
    com = ',';
    cl_br = ')';
    name = calloc(sizeof(char), 6);
    for (i = 0; i < 6; i++)
        name[i] = str[i];

    if ((strcmp(name, key)) == 0)
        sprintf(gcircle->name, "%s", name);
    else {
        i = 0;
        while (name[i] == key[i])
            i++;
        error_full(num, i, "expected 'circle' or 'trinagle'", str, 1);
    }

    i = cont(str, i);

    if (str[i] != op_br)
        error_full(num, i + 1, "(", str, 0);
    else
        i++;

    i = cont(str, i);

    for (int y = 0; str[i] != ' ' && y < 6; y++, i++) {
        if (char_number(str[i]))
            number1[y] = str[i];
        else
            error_full(num, i + 1, "'<double>'", str, 0);
    }
    gcircle->point1.number_x = atof(number1);

    i = cont(str, i);

    for (int y = 0; str[i] != ' ' && y < 6; y++, i++) {
        if (char_number(str[i]))
            number2[y] = str[i];
        else
            error_full(num, i + 1, "'<double>'", str, 0);
    }
    gcircle->point1.number_y = atof(number2);

    i = cont(str, i);

    if (str[i] != com)
        error_full(num, i + 1, ",", str, 0);
    else
        i++;

    i = cont(str, i);

    for (int y = 0; str[i] != ' ' && y < 6; y++, i++) {
        if (char_number(str[i]))
            rad[y] = str[i];
        else
            error_full(num, i + 1, "'<double>'", str, 0);
    }
    gcircle->R = atof(rad);

    i = cont(str, i);

    if (str[i] != cl_br)
        error_full(num, i + 1, ")", str, 0);
    else
        i++;

    i = cont(str, i);

    if (str[i] != '\n' && str[i] != '\0' && str[i] != '\r')
        error_full(num, i, "unexpected token", str, 1);
    free(name);

    gcircle->P = 2 * pi * gcircle->R;
    gcircle->S = pi * gcircle->R * gcircle->R;
}

void process_trinagle(struct Object* trinagle, int num, char* str)
{
    char *name, *key, number1_x[6], number1_y[6], number2_x[6], number2_y[6],
            number3_x[6], number3_y[6], number4_x[6], number4_y[6];
    char op_br, com, cl_br;
    int i;
    float x1, x2, x3, pr;

    key = "trinagle";
    op_br = '(';
    com = ',';
    cl_br = ')';
    name = calloc(sizeof(char), 8);
    for (i = 0; i < 8; i++)
        name[i] = str[i];

    if ((strcmp(name, key)) == 0)
        sprintf(trinagle->name, "%s", name);
    else {
        i = 0;
        while (name[i] == key[i])
            i++;
        error_full(num, i, "expected 'circle' or 'trinagle'", str, 1);
    }

    i = cont(str, i);

    if (str[i] != op_br)
        error_full(num, i + 1, "(", str, 0);
    else
        i++;

    i = cont(str, i);

    if (str[i] != op_br)
        error_full(num, i + 1, "(", str, 0);
    else
        i++;

    i = cont(str, i);

    for (int y = 0; str[i] != ' ' && y < 6; y++, i++) {
        if (char_number(str[i]))
            number1_x[y] = str[i];
        else
            error_full(num, i + 1, "'<double>'", str, 0);
    }
    trinagle->point1.number_x = atof(number1_x);

    i = cont(str, i);

    for (int y = 0; str[i] != ' ' && y < 6; y++, i++) {
        if (char_number(str[i]))
            number1_y[y] = str[i];
        else
            error_full(num, i + 1, "'<double>'", str, 0);
    }
    trinagle->point1.number_y = atof(number1_y);

    i = cont(str, i);

    if (str[i] != com)
        error_full(num, i + 1, ",", str, 0);
    else
        i++;

    i = cont(str, i);

    for (int y = 0; str[i] != ' ' && y < 6; y++, i++) {
        if (char_number(str[i]))
            number2_x[y] = str[i];
        else
            error_full(num, i + 1, "'<double>'", str, 0);
    }
    trinagle->point2.number_x = atof(number2_x);

    i = cont(str, i);

    for (int y = 0; str[i] != ' ' && y < 6; y++, i++) {
        if (char_number(str[i]))
            number2_y[y] = str[i];
        else
            error_full(num, i + 1, "'<double>'", str, 0);
    }
    trinagle->point2.number_y = atof(number2_y);

    i = cont(str, i);

    if (str[i] != com)
        error_full(num, i + 1, ",", str, 0);
    else
        i++;

    i = cont(str, i);

    for (int y = 0; str[i] != ' ' && y < 6; y++, i++) {
        if (char_number(str[i]))
            number3_x[y] = str[i];
        else
            error_full(num, i + 1, "'<double>'", str, 0);
    }
    trinagle->point3.number_x = atof(number3_x);

    i = cont(str, i);

    for (int y = 0; str[i] != ' ' && y < 6; y++, i++) {
        if (char_number(str[i]))
            number3_y[y] = str[i];
        else
            error_full(num, i + 1, "'<double>'", str, 0);
    }
    trinagle->point3.number_y = atof(number3_y);

    i = cont(str, i);

    if (str[i] != com)
        error_full(num, i + 1, ",", str, 0);
    else
        i++;

    i = cont(str, i);

    for (int y = 0; str[i] != ' ' && y < 6; y++, i++) {
        if (char_number(str[i]))
            number4_x[y] = str[i];
        else
            error_full(num, i + 1, "'<double>'", str, 0);
    }
    trinagle->point4.number_x = atof(number4_x);

    if (trinagle->point1.number_x != trinagle->point4.number_x)
        error_full(num, i, "data compatibility error", str, 1);

    i = cont(str, i);

    for (int y = 0; str[i] != ' ' && y < 6; y++, i++) {
        if (char_number(str[i]))
            number4_y[y] = str[i];
        else
            error_full(num, i + 1, "'<double>'", str, 0);
    }
    trinagle->point4.number_y = atof(number4_y);

    if (trinagle->point1.number_y != trinagle->point4.number_y)
        error_full(num, i, "data compatibility error", str, 1);

    i = cont(str, i);

    if (str[i] != cl_br)
        error_full(num, i + 1, ")", str, 0);
    else
        i++;

    i = cont(str, i);

    if (str[i] != cl_br)
        error_full(num, i + 1, ")", str, 0);
    else
        i++;

    i = cont(str, i);

    if (str[i] != '\n' && str[i] != '\0' && str[i] != '\r')
        error_full(num, i, "unexpected token", str, 1);

    free(name);

    x1 = sqrt(
            pow((trinagle->point1.number_x - trinagle->point2.number_x), 2)
            + pow((trinagle->point1.number_y - trinagle->point2.number_y), 2));
    x2 = sqrt(
            pow((trinagle->point2.number_x - trinagle->point3.number_x), 2)
            + pow((trinagle->point2.number_y - trinagle->point3.number_y), 2));
    x3 = sqrt(
            pow((trinagle->point3.number_x - trinagle->point4.number_x), 2)
            + pow((trinagle->point3.number_y - trinagle->point4.number_y), 2));

    trinagle->P = x1 + x2 + x3;
    pr = trinagle->P / 2;
    trinagle->S = sqrt(pr * (pr - x1) * (pr - x2) * (pr - x3));
}

int process_object(struct Object* object, char* str, int num)
{
    int i = 0;

    while (str[i] == ' ')
        i++;

    if (str[i] == 'c')
        process_circle(object, num, str);
    else if (str[i] == 't')
        process_trinagle(object, num, str);
    else
        error_full(num, i, "expected 'circle' or 'trinagle'", str, 1);

    return 0;
}
