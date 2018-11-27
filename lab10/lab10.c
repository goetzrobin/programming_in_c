#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_SIZE 250
#define NUMBER_OF_QUESTIONS 10
#define MAX_RESPONSE_COUNT 29

typedef struct
{
    int id;
    char full_name[MAX_NAME_SIZE];
    char responses[NUMBER_OF_QUESTIONS];
} bubble_response;

typedef bubble_response full_data[MAX_RESPONSE_COUNT];

void print_instructions(void);
void process_choice(int user_selection, full_data data_array);
void display_id();
void display_name(full_data data_array);
void display_range_of_ids();
void display_last_name(full_data data_array);
void process_data(full_data data_array);
char *str_to_lower(const char *str, char output[MAX_NAME_SIZE]);
void get_last_name(char *full_name, char *last_name);
int get_range(int low, int high, full_data ret, full_data sorted);
void selection_sort(full_data data);
bubble_response print_one_data(full_data p, int idx);
bubble_response create_bubble_response_struct(char *line);

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
    int user_selection;
    print_instructions();
    full_data data_array;
    process_data(data_array);
    while (1)
    {

        printf("\nEnter your choice [1-5]: ");
        scanf("%d", &user_selection);
        process_choice(user_selection, data_array);
    }
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
void process_data(full_data data_array)
{
    char *file_name = "full_data.csv";
    FILE *file = fopen(file_name, "r");
    char line[256];
    int counter = 0;

    if (!file)
    {
        puts("Could not open file...");
        exit(EXIT_FAILURE);
    }

    // get header
    fgets(line, sizeof(line), file);

    // process data
    while (fgets(line, sizeof(line), file))
    {
        data_array[counter] = create_bubble_response_struct(line);
        counter++;
    }

    fclose(file);
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
bubble_response create_bubble_response_struct(char *line)
{

    /* get the first token */
    char *token = strtok(line, ",");

    /* walk through other tokens */
    int column = 0;
    int answer_index = 0;
    char answers[NUMBER_OF_QUESTIONS];
    int id;
    char name[MAX_NAME_SIZE];
    bubble_response res;

    while (token != NULL)
    {
        if (column == 0)
        {
            res.id = atoi(token);
        }
        if (column == 1)
        {
            strncpy(res.full_name, token, MAX_NAME_SIZE);
        }
        if (column > 1 && column <= NUMBER_OF_QUESTIONS)
        {
            res.responses[answer_index] = (char)*token;
            answer_index++;
        }
        // pass in NULL so strtok picks up where first one ended
        token = strtok(NULL, ",");
        column++;
    }

    return res;
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
void print_instructions(void)
{
    puts("Bubble Sheet Results Data Mining Menu");
    puts("1. Display specific id");
    puts("2. Display specific name");
    puts("3. Display range of ids");
    puts("4. Display last name");
    puts("5. End the program");
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
void process_choice(int user_selection, full_data data_array)
{
    switch (user_selection)
    {
    case 1:
        display_id(data_array);
        break;
    case 2:
        display_name(data_array);
        break;
    case 3:
        display_range_of_ids(data_array);
        break;
    case 4:
        display_last_name(data_array);
        break;
    case 5:
        exit(EXIT_SUCCESS);
    }
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
void display_id(full_data data_array)
{
    int user_id;
    printf("Please enter the id of the response to be displayed: ");
    scanf("%d", &user_id);

    int i, found;
    for (i = found = 0; i < MAX_RESPONSE_COUNT; i++)
    {
        if (data_array[i].id == user_id)
        {
            print_one_data(data_array, i);
            found = 1;
        }
    }
    if (found == 0)
    {
        puts("Could not find an entry with that id.");
    }
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
void display_name(full_data data_array)
{

    char name_looked_for[MAX_NAME_SIZE];

    printf("Please enter a name: ");
    scanf("%s", name_looked_for);

    int i, found;
    for (i = found = 0; i < MAX_RESPONSE_COUNT; i++)
    {
        char *result = NULL;
        result = strcasestr(data_array[i].full_name, name_looked_for);

        if (result != NULL)
        {
            print_one_data(data_array, i);
            found = 1;
        }
    }
    if (found == 0)
    {
        puts("Could not find an entry with that id.");
    }

    memset(name_looked_for, 0, sizeof name_looked_for);
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
void display_range_of_ids(full_data data_array)
{
    int lower_limit, upper_limit;
    full_data returned_array;

    printf("\nEnter lower limit of a range of IDs: ");
    scanf("%d", &lower_limit);

    printf("\nEnter upper limit of a range of IDs: ");
    scanf("%d", &upper_limit);

    if (upper_limit - lower_limit > 3000)
    {
        puts("\nPlease enter a range that is no more than 3000 IDs.");
        return;
    }

    if (upper_limit - lower_limit <= 0)
    {
        puts("\nCannot display a negative range.");
        return;
    }

    selection_sort(data_array);

    get_range(lower_limit, upper_limit, returned_array, data_array);
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
int get_range(int low, int high, full_data ret, full_data sorted)
{
    int i;
    int count = 0;
    for (i = 0; i < MAX_RESPONSE_COUNT; i++)
    {
        if (count > 5)
        {
            puts("There are too many entries to display. Only displaying the first 5.");
        }
        if (sorted[i].id > low && sorted[i].id < high)
        {
            print_one_data(sorted, i);
            count++;
        }
    }
    if (count == 0)
    {
        puts("Could not find any students with id within range.");
    }
    return 0;
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
void selection_sort(full_data data)
{
    int n = MAX_RESPONSE_COUNT;
    int adjustment, i, j, location, t;
    bubble_response swapper;
    for (i = 0; i < n - 1; i++)
    {
        adjustment = data[i].id;
        location = i;
        for (j = i + 1; j < n; j++)
        {
            if (data[j].id < adjustment)
            {
                adjustment = data[j].id;
                location = j;
            }
        }
        swapper = data[i];
        data[i] = data[location];
        data[location] = swapper;
    }
    return;
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
void display_last_name(full_data data_array)
{
    char name_looked_for[MAX_NAME_SIZE];

    printf("Please enter a last name: ");
    scanf("%s", name_looked_for);

    int i, found;
    for (i = found = 0; i < MAX_RESPONSE_COUNT; i++)
    {
        char last_name[MAX_NAME_SIZE];

        get_last_name(data_array[i].full_name, last_name);

        char *result = NULL;
        result = strcasestr(last_name, name_looked_for);

        if (result != NULL)
        {
            print_one_data(data_array, i);
            found = 1;
        }
    }
    if (found == 0)
    {
        puts("Could not find an entry with that id.");
    }

    memset(name_looked_for, 0, sizeof name_looked_for);
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
void get_last_name(char *full_name, char *last_name)
{
    char *pch;
    char full_name_copy[MAX_NAME_SIZE];

    strcpy(full_name_copy, full_name);

    pch = strtok(full_name_copy, " ");
    while (pch != NULL)
    {
        strcpy(last_name, pch);
        pch = strtok(NULL, " ");
    }
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
bubble_response print_one_data(full_data p, int idx)
{
    printf("ID: %d Name: %s\n", p[idx].id, p[idx].full_name);
    printf(" ");
    int i;
    for (i = 0; i < NUMBER_OF_QUESTIONS; i++)
        printf("Q%d: %c ", i + 1, p[idx].responses[i]);
    puts("");
    return p[idx];
}