#pragma once 
#include <cmath>

namespace Torixyna::Math::Pythagore{

    // Calcul de l'hypoténuse à partir de deux côtés.
    template <typename T>
    T Hypotenuse(T SideA, T SideB);

    // Vérifie si un triangle est rectangle en utilisant le théorème de Pythagore.
    // Hypotenuse : Hypoténuse supposée, SideA et SideB : les deux autres côtés.
    template <typename T> 
    bool IsRectangle(T Hypotenuse, T SideA, T SideB);

    // Calcul d'un côté adjacent à partir de l'hypoténuse et d'un autre côté.
    // via la reciproque 
    template <typename T>
    T AdjacentSide(T Hypotenuse, T otherSide);

};