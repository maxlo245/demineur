# ?? Démineur HD

<div align="center">

![Version](https://img.shields.io/badge/version-1.0-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Platform](https://img.shields.io/badge/platform-Windows-lightgrey.svg)
![Language](https://img.shields.io/badge/language-C++-orange.svg)

**Un jeu de Démineur moderne et optimisé en Full HD 1920×1080**

[?? Télécharger](https://github.com/maxlo245/demineur/releases) • [?? Documentation](#documentation) • [?? Signaler un bug](https://github.com/maxlo245/demineur/issues)

![Screenshot](docs/screenshot.png)

</div>

---

## ? Fonctionnalités

### ?? Gameplay
- ? **4 niveaux de difficulté** (Facile, Moyen, Difficile, Expert)
- ? **Système d'aides** (3 hints par partie)
- ? **Score et combos** (multiplicateur ×1 à ×5)
- ? **Chronomètre** et statistiques complètes
- ? **Pause et recommencer** à tout moment

### ?? Graphismes
- ? **5 niveaux de qualité** ajustables en temps réel (touches 1-5)
- ? **Menu animé** avec particules et effets
- ? **Fond de jeu animé** (vagues, étoiles, particules)
- ? **60 FPS stables** en Full HD
- ? **Double buffering** (aucun scintillement)
- ? **Interface Windows 7** moderne et élégante

### ?? Audio
- ? **Support musique professionnelle** (Kevin MacLeod - CC BY 4.0)
- ? **10 effets sonores** immersifs
- ? **Fallback automatique** sur sons système
- ? **Toggle audio** facile (touche M)

### ? Performance
- ? **Cache GDI optimisé** (256 brushes + 64 pens)
- ? **GradientFill natif** (accéléré GPU)
- ? **Particules optimisées** (mise à jour partielle)
- ? **50-90 MB RAM** (selon qualité)

---

## ?? Installation

### Option 1 : Télécharger l'exécutable (Recommandé)

1. Téléchargez la dernière version : [Releases](https://github.com/maxlo245/demineur/releases)
2. Extrayez le fichier ZIP
3. Lancez `demineur.exe`
4. Profitez ! ??

### Option 2 : Compiler depuis les sources

#### Prérequis
- **Visual Studio 2019+** avec C++ Desktop Development
- **Windows SDK 10+**
- **Git**

#### Compilation

```bash
# Cloner le dépôt
git clone https://github.com/maxlo245/demineur.git
cd demineur

# Ouvrir dans Visual Studio
start demineur.sln

# Ou compiler en ligne de commande
msbuild demineur.sln /p:Configuration=Release /p:Platform=x64
```

---

## ?? Contrôles

| Touche | Action |
|--------|--------|
| **Clic gauche** | Révéler une case |
| **Clic droit** | Poser/retirer un drapeau |
| **1-5** | Changer la qualité graphique |
| **H** | Utiliser une aide |
| **P** | Pause |
| **R** | Recommencer |
| **M** | Audio On/Off |
| **C** | Effacer le hint |
| **ESC** | Retour au menu |

---

## ?? Qualité Graphique

Appuyez sur les touches **1 à 5** pour changer la qualité en temps réel :

| Niveau | Qualité | Description |
|--------|---------|-------------|
| **1** | Très Faible | Performance maximale (PC anciens) |
| **2** | Faible | Bon compromis (15 particules) |
| **3** | Moyen ? | Recommandé (30 particules) |
| **4** | Élevé | Qualité supérieure (40 particules) |
| **5** | Ultra | Maximum de détails (50 particules) |

---

## ?? Musiques (Optionnel)

Le jeu supporte les musiques de [Kevin MacLeod](https://incompetech.com) (CC BY 4.0) :

```
data/sounds/
??? menu.mp3      (Musique du menu)
??? game.mp3      (Musique de jeu)
??? win.mp3       (Musique de victoire)
```

**Recommandations :**
- **Menu :** Wallpaper, Ascending, Protofunk
- **Jeu :** Sakura Girl, Fluffing a Duck, Merry Go
- **Victoire :** Celebration, Pamgaea, Pixel Peeker Polka

> ?? Si les fichiers ne sont pas présents, le jeu utilise des sons système Windows.

---

## ?? Performance

### Configuration Minimale
- **OS :** Windows 7+
- **RAM :** 2 GB
- **GPU :** Carte graphique avec support DirectDraw
- **Résolution :** 1920×1080

### Configuration Recommandée
- **OS :** Windows 10/11
- **RAM :** 4 GB
- **GPU :** GPU moderne (améliore GradientFill)
- **Résolution :** 1920×1080 (natif)

### Optimisations
- ? **Cache GDI étendu** : 256 brushes + 64 pens réutilisables
- ? **GradientFill natif** : Accéléré GPU (300% plus rapide)
- ? **Particules optimisées** : Mise à jour 1 sur 2 à chaque frame
- ? **Double buffering** : Aucun scintillement

---

## ?? Documentation

- [?? Démarrage Rapide](DEMARRAGE_RAPIDE.md) - Jouer en 3 minutes
- [?? Qualité Graphique](QUALITE_GRAPHIQUE.md) - Guide des 5 niveaux
- [?? Installation Musiques](INSTALLATION_MUSIQUE.md) - Ajouter l'audio
- [? Optimisations](OPTIMISATIONS_PERFORMANCE.md) - Détails techniques
- [?? Distribution](GUIDE_DISTRIBUTION.md) - Créer un package
- [?? Récap Complet](RECAP_COMPLET.md) - Vue d'ensemble

---

## ??? Architecture

```
demineur/
??? demineur/              # Code source C++
?   ??? demineur.cpp      # Code principal (~3000 lignes)
?   ??? demineur.h        # Déclarations
?   ??? Resource.h        # Ressources
?
??? data/                  # Données du jeu
?   ??? sounds/           # Musiques (optionnel)
?
??? docs/                  # Documentation
?   ??? README.md
?   ??? DEMARRAGE_RAPIDE.md
?   ??? ...
?
??? scripts/              # Scripts utilitaires
    ??? build_release.bat
    ??? creer_package.bat
    ??? push_github.bat
```

---

## ??? Technologies

- **Langage :** C++ (ISO/IEC 14882:2017)
- **API :** Win32 API (GDI, GradientFill)
- **Audio :** Windows Multimedia API (PlaySound)
- **Compilateur :** MSVC 2019+
- **Build :** MSBuild

---

## ?? Statistiques

- **Lignes de code :** ~3000+
- **Fichiers source :** 6
- **Fonctions :** 100+
- **Cache GDI :** 256 brushes + 64 pens
- **Performance :** 60 FPS @ 1920×1080
- **RAM :** 50-90 MB (selon qualité)

---

## ?? Roadmap

### Version 1.1 (Future)
- [ ] Mode fenêtré redimensionnable
- [ ] Sauvegarde des scores
- [ ] Thèmes supplémentaires
- [ ] Mode multijoueur local

### Version 2.0 (Future)
- [ ] Éditeur de niveaux
- [ ] Achievements
- [ ] Statistiques détaillées
- [ ] Support multi-langues

---

## ?? Contribuer

Les contributions sont les bienvenues ! ??

1. Fork le projet
2. Créez votre branche (`git checkout -b feature/AmazingFeature`)
3. Commit vos changements (`git commit -m 'Add AmazingFeature'`)
4. Push vers la branche (`git push origin feature/AmazingFeature`)
5. Ouvrez une Pull Request

---

## ?? Licence

Ce projet est sous licence **MIT**. Voir [LICENSE](LICENSE) pour plus de détails.

### Crédits Audio

**Musiques** par [Kevin MacLeod](https://incompetech.com) (CC BY 4.0)
- License: [Creative Commons BY 4.0](http://creativecommons.org/licenses/by/4.0/)

**Titres suggérés :**
- Wallpaper (Menu)
- Sakura Girl (Jeu)
- Celebration (Victoire)

---

## ?? Contact

**Maxlo245** - [@maxlo245](https://github.com/maxlo245)

**Lien du projet :** [https://github.com/maxlo245/demineur](https://github.com/maxlo245/demineur)

---

## ?? Remerciements

- [Kevin MacLeod](https://incompetech.com) pour la musique
- Microsoft pour Win32 API et GDI
- La communauté C++ pour les conseils

---

<div align="center">

**Fait avec ?? et C++**

**© 2024 - Tous droits réservés**

? **N'oubliez pas de mettre une étoile si vous aimez le projet !** ?

</div>
