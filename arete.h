#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED
#include <string>
#include <vector>
#include <map>
#include <set>
#include "sommet.h"


class Arete
{
    public:
        ///constructeur qui reçoit en params les données du sommet
        Arete(std::string, double, double);
        void afficherData() const;
        void afficherVoisins() const;
        ~Arete();

    protected:

    private:
        /// Voisinage : liste d'adjacence
        std::map<std::string,Sommet*> m_arretes;

        /// Données spécifiques du sommet
        std::string m_id; // Identifiant
        double m_sommet1, m_sommet2; // Position
        double m_cout1, m_cout2; // Ponderation

};

#endif // ARETE_H_INCLUDED
