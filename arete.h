#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Arete
{
    public:
        ///constructeur qui re�oit en params les donn�es du sommet
        Arete(std::string,double,double);
        void afficherData() const;
        void afficherVoisins() const;
        ~Arete();

    protected:

    private:
        /// Voisinage : liste d'adjacence
        std::vector<const Arete*> m_voisins;

        /// Donn�es sp�cifiques du sommet
        std::string m_id; // Identifiant
        double m_sommet1, m_sommet2; // Position
        double m_cout1, m_cout2;

};


#endif // ARETE_H_INCLUDED
