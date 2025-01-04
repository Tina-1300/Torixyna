# Speaker Module

## Description

The **Speaker** module allows you to manage the PC volume simply and efficiently.

### Features

- Retrieve the current volume.
- Check the volume state to determine if it is muted or not.
- Modify the volume state (mute or unmute).
- Adjust the volume level between `0.0f` and `100.0f`.

---

## Compilation

To use the **Speaker** module, you must compile your program with the following options:

````bash
g++ -o test.exe test.cpp -lTorixyna -lole32 -lstdc++ -luuid & color
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
#define INCLUDE_SPEAKER
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

### Method : `isMuted()`

**Description** :  
Returns whether the audio device is currently muted or not. This function checks if the sound is muted and returns a boolean value.

#### Settings :
- `None` :  No parameters..
  
#### Returned value :
- `bool` : Returns `true` if the audio is muted, `false` if it is not muted.

#### Example of use :

````cpp
#define INCLUDE_SPEAKER
#include <Torixyna/Torixyna.hpp>

int main(){
    Torixyna::Speaker::Speaker sound;

    if (sound.isMuted() == true){
        std::cout << "The audio is muted." << std::endl;
    }else{
        std::cout << "The audio is not muted." << std::endl;
    }

    return 0;
}
````

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