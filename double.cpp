#include <iostream>
#include <stdexcept>
#include <string>
#include <limits>


// Function prototypes

template<class T>
T DoubleNumber(T number);

template<class T>
bool IsDoubleOverflow(T number);

template<class T>
bool IsDoubleUnderflow(T number);

template<class T>
T HalveNumber(T number);

template<class T>
bool IsInRange(T number, T min, T max);

template<class T>
void OutputDoubleNumber(T number, std::ostream & out = std::cout);

void PromptUserForNumber(std::ostream & out = std::cout);

template<class T>
void PromptValidNumberRange(T min, T max, std::ostream & out = std::cout);

template<class T>
void ReadAndDoubleNumber(std::istream & in = std::cin,
                         std::ostream & out = std::cout);

template<class T>
T ReadInt(T min = std::numeric_limits<T>::min(),
          T max = std::numeric_limits<T>::max(),
          std::istream & in = std::cin);

void RemoveLine(std::istream & in = std::cin);


// Function Implementations

int main() {
    ReadAndDoubleNumber<long long int>(std::cin, std::cout);
    
    return 0;
}

template<class T>
void ReadAndDoubleNumber(std::istream & in, std::ostream & out) {
    try {
        PromptUserForNumber(out);
        
        T minimum_number = HalveNumber(std::numeric_limits<T>::min());
        T maximum_number = HalveNumber(std::numeric_limits<T>::max());
        
        T number = ReadInt(minimum_number, maximum_number, in);
        T double_number = DoubleNumber(number);
        
        OutputDoubleNumber(double_number, out);
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


void PromptUserForNumber(std::ostream & out) {
    out << "Enter a number to double: ";
}

template<class T>
T HalveNumber(T number) {
    return number / 2;
}

template<class T>
T ReadInt(T min, T max, std::istream & in) {
    T number;
    
    in >> number;
    bool read_number_succeeded = in.good();
    
    while (!read_number_succeeded || !IsInRange(number, min, max)) {
        in.clear();
        
        RemoveLine(in);
        
        PromptValidNumberRange(min, max);

        in >> number;
        read_number_succeeded = in.good();
    }
    
    return number;
}

template<class T>
bool IsInRange(T number, T min, T max) {
    return (number >= min) && (number <= max);
}

void RemoveLine(std::istream & in) {
    std::string ignored_chars;
    getline(in, ignored_chars);
}

template<class T>
void PromptValidNumberRange(T min, T max, std::ostream & out) {
    out << "Please enter a number between ";
    out << min << " and " << max << ": ";
}

template<class T>
T DoubleNumber(T number) {
    
    if (IsDoubleOverflow(number)) {
        throw std::overflow_error("Overflow error!");
    } else if (IsDoubleUnderflow(number)) {
        throw std::underflow_error("Underflow error!");
    }
    
    T double_number = number * 2;
    
    return double_number;
}

template<class T>
bool IsDoubleOverflow(T number) {
    return number > HalveNumber(std::numeric_limits<T>::max());
}

template<class T>
bool IsDoubleUnderflow(T number) {
    return number < HalveNumber(std::numeric_limits<T>::min());
}

template<class T>
void OutputDoubleNumber(T number, std::ostream & out) {
    out << "Double your number is " << number << std::endl;
}

