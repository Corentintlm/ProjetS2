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
    graphe g{"triville.txt", "triville_weights_0.txt"};

    std::cout << "0 : pas de kruskal" << std::endl;
    std::cout << "1 : kruskal avec poids 1" << std::endl;
    std::cout << "2 : kruskal avec poids 2" << std::endl;

    //std::cin>>r;

    if(r!=0)
    {
        g.kruskal(r);
    }
    std::cout << "kruskal ok" << std::endl;
    std::cout << std::endl;
    g.solution(svgout,pareto);
    std::cout << "solution ok" << std::endl;
    g.dessiner(svgout,r);
    std::cout << "graphe ok" << std::endl;
    pareto.dessiner(svgout);
    std::cout << "graphique ok" << std::endl;
    return 0;
}
