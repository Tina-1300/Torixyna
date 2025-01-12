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

    INFO_TYPE Luna::GetRegisterTypeValue( const wchar_t * Register, const wchar_t* valueName, INFO_TYPE& data){
        HKEY keyHandle;
        DWORD dataType = 0;
        LONG result = RegOpenKeyExW(m_RootKey, Register, 0, KEY_QUERY_VALUE, &keyHandle);
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


    bool LunaConfig::SetsFileExtensionsVisibility(bool showExtensions){
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

    bool LunaConfig::SetsShowItemsHide(bool Status){
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
        
        DWORD value = Status ? 1 : 2;  // 1 = afficher, 2 = masquer
        result = RegSetValueExW(hKey, L"Hidden", 0, REG_DWORD, (const BYTE*)&value, sizeof(value));

        if(result != ERROR_SUCCESS){
            RegCloseKey(hKey);
            return false; 
        }

        RegCloseKey(hKey);
        return true;
    };


    bool LunaConfig::SetsTheStatusOfCheckboxes(bool Status){
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
        
        DWORD value = Status ? 1 : 0;  // 1 = Activer, 0 = Désactiver
        result = RegSetValueExW(hKey, L"AutoCheckSelect", 0, REG_DWORD, (const BYTE*)&value, sizeof(value));

        if(result != ERROR_SUCCESS){
            RegCloseKey(hKey);
            return false; 
        }

        RegCloseKey(hKey);
        return true;    

    };

    bool LunaConfig::SetWallpaper(const std::wstring& imagePath){
        HKEY hKey;
        LONG result;

        result = RegOpenKeyExW(HKEY_CURRENT_USER, L"Control Panel\\Desktop", 0, KEY_SET_VALUE, &hKey);
        if (result != ERROR_SUCCESS){
            //Erreur lors de l'ouverture de la cle de registre.
            return false;
        }

        DWORD fileAttr = GetFileAttributesW(imagePath.c_str());
        if (fileAttr == INVALID_FILE_ATTRIBUTES){
            //Le fichier image specifie n'existe pas.
            RegCloseKey(hKey);
            return false;
        }

        // Définir le chemin de l'image comme fond d'écran
        result = RegSetValueExW(hKey, L"Wallpaper", 0, REG_SZ, (const BYTE*)imagePath.c_str(), (imagePath.size() + 1) * sizeof(wchar_t));
        if (result != ERROR_SUCCESS){
            //Erreur lors de la modification du registre pour l'image.
            RegCloseKey(hKey);
            return false;
        }

        // Définir le style de fond d'écran (0: Ajuster, 1: Carrelé, 2: Centré)
        const wchar_t* wallpaperStyle = L"2";  // 2 : Centré
        result = RegSetValueExW(hKey, L"WallpaperStyle", 0, REG_SZ, (const BYTE*)wallpaperStyle, (wcslen(wallpaperStyle) + 1) * sizeof(wchar_t));
        if (result != ERROR_SUCCESS){
            //Erreur lors de la modification du style du fond d'ecran.
            RegCloseKey(hKey);
            return false;
        }

        // Définir si le fond d'écran doit être tuilé (0 : Non, 1 : Oui)
        const wchar_t* tileWallpaper = L"0";  // 0 : Pas de carrelage
        result = RegSetValueExW(hKey, L"TileWallpaper", 0, REG_SZ, (const BYTE*)tileWallpaper, (wcslen(tileWallpaper) + 1) * sizeof(wchar_t));
        if (result != ERROR_SUCCESS){
            //Erreur lors de la modification de la tuile du fond d'ecran.
            RegCloseKey(hKey);
            return false;
        }

        RegCloseKey(hKey);

        BOOL success = SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (PVOID)imagePath.c_str(), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
        if (!success){
            //Erreur lors de l'application du fond d'ecran.
            return false;
        }else{
            //Le fond d'ecran a ete change avec succes.
            return true;
        }
    };





    //------------------------------------------------------------------------------------------------


};