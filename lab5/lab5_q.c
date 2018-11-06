#include <stdio.h>
#include <stdlib.h>


void gpa_c(double gpa);

void wind_c(int wind);

void blood_pressure_c(int blood_pressure);


int main() {

    gpa_c(0.50);
    gpa_c(1.00);
    gpa_c(2.00);
    gpa_c(3.00);
    gpa_c(3.50);
    gpa_c(4.00);
    
    wind_c(24);
     wind_c(35);
      wind_c(40);
       wind_c(55);
        wind_c(73);

    blood_pressure_c(140);
    blood_pressure_c(120);
    blood_pressure_c(119);
    
}

void gpa_c(double gpa) {
    if(gpa >= 0.0 && gpa <= 4.00) {
        if(gpa < 3.50){
           if(gpa < 3.00) {
                if(gpa < 2.00) {
                    if(gpa < 1.00) {
                        puts("Failed semester - registration suspended");
                    } else {
                        puts("On probation for next semester");
                    }
                } else {
                    puts("");
                }
           } else {
               puts("Dean's list for semester");
           }
        } else {
             puts("Highest honors for semester");
        }
    }
}

void wind_c(int wind){
    if(wind < 25) {
        puts("not a strong wind");
    } else if(wind <= 38) {
        puts("strong wind");
    } else if(wind <= 54) {
        puts("gale");
    } else if(wind <=72){
        puts("whole gale");
    } else {
        puts("hurricane");
    }
}


void blood_pressure_c(int blood_pressure) {
    if(blood_pressure >= 140) {
        puts("hypertension");
    } else if (blood_pressure >= 120){
        puts("pre-hypertension");
    } else {
        puts("normal");
    }
}