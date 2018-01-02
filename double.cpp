#include <iostream>
#include <stdexcept>
#include <string>
#include <climits>

void promptUserForNumber() {
    std::cout << "Enter a number to double: ";
}

void outputNumber(int number) {
    std::cout << "Double your number is " << number << std::endl;
}

void removeLine() {
    std::string bad_chars;
    getline(std::cin, bad_chars);
}

void promptValidIntegerRange() {
    std::cout << "Please enter an integer between " << INT_MIN << " and " << INT_MAX << ": ";;
}

int readInt() {
    int number;
    
    bool readIntSucceeded = (std::cin >> number);
    
    while(!readIntSucceeded) {
        std::cin.clear();
        
        removeLine();
        
        promptValidIntegerRange();
        
        readIntSucceeded = (std::cin >> number);
    }
    
    return number;
}

bool doubleOverflow(int number, int double_number) {
    return number > 0 && double_number < number;
}

bool doubleUnderflow(int number, int double_number) {
    return number < 0 && double_number > number;
}

int doubleNumber(int number) {
    int double_number = number * 2;
    
    if(doubleOverflow(number, double_number)) {
        throw std::overflow_error("Overflow error!");
    } 
    else if(doubleUnderflow(number, double_number)) {
        throw std::underflow_error("Underflow error!");
    }
    return double_number;
}

int main() {
    try {
        promptUserForNumber();
        
        int number = readInt();
        int double_number = doubleNumber(number);
        
        outputNumber(double_number);
    }
    catch(std::runtime_error e) {
        std::cout << e.what() << std::endl;
    }
    catch(std::exception e) {
        std::cout << e.what() << std::endl;
    }
    catch(...) {
        std::cout << "Unknown Error" << std::endl;
    }
    
    return 0;
}
