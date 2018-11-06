#include <stdio.h>
#include <stdlib.h>

#include "../include/myheader.h"
#include "../include/orm.h"

/*
* Location:    Temple University Computer Science
* Programmer:  Robin Goetz
* Class:       Introduction to C Programming 1057  Fall 2018 Section 005
* Assignment:  Number 8 – OMR Grading
* Date:        10/31/2018
* Version:     1
* Description: Reads in an OMR file and grades the students answers, 
*              prints out a summary of questions marked incorrect,
*              creates a summary of errors and prints out the students' scores
*/
int main()
{
    display_startup_banner();

    processOMRData("newomr.txt");

    return EXIT_SUCCESS;
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
    puts("GRADING OMR FORMS PROGRAM WRITTEN IN C");
    printf("\nProgramm written by %s. \n", PRIME_PROGRAMMER);
    printf("Program compiled on %s at %s. \n\n", __DATE__, __TIME__);
}

/*
* Function:     processOMRData()
* Programmer:   Robin Goetz
* Date:         10/17/2018
* Inputs:       fname - name of OMR file
* Outputs:      none
* Globals:      LIMIT_TO_READING_LINES - number of lines to be read in from file
*               NUMBER_OF_QUESTIONS_PER_STUDENT - number of questions students answered
* Returns:      none
* Description:  Processes OMR Data file, calculates answer summary, data about questions marked 
*               incorect and student scores and output everything to command line
*/
void processOMRData(char *fname)
{
    FILE *IN = fopen(fname, "r"); // open the file and enable reading it

    int id; // will hold id when looping over students in file

    int student_ids[LIMIT_TO_READING_LINES]; // will hold all student ids

    char scores[NUMBER_OF_QUESTIONS_PER_STUDENT]; // will hold scores of each when looping over file

    char answer_key[NUMBER_OF_QUESTIONS_PER_STUDENT]; // all correct answers

    double students_percentages[LIMIT_TO_READING_LINES]; // percentages of all students

    int incorrect_answers[NUMBER_OF_QUESTIONS_PER_STUDENT] = {0}; // will keep track of count of how many times each answer was marked incorrectly

    int count = 0; // line count within file

    if (!IN)
    {
        printf("Error opening input file %s.\n", fname);
        perror(fname);
        return;
    }

    // loop over every row of data and first take the id (integer number)
    while (fscanf(IN, "%d", &id) == 1)
    {
        student_ids[count] = id;
        count++;

        // the first line is the answer key
        if (count == 1)
        {
            read_in_answer_key(answer_key, IN);
            print_out_answer_key(answer_key);

            // we are done with our answer key and print the intro for all other entries
            print_selection_summary_intro();
            continue;
        }

        // loop over rest of row of data representing a students answers
        int i;
        for ( i = 0; i < NUMBER_OF_QUESTIONS_PER_STUDENT; i++)
        {
            fscanf(IN, "%c", &scores[i]);

            char read_in_answer = scores[i];
            
            // display error if encountering unexpected character
            if (read_in_answer != 'a' && read_in_answer != 'b' && read_in_answer != 'c' && read_in_answer != 'd')
            {
                printf("Error when on line %d. Encountered unexpected character %c. SEE BELOW\n", count, read_in_answer);
            }
            // printf( "(%d) %d. >%c<\n", count, i, scores[ i ] );
        }
        
        //
        students_percentages[count - 1] = calculate_single_entry_print_entrys_selection_summary(id, scores, answer_key, incorrect_answers);

        if (count >= LIMIT_TO_READING_LINES)
            break;
    }

    print_incorrect_answer_count_percentage(incorrect_answers);

    print_grading_summary(student_ids, students_percentages);
}

/*
* Function:     print_selection_summary_intro()
* Programmer:   Robin Goetz
* Date:         10/31/2018
* Inputs:       none
* Outputs:      none
* Globals:      none
* Returns:      none
* Description:  Displays header of selection summary
*/
void print_selection_summary_intro(void)
{
    puts("ANSWER SELECTION SUMMARY");
    puts("Ident\tQ1\tQ2\tQ3\tQ4\tQ5\tQ6\tQ7\tQ8\tQ9\tQ10\tQ11");
}

