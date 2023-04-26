#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10
struct Point {
    double number_x;
    double number_y;
};
struct Object {
    char name[10];
    struct Point point1;
    struct Point point2;
    struct Point point3;
    struct Point point4;
    double R;
    double S;
    double P;
};

struct Object* figure_init(int quantity);

struct Object* figure_realloc(struct Object* object, int capacity);

int char_number(char x);

int name_figure(struct Object* figure, char* key, char* str, int* i, int mode);

int punctuation(char mark, char* str, int* i);

int double_value(double* struct_number, char* str, int* i);

void calculate_circle(double* P, double* S, double* R);

void calculate_trinagle(struct Object* trinagle);

int process_object(struct Object* object, char* str, int num);

int intersection(struct Object object1, struct Object object2);
