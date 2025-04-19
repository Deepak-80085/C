#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "finance.h"
#include "database.h"
#include "menu.h"

int main() {
    printf("===================================\n");
    printf("     PERSONAL FINANCE TRACKER     \n");
    printf("===================================\n\n");
    
    // Initialize the database
    if (!initDatabase()) {
        printf("Error initializing database. Exiting...\n");
        return EXIT_FAILURE;
    }
    
    // Display the main menu and handle user interactions
    displayMainMenu();
    
    // Cleanup before exiting
    closeDatabase();
    
    return EXIT_SUCCESS;
} 