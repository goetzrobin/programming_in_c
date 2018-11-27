#include "../include/array_stack.h"

/*
* Location:    Temple University Computer Science
* Programmer:  Robin Goetz
* Class:       Introduction to C Programming 1057  Fall 2018 Section 005
* Assignment:  Number 8 – OMR Grading
* Date:        10/31/2018
* Version:     1
* Description: Reads in an OMR file and grades the students answers, 
*              generates a csv file for statistical analysis
*/
int main()
{

    display_startup_banner();

    print_stack_actions();

    stack_exerciser("stack_test.txt");
}

/*
* Function:     display_startup_banner()
* Programmer:   Robin Goetz
* Date:         10/17/2018
* Inputs:       none
* Outputs:      none
* Globals:      PRIME_PROGRAMMER - name of primary programmer
* Returns:      none
* Description:  Displays startup banner with basic information
*/
void display_startup_banner(void)
{
    puts("STACK TEST PROGRAM WRITTEN IN C");
    printf("\nLab 11 Programm written by %s. \n", PRIME_PROGRAMMER);
    printf("Program compiled on %s at %s. \n\n", __DATE__, __TIME__);
    puts("This program reads in instructions from a file to exercise\nour stack data structure.\n");
}

/*
* Function:     display_startup_banner()
* Programmer:   Robin Goetz
* Date:         10/17/2018
* Inputs:       none
* Outputs:      none
* Globals:      PRIME_PROGRAMMER - name of primary programmer
* Returns:      none
* Description:  Displays startup banner with basic information
*/
void print_stack_actions()
{
    puts("Actions I can perform:");
    puts("1.  Display the Stack");
    puts("2.  Push to stack");
    puts("3.  Pop from stack");
    puts("");
}
void stack_exerciser(char *filename)
{
    char buffer[BUFFER_SIZE];
    int my_stack[STACK_SIZE] = {12};
    int *current_top = &my_stack[0];
    int count_lines = 0, count_push = 0, count_pop = 0, count_display = 0;

    FILE *IN = fopen(filename, "r");

    if (!IN)
    {
        printf("Can't open file named %s.  Abort.\n", filename);
        exit(EXIT_FAILURE);
    }

    puts("Starting with empty stack.");
    printf("Reading data from file \"%s\"\n\n", filename);

    while (fgets(buffer, BUFFER_SIZE, IN))
    {
        // process the line read in to buffer
        if (buffer[strlen(buffer) - 1] == '\n')
        {
            buffer[strlen(buffer) - 1] = '\0';
        }

        if (strcmp(buffer, "display") == 0)
        {
            stack_print(my_stack, &current_top);
            count_display++;
        }

        if (strcmp(buffer, "pop") == 0)
        {
            stack_pop(my_stack, &current_top);
            count_pop++;
        }

        if (strcmp(buffer, "push") == 0)
        {
            // get next line with number in
            fgets(buffer, BUFFER_SIZE, IN);
            count_lines++;
            // remove newline
            if (buffer[strlen(buffer) - 1] == '\n')
            {
                buffer[strlen(buffer) - 1] = '\0';
            }

            // buffer is now an int
            int number_to_push = atoi(buffer);

            stack_push(my_stack, &current_top, number_to_push);
            count_push++;
        }

        count_lines++;
    }

    fclose(IN);

    int count_commands = count_display + count_pop + count_push;

    puts("\nDone");
    printf("Processed %d commands on %d lines.\n", count_commands, count_lines);
    printf("%d pushed, %d pops, %d displays.\n", count_push, count_pop, count_display);
}

/* 
* Function:     stack_push( )
* Programmer:   Larry Learner
* Date:         December 1, 2018
* Inputs:       arr - array holding the stack
*               cur - current location of the top of the stack
*               num - number to add to the top of the stack
* Outputs:      arr-updated stack array
*               cur -updated location of the top of the stack
* Globals:      * none *
* Returns:      num -the number just added to the stack
* Description:  Adds a number to the stack as the top element.
*
*/
int stack_push(int arr[], int **curr, int num)
{
    long int current_position = *curr - &arr[0];

    arr[current_position] = num;
    *curr += 1;

    printf("pushed %d on to the stack\n", num);

    return num;
}

/* 
* Function:     stack_print( )
* Programmer:   Larry Learner
* Date:         December 1, 2018
* Inputs:       arr - array holding the stack
*               cur - current location of the top of the stack
* Outputs:      * none *
* Globals:      * none *
* Returns:      * none *
* Description:  Prints array to command line.
*
*/
void stack_print(int arr[], int **curr)
{
    long int current_position = *curr - &arr[0];
    if (current_position == 0)
    {
        puts("* the stack is empty *");
    }
    else
    {

        int i;
        for (i = current_position - 1 ; i >= 0 ; i--)
        {
            printf("%d\t", arr[i]);
        }
        puts("");
    }
}

/* 
* Function:     stack_pop( )
* Programmer:   Larry Learner
* Date:         December1, 2018
* Inputs:       arr -array holding the stack
*               cur -current location of the top of the stack
* Outputs:      arr-array holding the stack
*               cur -updated location of the top of the stack
* Globals:      * none *
* Returns:      num -the number just popped from the stack
* Description:  Adds a number to the stack as the top element.
*
*/
int stack_pop(int arr[], int **curr)
{
    long int current_position = *curr - &arr[0];
    int current_value = arr[current_position - 1];

    if (current_position == 0)
    {
        puts("\nCannot perform this action on an empty stack");
        return -1;
    }

    arr[current_position] = -99;
    *curr -= 1;

    printf("popped %d from the stack\n", current_value);

    return current_value;
}