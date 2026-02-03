@echo off
chcp 65001 >nul
echo.
echo ???????????????????????????????????????????????????????????
echo   ?? NETTOYAGE ET RÉORGANISATION - DÉMINEUR HD
echo ???????????????????????????????????????????????????????????
echo.

echo ??  Ce script va:
echo    1. Supprimer les fichiers .md redondants
echo    2. Supprimer les scripts .bat inutiles
echo    3. Réorganiser TOUT dans des sous-dossiers
echo.
echo ?? Structure finale:
echo    demineur/
echo    ??? src/          (Code source uniquement)
echo    ??? docs/         (5 docs essentiels)
echo    ??? scripts/      (4 scripts essentiels)
echo    ??? assets/       (Sons et images)
echo    ??? build/        (Builds)
echo.
set /p confirm="Continuer ? (O/N): "

if /i not "%confirm%"=="O" (
    echo ? Annulé.
    pause
    exit /b 0
)

echo.
echo ???????????????????????????????????????????????????????????
echo   ???  ÉTAPE 1/3: NETTOYAGE DES FICHIERS INUTILES
echo ???????????????????????????????????????????????????????????
echo.

echo ???  Suppression des .md redondants...

REM Supprimer les fichiers redondants
if exist "RECAP_COMPLET.md" (
    del "RECAP_COMPLET.md"
    echo ? Supprimé: RECAP_COMPLET.md (redondant avec PROJET_COMPLET.md)
)

if exist "ORGANISATION_PROJET.md" (
    del "ORGANISATION_PROJET.md"
    echo ? Supprimé: ORGANISATION_PROJET.md (redondant avec NOUVELLE_STRUCTURE.md)
)

if exist "PACKAGE_GITHUB_COMPLET.md" (
    del "PACKAGE_GITHUB_COMPLET.md"
    echo ? Supprimé: PACKAGE_GITHUB_COMPLET.md (redondant avec GITHUB_RELEASE_GUIDE.md)
)

if exist "RECAP_GITHUB.txt" (
    del "RECAP_GITHUB.txt"
    echo ? Supprimé: RECAP_GITHUB.txt (redondant)
)

if exist "GUIDE_REORGANISATION.txt" (
    del "GUIDE_REORGANISATION.txt"
    echo ? Supprimé: GUIDE_REORGANISATION.txt (temporaire)
)

if exist "SYSTEME_AUDIO_RESUME.md" (
    del "SYSTEME_AUDIO_RESUME.md"
    echo ? Supprimé: SYSTEME_AUDIO_RESUME.md (info dans INSTALLATION_MUSIQUE.md)
)

if exist "MUSIQUES_ALTERNATIVES.md" (
    del "MUSIQUES_ALTERNATIVES.md"
    echo ? Supprimé: MUSIQUES_ALTERNATIVES.md (info dans INSTALLATION_MUSIQUE.md)
)

if exist "OPTIMISATIONS_PERFORMANCE.md" (
    del "OPTIMISATIONS_PERFORMANCE.md"
    echo ? Supprimé: OPTIMISATIONS_PERFORMANCE.md (détails techniques inutiles pour utilisateurs)
)

echo.
echo ???  Suppression des .bat inutiles...

if exist "push_github.bat" (
    del "push_github.bat"
    echo ? Supprimé: push_github.bat (redondant avec github_package.bat)
)

if exist "verifier_audio.bat" (
    del "verifier_audio.bat"
    echo ? Supprimé: verifier_audio.bat (utilitaire rare)
)

if exist "telecharger_musiques.bat" (
    del "telecharger_musiques.bat"
    echo ? Supprimé: telecharger_musiques.bat (utilitaire rare)
)

if exist "SUCCES_REORGANISATION.bat" (
    del "SUCCES_REORGANISATION.bat"
    echo ? Supprimé: SUCCES_REORGANISATION.bat (temporaire)
)

echo.
echo ? Nettoyage terminé !

echo.
echo ???????????????????????????????????????????????????????????
echo   ?? ÉTAPE 2/3: CRÉATION DE LA STRUCTURE
echo ???????????????????????????????????????????????????????????
echo.

REM Créer les dossiers
echo ?? Création des dossiers...
if not exist "src" mkdir "src"
if not exist "docs" mkdir "docs"
if not exist "scripts" mkdir "scripts"
if not exist "assets" mkdir "assets"
if not exist "assets\sounds" mkdir "assets\sounds"
if not exist "assets\images" mkdir "assets\images"
if not exist "build" mkdir "build"
if not exist "build\Release" mkdir "build\Release"
if not exist "build\packages" mkdir "build\packages"

