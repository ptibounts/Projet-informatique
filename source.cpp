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
    auto it = m_aretes.begin();
    for (int i=0; i<ordre; ++i)
    {
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donnees sommet");
        ifs>>p1;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture poids1 sommet");
        ifs>>p2;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture poids2 sommet");

        it->second->setpoids1(p1);
        it->second->setpoids2(p2);

       ++it;
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

std::map <std::string, Sommet*> graphe::GetMapsom(){
return m_sommets;
}

std::map<std::string, Arete*> graphe::GetMapar()
{
    return m_aretes;
}



std::vector <Arete*> Tri (std::map<std::string, Arete*> m_aretes,int v )
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

std::map<std::string, Arete*> graphe::Kruskal ( int v )
{
    int poidsTotal1 = 0, poidsTotal2 = 0;
    std::vector <Arete*> m_aretes1;
    std::map<std::string, Arete*> m_areteg =(this)->GetMapar();
    m_aretes1= Tri(m_areteg,v);
    std::string id=m_aretes1[0]->GetId();
    std::map<std::string, Arete*> m_Kruskal;
    m_Kruskal[id]=m_aretes1[0];
    m_aretes1[0]->Setselect(true);
    std::vector <std::string > m_vecSommet;
    std::string Sommet1=m_aretes1[0]->GetSommet1();
        m_vecSommet.push_back(Sommet1);
    std::string Sommet2=m_aretes1[0]->GetSommet2();
        m_vecSommet.push_back(Sommet2);


int compteur=0;
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
        compteur+=1;
        }
        else if(z==1){
            m_aretes1[i]->Setselect(true);
        m_vecSommet.push_back(Sommet2);
        compteur+=1;
        }else if (z==2){
             m_aretes1[i]->Setselect(true);
        m_vecSommet.push_back(Sommet1);
        compteur+=1;
        }
        else if(z==3){
        Sommet* S0= m_sommets.at(Sommet1);
        std::unordered_set<std::string> cc=S0->rechercherCC(m_vecSommet,m_aretes1);

        if((cc.find(Sommet2)==cc.end())){
        m_aretes1[i]->Setselect(true);
        compteur+=1;
        }
        }

         if(compteur ==(m_sommets.size()-1)){
                break;
    }
        if(m_aretes1[i]->GetSelect()){
        std::cout<< m_aretes1[i]->GetId()<<" arete selectionnée"<<std::endl;
    } else{
    std::cout<< m_aretes1[i]->GetId()<< " non"<<std::endl;
    }
    }
    for (size_t i=0; i<m_aretes1.size(); i++)
    {
        bool a=m_aretes1[i]->GetSelect();
        if(a==true)
        {
            id=m_aretes1[i]->GetId();
            m_Kruskal[id]=m_aretes1[i];
        }
    }

        for (auto x:m_Kruskal)
        {
            poidsTotal1 += x.second->GetCout1();
            poidsTotal2 += x.second->GetCout2();
        }
        for (auto x:m_Kruskal)
        {
            std::string q=x.second->GetId();
            std::cout<<q<<std::endl;
        }
    std::cout<< "resultat ("<<poidsTotal1<< " , "<<poidsTotal2<<")"<<std::endl;
    return m_Kruskal;
    }



int choix()
{
        int choix;
        std::cout<<"Veuillez saisir a partir de quelle ponderation voulez-vous lancer Kruskal :"<<std::endl;
        std::cin>> choix;
        switch (choix)
        {
            case 1:
                return choix;
                break;
            case 2:
                return choix;
                break;
            default:
                std::cout << "Veuillez resaisir, s'il vous plait!"<<std::endl;
                return 0;
        }
}

graphe::~graphe()
{

}

void graphe::dessiner(std::map<std::string, Arete*> Kruskal)
{
    Svgfile svgout;
    svgout.addGrid();
    std::string couleur = "black";
    for (auto x: m_sommets)
    {

        svgout.addDisk(x.second->GetposX(), x.second->GetposY(), 10, couleur);
    }

    for (auto y: Kruskal)
    {
        std::string s1 = y.second->GetSommet1();
        std::string s2 = y.second->GetSommet2();

        Sommet* S1 = m_sommets.at(s1);
        Sommet* S2 = m_sommets.at(s2);
        svgout.addLine(S1->GetposX(), S1->GetposY(), S2->GetposX(), S2->GetposY(), couleur);
    }
}
