#include <stdio.h>
#include <stdlib.h>

// Node structure for a polynomial term
struct Term {
    int coef;
    int exp;
    struct Term* next;
};

// Polynomial structure
struct Polynomial {
    struct Term* front;
};

// Function to create a new term
struct Term* createTerm(int coef, int exp) {
    struct Term* newTerm = (struct Term*)malloc(sizeof(struct Term));
    if (newTerm == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newTerm->coef = coef;
    newTerm->exp = exp;
    newTerm->next = NULL;
    return newTerm;
}

// Function to initialize an empty polynomial
struct Polynomial* createPolynomial() {
    struct Polynomial* poly = (struct Polynomial*)malloc(sizeof(struct Polynomial));
    if (poly == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    poly->front = NULL;
    return poly;
}

// Function to insert a term into the polynomial
void insertTerm(struct Polynomial* poly, int coef, int exp) {
    struct Term* newTerm = createTerm(coef, exp);
    if (poly->front == NULL || exp > poly->front->exp) {
        newTerm->next = poly->front;
        poly->front = newTerm;
    } else {
        struct Term* current = poly->front;
        while (current->next != NULL && exp < current->next->exp) {
            current = current->next;
        }
        newTerm->next = current->next;
        current->next = newTerm;
    }
}

// Function to add two polynomials and return the result
struct Polynomial* addPolynomials(struct Polynomial* poly1, struct Polynomial* poly2) {
    struct Polynomial* result = createPolynomial();

    struct Term* term1 = poly1->front;
    struct Term* term2 = poly2->front;

    while (term1 != NULL && term2 != NULL) {
        if (term1->exp == term2->exp) {
            insertTerm(result, term1->coef + term2->coef, term1->exp);
            term1 = term1->next;
            term2 = term2->next;
        } else if (term1->exp > term2->exp) {
            insertTerm(result, term1->coef, term1->exp);
            term1 = term1->next;
        } else {
            insertTerm(result, term2->coef, term2->exp);
            term2 = term2->next;
        }
    }

    while (term1 != NULL) {
        insertTerm(result, term1->coef, term1->exp);
        term1 = term1->next;
    }

    while (term2 != NULL) {
        insertTerm(result, term2->coef, term2->exp);
        term2 = term2->next;
    }

    return result;
}

// Function to print the polynomial
void printPolynomial(struct Polynomial* poly) {
    struct Term* current = poly->front;
    while (current != NULL) {
        printf("%dx^%d", current->coef, current->exp);
        if (current->next != NULL) {
            printf(" + ");
        }
        current = current->next;
    }
    printf("\n");
}

// Function to free the memory allocated for the polynomial
void freePolynomial(struct Polynomial* poly) {
    struct Term* current = poly->front;
    struct Term* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(poly);
}

int main() {
    struct Polynomial* poly1 = createPolynomial();
    insertTerm(poly1, 5, 4);
    insertTerm(poly1, 3, 2);
    insertTerm(poly1, 1, 0);

    struct Polynomial* poly2 = createPolynomial();
    insertTerm(poly2, 4, 4);
    insertTerm(poly2, 2, 2);
    insertTerm(poly2, 1, 1);

    printf("First polynomial: ");
    printPolynomial(poly1);

    printf("Second polynomial: ");
    printPolynomial(poly2);

    struct Polynomial* result = addPolynomials(poly1, poly2);
    printf("Resultant polynomial: ");
    printPolynomial(result);

    // Free allocated memory
    freePolynomial(poly1);
    freePolynomial(poly2);
    freePolynomial(result);

    return 0;
}