echo ? Dossiers créés !

echo.
echo ???????????????????????????????????????????????????????????
echo   ?? ÉTAPE 3/3: ORGANISATION DES FICHIERS
echo ???????????????????????????????????????????????????????????
echo.

REM ========================================
REM CODE SOURCE (src/)
REM ========================================
echo ?? Organisation du code source...

REM Copier TOUT le contenu de demineur/ vers src/
if exist "demineur" (
    echo    Copie de demineur/ vers src/...
    xcopy "demineur\*.*" "src\" /E /Y /Q >nul
    echo ? Code source copié dans src/
)

REM ========================================
REM DOCUMENTATION (docs/) - SEULEMENT LES ESSENTIELS
REM ========================================
echo ?? Organisation de la documentation...

REM Garder seulement 5 fichiers essentiels
if exist "DEMARRAGE_RAPIDE.md" move /Y "DEMARRAGE_RAPIDE.md" "docs\" >nul
if exist "QUALITE_GRAPHIQUE.md" move /Y "QUALITE_GRAPHIQUE.md" "docs\" >nul
if exist "INSTALLATION_MUSIQUE.md" move /Y "INSTALLATION_MUSIQUE.md" "docs\" >nul
if exist "GITHUB_RELEASE_GUIDE.md" move /Y "GITHUB_RELEASE_GUIDE.md" "docs\" >nul
if exist "CREDITS.txt" move /Y "CREDITS.txt" "docs\" >nul

REM Supprimer les autres
if exist "PROJET_COMPLET.md" del "PROJET_COMPLET.md"
if exist "NOUVELLE_STRUCTURE.md" del "NOUVELLE_STRUCTURE.md"
if exist "GUIDE_DISTRIBUTION.md" del "GUIDE_DISTRIBUTION.md"
if exist "README_GITHUB.md" del "README_GITHUB.md"

echo ? Documentation organisée ! (5 fichiers essentiels)

REM ========================================
REM SCRIPTS (scripts/) - SEULEMENT LES ESSENTIELS
REM ========================================
echo ?? Organisation des scripts...

REM Garder seulement 4 scripts essentiels
if exist "build_release.bat" move /Y "build_release.bat" "scripts\" >nul
if exist "organiser_projet.bat" move /Y "organiser_projet.bat" "scripts\" >nul
if exist "creer_package.bat" move /Y "creer_package.bat" "scripts\" >nul
if exist "publier_github.bat" move /Y "publier_github.bat" "scripts\" >nul

REM Supprimer les autres
if exist "github_package.bat" del "github_package.bat"
if exist "reorganiser_projet.bat" del "reorganiser_projet.bat"

echo ? Scripts organisés ! (4 scripts essentiels)

REM ========================================
REM ASSETS (assets/)
REM ========================================
echo ?? Organisation des assets...

REM Sons
if exist "sounds" (
    xcopy "sounds\*.*" "assets\sounds\" /E /Y /Q >nul
    echo ? Assets/sounds copiés
)

echo ? Assets organisés !

REM ========================================
REM BUILDS (build/)
REM ========================================
echo ?? Organisation des builds...

REM Copier Release/ vers build/Release/
if exist "Release" (
    xcopy "Release\*.*" "build\Release\" /E /Y /Q >nul
    echo ? Build/Release copié
)

REM Déplacer les .zip vers build/packages/
if exist "*.zip" (
    move /Y "*.zip" "build\packages\" >nul 2>&1
    echo ? Packages .zip déplacés
)

echo ? Builds organisés !

echo.
echo ???????????????????????????????????????????????????????????
echo   ?? CRÉATION DES README
echo ???????????????????????????????????????????????????????????
echo.

