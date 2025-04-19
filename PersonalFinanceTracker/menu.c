#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "menu.h"
#include "finance.h"

// Clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Display the main menu and handle user choices
void displayMainMenu() {
    int choice = 0;
    
    while (1) {
        printf("\n===== PERSONAL FINANCE TRACKER MENU =====\n");
        printf("1. Add New Transaction\n");
        printf("2. View All Transactions\n");
        printf("3. Delete Transaction\n");
        printf("4. View Current Balance\n");
        printf("5. Category Analysis\n");
        printf("6. Monthly Report\n");
        printf("7. Exit\n");
        printf("Enter your choice (1-7): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                handleAddTransaction();
                break;
            case 2:
                handleViewTransactions();
                break;
            case 3:
                handleDeleteTransaction();
                break;
            case 4:
                handleViewBalance();
                break;
            case 5:
                handleCategoryAnalysis();
                break;
            case 6:
                handleMonthlyReport();
                break;
            case 7:
                printf("Thank you for using the Personal Finance Tracker. Goodbye!\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Handle adding a new transaction
void handleAddTransaction() {
    Transaction transaction;
    int typeChoice;
    
    printf("\n===== ADD NEW TRANSACTION =====\n");
    
    // Get transaction type
    printf("Transaction Type (1 for Income, 2 for Expense): ");
    scanf("%d", &typeChoice);
    clearInputBuffer();
    
    if (typeChoice != INCOME && typeChoice != EXPENSE) {
        printf("Invalid transaction type. Operation cancelled.\n");
        return;
    }
    
    transaction.type = typeChoice;
    
    // Get description
    printf("Description (max 99 chars): ");
    fgets(transaction.description, sizeof(transaction.description), stdin);
    // Remove newline if present
    size_t len = strlen(transaction.description);
    if (len > 0 && transaction.description[len-1] == '\n') {
        transaction.description[len-1] = '\0';
    }
    
    // Get amount
    printf("Amount: $");
    scanf("%lf", &transaction.amount);
    clearInputBuffer();
    
    // Get category
    printf("Category (max 49 chars): ");
    fgets(transaction.category, sizeof(transaction.category), stdin);
    // Remove newline if present
    len = strlen(transaction.category);
    if (len > 0 && transaction.category[len-1] == '\n') {
        transaction.category[len-1] = '\0';
    }
    
    // Set date to current time
    transaction.date = time(NULL);
    
    // Add transaction to database
    if (addTransaction(transaction)) {
        printf("Transaction added successfully!\n");
    } else {
        printf("Failed to add transaction.\n");
    }
}

// Handle viewing all transactions
void handleViewTransactions() {
    int count;
    Transaction* transactions = getTransactions(&count);
    
    if (transactions == NULL || count == 0) {
        printf("No transactions found.\n");
        return;
    }
    
    printf("\n===== ALL TRANSACTIONS =====\n");
    printf("%-5s %-20s %-10s %-15s %-10s %-20s\n", 
           "ID", "Description", "Amount", "Category", "Type", "Date");
    printf("-------------------------------------------------------------------\n");
    
    char dateStr[26];
    struct tm* timeInfo;
    
    for (int i = 0; i < count; i++) {
        timeInfo = localtime(&transactions[i].date);
        strftime(dateStr, sizeof(dateStr), "%Y-%m-%d %H:%M:%S", timeInfo);
        
        printf("%-5d %-20s $%-9.2f %-15s %-10s %-20s\n", 
            transactions[i].id,
            transactions[i].description,
            transactions[i].amount,
            transactions[i].category,
            transactions[i].type == INCOME ? "Income" : "Expense",
            dateStr);
    }
    
    free(transactions);
}

// Handle deleting a transaction
void handleDeleteTransaction() {
    int id;
    
    printf("\n===== DELETE TRANSACTION =====\n");
    
    // Display all transactions first
    handleViewTransactions();
    
    printf("\nEnter transaction ID to delete (0 to cancel): ");
    scanf("%d", &id);
    clearInputBuffer();
    
    if (id == 0) {
        printf("Operation cancelled.\n");
        return;
    }
    
    if (deleteTransaction(id)) {
        printf("Transaction deleted successfully!\n");
    } else {
        printf("Failed to delete transaction. ID may not exist.\n");
    }
}

// Handle viewing current balance
void handleViewBalance() {
    double balance = calculateBalance();
    
    printf("\n===== CURRENT BALANCE =====\n");
    printf("Your current balance is: $%.2f\n", balance);
    
    if (balance < 0) {
        printf("Warning: You are in debt!\n");
    }
}

// Handle category analysis
void handleCategoryAnalysis() {
    char category[50];
    
    printf("\n===== CATEGORY ANALYSIS =====\n");
    printf("Enter category to analyze: ");
    fgets(category, sizeof(category), stdin);
    
    // Remove newline if present
    size_t len = strlen(category);
    if (len > 0 && category[len-1] == '\n') {
        category[len-1] = '\0';
    }
    
    double income = calculateIncomeByCategory(category);
    double expenses = calculateExpensesByCategory(category);
    
    printf("\nAnalysis for category '%s':\n", category);
    printf("Total Income:  $%.2f\n", income);
    printf("Total Expense: $%.2f\n", expenses);
    printf("Net:           $%.2f\n", income - expenses);
}

// Handle monthly report
void handleMonthlyReport() {
    int month, year;
    
    printf("\n===== MONTHLY REPORT =====\n");
    printf("Enter month (1-12): ");
    scanf("%d", &month);
    clearInputBuffer();
    
    if (month < 1 || month > 12) {
        printf("Invalid month. Operation cancelled.\n");
        return;
    }
    
    printf("Enter year: ");
    scanf("%d", &year);
    clearInputBuffer();
    
    generateMonthlyReport(month, year);
} 