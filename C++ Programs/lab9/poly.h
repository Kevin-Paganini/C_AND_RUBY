
// Polynomial declaration
// Author: Kevin Paganini
// Lab 9
// Date: 5/5/2022

#ifndef _polynomial_h
#define _polynomial_h


#include <stdbool.h>

#define MAXDEGREE 19
#define MAXTERMS (MAXDEGREE + 1)

struct Polynomial {
    char var;
    int coef[MAXTERMS];

};

// initializes the polynomial
void initialize_polynomial(struct Polynomial *polynomial, char variable);

// read a polynomial in from a char array
// Basically has to call an entire subroutine
bool read_polynomial(struct Polynomial *polynomial, char toRead[]);

// Sub routine


//Writes to a polynomial
void write_polynomial(struct Polynomial *polynomial);

// sums two polynomials into a third polynomial
bool sum_polynomial(struct Polynomial *polynomial_dest, struct Polynomial *polynomial_one, struct Polynomial *polynomial_two);

//Helpers for read polynomial

// reads the next polynomials
bool read_next_polynomials(char *read_pointer, struct Polynomial *poly);

// Svaes part of polynomial to polynomial
bool save_poly(int coef, int degree, char var, int sign, struct Polynomial *poly);

// Moves pointer to next sign
char* next_sign(char *read_pointer);

//empties polynomial oiut
void clear_poly(struct Polynomial *poly);

// Helpers for write_polynomial
int print_poly(int i,  struct Polynomial *poly, int zeros);
void print_coef(int i, int coef);
void print_coef_neg_case(int coef);
void print_first_coef_neg_case(int coef);

void set_poly(struct Polynomial *p1, struct Polynomial *p2,struct Polynomial *p3);



#endif // stack