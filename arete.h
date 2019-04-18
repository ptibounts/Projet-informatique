#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED
#include <string>
#include <vector>
#include <map>
#include <set>


class Arete
{
    public:
        Arete(std::string, double, double, std::string, std::string);
        Arete(std::string, double, double);
        void afficher() const;
        void afficherPoids() const;
        void afficherVoisins() const;
        float GetCout1() const;
        float GetCout2() const;
        std::string GetSommet1()const;
        std::string GetSommet2() const;
        bool GetSelect()const;
        std::string GetId() const;
        void SetCout1(float x);
        void SetSelect(bool x);
        void setpoids1(double poids1);
        void setpoids2(double poids2);
        void setid(std::string id);
        ~Arete();

    protected:


    private:
        std::string m_id;         // Identifiant
        double m_poids1, m_poids2; // Ponderation
        std::string m_sommet1, m_sommet2; // Position
        bool m_select;

};

#endif // ARETE_H_INCLUDED
