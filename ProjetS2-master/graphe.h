#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include"sommet.h"
#include "pareto.h"
#include"svgfile.h"
#include"arrete.h"
#include<vector>


class graphe
{
public:
    graphe(std::string,std::string);
    void dessiner(Svgfile& svgout,int);
    std::vector<Arrete> kruskalp1();
    std::vector<Arrete> kruskalp2();
    void kruskal(int);
    void solution(Svgfile& svgout,Pareto& pareto);
protected:
    std::vector<Sommet> m_sommet;
    std::vector<Arrete> m_arrete;
    std::vector<Arrete> m_last;
};

#endif // GRAPHE_H_INCLUDED
