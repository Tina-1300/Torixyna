#pragma once

// Fichiers d'inclusion du framework : ce fichier sert à inclure toutes les module que je développe

#ifdef INCLUDE_PRIVILEGES
    #include "Privileges/PrivilegesManager.hpp" // module : getion des privilège
#endif

#ifdef INCLUDE_SPEAKER
    #include "Speaker/Speaker.hpp" // module : getion des speaker
#endif

#ifdef INCLUDE_REGISTRE
    #include "Registre/Luna.hpp" // module : getion des registre
#endif

#if !defined(INCLUDE_PRIVILEGES) && !defined(INCLUDE_SPEAKER) && !defined(INCLUDE_REGISTRE)
    #include "Privileges/PrivilegesManager.hpp"
    #include "Speaker/Speaker.hpp"
    #include "Registre/Luna.hpp"
#endif