#pragma once
#include <windows.h>
#include <string>


/*
https://learn.microsoft.com/fr-fr/windows/win32/apiindex/windows-api-list

https://learn.microsoft.com/fr-fr/windows/win32/sysinfo/registry-reference
https://learn.microsoft.com/fr-fr/windows/win32/sysinfo/registry

https://learn.microsoft.com/fr-fr/windows/win32/sysinfo/registry-files
*/


namespace Torixyna::Registre{

    struct INFO_TAILL{
        DWORD TaillMaximal = 0;
        DWORD TaillActuell = 0;
    };

    // Renomer la structure Rust en INFO_TYPE 
    struct INFO_TYPE{
        bool status; // si il et à true tout ses bien passé aucune error
        const char* valueName; // valeur si ses un REG_SZ ou autre...
        DWORD valueNameT; // valeur si ses un REG_SZ ou autre...
    };

    class Luna{
        public:
            Luna(HKEY RootKey);  // Constructeur par défaut


            // Ajout une clé de registre (return true si tout ses bien passé)
            bool AddRegistryKey(const wchar_t * Register, const WCHAR * NameKey, const WCHAR * Value);

            // suprime une clé de registre (return true si tout ses bien passé)
            bool DeleteRegistryKey(const wchar_t * Register, const WCHAR * NameKey);

            // Retourn un struct qui contient la taille maximal que le registre peut stocker 
            // et la taille actuelle que stock le registre (tout cela en Mo)
            // à vérifier si elle marche bien 
            INFO_TAILL GetSizeRegistry(INFO_TAILL& data);

            // return la structure Rust cette fonction permet de savoir le type de valeur que stock une clé 
            INFO_TYPE GetRegisterTypeValue(const wchar_t * Register, const wchar_t* valueName, INFO_TYPE& data);

            /*
            faire une fonction pour vérifier qu'un registre ou une clé existe bien 
            pour énuméré tout les valeur des clé 
            pour énuméré tout les clé
            pour modifier une clé ou sa valeur REG_SZ
            pour ajouter un DWORD, BINARY
            pour modifier un DWORD, BINARY
            pour lire un DWORD, BINARY
            */


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
            bool SetsFileExtensionsVisibility(bool showExtensions);

            // a tester 
            /*
            Sets the visibility of hidden items. 
            If set to true, hidden items are displayed.
            If set to false, hidden items are not displayed.
            The function returns false if there is an error, and true if there is no error.
            */
            bool SetsShowItemsHide(bool Status);

            /*
            Sets the status of checkboxes.
            Activates checkboxes if the 'Status' parameter is set to true.
            Deactivates checkboxes if the 'Status' parameter is set to false.
            This function returns true if the operation is successful.
            */
            bool SetsTheStatusOfCheckboxes(bool Status);

            /*
            Function to set the wallpaper
            This function takes the image path as a parameter.
            It returns false if there is an error and true if everything goes well.
            */
            bool SetWallpaper(const std::wstring& imagePath);



    };

//Ordinateur\HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\User Shell Folders


};

