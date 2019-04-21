#include <iostream>
#include"graphe.h"
#include "pareto.h"


int main()
{
    std::string fichier1, fichier2;
    Svgfile svgout;
    Pareto pareto;

    int r = 0;

    std::cout << "saisir les noms des fichiers" << std::endl;
    //std::cin>>fichier1>>fichier2;
    //graphe g{fichier1, fichier2};
    graphe g{"cubetown.txt", "cubetown_weights_0.txt"};

    std::cout << "0 : pas de kruskal" << std::endl;
    std::cout << "1 : kruskal avec poids 1" << std::endl;
    std::cout << "2 : kruskal avec poids 2" << std::endl;

    //std::cin>>r;

    if(r!=0)
    {
        g.kruskal(r);
    }
    std::cout << std::endl;
    g.solution(svgout,pareto);
    g.dessiner(svgout,r);
    pareto.dessiner(svgout);
    return 0;
}
