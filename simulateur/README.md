\mainpage ESP32 + OLED + Bluetooth

\tableofcontents

\section section_tdm Table des matières
- \ref page_README
- \ref page_about
- \ref page_licence

\section section_infos Informations

\author Thierry Vaira <<tvaira@free.fr>>
\date 2022
\version 0.1
\see https://github.com/btssn-lasalle-84/pikawa-2022/


\page page_README README

[TOC]

# Simulateur pikawa {#projet}

## Présentation du protocole PIKAWA implanté dans le simulateur ESP32 {#presentation}

Ce document présente rapidement le fonctionnement du simulateur PIKAWA ainsi que le protocole IKAWA implémenté. Le protocole complet est disponible dans Google Drive. Actuellement, la version du protocole est la **0.1** (04 avril 2022).

## Configuration du simulateur

Ce programme est destiné à un ESP32 équipé d'un écran OLED. Par défaut, la configuration de l'écran OLED est la suivante (fichier `lib/pikawa/pikawa.h`) :

```c
#define ADRESSE_I2C_OLED 0x3c
#define I2C_SDA_OLED     5
#define I2C_SCL_OLED     4
```

Autres réglages possibles :

- Nombre de colonnes du magasin  :

```c
#define NB_COLONNES       8
```

- Nombre de capsules par colonne :

```c
#define TAILLE_COLONNE    4
```

- Capacité du réservoir d'eau (ne tient pas compte des cafés court ou long) :

```c
#define CAPACITE_EAU      20 // capsules en café court
```

- Capacité du bac de récupération de capsules :

```c
#define CAPACITE_BAC      5 // capsules
```

- Les durées pour préparer un café court (le double pour un long) :

```c
#define TEMPO_CMD_CAFE    6000 // 6 s pour un café court et donc le double pour un long
```

- Périodicité de la simulation (toutes les **3 secondes**) :

```c
#define TEMPO_SIMULATION        3000 // en ms
#define SIMULATION_TASSE        (TEMPO_SIMULATION) // en ms
#define SIMULATION_VIDAGE       (TEMPO_SIMULATION*2) // en ms
#define SIMULATION_REMPLISSAGE  (TEMPO_SIMULATION*2) // en ms
```

Le remplissage d'eau et le vidage du bac à capsules se fera au plus tard après **6 secondes**. L'absence de tasse est aléatoire et ne dure que **3 secondes**.

## Limites actuelles



## platform.ini

```ini
[env:lolin32]
platform = espressif32
board = lolin32
board_build.partitions = huge_app.csv
framework = arduino
lib_deps =
  thingpulse/ESP8266 and ESP32 OLED driver for SSD1306 displays @ ^4.2.0
upload_port = /dev/ttyUSB0
upload_speed = 115200
monitor_port = /dev/ttyUSB0
monitor_speed = 115200
```

## Caractéristiques du simulateur

Cette machine possède par défaut les caractéristiques suivantes :

- Nombre de colonnes du magasin  : **8**
- Nombre de capsules par colonne : **4**
- Capacité du réservoir d'eau : **10** capsules (ne tient pas compte des cafés court ou long !)
- Capacité du bac de récupération de capsules :  **5** capsules

Les temps d'un café court est de **6 s** et un long de **12 s**. Pendant la préparation d'un café, on ne peut pas en lancer un autre.

La machine simule toutes les **3 s** :

- la détection d'une tasse (présente ou absente)
- le déclenchement du remplissage en réservoir d'eau si besoin
- un vidage du bac si besoin

L'afficheur OLED signale les informations essentielles :

- Ligne 1 : l'année (`pikawa 2021`) et la version (`v1`) suivi du nombre total de cafés, du nombre total de vidage du bac, du nombre total de remplissage d'eau.
- Ligne 3 : l'état de la préparation d'un café
- Ligne 4 : l'état des bacs d'eau et capsules 
- Ligne 5 : la présence/absence de tasse et l'état du magasin
- Ligne 6 : un compteur de trames reçues ou un affichage de la dernière trame reçue

_Remarque :_ quelques messages supplémentaires seront visibles en plaçant un terminal série (comme `cutecom`).

## Types de trames de requête

Elles sont envoyées lors d'un **changement d'état** ou en **interrogeant** la machine avec des trames de requêtes.

## Types de trames de commande

Elles sont envoyées par l'application :

- Test de communication
- Lancer la préparation d’un café
- Réinitialiser les paramètres machine

### Trame de préparation d'un café

Pour lancer la **préparation d'un café**, il faut envoyer la trame de commande comprenant la longueur et le type de boisson.

Le simulateur répond avec une trame d'acquittement indiquant si une préparation est possible ou impossible.

### Trame de réinitialisation

Pour réinitialiser les paramètres "usine" :

- nombre total de cafés effectués par la machine (0 = non / 1 = oui)
- nombre total de bacs vidés (0 = non / 1 = oui)
- nombre total de remplissage d’eau (0 = non / 1 = oui)
- dureté de l’eau (en option)
- qualité de l’eau (en option)

Les différents paramètres (nombre total de cafés effectués par la machine, nombre total de bacs vidés, nombre total de remplissage d’eau) seront remis à 0.

Le simulateur renvoie une trame d'acquittement.

## Exemples



## Informations {#informations}

\author Thierry Vaira <<tvaira@free.fr>>
\date 2022
\version 0.1
\see https://github.com/btssn-lasalle-84/pikawa-2022/

\page page_about A propos

\author Thierry Vaira <<tvaira@free.fr>>
\date 2022
\version 0.1
\see https://github.com/btssn-lasalle-84/pikawa-2022/

\page page_licence Licence GPL

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
