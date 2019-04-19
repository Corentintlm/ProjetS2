#include"arrete.h"
#include<iostream>
#include"couleur.h"
Arrete::Arrete(int j, int x1, int x2,int y1,int y2,float p1, float p2)
{
    m_j=j;
    m_x1=x1;
    m_x2=x2;
    m_y1=y1;
    m_y2=y2;
    m_p1=p1;
    m_p2=p2;
}

void Arrete::dessiner(Svgfile& svgout)
{
   Couleur vert{128,255,128};
   Couleur noir {0,0,0};
   svgout.addLine(m_x1,m_y1,m_x2,m_y2,noir);
   int x=((m_x1+m_x2)/2);
   int y=((m_y1+m_y2)/2);
   //svgout.addText(x-20,y+10,m_p1,noir);
   //svgout.addText(x-20,y-15,m_p2,noir);
   svgout.addText(x,y,m_j,vert);
}


float Arrete::getm_p1()
{
    return m_p1;
}
float Arrete::getm_p2()
{
    return m_p2;
}
int Arrete::getm_x1()
{
    return m_x1;
}
int Arrete::getm_x2()
{
    return m_x2;
}
int Arrete::getm_y1()
{
    return m_y1;
}
int Arrete::getm_y2()
{
    return m_y2;
}
int Arrete::getm_j()
{
    return m_j;
}
