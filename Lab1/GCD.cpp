#include <iostream>
#include <cstdlib> // For std::abs

// Function to compute the GCD of two numbers using the Euclidean algorithm
int gcd(int a, int b) {
    // Ensure a and b are positive
    a = std::abs(a);
    b = std::abs(b);

    // Use Euclidean algorithm
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int num1, num2;

    // Input two numbers
    std::cout << "Enter the first number: ";
    std::cin >> num1;
    std::cout << "Enter the second number: ";
    std::cin >> num2;

    // Compute and display the GCD
    int result = gcd(num1, num2);
    std::cout << "The greatest common divisor of " << num1 << " and " << num2 << " is " << result << std::endl;

    return 0;
}
