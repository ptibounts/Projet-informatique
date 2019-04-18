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
    g.sommet("broadway.txt");
    g.ponderation("broadway_weights_0.txt");
    g.afficher();
    g.afficherP();
    do
    {
        valeur = choix();
    } while (valeur == 0);
    Kruskal = g.Kruskal(1);
    g.dessiner(Kruskal, 1);
    system("start output.svg");
    g.RechercheSol();
    return 0;
}

