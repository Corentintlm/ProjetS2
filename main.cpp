#include <iostream>
#include"graphe.h"


int main()
{
    std::string fichier1, fichier2;
    Svgfile svgout;
    std::cout << "saisir les noms des fichiers" << std::endl;
    std::cin>>fichier1>>fichier2;
    graphe g{fichier1, fichier2};
    g.dessiner(svgout);
    return 0;
}
