#ifndef ORM_H

#define ORM_H

#include <stdio.h>
#include <stdlib.h>

#define LIMIT_TO_READING_LINES 30
#define NUMBER_OF_QUESTIONS_PER_STUDENT 11
#define ERROR_CODE_IN_INPUT_SCANNING 'e'

void display_startup_banner(void);
void processOMRData(char *fname, char *fname_names);
void print_file_header(FILE *output_file);
void read_in_answer_key(char answer_key[], FILE *IN);
void get_name(FILE *name_file, FILE *output_file);
void calculate_single_entry_print_entrys_selection_summary(int id, char scores[], char answer_key[], int incorrect_answers[], FILE *output_file);

#endif