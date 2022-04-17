#ifndef PREPARATION_H
#define PREPARATION_H

/**
 * @file preparation.h
 *
 * @brief Déclaration de la classe Preparation
 * @author
 * @version 0.2
 *
 */

#include <QObject>
#include <QVector>
#include <QString>
#include <QStringList>

class BaseDeDonnees;

/**
 * @class Preparation
 * @brief
 * @details
 */



#define NIVEAU_EAU_MAX 800
#define NIVEAU_EAU_MIN_CAFE 30

class Cafetiere;

class Preparation : public QObject
{
    Q_OBJECT
  private:
    BaseDeDonnees* baseDeDonneesPikawa; //!< instance d'un objet BaseDeDonnees
    Cafetiere*     cafetiere;     //!< instance d'un objet Cafetiere

    QVector<QString> nomCapsules;
    QVector<QString> nomLongueurs;
    bool             capsulePresente;
    bool             bacPlein;
    bool             tassePresente;
    int              niveauEau;

    void chargerNomCapsules();
    void chargerLongeurBoissons();

  public:
    Preparation(QObject* parent = nullptr);
    ~Preparation();

    QStringList getNomCapsules() const;
    QStringList getNomLongueurs() const;
    bool getCapsulePresente() const;
    bool getBacPlein() const;
    bool getTassePresente() const;
    int getNiveauEau() const;

    void setCapsulePresente(bool& capsulePresente);
    void setBacPlein(bool& bacPlein);
    void setTassePresente(bool& tassePresente);
    void setNiveauEau(int& niveauEau);

    bool estPreparationPrete();

};

#endif // PREPARATION_H
