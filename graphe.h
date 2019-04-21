#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include"sommet.h"
#include"svgfile.h"
#include"arrete.h"
#include"pareto.h"
#include<vector>


class graphe
{
public:
    graphe(std::string,std::string);
    void dessiner(Svgfile& svgout,int);
    std::vector<Arrete> kruskalp1();
    std::vector<Arrete> kruskalp2();
    float dijkstra(std::vector<Arrete>);
    void kruskal(int);
    void solution2(Svgfile& svgout,Pareto& pareto);
protected:
    std::vector<Sommet> m_sommet;
    std::vector<Arrete> m_arrete;
    std::vector<Arrete> m_last;
};

#endif // GRAPHE_H_INCLUDED
