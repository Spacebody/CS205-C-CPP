#include "distance.h"

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
    printf("Please input the name of first city with its latitude and its longitude(separate by whitespace):\n");
    char first_city[BUFFER_SIZE];
    float altitude_1 = 0., longitude_1 = 0.;
    while (scanf("%s %f %f", first_city, &altitude_1, &longitude_1) != 3)
    {
        printf("Input error! Input again:\n");
        while (getchar() != '\n');
    }
    printf("Please input the name of second city with its latitude and its longitude(separate by whitespace):\n");
    char second_city[BUFFER_SIZE];
    float altitude_2 = 0., longitude_2 = 0.;
    while (scanf("%s %f %f", second_city, &altitude_2, &longitude_2) != 3)
    {
        printf("Input error! Input again:\n");
        while (getchar() != '\n');
    }

    float angle = sin((90 - altitude_1) * PI / 180) * sin((90 - altitude_2) * PI / 180) * \
            cos((longitude_1 - longitude_2) * PI / 180) + cos((90 - altitude_1) * PI / 180) * \
            cos((90 - altitude_2) * PI / 180);
    float distance = R * acos(angle);

    printf("The distance between %s and %s is %.3f km\n", first_city, second_city, distance);
}