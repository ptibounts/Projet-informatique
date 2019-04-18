#include "source.h"
#include "sommet.h"
#include "arete.h"
#include <iostream>
#include <fstream>
#include<unordered_map>

int main()
{
    int valeur = 0;
    std::vector<Arete*> Tri(std::unordered_map<std::string, Arete*> m_aretes,int v);
    std::map<std::string, Arete*> Kruskal;
    graphe g;
    std::vector<Arete*> test;
    g.sommet("cubetown.txt");
    g.ponderation("cubetown_weights_0.txt");
    g.afficher();
    g.afficherP();
    do
    {
        valeur = choix();
    } while (valeur == 0);
    Kruskal = g.Kruskal(valeur);
    g.dessiner(Kruskal, valeur);
    system("start output.svg");
    return 0;
}
