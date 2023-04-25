#include "libgeometry/geometry.h"

char** str_init(int limit)
{
    char** str;
    str = malloc(sizeof(char*) * limit);
    for (int j = 0; j < limit; j++)
        str[j] = malloc(sizeof(char) * 80);
    return str;
}

char** str_realloc(char** str, int size)
{
    str = realloc(str, sizeof(char*) * 2 * size);
    for (int i = size; i < size * 2; i++)
        str[i] = malloc(sizeof(char) * 80);

    return str;
}

void free_str(char** str, int limit)
{
    for (int i = 0; i < limit; i++)
        free(str[i]);
    free(str);
}

void print_object(struct Object object, int i)
{
    if (strcmp(object.name, "circle") == 0) {
        printf("%d. %s", i + 1, object.name);
        printf(" ( %.1lf %.1lf , %.1lf )\n",
               object.point1.number_x,
               object.point1.number_y,
               object.R);
        printf("P = %.4lf\n", object.P);
        printf("S = %.4lf\n", object.S);
    } else if (strcmp(object.name, "triangle") == 0) {
        printf("%d. %s", i + 1, object.name);
        printf(" ( ( %.1lf %.1lf , %.1lf %.1lf , %.1lf %.1lf , %.1lf %.1lf ) )\n",
               object.point1.number_x,
               object.point1.number_y,
               object.point2.number_x,
               object.point2.number_y,
               object.point3.number_x,
               object.point3.number_y,
               object.point4.number_x,
               object.point4.number_y);
        printf("P = %.4lf\n", object.P);
        printf("S = %.4lf\n", object.S);
    }
}

void print_intesects(struct Object* object, int index, int size)
{
    int check;
    printf("Intersects:\n");
    for (int i = 0; i < size; i++) {
        if (i == index)
            continue;

        check = intersection(object[index], object[i]);
        if (check)
            printf("%d. %s\n", i + 1, object[i].name);
    }
    printf("\n");
}

int main(int argc, char* argv[])
{
    FILE* geometry = NULL;
    struct Object* object;
    int i = 0;
    int str_size = 0, str_limit;
    if (argc < 2) {
        fprintf(stderr, "Использование: %s имя_файла\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if ((geometry = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Не удается открыть файл \"%s\"\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    char** str;
    str_limit = 2;
    str = str_init(str_limit);

    for (int j = 0; fgets(str[j], 79, geometry) != NULL; j++) {
        if (j + 1 == str_limit) {
            str = str_realloc(str, str_limit);
            str_limit *= 2;
        }
        str_size++;
    }
    printf("Достигнут конец файла\n");

    object = figure_init(str_size);

    while (str_size > i) {
        process_object(&object[i], str[i], i + 1);
        i++;
    }

    for (int j = 0; j < i; j++) {
        print_object(object[j], j);
        print_intesects(object, j, i);
    }

    // free_str(str, i);
    // free(object);
    printf("\nПрограмма завершена.\n");

    return 0;
}