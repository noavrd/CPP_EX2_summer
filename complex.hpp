#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>

using namespace std; 

class Complex {
private:
    // The real & imagine of the current complex number
    double real; 
    double imag; 
public:
    /**
     * @brief Constructs a Complex number with the specified real and imaginary parts.
     * 
     * @param real The real part of the complex number.
     * @param imag The imaginary part of the complex number.
     */
    Complex(double real, double imag) : real(real), imag(imag) {}

    /**
     * @brief Returns the real part of the complex number.
     * 
     * @return double The real part.
     */
    double get_real() const { return real; }

    /**
     * @brief Returns the imaginary part of the complex number.
     * 
     * @return double The imaginary part.
     */
    double get_imag() const { return imag; }

    /**
     * @brief Compares this complex number with another for greater-than.
     * 
     * Compares first by real part; if equal, compares by imaginary part.
     * 
     * @param other The complex number to compare against.
     * @return true if this complex number is greater; false otherwise.
     */
    bool operator>(const Complex& other) const {
        return (real > other.real) || (real == other.real && imag > other.imag);
    }

    /**
     * @brief Compares this complex number with another for equality.
     * 
     * Two complex numbers are equal if both their real and imaginary parts are the same.
     * 
     * @param other The complex number to compare against.
     * @return true if both complex numbers are equal; false otherwise.
     */
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    /**
     * @brief Outputs the complex number to an output stream.
     * 
     * Prints the complex number in the format "real + imagi".
     * 
     * @param os The output stream.
     * @param c The complex number to output.
     * @return ostream& The output stream.
     */
    friend ostream& operator<<(ostream& os, const Complex& c) {
        os << c.real << " + " << c.imag << "i";
        return os;
    }

};

#endif // COMPLEX_HPP
