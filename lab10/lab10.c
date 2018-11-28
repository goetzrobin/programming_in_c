#include "../include/lab10.h"

/*
* Location:    Temple University Computer Science
* Programmer:  Robin Goetz
* Class:       Introduction to C Programming 1057  Fall 2018 Section 005
* Assignment:  Number 10 – Bubble Sheet examination
* Date:        11/28/2018
* Version:     1
* Description: Reads in CSV file and allows user to execute different kinds of
*              data mining options
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
* Function:     process_data()
* Programmer:   Robin Goetz
* Date:         11/28/2018
* Inputs:       * none *
* Outputs:      data_array - array of structs, which function reads in from csv file
* Globals:      MAX_LINE_LENGTH - maximum line length of data file
*               EXIT_FAILURE - code signaling program exited with failure
* Returns:      none
* Description:  Creates struct from CSV line and stores it in data_array
*/
void process_data(full_data data_array)
{
    char *file_name = "full_data.csv";
    FILE *file = fopen(file_name, "r");
    char line[MAX_LINE_LENGTH];
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
* Function:     create_bubble_response_struct()
* Programmer:   Robin Goetz
* Date:         11/28/2018
* Inputs:       line - line of CSV file as string
* Outputs:      none
* Globals:      NUMBER_OF_QUESTIONS - number of questions in bubble_response
*               MAX_NAME_SIZE - max length of name 
* Returns:      bubble_response struct created by CSV line
* Description:  Takes in string of one line of CSV file and creates struct
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
* Function:     print_instructions()
* Programmer:   Robin Goetz
* Date:         11/28/2018
* Inputs:       none
* Outputs:      none
* Globals:      none
* Returns:      none
* Description:  Prints possible instructions to console
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
* Function:     process_choice()
* Programmer:   Robin Goetz
* Date:         11/28/2018
* Inputs:       user_selection - int representing users selection of chosen meu option
*               data_array - array of bubble responses
* Outputs:      none
* Globals:      EXIT_SUCCESS - code representing program exited with success
* Returns:      none
* Description:  processes user choice and selects correct subfunction
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
* Function:     display_id()
* Programmer:   Robin Goetz
* Date:         11/28/2018
* Inputs:       data_array - array of bubble responses
* Outputs:      none
* Globals:      MAX_RESPONSE_COUNT - max number of resposnes in array
* Returns:      none
* Description:  prompts user for id of response to be displayed and 
*               displays it if response with id exists
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
* Function:     display_name()
* Programmer:   Robin Goetz
* Date:         11/28/2018
* Inputs:       data_array - array of bubble responses
* Outputs:      none
* Globals:      MAX_RESPONSE_COUNT - max number of resposnes in array
*               MAX_NAME_SIZE - max size of name
* Returns:      none
* Description:  prompts user for name of response to be displayed and 
*               displays it if response with name exists
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
* Function:     display_range_of_ids()
* Programmer:   Robin Goetz
* Date:         11/28/2018
* Inputs:       data_array - array of bubble responses
* Outputs:      none
* Globals:      MAX_RESPONSE_COUNT - max number of resposnes in array
*               MAX_NAME_SIZE - max size of name
* Returns:      none
* Description:  gets a range of ids by user and displays range of ids
*/
void display_range_of_ids(full_data data_array)
{
    int lower_limit, upper_limit;
    full_data returned_array[5];

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
* Function:     get_range()
* Programmer:   Robin Goetz
* Date:         11/28/2018
* Inputs:       data_array - array of bubble responses
* Outputs:      none
* Globals:      MAX_RESPONSE_COUNT - max number of resposnes in array
*               MAX_NAME_SIZE - max size of name
* Returns:      none
* Description:  gets a range of ids by user and displays range of ids*/
int get_range(int low, int high, full_data ret[], full_data sorted)
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
        return 1;
    }
    return 0;
}

/*
* Function:     selection_sort()
* Programmer:   Robin Goetz
* Date:         11/28/2018
* Inputs:       data_array - array of bubble responses
* Outputs:      none
* Globals:      MAX_RESPONSE_COUNT - max number of resposnes in array
* Returns:      none
* Description:  performs a selection sort on the data - sorting by id ascending
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
* Function:     display_last_name()
* Programmer:   Robin Goetz
* Date:         11/28/2018
* Inputs:       data_array - array of bubble responses
* Outputs:      none
* Globals:      MAX_RESPONSE_COUNT - max number of resposnes in array
*               MAX_NAME_SIZE - max size of name
* Returns:      none
* Description:  prompts user for lastname of response to be displayed and 
*               displays it if response with name exists
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
* Function:     get_last_name()
* Programmer:   Robin Goetz
* Date:         11/28/2018
* Inputs:       full_name - full name to be examined for lastname
* Outputs:      last_name - last_name passed by reference
* Globals:      MAX_RESPONSE_COUNT - max number of resposnes in array
*               MAX_NAME_SIZE - max size of name
* Returns:      none
* Description:  looks at full name and determines the last name
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
* Function:     print_one_data()
* Programmer:   Robin Goetz
* Date:         11/28/2018
* Inputs:       p - array of responses
*               idx - id of response to be displayed
* Outputs:      none
* Globals:      NUMBER_OF_QUESTIONS  - number of questions in a response
* Returns:      bubble_response - displayed data item
* Description:  prints specified item to console
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