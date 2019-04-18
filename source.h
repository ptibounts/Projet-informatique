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
        std::map<std::string, Sommet*> GetMapsom() const;
        std::map<std::string, Arete*> GetMapar() const;
        void dessiner(std::map<std::string, Arete*>, int);
         bool *DecToBin(int n);
        std::vector<std::vector<bool>> compteurbinaire() ;
        std::vector<std::vector<bool>> Connexite(std::vector<std::vector<bool>>);
         int rechercher_afficherToutesCC() const;
         std::vector<std::vector<bool>> RechercheSol();
         std::vector<std::vector<bool>> tailleGraphe(std::vector<std::vector<bool>>, std::vector <std::vector<double>>);

    protected:

    private:
        std::map<std::string, Sommet*> m_sommets;
        std::map<std::string, Arete*> m_aretes;
};
#endif // SOURCE_H_INCLUDED
