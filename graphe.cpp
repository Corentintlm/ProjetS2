#include <fstream>
#include <iostream>
#include<vector>
#include<algorithm>
#include "graphe.h"

graphe::graphe(std::string fichier1, std::string fichier2)
{
    std::ifstream ifs1{fichier1};//on ouvre les fichiers
    std::ifstream ifs2{fichier2};
    std::vector<int> sommet;
    int ordre;
    ifs1 >> ordre;//on note l'ordre du graphe
    int i, x, y;
    for(int j=0; j<ordre; j++)
    {
        ifs1 >> i;
        sommet.push_back(i);
        ifs1 >> x;
        sommet.push_back(x);//on note les coordoné dans une vecteur pour les transmettre au arrete
        ifs1 >> y;
        sommet.push_back(y);
        m_sommet.push_back( Sommet{i,x,y})//on retient id et les coordoné
    }
    int taille;//on note la taille
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
        x1=sommet[(3*s1)+1];//on recupere les coordonné
        x2=sommet[(3*s2)+1];
        y1=sommet[(3*s1)+2];
        y2=sommet[(3*s2)+2];
        //std::cout<< p1 <<"     "<< p2<<std::endl;
        m_arrete.push_back( Arrete{i,x1,x2,y1,y2,p1,p2});//on stock dans l'atribue

    }
}

void graphe::dessiner(Svgfile& svgout,int r)
{
    size_t j= m_sommet.size();
    size_t k=m_arrete.size();
    for (size_t i =0; i<j ; i++)
    {
        Sommet a=m_sommet[i];//on dessine tout les sommet un par un
        a.dessiner(svgout);
    }
    for(size_t i=0; i<k; i++)
    {
        if(r==0)
        {
            Arrete b=m_arrete[i];//on dessine toute les arrete si il n'y a pas kruskal
            b.dessiner(svgout);
        }
        else
        {
            Arrete b=m_last[i];//on dessine celle qui on était retenu par kruskal
            b.dessiner(svgout);
        }
    }
}

std::vector<Arrete> graphe::kruskalp1()// sous programme de trie pour le poids 1
{
    size_t j=m_arrete.size();
    std::vector<Arrete> arrete2, temp;
    temp=m_arrete;//on ne polus pas notre atribue
    Arrete a{0,0,0,0,0,90,0};
    int p =90;
    int s;
    for(size_t i=0; i<j; i++)//on parcours deux fois les arrete
    {
        for(size_t k=0; k<j; k++)
        {
            if(temp[k].getm_p1()<p)//on cherche la plus petite
            {

                p=temp[k].getm_p1();//on enregistre ca valeur
                s=k;//et sa position
            }

        }
        arrete2.push_back(m_arrete[s]);//on le sauvegarde
        temp[s]=a;//on remplace la valeur enregistré pour ne pas la stocké plusieurs fois
        p=90;//on remet p a une valeur haute
    }
    return arrete2;
}

std::vector<Arrete> graphe::kruskalp2()//idem que pour le poid 1
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

    std::vector<Arrete> arrete2;//on initialise les vecteur
    std::vector<int> sommets;
    if(r==1)//on regarde si on doit fair kruskal sur le poid & ou sur le poid 2
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
    for(size_t i=0; i<j; i++)//boucle qui parcour les arete trier
    {
        std::vector<int>sommets2;
        if(i>1)//pas pour la premiere boucle car la plus petite arrete du graphe apparait forcement
        {
            for (size_t k=0; k<m_sommet.size(); k++)//on cherche les sommet parcouru par l'arete
            {
                if(arrete2[i].getm_x1()==m_sommet[k].getm_x() && arrete2[i].getm_y1()==m_sommet[k].getm_y())
                {
                    s1=m_sommet[k].getm_i();//depart
                }
                if(arrete2[i].getm_x2()==m_sommet[k].getm_x() && arrete2[i].getm_y2()==m_sommet[k].getm_y())
                {
                    s2=m_sommet[k].getm_i();//arrive
                }
            }
            for(size_t k=0; k<sommets.size(); k++)//on verifie si nos sommet on deja était decouvert et si oui combien de fois chacun
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

            if(pres>1)//si c'est le cas on fait une BFS
            {
                if(press1!=0 && press2!=0)
                {

                    sommets2.push_back(s1);//on commence par le sommet de depard
                    for(size_t n=0; n<sommets.size(); n++)
                    {
                        if (n<sommets2.size())
                        {
                            s3=sommets2[n];//sommet temporaire
                        }
                        for(size_t k=0; k<sommets.size(); k++)
                        {

                            if(sommets[k]==s3)//si il est present on fait la BFS
                            {

                                s=0;
                                for(size_t m=0; m<sommets2.size(); m++)//on evite les doublons
                                {
                                    if(sommets2[m]==sommets[k+1])
                                        s=s+1;
                                }
                                if(k%2==0 && s==0)
                                {
                                    sommets2.push_back(sommets[k+1]);//on enregiste le sommet toucher

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
                                verife=verife+1;//on verifie si on a touché le sommet d'arrive ce qui impliquerait une boucle
                            }
                        }

                    }

                }
            }
        }

        if(verife==0)//si il n'y a pas de boucle on stock l'arete et les sommet qu'elle relis
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
        verife=0;//on remet tt a 0
        pres=0;
        press1=0;
        press2=0;
        s1=-1;
        s2=-1;
        s3=-1;
    }


}

