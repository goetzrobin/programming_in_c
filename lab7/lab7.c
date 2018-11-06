#include <stdlib.h>
#include <stdio.h>

#include "../include/myheader.h"
#include "../include/upc.h"

/*
* Location:    Temple University Computer Science
* Programmer:  Robin Goetz
* Class:       Introduction to C Programming 1057  Fall 2018 Section 005
* Assignment:  Number 7 – UPC Code
* Date:        08/10/2018
* Version:     1
* Description: Reads in UPC Code from user and validates code, 
*              prints information based on entered code, and 
*              continues until user enter X or Q to exit program
*/
int main()
{
    int continue_program = 1;
    int barcode_array[MAX_BARCODE_ARRAY_SIZE];
    int check_digit = 0;
    int is_check_last_digit = 0;
    int counter = 0;

    display_startup_banner();

    while (1)
    {

        readInUPCbarcode(barcode_array);

        calculateUPCcheckDigit(barcode_array, &check_digit);

        is_check_last_digit = isCheckDigitLastDigit(check_digit, barcode_array);

        if (is_check_last_digit)
        {
            printf(MESSAGE_SUCCESSFUL_VALIDATION, barcode_array[0], barcode_array[1], barcode_array[2], barcode_array[3], barcode_array[4], barcode_array[5], barcode_array[6], barcode_array[7], barcode_array[8], barcode_array[9], barcode_array[10], barcode_array[11]);
            print_UPC_designation(barcode_array);
            printf("%s\n", getAudioVideoProductString(barcode_array));
        }
        else
        {
            printf(MESSAGE_VALIDATION_FAILURE, barcode_array[0], barcode_array[1], barcode_array[2], barcode_array[3], barcode_array[4], barcode_array[5], barcode_array[6], barcode_array[7], barcode_array[8], barcode_array[9], barcode_array[10], barcode_array[11]);
        }

    } // end while
}

/*
* Function:     display_startup_banner()
* Programmer:   Robin Goetz
* Date:         10/17/2018
* Inputs:       none
* Outputs:      none
* Globals:      none
* Returns:      none
* Description:  Clears buffer
*/
void clear(void)
{
    // get a character until you reach \n
    while (getchar() != '\n')
    {
    }
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
    puts("UPC VERIFICATION PROGRAM WRITTEN IN C");
    printf("\nProgramm written by %s. \n", PRIME_PROGRAMMER);
    printf("Program compiled on %s at %s. \n\n", __DATE__, __TIME__);
}

/*
* Function:     readInUPCbarcode()
* Programmer:   Robin Goetz
* Date:         10/17/2018
* Inputs:       barcode_array holding old upc code or empty at start
* Outputs:      barcode_array holding new upc code
* Globals:      MAX_BARCODE_ARRAY_SIZE - size of barcode array
* Returns:      none
* Description:  Reads in UPC code or exits program if user wants to
*/
void readInUPCbarcode(int barcode_array[MAX_BARCODE_ARRAY_SIZE])
{
    char first_char, second_char;
    int reading_in = 1;
    while (reading_in)
    {
        // read in the first two chars entered by the user --> can handle numbers from 0-99
        printf("\nPlease enter your barcode, seperated by a new line (or X or Q to exit):\n");
        scanf("%c%c", &first_char, &second_char);

        // if user enters X or Q, exit the program
        if (first_char == 'X' || first_char == 'Q')
        {
            printf("Exiting program...\n");
            reading_in = 0;
            exit(0);
        }

        // if user entered a number greater than 9, clear the input buffer and start from the beginning
        if (second_char != '\n')
        {
            puts("Error. Make sure all numbers entered are from 0-9.");
            clear();
            continue;
        }
        else
        {
            // convert the char into an int if it is a digit from 0-9
            barcode_array[0] = first_char - '0';
        }

        // read in the other 11 numbers
        for (int i = 1; i < MAX_BARCODE_ARRAY_SIZE; i++)
        {
            int currently_read_in_integer;
            int input_status = scanf(" %d", &currently_read_in_integer);
            if (input_status != 1)
            {
                printf("Error when reading in number. Ending program...\n");
                clear();
                exit(0);
            }
            else
            {
                barcode_array[i] = currently_read_in_integer;
                // printf("Barcode integer number %d is %d\n", (i + 1), barcode_array[i]);
            }
        }

        // print the barcode to check if it is correct
        print_barcode(barcode_array);

        // check if all digits are from 0-9
        if (foundDigitsOnly(barcode_array) == 0)
        {
            // if not start over
            puts("Error. Make sure all numbers entered are from 0-9.");
            clear();
            continue;
        }

        reading_in = 0;
        // if successfully read in we still have one \n character in buffer, lets remove that
        clear();
    }
}

