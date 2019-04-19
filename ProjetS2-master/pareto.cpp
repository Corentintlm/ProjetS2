#include "pareto.h"
#include"couleur.h"
#include <iostream>

Pareto::Pareto(int x, int y)
{
    m_x=x;
    m_y=y;
}
Pareto::Pareto()
{

}

void Pareto::addPoids(std::vector<float> a)
{
    m_poids.push_back(a);
}

void Pareto::dessiner(Svgfile& svgout)
{
    Couleur noir{0,0,0};
    svgout.addLine(500, 100, 500, 400, noir);
    svgout.addLine(500, 400, 800, 400, "blue");

    int t = 0;
    int i = 0;


        //std::cout << "kkkoko" << std::endl;
        for(auto yo : m_poids)
        {
            if(yo[i+1] > t)
            {
             //   std::cout << "aaazazaz" << std::endl;
                t = yo[i+1];
            }
            i+=2;
        }


    //std::cout << "le plus haut : " << t << std::endl;
    i=0;
    for(auto yo : m_poids)
    {
        svgout.addDisk(yo[i]*10+100, (-yo[i+1] + t + 1)*10+300,1,noir);

        //std::cout << yo[i] << yo[i+1] << std::endl;
        //std::cout << "yo = " << yo[0] << " et y = " << 100+yo[1]*10 <<
        //                                       " ensuite y = " << 250-t << std::endl;
        i+=2;
    }
}
