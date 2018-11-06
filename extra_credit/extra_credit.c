#include <stdlib.h>
#include <stdio.h>

char *get_direction( char first, char second);

int main() {
    // char first,second;
    // printf("\nDirection of travel ( 2 characters): ");
    // scanf("%c%c", &first,&second );
    // printf("\nYou are going %s\n",get_direction(first,second));


    printf("%06d %06d %06d\n",78,94843,3);
    printf("%06d %06d %06d\n",123,14,8582);
    printf("%06d %06d %06d\n",3214,113491,788);
}

char *get_direction( char first, char second) {
    char *return_value = "Nowhere!";
    switch (first) {
        case 'n' : {
            switch (second) {
                case 'n': return_value = "North."; break;
                case 's': return_value = "Northsouth."; break;
                case 'e': return_value = "Northeast."; break;
                case 'w': return_value = "Northwest."; break;
            }
            break;
        }
        case 's' : {
            switch (second) {
                case 'n': return_value = "Southnorth."; break;
                case 's': return_value = "South."; break;
                case 'e': return_value = "Southeast."; break;
                case 'w': return_value = "Southwest."; break;
            }
            break;
        }
        case 'e' : {
            switch (second) {
                case 'n': return_value = "Northeast."; break;
                case 's': return_value = "Southeast."; break;
                case 'e': return_value = "East."; break;
                case 'w': return_value = "Eastwest."; break;
            }
            break;
        }
        case 'w' : {
            switch (second) {
                case 'n': return_value = "Northwest."; break;
                case 's': return_value = "Southwest."; break;
                case 'e': return_value = "Westeast."; break;
                case 'w': return_value = "West."; break;
            }
            break;
        }
    }


    return return_value;


}