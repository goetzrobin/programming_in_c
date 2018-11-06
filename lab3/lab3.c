#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STUDENT_NAME "Robin Goetz"

void display_startup_banner();

double promt_and_get_number();

long double calculate_gospers_algorithm();

/*
* Location:    Temple University Computer Science
* Programmer:  Robin Goetz
* Class:       Introduction to C Programming 1057  Fall 2018 Section 005
* Assignment:  Program to estimate the value of a factorial using Gosper's algorithm
* Date:        9/11/2018
* Version:       1
* Description: Program uses Gospers algorithm to estimate the factorial value of a user entered number.
*/

int main() {

    double number_entered_by_user;
    long double estimated_result;

    display_startup_banner();

    number_entered_by_user = promt_and_get_number();

    printf("\nYou entered the following number: %d. \n", (int) number_entered_by_user);
    
    puts("\nStarting calculation now...\n");

    estimated_result = calculate_gospers_algorithm(number_entered_by_user);

    printf("The estimated result is %Lf.\n", estimated_result);

    return EXIT_SUCCESS;
}




/*
* Function: display_startup_banner()
* Description: Displays introductory text and name of Programmer
* Author: Robin Goetz
* Date: 9/11/2018
* Inputs: none
* Outputs: Introductory text
* Globals: none
* Returns: none */

void display_startup_banner( void ) {
    puts("ESTIMATE A FACTORIAL VALUE WITHOUT ACTUALLY CALCULATING IT");
    printf("This program was written by %s. \n\n", STUDENT_NAME);
    puts("It will estimate the value of \"n!\" using Gosper's algorithm");
    return;
}


/*
* Function: promt_and_get_number()
* Description: Prompts user to enter a factorial value they want to be estimated
*               and gets the user input
* Author: Robin Goetz
* Date: 9/11/2018
* Inputs: none
* Outputs: Prompt to tell user to enter value to be estimated
* Globals: none
* Returns: Number entered by User */

double promt_and_get_number( void ) {

    double user_entered_value;

    printf("Please enter a factorial value to estimate: \t");
    scanf("%lf", &user_entered_value);

     return user_entered_value;
}


/*
* Function: calculate_gospers_algorithm(double n)
* Description: Calculates an estimate of n factorial and prints intermediate values
* Author: Robin Goetz
* Date: 9/11/2018
* Inputs: Factorial number to be estimated
* Outputs: Intermediate results of estimation
* Globals: none
* Returns: estimated result
*/

long double calculate_gospers_algorithm(double n) {
    long int n_to_the_nth_power;
    long double e_to_the_negative_nth_power;
    long double two_n_plus_one_third;
    long double two_n_plus_one_third_times_pi;
    long double square_root;
    long double result;


    puts("Calculating n to the n-th power");
    n_to_the_nth_power = pow(n,n);
    printf("Result: %ld. \n\n", n_to_the_nth_power);

    puts("Calculating e to the negative n-th power");
    e_to_the_negative_nth_power = pow(M_E, -n);
    printf("Result: %Lf. \n\n", e_to_the_negative_nth_power);

    puts("Calculating 2n + 1/3");
    two_n_plus_one_third = (2 * n) + (1.0/3.0);
    printf("Result: %Lf. \n\n", two_n_plus_one_third);

    puts("Calculating 2n + 1/3 times PI");
    two_n_plus_one_third_times_pi = two_n_plus_one_third * M_PI;
    printf("Result: %Lf. \n\n", two_n_plus_one_third_times_pi);


    puts("Taking the Square Root of the previous value");
    square_root = sqrt(two_n_plus_one_third_times_pi);
    printf("Result: %Lf. \n\n", square_root);

    puts("Calculating final result");
    result = n_to_the_nth_power * e_to_the_negative_nth_power * square_root;
    printf("Result: %Lf. \n\n", result);

    return result;
}