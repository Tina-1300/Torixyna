# PrivilegesManager

## Description

The **PrivilegesManager** module allows you to manage the PC privileges simply and efficiently.

### Features

- Retrieve the privileges of your program at runtime.  
- Elevate these privileges. 

---

## Compilation

To use the **PrivilegesManager** module, you must compile your program with the following options:

````bash
g++ -o t.exe t.cpp -lTorixyna & color
````


---


<br>

### Method : `getVolume()`

**Description** :  
Allows you to retrieve the current volume value. 

#### Settings :
- `None` :  No settings.
  
#### Returned value :
- `float` : Returns the current volume.

#### Example of use :

````cpp
#include <Torixyna/Torixyna.hpp>

int main(){
    Torixyna::Speaker::Speaker sound;

    float resultat = sound.getVolume();
    std::cout << resultat << std::endl;

    return 0;
}
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