#include "source.h"

graphe::graphe(std::string nomFichier){
    /// Sommet
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string id;
    int x,y;
    for (int i=0; i<ordre; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>x; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.insert({id,new Sommet{id,x,y}});
    }
    /// arrete
    int taille;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    std::string id_voisin;
    int x1, y1;
    for (int i=0; i<taille; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>x1; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y1; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        m_arretes.insert({id,new Sommet{id,x1,y1}});
    }
}

void graphe::afficher() const{ /// Sous-programme d'affichage du fichier charge
    std::cout<<"graphe : "<<std::endl;
    std::cout << "ordre : " << m_sommets.size() << std::endl;
    for ( auto it = m_sommets.begin(); it !=m_sommets.end(); ++it){
        std::cout << "sommet :  ";
        it->second->afficherData();
        std::cout << std::endl;
    }
    for(auto it = m_arretes.begin(); it !=m_arretes.end(); ++it)
    {
        std::cout<< "arretes : ";
        it->second->afficherData();
        std::cout << std::endl;
    }
}

graphe::~graphe()
{

}
