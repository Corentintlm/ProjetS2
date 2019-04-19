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
    float getm_p1();
    float getm_p2();
    int getm_x1();
    int getm_x2();
    int getm_y1();
    int getm_y2();
    int getm_j();
protected:
    int m_j, m_x1, m_x2, m_y1,m_y2;
    float m_p1, m_p2;


};

#endif // ARRETE_H_INCLUDED
