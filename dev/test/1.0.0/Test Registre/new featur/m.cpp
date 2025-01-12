#include <windows.h>
#include <iostream>

bool SetWallpaper(const std::wstring& imagePath){
    HKEY hKey;
    LONG result;

    result = RegOpenKeyExW(HKEY_CURRENT_USER, L"Control Panel\\Desktop", 0, KEY_SET_VALUE, &hKey);
    if (result != ERROR_SUCCESS){
        //Erreur lors de l'ouverture de la cle de registre.
        return false;
    }

    DWORD fileAttr = GetFileAttributesW(imagePath.c_str());
    if (fileAttr == INVALID_FILE_ATTRIBUTES){
        //Le fichier image specifie n'existe pas.
        RegCloseKey(hKey);
        return false;
    }

    // Définir le chemin de l'image comme fond d'écran
    result = RegSetValueExW(hKey, L"Wallpaper", 0, REG_SZ, (const BYTE*)imagePath.c_str(), (imagePath.size() + 1) * sizeof(wchar_t));
    if (result != ERROR_SUCCESS){
        //Erreur lors de la modification du registre pour l'image.
        RegCloseKey(hKey);
        return false;
    }

    // Définir le style de fond d'écran (0: Ajuster, 1: Carrelé, 2: Centré)
    const wchar_t* wallpaperStyle = L"2";  // 2 : Centré
    result = RegSetValueExW(hKey, L"WallpaperStyle", 0, REG_SZ, (const BYTE*)wallpaperStyle, (wcslen(wallpaperStyle) + 1) * sizeof(wchar_t));
    if (result != ERROR_SUCCESS){
        //Erreur lors de la modification du style du fond d'ecran.
        RegCloseKey(hKey);
        return false;
    }

    // Définir si le fond d'écran doit être tuilé (0 : Non, 1 : Oui)
    const wchar_t* tileWallpaper = L"0";  // 0 : Pas de carrelage
    result = RegSetValueExW(hKey, L"TileWallpaper", 0, REG_SZ, (const BYTE*)tileWallpaper, (wcslen(tileWallpaper) + 1) * sizeof(wchar_t));
    if (result != ERROR_SUCCESS){
        //Erreur lors de la modification de la tuile du fond d'ecran.
        RegCloseKey(hKey);
        return false;
    }

    RegCloseKey(hKey);

    BOOL success = SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (PVOID)imagePath.c_str(), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
    if (!success){
        //Erreur lors de l'application du fond d'ecran.
        return false;
    }else{
        //Le fond d'ecran a ete change avec succes.
        return true;
    }
};

int main(){

    std::wstring imagePath = L"C:\\Users\\alexp\\Downloads\\Devil.jpg";
    SetWallpaper(imagePath);
    return 0;
}
