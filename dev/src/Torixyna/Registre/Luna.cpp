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

    //------------------------------------------------------------------------------------------------

    //--------------------------------- LunaConfig ---------------------------------------------------


    bool LunaConfig::SetFileExtensionsVisibility(bool showExtensions){
        HKEY hKey;
        LONG result;
        
        result = RegOpenKeyEx(
            HKEY_CURRENT_USER, 
            "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 
            0, 
            KEY_SET_VALUE, 
            &hKey
        );

        if(result != ERROR_SUCCESS){
            return false; 
        }
        
        DWORD value = showExtensions ? 0 : 1;  // 0 = afficher, 1 = masquer
        result = RegSetValueEx(hKey, "HideFileExt", 0, REG_DWORD, (const BYTE*)&value, sizeof(value));

        if(result != ERROR_SUCCESS){
            RegCloseKey(hKey);
            return false; 
        }

        RegCloseKey(hKey);
        return true;
    };





    //------------------------------------------------------------------------------------------------


};