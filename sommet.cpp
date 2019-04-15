#include "sommet.h"

Sommet::Sommet(std::string id,int x,int y):m_id{id},m_x{x},m_y{y}
{

}

void Sommet::ajouterVoisin( Sommet* voisin)
{
    m_voisins.push_back(voisin);
}

void Sommet::afficherData() const /// Afficher les donnees d'un sommet
{
    std::cout<<"    "<<m_id<<" : "<<"(x,y)=("<<m_x<<","<<m_y<<")"<<std::endl;
}

void Sommet::afficherVoisins() const /// Sous-programme pour afficher les voisins d'un sommet
{
    std::cout<<"  voisins :"<<std::endl;
    for(auto v:m_voisins)
    {
        v->afficherData();
    }
}


