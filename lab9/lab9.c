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
*              generates a csv file for statistical analysis
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
* Description:  Processes OMR Data file and Name file, calculates scores and generates a csv file
*/
void processOMRData(char *fname, char *fname_names)
{
    FILE *IN = fopen(fname, "r"); // open the file and enable reading it

    FILE *IN_NAMES = fopen(fname_names, "r");

    FILE *OUTPUT = fopen("full_data.csv", "w");

    int id; // will hold id when looping over students in file

    int student_ids[LIMIT_TO_READING_LINES]; // will hold all student ids

    char scores[NUMBER_OF_QUESTIONS_PER_STUDENT]; // will hold scores of each when looping over file

    char answer_key[NUMBER_OF_QUESTIONS_PER_STUDENT]; // all correct answers

    double students_percentages[LIMIT_TO_READING_LINES]; // percentages of all students

    int count = 0; // line count within file

    if (!IN)
    {
        printf("Error opening input file %s.\n", fname);
        perror(fname);
        return;
    }

    if (!IN_NAMES)
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

            // we are done with our answer key and print the header for our csv file
            print_file_header(OUTPUT);
            continue;
        }

        //read in name from file with same structure as omr file
        get_name(IN_NAMES, OUTPUT);

        // loop over rest of row of data representing a students answers
        int i;
        for (i = 0; i < NUMBER_OF_QUESTIONS_PER_STUDENT; i++)
        {
            fscanf(IN, "%c", &scores[i]);
            char read_in_answer = scores[i];
        }

        calculate_single_entry_print_entrys_selection_summary(id, scores, answer_key, OUTPUT);

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
* Description:  Prints out the single students answers and generates comma seperated line of answers and percentage score
*/
void calculate_single_entry_print_entrys_selection_summary(int id, char scores[], char answer_key[], FILE *output_file)
{
    int i;
    double students_correct_answers = 0.0;

    for (i = 0; i < NUMBER_OF_QUESTIONS_PER_STUDENT; i++)
    {
        if (scores[i] == answer_key[i])
        {
            students_correct_answers++;
        }

        fprintf(output_file, "%c,", scores[i]);
    }
    fprintf(output_file, "%.0lf%%", 100.00 * (students_correct_answers / (double)NUMBER_OF_QUESTIONS_PER_STUDENT));

    fprintf(output_file, "\n");
}

/*
* Function:     get_name()
* Programmer:   Robin Goetz
* Date:         10/31/2018
* Inputs:       name_file - name of file storing list of full names
                output_file - csv file to be written to
* Outputs:      none
* Globals:      MAX_LINE_LENGTH - maximum line length of data file
*               ID_LENGTH - length of id 
*               NAME_LENGTH - maximum length for each name string
* Returns:      none
* Description:  Gets id and full name from file and outputs it to a csv file
*/
void get_name(FILE *name_file, FILE *output_file)
{
    // get names from other file
    char line[MAX_LINE_LENGTH];
    char id_arr[ID_LENGTH];

    int id_as_int;

    char firstname[NAME_LENGTH] = "";
    char secondname[NAME_LENGTH] = "";
    char lastname[NAME_LENGTH] = "";

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
* Function:     print_file_header()
* Programmer:   Robin Goetz
* Date:         10/31/2018
* Inputs:       output_file - pointer to csv file to be written to
* Outputs:      none
* Globals:      none
* Returns:      none
* Description:  Prints first line of csv file, table header
*/
void print_file_header(FILE *output_file)
{
    fprintf(output_file, "IDENTIY,NAME,Q1,Q2,Q3,Q4,Q5,Q6,Q7,Q8,Q9,Q10,Q11,PERCENTAGE\n");
}