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

    int plusGrandY = 0;
    int plusGrandX = 0;
    int plusPetitY = 200;
    int plusPetitX = 200;
    int i = 0;


    //std::cout << "kkkoko" << std::endl;
    for(auto yo : m_poids)
    {
        if(yo[i+1] > plusGrandY)
        {
         //   std::cout << "aaazazaz" << std::endl;
            plusGrandY = yo[i+1];
        }
        i+=2;
    }
    i = 0;
    for(auto yo : m_poids)
    {
        if(yo[i+1] < plusPetitY)
        {
         //   std::cout << "aaazazaz" << std::endl;
            plusPetitY = yo[i+1];
        }
        i+=2;
    }
    i = 0;
    for(auto yo : m_poids)
    {
        if(yo[i] < plusPetitX)
        {
         //   std::cout << "aaazazaz" << std::endl;
            plusPetitX = yo[i];
        }
        i+=2;
    }
    i = 0;
    for(auto yo : m_poids)
    {
        if(yo[i] > plusGrandX)
        {
         //   std::cout << "aaazazaz" << std::endl;
            plusGrandX = yo[i];
        }
        i+=2;
    }
/*
    plusGrandX*=10;
    plusGrandY*=10;
    plusPetitX*=10;
    plusPetitY*=10; */

    Couleur noir{0,0,0};
    svgout.addLine(500, 100, 500, 400, noir);    //ordonnée
    svgout.addTriangle(500, 90, 495, 100, 505, 100, noir);
    svgout.addLine(500, 400, (500/plusPetitX)*plusGrandX+50, 400, "blue");  //abscisse
    svgout.addTriangle((500/plusPetitX)*plusGrandX+60-25, 400, 50+(500/plusPetitX)*plusGrandX-25, 395, 50+(500/plusPetitX)*plusGrandX-25, 405, "blue");
    std::cout << (plusGrandX*500)+10 << " " << 400 << std::endl;
    std::cout << (plusGrandX*500) << " " << 395 << std::endl;
    std::cout << (plusGrandX*500) << " " << 405 << std::endl;



    //std::cout << "le plus haut : " << t << std::endl;
    i=0;

    std::cout << "plus grand y : " << plusGrandY << std::endl;

    int fe1 = 0;
    int fe2 = 0;

    std::vector<int> optimium;

    i = 0;
    int l = 0;
    int bzje = 0;
    int compt = 0;
    for(auto ez : m_poids)
    {
        bzje++;
        fe1 = ez[i];
        fe2 = ez[i+1];
        for(auto gg : m_poids)
        {
            if((fe1 <= gg[l]) || (fe2 <= gg[l+1]))
            {
                compt+=1;
            }
            else
                break;
            l+=2;
            //std::cout << bzje << std::endl;
        }
        l=0;
        if(compt == m_poids.size()-1)
        {
            //std::cout << "compt : " << compt << "poids size : " << m_poids.size() << std::endl;
            svgout.addDisk((500/plusPetitX)*ez[i]+50, ((-ez[i+1] + plusPetitY)*10) + 370, 5, "green");
            int op = 0;
            op++;
            std::cout << op << std::endl;
        }
        else
            svgout.addDisk((500/plusPetitX)*ez[i]+50, ((-ez[i+1] + plusPetitY)*10) + 370, 3, "red");
        compt = 0;
        i+=2;
    }
    //std::cout << "hey" << std::endl;
}
