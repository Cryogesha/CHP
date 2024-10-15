#include <iostream>
#include <cstdlib> // For std::abs

// Function to compute the GCD of two numbers using the Euclidean algorithm
int gcd(int a, int b) {
    a = std::abs(a);
    b = std::abs(b);

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to compute the LCM of two numbers
int plcm(int a, int b) {
    if (a == 0 || b == 0) {
        return 0; // LCM of any number with 0 is 0
    }
    return std::abs(a * b) / gcd(a, b);
}

int main() {
    int num1, num2;

    // Input two numbers
    std::cout << "Enter the first number: ";
    std::cin >> num1;
    std::cout << "Enter the second number: ";
    std::cin >> num2;

    // Compute and display the LCM
    int result = plcm(num1, num2);
    std::cout << "The least common multiple of " << num1 << " and " << num2 << " is " << result << std::endl;

    return 0;
}
