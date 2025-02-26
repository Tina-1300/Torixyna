# Registry Module


### Features

- Read, write, and delete registry keys, with support for all data types.
- Retrieve information about registry keys, including the value types stored and both the current and maximum size the registry can hold.
- Modify parameters such as changing the desktop background, enabling or disabling file extensions, and more.


---

## Compilation

To use the **Registry** module, you must compile your program with the following options:

````bash
g++ -Oz -O2 -Os -s -o test.exe test.cpp -lTorixyna & color
````

## Les Structures : 

- RegistrySizeInfo : A structure that stores the current size and maximum size of the registry.

- RegistryValueInfo : A structure that stores the type of the registry key (e.g., REG_SZ, REG_DWORD, etc.).


<br>

# Class Luna : 

---

<br>

### Method : `Write()`

**Description** :  
Overloaded method for writing to the registry.

#### Settings :
- `params1` : The path to the registry key.
- `params2` : The name of the registry key that holds the value.
- `params3` : The value to be stored in the registry.
  
#### Returned value :
- `bool` : Returns `true` if the operation was successful.

#### Example of use :

````cpp
#define INCLUDE_REGISTRE
#include <iostream>
#include <Torixyna/Torixyna.hpp>

int main(){
    SetConsoleOutputCP(CP_UTF8);

    Torixyna::Registry::Luna luna(HKEY_CURRENT_USER);

    // ---------------------------- Write DWORD value in the registry ----------------------
    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"testDWORD";
    DWORD value = 12345;

    if(luna.Write(registryPath, keyName, value) == true){
        std::cout << "Value successfully written" << "\n";
        std::cin.get();
    }else{
        std::cerr << "Failed to write value." << "\n";
        std::cin.get();
    }
    //-------------------------------------------------------------------------------------

    // ------------------------- Write REG_SZ value in the registry -------------------------
    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"testString";
    const wchar_t* value = L"Alex";

    if(luna.Write(registryPath, keyName, value) == true){
        std::cout << "Value successfully written" << "\n";
        std::cin.get();
    }else{
        std::cerr << "Failed to write value." << "\n"; 
        std::cin.get();
    }
    // -----------------------------------------------------------------------------------

    // ------------------------- Write BINARY value in the registry ----------------------
    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"testBinary";
    BYTE value[] = { 0x01, 0x02, 0x03, 0x04 };

    if(luna.Write(registryPath, keyName, value) == true){
        std::cout << "Value successfully written" << "\n";
        std::cin.get();
    }else{
        std::cerr << "Failed to write value." << "\n";
        std::cin.get();
    }
    // ------------------------------------------------------------------------------------

    // ------------------------ Write QWORD value in the registry -------------------------
    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"testQword";
    unsigned __int64 value = 1234567890123456;

    if(luna.Write(registryPath, keyName, value) == true){
        std::cout << "Value successfully written" << "\n";
        std::cin.get();
    }else{
        std::cerr << "Failed to write value." << "\n";
        std::cin.get();
    }
    // -----------------------------------------------------------------------------------

    // -------------------- Write REG_MULTI_SZ value in the registry ---------------------
    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"MaValeurMultiSZ";
    std::vector<std::wstring> values = {L"Valeur1", L"Valeur2", L"Valeur3"};
    
    if (luna.Write( registryPath, keyName, values) == true){
        std::cout << "Value successfully written" << "\n";
    }else{
        std::cout << "Failed to write value." << "\n";
    }
    // -------------------------------------------------------------------------------------

    // ------------------- Write REG_EXPAND_SZ value in the registry -----------------------
    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"MaValeurExpandSZ";
    if (luna.Write(registryPath, keyName, L"%SystemRoot%\\System32") == true){
        std::cout << "Value successfully written" << "\n";
    }else{
        std::cout << "Failed to write value." << "\n";
    }
    // -------------------------------------------------------------------------------------


    return 0;
};
````

<br>
---
<br>

### Method : `Read()`

**Description** :  
Reads the content of a registry key. This method is overloaded.

#### Settings :
- `params1` : The path to the registry key.
- `params2` : The name of the registry key holding the value.
- `params3` : A variable to store the value read.

#### Returned value :
- `bool` : Returns `true` if the operation was successful.

#### Example of use :

````cpp
#define INCLUDE_REGISTRE
#include <iostream>
#include <iomanip>
#include <Torixyna/Torixyna.hpp>

