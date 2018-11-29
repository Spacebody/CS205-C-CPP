#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// control size
#define STR_LEN 50
#define ARR_LEN 1000
#define BUF_LEN 1024

// city information
typedef struct City_Info 
{
    char city[STR_LEN];
    char country[STR_LEN];
    char state[STR_LEN];
    double longitude;
    double latitude;
} City;

// constant
const double PI = 3.1415926535;
const double R = 6371;

// statues code
const int NOT_FOUND = 0;
const int TOO_SHORTER = -1;
const int QUERY_SUCCEED = 2;
const int MULTIPLE_MATCH = 3;
const int USER_CONTINUE = 4;

// glabal variables
City cities[ARR_LEN];
City queried_cities[2];
int record = 0;

// utilities
int read_data(char* filename);
int query(char* command);
int search(char* input, int indices[ARR_LEN]);
double calculate_distance(City queried_cities[2]);

// main
int main(int argc, char *argv[])
{
    char command[BUF_LEN];
    char file_name[] = "world_cities.csv";
    if (read_data(file_name) != 0)
    {
        return -1;
    }
 
    while (fputs("Please input city name or \"bye\" to quit: ", stdout) && \
            fgets(command, BUF_LEN, stdin))
    {
        if (strcasecmp(command, "bye\n") == 0 || strncasecmp(command, "bye ", 4) == 0)
        {
            return 0;
        }
        else
        {
            int result = query(command);
            switch(result)
            {
                case NOT_FOUND:
                case TOO_SHORTER:
                case MULTIPLE_MATCH:
                case USER_CONTINUE:
                {
                    break;
                }
                case QUERY_SUCCEED:
                {
                    fputs("Query succeeds.\n", stdout);
                    fprintf(stdout, "The distance between %s and %s is %.2lf km\n", queried_cities[0].city, \
                            queried_cities[1].city, calculate_distance(queried_cities));
                    record = 0;
                }
                default: break;
            }
        }
        memset(command, 0, sizeof(command));
    }
    return 0;
}

int read_data(char filename[])
{
    FILE* input_file  = NULL;
    if ((input_file = fopen(filename, "r")))
    {
        int count = 0;
        const char* delimiter = ",";
        char line[BUF_LEN];
        char *rest;
        char *token;
        for (rest = token = NULL, memset(line, 0, sizeof(BUF_LEN)); !feof(input_file); \
                ++count, memset(line, 0, sizeof(BUF_LEN)), rest = token = NULL)
        {
            fgets(line, BUF_LEN, input_file);
            if (strlen(line) == 0)
            {
                break;
            }
            if (count+1 > ARR_LEN)
            {
                fputs("No enough size to load data\n", stderr);
                return -1;
            }
            // get city name
            if((token = strtok_r(line, delimiter, &rest)))
            {
                if (strlen(token) >= STR_LEN)
                {
                    fputs("WARNING: No enough space to store city name\n", stderr);
                    return -1;
                }
                strcpy(cities[count].city, token);
            }
            // get country name
            if (rest[0] == ',')
            {
                strcpy(cities[count].country, "");
            }
            else if ((token = strtok_r(rest, delimiter, &rest)))
            {
                if (strlen(token) >= STR_LEN)
                {
                    fputs("WARNING: No enough space to store country name\n", stderr);
                    return -1;
                }
                strcpy(cities[count].country, token);
            }
            // get state name
            if ((token = strtok_r(rest, delimiter, &rest)))
            {
                if (strlen(token) >= STR_LEN)
                {
                    fputs("WARNING: No enough space to store state name\n", stderr);
                    return -1;
                }
                strcpy(cities[count].state, token);
            }
            // get latitude
            if ((token = strtok_r(rest, delimiter, &rest)))
            {
                cities[count].latitude = strtod(token, &token);
            }
            // get longitude
            if ((token = strtok_r(rest, delimiter, &rest)))
            {
                cities[count].longitude = strtod(token, &token);
            }
        }
    }
    else
    {
        perror("Error");
    }
    fputs("Read data ok.\n", stdout);
    return 0;
}

int query(char* command)
{
    command[strlen(command) - 1] = '\0';
    int indices[ARR_LEN];
    int count = search(command, indices);
    if (count == TOO_SHORTER)
    {
        fputs("Input length should not be shorter than 3 letters\n", stderr);
        return TOO_SHORTER;
    }
    else if (count == NOT_FOUND)
    {
        fputs("No such city\n", stderr);
        return NOT_FOUND;
    }
    else if (count == 1)
    {   // only one city matched
        queried_cities[record++] = cities[indices[0]];
        if (record > 1)
        {
            return QUERY_SUCCEED;
        }
    }
    else if (count > 1)
    {   // multiple cities matched
        fputs("Multiple cities match the input:\n", stdout);
        int i = 0;
        for (; i < count; ++i)
        {
            fprintf(stdout, "  %s\n", cities[indices[i]].city);
        }
        return MULTIPLE_MATCH;
    }
    return USER_CONTINUE;
}

int search(char* input, int indices[ARR_LEN])
{
    if (strlen(input) < 3)
    {
        return -1;
    }
    memset(indices, -1, sizeof(int)*ARR_LEN);
    int i = 0, j = 0;
    for (; i < ARR_LEN; ++i)
    {
        if (strncasecmp(input, cities[i].city, strlen(input)) == 0)
        {
            indices[j] = i;
            ++j;
        }
    }
    // 0 is not found, 1 means only one matches, >1 means more than one cities found
    return j; 
}

double calculate_distance(City queried_cities[2])
{
    City city_1 = queried_cities[0];
    City city_2 = queried_cities[1];
    double phi_1 = (90 - city_1.latitude) * PI / 180;
    double phi_2 = (90 - city_2.latitude) * PI / 180;
    double theta_1 = (city_1.longitude) * PI / 180;
    double theta_2 = (city_2.longitude) * PI / 180;
    double angle = sin(phi_1) * sin(phi_2) * cos(theta_1 - theta_2) + cos(phi_1) * cos(phi_2);
    double distance = R * acos(angle);
    return distance;
}