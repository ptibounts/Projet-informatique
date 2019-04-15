#ifndef SOURCE_H_INCLUDED
#define SOURCE_H_INCLUDED
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include "sommet.h"
#include "arete.h"

class graphe
{
    public:
        graphe();
        graphe(std::string);
        ~graphe();
        void afficher() const ;
        void afficherP() const;
        void ponderation(std::string);
    protected:

    private:
        std::map<std::string, Sommet*> m_sommets;
        std::map<std::string, Arete*> m_aretes;
};
#endif // SOURCE_H_INCLUDED
