#include "source.h"
#include <bitset>
#include <string>
graphe::graphe() // Constructeur de graphe
{

}

void graphe::sommet(std::string nomFichier) // Chargement du fichier 1 avec les sommets (id + x + y) et les aretes (id + sommetD + sommetA)
{
    int x,y, ordre, taille;
    std::string id, id_voisin, sommetD, sommetF;
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier);
    ifs >> ordre;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture ordre du graphe");
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
        m_sommets.insert({id,new Sommet{id,x,y}}); // On ajoute des sommets depuis le fichier
    }
    ifs >> taille;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture taille du graphe");
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
        (m_sommets.find(sommetD))->second->ajouterVoisin((m_sommets.find(sommetF))->second);// On ajoute les voisins
        (m_sommets.find(sommetF))->second->ajouterVoisin((m_sommets.find(sommetD))->second);// On ajoute les voisins
        m_aretes.insert({id,new Arete{id,1,1,sommetD,sommetF}}); // On cree nos aretes
    }
}

void graphe::ponderation(std::string nomFichier) // Chargement du fichier 2 avec les aretes et le nombre de poids quelles ont
{
    int ordre, nbPonderation;
    std::string id;
    double p1, p2;
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    ifs >> ordre;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture ordre du graphe");
    ifs >> nbPonderation;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture nombre de ponderation du graphe");
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
        for (auto it = m_aretes.begin(); it !=m_aretes.end(); ++it)
        {
            if(id == it->first)
            {
                it->second->setpoids1(p1); // on set le poids 1
                it->second->setpoids2(p2); // on set le poids 2
            }
        }
    }
}

void graphe::afficherP() const // Sous-programme pour afficher les aretes
{
    for(auto it = m_aretes.begin(); it !=m_aretes.end(); ++it) // Boucle pour tout afficher
    {
        std::cout<< "Arretes : ";
        it->second->afficherPoids(); // Affichage
        std::cout << std::endl;
    }
}

void graphe::afficher() const // Sous-programme pour afficher les sommets, les voisins et les artes
{
    std::cout<<"Graphe : "<<std::endl;
    std::cout << "Ordre : " << m_sommets.size() << std::endl;
    for ( auto it = m_sommets.begin(); it !=m_sommets.end(); ++it) // Parcours les sommets
    {
        std::cout << "Sommets :  ";
        it->second->afficherData();  // Afficher les donnees du sommet
        it->second->afficherVoisins(); // Afficher les voisins
        std::cout << std::endl;
    }
    for(auto it = m_aretes.begin(); it !=m_aretes.end(); ++it) // Parcours les aretes
    {
        std::cout<< "Arretes : ";
        it->second->afficher(); // Afficher les donnees des aretes du premier fichier
        std::cout << std::endl;
    }
}

std::map<std::string, Sommet*> graphe::GetMapsom() // Obtenir la map de sommets sans l'affecter car elle est en privée
{
    return m_sommets;
}

std::map<std::string, Arete*> graphe::GetMapar() // Obtenir la map d'aretes sans l'affecter car elle est en privée
{
    return m_aretes;
}

std::vector <Arete*> Tri(std::map<std::string, Arete*> m_aretes,int v) // Sous-programme pour trier nos aretes par poids croissant pour Kruskal
{
    std::vector <Arete*> m_aretes1; // Notre vecteur que l'on va retourner
    double a, b;
    for( auto x: m_aretes) // boucle pour remplir notre vecteur des aretes que l'on connait de notre graphe
    {
        Arete* a=x.second;
        m_aretes1.push_back(a);
    }
    for(size_t i = 0 ; i< m_aretes1.size(); ++i)
    {
        for(size_t j = 0; j< m_aretes1.size(); ++j)
        {
            if(m_aretes1.size() > j+1 )
            {
                if(v==1) // Si le poids est a 1
                {
                    a=m_aretes1[j]->GetCout1();
                    b=m_aretes1[j+1]->GetCout1();
                }
                else // Sinon on prend le poids 2
                {
                    a=m_aretes1[j]->GetCout2();
                    b=m_aretes1[j+1]->GetCout2();
                }
                if(a>b) // Si a > b alors on insert et on erase
                {
                    Arete* a2=m_aretes1[j+1];
                    m_aretes1.insert(m_aretes1.begin()+j,a2);
                    m_aretes1.erase(m_aretes1.begin()+(j+2));
                }
            }
        }
    }
    return m_aretes1; //On retourve le vecteur trier
}

