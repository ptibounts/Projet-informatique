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
        graphe(std::string);
        ~graphe();
        void afficher() const ;
    protected:

    private:
        std::map<std::string,Sommet*> m_sommets;
};
#endif // SOURCE_H_INCLUDED
