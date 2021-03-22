#include<stdio.h>
#include<stdlib.h>
#include<time.h>


int main(void)
{
    srand(time(NULL));

    int max;
    int min;
    int r;
    double max_double;
    double min_double;
    double r_double;

    while(1)
    {

        printf("Enter min value: ");
        scanf("%d", &min);

        printf("Enter max value: ");
        scanf("%d", &max);
        if (min < max)
            break;
        printf("The minimum cannot be superior or equal to the maximum.\n");
    }

    while(1)
    {

        printf("Enter min_double value: ");
        scanf("%lf", &min_double);

        printf("Enter max_double value: ");
        scanf("%lf", &max_double);

        if (min < max)
            break;
        printf("The minimum cannot be superior or equal to the maximum.\n");
    }
    FILE *file = fopen("save.txt", "w+");

    for (int i = 0; i < 20; i++)
    {
        r = rand();
        r = r % (max+1 - min) + min;
        r_double = (double) rand() / ((double) RAND_MAX + 1);
        r_double = r_double * (max_double - min_double) + min_double;
        fprintf(file, "%d %lf\n", r, r_double);
    }
    fclose(file);
    return 0;
}
