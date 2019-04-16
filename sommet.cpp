#include "sommet.h"

Sommet::Sommet(std::string id,int x,int y):m_id{id},m_x{x},m_y{y}
{

}


std::string Sommet::GetId()
 {
    return m_id;
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

std::unordered_map<std::string,std::string> Sommet::parcoursBFS() const
{
    std::unordered_map<std::string,std::string> l_pred;
    std::queue<const Sommet*> file;
    std::unordered_set<std::string> l_decouvert;
    file.push(this);
    l_decouvert.insert(m_id);
    const Sommet* s=nullptr;

    while(!file.empty())
    {
        s=file.front();
        file.pop();
        for ( auto ts: (s->m_voisins))
        {
            if(l_decouvert.find(ts->m_id)==l_decouvert.end())
            {
                l_decouvert.insert(ts->m_id);
                file.push(ts);
                l_pred.insert({ts->m_id, s->m_id});
            }
        }
    }

    return l_pred;
}

std::unordered_set<std::string> Sommet::rechercherCC() const
{
    std::unordered_set<std::string> cc;
    std::unordered_map<std::string,std::string> l_pred = this->parcoursBFS();
    cc.insert(this->m_id);
    for (auto s: l_pred)
    {
        cc.insert(s.first);
    }
    return cc;
}


