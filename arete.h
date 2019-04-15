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
        Arete(std::string, double, double, double, double);
        Arete(std::string, double, double);
        void afficher() const;
        void afficherPoids();
        void afficherVoisins() const;
        ~Arete();
        std::string m_id;         // Identifiant
        double m_poids1, m_poids2; // Ponderation

    protected:


    private:
        //std::map<std::string,Sommet*> m_arretes;
        double m_sommet1, m_sommet2; // Position
};

#endif // ARETE_H_INCLUDED
