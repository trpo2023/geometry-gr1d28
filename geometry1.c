#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10
struct Point
{
    float number_x;
    float number_y;
};
struct Circle
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
void error_fun(FILE *geometry, long step_last, long step_in, int num)
{
    char buf[40];
    rewind(geometry);
    for(int i = 0; i < num + 1; i++)
        fgets(buf, 39, geometry);
    for(int i = 0; i < 39; i++) {
        if(buf[i] == '\n')
            buf[i] = '\0';
    }
    printf("%s\n", buf);
    while(step_last != step_in) {
        printf(" ");
        step_last--;
    }
    printf("^\n");
}
void error_full(FILE *geometry, char *c, long step_in, long step_last, int num)
{
    if(num != 0)
        step_last = step_last - 1;
    else
        step_last = step_last + 1;
    error_fun(geometry, step_last, step_in, num);
    printf("Error at column %ld: expected %s\n", step_last, c);
    exit(EXIT_FAILURE);
}
void process_circle(FILE *geometry, struct Circle *gcircle, int num, long step_in)
{
    char s[2], e[2], p[2];
    float pi = 3.14;
    long step_last;
    step_last = ftell(geometry);
    if((fscanf(geometry, "%s", s)) != 1)
    {
        error_full(geometry, "'('", step_in, step_last, num);
    }
    else
    {
        if(strcmp(s, "(") != 0)
        {
            error_full(geometry, "'('", step_in, step_last, num);
        }
    }
    step_last = ftell(geometry);
    if((fscanf(geometry, "%f", &gcircle->point1.number_x)) != 1)
    {
        error_full(geometry, "'<double>'", step_in, step_last, num);
    }
    step_last = ftell(geometry);
    if((fscanf(geometry, "%f", &gcircle->point1.number_y)) != 1)
    {
        error_full(geometry, "'<double>'", step_in, step_last, num);
    }
    step_last = ftell(geometry);
    if((fscanf(geometry, "%s", p)) != 1)
    {
        error_full(geometry, "','", step_in, step_last, num);
    }
    else
    {
        if(strcmp(p, ",") != 0)
        {
            error_full(geometry, "','", step_in, step_last, num);
        }
    }
    step_last = ftell(geometry);
    if((fscanf(geometry, "%f", &gcircle->R)) != 1)
    {
        step_last = ftell(geometry);
        error_full(geometry, "'<double>'", step_in, step_last, num);
    }
    step_last = ftell(geometry);
    if((fscanf(geometry, "%s", e)) != 1)
    {
        error_full(geometry, "')'", step_in, step_last, num);
    }
    else
    {
        if(strcmp(e, ")") != 0)
        {
            error_full(geometry, "')'", step_in, step_last, num);
        }
    }
    
    gcircle->P = 2 * pi * gcircle->R;
    gcircle->S = pi * gcircle->R * gcircle->R;
}

int main(int argc, char *argv[])
{
    FILE *geometry;
    struct Circle gcircle[SIZE];
    char str[10];
    long step_in;
    int num = 0;
    int quantity;
    int true = 0;
    if(argc < 2)
    {
        fprintf(stderr, "Использование: %s имя_файла\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if((geometry = fopen(argv[1], "rb")) == NULL)
    {
        fprintf(stderr, "Не удается открыть файл \"%s\"\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    printf("\n\nObject = 'circle' '(' Point ',' Number ')'\n\
    | 'triangle' '(' '(' Point ',' Point ',' Point ',' Point ')' ')'\n\
    Point = Number Number\n\
    Number = (* Floating-point number *)\n\n");
    printf("Количество фигур для ввода(не больше 10): ");
    if((true = scanf("%d", &quantity)) <= 0 || quantity >= 10)
        exit(EXIT_FAILURE);
    for(int i = 0; i < quantity; i++) {
        step_in = ftell(geometry);
        if((fscanf(geometry, "%s", str)) == 1)
        {
            if((strcmp(str, "circle")) == 0) {
                sprintf(gcircle[num].name, "%s", str);
                process_circle(geometry, &gcircle[num], num, step_in);
                num++;
            }
            else
            {
                error_fun(geometry, step_in, step_in, num);
                printf("Error at column %ld: expected 'circle'\n", step_in);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            error_fun(geometry, step_in, step_in, num);
            exit(EXIT_FAILURE);
        }
        printf("%d. %s", i + 1, gcircle[i].name);
        printf(" ( %.1f %.1f , %.1f )\n", gcircle[i].point1.number_x, gcircle[i].point1.number_y, gcircle[i].R);
        printf("P = %.4f\n", gcircle[i].P);
        printf("S = %.4f\n\n", gcircle[i].S);
    }
    return 0;
}