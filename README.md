# ?? DÉMINEUR HD - Version Ultra 1920×1080

![Version](https://img.shields.io/badge/version-1.0-blue)
![License](https://img.shields.io/badge/license-CC%20BY%204.0-green)
![Platform](https://img.shields.io/badge/platform-Windows-blue)

Un jeu de Démineur moderne et immersif avec effets visuels avancés et musique professionnelle !

---

## ? Fonctionnalités

### ?? Gameplay
- ? **4 niveaux de difficulté** : Facile, Moyen, Difficile, Expert
- ? **Système d'aide** : 3 hints par partie pour révéler des cases sûres
- ? **Système de score** : Points bonus pour vitesse et combos
- ? **Multiplicateur de combo** : Jusqu'à x5 !
- ? **Statistiques** : Suivi des parties, victoires, défaites

### ?? Graphismes
- ? **Résolution Full HD** : 1920×1080 natif
- ? **Double buffering** : Aucun scintillement
- ? **Particules animées** : Confettis de victoire, explosions
- ? **Fond animé** : Vagues lumineuses et étoiles scintillantes
- ? **Menu dynamique** : Particules flottantes et effets de lueur
- ? **Interface moderne** : Style Windows 7 avec effets 3D

### ?? Audio
- ? **Musiques de Kevin MacLeod** : Ambiance professionnelle
- ? **Effets sonores** : Chaque action a son propre son
- ? **Contrôle du volume** : Musique et SFX séparés
- ? **Fallback automatique** : Sons système si pas de fichiers custom

### ?? Contrôles
| Touche | Action |
|--------|--------|
| **Clic gauche** | Révéler une case |
| **Clic droit** | Poser/retirer un drapeau |
| **H** | Utiliser une aide (hint) |
| **P** | Pause |
| **R** | Recommencer |
| **M** | Activer/désactiver l'audio |
| **ESC** | Retour au menu |

---

## ?? Installation

### Option 1 : Téléchargement Simple
1. Téléchargez le dernier `.exe` depuis [Releases](#)
2. Lancez `demineur.exe`
3. Jouez ! (les sons système seront utilisés)

### Option 2 : Avec Musique de Kevin MacLeod ??
1. Téléchargez le jeu
2. Créez un dossier `sounds/` à côté de l'exe
3. Suivez le guide **[INSTALLATION_MUSIQUE.md](INSTALLATION_MUSIQUE.md)**
4. Profitez d'une ambiance musicale pro !

---

## ?? Musiques Recommandées (Kevin MacLeod)

Le jeu supporte les musiques de **Kevin MacLeod** (incompetech.com).
Voici les recommandations :

### ?? Pack Starter

| Fichier | Titre | Usage | Lien |
|---------|-------|-------|------|
| `sounds/menu.mp3` | **Wallpaper** | Menu principal | [? Télécharger](https://incompetech.com/music/royalty-free/index.html?isrc=USUAN1100331) |
| `sounds/game.mp3` | **Sakura Girl** | Pendant le jeu | [? Télécharger](https://incompetech.com/music/royalty-free/index.html?isrc=USUAN1100405) |
| `sounds/win.mp3` | **Celebration** | Victoire | [? Télécharger](https://incompetech.com/music/royalty-free/index.html?isrc=USUAN1100262) |

**?? Guide complet :** Consultez [INSTALLATION_MUSIQUE.md](INSTALLATION_MUSIQUE.md) pour plus d'options !

---

## ?? Niveaux de Difficulté

| Niveau | Grille | Mines | Difficulté |
|--------|--------|-------|------------|
| **Facile** | 9×9 | 10 | ? |
| **Moyen** | 16×16 | 40 | ?? |
| **Difficile** | 16×30 | 99 | ??? |
| **Expert** | 24×30 | 180 | ???? |

---

## ??? Compilation (Développeurs)

### Prérequis
- Visual Studio 2019 ou plus récent
- Windows SDK
- C++17 ou supérieur

### Build
```bash
git clone https://github.com/maxlo245/demineur
cd demineur
# Ouvrir demineur.sln dans Visual Studio
# Build > Build Solution (F7)
```

### Structure du projet
```
demineur/
??? demineur.cpp           # Code principal
??? demineur.h             # Header
??? demineur.rc            # Ressources
??? Resource.h             # Définitions ressources
??? sounds/                # Fichiers audio (créer ce dossier)
?   ??? menu.mp3
?   ??? game.mp3
?   ??? win.mp3
??? CREDITS.txt            # Crédits
??? INSTALLATION_MUSIQUE.md # Guide audio
```

---

## ?? Crédits

### ?? Musique
**Music by Kevin MacLeod** (incompetech.com)  
Licensed under Creative Commons: By Attribution 4.0 License  
http://creativecommons.org/licenses/by/4.0/

### ?? Développement
Développé en C++ avec Win32 API  
Double buffering pour performance optimale  
Effets visuels et animations 60 FPS

### ?? Licence
- **Code source** : Tous droits réservés
- **Musiques** : CC BY 4.0 (Kevin MacLeod)

**Voir [CREDITS.txt](CREDITS.txt) pour les détails complets**

---

## ?? Problèmes Connus

### Audio ne fonctionne pas ?
- ? Vérifiez que le dossier `sounds/` existe
- ? Vérifiez les noms de fichiers (sensible à la casse)
- ? Essayez .wav si .mp3 ne fonctionne pas
- ? Appuyez sur **M** pour vérifier l'activation audio

### Performance ?
- ? Désactivez les particules (moins d'effets visuels)
- ? Fermez les applications gourmandes
- ? Le jeu cible 60 FPS en 1920×1080

---

## ?? Contribuer

Les contributions sont les bienvenues !

1. Fork le projet
2. Créez une branche (`git checkout -b feature/AmazingFeature`)
3. Commit (`git commit -m 'Add some AmazingFeature'`)
4. Push (`git push origin feature/AmazingFeature`)
5. Ouvrez une Pull Request

---

## ?? Support

**Questions ? Bugs ?**
- ?? [Ouvrir une issue](https://github.com/maxlo245/demineur/issues)
- ?? Email : [votre-email]
- ?? Discord : [votre-discord]

---

## ?? Remerciements

Un immense merci à :
- **Kevin MacLeod** pour sa musique libre et de qualité
- La communauté **incompetech.com**
- Tous les testeurs et contributeurs

---

## ?? Captures d'écran

### Menu Principal
![Menu](screenshots/menu.png)

### Partie en cours
![Game](screenshots/game.png)

### Victoire !
![Win](screenshots/win.png)

---

**Fait avec ?? et beaucoup de ?**

Amusez-vous bien ! ???

---

© 2024 - Démineur HD
