#include <time.h>
#include "Graph.cpp"
using namespace std;

bool pesquisaValor(vector<double> posX, vector<double> posY, double posx, double posy)
{
 bool encontrouX,encontrouY;
 
 for(int i=0;i<posX.size();i++)
 {
  if (abs(posX[i]-posx)<0.000001)
  {
   encontrouX=true;
   break;
  }
  encontrouX=false;
 }

 for(int i=0;i<posY.size();i++)
 {
  if (abs(posY[i]-posy)<0.000001)
  {
   encontrouY=true;
   break;
  }
  encontrouY=false;
 }

 if ((encontrouX)&&(encontrouY))
  return true;
 else
  return false;

}

Graph criaGrafo(int qtdNos)
{
 Graph G;
 double posx,posy,normaliza;
 int i;

 G.V.resize(qtdNos);
 G.posX.resize(qtdNos);
 G.posY.resize(qtdNos);
 G.listAdj.resize(qtdNos);

 i=0;
 while(i!=qtdNos)
 {
  normaliza = ((double)rand()/RAND_MAX);
  posx = ((double)(rand()%3)+normaliza);
  
  normaliza = ((double)rand()/RAND_MAX);
  posy = ((double)(rand()%3)+normaliza);
  
  G.V[i]=i;
  
  //if(!pesquisaValor(G.posX,G.posY,posx,posy))
  //{
   G.posX[i]=posx;
   G.posY[i]=posy;
   i++;
  //}
 }

 return G;
}

Graph insereArestas(Graph G)
{
 double valAresta;
 int origem = 0;
 List elemento;
 
 valAresta = 1;
 
 for(int i=1;i<G.V.size();i++)
 {
	 origem = rand()%i;
	 elemento.v = G.V[i];
	 elemento.cost = valAresta;
	 G.listAdj[origem].push_back(elemento);
	 
	 int swap = elemento.v;
	 elemento.v = origem;
	 origem = swap;
	 G.listAdj[origem].push_back(elemento);
 }
 
return G;
}

void mostrar(vector<double> vet)
{
	for(int i=0;i<vet.size();i++)
	 cout << vet[i] << " ";
	cout << endl;
}

string montaNomeArquivo(int numVert, int posInst)
{
	string saida;
	stringstream arqNumeracao;
	string arqBfsPre = "instBFS_";
	string arqBfsPos = ".txt";
	
	saida.clear();
	arqNumeracao.seekp(0);
	arqNumeracao << numVert << "_" << posInst;
	saida = arqBfsPre;
	saida += arqNumeracao.str();
	saida += arqBfsPos;
	
	return saida;
}

void escreveSaida (string saida, Graph G)
{
	fstream arquivoSaida;
	string headerListAdj = "LINKS_SOURCE_DESTINATION_DISTANCE";
	string headerCoord = "COORD_X_Y";
	int links = 0;
	
	arquivoSaida.open(saida.data(),ios::out);
	
	arquivoSaida << headerCoord << " " << G.V.size() << endl;
	for(int i=0;i<G.posX.size();i++)
	 arquivoSaida << setw(9) << G.posX[i] << " " << setw(9) << G.posY[i] << endl;
	
	for(int i=0;i<G.listAdj.size();i++)
	 links += G.listAdj[i].size();
	arquivoSaida << headerListAdj << " " << links << endl;
	for(int i=0;i<G.listAdj.size();i++)
	 for(int j=0;j<G.listAdj[i].size();j++)
	  arquivoSaida << setw(6) << i << " " << setw(6) << G.listAdj[i][j].v << " " << setw(6) << G.listAdj[i][j].cost << endl;
	
	arquivoSaida.close();
}

main(int argc, char** argv)
{
	string nomeArquivoSaida, nomeArquivoGraphviz;
	fstream config;
	Graph G;
	int linhas, numInst, numVert, seed;
	
	seed = atoi(argv[1]);
	srand(seed);
	
	
	config.open(argv[2],ios::in);
	
	config >> linhas;
	
	for(int i=0;i<linhas;i++)
	{
		config >> numInst;
		config >> numVert;
		
		for(int j=0;j<numInst;j++)
		{
			cout << "gerando instancia " << j << " de " << numVert << " vertices." << endl;
			G = criaGrafo(numVert);
			G = insereArestas(G);
			
			nomeArquivoSaida = montaNomeArquivo(numVert,j);
			escreveSaida(nomeArquivoSaida,G);
			
			
			nomeArquivoGraphviz = nomeArquivoSaida + ".dot";
			graphOutput(strdup(nomeArquivoGraphviz.c_str()),G);
		}
	}
	
	config.close();
}