int main(){
    SetConsoleOutputCP(CP_UTF8);

    Torixyna::Registry::Luna luna(HKEY_CURRENT_USER); 

    // ------------------------ Read BINARY value -------------------------------------------
    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"test";

    std::vector<BYTE> binaryData;
    if (luna.Read(registryPath, keyName, binaryData)){
        std::wcout << L"Binary value read : ";
        for (size_t i = 0; i < binaryData.size(); i++){
            std::wcout << std::hex << std::setw(2) << std::setfill(L'0') << (int)binaryData[i] << L" ";
        }
        std::wcout << std::endl;
    }else{
        std::cout << "Failed to read binary value." << "\n";
    }
    //----------------------------------------------------------------------------------------

    //------------------------------ Read REG_MULTI_SZ ---------------------------------------
    std::vector<std::wstring> values;
    if (luna.Read(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", L"MaValeurMultiSZ", values)){
        std::wcout << L"Valeur REG_MULTI_SZ lue avec succès :\n";
        for (const auto& val : values){
            std::wcout << L" - " << val << "\n";
        }
    }else{
        std::wcout << L"Failed to read REG_MULTI_SZ value." << "\n";
    }
    // -----------------------------------------------------------------------------------------

    //------------------------------ Read REG_EXPAND_SZ -----------------------------------------
    std::wstring value;

    if (luna.Read(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", L"MaValeurExpandSZ", value)){
        std::wcout << L"Valeur REG_EXPAND_SZ value read : " << value << "\n";
    }else{
        std::cout << "Failed to read REG_EXPAND_SZ value" << "\n";
    }
    // -------------------------------------------------------------------------------------------

    // ----------------------------- Read REG_SZ -------------------------------------------------
    const wchar_t* registryPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    const wchar_t* keyName = L"OneDrive";
    std::wstring value;
    if (Read(registryPath, keyName, value)){
        std::wcout << L"wstring Value : " << value << "\n";
    }else{
        std::wcout << L"ERROR" << "\n";
    }
    // -------------------------------------------------------------------------------------------

    //--------------------------------- Read DWORD ------------------------------------------------
    DWORD value;
    if(luna.Read(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", L"testDWORD", value) == true){
        std::cout << "The value is : " << value << "\n";
    }else{
        std::cout << "Error" << "\n";
    }
    // --------------------------------------------------------------------------------------------

    // ---------------------------------- Read QWORD ----------------------------------------------
    unsigned __int64 val;
    if(luna.Read(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", L"testQword", val) == true){
        std::cout << "The value is : " << val << "\n";
    }else{
        std::cout << "Error" << "\n";
    }
    // ---------------------------------------------------------------------------------------------


    return 0;
}
````

<br>
---
<br>

### Method : `Delete()`

**Description** :  
Deletes a registry key.

#### Settings :
- `const wchar_t * Register` :  The path to the registry key.
- `const WCHAR * NameKey` : The name of the registry key to delete.
  
#### Returned value :
- `bool` : Returns `true` if the operation was successful.

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
        std::cout << "Key successfully deleted" << "\n";
        std::cin.get();
    }else{
        std::cerr << "Error" << "\n";
        std::cin.get();
    }


    return 0;
}
````


<br>

# Class LunaInfo : 

<br>
---
<br>

### Method : `GetSizeRegistry()`

**Description** :  
Retrieves the current size and maximum size of the registry, storing the values in the structure passed as a parameter in MB.

#### Settings :
- `RegistrySizeInfo& data` :  A structure holding the current and maximum size values.
  
#### Returned value :
- `bool` : Returns `true` if the operation was successful.

#### Example of use :

````cpp
#define INCLUDE_REGISTRE
#include <iostream>
#include <Torixyna/Torixyna.hpp>

int main(){
    SetConsoleOutputCP(CP_UTF8);
    Torixyna::Registry::LunaInfo luna(HKEY_CURRENT_USER);
    Torixyna::Registry::RegistrySizeInfo info;
    
    if(luna.GetSizeRegistry(info) == true){
        std::cout << "Current size : " << info.currentSize << "\n";
        std::cout << "Maximum size : " << info.maxSize << "\n";
    }else{
        std::cout << "Error" << "\n";
    }

    return 0;
}
````

<br>
---
<br>

### Method : `GetRegisterTypeValue()`

**Description** :  
Retrieves the type of value stored in a registry key (e.g., REG_SZ, REG_DWORD, REG_BINARY, REG_QWORD, REG_MULTI_SZ, REG_EXPAND_SZ, REG_NONE, REG_LINK).

#### Settings :

- `const wchar_t * Register` : The path to the registry.
- `const wchar_t* valueName` : The name of the key to check.
- `RegistryValueInfo& data` :  A structure that stores the type of value stored in the registry key.
  
#### Returned value :
- `bool` : Returns `true` if the operation was successful.

#### Example of use :

````cpp
#define INCLUDE_REGISTRE
#include <iostream>
#include <Torixyna/Torixyna.hpp>

int main(){
    SetConsoleOutputCP(CP_UTF8);
    Torixyna::Registry::LunaInfo luna(HKEY_CURRENT_USER);
    Torixyna::Registry::RegistryValueInfo info;

    if (luna.GetRegisterTypeValue(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", L"testQword", info) == true){

        if(info.valueNameT == REG_QWORD){
            std::cout << "The value is a QWORD" << "\n";
        }
    }

    return 0;
}
````



# class LunaConfig : 


<br>
---
<br>

### Method : `SetsFileExtensionsVisibility()`

**Description** :  
This method allows you to enable or disable the visibility of file extensions.
If the parameter showExtensions is set to true, the file extensions are displayed.
If the parameter is set to false, the file extensions are hidden.
The method returns true if everything was successful.

#### Settings :

- `bool showExtensions` : parameter showExtensions.
  
#### Returned value :
- `bool` : The method returns `true` if everything was successful.

#### Example of use :

````cpp
#define INCLUDE_REGISTRE
#include <iostream>
#include <Torixyna/Torixyna.hpp>

int main(){
    SetConsoleOutputCP(CP_UTF8);

    Torixyna::Registry::LunaConfig l;
    
    if (l.SetsFileExtensionsVisibility(true)){
        std::cout << "Les extension des fichier sont visible" << "\n";
    }else{
        std::cout << "Error" << "\n";
    }

    return 0;
}
````

<br>
---
<br>

### Method : `SetsShowItemsHide()`

**Description** :  
Sets the visibility of hidden items. 
If set to true, hidden items are displayed.
If set to false, hidden items are not displayed.
The method returns false if there is an error, and true if there is no error.

#### Settings :

- `bool Status` : parameter Status.
  
#### Returned value :
- `bool` : The method returns `false` if there is an error, and `true` if there is no error..

#### Example of use :

````cpp
#define INCLUDE_REGISTRE
#include <iostream>
#include <Torixyna/Torixyna.hpp>

int main(){
    SetConsoleOutputCP(CP_UTF8);

    Torixyna::Registry::LunaConfig l;
    
    if (l.SetsShowItemsHide(true)){
        std::cout << "affiche les éléments masquer" << "\n";
    }else{
        std::cout << "Error" << "\n";
    }

    return 0;
}
````

<br>
---
<br>

### Method : `SetsTheStatusOfCheckboxes()`

**Description** :  
Sets the status of checkboxes.
Activates checkboxes if the 'Status' parameter is set to true.
Deactivates checkboxes if the 'Status' parameter is set to false.
This method returns true if the operation is successful.

#### Settings :

- `bool Status` : parameter Status.
  
#### Returned value :
- `bool` : This method returns `true` if the operation is successful.

#### Example of use :

````cpp
#define INCLUDE_REGISTRE
#include <iostream>
#include <Torixyna/Torixyna.hpp>

int main(){
    SetConsoleOutputCP(CP_UTF8);

    Torixyna::Registry::LunaConfig l;
    
    if (l.SetsTheStatusOfCheckboxes(true)){
        std::cout << "Les cases à coché sont activer" << "\n";
    }else{
        std::cout << "Error" << "\n";
    }

    return 0;
}
````


<br>
---
<br>

### Method : `SetWallpaper()`

**Description** :  
Method to set the wallpaper
This method takes the image path as a parameter.
It returns false if there is an error and true if everything goes well.

#### Settings :

- `const std::wstring& imagePath` : Attend le chemin ver l'image.
  
#### Returned value :
- `bool` : This method returns `true` if the operation is successful.

#### Example of use :

````cpp
#define INCLUDE_REGISTRE
#include <iostream>
#include <Torixyna/Torixyna.hpp>

int main(){
    SetConsoleOutputCP(CP_UTF8);

    Torixyna::Registry::LunaConfig l;
    const wchar_t* pathWalpper = L"Background.jpg";

    if (l.SetWallpaper(pathWalpper)){
        std::cout << "Le fond d'écran à bien été modifier" << "\n";
    }else{
        std::cout << "Error" << "\n";
    }

    return 0;
}
````