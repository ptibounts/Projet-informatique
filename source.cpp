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
    double sommetD, sommetF;
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


void graphe::afficherP()
{

    for(auto it = m_aretes.begin(); it !=m_aretes.end(); ++it)
    {
        std::cout<< "Aretes : ";
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
        std::cout << std::endl;
    }
    for(auto it = m_aretes.begin(); it !=m_aretes.end(); ++it)
    {
        std::cout<< "Aretes : ";
        it->second->afficher();
        std::cout << std::endl;
    }
}
/*
std::vector<Arete*> graphe::Prim(graphe grph)
{
    std::vector<Arete*> aretetmp;
    std::vector<Sommet*> sommettmp;

    while(tant que c'est pas connexe)
    {

    }

    return aretetmp
}
*/
/*
int graphe::rechercherCompConnex() const{

    int nbrCompConnex;
    std::vector<std::unordered_set<std::string>> vec;
    bool tst;

    //std::cout<<"composantes connexes :"<<std::endl;

    for(auto s: m_sommets)
    {
        tst=0;
        for(auto cc: vec)
        {
            if(cc.find(s.first)!=cc.end())
                tst=1;
        }
        if(tst==0)
            tab.push_back((s.second)->rechercherCC());
    }

    nbrCompConnex=vec.size();
    return nbrCompConnex;
}
*/

bool *graphe::DecToBin(int n) ///ce programme permet de convertir un nb base 10 en base 2 et le retourne
{

    bool *nbBinaire = new bool [32];

    for(size_t i=0;i<32;i++) //initialisation du tableau
        nbBinaire[i]=0;

    int k=0;
    while(n>0) //attribution du chiffre décimal en binaire
    {
        if (n%2==0)
            nbBinaire[k]=0;
        else
            nbBinaire[k]=1;
        n/=2;
        k++;
    }
    return nbBinaire; //on retourne le tableau de booléen
}

void graphe::compteurbinaire()
{
    std::vector<std::vector<bool>> tab; //vecteur de booléen à 2 dimensions

    int ordre=m_sommets.size();
    int taille=m_aretes.size();
    int nbSol=pow(2,taille); //le nombre de solutions = 2^nb-arete
    int nbArete=0;

    for(int i=0; i<nbSol; ++i) //on réalise toutes les solutions possibles
    {
        std::vector <bool> ToutesSol; //tableau temporaire de booleen
        bool *nbBin=DecToBin(i); //conversion base 10 -> base 2

        for(int k=0; k<taille; ++k)
        {
            ToutesSol.push_back(nbBin[k]); // on rempli le tableau temporaire avec toutes les solutions possibles
        }

        for(std::size_t m=0; m<ToutesSol.size();++m)
        {
            if(ToutesSol[m]==1) nbArete++;//si une valeur vaut 1 on l'ajoute compte '1' arete en plus
        }

        if(nbArete==(ordre-1)) //on ajoute les solutions admissibles dans le tableau quasi final
        {
            tab.push_back(ToutesSol);
        }

        ToutesSol.erase(ToutesSol.begin(), ToutesSol.end()); //on efface le tableau temporaire
        nbArete=0;
    }

    ///Test si le vecteur s'est bien enregistré
    /*
    std::cout<<tab.size()<<" "<<taille;
    for(int n=0; n<tab.size(); n++) //affichage du tableau de booleen à l'envers
    {
        for(int p=taille-1; p>=0;p--)
        {std::cout<<tab[n][p];}
        std::cout<<std::endl;
    }
    */

    std::cout <<"\n\tNombre de vecteurs (enchainements possible) : "<<tab.size() <<'\n';
}

graphe::~graphe()
{}
