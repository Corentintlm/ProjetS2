#ifndef ARRETE_H_INCLUDED
#define ARRETE_H_INCLUDED
#include"svgfile.h"
#include<vector>
#include "sommet.h"
class Arrete
{
public:
    Arrete(int,int,int,int,int,float,float);
    void dessiner(Svgfile& svgout);
protected:
    int m_j, m_x1, m_x2, m_y1,m_y2;
    float m_p1, m_p2;
};

#endif // ARRETE_H_INCLUDED
