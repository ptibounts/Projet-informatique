#include "source.h"
#include "sommet.h"

int main()
{
    graphe g;
    g.sommet("broadway.txt");
    g.ponderation("broadway_weights_0.txt");
    g.afficher();
    g.afficherP();
    return 0;
}
