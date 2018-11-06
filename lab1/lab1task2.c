#include <stdio.h>
#include <stdlib.h>


/*
* Location:    Temple University Computer Science
* Programmer:  Robin Goetz
* Class:       Introduction to C Programming 1057  Fall 2018 Section 005
* Assignment:  Number 1–Calculate Sum and Difference.
* Date:        08/28/2018
* Version:       1
* Description:	Add two numbers together and print their sum.
*		Subtract two numbers from each other and print difference. 
*		Multiply two numbers and print product.
*/

int main() {

	int first_number;
	int second_number;

	int sum;
	int difference;
	int product;

	printf("Enter your first number: ");
	scanf("%d", &first_number);

	printf("Enter your second number: ");
	scanf("%", second_number);	

	sum = first_number + second_number;
	printf("The sum of %d and %d is %d.\n", first_number, second_number, sum);

	difference = first_number - second_number;
        printf("The difference between %d and %d is %d. \n" , first_number, second_number, difference);


	product = first_number * second_number;
	printf("The product of %d and %d is %d. \n", first_number, second_number, product);

	return EXIT_SUCCESS;
}