void graphe::solution2(Svgfile& svgout,Pareto& pareto)
{
    size_t nba= m_arrete.size();   ///nombre d'arêtes dans broadway_weights 5 18
    size_t n = m_sommet.size();   ///nombre de sommets dans broadway txt 4 10
    size_t i = n-1;
    int cc=0;
    int s = 0;
    int s1 = -1;
    int s2 = -1;

    float poids1 = 0;
    float poids2 = 0;

    std::vector<bool> per(nba,true);
    std::vector<bool> per2(nba,true);
    std::vector<float> vPoids1;
    std::vector<float> vPoids2;
    std::cout<<std::endl;


    for(size_t k=nba; k>i-1; k--)//double boucle pour avoir toutes les solutions admissible
    {
        for(size_t j=0; j<nba-k; j++)
        {
            per[j] = false;
        }

        do
        {
            std::vector<Arrete>arete;
            std::vector<int> sommets2;
            sommets2.push_back(95);
            for(auto i : per)
            {
                std::cout<< i;
            }
            poids1 = 0;
            poids2 = 0;
            for(size_t j = 0; j < nba; j++)
            {

                if(per[j] == 1)
                {


                    int ide = m_arrete[j].getm_j();
                    arete.push_back(m_arrete[ide]);
                    for (size_t k=0; k<m_sommet.size(); k++)
                    {
                        if(m_arrete[ide].getm_x1()==m_sommet[k].getm_x() && m_arrete[ide].getm_y1()==m_sommet[k].getm_y())
                        {
                            s1 = m_sommet[k].getm_i();
                            s = 0;

                            for(size_t i  = 0; i < sommets2.size(); i++)
                            {
                                //std::cout << "ght" << std::endl;
                                if(s1 == sommets2[i])
                                {
                                    s+=1;
                                }
                            }
                            if(s==0)
                            {
                                sommets2.push_back(s1);
                            }
                        }
                        if(m_arrete[ide].getm_x2()==m_sommet[k].getm_x() && m_arrete[ide].getm_y2()==m_sommet[k].getm_y())
                        {
                            //std::cout << "ah yyy" << std::endl;
                            s2 = m_sommet[k].getm_i();
                            //std::cout << "s2 = " << s2 << std::endl;
                            s=0;
                            for(size_t i  = 0; i < sommets2.size(); i++)
                            {
                                if(s2 == sommets2[i])
                                {
                                    s+=1;

                                    //std::cout << "fzrgerget" << std::endl;
                                }
                            }
                            if(s==0)
                            {
                                sommets2.push_back(s2);
                            }
                        }
                        //std::cout << "s = " << s << std::endl;
                    }
                    poids1 += m_arrete[j].getm_p1();

                }

            }
            //std::cout<<"size:"<<sommets2.size()<<std::endl;

            if(sommets2.size()==(m_sommet.size()+1))
            {

                cc+=1;
                poids2=dijkstra(arete);//on fait dijkstra sur le poid 2
                std::cout<<std::endl;
                std::cout<<poids2<<std::endl;
                vPoids1.push_back(poids1);
                vPoids2.push_back(poids2);
            }
            std::cout<<"connexe:"<< cc << std::endl;

        }
        while(std::next_permutation(per.begin(),per.end()));
    }


    for(size_t z=0; z< vPoids1.size(); z ++)
    {
        //std::cout << vPoids1[i] << std::endl;
        std::vector<float> wsh;
        wsh.push_back(vPoids1[z]);
        wsh.push_back(vPoids2[z]);
        pareto.addPoids(wsh);
    }
    std::cin.get();
}
float graphe::dijkstra(std::vector<Arrete>arete)//on recoit les aretes presente dans la solution admissible
{
    std::vector<int>sommets, sommets2;// declaration des vecteurs
    std::vector<int>poids, prec, poids2;
    int s1=-1;//initialisation des variables
    int s2=-1;
    int s3=-1;
    int h=0;
    int p=10000000;
    float P=0;
    for(size_t i=0; i<arete.size(); i++)
    {
        for (size_t k=0; k<m_sommet.size(); k++)// on retrouve les sommets par paire
        {
            if(arete[i].getm_x1()==m_sommet[k].getm_x() && arete[i].getm_y1()==m_sommet[k].getm_y())
            {
                sommets.push_back(m_sommet[k].getm_i());
            }
            if(arete[i].getm_x2()==m_sommet[k].getm_x() && arete[i].getm_y2()==m_sommet[k].getm_y())
            {
                sommets.push_back(m_sommet[k].getm_i());
            }
        }
        poids.push_back(arete[i].getm_p2());//on retrouve les poids dans l'ordre des aretes
        //poids.push_back(0);
    }

    for (size_t z=0; z<m_sommet.size(); z++)//on parcoure les sommets
    {
        s1=m_sommet[z].getm_i();//on prend chaque sommet comme depard
        for (size_t i=0; i<m_sommet.size(); i++)
        {
            s2=m_sommet[i].getm_i();//on prend chaque sommet comme arrivé

            if(s1!=s2)
            {
                std::vector<int>sommets2, prec, poids2;// on reinitialise les vecteur au debut de chaque boucle
                sommets2.push_back(s1);// on met le sommet de depart
                prec.push_back(70);
                poids2.push_back(0);
                h=0;
                for(size_t n=0; n<m_sommet.size(); n++)
                {
                    s3=sommets2[n];// sommet temporaire
                    for(size_t k=0; k<sommets.size(); k++)
                    {

                        if(sommets[k]==s3 && s3!=s2)// on verifie que il n'est pas egalle a l'arrivée
                        {

                            if(h==2)
                            {
                                //std::cout << "aaazazaz" << std::endl;
                                if(k%2==0  && sommets[k+1]!=prec[n])// on regarde si on ne va pas revenir sur nos pas
                                {
                                    sommets2.push_back(sommets[k+1]);//BFS
                                    prec.push_back(s3);//on retiens sont predecesseur
                                    //std::cout << "aaazazaz1111111111" << std::endl;
                                    poids2.push_back(poids[k/2]+poids2[n]);//on additionne les poids

                                }

                                if(k%2!=0  && sommets[k-1]!=prec[n])
                                {
                                    sommets2.push_back(sommets[k-1]);
                                    prec.push_back(s3);
                                    // std::cout << "aaazazaz22222222222" << std::endl;
                                    poids2.push_back(poids[(k-1)/2]+poids2[n]);
                                    // std::cout << "aaazazaz444444444444 " << std::endl;

                                }
                            }
                            if(h==0 || h==1)
                            {

                                if(k%2==0)
                                {
                                    sommets2.push_back(sommets[k+1]);
                                    prec.push_back(s3);
                                    //std::cout << "aaazazaz1111111111&&" << std::endl;
                                    poids2.push_back(poids[k/2]);

                                }

                                if(k%2!=0)
                                {
                                    sommets2.push_back(sommets[k-1]);
                                    prec.push_back(s3);
                                    // std::cout << "aaazazaz22222222222" << std::endl;
                                    poids2.push_back(poids[(k-1)/2]);

                                }
                                h=h+1;
                            }
                        }
                        //h=2;
                    }
                    //std::cout << "aaazazaz6666666666666666" << std::endl;
                }
                p=10000000;
                //std::cout << "gggggggggggggggggggggggggggggggggggggggggggggggg" << std::endl;
                for(size_t m=0; m<poids2.size(); m++)
                {
                    if(poids2[m]<p && sommets2[m]==s2)
                    {
                        p=poids2[m];//on cherche le plus petit poid enrigistré pour l'arrivée
                    }

                }
                P=P+p;
            }
        }


    }
    return P;//on retourne la valeur
}