std::map<std::string, Arete*> graphe::Kruskal (int v) // Sous-programme pour Kruskal
{
    int poidsTotal1 = 0, poidsTotal2 = 0, compteur=0, z;
    std::map<std::string, Arete*> m_areteg =(this)->GetMapar(); // copie de la map d'aretes
    std::vector <Arete*> m_aretes1 = Tri(m_areteg,v); // Tri du vecteur
    std::vector <std::string > m_vecSommet;
    std::string id=m_aretes1[0]->GetId();
    std::map<std::string, Arete*> m_Kruskal;
    m_Kruskal[id]=m_aretes1[0];
    m_aretes1[0]->SetSelect(true);
    std::string Sommet1=m_aretes1[0]->GetSommet1();
    m_vecSommet.push_back(Sommet1);
    std::string Sommet2=m_aretes1[0]->GetSommet2();
    m_vecSommet.push_back(Sommet2);
    for (size_t i=1; i<m_aretes1.size(); i++) // On parcours les aretes
    {
        Sommet1=m_aretes1[i]->GetSommet1(); // On prend le sommet 1
        Sommet2=m_aretes1[i]->GetSommet2(); // On prend le sommet 2
        z=0;
        for (size_t i=0; i<m_vecSommet.size(); i++) // Pour tous les sommets
        {
            if(m_vecSommet[i]==Sommet1) //Si on trouve le sommet 1
            {
                z+=1; // On ajoute 1
            }
            if(m_vecSommet[i]==Sommet2) // Si on trouve le sommet 2
            {
                z+=2; // On ajoute 2
            }
        }
        if(z==0) // Si il y en a aucuns
        {
            m_aretes1[i]->SetSelect(true);
            m_vecSommet.push_back(Sommet1); // on les push_back
            m_vecSommet.push_back(Sommet2); // on les push_back
            compteur+=1;
        }
        else if(z==1) //
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
        poidsTotal1 += x.second->GetCout1(); // Poids total 1
        poidsTotal2 += x.second->GetCout2(); // Poids total 2
    }
    std::cout<< "resultat ("<<poidsTotal1<< " , "<<poidsTotal2<<")"<<std::endl; // resultat de l'arbre couvrant de poids minimum
    return m_Kruskal; // On retourne  la map
}

graphe::~graphe() // Destructeur
{

}

int choix() // Notre choix de poids
{
    int choix;
    std::cout<<"Veuillez saisir a partir de quelle ponderation voulez-vous lancer l'Algorithme :"<<std::endl;
    std::cin>> choix;
    switch (choix)
    {
        case 1: // Pour le poids 1
            return choix;
            break;
        case 2: // Pour le poids 2
            return choix;
            break;
        default: // par defaut
            std::cout << "Veuillez resaisir, s'il vous plait!"<<std::endl; // resaisir
        return 0;
    }
}

