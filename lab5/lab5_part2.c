#include <stdlib.h>
#include <stdio.h>

#define NO_MISSING 0
#define MISSING_PENNIES 1
#define MISSING_NICKELS 2
#define MISSING_DIMES 3
#define MISSING_QUARTERS 4
#define MISSING_DOLLARS 5
#define MISSING_FIVES 6
#define MISSING_TENS 7
#define MISSING_TWENTIES 8

#define PRIME_PROGRAMMER "Robin Goetz"

void display_startup_banner(void);

double prompt_user_for_amount(void);

int prompt_user_for_shortage(char *prompt);

void calculate_change(double user_amount, int *twenty_dollars, int *ten_dollars, int *five_dollars, int *dollars, int *quarters, int *dimes, int *nickels, int *pennies, int shortage_id_1, int shortage_id_2, int shortage_id_3);

void print_change(int twenty_dollars, int ten_dollars, int five_dollars, int dollars, int quarters, int nickels, int dimes, int pennies, int shortage_id_1, int shortage_id_2, int shortage_id_3);

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
*              allow user to enter which denominations are not available and adjust result
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

    int shortage_id_1;
    int shortage_id_2;
    int shortage_id_3;

    display_startup_banner();

    user_dollar_amount = prompt_user_for_amount();

    shortage_id_1 = prompt_user_for_shortage("\nEnter Shortage of Bills and Coins\n0 - NO MISSING\n1 - MISSING PENNIES\n2 - NO NICKELS\n3 - MISSING DIMES\n4 - NO QUARTERS\n5 - MISSING DOLLARS\n6 - NO FIVE DOLLARS\n7 - MISSING TEN DOLLARS\n8 - MISSING TWENTY DOLLARS\nMISSING: ");

    shortage_id_2 = prompt_user_for_shortage("\nEnter Shortage of Bills and Coins\n0 - NO MISSING\n1 - MISSING PENNIES\n2 - NO NICKELS\n3 - MISSING DIMES\n4 - NO QUARTERS\n5 - MISSING DOLLARS\n6 - NO FIVE DOLLARS\n7 - MISSING TEN DOLLARS\n8 - MISSING TWENTY DOLLARS\nMISSING: ");

    shortage_id_3 = prompt_user_for_shortage("\nEnter Shortage of Bills and Coins\n0 - NO MISSING\n1 - MISSING PENNIES\n2 - NO NICKELS\n3 - MISSING DIMES\n4 - NO QUARTERS\n5 - MISSING DOLLARS\n6 - NO FIVE DOLLARS\n7 - MISSING TEN DOLLARS\n8 - MISSING TWENTY DOLLARS\nMISSING: ");

    printf("\n\nAmount entered: %.2lf\n", user_dollar_amount);

    calculate_change(user_dollar_amount, &twenty_dollars, &ten_dollars, &five_dollars, &dollars, &quarters, &dimes, &nickels, &pennies, shortage_id_1, shortage_id_2, shortage_id_3);

    print_change(twenty_dollars, ten_dollars, five_dollars, dollars, quarters, dimes, nickels, pennies, shortage_id_1, shortage_id_2, shortage_id_3);

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
* Function:     prompt_user_for_shortage()
* Programmer:   Robin Goetz
* Date:         09/25/2018
* Inputs:       String to be displayed when user is prompted
* Outputs:      none
* Globals:      none
* Returns:      Id entered by user
* Description:  Prompts user for shortage and scans, returns id of denomination entered by user
*/

int prompt_user_for_shortage(char *prompt)
{
    int denomination_id;

    printf("%s",prompt);
    scanf("%d", &denomination_id);

    return denomination_id;
}

