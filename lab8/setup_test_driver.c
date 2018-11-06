#include <stdio.h>
#include <stdlib.h>

// Simple driver to test out reading in data from the latest omr file
// and printing out the data read in by columns.

#define LIMIT_TO_READING_LINES 30
#define NUMBER_OF_QUESTIONS_PER_STUDENT 11
#define ERROR_CODE_IN_INPUT_SCANNING 'e'

void processOMRData( char *fname );
void printSingleEntry( int id, char scores[] );

int main()
{
	processOMRData( "newomr.txt" );   // probably want to prompt for this name.

	return EXIT_SUCCESS;
}


void processOMRData( char *fname )
{
	FILE *IN = fopen( fname, "r" );
	int id;
	char scores[ NUMBER_OF_QUESTIONS_PER_STUDENT ];
	int count = 0;
	int i;

	if ( ! IN ) {
		printf( "Error opening input file %s.\n", fname );
		perror( fname );
		return;
	}

	while ( fscanf( IN, "%d", &id ) == 1 ) {
		count++;
		printf( "Response %d, ID = %d.\n", count, id );
		for ( i = 0; i < NUMBER_OF_QUESTIONS_PER_STUDENT; i++ ) {
			fscanf( IN, "%c", &scores[ i ] );
			printf( "(%d) %d. >%c<\n", count, i, scores[ i ] );
		}
		printSingleEntry( id, scores );
		if ( count >= LIMIT_TO_READING_LINES ) 
			break;
	}
}


void printSingleEntry( int id, char scores[] )
{
	int i; 

	printf( "ID='%5.5d'  ", id );
	for ( i = 0; i < NUMBER_OF_QUESTIONS_PER_STUDENT; i++ )
		printf( "'%c'  ", scores[ i ] );
	puts("");
	puts("-------------------" );
}
