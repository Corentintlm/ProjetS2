#include <fstream>
#include <iostream>
#include<vector>
#include "graphe.h"

graphe::graphe(std::string fichier1, std::string fichier2)
{
    std::ifstream ifs1{fichier1};
    std::ifstream ifs2{fichier2};
    std::vector<int> sommet;
    int ordre;
    ifs1 >> ordre;
    int i, x, y;
    for(int j=0; j<ordre;j++)
    {
        ifs1 >> i;
        sommet.push_back(i);
        ifs1 >> x;
        sommet.push_back(x);
        ifs1 >> y;
        sommet.push_back(y);
        m_sommet.push_back( Sommet{i,x,y});
    }
    int taille;
    ifs1 >> taille;
    int p;// poubelle
    int s1, s2, x1,x2,y1,y2;
    float p1, p2;
    ifs2 >> p;
    ifs2 >> p;
    for (int j=0;j<taille ;j++)
    {
        ifs1 >> i;
        ifs1 >> s1;
        ifs1 >> s2;
        ifs2 >> p;
        ifs2 >> p1;
        ifs2 >> p2;
        x1=sommet[(3*s1)+1];
        x2=sommet[(3*s2)+1];
        y1=sommet[(3*s1)+2];
        y2=sommet[(3*s2)+2];
        std::cout<< p1 <<"     "<< p2<<std::endl;
        m_arrete.push_back( Arrete{i,x1,x2,y1,y2,p1,p2});

    }
}

void graphe::dessiner(Svgfile& svgout)
{
    size_t j= m_sommet.size();
    size_t k=m_arrete.size();
    for (size_t i =0; i<j ;i++)
    {
        Sommet a=m_sommet[i];
        a.dessiner(svgout);
    }
    for(size_t i=0; i<k;i++)
    {
        Arrete b=m_arrete[i];
        b.dessiner(svgout);
    }
}
