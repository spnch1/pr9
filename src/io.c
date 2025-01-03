#include "./include/io.h"
#include "./include/misc.h"
#include "./include/color.h"

#include <ctype.h>
#include <stdio.h>
#include <conio.h>

unsigned short getChoice(char *string, const unsigned char min, const unsigned char max) {
    unsigned short value = 0;
    do {
        printf("%s", string);

        value = getch();
        value = tolower(value);

        if (value < min || value > max) {
            printf("\n" ERR_MSG "Invalid choice. Press Enter to try again, Q to exit...\n");
            pressToExit();
        }
    } while (value < min || value > max);

    return value;
}

double getDouble(const char *string, double min, double max) {
    double result = 0;
    unsigned char isValid;

    do {
        isValid = 1;
        do {
            printf("\n%s [%g, %g]\n", string, min, max);

            if (scanf("%lf", &result) != 1) {
                printf(ERR_MSG "Invalid input. Press Enter to try again, Q to exit...\n");
                isValid = 0;
                fflush(stdin);
                pressToExit();
            }
        } while (isValid == 0);

        if (result < min || result > max) {
            printf(ERR_MSG "Number out of bounds. Press Enter to try again, Q to exit...\n");
            isValid = 0;
            pressToExit();
        }
    } while (isValid == 0);
    return result;
}