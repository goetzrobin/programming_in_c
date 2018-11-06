#include <stdlib.h>
#include <stdio.h>

#define PRIME_PROGRAMMER "Robin Goetz"

void display_startup_banner(void);

double prompt_user_for_amount(void);

void calculate_change(double dollar_amount, int *twenty_dollars, int *ten_dollars, int *five_dollars, int *dollars, int *quarters, int *nickels, int *dimes, int *pennies);

void print_change(int twenty_dollars, int ten_dollars, int five_dollars, int dollars, int quarters, int nickels, int dimes, int pennies);

double get_twenty_dollars( double dollar_amount,int *twenty_dollars);

double get_ten_dollars( double dollar_amount,int *ten_dollars);

double get_five_dollars( double dollar_amount,int *five_dollars);

double get_one_dollars( double dollar_amount,int *dollars);

double get_quarters( double dollar_amount,int *quarters);

double get_dimes( double dollar_amount,int *dimes);

double get_nickels( double dollar_amount,int *nickels);

double get_pennies( double dollar_amount,int *pennies);


/*
* Location:    Temple University Computer Science
* Programmer:  Robin Goetz
* Class:       Introduction to C Programming 1057  Fall 2018 Section 005
* Assignment:  Number 5 – Change Management
* Date:        09/25/2018
* Version:     1
* Description: Receive Dollar Amount and calculate change using standard U.S. denominations
*              of pennies, nickels, dimes, quarters, dollar bills, five-dollar bills, tens, and twenties
*/

int main()
{

    double user_dollar_amount;

    int twenty_dollars;
    int ten_dollars;
    int five_dollars;
    int dollars;
    int quarters;
    int nickels;
    int dimes;
    int pennies;


    display_startup_banner();

    user_dollar_amount = prompt_user_for_amount();

    printf("Amount entered: %.2lf\n", user_dollar_amount);

    calculate_change( user_dollar_amount, &twenty_dollars, &ten_dollars, &five_dollars, &dollars, &quarters, &dimes, &nickels, &pennies);

    print_change(twenty_dollars, ten_dollars, five_dollars, dollars, quarters, dimes, nickels, pennies);

    return EXIT_SUCCESS;
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
    puts("PROCESS CASH CHANGE");
    printf("\nProgramm written by %s. \n", PRIME_PROGRAMMER);
    printf("Program compiled on %s at %s. \n\n", __DATE__, __TIME__);
}

/*
* Function:     prompt_user_for_amount()
* Programmer:   Robin Goetz
* Date:         09/25/2018
* Inputs:       none
* Outputs:      none
* Globals:      none
* Returns:      Amount entered by user
* Description:  Prompts user for amount and scans, returns value entered by user
*/

double prompt_user_for_amount(void)
{
    double dollar_amount;

    printf("PLEASE ENTER DOLLAR AMOUNT: \t");
    scanf("%lf", &dollar_amount);

    return dollar_amount;
}

/*
* Function:     calculate_change()
* Programmer:   Robin Goetz
* Date:         09/25/2018
* Inputs:       User entered dollar amount to calculate change
* Outputs:      Number of twenty, ten, five, one dollar bills as well as quarters, dimes, nickles and pennies
* Globals:      none
* Returns:      none
* Description:  Calulates amount of different denominations of bills/coins needed to
*               return user entered dollar amount
*/
void calculate_change(double dollar_amount, int *twenty_dollars, int *ten_dollars, int *five_dollars, int *dollars, int *quarters, int *dimes, int *nickels, int *pennies)
{

    dollar_amount  = get_twenty_dollars(dollar_amount, twenty_dollars);
    printf("\nAmount left: %lf\n", dollar_amount);

    dollar_amount = get_ten_dollars(dollar_amount, ten_dollars);
    printf("\nAmount left: %lf\n", dollar_amount);

    dollar_amount = get_five_dollars(dollar_amount, five_dollars);
    printf("\nAmount left: %lf\n", dollar_amount);

    dollar_amount = get_one_dollars(dollar_amount, dollars);
    printf("\nAmount left: %lf\n", dollar_amount);

    dollar_amount = get_quarters(dollar_amount, quarters);
    printf("\nAmount left: %lf\n", dollar_amount);

    dollar_amount = get_dimes(dollar_amount, dimes);
    printf("\nAmount left: %lf\n", dollar_amount);

    dollar_amount = get_nickels(dollar_amount, nickels);
    printf("\nAmount left: %lf\n", dollar_amount);

    dollar_amount = get_pennies(dollar_amount, pennies);
    printf("\nAmount left: %lf\n", dollar_amount);
}

