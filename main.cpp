#include "source.h"
#include "sommet.h"
#include "arete.h"
/// Code ecrit par Wassim Sebbahi, Louis Donikian et Teo Rodriguez Nello TD7

//Sous-programme pour laisser a l'utilisateur le choix de choisir le document texte qu'il souhaite
std::vector<std::string> ChoixTxt(graphe g) // il retourne un vecteur de string qui equivaut au nom du fichier texte
{
    std::vector<std::string> choix;
    std::string choixville; // string pour la ville
    std::string choixpoids; // string pour le poids de la ville
    std::cout<<"\n\n\t\tChoisir une ville : ";
    std::cin>>choixville; // l'utilisateur saisit
    choix.push_back(choixville);
    std::cout<<"\n\t\tChoisir un fichier poids : ";
    std::cin>>choixpoids; // l'uitlisateur saisit
    choix.push_back(choixpoids);
    return choix; // oin retourne notre vecteur qui contient le nom de la ville et le poids
}

int main()
{
    int valeur = 0, valeurp = 0; // ce sont nos deux valeurs de choix
    std::map<std::string, Arete*> Kruskal; //notre map apres avoir appliquer Kruskal
    std::vector<std::vector<bool>> Solution; // Vecteur de booleen avec nos solutions intermediaire avant la dernier filtrage
    std::vector<std::vector<bool>> SolutionFinale; // Vecteur de booleen final
    std::vector<std::string> choix1; // Vecteur qui recoit la ville et le poids
    graphe g; // Creation de notre graph
    choix1=ChoixTxt(g); // Choix de la ville et du poids (saisie console)
    g.sommet(choix1[0]+".txt"); // On charge le fichier qui correspond
    g.ponderation(choix1[0]+"_weights_"+choix1[1]+".txt"); // On charge le fichier qui correspond
    g.afficher(); // On affiche le premier chargement avec les sommets (avec coordonnees) et leurs voisins et les aretes
    g.afficherP(); // On affiche les aretes et les poids en fonction du nombre de ponderation
    do // Boucle pour faire notre premier choix pour decider de quel poids nous allons utiliser pour le Kruskal
    {
        valeur = choix(); // On appelle le sous-programme choix qui retourne un int
    } while (valeur == 0); // Condition d'arret du do
    Kruskal = g.Kruskal(valeur); // On applique le Kruskal avec la valeur que nous venons de saisir
    g.dessiner(Kruskal, valeur); // Puis on dessine sur un .html le resultat du Kruskal qui permet de trouver l'arbre couvrant de poids minimum
    system("start output.html"); // On ouvre automatiquement le le fichier
    Solution = g.RechercheSol(); // Apres cela on cherche un moyen d'optimiser les deux poids au maximum possible (retourne un vecteur des graphes non finaux)
    SolutionFinale = g.SolutionFinale(Solution); //On trouve nos graphes finaux qui sont connexes, nbAretes =(n-1)ordres et les poids sont les plus petits possibles
    g.dessinFrontierePrometo(Solution, SolutionFinale); // On dessine cette frontiere de Pareto
    system("start output1.html"); // Ouverture automatique
    std::vector<std::vector<double>> RechercheSolDijskra(int choix);
    std::vector<std::vector<bool>> compteurbinaireDijskra();
    double Dijkstra(std::string Sdepart, std::string Sarrivee, int nbcout,  std::vector<Arete*> m_vecArete);
    std::vector<double> DijkstraToutSommet(int choix,std::vector<std::vector<bool>> dij);
    void dessinFrontierePrometoDij(std::vector<std::vector<double>> solution);
    std::vector<std::vector<double>> Dij;
    do
    {
        valeurp = choix();
    } while (valeurp == 0);
     Dij=g.RechercheSolDijskra(valeurp);
     g.dessinFrontierePrometoDij(Dij);
    return 0;
}

/// Source : Cours de Mme Palasi : http://files.ece.fr/~palasi/ING2/TG/
///Optimum de Pareto : https://fr.wikipedia.org/wiki/Optimum_de_Pareto
/// C++ reference : http://www.cplusplus.com/
/// Support de cours 2018 sur campus : 2017_2018_cours__graphe_ING2%20.pdf

