@echo off
chcp 65001 >nul
echo.
echo ???????????????????????????????????????????????????????????
echo   ?? ORGANISATION DU PROJET - DÉMINEUR HD
echo ???????????????????????????????????????????????????????????
echo.

REM Créer la structure de dossiers
echo ?? Création de la structure de dossiers...
if not exist "Release" mkdir "Release"
if not exist "Release\data" mkdir "Release\data"
if not exist "Release\data\sounds" mkdir "Release\data\sounds"
if not exist "Release\docs" mkdir "Release\docs"

echo ? Dossiers créés !
echo.

REM Copier l'exécutable
echo ?? Copie de l'exécutable...
if exist "x64\Release\demineur.exe" (
    copy "x64\Release\demineur.exe" "Release\" >nul
    echo ? demineur.exe copié !
) else (
    echo ??  ATTENTION: x64\Release\demineur.exe n'existe pas !
    echo    Compilez d'abord en mode Release (Ctrl+Shift+B)
)
echo.

REM Copier les fichiers audio
echo ?? Copie des fichiers audio...
if exist "sounds" (
    xcopy "sounds\*.*" "Release\data\sounds\" /E /Y >nul
    echo ? Fichiers audio copiés !
) else (
    echo ??  Dossier sounds/ non trouvé (normal si pas encore créé)
)
echo.

REM Copier la documentation
echo ?? Copie de la documentation...
copy "README.md" "Release\docs\" >nul 2>&1
copy "DEMARRAGE_RAPIDE.md" "Release\docs\" >nul 2>&1
copy "QUALITE_GRAPHIQUE.md" "Release\docs\" >nul 2>&1
copy "INSTALLATION_MUSIQUE.md" "Release\docs\" >nul 2>&1
copy "CREDITS.txt" "Release\docs\" >nul 2>&1
copy "RECAP_COMPLET.md" "Release\docs\" >nul 2>&1
echo ? Documentation copiée !
echo.

REM Créer un README pour le dossier Release
echo ?? Création du README de distribution...
(
echo # ?? DÉMINEUR HD - Version 1.0
echo.
echo ## ?? Installation
echo.
echo 1. Extraire tous les fichiers dans un dossier
echo 2. ^(Optionnel^) Ajouter les musiques dans `data/sounds/`
echo 3. Double-cliquer sur `demineur.exe`
echo 4. Profitez du jeu !
echo.
echo ## ?? Structure
echo.
echo ```
echo Release/
echo ??? demineur.exe        ^(Le jeu^)
echo ??? data/
echo ?   ??? sounds/        ^(Musiques et sons^)
echo ??? docs/              ^(Documentation^)
echo ```
echo.
echo ## ?? Contrôles
echo.
echo - **Clic gauche** : Révéler une case
echo - **Clic droit** : Poser/retirer un drapeau
echo - **1-5** : Changer la qualité graphique
echo - **M** : Audio On/Off
echo - **H** : Aide
echo - **P** : Pause
echo - **R** : Recommencer
echo - **ESC** : Menu
echo.
echo ## ?? Documentation
echo.
echo Consultez le dossier `docs/` pour la documentation complète.
echo.
echo ---
echo.
echo **Développé avec ?? et C++**
echo.
echo **Musiques** : Kevin MacLeod ^(incompetech.com^) - CC BY 4.0
) > "Release\README.txt"
echo ? README créé !
echo.

REM Créer un fichier de lancement
echo ?? Création du lanceur...
(
echo @echo off
echo cd /d "%%~dp0"
echo start "" "demineur.exe"
) > "Release\Lancer_Demineur.bat"
echo ? Lanceur créé !
echo.

echo ???????????????????????????????????????????????????????????
echo   ? ORGANISATION TERMINÉE !
echo ???????????????????????????????????????????????????????????
echo.
echo ?? Votre jeu est prêt dans le dossier: Release\
echo.
echo ?? Contenu:
echo    • demineur.exe              ^(Le jeu^)
echo    • Lancer_Demineur.bat       ^(Lanceur^)
echo    • data\sounds\              ^(Audio^)
echo    • docs\                     ^(Documentation^)
echo    • README.txt                ^(Instructions^)
echo.
echo ?? Prochaines étapes:
echo    1. Compilez en mode Release ^(Ctrl+Shift+B^)
echo    2. Ajoutez les musiques dans Release\data\sounds\
echo    3. Testez avec Release\demineur.exe
echo    4. Distribuez le dossier Release\ en .zip
echo.
pause