/*
* Function:     get_twenty_dollars()
* Programmer:   Robin Goetz
* Date:         09/25/2018
* Inputs:       Dollar amount for which to be determined how many twenties have to be returned
* Outputs:      Number of twenty dollar bills to be returned as change
* Globals:      none
* Returns:      Amount left after twenties are set aside
* Description:  Takes in dollar amount and specifies how many twenty dollar bills are to be returned as change
*/
double get_twenty_dollars( double dollar_amount,int *twenty_dollars) {

    int bill_value = 20;
    int count_bill = 0;
    double amount_left;

    count_bill = ((int) dollar_amount) / bill_value;

    *twenty_dollars = count_bill;

    amount_left = dollar_amount - (count_bill * bill_value);
    return amount_left;
}

/*
* Function:     get_ten_dollars()
* Programmer:   Robin Goetz
* Date:         09/25/2018
* Inputs:       Dollar amount for which to be determined how many tens have to be returned
* Outputs:      Number of ten dollar bills to be returned as change
* Globals:      none
* Returns:      Amount left after tens are set aside
* Description:  Takes in dollar amount and specifies how many ten dollar bills are to be returned as change
*/
double get_ten_dollars( double dollar_amount,int *ten_dollars) {
    int bill_value = 10;
    int count_bill = 0;
    double amount_left;

    count_bill = (int) dollar_amount / bill_value;
    *ten_dollars = count_bill;

    amount_left = dollar_amount - (count_bill * bill_value);
    return amount_left;
}

/*
* Function:     get_five_dollars()
* Programmer:   Robin Goetz
* Date:         09/25/2018
* Inputs:       Dollar amount for which to be determined how many fives have to be returned
* Outputs:      Number of five dollar bills to be returned as change
* Globals:      none
* Returns:      Amount left after fives are set aside
* Description:  Takes in dollar amount and specifies how many five dollar bills are to be returned as change
*/
double get_five_dollars( double dollar_amount,int *five_dollars) {
    int bill_value = 5;
    int count_bill = 0;
    double amount_left;

    count_bill = (int) dollar_amount / bill_value;
    *five_dollars = count_bill;

    amount_left = dollar_amount - (count_bill * bill_value);
    return amount_left;
}

/*
* Function:     get_one_dollars()
* Programmer:   Robin Goetz
* Date:         09/25/2018
* Inputs:       Dollar amount for which to be determined how many ones have to be returned
* Outputs:      Number of one dollar bills to be returned as change
* Globals:      none
* Returns:      Amount left after ones are set aside
* Description:  Takes in dollar amount and specifies how many one dollar bills are to be returned as change
*/
double get_one_dollars( double dollar_amount,int *dollars) {
    int bill_value = 1;
    int count_bill = 0;
    double amount_left;

    count_bill = (int) dollar_amount / bill_value;
    *dollars = count_bill;

    amount_left = dollar_amount - (count_bill * bill_value);
    return amount_left;
}

