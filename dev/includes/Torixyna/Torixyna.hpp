#pragma once

#if defined(_WIN32) || defined(_WIN64)

    #ifdef INCLUDE_PRIVILEGES
        #include "Privileges/PrivilegesManager.hpp" // module : getion des privilège
    #endif

    #ifdef INCLUDE_SPEAKER
        #include "Speaker/Speaker.hpp" // module : getion des speaker
    #endif

    #ifdef INCLUDE_REGISTRE
        #include "Registre/Luna.hpp" // module : getion des registre
    #endif


#else
    #error "Système d'exploitation non pris en charge !"    
#endif



