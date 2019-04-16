#include "source.h"

graphe::graphe()
{

}

void graphe::sommet(std::string nomFichier)
{
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int ordre;
    ifs >> ordre;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string id;
    int x,y;
    for (int i=0; i<ordre; ++i)
    {
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donnees sommet");
        ifs>>x;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donnees sommet");
        ifs>>y;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donnees sommet");
        m_sommets.insert({id,new Sommet{id,x,y}});
    }
    int taille;
    ifs >> taille;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture taille du graphe");
    std::string id_voisin;
    std::string sommetD, sommetF;
    for (int i=0; i<taille; ++i)
    {
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donnees sommet");
        ifs>>sommetD;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donnees sommet");
        ifs>>sommetF;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donnees sommet");
        (m_sommets.find(sommetD))->second->ajouterVoisin((m_sommets.find(sommetF))->second);
        (m_sommets.find(sommetF))->second->ajouterVoisin((m_sommets.find(sommetD))->second);
        m_aretes.insert({id,new Arete{id,1,1,sommetD,sommetF}});
    }
}

void graphe::ponderation(std::string nomFichier)
{
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int ordre, nbPonderation;
    ifs >> ordre;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture ordre du graphe");
    ifs >> nbPonderation;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture nombre de ponderation du graphe");
    std::string id;
    double p1, p2;
    for (int i=0; i<ordre; ++i)
    {
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donnees sommet");
        ifs>>p1;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donnees sommet");
        ifs>>p2;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donnees sommet");
        for (auto it = m_aretes.begin(); it !=m_aretes.end(); ++it)
        {
            if(id == it->first)
            {
                it->second->m_poids1 = p1;
                it->second->m_poids2 = p2;
            }
        }
    }
}

void graphe::afficherP() const
{

    for(auto it = m_aretes.begin(); it !=m_aretes.end(); ++it)
    {
        std::cout<< "Arretes : ";
        it->second->afficherPoids();
        std::cout << std::endl;
    }
}

void graphe::afficher() const
{
    std::cout<<"Graphe : "<<std::endl;
    std::cout << "Ordre : " << m_sommets.size() << std::endl;
    for ( auto it = m_sommets.begin(); it !=m_sommets.end(); ++it)
    {
        std::cout << "Sommets :  ";
        it->second->afficherData();
        it->second->afficherVoisins();
        std::cout << std::endl;
    }
    for(auto it = m_aretes.begin(); it !=m_aretes.end(); ++it)
    {
        std::cout<< "Arretes : ";
        it->second->afficher();
        std::cout << std::endl;
    }
}

/*
std::vector <Arete*> Tri (std::unordered_map<std::string, Arete*> m_aretes,int v )
{
    std::vector <Arete*> m_aretes1;
    for( auto x: m_aretes)
    {
        Arete* a=x.second;
        m_aretes1.push_back(a);

    }

    for(size_t i = 0 ; i< m_aretes1.size() ; ++i)
    {
        for(size_t j = 0 ; j< m_aretes1.size() ; ++j)
        {
            if(m_aretes1.size() > j+1 )
            {
                 float a;
                 float b;
                if(v==1){
                 a=m_aretes1[j]->GetCout1();
                 b=m_aretes1[j+1]->GetCout1();
                } else{
                 a=m_aretes1[j]->GetCout2();
                 b=m_aretes1[j+1]->GetCout2();
                }
                if(a>b)
                {
                    Arete* a2=m_aretes1[j+1];
                    m_aretes1.insert(m_aretes1.begin() + j,a2);
                    m_aretes1.erase(m_aretes1.begin() + (j+2));

                }
            }
        }

    }
    return m_aretes1;
}

std::unordered_map<std::string, Arete*> Kruskal ( std::unordered_map<std::string, Arete*> m_aretes std::unordered_map<std::string,Sommet*> m_sommets,int v )
{
    std::vector <Arete*> m_aretes1;
    m_aretes1= Tri(m_aretes,v);
    std::string id=m_aretes1[0]->GetId();
    std::unordered_map<std::string, Arete*> m_Kruskal;
    m_Kruskal[id]=m_aretes1[0];

    std::vector <std::string > m_vecSommet;
    std::string Sommet1=m_aretes1[0]->GetSommet1();
        m_vecSommet.push_back(Sommet1);
    std::string Sommet2=m_aretes1[0]->GetSommet2();
        m_vecSommet.push_back(Sommet2);


                    for (size_t i=1;i<m_aretes1.size();i++)
    {
         Sommet1=m_aretes1[i]->GetSommet1();
         Sommet2=m_aretes1[i]->GetSommet2();
    int z=0;

      for (size_t i=0;i<m_vecSommet.size();i++){

        if(m_vecSommet[i]==Sommet1){
            z+=1;
        }
        if(m_vecSommet[i]==Sommet2){
            z+=2;
      }
      }

      if(z==0){
    m_aretes1[i]->Setselect(true);
        m_vecSommet.push_back(Sommet1);
        m_vecSommet.push_back(Sommet2);
        }
        else if(z==1){
            m_aretes1[i]->Setselect(true);
        m_vecSommet.push_back(Sommet2);

        }else if (z==2){
             m_aretes1[i]->Setselect(true);
        m_vecSommet.push_back(Sommet1);
        }
        else if(z==3){
        Sommet* S0= m_sommets.at(Sommet1);
        std::unordered_set<std::string> cc=S0->rechercherCC();

        if(cc.find(Sommet2)==cc.end()){
        m_aretes1[i]->Setselect(true);
        }
        }
    }


     for (size_t i=0;i<m_aretes1.size();i++){
        bool a=m_aretes1[i]->GetSelect();
        if(a==true){
        id=m_aretes1[i]->GetId();
        m_Kruskal[id]=m_aretes1[i];
        }
     }
for (auto x:m_Kruskal){
    std::string q=x.second->GetId();
    std::cout<<q<<std::endl;
}
return m_Kruskal;
}*/

graphe::~graphe()
{

}


