#include <stdlib.h>
#include <stdio.h>

#include "../include/myheader.h"
#include "../include/boiling_points.h"

int is_subsctance_within_x_percent(double substance, double data, int percentage);

int main() {
    double substance = WATER;
    double data = 101.00;
    int percentage = 3;
    printf("\nThe boiling point from our unknown substance is is: %.2lf.\nThe boiling point from the table is: %.2lf.\nThe percentage range of accuracy is: %d.\nThe unknown substance is the substance from the table: %d.\n", data, substance, percentage, is_subsctance_within_x_percent(substance, data, percentage));

    data = 105.23;
    printf("\nThe boiling point from our unknown substance is is: %.2lf.\nThe boiling point from the table is: %.2lf.\nThe percentage range of accuracy is: %d.\nThe unknown substance is the substance from the table: %d.\n", data, substance, percentage, is_subsctance_within_x_percent(substance, data, percentage));
    
}

int is_subsctance_within_x_percent(double substance, double data, int percentage){
    double percent = percentage / 100.00;
    return (( substance - percent * substance )  <= data) && (data <= ( substance + percent * substance ));
}