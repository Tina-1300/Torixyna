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

namespace Torixyna::Registre{

    struct RegistrySizeInfo{
        DWORD maxSize = 0;    // Taille maximale du registre en Mo
        DWORD currentSize = 0; // Taille actuelle du registre en Mo
    };

    struct RegistryValueInfo{
        bool status; // si il et à true tout ses bien passé aucune error
        DWORD valueNameT; // valeur si ses un REG_SZ ou autre...
    };

    class Luna{
        public:
            Luna(HKEY RootKey);  // Constructeur par défaut

            // Ajout une clé de registre REG_SZ (return true si tout ses bien passé)
            bool Write(const wchar_t * Register, const WCHAR * NameKey, const WCHAR * Value);

            // Ajout une clé de registre dword (return true si tout ses bien passé)
            bool Write(const wchar_t * Register, const WCHAR * NameKey, DWORD Value);

            // Ajoute une clé de registre BINARY (return true si tout ses bien passé)
            bool Write(const wchar_t * Register, const WCHAR * NameKey, const BYTE* BinaryData);

            // Ajout une clé de registre Qword (return true si tout ses bien passé)
            bool Write(const wchar_t * Register, const WCHAR * NameKey, unsigned __int64 value);

            // à tester  : 

            // Ajout une clé de registre REG_MULTI_SZ (return true si tout ses bien passé)
            bool Write(const std::wstring& Register, const std::wstring& NameKey, const std::vector<std::wstring>& values);

            // Ajout une clé de registre REG_EXPAND_SZ (return true si tout ses bien passé)
            bool Write(const std::wstring& Register, const std::wstring& NameKey, const std::wstring& value);

            // -----------------------------------------------------------

            // Lecture du type DWORD (Return true si tout ses bien passé)
            bool Read(const wchar_t* registerPath, const wchar_t* nameKey, DWORD& result);

            // Lecture du type QWORD (Return true si tout ses bien passé)
            bool Read(const wchar_t* registerPath, const wchar_t* nameKey, ULONGLONG& result);

            // Lecture du type REG_SZ (Return true si tout ses bien passé)
            bool Read(const wchar_t* registerPath, const wchar_t* nameKey, std::wstring& result);

            // à tester 

            // Lecture du type BINARY (Return true si tout ses bien passé)
            // Problème affiche pas les bon truc regarder ce qu'il ne va pas dans le code 
            bool Read(const std::wstring& registerPath, const std::wstring& nameKey, std::vector<BYTE>& data);

            // Lecture du type REG_MULTI_SZ (Return true si tout ses bien passé)
            bool Read(const std::wstring& registerPath, const std::wstring& nameKey, std::vector<std::wstring>& values);

            // Lecture du type REG_EXPAND_SZ (Return true si tout ses bien passé)
            bool Read(const std::wstring& registerPath, const std::wstring& nameKey, std::wstring& value);
            
            // ---------------------------------------------------------
            
            // suprime une clé de registre (return true si tout ses bien passé)
            bool Delete(const wchar_t * Register, const WCHAR * NameKey);

            // à mettre dans une class LunaInfo :
            // et Refactorer ces deux fonction ci-dessous  

            // Retourn un struct qui contient la taille maximal que le registre peut stocker 
            // et la taille actuelle que stock le registre (tout cela en Mo)
            // à vérifier si elle marche bien 
            RegistrySizeInfo GetSizeRegistry(RegistrySizeInfo& data);

            // peut-être y mettre dans private cette fonction la pour que Read puisse l'utiliser 
            // return la structure Rust cette fonction permet de savoir le type de valeur que stock une clé 
            RegistryValueInfo GetRegisterTypeValue(const wchar_t * Register, const wchar_t* valueName, RegistryValueInfo& data);

        private:
            HKEY m_RootKey; // Stocke la clé racine (par ex. HKEY_CURRENT_USER)

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

