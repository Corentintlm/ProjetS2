#include <iostream>
#include"graphe.h"


int main()
{
    std::string fichier1, fichier2;
    Svgfile svgout;
    Pareto pareto;
    int r;
    //std::cout << "saisir les noms des fichiers" << std::endl;
    //std::cin>>fichier1>>fichier2;
    //graphe g{fichier1, fichier2};
    graphe g{"broadway.txt","broadway_weights_0.txt"};
    std::cin>>r;
    if(r!=0)
    {
        g.kruskal(r);
    }
    g.dessiner(svgout,r);
    g.solution(svgout,pareto);

    pareto.dessiner(svgout);
    return 0;
}
