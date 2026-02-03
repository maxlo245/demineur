# ?? GUIDE GITHUB RELEASE - DÉMINEUR HD

## ?? Créer une Release Professionnelle sur GitHub

Ce guide vous explique comment créer une release complète et professionnelle pour votre jeu.

---

## ?? Processus Complet (5 Étapes)

### **Étape 1 : Préparer le Package**

```bash
1. Compiler en Release
   - Ouvrir Visual Studio
   - Configuration: Release
   - Plateforme: x64
   - Ctrl+Shift+B

2. Organiser les fichiers
   - Double-clic sur build_release.bat

3. (Optionnel) Ajouter les musiques
   - Dans Release\data\sounds\

4. Créer le .zip
   - Double-clic sur creer_package.bat
   - Résultat: Demineur_HD_v1.0.zip
```

---

### **Étape 2 : Préparer GitHub**

#### Vérifier le README

```bash
1. Copier README_GITHUB.md vers README.md
   copy README_GITHUB.md README.md

2. Ajouter une capture d'écran
   - Créer docs\screenshot.png
   - Capture du jeu en action
```

#### Créer LICENSE (MIT)

Créer `LICENSE` avec :

```
MIT License

Copyright (c) 2024 maxlo245

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---

### **Étape 3 : Commit et Tag**

#### Option A : Script Automatique (Recommandé)

```bash
Double-clic sur github_package.bat

Choisir: [2] Commit complet + Tag version
Version: 1.0.0
Message: Release v1.0.0 - Version initiale
```

#### Option B : Manuel

```bash
# Ajouter tous les fichiers
git add .

# Commit
git commit -m "Release v1.0.0 - Version initiale"

# Créer le tag
git tag -a v1.0.0 -m "Version 1.0.0"

# Push commit
git push origin main

# Push tag
git push origin v1.0.0
```

---

### **Étape 4 : Créer la Release sur GitHub**

1. **Aller sur GitHub**
   ```
   https://github.com/maxlo245/demineur
   ```

2. **Aller dans Releases**
   - Cliquer sur "Releases" (à droite)
   - Ou aller sur : https://github.com/maxlo245/demineur/releases

3. **Draft a new release**
   - Cliquer sur "Draft a new release"

4. **Remplir les informations :**

   **Tag :** `v1.0.0`  
   **Target :** `main`  
   **Release title :** `?? Démineur HD v1.0.0 - Version Initiale`

   **Description (Markdown) :**

   ```markdown
   ## ?? Démineur HD - Version 1.0.0

   Première version publique du Démineur HD !

   ### ? Fonctionnalités

   #### ?? Gameplay
   - 4 niveaux de difficulté (Facile, Moyen, Difficile, Expert)
   - Système d'aides (3 hints par partie)
   - Score et combos (multiplicateur ×1 à ×5)
   - Chronomètre et statistiques

   #### ?? Graphismes
   - 5 niveaux de qualité ajustables (touches 1-5)
   - Menu animé avec particules
   - Fond de jeu animé (vagues, étoiles)
   - 60 FPS stables en Full HD 1920×1080

   #### ?? Audio
   - Support musique professionnelle (Kevin MacLeod)
   - 10 effets sonores immersifs
   - Fallback automatique sur sons système

   #### ? Performance
   - Cache GDI optimisé (256 brushes + 64 pens)
   - GradientFill natif (accéléré GPU)
   - 50-90 MB RAM (selon qualité)
   - 60 FPS @ 1920×1080

   ### ?? Installation

   1. Téléchargez `Demineur_HD_v1.0.0.zip`
   2. Extrayez dans un dossier
   3. Lancez `demineur.exe`
   4. Profitez ! ??

   ### ?? Contrôles

   | Touche | Action |
   |--------|--------|
   | Clic gauche | Révéler une case |
   | Clic droit | Poser/retirer un drapeau |
   | 1-5 | Changer la qualité graphique |
   | H | Utiliser une aide |
   | P | Pause |
   | R | Recommencer |
   | M | Audio On/Off |
   | ESC | Retour au menu |

   ### ?? Musiques (Optionnel)

   Ajoutez vos propres musiques dans `data\sounds\` :
   - `menu.mp3` - Musique du menu
   - `game.mp3` - Musique de jeu
   - `win.mp3` - Musique de victoire

   **Recommandations :** Kevin MacLeod (CC BY 4.0)
   - Menu: Wallpaper, Ascending
   - Jeu: Sakura Girl, Fluffing a Duck
   - Victoire: Celebration, Pamgaea

   ### ?? Configuration

   **Minimale :**
   - Windows 7+
   - 2 GB RAM
   - Résolution 1920×1080

   **Recommandée :**
   - Windows 10/11
   - 4 GB RAM
   - GPU moderne

   ### ?? Bugs Connus

   Aucun pour le moment ! ??

   ### ?? Crédits

   **Musiques :** Kevin MacLeod (incompetech.com) - CC BY 4.0  
   **Développé avec ?? par maxlo245**

   ---

   **Bon jeu ! ????**
   ```

5. **Uploader le fichier :**
   - Cliquer sur "Attach binaries"
   - Sélectionner `Demineur_HD_v1.0.0.zip`
   - Attendre l'upload

