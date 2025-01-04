#define INCLUDE_PRIVILEGES
#include <Torixyna/Torixyna.hpp>
#include <conio.h>
#include <string>
#include <cstdio>

// g++ -o t.exe t.cpp -lTorixyna & color



int main(){
    Torixyna::Privileges::PrivilegesManager p;
    
    Torixyna::Privileges::PrivilegeStatus r;
    auto admin = Torixyna::Privileges::PrivilegeLevel::Admin;

    p.GetPrivilegeFromCurrentSession(r);
    if (r.isSuccess){
        if (r.currentPrivilege != admin){
            std::cout << "Tentative d'elevation de privileges...\n";
            auto result = p.ElevationOfPrivileges(admin, r);
            if (result.isSuccess && result.currentPrivilege == admin){
                std::cout << "elevation reussie\n";
                p.DisplayPrivileges(r);
                system("sfc /scannow");
            }else{
                std::cerr << "Erreur lors de l'elevation des privileges.\n";
            }
        }
    }

    return 0;
}
