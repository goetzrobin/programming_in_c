#include <stdlib.h>
#include <stdio.h>

#include "../include/myheader.h"
#include "../include/boiling_points.h"

#define PERCENTAGE 3

void display_startup_banner(void);

int check_if_user_wants_to_continue(void);

double prompt_user_for_data(void);

int is_subsctance_within_x_percent(double substance_table_data, double user_data, int percentage);

double distance_from_boiling_point_in_percent(double substance_table_data, double user_data);

void print_result_with_data(double user_data, char *substance_table_name, double substance_table_data, int percentage);

void test_substance(int *substance_is_identified, char *substance_table_name, double substance_table_data, double user_data, int percentage);

/*
* Location:    Temple University Computer Science
* Programmer:  Robin Goetz
* Class:       Introduction to C Programming 1057  Fall 2018 Section 005
* Assignment:  Number 6 – Boiling Point
* Date:        08/10/2018
* Version:     1
* Description: Takes user input and determines if observation is within 3 percent of known
*              boiling point and returns identified substance or notice that substance is unidentified
*/
int main()
{

    double user_data;
    int substance_is_identified = 0;
    int percentage = PERCENTAGE;

    display_startup_banner();

    int counter = 0;

    while ( (user_data = prompt_user_for_data()) || user_data == 0)
    {
        // Test if substance if one of the specified values test_substance function will print if match is found
        test_substance(&substance_is_identified, "Carbon dioxide", CARBON_DIOXIDE, user_data, percentage);
        test_substance(&substance_is_identified, "Ammonia", AMMONIA, user_data, percentage);
        test_substance(&substance_is_identified, "Wax", WAX, user_data, percentage);
        test_substance(&substance_is_identified, "Water", WATER, user_data, percentage);
        test_substance(&substance_is_identified, "Olive Oil", OLIVE_OIL, user_data, percentage);
        test_substance(&substance_is_identified, "Mercury", MERCURY, user_data, percentage);
        test_substance(&substance_is_identified, "Sulfur", SULFUR, user_data, percentage);
        test_substance(&substance_is_identified, "Talc", TALC, user_data, percentage);
        test_substance(&substance_is_identified, "Silver", SILVER, user_data, percentage);
        test_substance(&substance_is_identified, "Copper", COPPER, user_data, percentage);
        test_substance(&substance_is_identified, "Gold", GOLD, user_data, percentage);
        test_substance(&substance_is_identified, "Iron", IRON, user_data, percentage);
        test_substance(&substance_is_identified, "Silicon", SILICON, user_data, percentage);

        // if no match is found let user know that no substance is found
        printf("%s", substance_is_identified ? "" : "\nThe substance is unidentified.\n\n");

        // Reset flag after running through tests
        substance_is_identified = 0;

        // check if user wants to continue to enter data or quit the program
         if(check_if_user_wants_to_continue() == 0) {
            break;
            }
    }
}

/*
* Function:     display_startup_banner()
* Programmer:   Robin Goetz
* Date:         09/25/2018
* Inputs:       none
* Outputs:      none
* Globals:      PRIME_PROGRAMMER - name of primary programmer
* Returns:      none
* Description:  Displays startup banner with basic information
*/
void display_startup_banner(void)
{
    puts("BOILING POINT");
    printf("\nProgramm written by %s. \n", PRIME_PROGRAMMER);
    printf("Program compiled on %s at %s. \n\n", __DATE__, __TIME__);
}

/*
* Function:     check_if_user_wants_to_continue()
* Programmer:   Robin Goetz
* Date:         09/25/2018
* Inputs:       none
* Outputs:      none
* Globals:      none
* Returns:      1 if user wants to continue, 0 if he wants to exit
* Description:  Prompts user to ask if he wants to continue or not
*/
int check_if_user_wants_to_continue(void) {
    char user_response;
    int wants_to_continue = 0;
    printf("\nDo you want to enter another Observation? [y/n]\t");
    scanf(" %c", &user_response);
    if(user_response == 'y') {
        puts("\nContinuing...\n");
        wants_to_continue = 1;
    } else {
        puts("\nGoodbye!\n");
        wants_to_continue = 0;
    }
    return wants_to_continue;
}

/*
* Function:     prompt_user_for_data()
* Programmer:   Robin Goetz
* Date:         09/25/2018
* Inputs:       none
* Outputs:      none
* Globals:      none
* Returns:      Data entered by user
* Description:  Prompts user for data and scans, returns value entered by user
*/
double prompt_user_for_data(void)
{
    double boiling_point;

    printf("PLEASE ENTER BOILING POINT DATA: \t");
    scanf("%lf", &boiling_point);
    printf("You entered the following boiling point:\t %.2lf.\n", boiling_point);

    return boiling_point;
}

/*
* Function:     prompt_user_for_data()
* Programmer:   Robin Goetz
* Date:         09/25/2018
* Inputs:       none
* Outputs:      none
* Globals:      none
* Returns:      Data entered by user
* Description:  Prompts user for data and scans, returns value entered by user
*/
int is_subsctance_within_x_percent(double substance_table_data, double user_data, int percentage)
{
    double percent = percentage / 100.00;
    double lower_limit = substance_table_data - percent * substance_table_data;
    double upper_limit = substance_table_data + percent * substance_table_data;

    if (user_data < 0)
    {
        // for negative values the absolute upper limit is smaller (more negative) than the lower limit
        // thus the two limits are reversed
        return (upper_limit <= user_data) && (user_data <= lower_limit);
    }
    else
    {
        return (lower_limit <= user_data) && (user_data <= upper_limit);
    }
}

/*
* Function:     prompt_user_for_data()
* Programmer:   Robin Goetz
* Date:         09/25/2018
* Inputs:       none
* Outputs:      none
* Globals:      none
* Returns:      Data entered by user
* Description:  Prompts user for data and scans, returns value entered by user
*/
double distance_from_boiling_point_in_percent(double substance_table_data, double user_data)
{
    double distance = user_data - substance_table_data;
    double distance_in_percent = distance / substance_table_data * 100.00;
    return distance_in_percent;
}

/*
* Function:     prompt_user_for_data()
* Programmer:   Robin Goetz
* Date:         09/25/2018
* Inputs:       none
* Outputs:      none
* Globals:      none
* Returns:      Data entered by user
* Description:  Prompts user for data and scans, returns value entered by user
*/
void print_result_with_data(double user_data, char *substance_table_name, double substance_table_data, int percentage)
{
    printf("\nYou entered a boiling point of %.2lf, which is within %d%% of the substance \"%s\".\n%.2lf is %.2lf%% away from the reference temperature of %.2lf for \"%s\".\n\n",
           user_data, percentage, substance_table_name, user_data, distance_from_boiling_point_in_percent(substance_table_data, user_data), substance_table_data, substance_table_name);
}

/*
* Function:     prompt_user_for_data()
* Programmer:   Robin Goetz
* Date:         09/25/2018
* Inputs:       none
* Outputs:      none
* Globals:      none
* Returns:      Data entered by user
* Description:  Prompts user for data and scans, returns value entered by user
*/
void test_substance(int *substance_is_identified, char *substance_table_name, double substance_table_data, double user_data, int percentage)
{
    int is_within_x_percent = is_subsctance_within_x_percent(substance_table_data, user_data, percentage);

    if (is_within_x_percent)
    {
        print_result_with_data(user_data, substance_table_name, substance_table_data, percentage);
        *substance_is_identified = is_within_x_percent;
    }
}