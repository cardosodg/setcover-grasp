#ifndef GRAFO_CPP
#define GRAFO_CPP

#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <limits.h>
#include <queue>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <sstream>

class ElementoLista{
public:
	/*--------------*/
	/* Atributos    */
	/*--------------*/
	int i_aID;                              /* Identificação do nó            */
	float f_aCusto;                         /* Custo do arco do nó            */

	ElementoLista(){}
    ~ElementoLista(){}

};

class Grafo{
public:
	/*--------------*/
	/* Atributos    */
	/*--------------*/
	std::vector<int> v_aListaNos;				             /* Lista dos nós da rede          */
	std::vector<float> v_aCoordX;                            /* Coordenada no eixo x           */
    std::vector<float> v_aCoordY;                            /* Coordenada no eixo y           */
    std::vector<std::vector<ElementoLista> > l_aListaAdj;    /* Lista de adjacência do grafo   */

    Grafo(){}
    ~Grafo(){
    	v_aListaNos.clear();
    	v_aCoordX.clear();
    	v_aCoordY.clear();
    	for(int i_wIt=0;i_wIt<l_aListaAdj.size();i_wIt++)
            l_aListaAdj[i_wIt].clear();
    }

    void LeArquivoGrafo (char* s_pNomeArquivo)
    {
        int i_wNumVert;
        int i_wNumLinks;
        int i_wOrigem;
        ElementoLista o_wElementoLista;
        std::string s_wLinhaArquivo;
        std::ifstream f_wArquivoGrafo;

        f_wArquivoGrafo.open(s_pNomeArquivo);

        f_wArquivoGrafo >> s_wLinhaArquivo;
        while(s_wLinhaArquivo.compare("COORD_X_Y")!=0)
            f_wArquivoGrafo >> s_wLinhaArquivo;

        f_wArquivoGrafo >> i_wNumVert;

        v_aListaNos.resize(i_wNumVert);
        v_aCoordX.resize(i_wNumVert);
        v_aCoordY.resize(i_wNumVert);
        l_aListaAdj.resize(i_wNumVert);

        for(int i_wIt = 0; i_wIt < i_wNumVert; i_wIt++)
        {
            f_wArquivoGrafo >> v_aCoordX[i_wIt] >> v_aCoordY[i_wIt];
            v_aListaNos[i_wIt] = i_wIt;
        }

        f_wArquivoGrafo >> s_wLinhaArquivo;
        while(s_wLinhaArquivo.compare("LINKS_SOURCE_DESTINATION_DISTANCE")!=0)
            f_wArquivoGrafo >> s_wLinhaArquivo;

        f_wArquivoGrafo >> i_wNumLinks;

        for(int i_wIt = 0; i_wIt < i_wNumLinks; i_wIt++)
        {
            f_wArquivoGrafo >> i_wOrigem >> o_wElementoLista.i_aID >> o_wElementoLista.f_aCusto;
            l_aListaAdj[i_wOrigem].push_back(o_wElementoLista);
        }

        f_wArquivoGrafo.close();
    }

    void ImprimeGrafo()
    {
        for (int i=0;i<v_aCoordX.size();i++)
            std::cout << i << " " << v_aCoordX[i] << " " << v_aCoordY[i] << std::endl;

        for (int i=0;i<l_aListaAdj.size();i++)
            for (int j=0;j<l_aListaAdj[i].size();j++)
                std::cout << i << " " << l_aListaAdj[i][j].i_aID << " " << l_aListaAdj[i][j].f_aCusto << std::endl;
    }

    void Dijkstra (int &saci, MatrizEsparsa &matriz)
    {
        saci = 500;
        matriz.f_aFuncaoObjetivo = 200.0;
    }

};

#endif
