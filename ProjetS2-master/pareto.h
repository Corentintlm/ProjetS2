#ifndef PARETO_H_INCLUDED
#define PARETO_H_INCLUDED
#include"svgfile.h"
#include <vector>

class Pareto
{
public:
    Pareto();
    Pareto(int, int);
    void dessiner(Svgfile& svgout);
    void addPoids(std::vector<float> a);
protected:
    int m_x,m_y;
    std::vector<std::vector<float>> m_poids;
};

#endif // PARETO_H_INCLUDED
