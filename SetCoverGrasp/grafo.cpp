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

};

/*
typedef struct tList
{
 int v;
 double cost;
}List;

typedef struct tgraph
{
 vector<vector<List> > listAdj;
 vector<int> V;
 vector<double> posX,posY;
 vector<double> sinr;
 vector<double> power;
}Graph;

Graph readGraph(char* arq)
{
  ifstream fileInput;
  Graph G;
  int numVert, links, origin, destiny;
  List element;
  double cost;
  string stringLine;


  fileInput.open(arq,ios::in);

  fileInput >> stringLine;
  while(stringLine.compare("COORD_X_Y")!=0)
   fileInput >> stringLine;

  fileInput >> numVert;

  G.V.resize(numVert);
  G.listAdj.resize(numVert);

  for(int i=0;i<numVert;i++)
   G.V[i] = i;

  fileInput >> stringLine;
  while(stringLine.compare("LINKS_SOURCE_DESTINATION_DISTANCE")!=0)
   fileInput >> stringLine;

  fileInput >> links;
  for(int i=0;i<links;i++)
  {
	fileInput >> origin;
	fileInput >> destiny;
	fileInput >> cost;

	element.v = destiny;
	element.cost = cost;
	G.listAdj[origin].push_back(element);
  }

  fileInput.close();


  return G;
}

void writeDot(char *arq, Graph G)
{
 ofstream fileOut;
 fileOut.open(arq,ofstream::out);
 int u,v;
 double cost;
 vector<int> discovered;

 discovered.resize(G.V.size(),0);

 fileOut << "graph G {" << endl;
 fileOut << "size=\"8.5,11;\"" << endl;
 fileOut << "ratio = \"expand;\"" << endl;
 fileOut << "fixedsize=\"true;\"" << endl;
 fileOut << "overlap=\"scale;\"" << endl;
 fileOut << "node[shape=circle,width=.12,hight=.12,fontsize=12]" << endl;
 fileOut << "edge[fontsize=12]" << endl;
 fileOut << endl;

 for(int i=0;i<G.V.size();i++)
 {
  fileOut << G.V[i] << "[label=\" " << G.V[i] << "\"";
  fileOut << " color=black, pos=\"";
  fileOut << setprecision(8) << G.posX[G.V[i]] << "," << G.posY[G.V[i]];
  fileOut << "!\"];" << endl;
 }

 for(int i=0;i<G.listAdj.size();i++)
 {
  for(int j=0;j<G.listAdj[i].size();j++)
  {
   u = i;
   v = G.listAdj[i][j].v;
   cost = G.listAdj[i][j].cost;

   if(discovered[v]==0)
   {
    fileOut << u << "--" << v << "[label=\"";
    fileOut << setprecision(3) << cost << "\"]" << endl;
   }
   discovered[u]=1;
  }
 }


 fileOut << endl;


 fileOut << "}" << endl;
 fileOut.close();
}

void graphOutput(char *arq, Graph G)
{
 string comandSys;

 comandSys = "dot -s -n -Tps ";
 comandSys += arq;
 comandSys += " -o ";
 comandSys += arq;
 comandSys += ".ps";
 writeDot(arq, G);

 system(comandSys.data());

}
*/
#endif
