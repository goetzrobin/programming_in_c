#include <stdio.h>
#include <stdlib.h>

#define REIMBURSMENT_RATE_PER_MILE 0.35

/*
 * Location: Temple University Computer Science
 * Programmer: Robin Goetz
 * Class: Introduction to C Programming 1057 Fall 2018 Section 005
 * Assignment: 2 - odometer calculations
 * Date: September 1, 2018 
 * Version: 1
 * Description: Given a starting and ending odometer reading, 
 *              calculate a mileage reimbursement amount in  
 *              dollars and cents for the distance driven.
 */

int main() {
	float beginning_mileage;
	float ending_mileage;
	float difference;
	float reimbursement;

	puts("MILEAGE REIMBURSMENT CALCULATOR");
	
	printf("Enter beginning odometer reading=>\t");
	scanf("%f",&beginning_mileage);
	
	printf("Enter ending odometer reading=>\t");
	scanf("%f", &ending_mileage);

	difference = ending_mileage - beginning_mileage;
	reimbursement = difference * REIMBURSMENT_RATE_PER_MILE;
	
	printf("You traveled %.1f miles. At $%.2f per mile, your reimbursment is $%.2f. \n",
		difference,REIMBURSMENT_RATE_PER_MILE,reimbursement);

	return EXIT_SUCCESS;
}
