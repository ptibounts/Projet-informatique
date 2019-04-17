#ifndef SOURCE_H_INCLUDED
#define SOURCE_H_INCLUDED
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include "sommet.h"
#include "arete.h"
#include "svgfile.h"

int choix();

class graphe
{
    public:
        void sommet(std::string);
        graphe();
        ~graphe();
        void afficher() const ;
        void afficherP() const;
        void ponderation(std::string);
        std::map<std::string, Arete*> Kruskal ( int v );
        std::map<std::string, Sommet*> GetMapsom();
        std::map<std::string, Arete*> GetMapar();
        void dessiner(std::map<std::string, Arete*>);
        std::vector<std::vector<bool>> Connexite(std::vector<std::vector<bool>>);
         int rechercher_afficherToutesCC() const;

    protected:

    private:
        std::map<std::string, Sommet*> m_sommets;
        std::map<std::string, Arete*> m_aretes;
};
#endif // SOURCE_H_INCLUDED
