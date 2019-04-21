#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED
#include <string>
#include <vector>
#include <map>
#include <set>

class Arete
{
    public:
        Arete();
        ~Arete();
        Arete(std::string, double, double, std::string, std::string); // Constructeur
        void afficher() const; // Afficher les aretes
        void afficherPoids(); // Afficher les poids
        double GetCout1(); // Obtenir le poids 1
        double GetCout2(); // Obtenir le poids 2
        std::string GetSommet1(); // Obtenir le sommet 2
        std::string GetSommet2(); // Obtenir le sommet 2
        bool GetSelect(); // Obtenir le booleen
        std::string GetId(); // Obtenir l'id
        void SetSelect(bool x); // Mettre une valeur de notre booleen de selection
        void setpoids1(double poids1); // Mettre une valeur a notre m_poids1
        void setpoids2(double poids2); // Mettre une valeur a notre m_poids2
        void setid(std::string id); // Mettre une valeur a notre m_id
    protected:

    private:
        std::string m_id;  // Identifiant
        double m_poids1, m_poids2; // Ponderation 1 et 2
        std::string m_sommet1, m_sommet2; // Position sommet 1 et sommet 2
        bool m_select; // Un booleen de selection
};

#endif // ARETE_H_INCLUDED
