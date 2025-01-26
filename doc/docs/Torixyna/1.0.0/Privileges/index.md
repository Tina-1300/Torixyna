# Documentation du module : Privilege 

Dans le Module Privilège nous avon :

- Namespace Torixyna::Privileges : 
    
    - enum class : 
        - PrivilegeLevel : Permet d'avoir un code pour chaque niveaux de privilège, ex : système, admin, etc...

    - struct : 
        - PrivilegeStatus : [pour plus de detaille...](https://www.google.com)
    
    - class : 
        - PrivilegesManager : Gère les principale fonctionalité des privilège : élévation, récupération des droit actuel
    
    - Méthode Appartenant à la class PrivilegesManager : 

        - GetPrivilegeFromCurrentSession : Permet de récupéré les droit actuelle du programme
        - ElevationOfPrivileges : Permet une élévation de privilège en fonction du grade demander par l'utilisateur... Warning il y a un bug cette méthode ne fonctionne pas bien
        - DisplayPrivileges : Permet d'afficher les privilège, en console.
        
