#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "arete.h"

Arete::Arete(std::string id,double poids1,double poids2, double sommet1, double sommet2)
:m_id{id},m_poids1{poids1},m_poids2{poids2}, m_sommet1{sommet1}, m_sommet2{sommet2}
{

}

Arete::Arete(std::string id,double poids1,double poids2)
:m_id{id},m_poids1{poids1},m_poids2{poids2}
{

}

Arete::~Arete()
{
    //dtor
}

void Arete::afficherPoids()
{
    std::cout<<m_id<<" : "<<m_sommet1<<" - "<< m_sommet2<< " Ponderation: " <<"("<<m_poids1<<","<<m_poids2<<")"<<std::endl;
}

void Arete::afficher() const
{
    std::cout<<m_id<< " depart: "<< m_sommet1 << " arrive: "<< m_sommet2<<std::endl;
}
