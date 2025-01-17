#include <windows.h>
#include <iostream>


// g++ -Os -s -g -o m.exe m.cpp & color
//https://doc.ubuntu-fr.org/gdb

struct ReadRegister{
    BYTE value; // valeur de la clé stocker dans les registre
    bool status; // Si elle et à true aucune error c'est passé
};

// BUG n'affiche pas les valeur binaire 
ReadRegister ReadRegistryByte(const wchar_t * Register, const wchar_t * NameKey, ReadRegister& data){
    HKEY keyHandle;
    LONG result = RegOpenKeyExW(HKEY_CURRENT_USER, Register, 0, KEY_QUERY_VALUE, &keyHandle);
    
    if(result != ERROR_SUCCESS){
        data.status = false;
        return data;
    }

    BYTE  ValueMSG;
    DWORD  ptrValue = sizeof(ValueMSG);

    result = RegQueryValueExW(keyHandle, NameKey, NULL, NULL, &ValueMSG, &ptrValue);

    if(result != ERROR_SUCCESS){
        data.status = false;
        RegCloseKey(keyHandle);
        return data;
    }    

    data.status = true;
    data.value = ValueMSG;

    RegCloseKey(keyHandle);

    return data;
};



int main(){

    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"MySetting";

    ReadRegister  v;
    ReadRegistryByte(registryPath, keyName, v);
    std::cout << &v << "\n";


    return 0;
};

/*
    bool AddRegistryKeyDWORD(const wchar_t * Register, const WCHAR * NameKey, DWORD Value){
        HKEY hKey;
        LONG result = RegOpenKeyW(HKEY_CURRENT_USER, Register, &hKey);

        if (result != ERROR_SUCCESS){
            return false;
        }

        DWORD ValueSize = sizeof(DWORD);
        result = RegSetValueExW(hKey, NameKey, 0, REG_DWORD, (const BYTE*)&Value, ValueSize); 
        RegCloseKey(hKey);

        if (result != ERROR_SUCCESS){
            return false; 
        }
        return true;
    };

    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"MySetting";
    DWORD value = 12345;
    AddRegistryKeyDWORD(registryPath, keyName, value);


    
    bool AddRegistryKeyBINARY(const wchar_t * Register, const WCHAR * NameKey, const BYTE* BinaryData){
        HKEY hKey;
        LONG result = RegOpenKeyW(HKEY_CURRENT_USER, Register, &hKey);

        if (result != ERROR_SUCCESS){
            return false;
        }

        DWORD dataSize = sizeof(BinaryData);
        result = RegSetValueExW(hKey, NameKey, 0, REG_BINARY, BinaryData, dataSize); 
        RegCloseKey(hKey);

        if (result != ERROR_SUCCESS){
            return false; 
        }
        return true;
    };

    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"MySetting";
    BYTE binaryData[] = { 0x01, 0x02, 0x03, 0x04 };
    AddRegistryKeyBINARY(registryPath, keyName, binaryData);
*/