#ifndef DATABASE_H
#define DATABASE_H

#include "finance.h"

// Function prototypes for database operations
int initDatabase();
void closeDatabase();
int saveTransaction(Transaction transaction);
int removeTransaction(int id);
Transaction* loadTransactions(int* count);

#endif /* DATABASE_H */ 