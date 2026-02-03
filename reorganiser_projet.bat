@echo off
chcp 65001 >nul
echo.
echo ???????????????????????????????????????????????????????????
echo   ???  RÉORGANISATION DU PROJET - DÉMINEUR HD
echo ???????????????????????????????????????????????????????????
echo.

echo ??  ATTENTION: Ce script va réorganiser TOUS les fichiers du projet
echo             dans une structure professionnelle.
echo.
echo ?? Nouvelle structure:
echo    demineur/
echo    ??? src/                  (Code source)
echo    ??? docs/                 (Documentation)
echo    ??? scripts/              (Scripts .bat)
echo    ??? assets/               (Ressources)
echo    ??? .github/              (Templates GitHub)
echo    ??? build/                (Builds et releases)
echo.
set /p confirm="Continuer la réorganisation ? (O/N): "

if /i not "%confirm%"=="O" (
    echo ? Annulé.
    pause
    exit /b 0
)

echo.
echo ???????????????????????????????????????????????????????????
echo   ?? CRÉATION DE LA STRUCTURE
echo ???????????????????????????????????????????????????????????
echo.

REM Créer les dossiers principaux
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
echo   ?? DÉPLACEMENT DES FICHIERS
echo ???????????????????????????????????????????????????????????
echo.

REM ========================================
REM DOCUMENTATION (docs/)
REM ========================================
echo ?? Déplacement de la documentation...

if exist "README_GITHUB.md" move /Y "README_GITHUB.md" "docs\" >nul
if exist "DEMARRAGE_RAPIDE.md" move /Y "DEMARRAGE_RAPIDE.md" "docs\" >nul
if exist "QUALITE_GRAPHIQUE.md" move /Y "QUALITE_GRAPHIQUE.md" "docs\" >nul
if exist "INSTALLATION_MUSIQUE.md" move /Y "INSTALLATION_MUSIQUE.md" "docs\" >nul
if exist "MUSIQUES_ALTERNATIVES.md" move /Y "MUSIQUES_ALTERNATIVES.md" "docs\" >nul
if exist "OPTIMISATIONS_PERFORMANCE.md" move /Y "OPTIMISATIONS_PERFORMANCE.md" "docs\" >nul
if exist "SYSTEME_AUDIO_RESUME.md" move /Y "SYSTEME_AUDIO_RESUME.md" "docs\" >nul
if exist "GUIDE_DISTRIBUTION.md" move /Y "GUIDE_DISTRIBUTION.md" "docs\" >nul
if exist "ORGANISATION_PROJET.md" move /Y "ORGANISATION_PROJET.md" "docs\" >nul
if exist "PROJET_COMPLET.md" move /Y "PROJET_COMPLET.md" "docs\" >nul
if exist "RECAP_COMPLET.md" move /Y "RECAP_COMPLET.md" "docs\" >nul
if exist "GITHUB_RELEASE_GUIDE.md" move /Y "GITHUB_RELEASE_GUIDE.md" "docs\" >nul
if exist "PACKAGE_GITHUB_COMPLET.md" move /Y "PACKAGE_GITHUB_COMPLET.md" "docs\" >nul
if exist "RECAP_GITHUB.txt" move /Y "RECAP_GITHUB.txt" "docs\" >nul
if exist "CREDITS.txt" move /Y "CREDITS.txt" "docs\" >nul

echo ? Documentation déplacée !

REM ========================================
REM SCRIPTS (scripts/)
REM ========================================
echo ?? Déplacement des scripts...

if exist "organiser_projet.bat" move /Y "organiser_projet.bat" "scripts\" >nul
if exist "build_release.bat" move /Y "build_release.bat" "scripts\" >nul
if exist "creer_package.bat" move /Y "creer_package.bat" "scripts\" >nul
if exist "push_github.bat" move /Y "push_github.bat" "scripts\" >nul
if exist "github_package.bat" move /Y "github_package.bat" "scripts\" >nul
if exist "publier_github.bat" move /Y "publier_github.bat" "scripts\" >nul
if exist "verifier_audio.bat" move /Y "verifier_audio.bat" "scripts\" >nul
if exist "telecharger_musiques.bat" move /Y "telecharger_musiques.bat" "scripts\" >nul

echo ? Scripts déplacés !

REM ========================================
REM CODE SOURCE (src/)
REM ========================================
echo ?? Copie du code source...

REM Copier le dossier demineur entier vers src/
if exist "demineur" (
    xcopy "demineur\*.*" "src\" /E /Y /Q >nul
    echo ? Code source copié dans src/
) else (
    echo ??  Dossier demineur/ introuvable
)

REM ========================================
REM ASSETS (assets/)
REM ========================================
echo ?? Déplacement des assets...