/*
* Function:     read_in_answer_key()
* Programmer:   Robin Goetz
* Date:         10/31/2018
* Inputs:       IN - pointer to the read in file
* Outputs:      answer_key - array of all correct answers
* Globals:      NUMBER_OF_QUESTIONS_PER_STUDENT - number of questions students answered
* Returns:      none
* Description:  Reads in the answer key, the first line in the file
*/
void read_in_answer_key(char answer_key[], FILE *IN)
{
    int i;
    for ( i = 0; i < NUMBER_OF_QUESTIONS_PER_STUDENT; i++)
    {
        fscanf(IN, "%c", &answer_key[i]);
        // printf( "Answer key is (%d) %d. >%c<\n", count, i, answer_key[ i ] );
    }
}

/*
* Function:     print_out_answer_key()
* Programmer:   Robin Goetz
* Date:         10/31/2018
* Inputs:       none
* Outputs:      none
* Globals:      NUMBER_OF_QUESTIONS_PER_STUDENT - number of questions students answered
* Returns:      none
* Description:  Prints the answer key, the first line in the file
*/
void print_out_answer_key(char answer_key[])
{
    puts("Read in the answer key:");

    int i;

    for ( i = 0; i < NUMBER_OF_QUESTIONS_PER_STUDENT; i++)
    {
        printf("\tQuestion %d:\t%c\n", i + 1, answer_key[i]);
    }
    puts("");
}

/*
* Function:     calculate_single_entry_print_entrys_selection_summary()
* Programmer:   Robin Goetz
* Date:         10/31/2018
* Inputs:       id - Id of currently evaluated student
                scores - Scores of current student
                answer_key - Array of all correct answers
* Outputs:      incorrect_answers - Array that counts how often each answer was marked incorrect
* Globals:      PRIME_PROGRAMMER - name of primary programmer
* Returns:      student's grade percentage
* Description:  Prints out the single students answers and an indicator if it is correct or not.
*               Updates number of incorrect answers per question. Keeps track of single student's correct answers
*               Finally, calculates the percentage of correct answers of current student
*/
double calculate_single_entry_print_entrys_selection_summary(int id, char scores[], char answer_key[], int incorrect_answers[])
{
    int i;
    char correct_indicator;
    double students_correct_answers = 0.0;

    printf("%5.5d\t", id);
    for (i = 0; i < NUMBER_OF_QUESTIONS_PER_STUDENT; i++)
    {
        if (scores[i] == answer_key[i])
        {
            correct_indicator = ' ';
            students_correct_answers++;
        }
        else
        {
            correct_indicator = 'X';
            incorrect_answers[i]++;
        }

        printf("%c%c\t", scores[i], correct_indicator);
    }
    puts("");
    return 100.00 * (students_correct_answers / (double)NUMBER_OF_QUESTIONS_PER_STUDENT);
}

/*
* Function:     print_incorrect_answer_count_percentage()
* Programmer:   Robin Goetz
* Date:         10/31/2018
* Inputs:       incorrect_answers - array containing the number of each question answered incorrectly
* Outputs:      none
* Globals:      LIMIT_TO_READING_LINES - number of lines to be read in from file
*               NUMBER_OF_QUESTIONS_PER_STUDENT - number of questions students answered
* Returns:      none
* Description:  Prints the number and percentage of times each question was marked incorrect
*/
void print_incorrect_answer_count_percentage(int incorrect_answers[])
{
    puts("");
    puts("\nCOUNT AND PERCENT OF ANSWER MARKED INCORRECT");
    puts("Ident\tQ1\tQ2\tQ3\tQ4\tQ5\tQ6\tQ7\tQ8\tQ9\tQ10\tQ11");
    printf("\t");
    int i;
    for ( i = 0; i < NUMBER_OF_QUESTIONS_PER_STUDENT; i++)
    {
        printf("%2d\t", incorrect_answers[i]);
    }
    puts("");
    printf("\t");
    for ( i = 0; i < NUMBER_OF_QUESTIONS_PER_STUDENT; i++)
    {
        printf("%.0lf%%\t", 100.00 * (double)incorrect_answers[i] / ((double)LIMIT_TO_READING_LINES - 1.00));
    }
    puts("");
}

/*
* Function:     print_grading_summary()
* Programmer:   Robin Goetz
* Date:         10/31/2018
* Inputs:       student_ids - array of student ids
*               students_percentages - percentage scores of students, corresponding to student_ids
* Outputs:      none
* Globals:      none
* Returns:      none
* Description:  Prints out scores of students, as well as corresponding id
*/
void print_grading_summary(int student_ids[], double students_percentages[])
{
    puts("\nGRADING SUMMARY");
    puts("Identification\t\tGrade");
    int i;
    for ( i = 1; i < LIMIT_TO_READING_LINES; i++)
    {
        printf("  %5.5d\t\t\t%.2lf%%\n", student_ids[i], students_percentages[i]);
    }
}