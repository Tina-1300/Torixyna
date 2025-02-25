#define INCLUDE_SPEAKER
#include <Torixyna/Torixyna.hpp>

// g++ -o test.exe test.cpp -lTorixyna -lole32 -lstdc++ -luuid & color

int main(){

    Torixyna::Speaker::Speaker sound;

    if(sound.isMuted() == true){
        sound.setMute(false); 
        if(sound.getVolume() != 20){
            sound.setVolume(20.0f); 
        }
        sound.setVolume(10.0f);
    }else{
        sound.setMute(true);
    }
    


    return 0;
}