REM Déplacer sounds/README.md vers assets/sounds/
if exist "sounds\README.md" (
    if not exist "assets\sounds" mkdir "assets\sounds"
    move /Y "sounds\README.md" "assets\sounds\" >nul
    echo ? sounds/README.md déplacé
)

REM Si le dossier sounds contient des fichiers audio, les déplacer aussi
if exist "sounds\*.mp3" move /Y "sounds\*.mp3" "assets\sounds\" >nul 2>&1
if exist "sounds\*.wav" move /Y "sounds\*.wav" "assets\sounds\" >nul 2>&1

echo ? Assets déplacés !

REM ========================================
REM BUILDS (build/)
REM ========================================
echo ?? Organisation des builds...

REM Copier Release/ vers build/Release/
if exist "Release" (
    xcopy "Release\*.*" "build\Release\" /E /Y /Q >nul
    echo ? Release/ copié dans build/Release/
)

REM Déplacer les packages .zip vers build/packages/
if exist "*.zip" (
    move /Y "*.zip" "build\packages\" >nul
    echo ? Packages .zip déplacés dans build/packages/
)

echo.
echo ???????????????????????????????????????????????????????????
echo   ?? MISE À JOUR DES CHEMINS
echo ???????????????????????????????????????????????????????????
echo.

REM Créer un README.md racine qui pointe vers la doc
(
echo # ?? Démineur HD
echo.
echo ^> **Jeu de Démineur moderne en Full HD 1920×1080 avec C++ et Win32 API**
echo.
echo ## ?? Structure du Projet
echo.
echo ```
echo demineur/
echo ??? src/                    ?? Code source C++
echo ??? docs/                   ?? Documentation complète
echo ??? scripts/                ?? Scripts d'automatisation
echo ??? assets/                 ?? Ressources ^(sons, images^)
echo ??? .github/                ?? Templates GitHub
echo ??? build/                  ?? Builds et releases
echo ```
echo.
echo ## ?? Démarrage Rapide
echo.
echo ### Compiler le Projet
echo.
echo ```bash
echo # Ouvrir dans Visual Studio
echo start src\demineur.sln
echo.
echo # Ou compiler en ligne de commande
echo cd scripts
echo build_release.bat
echo ```
echo.
echo ### Jouer
echo.
echo ```bash
echo # Lancer le jeu compilé
echo build\Release\demineur.exe
echo.
echo # Ou utiliser le script
echo cd scripts
echo organiser_projet.bat
echo ```
echo.
echo ## ?? Documentation
echo.
echo Toute la documentation est dans le dossier **`docs/`** :
echo.
echo - **[Démarrage Rapide]^(docs/DEMARRAGE_RAPIDE.md^)** - Jouer en 3 minutes
echo - **[Qualité Graphique]^(docs/QUALITE_GRAPHIQUE.md^)** - Guide des 5 niveaux
echo - **[Installation Musiques]^(docs/INSTALLATION_MUSIQUE.md^)** - Ajouter l'audio
echo - **[Distribution]^(docs/GUIDE_DISTRIBUTION.md^)** - Créer un package
echo - **[Performance]^(docs/OPTIMISATIONS_PERFORMANCE.md^)** - Optimisations techniques
echo - **[GitHub Release]^(docs/GITHUB_RELEASE_GUIDE.md^)** - Publier sur GitHub
echo.
echo ## ?? Fonctionnalités
echo.
echo ### Gameplay
echo - ? 4 niveaux de difficulté
echo - ? Système d'aides ^(3 hints^)
echo - ? Score et combos ^(×1 à ×5^)
echo - ? Chronomètre
echo.
echo ### Graphismes
echo - ? 5 niveaux de qualité ^(touches 1-5^)
echo - ? 60 FPS @ 1920×1080
echo - ? Animations et particules
echo - ? Menu animé
echo.
echo ### Audio
echo - ? Support Kevin MacLeod ^(CC BY 4.0^)
echo - ? 10 effets sonores
echo - ? Fallback automatique
echo.
echo ## ?? Contrôles
echo.
echo ^| Touche ^| Action ^|
echo ^|--------^|--------^|
echo ^| Clic gauche ^| Révéler ^|
echo ^| Clic droit ^| Drapeau ^|
echo ^| 1-5 ^| Qualité graphique ^|
echo ^| H ^| Aide ^|
echo ^| M ^| Audio On/Off ^|
echo ^| ESC ^| Menu ^|
echo.
echo ## ?? Scripts Disponibles
echo.
echo Dans le dossier **`scripts/`** :
echo.
echo - **`build_release.bat`** - Compiler en Release
echo - **`organiser_projet.bat`** - Organiser build/Release/
echo - **`creer_package.bat`** - Créer le .zip
echo - **`publier_github.bat`** - Publication GitHub complète
echo - **`github_package.bat`** - Gestion Git avancée
echo.
echo ## ?? Statistiques
echo.
echo - **Lignes de code :** ~3000+
echo - **Performance :** 60 FPS @ 1920×1080
echo - **RAM :** 50-90 MB
echo - **Qualités :** 5 niveaux
echo.
echo ## ?? Licence
echo.
echo Ce projet est sous licence **MIT**. Voir [LICENSE]^(LICENSE^).
echo.
echo **Musiques :** Kevin MacLeod ^(CC BY 4.0^) - Voir [docs/CREDITS.txt]^(docs/CREDITS.txt^)
echo.
echo ## ?? Liens
echo.
echo - **GitHub :** https://github.com/maxlo245/demineur
echo - **Releases :** https://github.com/maxlo245/demineur/releases
echo - **Issues :** https://github.com/maxlo245/demineur/issues
echo.
echo ---
echo.
echo **Développé avec ?? et C++**
) > "README.md"

