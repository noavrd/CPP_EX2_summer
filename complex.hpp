// noavrd@gmail.com

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
     * Constructor with the real and imagine parts
     * 
     * @param real The real part of the complex number
     * @param imag The imagine part of the complex number
     */
    Complex(double real, double imag) : real(real), imag(imag) {}

    /**     
     * @return The real part of the complex number
     */
    double get_real() const { return real; }

    /**
     * @return The imagine part of the complex number
     */
    double get_imag() const { return imag; }

    /**
     * Compares this complex number with another with bigger-than
     * 
     * First, it compares the real part, then if equal, compares by imagine part
     * 
     * @param other The complex number to compare
     * @return true if this complex number is bigger, false if not
     */
    bool operator>(const Complex& other) const {
        return (real > other.real) || (real == other.real && imag > other.imag);
    }

    /**
     * Compares this complex number with another for equality
     * 
     * It checks if both the real and imagine parts are the same
     * 
     * @param other The complex number to compare
     * @return true if both complex numbers are equal, false if not
     */
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    /**
     * Print the complex number to an output stream in the format "real + imag + i"
     * 
     * @param os The output stream
     * @param c The complex number to print
     * @return ostream& The output stream
     */
    friend ostream& operator<<(ostream& os, const Complex& c) {
        os << c.real << " + " << c.imag << "i";
        return os;
    }

};

#endif // COMPLEX_HPP
