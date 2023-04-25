#include <limits.h>
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

// double char_double(char *str)
// {
//     int i = 0, j = 0;
//     double sum = 0;
//     char *cp = malloc(sizeof(char) * 16);
//     sum += atoi(str);
//     while(str[i] != '.' && str[i] != '\0')
//         i++;
//     if(str[i] != '\0')
//         i++;

//     while(str[i] != '\0')
//     {
//         cp[j] = str[i];
//         j++;
//         i++;
//     }
//     cp[j] = '\0';
//     sum += atoi(cp) * pow(1e-1, j);
//     free(cp);
//     return sum;
// }

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
    printf("%s\n", str);
    while (column > 1) {
        printf(" ");
        column--;
    }
    printf("^\n");
}

void error_full(int num, int column, char* c, char* str, int mode)
{
    char* key_circle = "circle";
    char* key_trinagle = "triangle";

    if (mode == 0) {
        error_locate(column, str);
        printf("Error at string %d, column %d: expected %s\n", num, column, c);
        exit(EXIT_FAILURE);
    }

    if (mode == 1) {
        int size = 6;
        for (int i = 0; i < size && str[column] == key_circle[i]; i++)
            column++;

        // while (str[column] == key_circle[i])
        //     column--;
        error_locate(column + 1, str);
        printf("Error at string %d, column %d: %s\n", num, column, c);
        exit(EXIT_FAILURE);
    }

    if (mode == 2) {
        int size = 8;
        for (int i = 0; i < size && str[column] == key_trinagle[i]; i++)
            column++;
        // while (str[column] == key_trinagle[i])
        // {
        //     column--;
        //     i--;
        // }
        error_locate(column + 1, str);
        printf("Error at string %d, column %d: %s\n", num, column, c);
        exit(EXIT_FAILURE);
    }

    if (mode == 3) {
        error_locate(column, str);
        printf("Error at string %d, column %d: %s\n", num, column, c);
        exit(EXIT_FAILURE);
    }
}

int name_figure(struct Object* figure, char* key, char* str, int* i, int mode)
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
    else {
        free(name);
        return -1;
    }
    // error_full(num, d, "expected 'circle' or 'triangle'", str, mode);
    free(name);

    *i = d;
    return 0;
}

int punctuation(char mark, char* str, int* i)
{
    int b = *i;
    b = skip_space(str, b);
    if (str[b] != mark) {
        *i = b;
        return -1;
    }
    // error_full(num, i + 1, &mark, str, 0);
    else
        b++;
    *i = b;
    return 0;
}

int double_value(double* struct_number, char* str, int* i)
{
    int b = *i, y;
    char* number;
    number = calloc(sizeof(char), 8);

    b = skip_space(str, b);

    for (y = 0; str[b] != ' ' && y < 8; y++, b++) {
        if (char_number(str[b]))
            number[y] = str[b];
        else if (str[b] == '-' && y == 0)
            number[y] = str[b];
        else {
            *i = b;
            free(number);
            return -1;
        }
        // error_full(num, i + 1, "'<double>'", str, 0);
    }
    number[y] = '\0';
    *struct_number = atof(number);
    free(number);
    *i = b;
    return 0;
}

void R_check(double* R, char* str, int i, int num)
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
        double point1, double point2, char* str, int i, int num)
{
    if (point1 != point2)
        error_full(num, i, "data compatibility error", str, 3);
}

void calculate_circle(double* P, double* S, double* R)
{
    *P = 2 * M_PI * (*R);
    *S = M_PI * (*R) * (*R);
}

void calculate_trinagle(struct Object* trinagle)
{
    double x1, x2, x3, pr;

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
        error_full(num, i, "triangle does not exist", str, 3);
}

void process_circle(struct Object* gcircle, int num, char* str)
{
    int i = 0, res;

    res = name_figure(gcircle, "circle", str, &i, 1);
    if (res != 0)
        error_full(num, i, "expected 'circle' or 'triangle'", str, 1);

    res = punctuation('(', str, &i);
    if (res == -1)
        error_full(num, i + 1, "(", str, 0);

    res = double_value(&gcircle->point1.number_x, str, &i);
    if (res == -1)
        error_full(num, i + 1, "'<double>'", str, 0);

    res = double_value(&gcircle->point1.number_y, str, &i);
    if (res == -1)
        error_full(num, i + 1, "'<double>'", str, 0);

    res = punctuation(',', str, &i);
    if (res == -1)
        error_full(num, i + 1, ",", str, 0);

    res = double_value(&gcircle->R, str, &i);
    if (res == -1)
        error_full(num, i + 1, "'<double>'", str, 0);

    R_check(&gcircle->R, str, i, num);

    res = punctuation(')', str, &i);
    if (res == -1)
        error_full(num, i + 1, ")", str, 0);

    end_check(str, i, num);

    calculate_circle(&gcircle->P, &gcircle->S, &gcircle->R);
}

