# Registry Module

<!-- A faire traduire en anglais par chatGPT + lui faire corriger les fautes  -->

### Features

- lie, écrit, suprimme une clée de registre tout ces type de donné sont disponible
- Récupère des information sur le registre les types de valeur que stock une clé, ainsi que la taille 
actuel du registre et la taille maximal que peut stocker le registre

- Modifie des paramètre pour changer le fond d'écran, activer oui ou non les extansion des fichier 
et bien plus encor...

---

## Compilation

To use the **Speaker** module, you must compile your program with the following options:

````bash
g++ -Oz -O2 -Os -s -o test.exe test.cpp -lTorixyna & color
````

Les structures : 

- RegistrySizeInfo : (Structure qui stock la taille actuelle du registre et la taille maximal que peut avoir le registre)

- RegistryValueInfo : (Structure qui stock le type de la clé example si c'est : REG_SZ, ou autre...)




dans la class Luna : 

---

<br>
bool Write(const wchar_t * Register, const WCHAR * NameKey, const WCHAR * Value);
### Method : `Write()`

**Description** :  
Méthode Surcharger permettant d'écrire dans le registre. 

#### Settings :
- `params1` : Attent le chemin vers la clé de registre.
- `params2` : Nom de la clé de registre stockant la valeur.
- `params3` : Valeur à stocker dans le registre.
  
#### Returned value :
- `bool` : Return true si tout c'est bien passé.

#### Example of use :

````cpp
#define INCLUDE_REGISTRE
#include <iostream>
#include <iomanip>
#include <Torixyna/Torixyna.hpp>

int main(){
    SetConsoleOutputCP(CP_UTF8);

    Torixyna::Registry::Luna luna(HKEY_CURRENT_USER);

    // ---------------------------- write dword value in a registry ----------------------
    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"test";
    DWORD value = 12345;

    if(luna.Write(registryPath, keyName, value) == true){
        std::cout << "La valeur a bien été écrite" << "\n";
        std::cin.get();
    }else{
        std::cerr << "Error" << "\n";
        std::cin.get();
    }
    //-------------------------------------------------------------------------------------

    // ------------------------- write REG_SZ value in a registry -------------------------
    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"testString";
    const wchar_t* value = L"Alex";

    if(luna.Write(registryPath, keyName, value) == true){
        std::cout << "La valeur a bien été écrite" << "\n";
        std::cin.get();
    }else{
        std::cerr << "Error" << "\n"; 
        std::cin.get();
    }
    // -----------------------------------------------------------------------------------

    // ------------------------- write a BINARY value in a registry ----------------------
    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"testBinary";
    BYTE value[] = { 0x01, 0x02, 0x03, 0x04 };

    if(luna.Write(registryPath, keyName, value) == true){
        std::cout << "La valeur a bien été écrite" << "\n";
        std::cin.get();
    }else{
        std::cerr << "Error" << "\n";
        std::cin.get();
    }
    // ------------------------------------------------------------------------------------

    // ------------------------ write a QWORD value in a registry -------------------------
    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"testQword";
    unsigned __int64 value = 1234567890123456;

    if(luna.Write(registryPath, keyName, value) == true){
        std::cout << "La valeur a bien ete ecrite" << "\n";
        std::cin.get();
    }else{
        std::cerr << "Error" << "\n";
        std::cin.get();
    }
    // -----------------------------------------------------------------------------------

    // ---------------------------- write a REG_MULTI_SZ value in a registry -------------
    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"MaValeurMultiSZ";
    std::vector<std::wstring> values = {L"Valeur1", L"Valeur2", L"Valeur3"};
    
    if (luna.Write( registryPath, keyName, values) == true){
        std::cout << "Valeur écrite avec succès !" << "\n";
    }else{
        std::cout << "Échec de l'écriture de la valeur." << "\n";
    }
    // -------------------------------------------------------------------------------------

    // ---------------------- write a REG_EXPPAND_SZ value in a registry ------------------
    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"MaValeurExpandSZ";
    if (luna.Write(registryPath, keyName, L"%SystemRoot%\\System32") == true){
        std::cout << "Valeur REG_EXPAND_SZ écrite avec succès !" << "\n";
    }else{
        std::cout << "Échec de l'écriture de la valeur REG_EXPAND_SZ." << "\n";
    }
    // -------------------------------------------------------------------------------------


    return 0;
};
````

<br>
---
<br>

### Method : `setVolume()`

**Description** :  
Allows you to set the volume level of the audio device. This function takes a float number between 0 and 100, representing volume as a percentage.

#### Settings :
- `float volume` :  The volume to define must be a number between 0.0 and 100.0 (inclusive).
  
#### Returned value :
- `bool` : Returns `true` if the volume was correctly modified, `false` in case of error.

#### Example of use :

````cpp
#define INCLUDE_SPEAKER
#include <Torixyna/Torixyna.hpp>

int main(){
    Torixyna::Speaker::Speaker sound;

    if(sound.setVolume(50.0f) == true){
        std::cout << "Sucess" << std::endl;
    }else{
        std::cout << "Error" << std::endl;
    }

    return 0;
}
````

<br>
---
<br>
bool Delete(const wchar_t * Register, const WCHAR * NameKey);

### Method : `Delete()`

**Description** :  
Permet de suprimmer une clé de registre.

#### Settings :
- `const wchar_t * Register` :  Attent le chemin vers la clé de registre.
- `const WCHAR * NameKey` : Attend le nom de la clé de registre à suprimmer.
  
#### Returned value :
- `bool` : Return `true` si tout c'est bien passé.

#### Example of use :

````cpp
#define INCLUDE_REGISTRE
#include <iostream>
#include <Torixyna/Torixyna.hpp>

int main(){
    SetConsoleOutputCP(CP_UTF8);

    Torixyna::Registry::Luna luna(HKEY_CURRENT_USER);

    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"test";

    if(luna.Delete(registryPath, keyName) == true){
        std::cout << "La clé a bien été suprimmer" << "\n";
        std::cin.get();
    }else{
        std::cerr << "Error" << "\n";
        std::cin.get();
    }


    return 0;
}
````




dans la classe LunaInfo : 

<br>
---
<br>

### Method : `setMute()`

**Description** :  
Sets the mute status of the audio device. This function allows you to mute or unmute the audio depending on the value passed to it.

#### Settings :
- `bool mute` :  A boolean value. Pass true to mute the audio, or false to unmute it.
  
#### Returned value :
- `bool` : Returns `true` if the mute status was successfully set, `false` in case of an error.

#### Example of use :

````cpp
#define INCLUDE_SPEAKER
#include <Torixyna/Torixyna.hpp>

int main(){
    Torixyna::Speaker::Speaker sound;

    // Mute the audio
    if (sound.setMute(true)){
        std::cout << "The audio has been muted." << std::endl;
    }else{
        std::cout << "Failed to mute the audio." << std::endl;
    }

    // Unmute the audio
    if (sound.setMute(false)){
        std::cout << "The audio has been unmuted." << std::endl;
    }else{
        std::cout << "Failed to unmute the audio." << std::endl;
    }

    return 0;
}
````


dans la classe LunaConfig : 
