#include "source.h"
#include "sommet.h"
#include "arete.h"
#include <iostream>
#include <fstream>
#include<unordered_map>

int main()
{
    std::vector<Arete*> Tri(std::unordered_map<std::string, Arete*> m_aretes,int v);
    std::unordered_map<std::string, Arete*> Kruskal (std::unordered_map<std::string, Arete*> m_aretes, int v);
    graphe g;
    std::vector<Arete*> test;
    g.sommet("broadway.txt");
    g.ponderation("broadway_weights_0.txt");
    g.afficher();
    g.afficherP();
    return 0;
}
