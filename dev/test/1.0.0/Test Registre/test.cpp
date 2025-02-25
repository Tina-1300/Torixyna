#define INCLUDE_REGISTRE
#include <iostream>
#include <Torixyna/Torixyna.hpp>

// g++ -Os -s -o test.exe test.cpp -lTorixyna & color

void TestWriteDwordRegistry(){
    Torixyna::Registre::Luna luna(HKEY_CURRENT_USER);
    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"test";
    DWORD value = 12345;

    if(luna.Write(registryPath, keyName, value) == true){
        std::cout << "La valeur a bien ete ecrite" << "\n";
        std::cin.get();
    }else{
        std::cerr << "Error" << "\n";
        std::cin.get();
    }
};

// void TestWriteStringRegistry(){
//     Torixyna::Registre::Luna luna(HKEY_CURRENT_USER);
//     const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
//     const wchar_t* keyName = L"test";
//     const wchar_t* value = L"Alex";

//     if(luna.Write(registryPath, keyName, value) == true){
//         std::cout << "La valeur a bien ete ecrite" << "\n";
//         std::cin.get();
//     }else{
//         std::cerr << "Error" << "\n";
//         std::cin.get();
//     }
// };

void TestWriteBynaryRegistry(){
    Torixyna::Registre::Luna luna(HKEY_CURRENT_USER);
    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"test";
    BYTE value[] = { 0x01, 0x02, 0x03, 0x04 };

    if(luna.Write(registryPath, keyName, value) == true){
        std::cout << "La valeur a bien été écrite" << "\n";
        std::cin.get();
    }else{
        std::cerr << "Error" << "\n";
        std::cin.get();
    }
};

void TestWriteQword(){
    Torixyna::Registre::Luna luna(HKEY_CURRENT_USER);
    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"test";
    unsigned __int64 value = 1234567890123456;

    if(luna.Write(registryPath, keyName, value) == true){
        std::cout << "La valeur a bien ete ecrite" << "\n";
        std::cin.get();
    }else{
        std::cerr << "Error" << "\n";
        std::cin.get();
    }
};


//void TestDeleteRegistry(){
//     Torixyna::Registre::Luna luna(HKEY_CURRENT_USER);
//     const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
//     const wchar_t* keyName = L"test";

//     if(luna.Delete(registryPath, keyName)){
//         std::cout << "La cle a bien été suprimmer" << "\n";
//         std::cin.get();
//     }else{
//         std::cerr << "Error" << "\n";
//         std::cin.get();
//     }
// };

// à tester : 

// Problème affiche pas les bon truc regarder ce qu'il ne va pas dans le code 
void TestRead_BINARY(){
    Torixyna::Registre::Luna luna(HKEY_CURRENT_USER);

    std::vector<BYTE> binaryData;
    if (luna.Read(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", L"test", binaryData)){
        // valeur lue avec sucès 
        for (int i = 0; i < binaryData.size(); i++){
            std::wcout << binaryData.at(i) << "\n";
        }
        
    }else{
        std::wcout << L"Échec de la lecture de la valeur binaire." << "\n";
    }
};

void TestRead_REG_MULTI_SZ(){
    Torixyna::Registre::Luna luna(HKEY_CURRENT_USER);

    std::vector<std::wstring> values;
    if (luna.Read(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", L"MaValeurMultiSZ", values)){
        std::wcout << L"Valeur REG_MULTI_SZ lue avec succès :\n";
        for (const auto& val : values){
            std::wcout << L" - " << val << "\n";
        }
    }else{
        std::wcout << L"Échec de la lecture de la valeur REG_MULTI_SZ." << "\n";
    }
};

void TestRead_REG_EXPAND_SZ(){
    Torixyna::Registre::Luna luna(HKEY_CURRENT_USER);

    std::wstring value;

    if (luna.Read(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", L"MaValeurExpandSZ", value)){
        std::wcout << L"Valeur REG_EXPAND_SZ lue avec succès : " << value << "\n";
    }else{
        std::wcout << L"Échec de la lecture de la valeur REG_EXPAND_SZ." << "\n";
    }
};


void TestWrite_REG_MULTI_SZ(){
    Torixyna::Registre::Luna luna(HKEY_CURRENT_USER);

    std::vector<std::wstring> values = {L"Valeur1", L"Valeur2", L"Valeur3"};
    if (luna.Write( L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 
        L"MaValeurMultiSZ", values)){
        std::wcout << L"Valeur écrite avec succès !" << "\n";
    }else{
        std::wcout << L"Échec de l'écriture de la valeur." << "\n";
    }
};

void TestWrite_REG_EXPAND_SZ(){
    Torixyna::Registre::Luna luna(HKEY_CURRENT_USER);

    if (luna.Write(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", L"MaValeurExpandSZ", L"%SystemRoot%\\System32")){
        std::wcout << L"Valeur REG_EXPAND_SZ écrite avec succès !" << "\n";
    } else {
        std::wcout << L"Échec de l'écriture de la valeur REG_EXPAND_SZ." << "\n";
    }
};

int main(){
    SetConsoleOutputCP(CP_UTF8);

    //TestWriteBynaryRegistry();

    TestRead_BINARY();

    //Ces fonction Marche :

    //TestWriteDwordRegistry(); 
    //TestWriteStringRegistry();
    //TestWriteBynaryRegistry();

    //TestWriteQword();
    //TestDeleteRegistry();

    return 0;
};