#include "source.h"
#include "sommet.h"

int main()
{
    graphe g{"broadway.txt"};
    graphe h;
    h.ponderation("broadway_weights_0.txt");
    g.afficher();
    h.afficherP();
    return 0;
}
