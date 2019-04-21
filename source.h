#ifndef SOURCE_H_INCLUDED
#define SOURCE_H_INCLUDED
#include <string>
#include <iostream>
#include <fstream>
#include<unordered_map>
#include <map>
#include "sommet.h"
#include "arete.h"
#include "svgfile.h"

int choix();
std::vector<Arete*> Tri(std::unordered_map<std::string, Arete*> m_aretes,int v);

class graphe
{
    public:
        graphe();
        ~graphe();
        void afficher() const; //Affichage
        void afficherP() const; // Affichage
        void sommet(std::string); // Chargement 1
        void ponderation(std::string); // Chargement 2
        std::map<std::string, Arete*> Kruskal (int v); // Algorithme de Kruskal
        std::map<std::string, Sommet*> GetMapsom(); //Obtenir une copie de la map sommet
        std::map<std::string, Arete*> GetMapar(); //Obtenir une copie de la map arete
        void dessiner(std::map<std::string, Arete*>, int); // Dessiner mon Kruskal
        bool *DecToBin(int n); // Convertisseur decimal en binaire
        std::vector<std::vector<bool>> compteurbinaire(); // Compter en binaire
        std::vector<std::vector<bool>> Connexite(std::vector<std::vector<bool>>); // Avoir la conexite et savoir nos graphes le sont
        std::vector<std::vector<bool>> RechercheSol(); // Solution intermediare de la fonrtiere de Pareto
        std::vector<std::vector<bool>> SolutionFinale(std::vector<std::vector<bool>> solution); // Solution finale de la frontiere de Pareto
        void dessinFrontierePrometo(std::vector<std::vector<bool>>, std::vector<std::vector<bool>>); // Dessiner ma frontiere de Pareto
        std::vector <double> Dijkstra(std::string Sdepart, std::string Sarrivee, int nbcout); // Calcul du Dijsktra
        void DijkstraToutSommet(int choix); // Dijsktra
        std::vector<std::vector<double>> RechercheSolDijskra(int choix);
        std::vector<std::vector<bool>> compteurbinaireDijskra();
        double Dijkstra(std::string, std::string , int,  std::vector<Arete*>);
        std::vector<double> DijkstraToutSommet(int,std::vector<std::vector<bool>>);
        void dessinFrontierePrometoDij(std::vector<std::vector<double>>);
    protected:

    private:
        std::map<std::string, Sommet*> m_sommets; // Map de sommets
        std::map<std::string, Arete*> m_aretes; // Map d'aretes
};
#endif // SOURCE_H_INCLUDED
