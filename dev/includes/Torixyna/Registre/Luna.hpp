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

    struct Rust{
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
            Rust GetRegisterTypeValue(HKEY RootKey, const wchar_t * Register, const wchar_t* valueName, Rust& data);

        private:
            HKEY m_RootKey; // Stocke la clé racine (par ex. HKEY_CURRENT_USER)

    };

    class LunaConfig{
        public:

        /*
        Cette méthode permet d'activer la visibilité des extension de fichier ou de désactiver
        la visibilité des extension de fichier.
        Si le paramètre showExtensions est à true alor on affiche les extension des fichier 
        Si le paramètre et à false on Masque les extension des fichier 
        (La méthode retourn true si tout c'est bien passé)
        */
        bool SetFileExtensionsVisibility(bool showExtensions);

    };




};

