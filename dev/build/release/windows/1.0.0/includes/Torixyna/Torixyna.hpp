#pragma once

// Fichiers d'inclusion de la library : ce fichier sert à inclure toutes les module que je développe

#ifdef INCLUDE_PRIVILEGES
    #include "Privileges/PrivilegesManager.hpp" // module : getion des privilège
#endif

#ifdef INCLUDE_SPEAKER
    #include "Speaker/Speaker.hpp" // module : getion des speaker
#endif

#ifdef INCLUDE_REGISTRE
    #include "Registre/Luna.hpp" // module : getion des registre
#endif

#ifdef INCLUDE_MATH
    #include "Math/Pythagore.hpp" // module : pythagore
#endif 

#if !defined(INCLUDE_PRIVILEGES) && !defined(INCLUDE_SPEAKER) && !defined(INCLUDE_REGISTRE) && !defined(INCLUDE_MATH)
    #include "Privileges/PrivilegesManager.hpp"
    #include "Speaker/Speaker.hpp"
    #include "Registre/Luna.hpp"
    #include "Math/Pythagore.hpp"
#endif