#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "arete.h"

Arete::Arete(std::string id,double cout1,double cout2, double sommet1, double sommet2)
:m_id{id},m_cout1{cout1},m_cout2{cout2}, m_sommet1{sommet1}, m_sommet2{sommet2}
{

}

Arete::Arete(std::string id,double cout1,double cout2)
:m_id{id},m_cout1{cout1},m_cout2{cout2}
{

}

Arete::~Arete()
{
    //dtor
}

void Arete::afficherPoids() const
{
    std::cout<<m_id<<" : "<<m_sommet1<<" - "<< m_sommet2<< " Ponderation: " <<"("<<m_cout1<<","<<m_cout2<<")"<<std::endl;
}

void Arete::afficher() const
{
    std::cout<<m_id<< " depart: "<< m_sommet1 << " arrive: "<< m_sommet2<<std::endl;
}
