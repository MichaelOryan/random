#include <iostream>
#include <stdexcept>
#include <string>
#include <limits>

void promptUserForNumber(std::ostream & out = std::cout) {
    out << "Enter a number to double: ";
}

template<class T>
void outputDoubleNumber(T number, std::ostream & out = std::cout) {
    out << "Double your number is " << number << std::endl;
}

void removeLine(std::istream & in = std::cin) {
    std::string ignored_chars;
    getline(in, ignored_chars);
}

template<class T>
void promptValidNumberRange(T min, T max, std::ostream & out = std::cout) {
    out << "Please enter a number between " << min << " and " << max << ": ";;
}

template<class T>
bool inRange(T number, T min, T max) {
    return number >= min && number <= max;
}

template<class T>
T readInt(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max(), std::istream & in = std::cin) {
    T number;
    
    in >> number;
    bool readNumberSucceeded = in.good();
    
    while(!readNumberSucceeded || !inRange(number, min, max)) {
        in.clear();
        
        removeLine(in);
        
        promptValidNumberRange(min, max);

        in >> number;
        readNumberSucceeded = in.good();
    }
    
    return number;
}

template<class T>
T halveNumber(T number) {
    return number / 2;
}

template<class T>
bool doublingWillOverflow(T number) {
    return number > halveNumber(std::numeric_limits<T>::max());
}

template<class T>
bool doublingWillUnderflow(T number) {
    return number < halveNumber(std::numeric_limits<T>::min());
}

template<class T>
T doubleNumber(T number) {
    
    if(doublingWillOverflow(number)) {
        throw std::overflow_error("Overflow error!");
    } 
    else if(doublingWillUnderflow(number)) {
        throw std::underflow_error("Underflow error!");
    }
    
    T double_number = number * 2;
    
    return double_number;
}

template<class T>
void readAndDoubleNumber(std::istream & in = std::cin, std::ostream & out = std::cout) {
    try {
        promptUserForNumber(out);
        
        T minimum_number = halveNumber(std::numeric_limits<T>::min());
        T maximum_number = halveNumber(std::numeric_limits<T>::max());
        
        T number = readInt(minimum_number, maximum_number, in);
        T double_number = doubleNumber(number);
        
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
    readAndDoubleNumber<long long int>(std::cin, std::cout);
    
    return 0;
}