echo ? README.md racine créé !

REM Créer un fichier d'index dans docs/
(
echo # ?? Documentation - Démineur HD
echo.
echo ## ?? Index de la Documentation
echo.
echo ### ?? Pour Commencer
echo - **[Démarrage Rapide]^(DEMARRAGE_RAPIDE.md^)** - Jouer en 3 minutes
echo - **[Qualité Graphique]^(QUALITE_GRAPHIQUE.md^)** - Guide des 5 niveaux
echo - **[Installation Musiques]^(INSTALLATION_MUSIQUE.md^)** - Ajouter l'audio
echo.
echo ### ?? Distribution
echo - **[Guide Distribution]^(GUIDE_DISTRIBUTION.md^)** - Créer un package
echo - **[Organisation Projet]^(ORGANISATION_PROJET.md^)** - Structure du projet
echo - **[GitHub Release]^(GITHUB_RELEASE_GUIDE.md^)** - Publier sur GitHub
echo - **[Package GitHub]^(PACKAGE_GITHUB_COMPLET.md^)** - Package complet
echo.
echo ### ? Technique
echo - **[Optimisations Performance]^(OPTIMISATIONS_PERFORMANCE.md^)** - Détails techniques
echo - **[Système Audio]^(SYSTEME_AUDIO_RESUME.md^)** - Architecture audio
echo - **[Musiques Alternatives]^(MUSIQUES_ALTERNATIVES.md^)** - 20+ musiques
echo.
echo ### ?? Récapitulatifs
echo - **[Projet Complet]^(PROJET_COMPLET.md^)** - Vue d'ensemble complète
echo - **[Récap Complet]^(RECAP_COMPLET.md^)** - Résumé fonctionnalités
echo - **[Récap GitHub]^(RECAP_GITHUB.txt^)** - Guide GitHub
echo.
echo ### ?? Autres
echo - **[Crédits]^(CREDITS.txt^)** - Attributions
echo.
echo ---
echo.
echo **Navigation :** [?? Retour à la racine]^(../README.md^)
) > "docs\INDEX.md"

echo ? docs/INDEX.md créé !

REM Créer un README dans scripts/
(
echo # ?? Scripts - Démineur HD
echo.
echo ## ?? Scripts Disponibles
echo.
echo ### ?? Compilation
echo - **`build_release.bat`** - Compile le projet en mode Release
echo.
echo ### ?? Organisation
echo - **`organiser_projet.bat`** - Organise les fichiers dans build/Release/
echo - **`creer_package.bat`** - Crée le fichier .zip de distribution
echo.
echo ### ?? GitHub
echo - **`publier_github.bat`** - Publication complète automatique
echo - **`github_package.bat`** - Gestion commit/tag avancée
echo - **`push_github.bat`** - Push simple vers GitHub
echo.
echo ### ?? Audio
echo - **`verifier_audio.bat`** - Vérifie les fichiers audio
echo - **`telecharger_musiques.bat`** - Guide de téléchargement
echo.
echo ## ?? Utilisation
echo.
echo ### Build Complet
echo ```bash
echo build_release.bat
echo ```
echo.
echo ### Publication GitHub
echo ```bash
echo publier_github.bat
echo ```
echo.
echo ---
echo.
echo **Navigation :** [?? Retour à la racine]^(../README.md^) ^| [?? Documentation]^(../docs/INDEX.md^)
) > "scripts\README.md"

echo ? scripts/README.md créé !

