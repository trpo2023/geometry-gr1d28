#include <math.h>

#include "libgeometry/geometry.h"

int skip_space(char* str, int i)
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
    char* key_circle = "circle";
    char* key_trinagle = "trinagle";

    if (mode == 0) {
        error_locate(column, str);
        printf("Error at string %d, column %d: expected %s\n", num, column, c);
        exit(EXIT_FAILURE);
    }

    if (mode == 1) {
        while (str[column] == key_circle[column])
            column--;
        error_locate(column, str);
        printf("Error at string %d, column %d: %s\n", num, column, c);
        exit(EXIT_FAILURE);
    }

    if (mode == 2) {
        while (str[column] == key_trinagle[column])
            column--;
        error_locate(column, str);
        printf("Error at string %d, column %d: %s\n", num, column, c);
        exit(EXIT_FAILURE);
    }

    if (mode == 3) {
        error_locate(column, str);
        printf("Error at string %d, column %d: %s\n", num, column, c);
        exit(EXIT_FAILURE);
    }
}

void name_figure(
        struct Object* figure, char* key, char* str, int* i, int num, int mode)
{
    char* name;
    int d, size;
    d = *i;
    d = skip_space(str, d);
    if (mode == 1)
        size = 6;
    else if (mode == 2)
        size = 8;
    name = calloc(sizeof(char), size);
    for (d = 0; d < size; d++)
        name[d] = str[d];

    if ((strcmp(name, key)) == 0)
        sprintf(figure->name, "%s", name);
    else
        error_full(num, d, "expected 'circle' or 'trinagle'", str, mode);
    free(name);

    *i = d;
}

int punctuation(char mark, char* str, int i, int num)
{
    i = skip_space(str, i);
    if (str[i] != mark)
        error_full(num, i + 1, &mark, str, 0);
    else
        i++;
    return i;
}

int double_value(float* struct_number, char* str, int i, int num)
{
    char number[8];

    i = skip_space(str, i);

    for (int y = 0; str[i] != ' ' && y < 8; y++, i++) {
        if (char_number(str[i]))
            number[y] = str[i];
        else
            error_full(num, i + 1, "'<double>'", str, 0);
    }
    *struct_number = atof(number);

    return i;
}

void R_check(float* R, char* str, int i, int num)
{
    if (*R <= 0)
        error_full(num, i, "positive value for radius", str, 0);
}

void end_check(char* str, int i, int num)
{
    i = skip_space(str, i);

    if (str[i] != '\n' && str[i] != '\0' && str[i] != '\r')
        error_full(num, i + 1, "unexpected token", str, 3);
}

void data_compatibility_check(
        float point1, float point2, char* str, int i, int num)
{
    if (point1 != point2)
        error_full(num, i, "data compatibility error", str, 3);
}

void calculate_circle(float* P, float* S, float* R)
{
    *P = 2 * M_PI * (*R);
    *S = M_PI * (*R) * (*R);
}

void calculate_trinagle(struct Object* trinagle)
{
    float x1, x2, x3, pr;

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

void existence_check(struct Object* trinagle, char* str, int i, int num)
{
    if (trinagle->P <= 0 || trinagle->S <= 0)
        error_full(num, i, "trinagle does not exist", str, 3);
}

void process_circle(struct Object* gcircle, int num, char* str)
{
    int i = 0;

    name_figure(gcircle, "circle", str, &i, num, 1);

    i = punctuation('(', str, i, num);

    i = double_value(&gcircle->point1.number_x, str, i, num);

    i = double_value(&gcircle->point1.number_y, str, i, num);

    i = punctuation(',', str, i, num);

    i = double_value(&gcircle->R, str, i, num);

    R_check(&gcircle->R, str, i, num);

    i = punctuation(')', str, i, num);

    end_check(str, i, num);

    calculate_circle(&gcircle->P, &gcircle->S, &gcircle->R);
}

void process_trinagle(struct Object* trinagle, int num, char* str)
{
    int i = 0;

    name_figure(trinagle, "trinagle", str, &i, num, 2);

    i = punctuation('(', str, i, num);

    i = punctuation('(', str, i, num);

    i = double_value(&trinagle->point1.number_x, str, i, num);

    i = double_value(&trinagle->point1.number_y, str, i, num);

    i = punctuation(',', str, i, num);

    i = double_value(&trinagle->point2.number_x, str, i, num);

    i = double_value(&trinagle->point2.number_y, str, i, num);

    i = punctuation(',', str, i, num);

    i = double_value(&trinagle->point3.number_x, str, i, num);

    i = double_value(&trinagle->point3.number_y, str, i, num);

    i = punctuation(',', str, i, num);

    i = double_value(&trinagle->point4.number_x, str, i, num);

    data_compatibility_check(
            trinagle->point1.number_x, trinagle->point4.number_x, str, i, num);

    i = double_value(&trinagle->point4.number_y, str, i, num);

    data_compatibility_check(
            trinagle->point1.number_y, trinagle->point4.number_y, str, i, num);

    i = punctuation(')', str, i, num);

    i = punctuation(')', str, i, num);

    end_check(str, i, num);

    calculate_trinagle(trinagle);

    existence_check(trinagle, str, i, num);
}

int process_object(struct Object* object, char* str, int num)
{
    int i = 0;

    i = skip_space(str, i);

    if (str[i] == 'c')
        process_circle(object, num, str);
    else if (str[i] == 't')
        process_trinagle(object, num, str);
    else
        error_full(num, i, "expected 'circle' or 'trinagle'", str, 1);

    return 0;
}
