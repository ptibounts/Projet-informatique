#include "sommet.h"
// Constructeur
Sommet::Sommet(std::string id,int x,int y):m_id{id},m_x{x},m_y{y},m_composante{0}
{

}
// On set le composant
void Sommet::SetComposante(int x)
{
    m_composante=x;
}
// On prend le composant
int Sommet::GetComposante()
{
    return m_composante;
}

std::string Sommet::GetId()
{
    return m_id;
}
// Sous-programme  pour ajouter des voisins
void Sommet::ajouterVoisin(Sommet* voisin)
{
    m_voisins.push_back(voisin); // On push_back dans notre voisin
}

void Sommet::afficherData() const // Afficher les donnees d'un sommet
{
    std::cout<<"    "<<m_id<<" : "<<"(x,y)=("<<m_x<<","<<m_y<<")"<<std::endl;
}

void Sommet::afficherVoisins() const // Sous-programme pour afficher les voisins d'un sommet
{
    std::cout<<"  voisins :"<<std::endl;
    for(auto v:m_voisins)
    {
        v->afficherData();
    }
}

std::unordered_map<std::string,std::string> Sommet::parcoursBFS() const // Parcours BFS
{
    std::unordered_map<std::string,std::string> l_pred; // Nos predeceseurs
    std::queue<const Sommet*> file; // On cree notre file pour le BFS
    std::unordered_set<std::string> l_decouvert; // Pour nos sommets decouverts
    file.push(this); // On push notre premier element
    l_decouvert.insert(m_id); // Et on insere notre premier element dans le l_decouvert
    const Sommet* s=nullptr;
    while(!file.empty()) // Tant que notre file n'est pas vide
    {
        s=file.front(); // FIFO = 'First In Firts Out'
        file.pop(); // On le supprime le premier element qui a ete affecte a s
        for (auto ts: (s->m_voisins)) // On parcourt nos voisins
        {
            if(l_decouvert.find(ts->m_id)==l_decouvert.end()) // Si notre sommet n'est pas dans notre l_decouvert
            {
                l_decouvert.insert(ts->m_id); // alors on l'insere dans l_decouvert
                file.push(ts); // et on push dans notre file
                l_pred.insert({ts->m_id, s->m_id}); // On insere nos predecesseur
            }
        }
    }
    return l_pred; // On retourne nos predecesseurs
}

std::vector<Sommet*> Sommet::Getvoisins()
{
    return m_voisins;
}

std::unordered_map<std::string,std::string> Sommet::parcoursBFS(std::vector<std::string > m_vecSommet, std::vector <Arete*> m_aretes1)
{
    std::unordered_map<std::string,std::string> l_pred;
    std::queue< Sommet*> file;
    std::unordered_set<std::string> l_decouvert;
    file.push(this);
    l_decouvert.insert(m_id);
    Sommet* s=nullptr;
    std::string voisin;
    std::string soma1;
    std::string soma2;
    std::string som1;
     std::vector<Sommet*> vecvoisins;
    while(!file.empty())
    {
        bool selection=false;
        s=file.front();
        file.pop();
        vecvoisins= s->Getvoisins();
        for (auto ts:vecvoisins)
        {
            voisin= ts->GetId();
            for(auto y:m_aretes1)
            {
                selection=y->GetSelect();
                soma1=y->GetSommet1();
                soma2=y->GetSommet2();
                som1=s->GetId();
                if((soma1==som1 && soma2==voisin)||(soma1==voisin && soma2==som1))
                {
                    if(selection==true)


                    if(l_decouvert.find(voisin) == l_decouvert.end())
                    {
                        l_decouvert.insert(voisin);
                        file.push(ts);
                        l_pred.insert({voisin, som1});
                    }
                }
            }
        }
    }
    return l_pred;
}

std::unordered_set<std::string> Sommet::rechercherCC(std::vector <std::string > m_vecSommet,std::vector <Arete*> m_aretes1)
{
    std::unordered_set<std::string> cc;
    std::unordered_map<std::string,std::string> l_pred = this->parcoursBFS(m_vecSommet,m_aretes1);
    cc.insert(this->m_id);
    for (auto s: l_pred)
    {
        cc.insert(s.first);
    }
    return cc;
}

 std::vector<Sommet*> Sommet::rechercherCC1(std::vector <std::string > m_vecSommet,std::vector <Arete*> m_aretes1)
{
    std::unordered_map<std::string,std::string> l_pred;
    std::queue< Sommet*> file;
    std::unordered_set<std::string> l_decouvert;
    file.push(this);
    std::string tec=this->GetId();
    this->SetComposante(1);
    l_decouvert.insert(this->GetId());
    Sommet* s=nullptr;
    std::string voisin, soma1, soma2, som1;
    std::vector<Sommet*> vecvoisins;
    std::vector<Sommet*> vecConnexe;
    vecConnexe.push_back(this);
    bool selection;
    for(int i=0; file.size()!=0;i++)
    {
        s=file.front();
        file.pop();
        vecvoisins= s->Getvoisins();
        for (auto ts:vecvoisins)
        {
            voisin= ts->GetId();
            for(auto y:m_aretes1)
            {
                selection=y->GetSelect();
                soma1=y->GetSommet1();
                soma2=y->GetSommet2();
                som1=s->GetId();
                if((l_decouvert.find(voisin) == l_decouvert.end()) && (voisin!=tec) && (voisin!=som1))
                {
                    if((soma1==som1 && soma2==voisin)||(soma1==voisin && soma2==som1))
                    {
                        if(selection==true)
                        {
                            l_decouvert.insert(voisin);
                            file.push(ts);
                            ts->SetComposante(1);
                            vecConnexe.push_back(ts);
                        }
                    }
                }
            }
        }
    }
    return vecConnexe;
}

int Sommet::GetposY()
{
    return m_y;
}

int Sommet::GetposX()
{
    return m_x;
}

void Sommet::SetDis(double distance)
{
    m_distance=distance;
}

void Sommet::SetDisA(double distanceA)
{
    m_distanceautre=distanceA;
}

void Sommet::SetMark(bool mark)
{
    m_mark=mark;
}

void Sommet::SetPred(std::string pred)
{
    m_pred=pred;
}

double Sommet::GetDisA()const
{
    return m_distanceautre;
}

double Sommet::GetDis()const
{
    return m_distance;
}

bool Sommet::GetMark()const
{
    return m_mark;
}
