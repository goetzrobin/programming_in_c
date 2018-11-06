#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PRIME_PROGRAMMER "Robin Goetz"

void display_startup_banner(void);

int getNumberFromUser(void);

double predictFluCases(int day_from_first_report);

/*
* Location:    Temple University Computer Science
* Programmer:  Robin Goetz
* Class:       Introduction to C Programming 1057  Fall 2018 Section 005
* Assignment:  Number 4 – Flu Case Predictor
* Date:        09/19/2018
* Version:       1
* Description: Implements an algorithm that predicts the number of flu cases based on days since first outbreak
*/

int main()
{

    display_startup_banner();

    //Iteration number 1
    int days_from_user_1;
    int predicted_result_1;

    printf("\nEnter first of three days to check: ");
    days_from_user_1 = getNumberFromUser();
    predicted_result_1 = predictFluCases(days_from_user_1);

    printf("By day %d, our model predicts %d cases will be present.\n\n", days_from_user_1, predicted_result_1);

    //Iteration number 2
    int days_from_user_2;
    int predicted_result_2;

    printf("\nEnter second of three days to check: ");
    days_from_user_2 = getNumberFromUser();
    predicted_result_2 = predictFluCases(days_from_user_2);

    printf("By day %d, our model predicts %d cases will be present.\n\n", days_from_user_2, predicted_result_2);

    //Iteration number 3
    int days_from_user_3;
    int predicted_result_3;

    printf("\nEnter third of three days to check: ");
    days_from_user_3 = getNumberFromUser();
    predicted_result_3 = predictFluCases(days_from_user_3);

    printf("By day %d, our model predicts %d cases will be present.\n\n", days_from_user_3, predicted_result_3);

    puts("\nThank you for testing our flu function.\n");

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

void display_startup_banner(void)
{
    puts("FLU EPIDEMIC PREDICTIONS BASED ON\nELAPSED DAYS SINCE FIRST REPORTED CASE");
    printf("\nProgramm written by %s. \n", PRIME_PROGRAMMER);
    printf("Program compiled on %s at %s. \n\n", __DATE__, __TIME__);
}

/*
* Function: getNumberFromUser()
* Programmer: Robin Goetz
* Date: 9/19/2018
* Inputs: * none *
* Outputs: * none *
* Globals: * none *
* Returns: Number read in from keyboard.
* Description: Reads in number from user and returns it.
*/

int getNumberFromUser(void)
{
    int entered_number;
    scanf("%d", &entered_number);
    return entered_number;
}

/*
* Function: predictFluCases( int days_from_first_report )
* Programmer: Robin Goetz
* Date: 9/19/2018
* Inputs: Integer value of days since first outbreak
* Outputs: * none *
* Globals: * none *
* Returns: Prediction of Flu Cases on the entered day
* Description: Implements algorithm developed by Math Professor to predict number of flu cases after 
*              specified number of days.
*/

double predictFluCases(int days_from_first_report)
{

    double nominator = 40000.00;
    double exponent = -0.24681 * days_from_first_report;
    double e_power = pow(M_E, exponent);
    double denominator = 1.00 + 39999.00 * e_power;

    return (nominator / denominator);
}
