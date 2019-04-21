#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "arete.h"
// Fichier qui regroupe tout ce que l'on fait avec nos aretes pour les manipuler
// Constructeur
Arete::Arete(std::string id,double poids1,double poids2, std::string sommet1, std::string sommet2)
:m_id{id},m_poids1{poids1},m_poids2{poids2}, m_sommet1{sommet1}, m_sommet2{sommet2}
{

}
// Setter du poids 1 lorsque nous en avons besoin
void Arete::setpoids1(double poids1)
{
    m_poids1 = poids1;
}
// Setter du poids 2 lorsque nous en avons besoin
void Arete::setpoids2(double poids2)
{
    m_poids2=poids2;
}
// Setter de l'id de notre sommet lorsque nous en avons besoin
void Arete::setid(std::string id)
{
    m_id=id;
}
// Getter pour avoir l'id de notre sommet
std::string Arete::GetId()
{
    return m_id; // Il retourne un string
}
//Getter pour le cout numero 1 de notre arete
double Arete::GetCout1()
{
    return m_poids1; // Il retourne un double
}
//Getter pour le cout numero 2 de notre arete
double Arete::GetCout2()
{
    return m_poids2; // Il retourne un double
}
//Getter pour notre sommet 1 donc celui de depart de notre arete
std::string Arete::GetSommet1()
{
    return m_sommet1; // Il retourne un string
}
//Getter pour notre sommet 2 donc celui d'arrive de notre arete
std::string Arete::GetSommet2()
{
    return m_sommet2; // Il retourne un string
}
//Getter pour savoir si notre arete est selectionne ou pas
bool Arete::GetSelect()
{
    return m_select; // On return un booleen soit 0 soit 1
}
// Set le booleen de notre arete
void Arete::SetSelect(bool x)
{
    m_select=x;
}
// Destructeur
Arete::~Arete()
{
    //dtor
}
// Affichage pour les aretes donc avec le sommet de depart celui d'arrive et la double ponderation
void Arete::afficherPoids()
{
    std::cout<<m_id<<" : "<<m_sommet1<<" - "<< m_sommet2<< " Ponderation: " <<"("<<m_poids1<<","<<m_poids2<<")"<<std::endl;
}
// Affichage du sommet de depart et celui d'arriver
void Arete::afficher() const
{
    std::cout<<m_id<< " depart: "<< m_sommet1 << " arrive: "<< m_sommet2<<std::endl;
}
