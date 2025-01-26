#pragma once

namespace Torixyna::Math::Fraction{

    template <typename T>
    struct Fraction{
        T numerateur;
        T denominateur;
    };

    // Aditionne une fraction
    template <typename T>
    Fraction<T> add(const Fraction<T>& F1, const Fraction<T>& F2);

    // Soustrait une fraction
    template <typename T>
    Fraction<T> sous(const Fraction<T>& F1, const Fraction<T>& F2);

    // Multiply une fraction 
    template <typename T>
    Fraction<T> multy(const Fraction<T>& F1, const Fraction<T>& F2);

    // divise une fraction
    template <typename T>
    Fraction<T> divi(const Fraction<T>& F1, const Fraction<T>& F2);

    // Return une fraction
    template <typename T>
    Fraction<T> CalculeFraction(const Fraction<T>& F1);

};