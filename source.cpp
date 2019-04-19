#include "source.h"
#include <bitset>
#include <string>
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

std::map<std::string, Sommet*> graphe::GetMapsom()
{
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
                if(v==1)
                {
                    a=m_aretes1[j]->GetCout1();
                    b=m_aretes1[j+1]->GetCout1();
                }
                else
                {
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
    m_aretes1[0]->SetSelect(true);
    std::vector <std::string > m_vecSommet;
    std::string Sommet1=m_aretes1[0]->GetSommet1();
    m_vecSommet.push_back(Sommet1);
    std::string Sommet2=m_aretes1[0]->GetSommet2();
    m_vecSommet.push_back(Sommet2);


    int compteur=0;
    for (size_t i=1; i<m_aretes1.size(); i++)
    {
        Sommet1=m_aretes1[i]->GetSommet1();
        Sommet2=m_aretes1[i]->GetSommet2();
        int z=0;

        for (size_t i=0; i<m_vecSommet.size(); i++)
        {

            if(m_vecSommet[i]==Sommet1)
            {
                z+=1;
            }
            if(m_vecSommet[i]==Sommet2)
            {
                z+=2;
            }
        }

        if(z==0)
        {
            m_aretes1[i]->SetSelect(true);
            m_vecSommet.push_back(Sommet1);
            m_vecSommet.push_back(Sommet2);
            compteur+=1;
        }
        else if(z==1)
        {
            m_aretes1[i]->SetSelect(true);
            m_vecSommet.push_back(Sommet2);
            compteur+=1;
        }
        else if (z==2)
        {
            m_aretes1[i]->SetSelect(true);
            m_vecSommet.push_back(Sommet1);
            compteur+=1;
        }
        else if(z==3)
        {
            Sommet* S0= m_sommets.at(Sommet1);
            std::unordered_set<std::string> cc=S0->rechercherCC(m_vecSommet,m_aretes1);

            if((cc.find(Sommet2)==cc.end()))
            {
                m_aretes1[i]->SetSelect(true);
                compteur+=1;
            }
        }

        if(compteur ==(m_sommets.size()-1))
        {
            break;
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
        std::cout<< q <<" ";
    }
    std::cout<<std::endl;
    std::cout<< "resultat ("<<poidsTotal1<< " , "<<poidsTotal2<<")"<<std::endl;
    return m_Kruskal;
}


graphe::~graphe()
{}


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

void graphe::dessiner(std::map<std::string, Arete*> Kruskal, int valeur)
{
    Svgfile svgout("output.svg");
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
        int x1 = S1->GetposX();
        int y1 = S1->GetposY();
        int x2 = S2->GetposX();
        int y2 = S2->GetposY();
        svgout.addLine(x1, y1, x2, y2, couleur);
        if (valeur == 1)
        {
            float v1 = y.second->GetCout1();
            if(y1 == y2)
            {
                y1 = y1 - 10;
            }
            svgout.addText(((x1+x2)/2)+10, (y1+y2)/2, v1, couleur);
        }
        else if (valeur == 2)
        {
            float v2 = y.second->GetCout2();
            if(y1 == y2)
            {
                y1 = y1 - 10;
            }
            svgout.addText(((x1+x2)/2)+10, (y1+y2)/2, v2, couleur);
        }
    }
}


std::vector<std::vector<bool>> graphe::Connexite(std::vector<std::vector<bool>> m_Aretepossible)
{
    std::vector<std::vector<bool>> m_GrapheFinal;

    for(auto x: m_Aretepossible)
    {

        std::vector<std::string> m_vecSommet;
        for(auto y:m_sommets)
        {
            m_vecSommet.push_back(y.first);
        }

        std::vector<Arete*> m_vecArete;
        for(auto z:m_aretes)
        {
            m_vecArete.push_back(z.second);
        }
        for(size_t i=0; i<x.size(); i++)
        {
            m_vecArete[i]->SetSelect(x[i]);

        }
        Sommet* S1=m_sommets.begin()->second;
        std::unordered_set<std::string> cc= S1->rechercherCC(m_vecSommet,m_vecArete);

        if(cc.size()==m_vecSommet.size())
        {
            m_GrapheFinal.push_back(x);
        }
    }
    return m_GrapheFinal;
}

bool *graphe::DecToBin(int n) ///ce programme permet de convertir un nb base 10 en base 2 et le retourne
{

    bool *nbBinaire = new bool [32];

    for(size_t i=0; i<32; i++) //initialisation du tableau
        nbBinaire[i]=0;

    int k=0;
    while(n>0) //attribution du chiffre d�cimal en binaire
    {
        if (n%2==0)
            nbBinaire[k]=0;
        else
            nbBinaire[k]=1;
        n/=2;
        k++;
    }
    return nbBinaire; //on retourne le tableau de bool�en
}

std::vector<std::vector<bool>> graphe::compteurbinaire()
{
    std::vector<std::vector<bool>> tab; //vecteur de bool�en � 2 dimensions

    int ordre=m_sommets.size();
    int taille=m_aretes.size();
    int nbSol=pow(2,taille); //le nombre de solutions = 2^nb-arete
    int nbArete=0;

    for(int i=0; i<nbSol; ++i) //on r�alise toutes les solutions possibles
    {
        std::vector <bool> ToutesSol; //tableau temporaire de booleen
        bool *nbBin=DecToBin(i); //conversion base 10 -> base 2

        for(int k=0; k<taille; ++k)
        {
            ToutesSol.push_back(nbBin[k]); // on rempli le tableau temporaire avec toutes les solutions possibles
        }

        for(std::size_t m=0; m<ToutesSol.size(); ++m)
        {
            if(ToutesSol[m]==1)
                nbArete++;//si une valeur vaut 1 on l'ajoute compte '1' arete en plus
        }

        if(nbArete==(ordre-1)) //on ajoute les solutions admissibles dans le tableau quasi final
        {
            tab.push_back(ToutesSol);
        }

        ToutesSol.erase(ToutesSol.begin(), ToutesSol.end()); //on efface le tableau temporaire
        nbArete=0;
    }
    return tab;
}

/*std::vector<std::vector<bool>> graphe::RechercheSol(){
    std::vector<std::vector<bool>>Solutiontemp=this->compteurbinaire();
    std::vector<std::vector<bool>>Solutionfin=this->Connexite(Solutiontemp);

std::cout<<"Les Aretes finales sont: ";
for (auto x:Solutionfin){
        std::cout<< "Arete: ";
    for (auto y:x){
        std::cout<<y;
    }
    std::cout<<std::endl;

}
    return Solutionfin;

}
*/
std::vector<std::vector<bool>> graphe::tailleGraphe(std::vector<std::vector<bool>>Solutionfin, std::vector <std::vector<double>> m_vecFin)
{
    std::vector<std::vector<bool>>SolutionfinT;
    std::vector <std::vector<double>> test;
    std::vector <std::vector<double>> m_vecfinT;
    int z,y;
    for (size_t i = 0; i<m_vecFin.size(); ++i)
    {
        for (size_t j = i+1; j<m_vecFin.size(); ++j)
        {
            if ((m_vecFin[i][0] < m_vecFin[j][0]) && (m_vecFin[i][1] < m_vecFin[j][1]))
            {
                test.push_back(m_vecFin[j]);

            }

        }
    }

    for( auto x: m_vecFin)
    {
        z=2;
        for (auto y :test)
        {
            if(x==y)
            {
                z+=1;
            }
        }
        if(z==2)
        {
            m_vecfinT.push_back(x);
        }
    }
    for (size_t i = 0; i<m_vecFin.size(); ++i)
    {
        y=2;
        for (size_t j = 0; j<m_vecfinT.size(); ++j)
        {
            if(m_vecfinT[j]==m_vecFin[i])
            {
                y+=1;
            }
        }
        if(y!=2)
        {

            SolutionfinT.push_back(Solutionfin[i]);
        }
    }

    return SolutionfinT;
}



std::vector<std::vector<bool>> graphe::RechercheSol()
{
    double poidsTotal1,poidsTotal2;
    std::vector<std::vector<bool>>Solutiontemp=this->compteurbinaire();
    std::vector<std::vector<bool>>Solutionfin=this->Connexite(Solutiontemp);

    std::vector <double> m_vecPoids;
    std::vector <std::vector<double>> m_vecFin;
    for (auto x:Solutionfin)
    {
        poidsTotal1=0;
        poidsTotal2=0;

        for(size_t i=0; i<x.size(); ++i)
        {
            if(x[i])
            {
                std::string s = std::to_string(i);
                poidsTotal1 += m_aretes.at(s)->GetCout1();
                poidsTotal2 += m_aretes.at(s)->GetCout2();
            }
        }

        m_vecPoids.push_back(poidsTotal1);
        m_vecPoids.push_back(poidsTotal2);

        m_vecFin.push_back(m_vecPoids);
        m_vecPoids.clear();
    }
    std::vector<std::vector<bool>>SolutionFinal=this->tailleGraphe(Solutionfin,m_vecFin);

    std::cout<<"Les Aretes finales sont: "<<std::endl;
    for (auto x:SolutionFinal)
    {
        std::cout<< "Arete: ";
        for (auto y:x)
        {
            std::cout<<y;
        }
        std::cout<<std::endl;
    }
    return SolutionFinal;
}

void graphe::dessinFrontierePrometo(std::vector<std::vector<bool>> solution)
{
    std::vector<std::vector<bool>> Sol = solution;
    int x1, y1, x3, y3, x4, y4, valeur = 0;
    Svgfile svgout("output1.svg");
    svgout.addGrid();
    int TotalCout1 = 0, TotalCout2 = 0;
    for(auto x: m_aretes)
    {
        TotalCout1 += x.second->GetCout1();
        TotalCout2 += x.second->GetCout2();
    }
    std::cout<< TotalCout1 << " " << TotalCout2;
    std::string couleur = "black";
    svgout.addLine(500,500, 500+(TotalCout1*10), 500, couleur);
    svgout.addLine((500+(TotalCout1*10))-50, 500-25,500+(TotalCout1*10), 500, couleur);
    svgout.addLine((500+(TotalCout1*10))-50, 500+25,500+(TotalCout1*10), 500, couleur);
    svgout.addLine(500, 500, 500, 500-(TotalCout2*10), couleur);
    svgout.addLine(500+25, (500-(TotalCout1*10))+50,500, 500-(TotalCout2*10), couleur);
    svgout.addLine(500-25, (500-(TotalCout1*10))+50,500, 500-(TotalCout2*10), couleur);
    for(auto x: Sol)
    {
        x1 = 0, y1 = 0, x3 = 0, y3 = 0, x4 = 0, y4 =0;
        for (int i = 0; i<x.size(); ++i)
        {
            std::string s = std::to_string(i);
            if(x[i] == 1)
            {
                x1 += m_aretes.at(s)->GetCout1();
                y1 += m_aretes.at(s)->GetCout2();
                std::string s1 = m_aretes.at(s)->GetSommet1();
                std::string s2 = m_aretes.at(s)->GetSommet2();
                Sommet* S1 = m_sommets.at(s1);
                Sommet* S2 = m_sommets.at(s2);
                x3 = S1->GetposX();
                y3 = S1->GetposY();
                x4 = S2->GetposX();
                y4 = S2->GetposY();
                svgout.addDisk(x3, y3+valeur, 10, couleur);
                svgout.addDisk(x4, y4+valeur, 10, couleur);
                svgout.addLine(x3, y3+valeur, x4, y4+valeur, couleur);

            }

        }
        valeur+= 150;
        svgout.addDisk(500+(x1*10),500-(y1*10),5, "green");
    }
}