REM Créer un README dans assets/
(
echo # ?? Assets - Démineur HD
echo.
echo ## ?? Structure
echo.
echo ```
echo assets/
echo ??? sounds/         ?? Fichiers audio
echo ??? images/         ??? Images et screenshots
echo ```
echo.
echo ## ?? Sons
echo.
echo ### Musiques ^(Optionnel^)
echo.
echo Placez vos musiques dans **`sounds/`** :
echo.
echo - `menu.mp3` ou `menu.wav` - Musique du menu
echo - `game.mp3` ou `game.wav` - Musique de jeu
echo - `win.mp3` ou `win.wav` - Musique de victoire
echo.
echo **Recommandations :** Kevin MacLeod ^(CC BY 4.0^)
echo - Menu: Wallpaper, Ascending
echo - Jeu: Sakura Girl, Fluffing a Duck
echo - Victoire: Celebration, Pamgaea
echo.
echo ### Effets Sonores ^(Optionnel^)
echo.
echo - `click.wav` - Clic
echo - `reveal.wav` - Révéler
echo - `flag.wav` - Drapeau
echo - `explosion.wav` - Explosion
echo - `hint.wav` - Aide
echo - `combo.wav` - Combo
echo.
echo ^> ?? Si les fichiers ne sont pas présents, le jeu utilise des sons système Windows.
echo.
echo ## ??? Images
echo.
echo Placez vos screenshots dans **`images/`** :
echo.
echo - `screenshot.png` - Screenshot principal
echo - `gameplay.png` - Gameplay
echo - `menu.png` - Menu
echo.
echo ---
echo.
echo **Navigation :** [?? Retour à la racine]^(../README.md^) ^| [?? Documentation]^(../docs/INDEX.md^)
) > "assets\README.md"

echo ? assets/README.md créé !

echo.
echo ???????????????????????????????????????????????????????????
echo   ???  NETTOYAGE ^(Optionnel^)
echo ???????????????????????????????????????????????????????????
echo.

set /p cleanup="Supprimer les dossiers originaux vides ? (O/N): "

if /i "%cleanup%"=="O" (
    echo.
    echo ???  Nettoyage...
    
    REM Supprimer le dossier sounds s'il est vide
    if exist "sounds" (
        dir /b "sounds" | findstr "^" >nul || rmdir "sounds" 2>nul
    )
    
    REM Ne PAS supprimer le dossier demineur/ car il est utilisé par Visual Studio
    REM Ne PAS supprimer Release/ car il peut contenir des builds actifs
    
    echo ? Nettoyage terminé !
)

echo.
echo ???????????????????????????????????????????????????????????
echo   ? RÉORGANISATION TERMINÉE !
echo ???????????????????????????????????????????????????????????
echo.

echo ?? Nouvelle structure:
echo.
echo demineur/
echo ??? src/                    ?? Code source C++
echo ?   ??? demineur.cpp
echo ?   ??? demineur.h
echo ?   ??? demineur.sln
echo ?
echo ??? docs/                   ?? Documentation ^(14+ fichiers^)
echo ?   ??? INDEX.md
echo ?   ??? DEMARRAGE_RAPIDE.md
echo ?   ??? ...
echo ?
echo ??? scripts/                ?? Scripts ^(8 scripts^)
echo ?   ??? README.md
echo ?   ??? build_release.bat
echo ?   ??? ...
echo ?
echo ??? assets/                 ?? Ressources
echo ?   ??? README.md
echo ?   ??? sounds/            ?? Audio
echo ?   ??? images/            ??? Screenshots
echo ?
echo ??? .github/                ?? Templates GitHub
echo ?   ??? ISSUE_TEMPLATE/
echo ?
echo ??? build/                  ?? Builds
echo ?   ??? Release/           ?? Build Release
echo ?   ??? packages/          ?? .zip
echo ?
echo ??? README.md               ?? README principal
echo ??? LICENSE                 ?? Licence MIT
echo ??? .gitignore              ?? Git ignore
echo.

echo ???????????????????????????????????????????????????????????
echo.
echo ?? IMPORTANT:
echo.
echo 1. ??  Le dossier demineur/ original est CONSERVÉ
echo       ^(nécessaire pour Visual Studio^)
echo.
echo 2. ?? Les scripts doivent maintenant être lancés depuis scripts/
echo       Ex: scripts\build_release.bat
echo.
echo 3. ?? Le .sln principal est maintenant dans src/
echo       Ouvrir: src\demineur.sln
echo.
echo 4. ?? Les builds sont dans build/Release/
echo.
echo 5. ?? Toute la doc est dans docs/
echo.
echo ???????????????????????????????????????????????????????????
echo.
echo ?? Prochaines étapes:
echo.
echo 1. Mettre à jour .gitignore pour la nouvelle structure
echo 2. Commit les changements
echo 3. Push vers GitHub
echo.
pause
