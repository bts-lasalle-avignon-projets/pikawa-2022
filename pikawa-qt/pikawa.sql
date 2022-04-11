BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "Preferences" (
	"idPreferences"	INTEGER,
	"idUtilisateur"	INTEGER NOT NULL,
	"capsuleActuelle"	INTEGER NOT NULL,
	"typeBoissonActuelle"	INTEGER NOT NULL,
	CONSTRAINT "Preferences_fk_3" FOREIGN KEY("typeBoissonActuelle") REFERENCES "TypeBoisson"("idTypeBoisson") ON DELETE CASCADE,
	CONSTRAINT "Preferences_fk_2" FOREIGN KEY("capsuleActuelle") REFERENCES "Capsule"("idCapsule") ON DELETE CASCADE,
	CONSTRAINT "Preferences_fk_1" FOREIGN KEY("idUtilisateur") REFERENCES "Utilisateur"("idUtilisateur") ON DELETE CASCADE,
	PRIMARY KEY("idPreferences")
);
CREATE TABLE IF NOT EXISTS "Statistiques" (
	"idUtilisateur"	INTEGER NOT NULL,
	"nombreCafeDuJour"	INTEGER DEFAULT 0,
	"nombreCafeTotal"	INTEGER DEFAULT 0,
	"nombreBacVide"	INTEGER DEFAULT 0,
	"nombreEauRemplie"	INTEGER DEFAULT 0,
	"dureteeEau"	INTEGER DEFAULT 0,
	"qualiteEau"	INTEGER DEFAULT 0,
	CONSTRAINT "Statistiques_fk_1" FOREIGN KEY("idUtilisateur") REFERENCES "Utilisateur"("idUtilisateur") ON DELETE CASCADE,
	PRIMARY KEY("idUtilisateur")
);
CREATE TABLE IF NOT EXISTS "StockMagasin" (
	"idStockMagasin"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"idMagasin"	INTEGER NOT NULL,
	"idCapsule"	INTEGER NOT NULL,
	"quantiteMax"	INTEGER DEFAULT 4,
	"quantite"	INTEGER DEFAULT 0,
	"rangee"	INTEGER NOT NULL,
	CONSTRAINT "Stock_fk_2" FOREIGN KEY("idCapsule") REFERENCES "Capsule"("idCapsule") ON DELETE CASCADE,
	CONSTRAINT "Stock_fk_1" FOREIGN KEY("idMagasin") REFERENCES "Magasin"("idMagasin") ON DELETE CASCADE,
	CONSTRAINT "Unique_Rangee" UNIQUE("idMagasin","rangee")
);
CREATE TABLE IF NOT EXISTS "Magasin" (
	"idMagasin"	INTEGER,
	"nbRangees"	INTEGER NOT NULL DEFAULT 8,
	PRIMARY KEY("idMagasin")
);
CREATE TABLE IF NOT EXISTS "TypeBoisson" (
	"idTypeBoisson"	INTEGER,
	"type"	VARCHAR,
	PRIMARY KEY("idTypeBoisson")
);
CREATE TABLE IF NOT EXISTS "Capsule" (
	"idCapsule"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"marque"	VARCHAR NOT NULL,
	"designation"	VARCHAR,
	"description"	VARCHAR,
	"intensite"	INTEGER DEFAULT 0
);
CREATE TABLE IF NOT EXISTS "Utilisateur" (
	"idUtilisateur"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"nom"	varchar(64) NOT NULL,
	"prenom"	varchar(64) NOT NULL,
	"identifiant"	varchar(255) DEFAULT NULL UNIQUE,
	"password"	varchar(255) DEFAULT NULL,
	"badge"	VARCHAR,
	"email"	varchar(64) NOT NULL
);
INSERT INTO "Preferences" VALUES (1,2,1,1);
INSERT INTO "Preferences" VALUES (2,2,4,3);
INSERT INTO "Statistiques" VALUES (1,0,0,0,0,0,0);
INSERT INTO "Statistiques" VALUES (2,0,0,0,0,0,0);
INSERT INTO "StockMagasin" VALUES (1,1,1,4,0,1);
INSERT INTO "StockMagasin" VALUES (2,1,2,4,0,2);
INSERT INTO "StockMagasin" VALUES (3,1,3,4,0,3);
INSERT INTO "StockMagasin" VALUES (4,1,4,4,0,4);
INSERT INTO "StockMagasin" VALUES (5,1,5,4,0,5);
INSERT INTO "StockMagasin" VALUES (6,1,6,4,0,6);
INSERT INTO "StockMagasin" VALUES (7,1,7,4,0,7);
INSERT INTO "StockMagasin" VALUES (8,1,8,4,0,8);
INSERT INTO "Magasin" VALUES (1,8);
INSERT INTO "TypeBoisson" VALUES (1,'Ristretto');
INSERT INTO "TypeBoisson" VALUES (2,'Espresso');
INSERT INTO "TypeBoisson" VALUES (3,'Lungo');
INSERT INTO "Capsule" VALUES (1,'Nespresso','Colombia','Arabica cueilli en récolte tardive, unique comme la cordillère des Andes',6);
INSERT INTO "Capsule" VALUES (2,'Nespresso','Indonesia','Arabica, né des pluies de Sumatra, labellisé Fairtrade et certifié biologique',8);
INSERT INTO "Capsule" VALUES (3,'Nespresso','Ethiopia','Arabica dépulpé par voie sèche sous le soleil bienfaiteur',4);
INSERT INTO "Capsule" VALUES (4,'Nespresso','Volluto','Doux et léger',4);
INSERT INTO "Capsule" VALUES (5,'Nespresso','Capriccio','Riche et exclusif',5);
INSERT INTO "Capsule" VALUES (6,'Nespresso','Cosi','Équilibré et délicatement torréfié',4);
INSERT INTO "Capsule" VALUES (7,'Nespresso','Scuro','Idéal pour les amateurs de recettes intenses et équilibrées à base de lait',0);
INSERT INTO "Capsule" VALUES (8,'Nespresso','Vanilla Eclair','Saveur éclair à la vanille',0);
INSERT INTO "Utilisateur" VALUES (1,'VAIRA','Thierry','tvaira',NULL,NULL,'tvaira@free.fr');
INSERT INTO "Utilisateur" VALUES (2,'BEAUMONT','Jérôme','jbeaumont',NULL,NULL,'beaumont@lasalle84.org');
COMMIT;
