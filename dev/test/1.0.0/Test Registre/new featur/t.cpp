#include <iostream>
#include <windows.h>

/*
https://learn.microsoft.com/fr-fr/windows/win32/sysinfo/registry-reference


*/



struct Rust{
    bool status; // si il et à true tout ses bien passé aucune error
    const char* valueName; // valeur si ses un REG_SZ ou autre...
    DWORD valueNameT; // valeur si ses un REG_SZ ou autre...
};

Rust GetRegisterTypeValue(HKEY RootKey, const wchar_t * Register, const wchar_t* valueName, Rust& data){
    HKEY keyHandle;
    DWORD dataType = 0;
    LONG result = RegOpenKeyExW(RootKey, Register, 0, KEY_QUERY_VALUE, &keyHandle);

    if(result != ERROR_SUCCESS){
        data.status = false;
        return data;
    }

    result = RegQueryValueExW(keyHandle, valueName, NULL, &dataType, NULL, NULL);

    if (result != ERROR_SUCCESS){
        data.status = false;
        RegCloseKey(keyHandle);
        return data;
    }

    data.status = true;
    data.valueName = (dataType == REG_SZ) ? "REG_SZ": (dataType == REG_BINARY) ? "REG_BINARY": (dataType == REG_DWORD) ? "REG_DWORD": (dataType == REG_QWORD) ? "REG_QWORD": (dataType == REG_MULTI_SZ) ? "REG_MULTI_SZ": (dataType == REG_LINK) ? "REG_LINK": (dataType == REG_EXPAND_SZ) ? "REG_EXPAND_SZ": (dataType == REG_NONE) ? "REG_NONE": "Error";
    data.valueNameT = (dataType == REG_SZ) ? REG_SZ: (dataType == REG_BINARY) ? REG_BINARY: (dataType == REG_DWORD) ? REG_DWORD: (dataType == REG_QWORD) ? REG_QWORD: (dataType == REG_MULTI_SZ) ? REG_MULTI_SZ: (dataType == REG_LINK) ? REG_LINK: (dataType == REG_EXPAND_SZ) ? REG_EXPAND_SZ: (dataType == REG_NONE) ? REG_NONE: -808;

    RegCloseKey(keyHandle);

    return data;
};



// ---------------------------------------------------------------------------------------------------


// fonction pour énuméré tout les clé d'un dossier de registre

struct RustKey{
    bool status; // si ses à true tout ses bien passé pas d'error 
};


RustKey GetKeysRegister(HKEY RootKey, const wchar_t * Register, const wchar_t* valueName, RustKey& data){
    HKEY keyHandle;
    LONG result = RegOpenKeyExW(RootKey, Register, 0, KEY_ENUMERATE_SUB_KEYS, &keyHandle);

    if(result != ERROR_SUCCESS){
        data.status = false;
        return data;
    }
    

}



// foncton pour modifier la valeur des clé 


// fonction pour lire la valeur d'une clé 






int main(){



/*
    Rust r;

    GetRegisterTypeValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", L"OneDrive", r);

    if(r.status != true){
        std::cerr << "Error" << "\n";
    }

    std::cout << r.valueName << "\n";
*/
    //HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"

    return 0;
}