#include "source.h"
#include "sommet.h"
#include "arete.h"

int main()
{
    graphe g;
    std::vector<Arete*> test;
    g.sommet("broadway.txt");
    g.ponderation("broadway_weights_0.txt");
    g.afficher();
    g.afficherP();
    return 0;
}
