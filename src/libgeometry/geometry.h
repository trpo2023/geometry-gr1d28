#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10
struct Point {
    float number_x;
    float number_y;
};
struct Object {
    char name[10];
    struct Point point1;
    struct Point point2;
    struct Point point3;
    struct Point point4;
    float R;
    float S;
    float P;
};

struct Object* figure_init(int quantity);

struct Object* figure_realloc(struct Object* object, int capacity);

int process_object(struct Object* object, char* str, int num);
