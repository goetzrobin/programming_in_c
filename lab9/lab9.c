#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/myheader.h"
#include "../include/lab9.h"

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
    puts("Starting Data processing...\n");
    processOMRData("newomr.txt", "test_taker_names.txt");
    puts("Finished generating CSV file. File stored as lab9_output.csv");
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
    puts("GRADING OMR FORMS AND STORE AS CSV PROGRAM WRITTEN IN C");
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
void processOMRData(char *fname, char *fname_names)
{
    FILE *IN = fopen(fname, "r"); // open the file and enable reading it

    FILE *INTWO = fopen(fname_names, "r");

    FILE *OUTPUT = fopen("lab9_output.csv", "w");

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

    if (!INTWO)
    {
        printf("Error opening input file %s.\n", fname_names);
        perror(fname_names);
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

            // we are done with our answer key and print the intro for all other entries
            print_file_header(OUTPUT);
            continue;
        }
        //read in name
        get_name(INTWO, OUTPUT);
        // loop over rest of row of data representing a students answers
        int i;
        for (i = 0; i < NUMBER_OF_QUESTIONS_PER_STUDENT; i++)
        {
            fscanf(IN, "%c", &scores[i]);

            char read_in_answer = scores[i];

            // display error if encountering unexpected character
            // if (read_in_answer != 'a' && read_in_answer != 'b' && read_in_answer != 'c' && read_in_answer != 'd')
            // {
            //     printf("Error when on line %d. Encountered unexpected character %c. SEE BELOW\n", count, read_in_answer);
            // }
            // printf( "(%d) %d. >%c<\n", count, i, scores[ i ] );
        }

        calculate_single_entry_print_entrys_selection_summary(id, scores, answer_key, incorrect_answers, OUTPUT);

        if (count >= LIMIT_TO_READING_LINES)
            break;
    }
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
    for (i = 0; i < NUMBER_OF_QUESTIONS_PER_STUDENT; i++)
    {
        fscanf(IN, "%c", &answer_key[i]);
        // printf( "Answer key is (%d) %d. >%c<\n", count, i, answer_key[ i ] );
    }
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
void calculate_single_entry_print_entrys_selection_summary(int id, char scores[], char answer_key[], int incorrect_answers[], FILE *output_file)
{
    int i;
    double students_correct_answers = 0.0;

    for (i = 0; i < NUMBER_OF_QUESTIONS_PER_STUDENT; i++)
    {
        if (scores[i] == answer_key[i])
        {
            students_correct_answers++;
        }
        else
        {
            incorrect_answers[i]++;
        }

        fprintf(output_file, "%c,", scores[i]);
    }
    fprintf(output_file, "%.0lf%%", 100.00 * (students_correct_answers / (double)NUMBER_OF_QUESTIONS_PER_STUDENT));

    fprintf(output_file, "\n");
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
void get_name(FILE *name_file, FILE *output_file)
{
    // get names from other file
    char line[265];
    char id_arr[5];
    int id_as_int;
    char firstname[260] = "";
    char secondname[260] = "";
    char lastname[260] = "";
    fgets(line, sizeof(line), name_file);
    sscanf(line, "%d %s %s %s", &id_as_int, firstname, secondname, lastname);

    if (strlen(lastname) == 0)
    {
        fprintf(output_file, "%5.5d,%s %s,", id_as_int, firstname, secondname);
    }
    else
    {
        fprintf(output_file, "%5.5d,%s %s %s,", id_as_int, firstname, secondname, lastname);
    }
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
void print_file_header(FILE *output_file)
{
    fprintf(output_file, "IDENTIY,NAME,Q1,Q2,Q3,Q4,Q5,Q6,Q7,Q8,Q9,Q10,Q11,PERCENTAGE\n");
}