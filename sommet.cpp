#include "sommet.h"
#include"couleur.h"
#include <iostream>

Sommet::Sommet(int i,int x,int y)
{
    m_i=i;
    m_x=x;
    m_y=y;
}

void Sommet::dessiner(Svgfile& svgout)
{
   Couleur rouge{255,128,128};
   Couleur noir{0,0,0};
   svgout.addDisk(m_x,m_y,15,noir);
   svgout.addText(m_x-20,m_y-20,m_i,rouge);
}
