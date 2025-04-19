# Personal Finance Tracker

A simple C-based application for tracking personal finances, allowing users to manage income and expenses, analyze spending patterns, and generate reports.

## Features

- Add income and expense transactions
- View all transactions
- Delete transactions by ID
- View current balance
- Analyze spending/income by category
- Generate monthly reports

## Requirements

- C compiler (GCC recommended)
- Standard C libraries

## Building the Project

To build the project, navigate to the project directory and run:

```bash
make
```

This will compile the source files and create an executable named `finance_tracker`.

## Running the Application

After building, you can run the application with:

```bash
make run
```

Or directly with:

```bash
./finance_tracker
```

## Using the Application

The application provides a menu-driven interface with the following options:

1. **Add New Transaction** - Record a new income or expense
2. **View All Transactions** - See a list of all recorded transactions
3. **Delete Transaction** - Remove a transaction by its ID
4. **View Current Balance** - Check your current financial balance
5. **Category Analysis** - Analyze spending/income for a specific category
6. **Monthly Report** - Generate a financial report for a specific month
7. **Exit** - Close the application

## Data Storage

Transaction data is stored in a file named `finance_data.dat` in the same directory as the executable. This file is created automatically when the application is first run.

## Cleaning Up

To remove all compiled files:

```bash
make clean
``` 