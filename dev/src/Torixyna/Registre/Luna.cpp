#include "../../../includes/Torixyna/Registre/Luna.hpp"

namespace Torixyna::Registre{

    // ---------------------------- Luna -----------------------------------------


    // Constructeur surchargé : permet de passer une clé racine spécifique
    Luna::Luna(HKEY RootKey) : m_RootKey(RootKey) {}


    bool Luna::AddRegistryKey(const wchar_t * Register, const WCHAR * NameKey, const WCHAR * Value){
        HKEY hKey;
        LONG result = RegOpenKeyW(m_RootKey, Register, &hKey);

        if (result != ERROR_SUCCESS){
            return false;
        }

        DWORD ValueSize = (wcslen(Value) + 1) * sizeof(WCHAR);
        result = RegSetValueExW(hKey, NameKey, 0, REG_SZ, (const BYTE*)Value, ValueSize); 
        RegCloseKey(hKey);

        if (result != ERROR_SUCCESS){
            return false; 
        }
        return true;
    };

    bool Luna::DeleteRegistryKey(const wchar_t * Register, const WCHAR * NameKey){
        HKEY hKey;
        LONG result = RegOpenKeyW(m_RootKey, Register, &hKey);
        if (result != ERROR_SUCCESS){
            return false;
        }
        result = RegDeleteValueW(hKey, NameKey); 
        RegCloseKey(hKey);

        if (result != ERROR_SUCCESS){
            return false;
        }
        return true;
    };

    
    INFO_TAILL Luna::GetSizeRegistry(INFO_TAILL& data){
        DWORD T_MAX, T_ACTUELL;
        GetSystemRegistryQuota(&T_MAX, &T_ACTUELL);
        data.TaillMaximal, data.TaillActuell = T_MAX / (1024*1024), T_ACTUELL / (1024*1024);
        return data;
    };

    Rust Luna::GetRegisterTypeValue(HKEY RootKey, const wchar_t * Register, const wchar_t* valueName, Rust& data){
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

    //------------------------------------------------------------------------------------------------

    //--------------------------------- LunaConfig ---------------------------------------------------


    bool LunaConfig::SetFileExtensionsVisibility(bool showExtensions){
        HKEY hKey;
        LONG result;
        
        result = RegOpenKeyExW(
            HKEY_CURRENT_USER, 
            L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 
            0, 
            KEY_SET_VALUE, 
            &hKey
        );

        if(result != ERROR_SUCCESS){
            return false; 
        }
        
        DWORD value = showExtensions ? 0 : 1;  // 0 = afficher, 1 = masquer
        result = RegSetValueExW(hKey, L"HideFileExt", 0, REG_DWORD, (const BYTE*)&value, sizeof(value));

        if(result != ERROR_SUCCESS){
            RegCloseKey(hKey);
            return false; 
        }

        RegCloseKey(hKey);
        return true;
    };





    //------------------------------------------------------------------------------------------------


};