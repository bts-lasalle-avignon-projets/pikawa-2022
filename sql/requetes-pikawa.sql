--- Exemples et exercices d'accompagnement : déterminer les requêtes SQL

-- Liste des utilisateurs

SELECT * FROM Utilisateur;

-- Liste des capsules



--- Nombre de capsules



--- Liste des types de boisson

SELECT * FROM TypeBoisson;

|idTypeBoisson|type|
|---|---|
|1|Ristretto|
|2|Espresso|
|3|Lungo|

--- Contenu du magasin

SELECT * FROM Magasin;

SELECT * FROM StockMagasin;

SELECT Magasin.nbRangees,StockMagasin.rangee,Capsule.designation,Capsule.intensite,StockMagasin.quantite,StockMagasin.quantiteMax FROM StockMagasin
INNER JOIN Magasin ON Magasin.idMagasin=StockMagasin.idMagasin
INNER JOIN Capsule ON Capsule.idCapsule=StockMagasin.idCapsule;

|nbRangees|rangee|designation|intensite|quantite|quantiteMax|
|---|---|---|---|---|---|
|8|1|Colombia|6|0|4|
|8|2|Indonesia|8|0|4|
|8|3|Ethiopia|4|0|4|
|8|4|Volluto|4|0|4|
|8|5|Capriccio|5|0|4|
|8|6|Cosi|4|0|4|
|8|7|Scuro|0|0|4|
|8|8|Vanilla Eclair|0|0|4|

