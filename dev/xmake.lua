-- xmake f -c
-- xmake
--xmake f -m release

-- Définir le projet
set_project("Torixyna")

-- Configurer le compilateur pour MinGW
toolchain("mingw")
    set_kind("standalone") -- Indique un compilateur indépendant
    set_sdkdir("C:/mingw64") -- Chemin vers le répertoire MinGW
toolchain_end()

-- Appliquer le toolchain "mingw"
set_toolchains("mingw")

-- Définir la cible principale
target("Torixyna")
set_kind("static") -- Générer une bibliothèque statique
set_languages("c++20") -- Définir la version de C++
add_includedirs("includes") -- Ajouter les répertoires d'en-tête
add_files("src/**.cpp") -- Ajouter tous les fichiers source de manière récursive

-- Répertoire de sortie pour la bibliothèque
set_targetdir("build/release/windows/1.0.0/lib")
    -- Action après la compilation
    after_build(function (target)
        -- Copier tous les fichiers d'en-tête, y compris les sous-dossiers
        os.cp("includes/*", "build/release/windows/1.0.0/includes/")
    end)

        -- xmake f --toolchain=mingw --sdk=C:/mingw64