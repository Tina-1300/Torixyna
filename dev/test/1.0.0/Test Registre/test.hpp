#pragma once
#include <windows.h>
#include <string>
#include <stdexcept>
#include <memory>

namespace Torixyna::Registry {

    // Gestion des erreurs pour la manipulation du registre
    class RegistryException : public std::runtime_error {
    public:
        explicit RegistryException(const std::string& msg) : std::runtime_error(msg) {}
    };

    // Classe utilitaire pour l'ouverture et la fermeture des clés du registre
    class RegistryHelper {
    public:
        static HKEY OpenKey(HKEY rootKey, const wchar_t* registerPath, REGSAM access) {
            HKEY hKey;
            LONG result = RegOpenKeyExW(rootKey, registerPath, 0, access, &hKey);
            if (result != ERROR_SUCCESS) {
                throw RegistryException("Failed to open registry key.");
            }
            return hKey;
        }

        static void CloseKey(HKEY hKey) {
            RegCloseKey(hKey);
        }
    };

    // Interface pour l'écriture d'une clé dans le registre
    template <typename T>
    class WriteRegistry {
    public:
        virtual bool Write(HKEY RootKey, const wchar_t* Register, const wchar_t* NameKey, T Value) = 0;
        virtual ~WriteRegistry() = default;
    };

    // Interface pour la lecture d'une clé dans le registre
    template <typename T>
    class ReadRegistry {
    public:
        virtual bool Read(HKEY RootKey, const wchar_t* Register, const wchar_t* NameKey, T& result) = 0;
        virtual ~ReadRegistry() = default;
    };

    // Interface pour la suppression d'une clé dans le registre
    class DeleteRegistry {
    public:
        virtual bool Delete(HKEY RootKey, const wchar_t* Register, const wchar_t* NameKey) = 0;
        virtual ~DeleteRegistry() = default;
    };

    // Implémentation pour écrire une chaîne dans le registre
    class WriteStringRegistry : public WriteRegistry<std::wstring> {
    public:
        bool Write(HKEY RootKey, const wchar_t* Register, const wchar_t* NameKey, std::wstring Value) override {
            HKEY hKey = RegistryHelper::OpenKey(RootKey, Register, KEY_WRITE);
            LONG result = RegSetValueExW(hKey, NameKey, 0, REG_SZ,
                                         reinterpret_cast<const BYTE*>(Value.c_str()), (Value.size() + 1) * sizeof(wchar_t));
            RegistryHelper::CloseKey(hKey);
            return result == ERROR_SUCCESS;
        }
    };

    // Implémentation pour écrire un entier dans le registre
    class WriteIntRegistry : public WriteRegistry<int> {
    public:
        bool Write(HKEY RootKey, const wchar_t* Register, const wchar_t* NameKey, int Value) override {
            HKEY hKey = RegistryHelper::OpenKey(RootKey, Register, KEY_WRITE);
            LONG result = RegSetValueExW(hKey, NameKey, 0, REG_DWORD,
                                         reinterpret_cast<const BYTE*>(&Value), sizeof(Value));
            RegistryHelper::CloseKey(hKey);
            return result == ERROR_SUCCESS;
        }
    };

    // Implémentation pour la lecture d'une chaîne depuis le registre
    class ReadStringRegistry : public ReadRegistry<std::wstring> {
    public:
        bool Read(HKEY RootKey, const wchar_t* Register, const wchar_t* NameKey, std::wstring& result) override {
            HKEY hKey = RegistryHelper::OpenKey(RootKey, Register, KEY_READ);
            DWORD dataSize = 0;
            LONG res = RegQueryValueExW(hKey, NameKey, nullptr, nullptr, nullptr, &dataSize);
            if (res != ERROR_SUCCESS) {
                RegistryHelper::CloseKey(hKey);
                return false;
            }

            wchar_t* buffer = new wchar_t[dataSize / sizeof(wchar_t)];
            res = RegQueryValueExW(hKey, NameKey, nullptr, nullptr, reinterpret_cast<BYTE*>(buffer), &dataSize);
            if (res == ERROR_SUCCESS) {
                result = buffer;
            }

            delete[] buffer;
            RegistryHelper::CloseKey(hKey);
            return res == ERROR_SUCCESS;
        }
    };

    // Implémentation pour la suppression d'une clé du registre
    class DeleteRegistryImpl : public DeleteRegistry {
    public:
        bool Delete(HKEY RootKey, const wchar_t* Register, const wchar_t* NameKey) override {
            HKEY hKey = RegistryHelper::OpenKey(RootKey, Register, KEY_SET_VALUE);
            LONG result = RegDeleteValueW(hKey, NameKey);
            RegistryHelper::CloseKey(hKey);
            return result == ERROR_SUCCESS;
        }
    };

};
