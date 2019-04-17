#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "arete.h"

Arete::Arete(std::string id,double poids1,double poids2, std::string sommet1, std::string sommet2)
:m_id{id},m_poids1{poids1},m_poids2{poids2}, m_sommet1{sommet1}, m_sommet2{sommet2}
{

}

std::string Arete::GetId()
{
    return m_id;
}

float Arete::GetCout1()
{
    return m_poids1;
}

float Arete::GetCout2()
{
    return m_poids2;
}

std::string Arete::GetSommet1()
{
    return m_sommet1;
}

std::string Arete::GetSommet2()
{
    return m_sommet2;
}

 bool Arete::GetSelect()
 {
    return m_select;
 }

void Arete::Setselect(bool x)
{
    m_select=x;
}

void Arete::SetCout1(float x)
{
    m_poids1=x;
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
