#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string.h>

using namespace std;

int main(int argc, char **argv) {

    FILE *f;
    f = fopen(argv[1], "r");
    fseek(f, 0L, SEEK_END); 
    int len = ftell(f); 
    rewind(f);
    char c, buffer[len];    
    int i = 0;
    while( fread(&c, sizeof(char), 1, f) > 0 ) buffer[i++] = c;
    fclose(f);
    buffer[i] = '\0';
    
    i = 0;
    char curr = buffer[i];
    while(curr) {
        printf("%c\n", curr);
        i++;
        curr = buffer[i];
    }
    
    return 0;

}
