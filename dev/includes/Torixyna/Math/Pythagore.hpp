#pragma once 
#include <iostream>
#include <cmath>

namespace Torixyna::Pythagore{

    // Calcul de l'hypoténuse à partir de deux côtés.
    template <typename T>
    T Hypotenuse(T a, T b);

    // Vérifie si un triangle est rectangle en utilisant le théorème de Pythagore.
    // OP : Hypoténuse supposée, PN et NO : les deux autres côtés.
    template <typename T> 
    bool IsRectangle(T OP, T PN, T NO);

    // Calcul d'un côté adjacent à partir de l'hypoténuse et d'un autre côté.
    template <typename T>
    T AdjacentSide(T hypotenuse, T otherSide);

};