# ?? STRUCTURE FINALE DU PROJET

## Dossiers et Scripts d'Organisation

Votre projet est maintenant organisé avec plusieurs scripts d'automatisation ! ??

---

## ?? Structure Complète

```
demineur/
?
??? ?? demineur/                    (Code source)
?   ??? demineur.cpp               ? Code principal
?   ??? demineur.h
?   ??? ...
?
??? ?? x64/Release/                (Build Release)
?   ??? demineur.exe              ? Exécutable compilé
?
??? ?? Release/                    ?? PACKAGE DE DISTRIBUTION
?   ??? demineur.exe              ?? Le jeu
?   ??? Lancer_Demineur.bat       ?? Lanceur
?   ??? README.txt                ?? Instructions
?   ??? VERSION.txt               ?? Informations version
?   ?
?   ??? ?? data/                   ?? Données
?   ?   ??? ?? sounds/             ?? Audio
?   ?       ??? menu.mp3
?   ?       ??? game.mp3
?   ?       ??? win.mp3
?   ?
?   ??? ?? docs/                   ?? Documentation
?       ??? README.md
?       ??? DEMARRAGE_RAPIDE.md
?       ??? QUALITE_GRAPHIQUE.md
?       ??? CREDITS.txt
?
??? ?? organiser_projet.bat       ?? Organiser Release/
??? ?? build_release.bat          ?? Compiler + Organiser
??? ?? creer_package.bat          ?? Créer le .zip
?
??? ?? GUIDE_DISTRIBUTION.md      ?? Guide complet
??? ?? Demineur_HD_v1.0.zip       ?? Package final
```

---

## ?? Scripts Disponibles

### 1. `organiser_projet.bat` ??
**Fonction :** Organiser les fichiers dans Release/

```batch
? Crée la structure de dossiers
? Copie demineur.exe depuis x64/Release/
? Copie la documentation
? Crée README.txt et Lancer_Demineur.bat
```

**Utilisation :**
```batch
Double-clic sur organiser_projet.bat
```

**Quand l'utiliser :**
- Après avoir compilé manuellement
- Pour mettre à jour Release/ après modifications

---

### 2. `build_release.bat` ??
**Fonction :** Tout compiler et organiser automatiquement

```batch
? Compile le projet en mode Release
? Lance organiser_projet.bat
? Crée VERSION.txt
? Vérifie la présence des musiques
```

**Utilisation :**
```batch
Double-clic sur build_release.bat
```

**Quand l'utiliser :**
- Pour un build complet automatique
- Avant de créer le package de distribution

**Prérequis :**
- Visual Studio installé
- Lancer depuis "Developer Command Prompt" OU
- Lancer depuis "x64 Native Tools Command Prompt"

---

### 3. `creer_package.bat` ??
**Fonction :** Créer le fichier .zip de distribution

```batch
? Vérifie que Release/ est prêt
? Crée Demineur_HD_v1.0.zip
? Affiche la taille du fichier
? Propose d'ouvrir l'explorateur
```

**Utilisation :**
```batch
Double-clic sur creer_package.bat
```

**Quand l'utiliser :**
- Après build_release.bat
- Quand Release/ est prêt pour distribution

---

## ?? Workflow Complet (3 Étapes)

### Méthode Rapide (Tout Automatique)

```batch
1. Double-clic sur build_release.bat
   ? Compile + Organise

2. (Optionnel) Ajouter les musiques dans Release\data\sounds\

3. Double-clic sur creer_package.bat
   ? Crée Demineur_HD_v1.0.zip
```

**Résultat :** Fichier .zip prêt à distribuer ! ??

---

### Méthode Manuelle (Plus de Contrôle)

```batch
1. Compiler dans Visual Studio
   - Configuration: Release
   - Plateforme: x64
   - Appuyer sur Ctrl+Shift+B

2. Double-clic sur organiser_projet.bat

3. Ajouter les musiques dans Release\data\sounds\

4. Double-clic sur creer_package.bat
```

---

## ?? Checklist Avant Distribution

### Compilation
- [ ] ? Mode **Release** (pas Debug)
- [ ] ? Plateforme **x64**
- [ ] ? Build réussi sans erreurs

### Organisation
- [ ] ? `Release\demineur.exe` existe
- [ ] ? `Release\data\sounds\` créé
- [ ] ? Documentation copiée dans `docs\`

### Musiques (Optionnel)
- [ ] ?? `menu.mp3` ou `menu.wav`
- [ ] ?? `game.mp3` ou `game.wav`
- [ ] ?? `win.mp3` ou `win.wav`

### Tests
- [ ] ? Lancer `Release\demineur.exe`
- [ ] ? Tester qualité 1-5
- [ ] ? Tester audio (touche M)
- [ ] ? Tester les 4 difficultés

### Package Final
- [ ] ?? `Demineur_HD_v1.0.zip` créé
- [ ] ? Testé sur un autre PC
- [ ] ? README.txt inclus

---

## ?? Ajout des Musiques

### Étape par Étape

```batch
1. Télécharger les musiques de Kevin MacLeod:
   https://incompetech.com/music/

