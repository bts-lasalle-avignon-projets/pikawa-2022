--- LDD (langage de définition de données)

--- Supprime les tables

DROP TABLE IF EXISTS Preferences;
DROP TABLE IF EXISTS Statistiques;
DROP TABLE IF EXISTS StockMagasin;
DROP TABLE IF EXISTS Magasin;
DROP TABLE IF EXISTS TypeBoisson;
DROP TABLE IF EXISTS Capsule;
DROP TABLE IF EXISTS Utilisateur;

--- Création des tables

-- Structure de la table Utilisateur

CREATE TABLE IF NOT EXISTS Utilisateur(
  idUtilisateur INTEGER PRIMARY KEY AUTOINCREMENT,
  nom varchar(64) NOT NULL,
  prenom varchar(64) NOT NULL,
  identifiant varchar(255) DEFAULT NULL,
  `password` varchar(255) DEFAULT NULL,
  badge VARCHAR,
  email varchar(64) NOT NULL,
  UNIQUE (identifiant)
);

-- Structure de la table Capsule

CREATE TABLE IF NOT EXISTS Capsule(
  idCapsule INTEGER PRIMARY KEY AUTOINCREMENT,
  marque VARCHAR NOT NULL,
  designation VARCHAR,
  libelle VARCHAR,
  description VARCHAR,
  intensite INTEGER DEFAULT 0,
);

-- Structure de la table TypeBoisson

CREATE TABLE IF NOT EXISTS TypeBoisson(idTypeBoisson INTEGER PRIMARY KEY, type VARCHAR);

-- Structure de la table Magasin

CREATE TABLE IF NOT EXISTS Magasin(
  idMagasin INTEGER PRIMARY KEY,
  nbRangees INTEGER NOT NULL DEFAULT 8
);

-- Structure de la table StockMagasin

CREATE TABLE IF NOT EXISTS StockMagasin(
  idStockMagasin INTEGER PRIMARY KEY AUTOINCREMENT,
  idMagasin INTEGER NOT NULL,
  idCapsule INTEGER NOT NULL,
  quantiteMax INTEGER DEFAULT 4,
  quantite INTEGER DEFAULT 0,
  rangee INTEGER NOT NULL,
  CONSTRAINT Unique_Rangee UNIQUE (idMagasin,rangee),
  CONSTRAINT Stock_fk_1 FOREIGN KEY (idMagasin) REFERENCES Magasin(idMagasin) ON DELETE CASCADE,
  CONSTRAINT Stock_fk_2 FOREIGN KEY (idCapsule) REFERENCES Capsule(idCapsule) ON DELETE CASCADE
);

--- Voir aussi :
--- ON DELETE CASCADE

-- Structure de la table Statistiques

CREATE TABLE IF NOT EXISTS Statistiques(
  idUtilisateur INTEGER PRIMARY KEY NOT NULL,
  nombreCafeDuJour INTEGER DEFAULT 0,
  nombreCafeTotal INTEGER DEFAULT 0,
  nombreBacVide INTEGER DEFAULT 0,
  nombreEauRemplie INTEGER DEFAULT 0,
  dureteeEau INTEGER DEFAULT 0,
  qualiteEau INTEGER DEFAULT 0,
  CONSTRAINT Statistiques_fk_1 FOREIGN KEY (idUtilisateur) REFERENCES Utilisateur(idUtilisateur) ON DELETE CASCADE
);

-- Structure de la table Preferences

CREATE TABLE IF NOT EXISTS Preferences(
  idPreferences INTEGER PRIMARY KEY,
  idUtilisateur INTEGER NOT NULL,
  capsuleActuelle INTEGER NOT NULL,
  typeBoissonActuelle INTEGER NOT NULL,
  CONSTRAINT Preferences_fk_1 FOREIGN KEY (idUtilisateur) REFERENCES Utilisateur(idUtilisateur) ON DELETE CASCADE,
  CONSTRAINT Preferences_fk_2 FOREIGN KEY (capsuleActuelle) REFERENCES Capsule(idCapsule) ON DELETE CASCADE,
  CONSTRAINT Preferences_fk_3 FOREIGN KEY (typeBoissonActuelle) REFERENCES TypeBoisson(idTypeBoisson) ON DELETE CASCADE
);
