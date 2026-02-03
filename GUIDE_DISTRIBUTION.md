# ?? GUIDE DE DISTRIBUTION - DÉMINEUR HD

## Structure Professionnelle du Projet

Votre jeu est maintenant organisé de manière professionnelle pour une distribution facile ! ??

---

## ?? Nouvelle Structure

```
demineur/                    (Projet de développement)
??? demineur/               (Code source)
?   ??? demineur.cpp       ? Code principal
?   ??? demineur.h
?   ??? Resource.h
?   ??? ...
?
??? x64/Release/           (Compilation Release)
?   ??? demineur.exe      ? Exécutable compilé
?
??? Release/               ?? DOSSIER DE DISTRIBUTION
    ??? demineur.exe       ?? Le jeu (à distribuer)
    ??? Lancer_Demineur.bat  ?? Lanceur
    ?
    ??? data/              ?? Données du jeu
    ?   ??? sounds/        ?? Musiques et effets
    ?       ??? menu.mp3
    ?       ??? game.mp3
    ?       ??? win.mp3
    ?       ??? ... (autres sons)
    ?
    ??? docs/              ?? Documentation
    ?   ??? README.md
    ?   ??? DEMARRAGE_RAPIDE.md
    ?   ??? QUALITE_GRAPHIQUE.md
    ?   ??? INSTALLATION_MUSIQUE.md
    ?   ??? CREDITS.txt
    ?
    ??? README.txt         ?? Instructions de base
```

---

## ?? Processus de Distribution (3 Étapes)

### Étape 1 : Compiler en Release

```batch
1. Dans Visual Studio
2. Configuration : Release
3. Plateforme : x64
4. Appuyer sur Ctrl+Shift+B (ou F7)
```

### Étape 2 : Organiser les Fichiers

```batch
1. Double-cliquer sur organiser_projet.bat
2. Tout est automatiquement copié dans Release/
```

**Ce qui est fait automatiquement :**
- ? Copie de `demineur.exe`
- ? Création de la structure `data/sounds/`
- ? Copie de la documentation
- ? Création du README.txt
- ? Création du lanceur

### Étape 3 : Ajouter les Musiques

```batch
1. Télécharger les 3 musiques de Kevin MacLeod
2. Les placer dans Release\data\sounds\
   - menu.mp3 (ou menu.wav)
   - game.mp3 (ou game.wav)
   - win.mp3 (ou win.wav)
```

---

## ?? Créer le Package de Distribution

### Option 1 : ZIP Simple

```batch
1. Aller dans le dossier Release\
2. Sélectionner tous les fichiers
3. Clic droit > Envoyer vers > Dossier compressé
4. Renommer : Demineur_HD_v1.0.zip
```

### Option 2 : Avec 7-Zip (Recommandé)

```batch
1. Clic droit sur Release\
2. 7-Zip > Ajouter à l'archive
3. Nom : Demineur_HD_v1.0.7z
4. Compression : Maximum
```

**Taille estimée :**
- Sans musiques : ~200 KB
- Avec musiques MP3 : ~5-10 MB
- Avec musiques WAV : ~20-30 MB

---

## ?? Gestion des Musiques

### Chemins Supportés (Par Ordre de Priorité)

Le jeu cherche les fichiers dans cet ordre :

1. **`data\sounds\`** ? Priorité (pour distribution)
2. **`sounds\`** ? Fallback (pour développement)
3. **Sons système Windows** ? Si aucun fichier trouvé

### Formats Audio Supportés

- ? **MP3** (Recommandé - petit, qualité)
- ? **WAV** (Plus gros, compatible)

### Fichiers Audio Attendus

```
data\sounds\
??? menu.mp3         (Musique du menu)
??? game.mp3         (Musique de jeu)
??? win.mp3          (Musique de victoire)
??? click.wav        (Optionnel - clic)
??? reveal.wav       (Optionnel - révéler)
??? flag.wav         (Optionnel - drapeau)
??? explosion.wav    (Optionnel - explosion)
??? hint.wav         (Optionnel - aide)
??? combo.wav        (Optionnel - combo)
```

**Note :** Si les fichiers optionnels n'existent pas, le jeu utilise Beep() ou sons système.

---

## ?? Créer un Installeur (Optionnel)

### Avec Inno Setup (Gratuit)

1. **Télécharger** Inno Setup : https://jrsoftware.org/isinfo.php
2. **Créer** un script `.iss`
3. **Compiler** pour créer `Setup_Demineur_HD.exe`

**Script basique :**

```ini
[Setup]
AppName=Démineur HD
AppVersion=1.0
DefaultDirName={pf}\Demineur HD
DefaultGroupName=Démineur HD
OutputDir=Output
OutputBaseFilename=Setup_Demineur_HD

[Files]
Source: "Release\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs

