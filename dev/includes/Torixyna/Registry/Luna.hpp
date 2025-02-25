#pragma once
#include <windows.h>
#include <string>
#include <vector>

/*
https://learn.microsoft.com/fr-fr/windows/win32/apiindex/windows-api-list
https://learn.microsoft.com/fr-fr/windows/win32/sysinfo/registry-reference
https://learn.microsoft.com/fr-fr/windows/win32/sysinfo/registry
https://learn.microsoft.com/fr-fr/windows/win32/sysinfo/registry-files
*/

// Faire la documentation de ce module 

namespace Torixyna::Registry{

    struct RegistrySizeInfo{
        DWORD maxSize = 0;    // Taille maximale du registre en Mo
        DWORD currentSize = 0; // Taille actuelle du registre en Mo
    };

    struct RegistryValueInfo{
        DWORD valueNameT; // valeur si ses un REG_SZ ou autre...
    };

    class LunaBase{
        public:
            explicit LunaBase(HKEY rootKey) : m_RootKey(rootKey) {}
            virtual ~LunaBase() = default;
    
        protected:
            HKEY m_RootKey; // Stocke la clé racine (ex: HKEY_CURRENT_USER)
    };

    class Luna : public LunaBase{
        public:
            explicit Luna(HKEY rootKey) : LunaBase(rootKey) {}

            // Adding a registry key REG_SZ (return true if everything went well)
            bool Write(const wchar_t * Register, const WCHAR * NameKey, const WCHAR * Value);

            // Adding a registry key dword (return true if everything went well)
            bool Write(const wchar_t * Register, const WCHAR * NameKey, DWORD Value);

            // AAdding a registry key BINARY (return true if everything went well)
            bool Write(const wchar_t * Register, const WCHAR * NameKey, const BYTE* BinaryData);

            // Adding a registry key Qword (return true if everything went well)
            bool Write(const wchar_t * Register, const WCHAR * NameKey, unsigned __int64 value);

            // Adding a registry key REG_MULTI_SZ (return true if everything went well)
            bool Write(const std::wstring& Register, const std::wstring& NameKey, const std::vector<std::wstring>& values);

            // Adding a registry key REG_EXPAND_SZ (return true if everything went well)
            bool Write(const std::wstring& Register, const std::wstring& NameKey, const std::wstring& value);


            // Type reading (return true if everything went well)
            bool Read(const wchar_t* registerPath, const wchar_t* nameKey, DWORD& result);

            // Type reading (return true if everything went well)
            bool Read(const wchar_t* registerPath, const wchar_t* nameKey, ULONGLONG& result);

            // Type reading REG_SZ (return true if everything went well)
            bool Read(const wchar_t* registerPath, const wchar_t* nameKey, std::wstring& result);

            // Type reading BINARY (return true if everything went well)
            bool Read(const std::wstring& registerPath, const std::wstring& nameKey, std::vector<BYTE>& data);

            // Type reading REG_MULTI_SZ (return true if everything went well)
            bool Read(const std::wstring& registerPath, const std::wstring& nameKey, std::vector<std::wstring>& values);

            // Type reading REG_EXPAND_SZ (return true if everything went well)
            bool Read(const std::wstring& registerPath, const std::wstring& nameKey, std::wstring& value);
            
            // delete a registry key (return true if everything went well)
            bool Delete(const wchar_t * Register, const WCHAR * NameKey);

    };

    class LunaInfo : public LunaBase{
        public:

            explicit LunaInfo(HKEY rootKey) : LunaBase(rootKey) {}

            // Return true si tout ses bien passé, stock dans la structure : RegistrySizeInfo 
            // la taille que fait actuellement les registres et la taille maximal supporté par les registre
            // les valeur retourner pas la structure sont convertie en MO
            bool GetSizeRegistry(RegistrySizeInfo& data);

            // Return true si tout ses bien passé, stock le type de la valeur dans la Structure RegistryValueInfo
            // si le type de la valeur n'est pas trouver un code d'error -808 stocké a la place du type de la valeur 
            bool GetRegisterTypeValue(const wchar_t * Register, const wchar_t* valueName, RegistryValueInfo& data);
        
    };


    class LunaConfig{
        public:

            /*
            This method allows you to enable or disable the visibility of file extensions.
            If the parameter showExtensions is set to true, the file extensions are displayed.
            If the parameter is set to false, the file extensions are hidden.
            The method returns true if everything was successful.
            */
            static bool SetsFileExtensionsVisibility(bool showExtensions);

            // a tester 
            /*
            Sets the visibility of hidden items. 
            If set to true, hidden items are displayed.
            If set to false, hidden items are not displayed.
            The function returns false if there is an error, and true if there is no error.
            */
            static bool SetsShowItemsHide(bool Status);

            /*
            Sets the status of checkboxes.
            Activates checkboxes if the 'Status' parameter is set to true.
            Deactivates checkboxes if the 'Status' parameter is set to false.
            This function returns true if the operation is successful.
            */
            static bool SetsTheStatusOfCheckboxes(bool Status);

            /*
            Function to set the wallpaper
            This function takes the image path as a parameter.
            It returns false if there is an error and true if everything goes well.
            */
            static bool SetWallpaper(const std::wstring& imagePath);

    };


};

