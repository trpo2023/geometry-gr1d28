#include "libgeometry/geometry.h"

int main(int argc, char* argv[])
{
    FILE* geometry = NULL;
    struct Object* object;
    int i = 0;
    int capacity = i + 1;
    int cal;
    object = figure_init(capacity);
    if (argc < 2) {
        fprintf(stderr, "Использование: %s имя_файла\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if ((geometry = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Не удается открыть файл \"%s\"\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    printf("Количество фигур для ввода: ");
    scanf("%d", &cal);

    char str[cal][80];
    for (int b = 0; b < cal; b++) {
        if (fgets(str[b], 79, geometry) == NULL) {
            printf("Достигнут конец файла\n");
            break;
        }
    }
    while (cal > i) {
        process_object(&object[i], str[i], i + 1);
        if (strcmp(object[i].name, "circle") == 0) {
            printf("%d. %s", i + 1, object[i].name);
            printf(" ( %.1f %.1f , %.1f )\n",
                   object[i].point1.number_x,
                   object[i].point1.number_y,
                   object[i].R);
            printf("P = %.4f\n", object[i].P);
            printf("S = %.4f\n\n", object[i].S);
        } else if (strcmp(object[i].name, "trinagle") == 0) {
            printf("%d. %s", i + 1, object[i].name);
            printf(" ( ( %.1f %.1f , %.1f %.1f , %.1f %.1f , %.1f %.1f ) )\n",
                   object[i].point1.number_x,
                   object[i].point1.number_y,
                   object[i].point2.number_x,
                   object[i].point2.number_y,
                   object[i].point3.number_x,
                   object[i].point3.number_y,
                   object[i].point4.number_x,
                   object[i].point4.number_y);
            printf("P = %.4f\n", object[i].P);
            printf("S = %.4f\n\n", object[i].S);
        }

        if (capacity == i + 1)
            figure_realloc(object, capacity);
        i++;
    }
    free(object);
    printf("Программа завершена.\n");

    return 0;
}