# ⌨️ ShortDeck : Votre Mini-Clavier Modulaire Arduino Personnalisable

	
[![Arduino](https://img.shields.io/badge/Arduino-CC0000?style=for-the-badge&logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![GitHub Stars](https://img.shields.io/github/stars/DJMartinez-b2g/ShortDeck?style=social)](https://github.com/DJMartinez-b2g/ShortDeck)
[![GitHub Forks](https://img.shields.io/github/forks/DJMartinez-b2g/ShortDeck?style=social)](https://github.com/DJMartinez-b2g/ShortDeck)
[![License](https://img.shields.io/github/license/DJMartinez-b2g/ShortDeck)](LICENSE)



  <img src="https://img.shields.io/github/v/release/DJMartinez-b2g/ShortDeck" alt="GitHub release"/>
  <img src="https://img.shields.io/github/actions/workflow/status/OctoPrint/OctoPrint/build.yml?branch=master" alt="Build status"/>


</p>

**Créez votre propre mini-clavier entièrement personnalisable avec ShortDeck !** Basé sur une carte Arduino, ce projet open-source vous permet de concevoir un périphérique d'entrée compact et polyvalent, adapté à vos besoins spécifiques. Que vous soyez un gamer, un créateur de contenu, ou simplement à la recherche d'un moyen d'optimiser votre flux de travail, ShortDeck est fait pour vous.

## ✨ Fonctionnalités Clés

* **Entièrement Modulable :** Adaptez le nombre de touches et leur disposition selon vos préférences.
* **Quatre Profils Configurables :** Basculez facilement entre quatre configurations de commandes distinctes pour différentes applications ou tâches.
* **Huit Touches Programmables :** Chaque touche peut être assignée à une variété de fonctions.
* **Actions Multiples par Touche :** Gérez des actions différentes en fonction de la durée de la pression (pression courte et longue).
* **Intégration HID :** Exploite la librairie `HID-Project` pour émuler un clavier et des contrôles multimédia standard.
* **Indication Visuelle des Profils :** Quatre LEDs dédiées signalent clairement le profil actif.
* **Open-Source :** Le code est entièrement accessible et modifiable pour une personnalisation poussée.
* **Basé sur Arduino :** Facile à prototyper, programmer et étendre avec l'écosystème Arduino.

## 🛠️ Ce Que Vous Pouvez Faire

Grâce au code actuel, votre ShortDeck est capable de :

* **Contrôler la lecture multimédia** (muet, précédent, suivant, volume haut/bas) sur le **Profil 1** avec une pression courte.
* **Exécuter des raccourcis clavier** (sélection de mots) sur le **Profil 1** avec une pression courte.
* **Lancer des applications** (mélangeur audio, Spotify) sur le **Profil 1** avec une **pression longue**.
* **Définir des actions personnalisées** pour chaque profil et chaque bouton. Le code actuel fournit des exemples simples pour les **Profils 2, 3 et 4** (affichage de texte via le port série pour le premier bouton).

## ⚙️ Prérequis

Pour reproduire et modifier ce projet, vous aurez besoin de :

* Une carte **Arduino** (par exemple, Arduino Leonardo ou Micro, nécessaires pour l'émulation HID).
* **Huit boutons poussoirs**.
* **Quatre LEDs**.
* Des **résistances** pour les boutons (généralement 10kΩ pour le pull-up) et les LEDs (valeur à adapter selon vos LEDs).
* Du **câblage** pour connecter les composants à l'Arduino.
* L'**IDE Arduino** installé sur votre ordinateur.
* La librairie **`HID-Project`** installée dans votre IDE Arduino (disponible via le gestionnaire de librairies).

## 🚀 Installation et Utilisation

1.  **Clonez ce repository** sur votre ordinateur :
    ```bash
    git clone [https://github.com/DJMartinez-b2g/ShortDeck.git](https://github.com/DJMartinez-b2g/ShortDeck.git)
    cd ShortDeck
    ```

2.  **Ouvrez le fichier `ShortDeck.ino`** avec l'IDE Arduino.

3.  **Vérifiez que la librairie `HID-Project` est installée.** Si ce n'est pas le cas, allez dans `Croquis` -> `Inclure une librairie` -> `Gérer les librairies...` et recherchez `HID-Project` pour l'installer.

4.  **Connectez les composants** à votre carte Arduino en suivant le schéma de câblage (à ajouter ici ou dans un fichier séparé). Assurez-vous de connecter les boutons aux broches `2` à `9`, le bouton de profil à `A0`, et les LEDs aux broches `10`, `16`, `14`, `15`.

5.  **Téléchargez le code** sur votre carte Arduino via l'IDE.

6.  **Utilisez votre ShortDeck !**
    * Appuyez sur le bouton connecté à `A0` pour changer de profil. La LED correspondante s'allumera.
    * Appuyez brièvement sur les autres boutons pour exécuter les commandes configurées pour le profil actif (pression courte).
    * Maintenez certains boutons enfoncés pendant plus de 1.5 seconde sur le Profil 1 pour déclencher les actions de pression longue.

## ✍️ Personnalisation

Le véritable potentiel de ShortDeck réside dans sa personnalisation. Pour modifier les actions des boutons :

1.  **Ouvrez le fichier `ShortDeck.ino`**.
2.  **Modifiez la fonction `envoyerCommande(int profil, int bouton)`** pour définir les actions des pressions courtes pour chaque profil et chaque bouton. Vous pouvez utiliser les fonctions de la librairie `Keyboard` (pour simuler des frappes de clavier) et `Consumer` (pour les commandes multimédia).
3.  **Modifiez la fonction `envoyerCommandeLonguePression(int profil, int bouton)`** pour définir les actions des pressions longues.
4.  **N'hésitez pas à ajouter de nouveaux profils, plus de boutons (en adaptant le câblage et les définitions de broches), ou d'autres fonctionnalités selon vos besoins !**

## 🖼️ Schéma de Câblage (À Ajouter)
