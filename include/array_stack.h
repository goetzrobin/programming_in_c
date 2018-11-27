#ifndef ARRAT_STACK_H

#define ARRAT_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/myheader.h"

const int BUFFER_SIZE = 80;
const int STACK_SIZE = 100;

void display_startup_banner(void);
void print_stack_actions(void);
void stack_exerciser(char *filename);
void stack_print(int arr[], int **curr);
int stack_pop(int[], int **);
int stack_push(int[], int **, int);


#endif