6. **Options supplémentaires :**
   - ? **This is a pre-release** (si c'est une beta)
   - ? **Set as the latest release** (recommandé)

7. **Publier :**
   - Cliquer sur "Publish release"

---

### **Étape 5 : Promouvoir la Release**

#### Sur GitHub

1. **Mettre à jour le README principal**
   - Ajouter un badge de version
   - Lien vers la release

2. **Créer un Wiki (optionnel)**
   - Guide d'installation détaillé
   - FAQ
   - Changelog

#### Sur Reddit

```
Title: [Release] Démineur HD v1.0 - Jeu de Démineur moderne en C++

Body:
Salut /r/cpp !

Je viens de publier Démineur HD, un jeu de démineur moderne
développé en C++ avec Win32 API.

? Fonctionnalités:
- 60 FPS en Full HD (1920×1080)
- 5 niveaux de qualité ajustables
- Cache GDI optimisé pour performance maximale
- Audio professionnel (Kevin MacLeod)

?? GitHub: https://github.com/maxlo245/demineur
?? Download: https://github.com/maxlo245/demineur/releases

Feedback bienvenu ! ??
```

#### Sur Itch.io

```
1. Créer un compte sur itch.io
2. Create New Project
3. Uploader Demineur_HD_v1.0.0.zip
4. Prix: Free ou Pay What You Want
5. Publish !
```

---

## ?? Checklist Finale

### Avant la Release

- [ ] ? Compilé en mode **Release**
- [ ] ? Testé sur plusieurs PC
- [ ] ? README.md à jour
- [ ] ? LICENSE créé
- [ ] ? Capture d'écran ajoutée
- [ ] ? .gitignore vérifié
- [ ] ? Package .zip créé

### Pendant la Release

- [ ] ? Tag créé (v1.0.0)
- [ ] ? Commit poussé
- [ ] ? Tag poussé
- [ ] ? Release créée sur GitHub
- [ ] ? .zip uploadé
- [ ] ? Description complète

### Après la Release

- [ ] ? Lien fonctionnel testé
- [ ] ? Téléchargement testé
- [ ] ? Annoncé sur réseaux sociaux
- [ ] ? Issues activées

---

## ?? Badges GitHub

Ajoutez ces badges dans votre README :

```markdown
![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Platform](https://img.shields.io/badge/platform-Windows-lightgrey.svg)
![Language](https://img.shields.io/badge/language-C++-orange.svg)
![Downloads](https://img.shields.io/github/downloads/maxlo245/demineur/total)
![Stars](https://img.shields.io/github/stars/maxlo245/demineur)
```

---

## ?? Analytics

### Suivre les Téléchargements

GitHub fournit automatiquement :
- Nombre de téléchargements par release
- Nombre de visiteurs
- Traffic sources

**Voir :** `Insights` > `Traffic`

---

## ?? Mise à Jour Future

### Pour la v1.1

```bash
1. Faire les modifications
2. Tester
3. Mettre à jour la version dans le code
4. Créer un nouveau tag: v1.1.0
5. Créer une nouvelle release
6. Ajouter un CHANGELOG.md
```

### CHANGELOG.md

```markdown
# Changelog

## [1.1.0] - 2024-XX-XX

### Ajouté
- Mode fenêtré
- Sauvegarde des scores

### Modifié
- Performance améliorée (+10% FPS)

### Corrigé
- Bug de crash au niveau Expert

## [1.0.0] - 2024-XX-XX

### Initial Release
- Première version publique
```

---

## ?? Tips Professionnels

### 1. Screenshots de Qualité

```
- Résolution native (1920×1080)
- Moment clé du jeu (victoire, menu)
- Compressé (PNG optimisé)
- Nom: screenshot.png, gameplay.png
```

### 2. GIF Animé

```
- Utiliser ScreenToGif
- 5-10 secondes
- Compressé (<5 MB)
- Montre les fonctionnalités clés
```

### 3. Description Marketing

```
? Court et impactant
? Bullets points
? Emojis (avec modération)
? Call to action
? Trop technique
? Trop long
```

### 4. SEO GitHub

```
Utilisez ces mots-clés dans:
- Titre du projet
- Description
- README
- Tags

Mots-clés:
minesweeper, game, c++, win32, gdi,
hd, 1080p, performance, optimized
```

---

## ?? Support Utilisateur

### Issues Template

Créer `.github/ISSUE_TEMPLATE/bug_report.md` :

```markdown
---
name: Bug Report
about: Signaler un bug
title: '[BUG] '
labels: bug
---

**Description du bug**
Description claire du problème.

**Comment reproduire**
1. Aller à '...'
2. Cliquer sur '...'
3. Voir l'erreur

**Comportement attendu**
Ce qui devrait se passer.

**Screenshots**
Si applicable.

**Environnement:**
 - OS: [Windows 10/11]
 - Version: [1.0.0]
 - Qualité graphique: [1-5]

**Informations supplémentaires**
Tout autre détail.
```

---

## ?? Félicitations !

Votre jeu est maintenant **publié sur GitHub** de manière professionnelle ! ??

**Étapes suivantes :**

1. ? Promouvoir sur réseaux sociaux
2. ? Répondre aux issues
3. ? Collecter feedback
4. ? Planifier v1.1

**Bon succès ! ????**

---

**Créé avec ?? • Guide complet • Prêt pour le succès**

© 2024 - Démineur HD
