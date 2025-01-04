#pragma once 
#include <iostream>
#include <windows.h>
#include <aclapi.h>

/*
documentation : 

https://learn.microsoft.com/en-us/windows/win32/secauthz/authorization-portal
https://learn.microsoft.com/en-us/windows/win32/secauthz/privileges
https://learn.microsoft.com/en-us/windows/win32/api/_security/
https://learn.microsoft.com/en-us/windows/win32/api/_processthreadsapi/
https://learn.microsoft.com/fr-fr/windows/win32/apiindex/windows-api-list

*/


/*
compilation :
g++ -O3 -o test.exe test.cpp -lTorixyna
*/

/*
Tableau de code des privileges :

System         = 344   (Processus ayant les privilèges les plus élevés. | Process with the highest privileges.)
Administrateur = 345   (Processus administratifs avec des droits élevés. | Administrative processes with elevated rights)
Utilisateur    = 346   (Processus utilisateur standard. | Standard user processes.)
Bas            = 347   (Processur avec un peut plus de droit que Invité. | Processor with a little more rights than Guest.)
Inviter        = 348   (Processus avec des droits les plus restreints. (invité) | Process with the most restricted rights. (guest))
*/


// Version 1.0.0
namespace Torixyna{
    namespace Privileges{

        enum class PrivilegeLevel{
            System = 344,
            Admin,
            User,
            Bas, 
            Invite
        };

        struct PrivilegeStatus{
            PrivilegeLevel currentPrivilege;// return l'identifiant du privileges actuel si ses Admin ou user ou autre...
            bool isSuccess; // return si il y a une error = false sinon return true
        };



        class PrivilegesManager{
            public:
                // Cette méthode permet de récupéré le privileges actuelle du programme
                PrivilegeStatus GetPrivilegeFromCurrentSession(PrivilegeStatus& dataPrivileges);

                // Cette méthode permet d'éléver ses privileger au seuille que l'on veut si ses admin, ou System etc....
                PrivilegeStatus ElevationOfPrivileges(PrivilegeLevel PrivilegesElevation, PrivilegeStatus& dataPrivileges); // Cette méthode contient une error. A corriger

                // affiche le privilèges actuelle
                void DisplayPrivileges(PrivilegeStatus& data);
        };


    };
};