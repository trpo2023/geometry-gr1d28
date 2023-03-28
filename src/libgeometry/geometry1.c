#include "geometry.h"

int choose(char x)
{
    if(x == '0' || x == '1' || x == '2' || x == '3' || x == '4' || x == '5' || x == '6' || x == '7' || x == '8' || x == '9' || x == '.')
        return 1;
    else
        return 0;
}

struct Object *figure_init(int quantity)
{
    struct Object *object;
    object = malloc(sizeof(struct Object *) * quantity);
    if(object)
        return object;
    printf("Ошибка выделения памяти!\n");
    return NULL;
}

struct Object *figure_realloc(struct Object *object, int capacity)
{
    int k = 2;
    object = realloc(object, sizeof(struct Object *) * capacity * k);
    if(object)
        return object;
    else
    {
        fprintf(stderr, "Ошибка перевыделения памяти\n");
        exit(EXIT_FAILURE);
    }
}

void error_locate(int column, char *str)
{
    printf("%s", str);
    while(column > 1)
    {
        printf(" ");
        column--;
    }
    printf("^\n");

}

void error_full(int num, int column, char *c, char *str)
{
    error_locate(column, str);
    printf("Error at string %d, column %d: expected %s\n", num, column, c);
    exit(EXIT_FAILURE);
}

void process_circle(struct Object *gcircle, int num, char *str)
{
    char *name, *key, number1[6], number2[6], rad[6];
    char s, p, e;
    int i;
    float pi = 3.14;
    key = "circle";
    s = '(';
    p = ',';
    e = ')';
    name = calloc(sizeof(char), 6);
    //step_in = ftell(geometry);
    for(i = 0; i < 6; i++)
	name[i] = str[i];
    /*{
        if(str[i] == key[i])
		continue;*/
    if((strcmp(name, key)) == 0)
    {
        sprintf(gcircle->name, "%s", name);
    }
    	else
    	{
        	i = 0;
        	while(name[i] == key[i])
            		i++;
        	error_locate(i + 1, str);
        	printf("Error at string %d, column %d: expected 'circle' or 'trinagle'\n", num, i + 1);
        	exit(EXIT_FAILURE);
    	}
    //}

    while(str[i] == ' ')
        i++;
    if(str[i] != s)
    {
        error_full(num, i + 1, "(", str);
    }
    else
        i++;

    while(str[i] == ' ')
        i++;
    for(int y = 0; str[i] != ' ' && y < 6; y++, i++)
    {
        if(choose(str[i]))
            number1[y] = str[i];
        else
            error_full(num, i + 1, "'<double>'", str);
    }
    gcircle->point1.number_x = atof(number1);

    while(str[i] == ' ')
        i++;
    for(int y = 0; str[i] != ' ' && y < 6; y++, i++)
    {
        if(choose(str[i]))
            number2[y] = str[i];
        else
            error_full(num, i + 1, "'<double>'", str);
    }
    gcircle->point1.number_y = atof(number2);

    while(str[i] == ' ')
        i++;
    if(str[i] != p)
    {
        error_full(num, i + 1, ",", str);
    }
    else
        i++;

    while(str[i] == ' ')
        i++;
    for(int y = 0; str[i] != ' ' && y < 6; y++, i++)
    {
        if(choose(str[i]))
            rad[y] = str[i];
        else
            error_full(num, i + 1, "'<double>'", str);
    }
    gcircle->R = atof(rad);

    while(str[i] == ' ')
        i++;
    if(str[i] != e)
    {
        error_full(num, i + 1, ")", str);
    }
    else
        i++;

    while(str[i] == ' ')
        i++;
    if(str[i] != '\n' && str[i] != '\0' && str[i] != '\r')
    {
        error_locate(i + 1, str);
        printf("Error at string %d, column %d: unexpected token\n", num, i + 1);
        exit(EXIT_FAILURE);
    }
    free(name);

    gcircle->P = 2 * pi * gcircle->R;
    gcircle->S = pi * gcircle->R * gcircle->R;
}

