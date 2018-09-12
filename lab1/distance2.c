#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BUFFER_SIZE 1024
#define PI 3.1415926535
#define R 6371

void cal_distance(void);

// main
int main(int argc, char* argv[])
{
    cal_distance();
    return 0;
}

// calculate the distance between two cities
void cal_distance(void)
{
    // printf("Please input the name of first city with its latitude \
            and its longitude(separate by whitespace):\n");
    char first_city[BUFFER_SIZE];
    double altitude_1 = 0., longitude_1 = 0.;
    while (scanf("%[^\n]s", first_city) != 1)
    {
        // printf("Input error! Input again:\n");
        while (getchar() != '\n');
    }
    while (scanf("%lf %lf", &altitude_1, &longitude_1) != 2)
    {
        // printf("Input error! Input again:\n");
        while (getchar() != '\n');
    }
    // printf("Please input the name of second city with its latitude\
             and its longitude(separate by whitespace):\n");
    char second_city[BUFFER_SIZE];
    double altitude_2 = 0., longitude_2 = 0.;
    while (scanf("%[^\n]s", second_city) != 1)
    {
        // printf("Input error! Input again:\n");
        while (getchar() != '\n');
    }
    while (scanf("%lf %lf", &altitude_2, &longitude_2) != 2)
    {
        // printf("Input error! Input again:\n");
        while (getchar() != '\n');
    }

    double angle = sin((90 - altitude_1) * PI / 180) * \
            sin((90 - altitude_2) * PI / 180) * \
            cos((longitude_1 - longitude_2) * PI / 180) + \
            cos((90 - altitude_1) * PI / 180) * \
            cos((90 - altitude_2) * PI / 180);
    double distance = R * acos(angle);

    printf("The distance between %s and %s is %.2lf km\n", \
            first_city, second_city, distance);
}