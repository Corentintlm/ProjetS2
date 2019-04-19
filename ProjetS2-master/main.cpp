#include <iostream>
#include"graphe.h"
#include "pareto.h"


int main()
{
    std::string fichier1, fichier2;
    Svgfile svgout;
    Pareto pareto;

    int r;

    std::cout << "saisir les noms des fichiers" << std::endl;
    //std::cin>>fichier1>>fichier2;
    //graphe g{fichier1, fichier2};
    graphe g{"triville.txt", "triville_weights_0.txt"};

    std::cin>>r;

    std::cout << "ok0" << std::endl;
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