void process_triangle(struct Object* trinagle, int num, char* str)
{
    int i = 0, res;

    res = name_figure(trinagle, "triangle", str, &i, 2);
    if (res != 0)
        error_full(num, i, "expected 'circle' or 'triangle'", str, 2);

    res = punctuation('(', str, &i);
    if (res == -1)
        error_full(num, i + 1, "(", str, 0);

    res = punctuation('(', str, &i);
    if (res == -1)
        error_full(num, i + 1, "(", str, 0);

    res = double_value(&trinagle->point1.number_x, str, &i);
    if (res == -1)
        error_full(num, i + 1, "'<double>'", str, 0);

    res = double_value(&trinagle->point1.number_y, str, &i);
    if (res == -1)
        error_full(num, i + 1, "'<double>'", str, 0);

    res = punctuation(',', str, &i);
    if (res == -1)
        error_full(num, i + 1, ",", str, 0);

    res = double_value(&trinagle->point2.number_x, str, &i);
    if (res == -1)
        error_full(num, i + 1, "'<double>'", str, 0);

    res = double_value(&trinagle->point2.number_y, str, &i);
    if (res == -1)
        error_full(num, i + 1, "'<double>'", str, 0);

    res = punctuation(',', str, &i);
    if (res == -1)
        error_full(num, i + 1, ",", str, 0);

    res = double_value(&trinagle->point3.number_x, str, &i);
    if (res == -1)
        error_full(num, i + 1, "'<double>'", str, 0);

    res = double_value(&trinagle->point3.number_y, str, &i);
    if (res == -1)
        error_full(num, i + 1, "'<double>'", str, 0);

    res = punctuation(',', str, &i);
    if (res == -1)
        error_full(num, i + 1, ",", str, 0);

    res = double_value(&trinagle->point4.number_x, str, &i);
    if (res == -1)
        error_full(num, i + 1, "'<double>'", str, 0);

    data_compatibility_check(
            trinagle->point1.number_x, trinagle->point4.number_x, str, i, num);

    res = double_value(&trinagle->point4.number_y, str, &i);
    if (res == -1)
        error_full(num, i + 1, "'<double>'", str, 0);

    data_compatibility_check(
            trinagle->point1.number_y, trinagle->point4.number_y, str, i, num);

    res = punctuation(')', str, &i);
    if (res == -1)
        error_full(num, i + 1, ")", str, 0);

    res = punctuation(')', str, &i);
    if (res == -1)
        error_full(num, i + 1, ")", str, 0);

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
        process_triangle(object, num, str);
    else
        error_full(num, i, "expected 'circle' or 'triangle'", str, 1);

    return 0;
}

double distance(struct Point first, struct Point second)
{
    double dist;
    dist = pow((first.number_x - second.number_x), 2)
            + pow((first.number_y - second.number_y), 2);
    return dist;
}

int for_triangle(struct Point point, struct Point first, struct Point second)
{
    double k, check, b;
    if (first.number_x >= second.number_x
        && (point.number_x >= first.number_x
            || point.number_x <= second.number_x))
        return 0;
    else if (
            first.number_x <= second.number_x
            && (point.number_x >= second.number_x
                || point.number_x <= first.number_x))
        return 0;

    k = (first.number_y - second.number_y) / (first.number_x - second.number_x);
    b = first.number_y - k * first.number_x;
    check = k * point.number_x + b;
    if (check >= point.number_y)
        return -1;
    if (check <= point.number_y)
        return 1;

    return 0;
}

int point_inside(struct Point point, struct Object object2)
{
    int check1, check2, check3, check4;

    check1 = for_triangle(point, object2.point1, object2.point2);
    check2 = for_triangle(point, object2.point2, object2.point3);
    check3 = for_triangle(point, object2.point3, object2.point4);
    check4 = for_triangle(point, object2.point4, object2.point1);

    if (check1 == -1 && (check2 == 1 || check4 == 1))
        return 1;
    if (check2 == -1 && (check1 == 1 || check3 == 1))
        return 1;
    if (check3 == -1 && (check2 == 1 || check4 == 1))
        return 1;
    if (check4 == -1 && (check3 == 1 || check3 == 1))
        return 1;
    return 0;
}

int triangle_intersection(struct Object object1, struct Object object2)
{
    if (point_inside(object1.point1, object2))
        return 1;
    if (point_inside(object1.point2, object2))
        return 1;
    if (point_inside(object1.point3, object2))
        return 1;
    return 0;
}

int intersection(struct Object object1, struct Object object2)
{
    int circle1, circle2, trinagle1, trinagle2;
    double radsum;
    double dist;
    circle1 = strcmp(object1.name, "circle");
    trinagle1 = strcmp(object1.name, "triangle");
    circle2 = strcmp(object2.name, "circle");
    trinagle2 = strcmp(object2.name, "triangle");

    if (circle1 == 0 && circle2 == 0) {
        dist = distance(object1.point1, object2.point1);
        radsum = object1.R + object2.R;
        if (radsum > dist)
            return 1;
    } else if (circle1 == 0 && trinagle2 == 0) {
        dist = distance(object1.point1, object2.point1);
        if (object1.R > dist)
            return 1;

        dist = distance(object1.point1, object2.point2);
        if (object1.R > dist)
            return 1;

        dist = distance(object1.point1, object2.point3);
        if (object1.R > dist)
            return 1;
    } else if (trinagle1 == 0 && circle2 == 0) {
        dist = distance(object2.point1, object1.point1);
        if (object2.R > dist)
            return 1;

        dist = distance(object2.point1, object1.point2);
        if (object2.R > dist)
            return 1;

        dist = distance(object2.point1, object1.point3);
        if (object2.R > dist)
            return 1;
    } else if (trinagle1 == 0 && trinagle2 == 0) {
        if (triangle_intersection(object1, object2))
            return 1;
    }

    return 0;
}