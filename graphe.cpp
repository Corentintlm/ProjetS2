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
    for(int j=0; j<ordre; j++)
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
    for (int j=0; j<taille ; j++)
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
        //std::cout<< p1 <<"     "<< p2<<std::endl;
        m_arrete.push_back( Arrete{i,x1,x2,y1,y2,p1,p2});

    }
}

void graphe::dessiner(Svgfile& svgout,int r)
{
    size_t j= m_sommet.size();
    size_t k=m_arrete.size();
    for (size_t i =0; i<j ; i++)
    {
        Sommet a=m_sommet[i];
        a.dessiner(svgout);
    }
    for(size_t i=0; i<k; i++)
    {
        if(r==0)
        {
            Arrete b=m_arrete[i];
            b.dessiner(svgout);
        }
        else
        {
            Arrete b=m_last[i];
            b.dessiner(svgout);
        }
    }
}

std::vector<Arrete> graphe::kruskalp1()
{
    size_t j=m_arrete.size();
    std::vector<Arrete> arrete2, temp;
    temp=m_arrete;
    Arrete a{0,0,0,0,0,90,0};
    int p =90;
    int s;
    for(size_t i=0; i<j; i++)
    {
        for(size_t k=0; k<j; k++)
        {
            if(temp[k].getm_p1()<p)
            {

                p=temp[k].getm_p1();
                s=k;
            }

        }
        arrete2.push_back(m_arrete[s]);
        temp[s]=a;
        p=90;
    }
    return arrete2;
}

std::vector<Arrete> graphe::kruskalp2()
{
    size_t j=m_arrete.size();
    std::vector<Arrete> arrete2, temp;
    temp=m_arrete;
    Arrete a{0,0,0,0,0,0,90};
    int p =90;
    int s;
    for(size_t i=0; i<j; i++)
    {
        for(size_t k=0; k<j; k++)
        {
            if(temp[k].getm_p2()<p)
            {

                p=temp[k].getm_p2();

                s=k;
            }
        }
        arrete2.push_back(m_arrete[s]);
        temp[s]=a;
        p=90;
    }
    return arrete2;
}
void graphe::kruskal(int r)

{

    std::vector<Arrete> arrete2;
    std::vector<int> sommets;
    if(r==1)
        arrete2=kruskalp1();
    if(r==2)
        arrete2=kruskalp2();

    int verife=0;
    int pres=0;
    int press1=0;
    int press2=0;


    int s1, s2,s3, s;
    s1=-1;
    s2=-1;
    s3=-1;
    s=0;
    size_t j=arrete2.size();
    for(size_t i=0; i<j; i++)
    {
        std::vector<int>sommets2;
        if(i>1)
        {
            for (size_t k=0; k<m_sommet.size(); k++)
            {
                if(arrete2[i].getm_x1()==m_sommet[k].getm_x() && arrete2[i].getm_y1()==m_sommet[k].getm_y())
                {
                    s1=m_sommet[k].getm_i();
                }
                if(arrete2[i].getm_x2()==m_sommet[k].getm_x() && arrete2[i].getm_y2()==m_sommet[k].getm_y())
                {
                    s2=m_sommet[k].getm_i();
                }
            }
            for(size_t k=0; k<sommets.size(); k++)
            {
                if(sommets[k]==s1)
                {
                    pres=pres+1;
                    press1=press1+1;
                }
                if(sommets[k]==s2)
                {
                    pres=pres+1;
                    press2=press2+1;
                }
            }

            if(pres>1)
            {
                if(press1!=0 && press2!=0)
                {

                    sommets2.push_back(s1);
                    for(size_t n=0; n<sommets.size(); n++)
                    {
                        if (n<sommets2.size())
                        {
                            s3=sommets2[n];
                        }
                        for(size_t k=0; k<sommets.size(); k++)
                        {

                            if(sommets[k]==s3)
                            {

                                s=0;
                                for(size_t m=0; m<sommets2.size(); m++)
                                {
                                    if(sommets2[m]==sommets[k+1])
                                        s=s+1;
                                }
                                if(k%2==0 && s==0)
                                {
                                    sommets2.push_back(sommets[k+1]);

                                }

                                s=0;
                                for(size_t m=0; m<sommets2.size(); m++)
                                {
                                    if(sommets2[m]==sommets[k-1])
                                        s=s+1;
                                }
                                if(k%2!=0 && s==0)
                                {
                                    sommets2.push_back(sommets[k-1]);

                                }
                            }


                        }
                        for(size_t m=0; m<sommets2.size(); m++)
                        {
                            if(sommets2[m]==s2)
                            {
                                verife=verife+1;
                            }
                        }

                    }

                }
            }
        }

        if(verife==0)
        {
            m_last.push_back(arrete2[i]);
            for (size_t k=0; k<m_sommet.size(); k++)
            {
                if(arrete2[i].getm_x1()==m_sommet[k].getm_x() && arrete2[i].getm_y1()==m_sommet[k].getm_y())
                {
                    sommets.push_back(m_sommet[k].getm_i());
                }
                if(arrete2[i].getm_x2()==m_sommet[k].getm_x() && arrete2[i].getm_y2()==m_sommet[k].getm_y())
                {
                    sommets.push_back(m_sommet[k].getm_i());
                }
            }
        }
        verife=0;
        pres=0;
        press1=0;
        press2=0;
        s1=-1;
        s2=-1;
        s3=-1;
        std::cout<<arrete2[i].getm_j()<<":";
        for(size_t m=0; m<sommets2.size(); m++)
        {
            std::cout<<sommets2[m]<<"   ";

        }
        std::cout<<std::endl;
    }
    for(size_t k=0; k<sommets.size(); k++)
    {
        std::cout<<sommets[k]<<"   ";
    }
    std::cout<<sommets[sommets.size()+1];


}

