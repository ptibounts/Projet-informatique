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
        Arete(std::string, double, double, std::string, std::string);
        Arete(std::string, double, double);
        void afficher() const;
        void afficherPoids();
        void afficherVoisins() const;
        float GetCout1();
        float GetCout2();
        std::string GetSommet1();
        std::string GetSommet2();
        bool GetSelect();
        std::string GetId();
        void SetCout1(float x);
        void SetSelect(bool x);
        ~Arete();
        std::string m_id;         // Identifiant
        double m_poids1, m_poids2; // Ponderation


    protected:


    private:

        std::string m_sommet1, m_sommet2; // Position

        bool m_select;
};

#endif // ARETE_H_INCLUDED
