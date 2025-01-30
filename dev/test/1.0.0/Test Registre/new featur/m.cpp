#include <windows.h>
#include <iostream>

// g++ -Os -s -g -o m.exe m.cpp & color

bool Read(const wchar_t* registerPath, const wchar_t* nameKey, DWORD& result) {
    HKEY hKey;
    LONG status = RegOpenKeyW(HKEY_CURRENT_USER, registerPath, &hKey);
    
    if (status != ERROR_SUCCESS) return false;

    DWORD dataSize = sizeof(DWORD);
    status = RegQueryValueExW(hKey, nameKey, nullptr, nullptr, reinterpret_cast<LPBYTE>(&result), &dataSize);

    RegCloseKey(hKey);
    return status == ERROR_SUCCESS;
};

// Ajout du type QWORD (64 bits)
bool Read(const wchar_t* registerPath, const wchar_t* nameKey, ULONGLONG& result) {
    HKEY hKey;
    LONG status = RegOpenKeyW(HKEY_CURRENT_USER, registerPath, &hKey);

    if (status != ERROR_SUCCESS){
        return false;
    }

    DWORD dataSize = sizeof(ULONGLONG);
    status = RegQueryValueExW(hKey, nameKey, nullptr, nullptr, reinterpret_cast<LPBYTE>(&result), &dataSize);

    RegCloseKey(hKey);
    return status == ERROR_SUCCESS;
};


// Lectur du type REG_SZ
bool Read(const wchar_t* registerPath, const wchar_t* nameKey, std::wstring& result) {
    HKEY hKey;
    LONG status = RegOpenKeyW(HKEY_CURRENT_USER, registerPath, &hKey);

    if (status != ERROR_SUCCESS){
        return false;
    }

    DWORD dataSize = 0;
    status = RegQueryValueExW(hKey, nameKey, nullptr, nullptr, nullptr, &dataSize);

    if (status != ERROR_SUCCESS){
        RegCloseKey(hKey);
        return false;
    }

    wchar_t* buffer = new wchar_t[dataSize / sizeof(wchar_t)];

    status = RegQueryValueExW(hKey, nameKey, nullptr, nullptr, reinterpret_cast<BYTE*>(buffer), &dataSize);

    if (status == ERROR_SUCCESS){
        result.assign(buffer);
    }

    delete[] buffer;
    RegCloseKey(hKey);
    return status == ERROR_SUCCESS;
};

// Lecture d'un Bynary



int main(){

    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"OneDrive";
    std::wstring value;
    if (Read(registryPath, keyName, value)){
        std::wcout << L"wstring Value : " << value << "\n";
    }else{
        std::wcout << L"ERROR" << "\n";
    }


    return 0;
};