REM ========================================
REM README PRINCIPAL (racine)
REM ========================================
(
echo # ?? Démineur HD
echo.
echo ^> **Jeu de Démineur moderne en Full HD 1920×1080**
echo.
echo ![Version](https://img.shields.io/badge/version-1.0-blue.svg^)
echo ![License](https://img.shields.io/badge/license-MIT-green.svg^)
echo ![Platform](https://img.shields.io/badge/platform-Windows-lightgrey.svg^)
echo ![Language](https://img.shields.io/badge/language-C++-orange.svg^)
echo.
echo ## ?? Structure du Projet
echo.
echo ```
echo demineur/
echo ??? src/          ?? Code source C++
echo ??? docs/         ?? Documentation (5 fichiers)
echo ??? scripts/      ?? Scripts (4 scripts)
echo ??? assets/       ?? Ressources
echo ??? .github/      ?? Templates GitHub
echo ??? build/        ?? Builds
echo ```
echo.
echo ## ?? Démarrage Rapide
echo.
echo ### Compiler
echo ```bash
echo scripts\build_release.bat
echo ```
echo.
echo ### Jouer
echo ```bash
echo build\Release\demineur.exe
echo ```
echo.
echo ## ?? Documentation
echo.
echo - **[Démarrage Rapide]^(docs/DEMARRAGE_RAPIDE.md^)** - Jouer en 3 min
echo - **[Qualité Graphique]^(docs/QUALITE_GRAPHIQUE.md^)** - 5 niveaux (1-5)
echo - **[Installation Musiques]^(docs/INSTALLATION_MUSIQUE.md^)** - Audio
echo - **[GitHub Release]^(docs/GITHUB_RELEASE_GUIDE.md^)** - Publier
echo - **[Crédits]^(docs/CREDITS.txt^)** - Attributions
echo.
echo ## ?? Fonctionnalités
echo.
echo - ? 4 niveaux de difficulté
echo - ? 5 qualités graphiques (touches 1-5)
echo - ? 60 FPS @ 1920×1080
echo - ? Audio professionnel (Kevin MacLeod)
echo - ? Score et combos
echo.
echo ## ?? Contrôles
echo.
echo ^| Touche ^| Action ^|
echo ^|--------^|--------^|
echo ^| Clic gauche ^| Révéler ^|
echo ^| Clic droit ^| Drapeau ^|
echo ^| **1-5** ^| Qualité ^|
echo ^| H ^| Aide ^|
echo ^| M ^| Audio ^|
echo ^| ESC ^| Menu ^|
echo.
echo ## ?? Scripts
echo.
echo ```bash
echo scripts\build_release.bat      # Compiler
echo scripts\organiser_projet.bat   # Organiser
echo scripts\creer_package.bat      # Créer .zip
echo scripts\publier_github.bat     # Publier
echo ```
echo.
echo ## ?? Licence
echo.
echo MIT License - Voir [LICENSE]^(LICENSE^)
echo.
echo **Musiques :** Kevin MacLeod (CC BY 4.0^) - [docs/CREDITS.txt]^(docs/CREDITS.txt^)
echo.
echo ---
echo.
echo **Développé avec ?? et C++**
) > "README.md"

echo ? README.md créé !

REM ========================================
REM README docs/
REM ========================================
(
echo # ?? Documentation - Démineur HD
echo.
echo ## ?? Documentation Disponible
echo.
echo ### Pour Utilisateurs
echo - **[Démarrage Rapide]^(DEMARRAGE_RAPIDE.md^)** - Jouer en 3 minutes
echo - **[Qualité Graphique]^(QUALITE_GRAPHIQUE.md^)** - 5 niveaux (touches 1-5)
echo - **[Installation Musiques]^(INSTALLATION_MUSIQUE.md^)** - Ajouter l'audio
echo.
echo ### Pour Développeurs
echo - **[GitHub Release]^(GITHUB_RELEASE_GUIDE.md^)** - Publier sur GitHub
echo - **[Crédits]^(CREDITS.txt^)** - Attributions Kevin MacLeod
echo.
echo ---
echo **[?? Retour]^(../README.md^)**
) > "docs\README.md"

echo ? docs/README.md créé !

REM ========================================
REM README scripts/
REM ========================================
(
echo # ?? Scripts - Démineur HD
echo.
echo ## ?? Scripts Disponibles
echo.
echo ### ?? Compilation
echo ```bash
echo build_release.bat
echo ```
echo Compile le projet en mode Release x64.
echo.
echo ### ?? Organisation
echo ```bash
echo organiser_projet.bat
echo ```
echo Organise les fichiers dans build/Release/.
echo.
echo ### ?? Package
echo ```bash
echo creer_package.bat
echo ```
echo Crée le fichier .zip de distribution.
echo.
echo ### ?? Publication
echo ```bash
echo publier_github.bat
echo ```
echo Publication complète sur GitHub (compile + organise + commit + tag).
echo.
echo ---
echo **[?? Retour]^(../README.md^)**
) > "scripts\README.md"

echo ? scripts/README.md créé !

REM ========================================
REM README assets/
REM ========================================
(
echo # ?? Assets - Démineur HD
echo.
echo ## ?? Structure
echo.
echo ```
echo assets/
echo ??? sounds/     ?? Fichiers audio
echo ??? images/     ??? Screenshots
echo ```
echo.
echo ## ?? Musiques (Optionnel)
echo.
echo Placez vos musiques dans **sounds/** :
echo.
echo - `menu.mp3` - Musique du menu
echo - `game.mp3` - Musique de jeu
echo - `win.mp3` - Musique de victoire
echo.
echo **Recommandations :** Kevin MacLeod (CC BY 4.0)
echo.
echo Voir [../docs/INSTALLATION_MUSIQUE.md]^(../docs/INSTALLATION_MUSIQUE.md^)
echo.
echo ---
echo **[?? Retour]^(../README.md^)**
) > "assets\README.md"

echo ? assets/README.md créé !

echo.
echo ???????????????????????????????????????????????????????????
echo   ???  NETTOYAGE FINAL (Optionnel)
echo ???????????????????????????????????????????????????????????
echo.

set /p cleanup="Supprimer les dossiers originaux vides ? (O/N): "

if /i "%cleanup%"=="O" (
    echo.
    echo ???  Nettoyage des dossiers vides...
    
    REM Supprimer sounds/ s'il est vide
    if exist "sounds" (
        dir /b "sounds" | findstr "^" >nul || rmdir "sounds" 2>nul
        echo ? sounds/ supprimé (vide)
    )
    
    echo ? Nettoyage terminé !
)

echo.
echo ???????????????????????????????????????????????????????????
echo   ? RÉORGANISATION TERMINÉE !
echo ???????????????????????????????????????????????????????????
echo.

echo ?? Structure finale PROPRE:
echo.
echo demineur/
echo ??? src/                 ?? Code C++ + .sln
echo ??? docs/                ?? 5 docs essentiels
echo ?   ??? README.md
echo ?   ??? DEMARRAGE_RAPIDE.md
echo ?   ??? QUALITE_GRAPHIQUE.md
echo ?   ??? INSTALLATION_MUSIQUE.md
echo ?   ??? GITHUB_RELEASE_GUIDE.md
echo ?   ??? CREDITS.txt
echo ??? scripts/             ?? 4 scripts essentiels
echo ?   ??? README.md
echo ?   ??? build_release.bat
echo ?   ??? organiser_projet.bat
echo ?   ??? creer_package.bat
echo ?   ??? publier_github.bat
echo ??? assets/              ?? Ressources
echo ?   ??? sounds/
echo ?   ??? images/
echo ??? .github/             ?? Templates
echo ??? build/               ?? Builds
echo ?   ??? Release/
echo ?   ??? packages/
echo ??? README.md            ?? Principal
echo ??? LICENSE              ?? Licence
echo ??? .gitignore           ?? Git
echo.

echo ???????????????????????????????????????????????????????????
echo.
echo ?? STATISTIQUES:
echo    • Fichiers .md: 6 (au lieu de 15+)
echo    • Scripts .bat: 4 (au lieu de 10+)
echo    • Dossiers: 6 bien organisés
echo.
echo ? PROJET PROPRE ET ORGANISÉ !
echo.
echo ???????????????????????????????????????????????????????????
echo.
echo ?? UTILISATION:
echo.
echo    Compiler:     scripts\build_release.bat
echo    Organiser:    scripts\organiser_projet.bat
echo    Package:      scripts\creer_package.bat
echo    Publier:      scripts\publier_github.bat
echo.
echo    Ouvrir VS:    start src\demineur.sln
echo    Jouer:        build\Release\demineur.exe
echo.
echo ???????????????????????????????????????????????????????????
echo.
echo ?? Prochaines étapes:
echo.
echo 1. Tester la compilation: scripts\build_release.bat
echo 2. Commit les changements: git add . ^&^& git commit -m "?? Nettoyage et réorganisation"
echo 3. Push: git push origin main
echo.
echo ???????????????????????????????????????????????????????????
echo.

REM Supprimer ce script lui-même après utilisation
set /p delete_self="Supprimer ce script ? (O/N): "
if /i "%delete_self%"=="O" (
    echo.
    echo ???  Ce script va s'auto-détruire dans 3 secondes...
    timeout /t 3 >nul
    del "%~f0" 2>nul
    exit
)

pause
