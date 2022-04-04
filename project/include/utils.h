#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_
#define UTILS_H

#define FILENAME "transaction.dat"

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

struct masterRecord {
    int Number;
    char* Name;
    char Surname[20];
    char addres[30];
    char TelNumber[15];
    float indebtedness;
    float credit_limit;
    float cash_payments;};

typedef  struct  masterRecord Data;

void masterWrite(FILE *ofPTR , Data *Client);
void transactionWrite(FILE *ofPTR, Data *transfer);
void blackRecord(FILE *ofPTR, FILE *ofPTR_2, FILE *blackrecord, Data *client_data, Data *transfer);

#endif  // PROJECT_INCLUDE_UTILS_H_
