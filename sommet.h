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
#include <vector>

class Sommet
{
    public:
        Sommet(std::string,int,int);
        void ajouterVoisin(Sommet* voisin); // Ajouter un voisin
        void afficherData() const; // Afficher les voisins et les valeur en x et y
        void afficherVoisins() const ; // Afficahge des voisins
        std::string GetId(); // Obtenir l'id
        int GetposY(); // Obtenir la position en y
        int GetposX(); // Obtenir la poistion en x
        std::unordered_map<std::string,std::string> parcoursBFS() const; // Parcours BFS
        std::unordered_map<std::string,std::string> parcoursBFS(std::vector <std::string> , std::vector <Arete*>);
        std::unordered_set<std::string> rechercherCC(std::vector<std::string>,std::vector <Arete*>);
        std::vector<Sommet*> rechercherCC1(std::vector <std::string>,std::vector <Arete*>);
        std::vector<Sommet*> Getvoisins(); // Obtenir les voisins
        void SetComposante(int);
        int GetComposante();
        double GetDis() const;
        double GetDisA() const;
        void SetDis(double);
        void SetDisA(double);
        bool GetMark() const;
        void SetMark(bool);
        void SetPred(std::string);
        ~Sommet(); // Destructeur
    protected:

    private:
        std::vector<Sommet*> m_voisins; // vecteur des voisins
        std::string m_id; // Identifiant du sommet
        int m_x, m_y; // Position en x et y
        int m_composante=0;
        double m_distance;
        std::string m_pred; //predecesseur (pour dijsktra)
        double m_distanceautre;
        bool m_mark;
};

#endif // SOMMET_H_INCLUDED
