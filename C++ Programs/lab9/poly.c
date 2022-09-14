
// Polynomial implementation
// Author: Kevin Paganini
// Lab 9
// Date: 5/5/2022

// Nice and compact code for you

#include "poly.h"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Initializes a polynomial
// Parameters: Polynomial to initialize and variable
void initialize_polynomial(struct Polynomial *polynomial, char variable){
    polynomial->var = variable;
    for(int i = 0; i < MAXTERMS; ++i){polynomial->coef[i] = 0;}
}
// Skips to next sign
// Iterates pointer to next sign in char array
char *next_sign(char *read_pointer){
    while((*read_pointer != '+') && (*read_pointer != '-') && (*read_pointer != '\n')){++read_pointer;}
    return read_pointer;
}
// Clears polynomial because apparently they aren't always empty
void clear_poly(struct Polynomial *poly){
    for (int i =0; i < MAXTERMS; i++) {poly->coef[i] = 0;}
}

// PSEUDOCODE FROM WEBSITE
// use atoi to convert the start of the string into an integer
// skip to the next + or - or newline
// while the next character is + or -
// store whether it was + or -
// skip to the first digit
// assuming p points to the current place in the buffer, use
// sscanf(p, "%d%c%d", &coefficient, &letter, &degree);
// to parse the coefficient, variable name, and degree
// record the coefficient in your polynomial array (at the right degree)
// Use the + or - stored above to determine if that coefficient is negative
// skip to the next +, -, or newline
bool read_polynomial(struct Polynomial *poly, char toRead[]){
    clear_poly(poly);
    int zeroCoef = atoi(toRead);
    char *read_pointer = toRead;
    if (zeroCoef < 0){read_pointer++;}
    poly->coef[0] = zeroCoef;
    read_pointer = next_sign(read_pointer);
    if(read_next_polynomials(read_pointer, poly)){return true;}
    else {return false;}
}

// Reads all the polynomials after the first one into polynomial
bool read_next_polynomials(char *read_pointer, struct Polynomial *poly){    
    int coef, degree;
    char var;
    int sign = 1;
    while((*read_pointer == '+') || (*read_pointer == '-')){
        if(*read_pointer == '-'){sign = -1;} else {sign = 1;}
        read_pointer += 2; // get away from plus sign
        sscanf(read_pointer, "%d%c%d", &coef, &var, &degree);
        if (!save_poly(coef, degree, var, sign, poly)){return false;}
        read_pointer = next_sign(read_pointer);
    }
    return true;
}

// Saves the polynomial if degree is less than max terms
// return true if degree is saved
// return false if degree is not saved
bool save_poly(int coef, int degree, char var, int sign, struct Polynomial *poly){
    if(degree < MAXTERMS){
        int ret = sign * coef;
        poly->coef[degree] = ret;
        return true;
    } else {return false;}
}

// Calls the entire subroutine of writing a polynomial
void write_polynomial(struct Polynomial *poly){
    int zeros = 0;
    for(int i = 0; i < MAXTERMS; i++){zeros += print_poly(i, poly, zeros);}
    if (zeros == MAXTERMS){printf("%d", 0);}
}

// Prints polynomial one at a time
// returns zero if a zero is found
int print_poly(int i,  struct Polynomial *poly, int zeros){
    if(poly->coef[i] != 0){
        int coef =  poly->coef[i];
        if (coef == 0){zeros++;}
        print_coef(i, coef); // handles coef printing
        if(i != 0){printf("%c%d", poly->var, i);}  // prints variable and coefficient
    } else if (i == 0){printf("%d", poly->coef[0]);} // prints first coef no x so no d
    return zeros;
}

// Handles coefficient printing subroutine
void print_coef(int i, int coef){
    if (i == 0) {
        if (coef < 0){print_first_coef_neg_case(coef);} 
        else {printf("%d", coef);}
    } else {
        if (coef < 0){print_coef_neg_case(coef);}
        else {
            printf(" + ");
            printf("%d", coef);
        }
    }
}
// Prints coefficients with negatives
void print_coef_neg_case(int coef){
    printf(" - ");
    printf("%d", (coef * -1)); 
}
// Prints first coefficient with negative
void print_first_coef_neg_case(int coef){
    printf("-");
    printf("%d", (coef * -1)); 
}


// Sums polynomial together
// checks p2 and p3 var to be the same then calls setpoly
// returns true if success
// returns false if vars do not match
bool sum_polynomial(struct Polynomial *p1, struct Polynomial *p2,struct Polynomial *p3){
    if(p2->var == p3->var ){set_poly(p1, p2, p3);}
    else{return false;}
    return true;
}

// Actually does the adding cause why not make it modular
void set_poly(struct Polynomial *p1, struct Polynomial *p2,struct Polynomial *p3){
    p1->var = p2->var;
    for(int i = 0; i < MAXTERMS; i++){p1->coef[i] = p2->coef[i] + p3->coef[i];} 
}