/*
* Function:     get_quarters()
* Programmer:   Robin Goetz
* Date:         09/25/2018
* Inputs:       Dollar amount for which to be determined how many quarters have to be returned
* Outputs:      Number of quarters to be returned as change
* Globals:      none
* Returns:      Amount left after quarters are set aside
* Description:  Takes in dollar amount and specifies how many quarters are to be returned as change
*/
double get_quarters( double dollar_amount,int *quarters) {
    int amount_in_cents = dollar_amount * 100.0001;
    int coin_value = 25;
    int count_coin = 0;
    double amount_left;

    count_coin = (int) amount_in_cents / coin_value;
    *quarters = count_coin;

    amount_left = amount_in_cents - (count_coin * coin_value);
    return (amount_left / 100);
}

/*
* Function:     get_dimes()
* Programmer:   Robin Goetz
* Date:         09/25/2018
* Inputs:       Dollar amount for which to be determined how many dimes have to be returned
* Outputs:      Number of dimes to be returned as change
* Globals:      none
* Returns:      Amount left after dimes are set aside
* Description:  Takes in dollar amount and specifies how many dimes are to be returned as change
*/
double get_dimes( double dollar_amount,int *dimes) {
    int amount_in_cents = dollar_amount * 100.0001;
    int coin_value = 10;
    int count_coin = 0;
    double amount_left;

    count_coin = (int) amount_in_cents / coin_value;
    *dimes = count_coin;

    amount_left = amount_in_cents - (count_coin * coin_value);
    return (amount_left / 100);
}

/*
* Function:     get_nickels()
* Programmer:   Robin Goetz
* Date:         09/25/2018
* Inputs:       Dollar amount for which to be determined how many nickels have to be returned
* Outputs:      Number of nickels to be returned as change
* Globals:      none
* Returns:      Amount left after nickels are set aside
* Description:  Takes in dollar amount and specifies how many nickels are to be returned as change
*/
double get_nickels( double dollar_amount,int *nickels) {
    int amount_in_cents = dollar_amount * 100.0001;
    int coin_value = 5;
    int count_coin = 0;
    double amount_left;

    count_coin = (int) amount_in_cents / coin_value;
    *nickels = count_coin;

    amount_left = amount_in_cents - (count_coin * coin_value);
    return (amount_left / 100);
}

/*
* Function:     get_pennies()
* Programmer:   Robin Goetz
* Date:         09/25/2018
* Inputs:       Dollar amount for which to be determined how many pennies have to be returned
* Outputs:      Number of pennies to be returned as change
* Globals:      none
* Returns:      Amount left after pennies are set aside
* Description:  Takes in dollar amount and specifies how many pennies are to be returned as change
*/
double get_pennies( double dollar_amount,int *pennies) {
    int amount_in_cents = dollar_amount * 100.0001;
    int coin_value = 1;
    int count_coin = 0;
    double amount_left;

    count_coin = (int) amount_in_cents / coin_value;
    *pennies = count_coin;

    amount_left = amount_in_cents - (count_coin * coin_value);
    return (amount_left / 100);
}

/*
* Function:     print_change()
* Programmer:   Robin Goetz
* Date:         09/25/2018
* Inputs:       Amount of twenty, ten, five, one dollar bills and quarters, dimes, nickles and pennies to be returned as change
* Outputs:      none
* Globals:      none
* Returns:      none
* Description:  Prints calculated amount of bills and coins to the command line
*/
void print_change(int twenty_dollars, int ten_dollars, int five_dollars, int dollars, int quarters, int dimes, int nickels, int pennies)
{
    printf("\nTWENTY DOLLAR BILLS: \t%d\n", twenty_dollars);

    printf("TEN DOLLAR BILLS: \t%d\n", ten_dollars);

    printf("FIVE DOLLAR BILLS: \t%d\n", five_dollars);

    printf("ONE DOLLAR BILLS: \t%d\n", dollars);

    printf("QUARTERS: \t\t%d\n", quarters);

    printf("DIMES: \t\t\t%d\n", dimes);

    printf("NICKLES: \t\t%d\n", nickels);

    printf("PENNIES: \t\t%d\n\n", pennies);
}