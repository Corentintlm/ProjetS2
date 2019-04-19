#include <iostream>
#include"graphe.h"


int main()
{
    std::string fichier1, fichier2;
    Svgfile svgout;
    int r;
    std::cout << "saisir les noms des fichiers" << std::endl;
    std::cin>>fichier1>>fichier2;
    graphe g{fichier1, fichier2};
    std::cin>>r;
    if(r!=0)
    {
        g.kruskal(r);
    }
    g.dessiner(svgout,r);
    return 0;
}
