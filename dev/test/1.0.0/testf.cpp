#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include "python.hpp"

// Ajouter l'asyncrone dans certaine partie de mes modules

// g++ -O2 -Oz -Os -s -Wall -Wextra -flto -march=native -Wl,-strip-all -fno-rtti -fno-exceptions -funroll-loops -static -o main.exe testf.cpp -lstdc++ -lgcc & color
// upx --best --lzma --brute -o main_compressed.exe main.exe


int operation_lourde(int x){
    std::this_thread::sleep_for(std::chrono::seconds(2)); 
    return x * 2;
};


int main(){

    std::future<int> resultat = std::async(std::launch::async, operation_lourde, 5);

    print("Calcul en cours...");
    for (unsigned int i = 0; i <= 3000; i++){
        print("Execution de code en attente de la reponce : ", i);
    }
    

    print("Resultat : ", resultat.get());

    return 0;
};