/*
* Function:     calculate_change()
* Programmer:   Robin Goetz
* Date:         09/25/2018
* Inputs:       User entered dollar amount to calculate change
* Outputs:      Number of twenty, ten, five, one dollar bills as well as quarters, dimes, nickles and pennies as well as ids of denominations, which are unavailable
* Globals:      none
* Returns:      none
* Description:  Calulates amount of different denominations of bills/coins needed to
*               return user entered dollar amount and adjusts for unavailable denominations
*/
void calculate_change(double user_amount, int *twenty_dollars, int *ten_dollars, int *five_dollars, int *dollars, int *quarters, int *dimes, int *nickels, int *pennies, int shortage_id_1, int shortage_id_2, int shortage_id_3)
{

    if (shortage_id_1 != MISSING_TWENTIES && shortage_id_2 != MISSING_TWENTIES && shortage_id_3 != MISSING_TWENTIES)
    {
        user_amount = get_twenty_dollars(user_amount, twenty_dollars);
    }
    printf("\nAmount left: %lf\n", user_amount);

    if (shortage_id_1 != MISSING_TENS && shortage_id_2 != MISSING_TENS && shortage_id_3 != MISSING_TENS)
    {

        user_amount = get_ten_dollars(user_amount, ten_dollars);
    }
    printf("\nAmount left: %lf\n", user_amount);

    if (shortage_id_1 != MISSING_FIVES && shortage_id_2 != MISSING_FIVES && shortage_id_3 != MISSING_FIVES)
    {

        user_amount = get_five_dollars(user_amount, five_dollars);
    }
    printf("\nAmount left: %lf\n", user_amount);

    if (shortage_id_1 != MISSING_DOLLARS && shortage_id_2 != MISSING_DOLLARS && shortage_id_3 != MISSING_DOLLARS)
    {

        user_amount = get_one_dollars(user_amount, dollars);
    }
    printf("\nAmount left: %lf\n", user_amount);

    if (shortage_id_1 != MISSING_QUARTERS && shortage_id_2 != MISSING_QUARTERS && shortage_id_3 != MISSING_QUARTERS)
    {

        user_amount = get_quarters(user_amount, quarters);
    }
    printf("\nAmount left: %lf\n", user_amount);

    if (shortage_id_1 != MISSING_DIMES && shortage_id_2 != MISSING_DIMES && shortage_id_3 != MISSING_DIMES)
    {
        user_amount = get_dimes(user_amount, dimes);
    }
    printf("\nAmount left: %lf\n", user_amount);

    if (shortage_id_1 != MISSING_NICKELS && shortage_id_2 != MISSING_NICKELS && shortage_id_3 != MISSING_NICKELS)
    {
        user_amount = get_nickels(user_amount, nickels);
    }
    printf("\nAmount left: %lf\n", user_amount);

    if (shortage_id_1 != MISSING_PENNIES && shortage_id_2 != MISSING_PENNIES && shortage_id_3 != MISSING_PENNIES)
    {
        user_amount = get_pennies(user_amount, pennies);
    }
    printf("\nAmount left: %lf\n", user_amount);
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
* Inputs:       Amount of twenty, ten, five, one dollar bills and quarters, dimes, nickles and pennies to be returned as change as well as ids of denominations, which are unavailable
* Outputs:      none
* Globals:      none
* Returns:      none
* Description:  Prints calculated amount of bills and coins to the command line and adjusts for unavailable denominations
*/
void print_change(int twenty_dollars, int ten_dollars, int five_dollars, int dollars, int quarters, int dimes, int nickels, int pennies, int shortage_id_1, int shortage_id_2, int shortage_id_3)
{
    if (shortage_id_1 != MISSING_TWENTIES && shortage_id_2 != MISSING_TWENTIES && shortage_id_3 != MISSING_TWENTIES)
    {
        printf("\nTWENTY DOLLAR BILLS: \t%d\n", twenty_dollars);
    } else {
        printf("NOT AVAILABLE\n");
    }

    if (shortage_id_1 != MISSING_TENS && shortage_id_2 != MISSING_TENS && shortage_id_3 != MISSING_TENS)
    {
        printf("TEN DOLLAR BILLS: \t%d\n", ten_dollars);
    } else {
        printf("NOT AVAILABLE\n");
    }

    if (shortage_id_1 != MISSING_FIVES && shortage_id_2 != MISSING_FIVES && shortage_id_3 != MISSING_FIVES)
    {
        printf("FIVE DOLLAR BILLS: \t%d\n", five_dollars);
    } else {
        printf("NOT AVAILABLE\n");
    }

    if (shortage_id_1 != MISSING_DOLLARS && shortage_id_2 != MISSING_DOLLARS && shortage_id_3 != MISSING_DOLLARS)
    {
        printf("ONE DOLLAR BILLS: \t%d\n", dollars);
    } else {
        printf("NOT AVAILABLE\n");
    }

    if (shortage_id_1 != MISSING_QUARTERS && shortage_id_2 != MISSING_QUARTERS && shortage_id_3 != MISSING_QUARTERS)
    {
        printf("QUARTERS: \t\t%d\n", quarters);
    } else {
        printf("NOT AVAILABLE\n");
    }

    if (shortage_id_1 != MISSING_DIMES && shortage_id_2 != MISSING_DIMES && shortage_id_3 != MISSING_DIMES)
    {
        printf("DIMES: \t\t\t%d\n", dimes);
    } else {
        printf("NOT AVAILABLE\n");
    }

    if (shortage_id_1 != MISSING_NICKELS && shortage_id_2 != MISSING_NICKELS && shortage_id_3 != MISSING_NICKELS)
    {
        printf("NICKLES: \t\t%d\n", nickels);
    } else {
        printf("NOT AVAILABLE\n");
    }

    if (shortage_id_1 != MISSING_PENNIES && shortage_id_2 != MISSING_PENNIES && shortage_id_3 != MISSING_PENNIES)
    {
        printf("PENNIES: \t\t%d\n\n", pennies);
    } else {
        printf("NOT AVAILABLE\n");
    }
}