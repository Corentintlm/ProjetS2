#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include"svgfile.h"
class Sommet
{
public:
    Sommet(int,int,int);
    void dessiner(Svgfile& svgout);

protected:
    int m_i, m_x,m_y;
};

#endif // SOMMET_H_INCLUDED
