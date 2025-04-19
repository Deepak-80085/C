#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

#define DB_FILE "finance_data.dat"

// Initialize the database
int initDatabase() {
    // Check if database file exists, if not create it
    FILE* file = fopen(DB_FILE, "rb");
    if (file == NULL) {
        // Create a new empty database file
        file = fopen(DB_FILE, "wb");
        if (file == NULL) {
            printf("Error: Could not create database file.\n");
            return 0;
        }
        
        // Write 0 as the initial transaction count
        int count = 0;
        fwrite(&count, sizeof(int), 1, file);
        fclose(file);
    } else {
        fclose(file);
    }
    
    return 1;
}

// Close database resources
void closeDatabase() {
    // No resources to close for file-based database
}

// Save a transaction to the database
int saveTransaction(Transaction transaction) {
    int count = 0;
    
    // Open the file
    FILE* file = fopen(DB_FILE, "rb+");
    if (file == NULL) {
        printf("Error: Could not open database file.\n");
        return 0;
    }
    
    // Read the current count
    fread(&count, sizeof(int), 1, file);
    
    // Move to the end of the file to append new transaction
    fseek(file, 0, SEEK_END);
    
    // Write the new transaction
    fwrite(&transaction, sizeof(Transaction), 1, file);
    
    // Update the count
    count++;
    fseek(file, 0, SEEK_SET);
    fwrite(&count, sizeof(int), 1, file);
    
    fclose(file);
    return 1;
}

// Remove a transaction from the database
int removeTransaction(int id) {
    int count = 0;
    int found = 0;
    
    // Open the file
    FILE* file = fopen(DB_FILE, "rb");
    if (file == NULL) {
        printf("Error: Could not open database file.\n");
        return 0;
    }
    
    // Read the current count
    fread(&count, sizeof(int), 1, file);
    
    // If no transactions, nothing to delete
    if (count == 0) {
        fclose(file);
        return 0;
    }
    
    // Create a temporary array to hold all transactions
    Transaction* transactions = (Transaction*)malloc(count * sizeof(Transaction));
    if (transactions == NULL) {
        fclose(file);
        printf("Error: Memory allocation failed.\n");
        return 0;
    }
    
    // Read all transactions
    fread(transactions, sizeof(Transaction), count, file);
    fclose(file);
    
    // Open the file for writing (this will clear the file)
    file = fopen(DB_FILE, "wb");
    if (file == NULL) {
        free(transactions);
        printf("Error: Could not open database file for writing.\n");
        return 0;
    }
    
    // Write new count (to be updated later)
    int newCount = count;
    fwrite(&newCount, sizeof(int), 1, file);
    
    // Write all transactions except the one to delete
    for (int i = 0; i < count; i++) {
        if (transactions[i].id != id) {
            fwrite(&transactions[i], sizeof(Transaction), 1, file);
        } else {
            newCount--;
            found = 1;
        }
    }
    
    // Update the count if a transaction was deleted
    if (found) {
        fseek(file, 0, SEEK_SET);
        fwrite(&newCount, sizeof(int), 1, file);
    }
    
    free(transactions);
    fclose(file);
    
    return found;
}

// Load all transactions from the database
Transaction* loadTransactions(int* count) {
    // Open the file
    FILE* file = fopen(DB_FILE, "rb");
    if (file == NULL) {
        *count = 0;
        return NULL;
    }
    
    // Read the count
    fread(count, sizeof(int), 1, file);
    
    // If no transactions, return NULL
    if (*count == 0) {
        fclose(file);
        return NULL;
    }
    
    // Allocate memory for transactions
    Transaction* transactions = (Transaction*)malloc(*count * sizeof(Transaction));
    if (transactions == NULL) {
        fclose(file);
        *count = 0;
        printf("Error: Memory allocation failed.\n");
        return NULL;
    }
    
    // Read all transactions
    fread(transactions, sizeof(Transaction), *count, file);
    fclose(file);
    
    return transactions;
} 