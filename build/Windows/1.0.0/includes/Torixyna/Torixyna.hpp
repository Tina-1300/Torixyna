#pragma once

#if defined(_WIN32) || defined(_WIN64)

    #ifdef INCLUDE_SPEAKER
        #include "Speaker/Speaker.hpp" // module : getion des speaker
    #endif

    #ifdef INCLUDE_REGISTRE
        #include "Registry/Luna.hpp" // module : getion des registre
    #endif


#else
    #error "Unsupported operating system !"    
#endif