/*
* Function:     foundDigitsOnly()
* Programmer:   Robin Goetz
* Date:         10/17/2018
* Inputs:       barcode_array holding upc code
* Outputs:      barcode_array holding new upc code
* Globals:      MAX_BARCODE_ARRAY_SIZE - size of barcode array
* Returns:      1 when true that only digits in UPC code - 0 when false
* Description:  Determines if there is only digits from 0-9 in barcode given to function
*/
int foundDigitsOnly(int barcode_array[MAX_BARCODE_ARRAY_SIZE])
{
    int is_digits_only = 1;
    for (int i = 0; i < MAX_BARCODE_ARRAY_SIZE; i++)
    {
        if (barcode_array[i] > 9 || barcode_array[i] < 0)
        {
            is_digits_only = 0;
        }
    }
    return is_digits_only;
}

/*
* Function:     calculateUPCcheckDigit()
* Programmer:   Robin Goetz
* Date:         10/17/2018
* Inputs:       barcode_array holding upc code
* Outputs:      barcode_array holding new upc code, calculated check digit
* Globals:      MAX_BARCODE_ARRAY_SIZE - size of barcode array
* Returns:      none
* Description:  Calculates the UPC's check digit
*/
void calculateUPCcheckDigit(int barcode_array[MAX_BARCODE_ARRAY_SIZE], int *check_digit)
{
    int odd_sum = 0;
    int odd_sum_times_3 = 0;
    int even_sum = 0;
    int sum_odd_sum_times_3_plus_even_sum = 0;
    int last_digit = 0;

    for (int i = 0; i < MAX_BARCODE_ARRAY_SIZE - 1 ; i++)
    {
        if (i % 2 == 0)
        {
            odd_sum += barcode_array[i];
        }
        else
        {
            even_sum += barcode_array[i];
        }
    }

    // printf("Odd sum: %d\n", odd_sum);
    // printf("Even sum: %d\n", even_sum);

    odd_sum_times_3 = odd_sum * 3;

    // printf("Odd sum times 3: %d\n", odd_sum_times_3);

    sum_odd_sum_times_3_plus_even_sum = odd_sum_times_3 + even_sum;

    // printf("Sum Odd x 3 plus even: %d\n", sum_odd_sum_times_3_plus_even_sum);

    last_digit = sum_odd_sum_times_3_plus_even_sum % 10;

    // printf("Last digit: %d\n", last_digit);

    *check_digit = (last_digit == 0) ? last_digit : 10 - last_digit;
    // printf("\ncheck digit: %d\n", *check_digit);
}

/*
* Function:     isCheckDigitLastDigit()
* Programmer:   Robin Goetz
* Date:         10/17/2018
* Inputs:       barcode_array holding old upc code, check digit
* Outputs:      none
* Globals:      MAX_BARCODE_ARRAY_SIZE - size of barcode array
* Returns:      1 - when last digit is check digit and UPC is valid, 0 otherwise
* Description:  Checks if check digit is last digit of barcode to validate code
*/
int isCheckDigitLastDigit(int check_digit, int barcode_array[MAX_BARCODE_ARRAY_SIZE])
{
    // printf("barcode 11: %d\n", barcode_array[11]);
    // printf("barcode cd: %d\n", check_digit);
    return barcode_array[11] == check_digit;
}

