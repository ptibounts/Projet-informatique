#ifndef SOURCE_H_INCLUDED
#define SOURCE_H_INCLUDED
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "sommet.h"

class graphe
{
    public:
        graphe(std::string);
        ~graphe();
        void afficher() const ;
    protected:

    private:
        std::unordered_map<std::string,Sommet*> m_sommets;
        std::unordered_map<std::string,Sommet*> m_arretes;
};
#endif // SOURCE_H_INCLUDED
