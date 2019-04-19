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
    std::vector<std::vector<bool>> Solution;
    graphe g;
    g.sommet("broadway.txt");
    g.ponderation("broadway_weights_0.txt");
    g.afficher();
    g.afficherP();
    do
    {
        valeur = choix();
    } while (valeur == 0);
    Kruskal = g.Kruskal(valeur);
    g.dessiner(Kruskal, valeur);
    system("start output.svg");
    Solution = g.RechercheSol();
    g.dessinFrontierePrometo(Solution);
    system("start output1.svg");
    return 0;
}
