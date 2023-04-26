#include "ctest.h"
#include "libgeometry/geometry.h"

CTEST(correct_data, name_test_circle)
{
    struct Object figure;
    int i = 0;
    char* key = "circle";

    const int result = name_figure(&figure, "circle", key, &i, 1);
    ASSERT_EQUAL(0, result);
    ASSERT_STR(key, figure.name);
}

CTEST(correct_data, name_test_triangle)
{
    struct Object figure;
    int i = 0;
    char* key = "triangle";

    const int result = name_figure(&figure, "triangle", key, &i, 2);
    ASSERT_EQUAL(0, result);
    ASSERT_STR(key, figure.name);
}

CTEST(correct_data, punctuation)
{
    int i = 0;
    char* key_op_br = "(";
    char* key_cl_br = ")";
    char* key_comma = ",";

    const int res_op_br = punctuation('(', key_op_br, &i);
    i = 0;
    const int res_cl_br = punctuation(')', key_cl_br, &i);
    i = 0;
    const int res_comma = punctuation(',', key_comma, &i);

    ASSERT_EQUAL(0, res_op_br);
    ASSERT_EQUAL(0, res_cl_br);
    ASSERT_EQUAL(0, res_comma);
}

CTEST(correct_data, double_value)
{
    int i;
    double number_neg;
    double number_pos;
    char* key_neg = "-3.0 ";
    char* key_pos = "2.593 ";

    i = 0;
    int res_neg = double_value(&number_neg, key_neg, &i);
    i = 0;
    int res_pos = double_value(&number_pos, key_pos, &i);

    ASSERT_DBL_NEAR_TOL(-3.0, number_neg, 1e-3);
    ASSERT_DBL_NEAR_TOL(2.593, number_pos, 1e-3);
    ASSERT_EQUAL(0, res_neg);
    ASSERT_EQUAL(0, res_pos);
}

CTEST(correct_data, calculate_circle)
{
    double S, R, P;
    R = 1.5;
    calculate_circle(&P, &S, &R);
    ASSERT_DBL_NEAR_TOL(9.4248, P, 1e-4);
    ASSERT_DBL_NEAR_TOL(7.0686, S, 1e-4);
}

CTEST(correct_data, calculate_trinagle)
{
    struct Object trinagle;
    trinagle.point1.number_x = -3.0;
    trinagle.point1.number_y = -2.0;
    trinagle.point2.number_x = -1.0;
    trinagle.point2.number_y = 0;
    trinagle.point3.number_x = -3.0;
    trinagle.point3.number_y = 2.0;
    trinagle.point4.number_x = -3.0;
    trinagle.point4.number_y = -2.0;

    calculate_trinagle(&trinagle);
    ASSERT_DBL_NEAR_TOL(9.6569, trinagle.P, 1e-4);
    ASSERT_DBL_NEAR_TOL(4.0000, trinagle.S, 1e-4);
}

CTEST(UNcorrect_data, name_test_circle)
{
    struct Object figure;
    int i = 0;
    char* key = "cicle";

    const int result = name_figure(&figure, "circle", key, &i, 1);
    ASSERT_EQUAL(-1, result);
}

CTEST(UNcorrect_data, name_test_triangle)
{
    struct Object figure;
    int i = 0;
    char* key = "trianle";

    const int result = name_figure(&figure, "triangle", key, &i, 1);
    ASSERT_EQUAL(-1, result);
}

CTEST(UNcorrect_data, punctuation)
{
    int i = 0;
    char* key_op_br = "g";
    char* key_cl_br = "x";
    char* key_comma = ".";

    const int res_op_br = punctuation('(', key_op_br, &i);
    i = 0;
    const int res_cl_br = punctuation(')', key_cl_br, &i);
    i = 0;
    const int res_comma = punctuation(',', key_comma, &i);

    ASSERT_EQUAL(-1, res_op_br);
    ASSERT_EQUAL(-1, res_cl_br);
    ASSERT_EQUAL(-1, res_comma);
}

CTEST(UNcorrect_data, double_value)
{
    int i = 0;
    double number_neg;
    double number_pos;
    char* key_neg = "-2.5c93";
    char* key_pos = "2.593x";

    int res_neg = double_value(&number_neg, key_neg, &i);
    i = 0;
    int res_pos = double_value(&number_pos, key_pos, &i);

    ASSERT_EQUAL(-1, res_neg);
    ASSERT_EQUAL(-1, res_pos);
}
