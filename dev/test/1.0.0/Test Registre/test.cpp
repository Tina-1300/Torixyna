#define INCLUDE_REGISTRE
#include <iostream>
#include <iomanip>
#include <Torixyna/Torixyna.hpp>

// g++ -Os -s -o test.exe test.cpp -lTorixyna & color

void TestWriteDwordRegistry(){
    Torixyna::Registry::Luna luna(HKEY_CURRENT_USER);
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

void TestWriteStringRegistry(){
    Torixyna::Registry::Luna luna(HKEY_CURRENT_USER);
    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"test";
    const wchar_t* value = L"Alex";

    if(luna.Write(registryPath, keyName, value) == true){
        std::cout << "La valeur a bien ete ecrite" << "\n";
        std::cin.get();
    }else{
        std::cerr << "Error" << "\n"; 
        std::cin.get();
    }
};

void TestWriteBynaryRegistry(){
    Torixyna::Registry::Luna luna(HKEY_CURRENT_USER);
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
    Torixyna::Registry::Luna luna(HKEY_CURRENT_USER);
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


void TestWrite_REG_MULTI_SZ(){
    Torixyna::Registry::Luna luna(HKEY_CURRENT_USER);

    std::vector<std::wstring> values = {L"Valeur1", L"Valeur2", L"Valeur3"};
    if (luna.Write( L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 
        L"MaValeurMultiSZ", values)){
        std::wcout << L"Valeur écrite avec succès !" << "\n";
    }else{
        std::wcout << L"Échec de l'écriture de la valeur." << "\n";
    }
};

void TestWrite_REG_EXPAND_SZ(){
    Torixyna::Registry::Luna luna(HKEY_CURRENT_USER);

    if (luna.Write(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", L"MaValeurExpandSZ", L"%SystemRoot%\\System32")){
        std::wcout << L"Valeur REG_EXPAND_SZ écrite avec succès !" << "\n";
    } else {
        std::wcout << L"Échec de l'écriture de la valeur REG_EXPAND_SZ." << "\n";
    }
};




// Ajouter Read à la doc + delete 

void TestDeleteRegistry(){
     Torixyna::Registry::Luna luna(HKEY_CURRENT_USER);
     const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
     const wchar_t* keyName = L"test";

     if(luna.Delete(registryPath, keyName)){
         std::cout << "La cle a bien été suprimmer" << "\n";
         std::cin.get();
     }else{
         std::cerr << "Error" << "\n";
         std::cin.get();
    }
};

// -------------------------------------------------------------------------------------


// à tester : (tout marche) 

void TestRead_BINARY(){
    Torixyna::Registry::Luna luna(HKEY_CURRENT_USER);
    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"test";

    std::vector<BYTE> binaryData;
    if (luna.Read(registryPath, keyName, binaryData)){
        std::wcout << L"Valeur binaire lue : ";
        for (size_t i = 0; i < binaryData.size(); i++){
            std::wcout << std::hex << std::setw(2) << std::setfill(L'0') << (int)binaryData[i] << L" ";
        }
        std::wcout << std::endl;
    }else{
        std::wcout << L"Échec de la lecture de la valeur binaire." << std::endl;
    }
};




void TestRead_REG_MULTI_SZ(){
    Torixyna::Registry::Luna luna(HKEY_CURRENT_USER);

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
    Torixyna::Registry::Luna luna(HKEY_CURRENT_USER);

    std::wstring value;

    if (luna.Read(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", L"MaValeurExpandSZ", value)){
        std::wcout << L"Valeur REG_EXPAND_SZ lue avec succès : " << value << "\n";
    }else{
        std::wcout << L"Échec de la lecture de la valeur REG_EXPAND_SZ." << "\n";
    }
};


void TestRead_DWORD(){
    Torixyna::Registry::Luna luna(HKEY_CURRENT_USER);
    DWORD value;
    if(luna.Read(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", L"testDWORD", value) == true){
        std::cout << "La valeur est : " << value << "\n";
    }else{
        std::cout << "Error" << "\n";
    }

}

void TestRead_QDWORD(){
    Torixyna::Registry::Luna luna(HKEY_CURRENT_USER);
    unsigned __int64 val;
    if(luna.Read(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", L"testQword", val) == true){
        std::cout << "La valeur est : " << val << "\n";
    }else{
        std::cout << "Error" << "\n";
    }

}


void TEST_GET_INFO_TAILL(){
    Torixyna::Registry::LunaInfo luna(HKEY_CURRENT_USER);
    Torixyna::Registry::RegistrySizeInfo info;
    if(luna.GetSizeRegistry(info) == true){
        std::cout << "Taille Actuelle : " << info.currentSize << "\n";
        std::cout << "Taille Maximal : " << info.maxSize << "\n";
    }else{
        std::cout << "Error" << "\n";
    }

}


void Test_Get_value_type(){
    Torixyna::Registry::LunaInfo luna(HKEY_CURRENT_USER);
    Torixyna::Registry::RegistryValueInfo info;

    if (luna.GetRegisterTypeValue(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", L"testQword", info) == true){
        if(info.valueNameT == REG_QWORD){
            std::cout << "La valeur et un QWORD" << "\n";
        }
    }

}


void test_activate_extension_file(){
    Torixyna::Registry::LunaConfig l;
    
    if (l.SetsFileExtensionsVisibility(true)){
        std::cout << "Les extension des fichier sont visible" << "\n";
    }else{
        std::cout << "Error" << "\n";
    }

}


void test_display_element_masquer(){

    Torixyna::Registry::LunaConfig l;
    
    if (l.SetsShowItemsHide(true)){
        std::cout << "affiche les éléments masquer" << "\n";
    }else{
        std::cout << "Error" << "\n";
    }

}


void test_activate_case_a_cocher(){

    Torixyna::Registry::LunaConfig l;
    
    if (l.SetsTheStatusOfCheckboxes(true)){
        std::cout << "Les cases à coché sont activer" << "\n";
    }else{
        std::cout << "Error" << "\n";
    }

}

void test_display_walper_screen(){

    Torixyna::Registry::LunaConfig l;
    const wchar_t* pathWalpper = L"Background.jpg";

    if (l.SetWallpaper(pathWalpper)){
        std::cout << "Les cases à coché sont activer" << "\n";
    }else{
        std::cout << "Error" << "\n";
    }

}


int main(){
    SetConsoleOutputCP(CP_UTF8);

    //TestWriteBynaryRegistry();

    //TestRead_BINARY();

    //Ces fonction Marche :

    //TestWriteDwordRegistry(); 
    //TestWriteStringRegistry();
    //TestWriteBynaryRegistry();

    //TestWriteQword();
    //TestDeleteRegistry();

    return 0;
};