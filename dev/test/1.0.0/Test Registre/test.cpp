#define INCLUDE_REGISTRE
#include <iostream>
#include <Torixyna/Torixyna.hpp>

// g++ -Os -s -o test.exe test.cpp -lTorixyna & color




void TestWriteDwordRegistry(){
    Torixyna::Registre::Luna luna(HKEY_CURRENT_USER);
    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"test";
    DWORD value = 12345;

    if(luna.Write(registryPath, keyName, value, REG_DWORD) == true){
        std::cout << "La valeur a bien ete ecrite" << "\n";
        std::cin.get();
    }else{
        std::cerr << "Error" << "\n";
        std::cin.get();
    }
};

// void TestWriteStringRegistry(){
//     Torixyna::Registre::Luna<const wchar_t*> luna(HKEY_CURRENT_USER);
//     const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
//     const wchar_t* keyName = L"test";
//     const wchar_t* value = L"Alex";

//     if(luna.Write(registryPath, keyName, value, REG_SZ) == true){
//         std::cout << "La valeur a bien ete ecrite" << "\n";
//         std::cin.get();
//     }else{
//         std::cerr << "Error" << "\n";
//         std::cin.get();
//     }
// };

// void TestWriteBynaryRegistry(){
//     Torixyna::Registre::Luna<BYTE[]> luna(HKEY_CURRENT_USER);
//     const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
//     const wchar_t* keyName = L"test";
//     BYTE value[] = { 0x01, 0x02, 0x03, 0x04 };

//     if(luna.Write(registryPath, keyName, value, REG_BINARY) == true){
//         std::cout << "La valeur a bien ete ecrite" << "\n";
//         std::cin.get();
//     }else{
//         std::cerr << "Error" << "\n";
//         std::cin.get();
//     }
// };

void TestWriteQword(){
    Torixyna::Registre::Luna luna(HKEY_CURRENT_USER);
    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"test";
    unsigned __int64 value = 1234567890123456;

    if(luna.Write(registryPath, keyName, value, REG_QWORD) == true){
        std::cout << "La valeur a bien ete ecrite" << "\n";
        std::cin.get();
    }else{
        std::cerr << "Error" << "\n";
        std::cin.get();
    }
};


// void TestDeleteRegistry(){
//     Torixyna::Registre::Luna<DWORD> luna(HKEY_CURRENT_USER);
//     const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
//     const wchar_t* keyName = L"test";

//     if(luna.Delete(registryPath, keyName, REG_NONE)){
//         std::cout << "La cle a bien ete suprimmer" << "\n";
//         std::cin.get();
//     }else{
//         std::cerr << "Error" << "\n";
//         std::cin.get();
//     }
// };


int main(){
    //Ces fonction Marche :

    TestWriteDwordRegistry(); 
    //TestWriteStringRegistry();
    //TestWriteBynaryRegistry();

    //TestWriteQword();
    //TestDeleteRegistry();

}