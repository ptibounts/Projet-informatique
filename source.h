#ifndef SOURCE_H_INCLUDED
#define SOURCE_H_INCLUDED
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include "sommet.h"
#include "arete.h"
#include <cmath>
#include <math.h>
#include <vector>

class graphe
{
    public:
        graphe();
        ~graphe();
        void sommet(std::string);
        void afficher() const ;
        void afficherP();
        void ponderation(std::string);
        void compteurbinaire();
        bool *DecToBin(int n);
    protected:

    private:
        std::map<std::string, Sommet*> m_sommets;
        std::map<std::string, Arete*> m_aretes;
};
#endif // SOURCE_H_INCLUDED
