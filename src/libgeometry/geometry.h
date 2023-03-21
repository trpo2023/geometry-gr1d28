#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define SIZE 10
struct Point
{
    float number_x;
    float number_y;
};
struct Object
{
    char name[10];
    struct Point point1;
    struct Point point2;
    struct Point point3;
    struct Point point4;
    float R;
    float S;
    float P;
};

int choose(char x);

struct Object *figure_init(int quantity);

struct Object *figure_realloc(struct Object *object, int capacity);

void error_locate(int column, char *str);

void error_full(int num, int column, char *c, char *str);

void process_circle(struct Object *gcircle, int num, char *str);

void process_trinagle(struct Object *trinagle, int num, char *str);

int process_object(struct Object *object, char *str, int num);
