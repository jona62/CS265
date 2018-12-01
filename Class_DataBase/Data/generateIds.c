#include "functions.h"

char LIST_OF_IDS[] = "listOfUserIds.txt";

void makeUserNames() {
    FILE *file = fopen(LIST_OF_IDS, "w");
    int i, id = 10000;
    for(i=0; i<50; i++) {
        fprintf(file, "MEC%d\n", id);
        id++;
    }
    fclose(file);
}

int main() {
    makeUserNames();
}