void process_trinagle(struct Object *trinagle, int num, char *str)
{
    char *name, *key, number1_x[6], number1_y[6], number2_x[6], number2_y[6], number3_x[6], number3_y[6], number4_x[6], number4_y[6];
    char s, p, e;
    int i;
    float x1, x2, x3, pr;

    key = "trinagle";
    s = '(';
    p = ',';
    e = ')';
    name = calloc(sizeof(char), 8);
    for(i = 0; i < 8; i++)
        name[i] = str[i];
    if((strcmp(name, key)) == 0)
    {
        sprintf(trinagle->name, "%s", name);
    }
    else
    {
        i = 0;
        while(name[i] == key[i])
            i++;
        error_locate(i + 1, str);
        printf("Error at string %d, column %d: expected 'circle' or 'trinagle'\n", num, i + 1);
        exit(EXIT_FAILURE);
    }

    while(str[i] == ' ')
        i++;
    if(str[i] != s)
    {
        error_full(num, i + 1, "(", str);
    }
    else
        i++;

    while(str[i] == ' ')
        i++;
    if(str[i] != s)
    {
        error_full(num, i + 1, "(", str);
    }
    else
        i++;

    while(str[i] == ' ')
        i++;
    for(int y = 0; str[i] != ' ' && y < 6; y++, i++)
    {
        if(choose(str[i]))
            number1_x[y] = str[i];
        else
            error_full(num, i + 1, "'<double>'", str);
    }
    trinagle->point1.number_x = atof(number1_x);

    while(str[i] == ' ')
        i++;
    for(int y = 0; str[i] != ' ' && y < 6; y++, i++)
    {
        if(choose(str[i]))
            number1_y[y] = str[i];
        else
            error_full(num, i + 1, "'<double>'", str);
    }
    trinagle->point1.number_y = atof(number1_y);

    while(str[i] == ' ')
        i++;
    if(str[i] != p)
    {
        error_full(num, i + 1, ",", str);
    }
    else
        i++;

    while(str[i] == ' ')
        i++;
    for(int y = 0; str[i] != ' ' && y < 6; y++, i++)
    {
        if(choose(str[i]))
            number2_x[y] = str[i];
        else
            error_full(num, i + 1, "'<double>'", str);
    }
    trinagle->point2.number_x = atof(number2_x);

    while(str[i] == ' ')
        i++;
    for(int y = 0; str[i] != ' ' && y < 6; y++, i++)
    {
        if(choose(str[i]))
            number2_y[y] = str[i];
        else
            error_full(num, i + 1, "'<double>'", str);
    }
    trinagle->point2.number_y = atof(number2_y);

    while(str[i] == ' ')
        i++;
    if(str[i] != p)
    {
        error_full(num, i + 1, ",", str);
    }
    else
        i++;

    while(str[i] == ' ')
        i++;
    for(int y = 0; str[i] != ' ' && y < 6; y++, i++)
    {
        if(choose(str[i]))
            number3_x[y] = str[i];
        else
            error_full(num, i + 1, "'<double>'", str);
    }
    trinagle->point3.number_x = atof(number3_x);

    while(str[i] == ' ')
        i++;
    for(int y = 0; str[i] != ' ' && y < 6; y++, i++)
    {
        if(choose(str[i]))
            number3_y[y] = str[i];
        else
            error_full(num, i + 1, "'<double>'", str);
    }
    trinagle->point3.number_y = atof(number3_y);

     while(str[i] == ' ')
        i++;
    if(str[i] != p)
    {
        error_full(num, i + 1, ",", str);
    }
    else
        i++;

    while(str[i] == ' ')
        i++;
    for(int y = 0; str[i] != ' ' && y < 6; y++, i++)
    {
        if(choose(str[i]))
            number4_x[y] = str[i];
        else
            error_full(num, i + 1, "'<double>'", str);
    }
    trinagle->point4.number_x = atof(number4_x);

    if(trinagle->point1.number_x != trinagle->point4.number_x)
    {
        error_locate(i + 1, str);
        printf("Error at string %d, column %d: data compatibility error\n", num, i + 1);
        exit(EXIT_FAILURE);
    }

    while(str[i] == ' ')
        i++;
    for(int y = 0; str[i] != ' ' && y < 6; y++, i++)
    {
        if(choose(str[i]))
            number4_y[y] = str[i];
        else
            error_full(num, i + 1, "'<double>'", str);
    }
    trinagle->point4.number_y = atof(number4_y);

    if(trinagle->point1.number_y != trinagle->point4.number_y)
    {
        error_locate(i + 1, str);
        printf("Error at string %d, column %d: data compatibility error\n", num, i + 1);
        exit(EXIT_FAILURE);
    }

    while(str[i] == ' ')
        i++;
    if(str[i] != e)
    {
        error_full(num, i + 1, ")", str);
    }
    else
        i++;

    while(str[i] == ' ')
        i++;
    if(str[i] != e)
    {
        error_full(num, i + 1, ")", str);
    }
    else
        i++;

    while(str[i] == ' ')
        i++;
    if(str[i] != '\n' && str[i] != '\0' && str[i] != '\r')
    {
        error_locate(i + 1, str);
        printf("Error at string %d, column %d: unexpected token\n", num, i + 1);
        exit(EXIT_FAILURE);
    }
    free(name);

    x1 = sqrt(pow((trinagle->point1.number_x - trinagle->point2.number_x), 2) + pow((trinagle->point1.number_y - trinagle->point2.number_y), 2));
    x2 = sqrt(pow((trinagle->point2.number_x - trinagle->point3.number_x), 2) + pow((trinagle->point2.number_y - trinagle->point3.number_y), 2));
    x3 = sqrt(pow((trinagle->point3.number_x - trinagle->point4.number_x), 2) + pow((trinagle->point3.number_y - trinagle->point4.number_y), 2));

    trinagle->P = x1 + x2 + x3;
    pr = trinagle->P / 2;
    trinagle->S = sqrt(pr * (pr - x1) * (pr - x2) * (pr - x3));
}

int process_object(struct Object *object, char *str, int num)
{
    int i = 0;

    while(str[i] == ' ')
        i++;
    
    if(str[i] == 'c')
        process_circle(object, num, str);
    else if (str[i] == 't')
        process_trinagle(object, num, str);
    else
    {
        error_locate(i + 1, str);
        printf("Error at string %d, column %d: expected 'circle' or 'trinagle'\n", num, i + 1);
        exit(EXIT_FAILURE);
    }
    return 0;
}
