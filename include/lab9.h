#ifndef LAB9_H

#define LAB9_H

#include <stdio.h>
#include <stdlib.h>

#define LIMIT_TO_READING_LINES 30
#define NUMBER_OF_QUESTIONS_PER_STUDENT 11
#define MAX_LINE_LENGTH 265
#define ID_LENGTH 5
#define NAME_LENGTH 260

void display_startup_banner(void);
void processOMRData(char *fname, char *fname_names);
void print_file_header(FILE *output_file);
void read_in_answer_key(char answer_key[], FILE *IN);
void get_name(FILE *name_file, FILE *output_file);
void calculate_single_entry_print_entrys_selection_summary(int id, char scores[], char answer_key[], FILE *output_file);
#endif