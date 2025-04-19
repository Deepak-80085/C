#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ITERATIONS 100
#define WIDTH 80
#define HEIGHT 40
#define X_MIN -2.0
#define X_MAX 1.0
#define Y_MIN -1.0
#define Y_MAX 1.0

// Function to calculate if a point is in the Mandelbrot set
int is_in_mandelbrot(double x0, double y0) {
    double x = 0;
    double y = 0;
    double x_temp;
    int iteration = 0;

    while (x*x + y*y <= 4 && iteration < MAX_ITERATIONS) {
        x_temp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = x_temp;
        iteration++;
    }

    return iteration;
}

// Function to map a value from one range to another
double map(double value, double start1, double stop1, double start2, double stop2) {
    return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
}

// Function to get ASCII character based on iteration count
char get_char(int iterations) {
    if (iterations == MAX_ITERATIONS) {
        return '#';
    } else {
        const char charset[] = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
        int char_len = sizeof(charset) - 1;
        return charset[iterations % char_len];
    }
}

int main() {
    double x, y;
    int iterations;

    // Clear screen using ANSI escape code
    printf("\033[2J\033[H");
    printf("ASCII Mandelbrot Set Explorer\n");
    printf("============================\n\n");

    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            // Map pixel coordinates to complex plane
            x = map(col, 0, WIDTH - 1, X_MIN, X_MAX);
            y = map(row, 0, HEIGHT - 1, Y_MIN, Y_MAX);

            // Calculate iterations for this point
            iterations = is_in_mandelbrot(x, y);

            // Print appropriate character
            printf("%c", get_char(iterations));
        }
        printf("\n");
    }

    printf("\nControls:\n");
    printf("- The darker regions (#) represent points in the Mandelbrot set\n");
    printf("- Other characters show how quickly points escape the set\n");
    
    return 0;
} 

