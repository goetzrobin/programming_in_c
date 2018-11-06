#ifndef ORM_H

#define ORM_H

#include <stdio.h>
#include <stdlib.h>

#define LIMIT_TO_READING_LINES 30
#define NUMBER_OF_QUESTIONS_PER_STUDENT 11
#define ERROR_CODE_IN_INPUT_SCANNING 'e'

void display_startup_banner(void);
void processOMRData(char *fname);
void print_selection_summary_intro(void);
void read_in_answer_key(char answer_key[], FILE *IN);
void print_out_answer_key(char answer_key[]);
double calculate_single_entry_print_entrys_selection_summary(int id, char scores[], char answer_key[], int incorrect_answers[]);
void print_incorrect_answer_count_percentage(int incorrect_answers[]);
void print_grading_summary(int student_ids[], double students_percentages[]);

#endif