/*
* Function:     print_barcode()
* Programmer:   Robin Goetz
* Date:         10/17/2018
* Inputs:       barcode_array holding old upc code
* Outputs:      none
* Globals:      MAX_BARCODE_ARRAY_SIZE - size of barcode array
* Returns:      none
* Description:  Prints the barcode
*/
void print_barcode(int barcode_array[MAX_BARCODE_ARRAY_SIZE])
{
    printf("\nEntered bar-code: ");
    for (int i = 0; i < MAX_BARCODE_ARRAY_SIZE; i++)
    {
        printf("%d", barcode_array[i]);
    }
    printf("\n");
}

/*
* Function:     display_startup_banner()
* Programmer:   Robin Goetz
* Date:         10/17/2018
* Inputs:       barcode_array holding old upc code
* Outputs:      none
* Globals:      MAX_BARCODE_ARRAY_SIZE - size of barcode array
*               PREFIX_0_1_6_7_8       - designation for products with digit 0,1,6,7,8
*               PREFIX_2               - designation for products with digit 2
*               PREFIX_3               - designation for products with digit 3
*               PREFIX_4               - designation for products with digit 4
*               PREFIX_5_9             - designation for products with digit 5 or 9
*               PREFIX_ERROR           - error when no designation can be found
* Returns:      none
* Description:  Prints the barcode's UPC designation
*/
void print_UPC_designation(int barcode_array[MAX_BARCODE_ARRAY_SIZE])
{
    printf("\nBarcode UPC designation: ");
    switch (barcode_array[0])
    {
    case 0:
    case 1:
    case 6:
    case 7:
    case 8:
        printf(PREFIX_0_1_6_7_8);
        break;
    case 2:
        printf(PREFIX_2);
        break;
    case 3:
        printf(PREFIX_3);
        break;
    case 4:
        printf(PREFIX_4);
        break;
    case 5:
    case 9:
        printf(PREFIX_5_9);
        break;
    default:
        printf(PREFIX_ERROR);
        break;
    }
    printf("\n");
}

/*
* Function:     display_startup_banner()
* Programmer:   Robin Goetz
* Date:         10/17/2018
* Inputs:       barcode_array holding old upc code
* Outputs:      none
* Globals:      MAX_BARCODE_ARRAY_SIZE - size of barcode array
*               AUDIO_MEDIA_DIGIT_1     - audio and media product string with digit  1
*               AUDIO_MEDIA_DIGIT_2     - audio and media product string with digit  2
*               AUDIO_MEDIA_DIGIT_3     - audio and media product string with digit  3
*               AUDIO_MEDIA_DIGIT_4     - audio and media product string with digit  4
*               AUDIO_MEDIA_DIGIT_5     - audio and media product string with digit  5
*               AUDIO_MEDIA_DIGIT_6     - audio and media product string with digit  6
*               AUDIO_MEDIA_DIGIT_7     - audio and media product string with digit  7
*               AUDIO_MEDIA_DIGIT_8     - audio and media product string with digit  8
*               AUDIO_MEDIA_DIGIT_ERROR - error if no audio media product string can be determined
* Returns:      audio media product string
* Description:  Prints the barcode's UPC designation
*/
char *getAudioVideoProductString(int barcode_array[MAX_BARCODE_ARRAY_SIZE])
{
    printf("\nBarcode AUDIO MEDIA type: ");
    switch (barcode_array[10])
    {
    case 0:
        return AUDIO_MEDIA_DIGIT_0;
    case 1:
        return AUDIO_MEDIA_DIGIT_1;
    case 2:
        return AUDIO_MEDIA_DIGIT_2;
    case 3:
        return AUDIO_MEDIA_DIGIT_3;
    case 4:
        return AUDIO_MEDIA_DIGIT_4;
    case 5:
        return AUDIO_MEDIA_DIGIT_5;
    case 6:
        return AUDIO_MEDIA_DIGIT_6;
    case 7:
        return AUDIO_MEDIA_DIGIT_7;
    case 8:
        return AUDIO_MEDIA_DIGIT_8;
    case 9:
        return AUDIO_MEDIA_DIGIT_9;
    default:
        return (AUDIO_MEDIA_DIGIT_ERROR);
    }
}