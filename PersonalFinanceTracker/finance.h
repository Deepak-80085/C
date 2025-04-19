#ifndef FINANCE_H
#define FINANCE_H

#include <time.h>

// Transaction types
#define INCOME 1
#define EXPENSE 2

// Transaction structure
typedef struct {
    int id;
    char description[100];
    double amount;
    int type; // INCOME or EXPENSE
    char category[50];
    time_t date;
} Transaction;

// Function prototypes
int addTransaction(Transaction transaction);
int deleteTransaction(int id);
Transaction* getTransactions(int* count);
double calculateBalance();
double calculateExpensesByCategory(const char* category);
double calculateIncomeByCategory(const char* category);
void generateMonthlyReport(int month, int year);

#endif /* FINANCE_H */ 