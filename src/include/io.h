#ifndef IO_H
#define IO_H

#define MAX_NAME_LENGTH 100

typedef struct {
    char region_name[MAX_NAME_LENGTH];
    float area;
    int population;
} Record;

unsigned short getChoice(char *string, const unsigned char min, const unsigned char max);
double getDouble(const char *string, double min, double max);

#endif //IO_H
