# Présentation du protocole PIKAWA

Ce document prsente rapidement le protocole PIKAWA implémenté dans le simulateur ESP32.

## Types de trames

### Trames d'états



### Trame de commande



## Caractéristiques du simulateur

Cette machine possède les caractéristiques suivantes :

- Nombre de colonnes du magasin  : **8**
- Nombre de capsules par colonne : **4**
- Capacité du réservoir d'eau : **10** capsules (ne tient pas compte des cafés court ou long !)
- Capacité du bac de récupération de capsules :  **5** capsules

Les temps d'un café court est de **3 s** et un long de **6 s**. Pendant la préparation d'un café, on ne peut pas en lancer un autre.

La machine simule toutes les **3 s** :

- la détection d'une tasse (présente ou absente)
- le déclenchement du remplissage en réservoir d'eau si besoin
- un vidage du bac si besoin

L'afficheur OLED signale les informations essentielles. 

_Remarque :_ quelques messages supplémentaires seront visibles en plaçant un terminal série (comme `cutecom`).

## Exemples



Thierry Vaira 04/04/2021
