# Présentation du protocole PIKAWA

Ce document présente rapidement le protocole PIKAWA implémenté dans le simulateur ESP32.

## Types de trames

### Trames d'états

Trame de requête : Application → Cafetière

- Cafetière : `$PIKAWA;ETAT;C;\r\n`
- Magasin : `$PIKAWA;ETAT;M;\r\n`

Trame de réponse : Cafetière → Application

Cafetière : `$PIKAWA;C;EAU;BAC;CASPULE;TASSE;\r\n`

- Le champ EAU aura une valeur entre 0 et 800, 0 il n’a plus d’eau et, 800 si le réservoir est plein. L’application affichera un pourcentage de remplissage.
- Le champ BAC aura la valeur 1 si il est plein sinon ou 0.
- Le champ CAPSULE aura la valeur 1 si elle est présente sinon 0.
- Le champ TASSE aura la valeur 1 si elle est présente sinon 0.

Magasin : `$PIKAWA;M;R1;R2;R3;R4;R5;R6;R7;R8;\r\n`

- Pour chaque rangée, un 1 indique la présence d'au moins une capsule sinon 0.

### Trame de commande

Préparation d’un café : Application → Cafetière

Format : `$PIKAWA;P;NUMERO_RANGE;LONGUEUR;\r\n`

- Le champ NUMERO_RANGE aura une valeur entre 1 et 8 pour sélectionner la capsule dans le magasin.
- Le champ LONGUEUR aura 3 états possible :
    - 1 Ristretto
    - 2 Espresso
    - 3 Lungo

Trame de réponse à la préparation d’un café : Cafetière → Application

Format : `$PIKAWA;P;ETAT;\r\n`

- Le champ ETAT à deux états :
    - 0 le café est prêt (ou repos)
    - 1 le café est en cours de préparation
    - 2 impossible (erreur)

## Remarques

Les trames d'état (`C`, `M` et `P`) peuvent être envoyées directement lors d’un changement d’état.

## Caractéristiques du simulateur

Cette machine possède les caractéristiques suivantes :

- Nombre de colonnes du magasin  : **8**
- Nombre de capsules par colonne : **4**
- Capacité du réservoir d'eau : **20** capsules (en café court)
- Capacité du bac de récupération de capsules :  **5** capsules

Les temps d'un café court est de **3 s** et un long de **6 s**. Pendant la préparation d'un café, on ne peut pas en lancer un autre.

La machine simule toutes les **3 s** :

- la détection d'une tasse (présente ou absente)
- le déclenchement du remplissage en réservoir d'eau si besoin
- un vidage du bac si besoin

L'afficheur OLED signale les informations essentielles.

_Remarque :_ quelques messages supplémentaires seront visibles en plaçant un terminal série (comme `cutecom`).

---
Thierry Vaira 25/04/2021