[Icons]
Name: "{group}\Démineur HD"; Filename: "{app}\demineur.exe"
Name: "{commondesktop}\Démineur HD"; Filename: "{app}\demineur.exe"
```

---

## ?? Distribution en Ligne

### Sur itch.io (Recommandé pour Jeux Indés)

```
1. Créer un compte sur itch.io
2. Create New Project
3. Upload Demineur_HD_v1.0.zip
4. Prix : Free ou Pay What You Want
5. Publish !
```

### Sur GitHub Releases

```bash
1. git tag v1.0.0
2. git push origin v1.0.0
3. Aller sur GitHub > Releases > Create Release
4. Attacher Demineur_HD_v1.0.zip
5. Publish release
```

### Sur GameJolt

```
1. Créer un compte sur GameJolt
2. Dashboard > Add Game
3. Upload le .zip
4. Ajouter screenshots, description
5. Publish
```

---

## ?? Checklist de Distribution

### Avant de Distribuer

- [ ] ? Compilé en mode **Release** (pas Debug)
- [ ] ? Testé l'exécutable dans `Release\`
- [ ] ? Vérifié que les musiques se chargent
- [ ] ? Testé les 5 niveaux de qualité (1-5)
- [ ] ? Testé les 4 niveaux de difficulté
- [ ] ? Vérifié l'audio (touche M)
- [ ] ? Documentation à jour dans `docs\`
- [ ] ? CREDITS.txt inclus
- [ ] ? README.txt clair et complet

### Fichiers Obligatoires

- [ ] ? `demineur.exe`
- [ ] ? `data\` (dossier vide minimum)
- [ ] ? `README.txt`
- [ ] ? `docs\CREDITS.txt`

### Fichiers Optionnels

- [ ] ?? Musiques MP3/WAV dans `data\sounds\`
- [ ] ?? Documentation complète dans `docs\`
- [ ] ?? `Lancer_Demineur.bat`
- [ ] ??? Screenshots (pour itch.io, etc.)

---

## ?? Tester le Package

### Test Local

```batch
1. Extraire Demineur_HD_v1.0.zip dans un nouveau dossier
2. Double-cliquer sur demineur.exe
3. Vérifier que tout fonctionne
4. Tester avec/sans musiques
```

### Test sur un Autre PC

```
1. Transférer le .zip sur un autre PC Windows
2. Extraire et lancer
3. Vérifier les sons système (si pas de musiques)
4. Tester toutes les touches (1-5, M, H, etc.)
```

---

## ?? Taille du Package

| Configuration | Taille |
|---------------|--------|
| **Minimal** (exe + docs) | ~500 KB |
| **Standard** (+ musiques MP3) | ~5-10 MB |
| **Complet** (+ musiques WAV) | ~20-30 MB |
| **Avec source** | +2-3 MB |

---

## ?? Dépannage Distribution

### "L'application n'a pas pu démarrer"

**Cause :** Manque Visual C++ Redistributable

**Solution :**
```
Option 1: Recompiler en "Static" (/MT)
Option 2: Inclure vcredist_x64.exe
Option 3: Indiquer le téléchargement dans README
```

### "Pas de son"

**Cause :** Fichiers audio manquants

**Solution :**
- Le jeu utilise des sons système si pas de fichiers
- Indiquer où télécharger les musiques
- Voir INSTALLATION_MUSIQUE.md

### "La fenêtre ne s'affiche pas"

**Cause :** Résolution 1920×1080 trop grande

**Solution :**
- Modifier WINDOW_WIDTH/HEIGHT si besoin
- Ajouter un mode fenêtré

---

## ?? Licence et Crédits

### Musiques Kevin MacLeod

**IMPORTANT :** Si vous distribuez avec les musiques :

```
Inclure OBLIGATOIREMENT dans CREDITS.txt :

Music by Kevin MacLeod (incompetech.com)
Licensed under Creative Commons: By Attribution 4.0
http://creativecommons.org/licenses/by/4.0/

Tracks used:
• Wallpaper (Menu)
• Sakura Girl (Game)  
• Celebration (Win)
```

### Votre Code

Vous pouvez choisir votre licence :
- **MIT** (Open Source, très permissive)
- **GPL** (Open Source, copyleft)
- **Propriétaire** (Tous droits réservés)

---

## ?? Commandes Rapides

### Compiler Release
```batch
msbuild demineur.sln /p:Configuration=Release /p:Platform=x64
```

### Organiser
```batch
organiser_projet.bat
```

### Créer ZIP
```batch
cd Release
7z a -tzip ..\Demineur_HD_v1.0.zip *
```

### Tout en 1
```batch
msbuild demineur.sln /p:Configuration=Release /p:Platform=x64
organiser_projet.bat
cd Release
7z a -tzip ..\Demineur_HD_v1.0.zip *
```

---

## ?? Roadmap Distribution

### Version 1.0 (Actuelle)
- ? Jeu complet et fonctionnel
- ? 5 niveaux de qualité
- ? Audio professionnel
- ? Documentation complète

### Version 1.1 (Future)
- [ ] Mode fenêtré en option
- [ ] Sauvegarde des scores
- [ ] Classement en ligne
- [ ] Thèmes supplémentaires

### Version 2.0 (Future)
- [ ] Éditeur de niveaux
- [ ] Mode multijoueur
- [ ] Achievements
- [ ] Statistiques détaillées

---

## ?? Support Utilisateur

### FAQ à Inclure

```
Q: Le jeu ne se lance pas
A: Téléchargez Visual C++ Redistributable 2019+

Q: Pas de musique
A: Les musiques sont optionnelles. Le jeu utilise des sons système.

Q: Lag/Saccades
A: Appuyez sur 1 ou 2 pour réduire la qualité graphique

Q: Comment changer la qualité ?
A: Appuyez sur les touches 1-5 (1=Minimal, 5=Ultra)
```

---

## ?? Félicitations !

Votre jeu est maintenant **prêt pour la distribution** ! ??

**Étapes finales :**

1. ? Compiler en Release
2. ? Lancer `organiser_projet.bat`
3. ? Ajouter les musiques dans `Release\data\sounds\`
4. ? Créer le .zip
5. ? Tester sur un autre PC
6. ? Distribuer !

**Bon succès avec votre jeu ! ????**

---

**Fait avec ?? • Optimisé pour Distribution • Prêt à Partager**

© 2024 - Démineur HD - Version 1.0