void graphe::dessiner(std::map<std::string, Arete*> Kruskal, int valeur) // Afficher le Kruskal
{
    Svgfile svgout("output.html");
    std::string couleur = "black";
    for (auto x: m_sommets)
    {
        svgout.addDisk(x.second->GetposX(), x.second->GetposY(), 10, couleur); // Affichage des sommets
    }
    for (auto y: Kruskal) // On parcourt la map
    {
        std::string s1 = y.second->GetSommet1();
        std::string s2 = y.second->GetSommet2();
        Sommet* S1 = m_sommets.at(s1);
        Sommet* S2 = m_sommets.at(s2);
        int x1 = S1->GetposX();
        int y1 = S1->GetposY();
        int x2 = S2->GetposX();
        int y2 = S2->GetposY();
        svgout.addLine(x1, y1, x2, y2, couleur); // On affiche les aretes
        if (valeur == 1) // Pour afficher les poids
        {
            float v1 = y.second->GetCout1();
            if(y1 == y2)
            {
                y1 = y1 - 10;
            }
            svgout.addText(((x1+x2)/2)+10, (y1+y2)/2, v1, couleur);
        }
        else if (valeur == 2) //Pour afficher les poids
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

std::vector<std::vector<bool>> graphe::Connexite(std::vector<std::vector<bool>> m_Aretepossible) // Connexite d'un graphe
{
    int k;
    std::vector<std::vector<bool>> m_GrapheFinal;
    Sommet* S1;
    std::map<std::string,Sommet*>m_sommets2=this->GetMapsom();
    std::map<std::string,Arete*>m_aretes2=this->GetMapar();
    std::vector<std::string> m_vecSommet;
    std::vector<Sommet*> lol;
    for(auto y:m_sommets2) //. Parcours  les sommets
    {
        m_vecSommet.push_back(y.first);
    }
    std::vector<Arete*> m_vecArete;
    for(auto z:m_aretes2) // Parcours les aretes
    {
        m_vecArete.push_back(z.second);
    }
    std::string r=m_vecSommet[0];
    for(auto x: m_Aretepossible) // On parcourt les possibilitees
    {
        k=2;
        for(size_t i=0; i<x.size(); i++)
        {
            m_vecArete[(x.size()-1-i)]->SetSelect(x[i]);
        }
        S1=m_sommets.at(r);
        lol=S1->rechercherCC1(m_vecSommet,m_vecArete); // On fait la recherhce des composantes connexes
        for( auto z:m_sommets2)
        {
            if((z.second->GetComposante()) !=1)
            {
                k+=1;
            }
        }
        if(k==2)
        {
            m_GrapheFinal.push_back(x); // on push_back

        }
        for( auto y:m_sommets2)
        {
            y.second->SetComposante(0);
        }
    }
    return m_GrapheFinal; // On retourne une solution avec les 2eme filtre
}

bool *graphe::DecToBin(int n) //ce programme permet de convertir un nb base 10 en base 2 et le retourne
{
    bool *nbBinaire = new bool [32];
    int k=0;
    for(size_t i=0; i<32; i++) //initialisation du tableau
        nbBinaire[i]=0;

    while(n>0) //attribution du chiffre decimal en binaire
    {
        if (n%2==0)
            nbBinaire[k]=0;
        else
            nbBinaire[k]=1;
        n/=2;
        k++;
    }
    return nbBinaire; //on retourne le tableau de booleen
}

std::vector<std::vector<bool>> graphe::compteurbinaire()
{
    std::vector<std::vector<bool>> tab; //vecteur de booleen a 2 dimensions
    int ordre=m_sommets.size();
    int taille=m_aretes.size();
    int nbSol=pow(2,taille); //le nombre de solutions = 2^nb-arete
    int nbArete=0;
    for(int i=0; i<nbSol; ++i) //on realise toutes les solutions possibles
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

std::vector<std::vector<bool>> graphe::compteurbinaireDijskra()
{
    std::vector<std::vector<bool>> tab; //vecteur de booleen a 2 dimensions
    int taille=m_aretes.size();
    int nbSol=pow(2,taille); //le nombre de solutions = 2^nb-arete
    for(int i=0; i<nbSol; ++i) //on realise toutes les solutions possibles
    {
        std::vector <bool> ToutesSol; //tableau temporaire de booleen
        bool *nbBin=DecToBin(i); //conversion base 10 -> base 2
        for(int k=0; k<taille; ++k)
        {
            ToutesSol.push_back(nbBin[k]); // on rempli le tableau temporaire avec toutes les solutions possibles
        }
        tab.push_back(ToutesSol);
        ToutesSol.erase(ToutesSol.begin(), ToutesSol.end()); //on efface le tableau temporaire
    }
    return tab;
}

std::vector<std::vector<bool>> graphe::RechercheSol() // Recherche de solution pour notre fonritere de Pareto
{
    std::vector<std::vector<bool>>Solutiontemp=this->compteurbinaire(); // Comptage en binaire et premier filtre (n-1)ordre
    std::vector<std::vector<bool>>Solutionfin=this->Connexite(Solutiontemp); // 2eme filtre connexite
    return Solutionfin; // On retourne le vecteur de vecteur de booleen apres notre 2eme filtre
}

std::vector<std::vector<bool>> graphe::SolutionFinale(std::vector<std::vector<bool>> solution) // Dernier filtre pour la frontiere de Pareto
{
    double poidsTotal1, poidsTotal2, poidsTotal2_2, poidsTotal1_2;
    std::vector <std::vector<double>> m_vecFin;
    std::vector<double> m_vecPoids;
    std::string s,a;
    std::vector <std::vector<bool>> Solutionfinal;
    int w;
    std::map<std::string,Arete*>m_aretes2=this->GetMapar();
    std::vector<Arete*> m_vecArete;
    for(auto z:m_aretes2)
    {
        m_vecArete.push_back(z.second);
    }
    for (auto x:solution)
    {
        for (size_t i = 0; i<x.size(); ++i)
        {
            m_vecArete[(x.size()-1-i)]->SetSelect(x[i]);
        }
        poidsTotal1=0;
        poidsTotal2=0;
        w=2;
        for(auto y:m_vecArete)
        {
            if(y->GetSelect()==true)
            {
                poidsTotal1 += y->GetCout1();
                poidsTotal2 += y->GetCout2();
            }
        }
        for(auto y:solution)
        {
            poidsTotal2_2=0;
            poidsTotal1_2=0;
            for (size_t i = 0; i<y.size(); ++i)
            {
                m_vecArete[(y.size()-1-i)]->SetSelect(y[i]);
            }
            for(auto z:m_vecArete)
            {
                if(z->GetSelect()==true)
                {
                    poidsTotal1_2 += z->GetCout1();
                    poidsTotal2_2 += z->GetCout2();
                }
            }
            if((poidsTotal1_2<poidsTotal1) && (poidsTotal2_2<poidsTotal2))
            {
                w+=1;
            }
            if((poidsTotal1_2==poidsTotal1) && (poidsTotal2_2<poidsTotal2))
            {
                w+=1;
            }
            if((poidsTotal1_2<poidsTotal1) && (poidsTotal2_2==poidsTotal2))
            {
                w+=1;
            }
        }
        if(w==2)
        {
            Solutionfinal.push_back(x);
        }
    } // Affichage des solutions apres tous les filtres
    std::cout<<"Les Aretes finales sont: "<<std::endl;
    for (auto x:Solutionfinal)
    {
        std::cout<< "Arete : ";
        for (auto y:x)
        {
            std::cout<<y;
        }
        std::cout<<std::endl;
    }
    return(Solutionfinal); // On retourne notre vecteur de vecteur de booleen final
}

void graphe::dessinFrontierePrometo(std::vector<std::vector<bool>> solution, std::vector<std::vector<bool>> solutionF)
{ // Initialisation
    int x1, y1, x3, y3, x4, y4, valeur = 0, longueur = 0, TotalCout1 = 0, TotalCout2 = 0, test;
    double nom = 1;
    Sommet* S1;
    Sommet* S2;
    std::string Poids1 = "cout1";
    std::string Poids2 = "cout2";
    std::string s, s1,s2;
    std::string couleur = "black";
    std::map<std::string,Arete*>m_aretes2=this->GetMapar();
    std::vector<Arete*> m_vecArete;
    Svgfile svgout("output1.html");
    Svgfile frontierePareto("pareto.html");
    frontierePareto.addGrid();
    svgout.addGrid();
    for(auto x: m_aretes) // recherche de la valeur max pour mon graphique
    {
        TotalCout1 += x.second->GetCout1(); // Cout total en cout 1
        TotalCout2 += x.second->GetCout2(); // Cout total en cout 2
    } // Dessin de mon graphique pour acceuillir la frontiere de Pareto
    svgout.addLine(500,700, 500+(TotalCout1*7), 700, couleur); // Axe des abscisses
    svgout.addLine((500+(TotalCout1*7))-50, 700-25,500+(TotalCout1*7), 700, couleur);
    svgout.addLine((500+(TotalCout1*7))-50, 700+25,500+(TotalCout1*7), 700, couleur);
    svgout.addLine(500, 700, 500, 700-(TotalCout2*7), couleur); // Ave des ordonnees
    svgout.addLine(500+25, (700-(TotalCout2*7))+50,500, 700-(TotalCout2*7), couleur);
    svgout.addLine(500-25, (700-(TotalCout2*7))+50,500, 700-(TotalCout2*7), couleur);
    svgout.addText(500+(TotalCout1*7), 720, Poids1, "black");
    svgout.addText(450, 700-(TotalCout2*7), Poids2, "black");
    for(auto z:m_aretes2) // On parcours nos aretes
    {
        m_vecArete.push_back(z.second);
    }
    for(auto x:solution) // On parcrours nos solutions binaires apres tous les filtres
    {
        x1 = 0, y1 = 0;
        for (size_t i = 0; i<x.size(); ++i)
        {
            m_vecArete[(x.size()-1-i)]->SetSelect(x[i]);
        }
        for(auto y:m_vecArete) // On affiche toutes la solutions avant le troisieme filtre pour la fontiere
        {
            if(y->GetSelect()==true) // Si l'arete est en true alors on ajoute la valeur du poids 1 et du poids 2 a nos deux totaux
            {
                x1 += y->GetCout1();
                y1 += y->GetCout2();
                s1 = y->GetSommet1();
            }
        }
        svgout.addDisk(500+(x1*7),700-(y1*7),5, "red", 0, "red");  // Ce sont les cercles rouges
    }
    for(auto x:solutionF) // on parcours nos solutions finales pour la frontiere
    {
        x1 = 0, y1 = 0, x3 = 0, y3 = 0, x4 = 0, y4 =0; // on met tout a zero
        for (size_t i = 0; i<x.size(); ++i)
        {
            m_vecArete[(x.size()-1-i)]->SetSelect(x[i]);
        }
        test = 0;
        for(auto y:m_vecArete) // On parcours les aretes
        {
            if(y->GetSelect()==true) // Si l'arete est selectionne donc que le booleen est egal a 1
            {
                x1 += y->GetCout1(); // pour le coup total pour le cout 1
                y1 += y->GetCout2(); // pour le coup total pour le cout 2
                s1 = y->GetSommet1();
                s2 =y->GetSommet2();
                S1 = m_sommets.at(s1);
                S2 = m_sommets.at(s2);
                x3 = S1->GetposX(); // Position x du premier sommet
                y3 = S1->GetposY(); // Position y du premier sommet
                x4 = S2->GetposX(); // Position x du deuxieme sommet
                y4 = S2->GetposY(); // Position y du deuxieme sommet
                if (test == 0) // Si on a toujours pas donne un indice au graphe qu'on dessine alors on lui en met un
                {
                    frontierePareto.addText(x3+longueur-15, y3+valeur-15, nom, "black");
                    test++; // une fois par graphe
                }
                frontierePareto.addDisk(x3+longueur, y3+valeur, 10, couleur); // Sommet 1
                frontierePareto.addDisk(x4+longueur, y4+valeur, 10, couleur); // Sommet 2
                frontierePareto.addLine(x3+longueur, y3+valeur, x4+longueur, y4+valeur, couleur); // Arete
            }
        }
        valeur+= 400; // Pour que les graphes ne se supperposent pas
        if(((y3+valeur) >= 1800) ||((y4+valeur) >= 1800)) // Pour eviter de depasser de la grille
        {
            longueur += 400;
            valeur = 0;
        }
        svgout.addDisk(500+(x1*7),700-(y1*7),5, "green", 0, "green"); // Point de la fontiere de Pareto
        svgout.addText(500+(x1*7)-15,700-(y1*7)+15, nom, "black"); // Avec leur indice
        nom++; // On incremente a chaque fois
    }
}

double graphe::Dijkstra(std::string Sdepart, std::string Sarrivee, int nbcout,  std::vector<Arete*> m_vecArete)
{


    double distance3=0;

    double minfinal;
    std::vector<Sommet*> markedSommets;
    std::vector<Sommet*> unmarkedSommets;
    double distance2=0;
    std::string soma1;
    std::string soma2;
    float disa1;
    float disa2;


    ///initialisation des sommets : distance min & marque
    for(auto i: m_sommets)
    {
        if(i.second->GetId()==Sdepart)
        {
            ///initialisation de la distance & marque du sommet de départ
            i.second->SetDis(0.0); //distance nul
            i.second->SetMark(true); //marquage du    std::map<std::string, Arete*> m_aretes1=GetMapar();
            markedSommets.push_back(i.second);
        }
        else
        {
            i.second->SetDis(999999.9); //distance très grande (infini)
            i.second->SetMark(false); //marquage des sommets à 0
            unmarkedSommets.push_back(i.second);
        }
    }

    for(auto it : m_vecArete) //parcours de toutes les arêtes
    {

            if(it->GetSelect()==true){

        soma1=it->GetSommet1();
        soma2=it->GetSommet2();
        disa1=it->GetCout1();
        disa2=it->GetCout2();

        if(soma1==Sdepart)
        {
            for(auto itt : m_sommets)
            {
                if(itt.second->GetId()==soma2)
                {
                    itt.second->SetPred(soma1);
                    if(nbcout==1)
                    {
                        itt.second->SetDis(disa1);

                    }
                    if(nbcout==2)
                    {
                        itt.second->SetDis(disa2);

                    }
                }
            }
        }
        if(soma2==Sdepart)
        {
            for(auto itt : m_sommets)
            {
                if(itt.second->GetId()==soma1)
                {
                    itt.second->SetPred(soma2);
                    if(nbcout==1)
                    {
                        itt.second->SetDis(disa1);

                    }
                    if(nbcout==2)
                    {
                        itt.second->SetDis(disa2);

                    }
                }
            }
        }
    }
    }
    while(markedSommets.size()!=m_sommets.size())
    {
        ///recherche de la plus petite distance lié aux voisins du sommet
        double distmin=999999999.9;
        double distance;
        std::string idsomm;

        for(auto unmrk : unmarkedSommets)
        {
            for(auto it : m_sommets)
            {
                if(it.second->GetId()==unmrk->GetId())
                {
                    distance = unmrk->GetDis();
                    if(distance < distmin)
                    {
                        distmin=distance;


                    }
                }
            }
        }

        ///recherche du sommet lié à cette distance minimale
        for(size_t i=0; i<unmarkedSommets.size(); ++i)
        {
            //std::cout<<unmrk2->GetDis()<<" ";
            if(unmarkedSommets[i]->GetDis()==distmin)
            {
                //idsomm=unmrk2->GetId();
                unmarkedSommets[i]->SetMark(true);
                markedSommets.push_back(unmarkedSommets[i]);
                unmarkedSommets.erase(unmarkedSommets.begin()+i);
            }
        }



        for(auto a : m_vecArete)
        {

            if(a->GetSelect()==true){

            if(a->GetSommet1() == (markedSommets[markedSommets.size()-1]->GetId()))
            {
                for(auto it : m_sommets)
                {
                    if(it.second->GetId()==a->GetSommet2())
                    {
                        if(it.second->GetMark()== false)
                        {
                            if(nbcout==1)
                            {

                                distance2=(a->GetCout1())+distmin;

                            }
                            if(nbcout==2)
                            {

                                distance2=(a->GetCout2())+distmin;
                            }

                            if(distance2 < it.second->GetDis())
                            {

                                it.second->SetDis(distance2);
                                it.second->SetPred(markedSommets[markedSommets.size()-1]->GetId());
                            }
                        }
                    }
                }
            }

            if(a->GetSommet2() == (markedSommets[markedSommets.size()-1]->GetId()))
            {
                for(auto it : m_sommets)
                {
                    if(it.second->GetId()==a->GetSommet1())
                    {
                        if(it.second->GetMark()== false)
                        {
                            if(nbcout==1)
                            {
                                distance3=(a->GetCout1())+distmin;
                            }
                            if(nbcout==2)
                            {
                                distance3=(a->GetCout2())+distmin;
                            }
                            if(distance2< it.second->GetDis())
                            {

                                it.second->SetDis(distance3);
                                it.second->SetPred(markedSommets[markedSommets.size()-1]->GetId());
                            }
                        }
                    }
                }
            }
        }
        }
    }


    for(size_t itt=0; itt<markedSommets.size(); ++itt)
    {
        if(markedSommets[itt]->GetId()==Sarrivee)
        {
           minfinal= markedSommets[itt]->GetDis();
           break;
        }

    }
 return  minfinal;

}

std::vector<double> graphe::DijkstraToutSommet(int choix,std::vector<std::vector<bool>> dij)
{
    double distancemin1=0;
    double distancemin2=0;
    std::vector<double> distancegraphes;
    std::map<std::string, Arete*> m_aretes1=GetMapar();
    std::vector<Arete*> m_vecArete;

    for(auto z:m_aretes1)
    {
        m_vecArete.push_back(z.second);
    }

    for(auto z : dij)
    {
distancemin1=0;
distancemin2=0;
    for (size_t i = 0; i<z.size(); ++i)
        {
            m_vecArete[(z.size()-1-i)]->SetSelect(z[i]);
        }

        for(auto x : m_sommets)
        {
        for(auto y : m_sommets)
        {
            if(choix==1){
                distancemin1+=(Dijkstra(x.first, y.first, choix, m_vecArete));}
            if(choix==2){
                distancemin2+=(Dijkstra(x.first, y.first, choix,m_vecArete));}

        }
    }
    if(choix==1){
    distancegraphes.push_back(distancemin1);
    }
    if(choix==2){
    distancegraphes.push_back(distancemin2);
    }
    }


    return distancegraphes;

}



std::vector<std::vector<double>> graphe::RechercheSolDijskra(int choix)
{
    double poidsTotal1;

    std::vector<std::vector<bool>>Solutiontemp=this->compteurbinaireDijskra();


    std::vector<std::vector<bool>>Solutionfin=this->Connexite(Solutiontemp);

    std::vector<double> distancegraphes=DijkstraToutSommet(choix,Solutionfin);

     std::vector <std::vector<double>> Solutionfinal;

    std::vector <std::vector<double>> m_vecFin;
    std::vector<double> m_vecPoids;
      std::string s,a;

   int w;
std::map<std::string,Arete*>m_aretes2=this->GetMapar();

    std::vector<Arete*> m_vecArete;
    for(auto z:m_aretes2)
    {
        m_vecArete.push_back(z.second);
    }

 for (size_t m=0;m<Solutionfin.size();++m)
   {

    for (size_t i = 0; i<Solutionfin[m].size(); ++i)
        {
            m_vecArete[(Solutionfin[m].size()-1-i)]->SetSelect(Solutionfin[m][i]);
        }

        //1->176s
        poidsTotal1=0;


        w=2;

            for(auto y:m_vecArete){
            if(y->GetSelect()==true){
                    if(choix==2){
                poidsTotal1 += y->GetCout1();
                    }
                      if(choix==1){
                poidsTotal1 += y->GetCout2();
            }
            }
            }

       Solutionfinal.push_back({poidsTotal1,distancegraphes[m]});
   }
    std::cout<<"Les Aretes finales sont: "<<std::endl;
    for (auto x:Solutionfinal)
    {
        std::cout<< "Arete: ";

            std::cout<<x[0]<<" "<<x[1];

        std::cout<<std::endl;
    }


    return Solutionfinal; // Modification
}
void graphe::dessinFrontierePrometoDij(std::vector<std::vector<double>> solution)
{

    int x1, y1;
    Svgfile svgout("output1.html");
    Svgfile frontierePareto("pareto.html");
    frontierePareto.addGrid();
    svgout.addGrid();
    int TotalCout1 = 0, TotalCout2 = 0;
    for(auto x: m_aretes)
    {
        TotalCout1 += x.second->GetCout1();
        TotalCout2 += x.second->GetCout2();
    }
    std::string couleur = "black";
    svgout.addLine(500,500, 500+(TotalCout1*7), 500, couleur);
    svgout.addLine((500+(TotalCout1*7))-50, 500-25,500+(TotalCout1*7), 500, couleur);
    svgout.addLine((500+(TotalCout1*7))-50, 500+25,500+(TotalCout1*7), 500, couleur);
    svgout.addLine(500, 500, 500, 500-(TotalCout2*7), couleur);
    svgout.addLine(500+25, (500-(TotalCout1*7))+50,500, 500-(TotalCout2*7), couleur);
    svgout.addLine(500-25, (500-(TotalCout1*7))+50,500, 500-(TotalCout2*7), couleur);
     std::string s, s1,s2;


        for(auto x:solution){
            x1=x[0];
            y1=x[1];

        svgout.addDisk(500+(x1*6),500-(y1),5, "green", 0, "green");
    }
}
