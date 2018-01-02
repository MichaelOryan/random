#include <iostream>
#include <stdexcept>
#include <string>
#include <climits>

void promptUserForNumber(std::ostream & out = std::cout) {
    out << "Enter a number to double: ";
}

void outputDoubleNumber(int number, std::ostream & out = std::cout) {
    out << "Double your number is " << number << std::endl;
}

void removeLine(std::istream & in = std::cin) {
    std::string bad_chars;
    getline(in, bad_chars);
}

void promptValidIntegerRange(int min, int max, std::ostream & out = std::cout) {
    out << "Please enter an integer between " << min << " and " << max << ": ";;
}

bool inRange(int n, int min, int max) {
    return n >= min && n <= max;
}

int readInt(int min, int max, std::istream & in = std::cin) {
    int number;
    
    in >> number;
    bool readIntSucceeded = in.good();
    
    while(!readIntSucceeded || !inRange(number, min, max)) {
        in.clear();
        
        removeLine(in);
        
        promptValidIntegerRange(min, max);

        in >> number;
        readIntSucceeded = in.good();
    }
    
    return number;
}

bool doubleOverflow(int number) {
    return number > INT_MAX / 2;
}

bool doubleUnderflow(int number) {
    return number < INT_MIN / 2;
}

int doubleNumber(int number) {
  
    if(doubleOverflow(number)) {
        throw std::overflow_error("Overflow error!");
    } 
    else if(doubleUnderflow(number)) {
        throw std::underflow_error("Underflow error!");
    }
    
    int double_number = number * 2;
    
    return double_number;
}

int halveNumber(int number) {
    return number / 2;
}

void readAndDoubleNumber(std::istream & in = std::cin, std::ostream & out = std::cout) {
    try {
    
        promptUserForNumber(out);
        
        int minimum_number = halveNumber(INT_MIN);
        int maximum_number = halveNumber(INT_MAX);
        
        int number = readInt(minimum_number, maximum_number, in);
        int double_number = doubleNumber(number);
        
        outputDoubleNumber(double_number, out);
    }
    catch(std::runtime_error e) {
        std::cerr << e.what() << std::endl;
    }
    catch(std::exception e) {
        std::cerr << e.what() << std::endl;
    }
    catch(...) {
        std::cerr << "Unknown Error" << std::endl;
    }
    
}

int main() {
    readAndDoubleNumber(std::cin, std::cout);
    
    return 0;
}
