#include "../../../includes/Torixyna/Math/Pythagore.hpp"

namespace Torixyna::Pythagore{

    // Calcul de l'hypoténuse à partir de deux côtés.
    template <typename T>
    T Hypotenuse(T a, T b){
        return sqrt(pow(a, 2) + pow(b, 2));  
    };

    // Vérifie si un triangle est rectangle en utilisant le théorème de Pythagore.
    // OP : Hypoténuse supposée, PN et NO : les deux autres côtés.
    template <typename T> 
    bool IsRectangle(T OP, T PN, T NO){
        T result_OP, pn, no, result;
        result_OP = pow(OP, 2);
        pn = pow(PN, 2);no = pow(NO, 2);
        result = pn + no;
        if(result_OP == result){
            return true; 
        }else{
            return false;
        }

    };

    // Calcul d'un côté adjacent à partir de l'hypoténuse et d'un autre côté.
    template <typename T>
    T AdjacentSide(T hypotenuse, T otherSide){ 
        return sqrt(pow(hypotenuse, 2) - pow(otherSide, 2));
    };

};