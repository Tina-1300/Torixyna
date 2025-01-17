#include "../../../includes/Torixyna/Privileges/PrivilegesManager.hpp"



namespace Torixyna::Privileges{

    PrivilegeStatus PrivilegesManager::GetPrivilegeFromCurrentSession(PrivilegeStatus& dataPrivileges){
        HANDLE hToken = NULL;
        DWORD dwLengthNeeded = 0;
        PTOKEN_MANDATORY_LABEL pTIL = NULL;

        if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)){
            dataPrivileges.isSuccess = false;
            return dataPrivileges;
        }

        if (!GetTokenInformation(hToken, TokenIntegrityLevel, NULL, 0, &dwLengthNeeded)){
            if (GetLastError() != ERROR_INSUFFICIENT_BUFFER){
                CloseHandle(hToken);
                dataPrivileges.isSuccess = false;
                return dataPrivileges;
            }
        }

        pTIL = (PTOKEN_MANDATORY_LABEL)LocalAlloc(LPTR, dwLengthNeeded);
        
        if (pTIL == NULL){
            CloseHandle(hToken);
            dataPrivileges.isSuccess = false;
            return dataPrivileges;
        }

        if (!GetTokenInformation(hToken, TokenIntegrityLevel, pTIL, dwLengthNeeded, &dwLengthNeeded)){
            LocalFree(pTIL);
            CloseHandle(hToken);
            dataPrivileges.isSuccess = false;
            return dataPrivileges;
        }

        DWORD dwIntegrityLevel = *GetSidSubAuthority(pTIL->Label.Sid, (DWORD)(UCHAR)(*GetSidSubAuthorityCount(pTIL->Label.Sid) - 1));

        if (dwIntegrityLevel >= SECURITY_MANDATORY_SYSTEM_RID){
            dataPrivileges.currentPrivilege = PrivilegeLevel::System;//344
        }else if (dwIntegrityLevel >= SECURITY_MANDATORY_HIGH_RID){
            dataPrivileges.currentPrivilege = PrivilegeLevel::Admin; //345
        }else if (dwIntegrityLevel >= SECURITY_MANDATORY_MEDIUM_RID){
            dataPrivileges.currentPrivilege = PrivilegeLevel::User; // 346
        }else if (dwIntegrityLevel >= SECURITY_MANDATORY_LOW_RID){
             dataPrivileges.currentPrivilege = PrivilegeLevel::Bas; // 347
        }else{
            dataPrivileges.currentPrivilege = PrivilegeLevel::Invite; // 348
        }

        LocalFree(pTIL);
        CloseHandle(hToken);

        dataPrivileges.isSuccess = true;
        return dataPrivileges;
    };

    // ne marche pas encore a modifier pour que les élévation marche
    PrivilegeStatus PrivilegesManager::ElevationOfPrivileges(PrivilegeLevel PrivilegesElevation, PrivilegeStatus& dataPrivileges){
        if (PrivilegesElevation == PrivilegeLevel::Admin){ // admin
            wchar_t exePath[MAX_PATH];
            if(!GetModuleFileNameW(NULL, exePath, MAX_PATH)){
                dataPrivileges.isSuccess = false;
                return dataPrivileges;
            }
            SHELLEXECUTEINFOW sei = { sizeof(SHELLEXECUTEINFOW) };
            sei.lpVerb = L"runas";
            sei.lpFile = exePath;
            sei.hwnd = NULL;
            sei.nShow = SW_NORMAL;
            sei.fMask = SEE_MASK_NOASYNC;

            if (!ShellExecuteExW(&sei)){
                DWORD error = GetLastError();
                if (error == ERROR_CANCELLED){
                    dataPrivileges.isSuccess = false; // error
                    return dataPrivileges;
                }
                dataPrivileges.isSuccess = false;
                return dataPrivileges; // refus de l'utilisateur
            }
            dataPrivileges.currentPrivilege = PrivilegeLevel::Admin;
            dataPrivileges.isSuccess = true;

            // crée un nouveaux processus en laissant l'utilisateur paramétré le processus 
            // et avant de crée le nouveaux processus on récupère l'ancien comme ça une fois que l'on re ouvre 
            // l'application avec le nouveau processus bas on kill l'ancien processus 
        }

        
        return dataPrivileges;
    };  


    // Cette fonction marche.
    void PrivilegesManager::DisplayPrivileges(PrivilegeStatus& data){
        std::string resultat;
        resultat =  (data.currentPrivilege == PrivilegeLevel::System) ? "System": // system
                    (data.currentPrivilege == PrivilegeLevel::Admin) ? "Admin": // admin
                    (data.currentPrivilege == PrivilegeLevel::User) ? "User": // user
                    (data.currentPrivilege == PrivilegeLevel::Bas) ? "Low": // bas
                    (data.currentPrivilege == PrivilegeLevel::Invite) ? "Guest": // inviter 
                    "Privileges Unknown"; // privileges inconnu 
        std::cout << resultat << "\n";
    };


};