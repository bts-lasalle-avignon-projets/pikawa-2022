#ifndef PROTOCOLE_H
#define PROTOCOLE_H

#define ENTETE           "$PIKAWA"
#define FIN_TRAME        "\r\n"
#define DELIMITEUR       ';'
#define ETAT_CAFETIERE   "C"
#define ETAT_MAGASIN     "M"
#define ETAT_PREPARATION "P"
#define TRAME_ERREUR     "ERREUR"
#define CHAMP_TYPE_TRAME 1

// Code erreur
#define ERREUR_PROTOCOLE      1
#define ERREUR_NB_PARAMETRES  2
#define ERREUR_TRAME_INCONNUE 3
#define ERREUR_TYPE_CAFE      4
#define ERREUR_LONGUEUR_CAFE  5

/**
 * @def TRAME_DEMANDE_ETAT_CAFETIERE
 * @brief Trame de requête permettant d'obtenir l'état de la cafetière
 */
#define TRAME_DEMANDE_ETAT_CAFETIERE "$PIKAWA;ETAT;C;\r\n"

/**
 * @def TRAME_DEMANDE_ETAT_MAGASIN
 * @brief Trame de requête permettant d'obtenir l'état du magasin
 */
#define TRAME_DEMANDE_ETAT_MAGASIN "$PIKAWA;ETAT;M;\r\n"

#define DEBUT_TRAME_PREPARATION "$PIKAWA;P;"

/**
 * @enum TypeTrame
 * @brief Les différents types de trame
 */
enum TypeTrame
{
    Inconnue = -1,
    EtatCafetiere,
    EtatMagasin,
    EtatPreparation,
    ErreurPreparation,
    NbTrames
};

#endif // PROTOCOLE_H
