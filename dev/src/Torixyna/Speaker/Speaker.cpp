#include "../../../includes/Torixyna/Speaker/Speaker.hpp"



namespace Torixyna::Speaker{

    Speaker::Speaker() : endpointVolume(nullptr){
        initialize();
    };
    
    
    Speaker::~Speaker(){
        if (endpointVolume){
            endpointVolume->Release();
        }
        CoUninitialize();
    };

    // No parameters..
    // Returns the current volume.
    float Speaker::getVolume(){
        float currentVolume = 0.0f;
        HRESULT hr = endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
        if (FAILED(hr)){
            throw std::runtime_error("Failed to get current volume level.");
        }
        return currentVolume * 100; 
    };

    // The volume to define must be a number between 0.0f and 100.0f (inclusive).
    // Returns `true` if the volume was correctly modified, `false` in case of error.
    bool Speaker::setVolume(float volume){
        if (volume < 0.0f || volume > 100.0f){
            throw std::invalid_argument("Volume must be between 0 and 100.");
            return false;
        }
        HRESULT hr = endpointVolume->SetMasterVolumeLevelScalar(volume / 100.0f, nullptr);
        if (FAILED(hr)){
            throw std::runtime_error("Failed to set volume level.");
            return false;
        }
        return true;
    };

    // No parameters..
    // Returns `true` if the audio is muted, `false` if it is not muted.
    bool Speaker::isMuted(){
        BOOL isMuted = FALSE;
        HRESULT hr = endpointVolume->GetMute(&isMuted);
        if (FAILED(hr)){
            throw std::runtime_error("Failed to get mute status.");
        }
        return isMuted;
    };

    // A boolean value. Pass true to mute the audio, or false to unmute it.
    // Returns `true` if the mute status was successfully set, `false` in case of an error.
    bool Speaker::setMute(bool mute){
        HRESULT hr = endpointVolume->SetMute(mute, nullptr);
        if (FAILED(hr)){
            throw std::runtime_error("Failed to set mute status.");
            return false;
        }
        return true;
    };


    
            
    void Speaker::initialize(){
        CoInitialize(nullptr);

        IMMDeviceEnumerator* deviceEnumerator = nullptr;
        HRESULT hr = CoCreateInstance(
            __uuidof(MMDeviceEnumerator),
            nullptr,
            CLSCTX_ALL,
            __uuidof(IMMDeviceEnumerator),
            (void**)&deviceEnumerator);

        if (FAILED(hr) || !deviceEnumerator){
            throw std::runtime_error("Failed to create device enumerator.");
        }

        IMMDevice* defaultDevice = nullptr;
        hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
        deviceEnumerator->Release();

        if (FAILED(hr) || !defaultDevice){
            throw std::runtime_error("Failed to get default audio endpoint.");
        }

        hr = defaultDevice->Activate(
            __uuidof(IAudioEndpointVolume),
            CLSCTX_ALL,
            nullptr,
            (void**)&endpointVolume);
        defaultDevice->Release();

        if (FAILED(hr) || !endpointVolume){
            throw std::runtime_error("Failed to activate audio endpoint.");
        }
    };



};