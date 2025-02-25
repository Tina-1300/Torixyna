#pragma once
#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <stdexcept>
#include <iostream>

/*s
compilation :
g++ -o test.exe test.cpp -lTorixyna -lole32 -lstdc++ -luuid & color
*/

namespace Torixyna::Speaker{

    class Speaker{
        public:
            Speaker();
            ~Speaker();

            float getVolume();
            bool setVolume(float volume);
            bool isMuted();
            bool setMute(bool mute);

        private:
            IAudioEndpointVolume* endpointVolume;
            void initialize();
    };


};