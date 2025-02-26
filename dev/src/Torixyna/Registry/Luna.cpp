#include "../../../includes/Torixyna/Registry/Luna.hpp"

namespace Torixyna::Registry{

    // ---------------------------- Luna -----------------------------------------

    bool Luna::Write(const wchar_t * Register, const WCHAR * NameKey, const WCHAR * Value){
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

    bool Luna::Write(const wchar_t * Register, const WCHAR * NameKey, DWORD Value){
        HKEY hKey;
        LONG result = RegOpenKeyW(m_RootKey, Register, &hKey);

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

    bool Luna::Write(const wchar_t * Register, const WCHAR * NameKey, const BYTE* BinaryData){
        HKEY hKey;
        LONG result = RegOpenKeyW(m_RootKey, Register, &hKey);

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

    bool Luna::Write(const wchar_t * Register, const WCHAR * NameKey, unsigned __int64 value){
        HKEY hKey;
        LONG result = RegOpenKeyW(m_RootKey, Register, &hKey);

        if (result != ERROR_SUCCESS){
            return false;
        }

        result = RegSetValueExW(hKey, NameKey, 0, REG_QWORD, reinterpret_cast<const BYTE*>(&value), sizeof(value));
        RegCloseKey(hKey);

        if (result != ERROR_SUCCESS){
            return false; 
        }
        return true;
    };

    bool Luna::Write(const std::wstring& Register, const std::wstring& NameKey, const std::vector<std::wstring>& values){
        HKEY hKey;
        LONG result = RegOpenKeyExW(m_RootKey, NameKey.c_str(), 0, KEY_SET_VALUE, &hKey);
        
        if (result != ERROR_SUCCESS){
            return false;
        }
        
        std::vector<wchar_t> multiSzData;
        for (const auto& value : values){
            multiSzData.insert(multiSzData.end(), value.begin(), value.end());
            multiSzData.push_back(L'\0'); // separator between string
        }
        multiSzData.push_back(L'\0');
        
        result = RegSetValueExW(hKey, NameKey.c_str(), 0, REG_MULTI_SZ, 
                                reinterpret_cast<const BYTE*>(multiSzData.data()), 
                                static_cast<DWORD>(multiSzData.size() * sizeof(wchar_t)));
        RegCloseKey(hKey);
        
        if (result != ERROR_SUCCESS){
            return false;
        }
        
        return true;
    };

    bool Luna::Write(const std::wstring& Register, const std::wstring& NameKey, const std::wstring& value){
        HKEY hKey;
        LONG result = RegOpenKeyExW(m_RootKey, Register.c_str(), 0, KEY_SET_VALUE, &hKey);
        if (result != ERROR_SUCCESS){
            return false;
        }
        result = RegSetValueExW(hKey, NameKey.c_str(), 0, REG_EXPAND_SZ, reinterpret_cast<const BYTE*>(value.c_str()), static_cast<DWORD>((value.size() + 1) * sizeof(wchar_t)));
        RegCloseKey(hKey);
        
        if (result != ERROR_SUCCESS){
            return false;
        }
        return true;
    };

    // ---------------------- Read ---------------------------------
    
    bool Luna::Read(const wchar_t* registerPath, const wchar_t* nameKey, DWORD& result){
        HKEY hKey;
        LONG status = RegOpenKeyW(m_RootKey, registerPath, &hKey);
        
        if (status != ERROR_SUCCESS){
            return false;
        }

        DWORD dataSize = sizeof(DWORD);
        status = RegQueryValueExW(hKey, nameKey, nullptr, nullptr, reinterpret_cast<LPBYTE>(&result), &dataSize);

        RegCloseKey(hKey);
        return status == ERROR_SUCCESS;
    };
    
    bool Luna::Read(const wchar_t* registerPath, const wchar_t* nameKey, ULONGLONG& result){
        HKEY hKey;
        LONG status = RegOpenKeyW(m_RootKey, registerPath, &hKey);

        if (status != ERROR_SUCCESS){
            return false;
        }

        DWORD dataSize = sizeof(ULONGLONG);
        status = RegQueryValueExW(hKey, nameKey, nullptr, nullptr, reinterpret_cast<LPBYTE>(&result), &dataSize);

        RegCloseKey(hKey);
        return status == ERROR_SUCCESS;
    };

    bool Luna::Read(const wchar_t* registerPath, const wchar_t* nameKey, std::wstring& result){
        HKEY hKey;
        LONG status = RegOpenKeyW(m_RootKey, registerPath, &hKey);

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

    bool Luna::Read(const std::wstring& registerPath, const std::wstring& nameKey, std::vector<BYTE>& data){
        HKEY hKey;
        LONG result = RegOpenKeyExW(m_RootKey, registerPath.c_str(), 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS){
            return false;
        }
        DWORD dataSize = 0;
        result = RegQueryValueExW(hKey, nameKey.c_str(), nullptr, nullptr, nullptr, &dataSize);
        if (result != ERROR_SUCCESS || dataSize == 0){
            RegCloseKey(hKey);
            return false;
        }
        
        data.resize(dataSize);
        result = RegQueryValueExW(hKey, nameKey.c_str(), nullptr, nullptr, data.data(), &dataSize);
        RegCloseKey(hKey);
        
        if (result != ERROR_SUCCESS){
            return false;
        }
        return true;
    };

    bool Luna::Read(const std::wstring& registerPath, const std::wstring& nameKey, std::vector<std::wstring>& values){

        HKEY hKey;
        LONG result = RegOpenKeyExW(m_RootKey, registerPath.c_str(), 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS){
            return false;
        }
        
        DWORD dataSize = 0;
        result = RegQueryValueExW(hKey, nameKey.c_str(), nullptr, nullptr, nullptr, &dataSize);
        if (result != ERROR_SUCCESS || dataSize == 0){
            RegCloseKey(hKey);
            return false;
        }
        
        std::vector<wchar_t> buffer(dataSize / sizeof(wchar_t));
        result = RegQueryValueExW(hKey, nameKey.c_str(), nullptr, nullptr, reinterpret_cast<LPBYTE>(buffer.data()), &dataSize);
        RegCloseKey(hKey);
        
        if (result != ERROR_SUCCESS){
            return false;
        }
        
        values.clear();
        wchar_t* ptr = buffer.data();
        while (*ptr){
            values.push_back(ptr);
            ptr += wcslen(ptr) + 1;
        }
        return true;
    };

    bool Luna::Read(const std::wstring& registerPath, const std::wstring& nameKey, std::wstring& value){
        HKEY hKey;
        LONG result = RegOpenKeyExW(m_RootKey, registerPath.c_str(), 0, KEY_QUERY_VALUE, &hKey);
        if (result != ERROR_SUCCESS){
            return false;
        }
        DWORD dataSize = 0;
        result = RegQueryValueExW(hKey, nameKey.c_str(), nullptr, nullptr, nullptr, &dataSize);
        if (result != ERROR_SUCCESS || dataSize == 0){
            RegCloseKey(hKey);
            return false;
        }
        std::vector<wchar_t> buffer(dataSize / sizeof(wchar_t));
        result = RegQueryValueExW(hKey, nameKey.c_str(), nullptr, nullptr, reinterpret_cast<LPBYTE>(buffer.data()), &dataSize);
        RegCloseKey(hKey);
        if (result != ERROR_SUCCESS){
            return false;
        }
        value.assign(buffer.begin(), buffer.end());
        return true;

    };

    // ---------------------- Delete ---------------------------------

    bool Luna::Delete(const wchar_t * Register, const WCHAR * NameKey){
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

    //------------------------------------------------------------------------------------------------

    //-------------------------------------- LunaInfo ------------------------------------------------

    bool LunaInfo::GetSizeRegistry(RegistrySizeInfo& data){
        DWORD T_MAX, T_ACTUELL;
        if (!GetSystemRegistryQuota(&T_MAX, &T_ACTUELL)){
            return false; // Failed to retrieve information
        }
        data.maxSize = T_MAX / (1024 * 1024);
        data.currentSize = T_ACTUELL / (1024 * 1024);
        return true; 
    };

    bool LunaInfo::GetRegisterTypeValue(const wchar_t * Register, const wchar_t* valueName, RegistryValueInfo& data){
        HKEY keyHandle;
        DWORD dataType = 0;
    
        LONG result = RegOpenKeyExW(m_RootKey, Register, 0, KEY_QUERY_VALUE, &keyHandle);
        if (result != ERROR_SUCCESS){
            return false;
        }
    
        // Get the type of the value
        result = RegQueryValueExW(keyHandle, valueName, NULL, &dataType, NULL, NULL);
        if (result != ERROR_SUCCESS){
            RegCloseKey(keyHandle);
            return false;
        }
    
        RegCloseKey(keyHandle);
    
        switch (dataType){
            case REG_SZ: data.valueNameT = REG_SZ; break;
            case REG_BINARY: data.valueNameT = REG_BINARY; break;
            case REG_DWORD: data.valueNameT = REG_DWORD; break;
            case REG_QWORD: data.valueNameT = REG_QWORD; break;
            case REG_MULTI_SZ: data.valueNameT = REG_MULTI_SZ; break;
            case REG_LINK: data.valueNameT = REG_LINK; break;
            case REG_EXPAND_SZ: data.valueNameT = REG_EXPAND_SZ; break;
            case REG_NONE: data.valueNameT = REG_NONE; break;
            default: data.valueNameT = -808; break; // Custom error code (can't find the type of the value)
        }

        return true;
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
        
        DWORD value = showExtensions ? 0 : 1;  // 0 = show, 1 = hide
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
        
        DWORD value = Status ? 1 : 2;  // 1 = show, 2 = hide
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
        
        DWORD value = Status ? 1 : 0;  // 1 = Enable, 0 = Disable
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
            return false;
        }

        DWORD fileAttr = GetFileAttributesW(imagePath.c_str());
        if (fileAttr == INVALID_FILE_ATTRIBUTES){
            RegCloseKey(hKey);
            return false;
        }

        result = RegSetValueExW(hKey, L"Wallpaper", 0, REG_SZ, (const BYTE*)imagePath.c_str(), (imagePath.size() + 1) * sizeof(wchar_t));
        if (result != ERROR_SUCCESS){
            RegCloseKey(hKey);
            return false;
        }

        // définit le style du fond d'écran (0: Ajuster, 1: Carreler, 2: Centrer)
        const wchar_t* wallpaperStyle = L"2";  // 2 : Centrer
        result = RegSetValueExW(hKey, L"WallpaperStyle", 0, REG_SZ, (const BYTE*)wallpaperStyle, (wcslen(wallpaperStyle) + 1) * sizeof(wchar_t));
        if (result != ERROR_SUCCESS){
            RegCloseKey(hKey);
            return false;
        }

        // set whether the wallpaper should be tiled (0: No, 1: Yes)
        const wchar_t* tileWallpaper = L"0";  // 0 : Pas de carrelage
        result = RegSetValueExW(hKey, L"TileWallpaper", 0, REG_SZ, (const BYTE*)tileWallpaper, (wcslen(tileWallpaper) + 1) * sizeof(wchar_t));
        if (result != ERROR_SUCCESS){
            RegCloseKey(hKey);
            return false;
        }

        RegCloseKey(hKey);

        BOOL success = SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (PVOID)imagePath.c_str(), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
        if (!success){
            return false;
        }else{
            return true;
        }
    };
    //------------------------------------------------------------------------------------------------

};