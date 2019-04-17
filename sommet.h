#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <set>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "arete.h"

class Sommet
{
    public:
        Sommet(std::string,int,int);
        void ajouterVoisin(Sommet* voisin);
        void afficherData() const;
        void afficher() const;
        void afficherVoisins() const ;
        std::string GetId();
        int GetposY();
        int GetposX();
        std::unordered_map<std::string,std::string> parcoursBFS() const;
        std::unordered_map<std::string,std::string> parcoursBFS(std::vector <std::string > m_vecSommet, std::vector <Arete*> m_aretes1) ;
        std::unordered_set<std::string> rechercherCC() const;
        std::unordered_set<std::string> rechercherCC(std::vector<std::string>,std::vector <Arete*> m_aretes1) ;
        ~Sommet();


    protected:

    private:
        std::vector<Sommet*> m_voisins;
        std::string m_id; // Identifiant
        int m_x, m_y; // Position

};


#endif // SOMMET_H_INCLUDED