2. Renommer les fichiers:
   - Wallpaper.mp3 ? menu.mp3
   - Sakura Girl.mp3 ? game.mp3
   - Celebration.mp3 ? win.mp3

3. Copier dans:
   Release\data\sounds\

4. Vérifier:
   - Lancer Release\demineur.exe
   - La musique doit jouer automatiquement
```

**Musiques recommandées :**
- **Menu :** Wallpaper, Ascending, Protofunk
- **Jeu :** Sakura Girl, Fluffing a Duck, Merry Go
- **Victoire :** Celebration, Pamgaea, Pixel Peeker Polka

---

## ?? Dépannage

### "MSBuild introuvable"

**Problème :** `build_release.bat` ne trouve pas MSBuild

**Solutions :**

1. **Option 1 :** Lancer depuis Developer Command Prompt
   ```
   - Menu Démarrer
   - Visual Studio 2022
   - Developer Command Prompt for VS 2022
   - cd C:\chemin\vers\demineur
   - build_release.bat
   ```

2. **Option 2 :** Compiler manuellement dans VS
   ```
   - Ouvrir demineur.sln dans Visual Studio
   - Configuration: Release
   - Ctrl+Shift+B
   - Puis: organiser_projet.bat
   ```

---

### "demineur.exe introuvable"

**Problème :** L'exécutable n'est pas dans `x64\Release\`

**Solution :**
```
1. Ouvrir Visual Studio
2. Configuration ? Release
3. Plateforme ? x64
4. Générer ? Régénérer la solution
5. Vérifier x64\Release\demineur.exe
```

---

### "Échec de création du .zip"

**Problème :** PowerShell bloqué

**Solutions :**

1. **Option 1 :** Créer manuellement
   ```
   - Ouvrir Release\
   - Sélectionner tous les fichiers
   - Clic droit ? Envoyer vers ? Dossier compressé
   ```

2. **Option 2 :** Utiliser 7-Zip
   ```
   - Installer 7-Zip
   - Clic droit sur Release\
   - 7-Zip ? Ajouter à l'archive
   - Nom: Demineur_HD_v1.0.7z
   ```

---

## ?? Tailles Estimées

| Configuration | Taille Fichier | Taille .zip |
|---------------|----------------|-------------|
| **Minimal** (exe + docs) | ~500 KB | ~200 KB |
| **+ Musiques MP3** | ~8 MB | ~6 MB |
| **+ Musiques WAV** | ~25 MB | ~20 MB |

---

## ?? Tester le Package

### Test 1 : Local

```batch
1. Extraire Demineur_HD_v1.0.zip dans C:\Temp\Test\
2. Lancer demineur.exe
3. Vérifier:
   - Le jeu démarre
   - Les musiques jouent (si présentes)
   - Touches 1-5 changent la qualité
   - Touche M active/désactive l'audio
```

### Test 2 : Autre PC

```batch
1. Transférer le .zip sur un autre PC Windows
2. Extraire dans un dossier
3. Lancer et tester toutes les fonctionnalités
```

---

## ?? Distribution

### Plateformes Recommandées

1. **itch.io** (Jeux indés)
   - https://itch.io
   - Gratuit, facile, communauté active

2. **GitHub Releases**
   - Pour partage open source
   - Via git tag et release

3. **GameJolt**
   - https://gamejolt.com
   - Communauté gaming

---

## ?? Crédits à Inclure

**OBLIGATOIRE si musiques Kevin MacLeod :**

```
Music by Kevin MacLeod (incompetech.com)
Licensed under Creative Commons: By Attribution 4.0 License
http://creativecommons.org/licenses/by/4.0/
```

**Déjà inclus dans :**
- `Release\docs\CREDITS.txt`
- Boîte "À propos" du jeu

---

## ?? Récapitulatif

### Votre Projet Est Maintenant :

? **Organisé** - Structure professionnelle
? **Automatisé** - Scripts pour tout
? **Documenté** - Guides complets
? **Optimisé** - 60 FPS stable
? **Prêt** - Distribution facile

### Commandes Essentielles

```batch
build_release.bat        # Compiler + Organiser
creer_package.bat        # Créer le .zip
```

### Fichiers Importants

```
Release\demineur.exe     # Le jeu
Release\data\sounds\     # Musiques
Release\docs\            # Documentation
Demineur_HD_v1.0.zip     # Package final
```

---

## ?? Prochaines Étapes

1. ? Compiler avec `build_release.bat`
2. ?? Ajouter musiques dans `Release\data\sounds\`
3. ? Tester `Release\demineur.exe`
4. ?? Créer package avec `creer_package.bat`
5. ?? Distribuer `Demineur_HD_v1.0.zip`

---

**Votre jeu est prêt pour le monde ! ????**

**Bon succès ! ??**

---

*Créé avec ?? • Optimisé pour Performance • Prêt pour Distribution*

© 2024 - Démineur HD v1.0
