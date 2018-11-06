#include <stdio.h>
#include <stdlib.h>

#define PI_VALUE 3.14159265

/*
* Location:    Temple University Computer Science
* Programmer:  Robin Goetz
* Class:       Introduction to C Programming 1057  Fall 2018 Section 005
* Assignment:  Number 1–Calculate Sum and Difference.
* Date:        08/28/2018
* Version:       1
* Description: Take in radius and calculate area and circumfence and print results to console
*/

int main() {
	// Declare 3 floating-point variables to hold our calculations
	double radius;
	double circumfence;
	double area;

	//Input the required data to perform calculation
	printf("Enter the radius: ");		// Prompting Message
	scanf("%lf", &radius);		// Read input into variable

	// Compute area and circumfence
	area = radius * radius * PI_VALUE;
	circumfence = 2 * radius * PI_VALUE;

	// Output the results
	printf("The circle radius is\t %lf. \n", radius);
	printf("The calculated area is\t %lf. \n", area);
	printf("The circumfence is\t %lf. \n", circumfence);

	return EXIT_SUCCESS;	
}
