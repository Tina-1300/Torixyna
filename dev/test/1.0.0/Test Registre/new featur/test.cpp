#include <iostream>
#include <windows.h>
#include <string>

#include <thread>
#include <chrono>

bool SavingRegistre(HKEY RootKey, const wchar_t * Register){
    HKEY hkey;
    LONG result = RegOpenKeyExW(RootKey, Register, 0, KEY_READ, &hkey);

    if(result != ERROR_SUCCESS){
        return false;
    }

    
    //result = RegEnumKeyEx(hkey, 0,);

};


void DisplayLoading(){
    for(;;){
        std::cout << "\b\b\b\b\b\b\b\b\b\bLoading..." << std::flush;
        Sleep(100);
        std::cout << "\b\b\b\b\b\b\b\b\b\blOading..." << std::flush;
        Sleep(100);
        std::cout << "\b\b\b\b\b\b\b\b\b\bloAding..." << std::flush;
        Sleep(100);
        std::cout << "\b\b\b\b\b\b\b\b\b\bloaDing..." << std::flush;
        Sleep(100);
        std::cout << "\b\b\b\b\b\b\b\b\b\bloadIng..." << std::flush;
        Sleep(100);
        std::cout << "\b\b\b\b\b\b\b\b\b\bloadiNg..." << std::flush;
        Sleep(100);
        std::cout << "\b\b\b\b\b\b\b\b\b\bloadinG..." << std::flush;
        Sleep(100);
    }
}

void TypeWriteEffect(const std::string& message, int microsecond){
    for(const auto c : message){
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::microseconds(microsecond));
    }
    std::cout << "\n";
};


int main(){
    
    //SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run
    if(SavingRegistre(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run")){
        std::cout << "Fichier enregistrer avec succes" << "\n";
    }else{
        TypeWriteEffect("Erreur tu code comme un petit pd !!!", 40000);
        DisplayLoading();
    }
    

    return 0;
}

