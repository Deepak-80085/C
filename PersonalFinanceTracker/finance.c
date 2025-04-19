#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "finance.h"
#include "database.h"

// Add a new transaction to the database
int addTransaction(Transaction transaction) {
    // Generate a unique ID (could be more sophisticated in a real app)
    static int nextId = 1;
    transaction.id = nextId++;
    
    // Save to database
    return saveTransaction(transaction);
}

// Delete a transaction by ID
int deleteTransaction(int id) {
    return removeTransaction(id);
}

// Get all transactions from the database
Transaction* getTransactions(int* count) {
    return loadTransactions(count);
}

// Calculate the current balance (income - expenses)
double calculateBalance() {
    int count;
    Transaction* transactions = loadTransactions(&count);
    
    if (transactions == NULL) {
        return 0.0;
    }
    
    double balance = 0.0;
    for (int i = 0; i < count; i++) {
        if (transactions[i].type == INCOME) {
            balance += transactions[i].amount;
        } else {
            balance -= transactions[i].amount;
        }
    }
    
    free(transactions);
    return balance;
}

// Calculate total expenses for a specific category
double calculateExpensesByCategory(const char* category) {
    int count;
    Transaction* transactions = loadTransactions(&count);
    
    if (transactions == NULL) {
        return 0.0;
    }
    
    double total = 0.0;
    for (int i = 0; i < count; i++) {
        if (transactions[i].type == EXPENSE && 
            strcmp(transactions[i].category, category) == 0) {
            total += transactions[i].amount;
        }
    }
    
    free(transactions);
    return total;
}

// Calculate total income for a specific category
double calculateIncomeByCategory(const char* category) {
    int count;
    Transaction* transactions = loadTransactions(&count);
    
    if (transactions == NULL) {
        return 0.0;
    }
    
    double total = 0.0;
    for (int i = 0; i < count; i++) {
        if (transactions[i].type == INCOME && 
            strcmp(transactions[i].category, category) == 0) {
            total += transactions[i].amount;
        }
    }
    
    free(transactions);
    return total;
}

// Generate a report for a specific month
void generateMonthlyReport(int month, int year) {
    int count;
    Transaction* transactions = loadTransactions(&count);
    
    if (transactions == NULL) {
        printf("No data available for report.\n");
        return;
    }
    
    double totalIncome = 0.0;
    double totalExpense = 0.0;
    
    printf("\n=== Monthly Report: %d/%d ===\n", month, year);
    printf("%-5s %-20s %-10s %-15s %-10s\n", "ID", "Description", "Amount", "Category", "Type");
    printf("------------------------------------------------------\n");
    
    struct tm* timeInfo;
    
    for (int i = 0; i < count; i++) {
        timeInfo = localtime(&transactions[i].date);
        
        // Check if transaction is in the requested month/year
        if (timeInfo->tm_mon + 1 == month && timeInfo->tm_year + 1900 == year) {
            printf("%-5d %-20s $%-9.2f %-15s %-10s\n", 
                transactions[i].id,
                transactions[i].description,
                transactions[i].amount,
                transactions[i].category,
                transactions[i].type == INCOME ? "Income" : "Expense");
                
            if (transactions[i].type == INCOME) {
                totalIncome += transactions[i].amount;
            } else {
                totalExpense += transactions[i].amount;
            }
        }
    }
    
    printf("------------------------------------------------------\n");
    printf("Total Income:  $%.2f\n", totalIncome);
    printf("Total Expense: $%.2f\n", totalExpense);
    printf("Net:           $%.2f\n", totalIncome - totalExpense);
    
    free(transactions);
} 