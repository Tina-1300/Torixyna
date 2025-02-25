@echo off
setlocal enabledelayedexpansion

:: Définir le répertoire cible
set TARGET_DIR=build\release\windows\1.0.0\includes

:: Se déplacer dans le répertoire
cd /d "%TARGET_DIR%"

:: Supprimer tous les fichiers et dossiers sauf "Torixyna"
for /d %%D in (*) do (
    if /i not "%%D" == "Torixyna" (
        rd /s /q "%%D"
    )
)

for %%F in (*) do (
    if /i not "%%F" == "Torixyna" (
        del /q "%%F"
    )
)

echo Suppression terminée.
