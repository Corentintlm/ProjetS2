#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include"sommet.h"
#include"svgfile.h"
#include"arrete.h"
#include<vector>


class graphe
{
public:
    graphe(std::string,std::string);
    void dessiner(Svgfile& svgout);
protected:
    std::vector<Sommet> m_sommet;
    std::vector<Arrete> m_arrete;
};

#endif // GRAPHE_H_INCLUDED
