#include "source.h"

int main()
{
    graphe g;
    g.sommet("broadway.txt");
    g.ponderation("broadway_weights_0.txt");
    //g.afficher();
    //g.afficherP();
    g.compteurbinaire();
    return 0;
}
