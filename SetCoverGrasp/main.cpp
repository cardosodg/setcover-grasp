/*------------------------------------*/
/* Includes                           */
/*------------------------------------*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>
#include <dirent.h>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>

/*------------------------------------*/
/* Define                             */
/*------------------------------------*/
#define EPS 1.0
#define EXTENSAO "png"

/*------------------------------------*/
/* Namespaces                         */
/*------------------------------------*/


/*------------------------------------*/
/* Classes                            */
/*------------------------------------*/
class Linha;
class Coluna;
class Vertice;
class Grafo;

class Coluna{
public:
	/*--------------*/
	/* Atributos    */
	/*--------------*/
	int i_aID;                          /* ID do nó                                           */
	int i_aLinhasCobertas = 0;			/* Quantidade de linhas que a coluna cobre no momento */
	float f_aCusto = 1.0;               /* Custo da coluna                                    */
	bool b_aSelecionada = false;        /* Indica se a coluna foi selecionada                 */
	std::vector<Linha*> v_aLinhas;		/* Linhas cobertas pela coluna                        */

	/*--------------*/
	/* Construtores */
	/*--------------*/
	//TODO: Ver como criar e deletar para não ter vazamento de memória
	Coluna(){}
	Coluna(int i_pID){
		i_aID = i_pID;
	}
	Coluna(Coluna * other){
		i_aID = other->i_aID;
		i_aLinhasCobertas = other->i_aLinhasCobertas;
		f_aCusto = other->f_aCusto;
		b_aSelecionada = other->b_aSelecionada;
	}
	~Coluna(){
		// Clear the vector
		v_aLinhas.clear();
	}

	/*--------------*/
	/* Métodos      */
	/*--------------*/

	/*-----------------------------------------------------------*/
	/* Método AddLinha                                           */
	/*   Adiciona uma linha que a coluna cobre                   */
	/* Parâmetros                                                */
	/*   Coluna* p_pLinha - input  - Ponteiro para uma coluna    */
	/*-----------------------------------------------------------*/
	void AddLinha(Linha * p_pLinha){
		v_aLinhas.push_back(p_pLinha);
		i_aLinhasCobertas++;
	}

	/*--------------------------------------------------------------*/
	/* Método CobreLinhas											*/
	/*   Realiza a corbertura das linhas apontadas pela coluna		*/
	/*    passada como parâmetro									*/
	/* Parâmetros                                                   */
	/*   int i_pIndiceColuna - input - Índice da coluna selecionada */
	/*--------------------------------------------------------------*/
	//void CobreLinhas(){
	//	int i_wI;

	//	for (i_wI = 0; i_wI < v_aLinhas.size(); i_wI++){
	//		v_aLinhas[i_wI]->CobreLinha();
	//	}

	//}

};

class Linha{
public:
	/*--------------*/
	/* Atributos    */
	/*--------------*/
	int i_aOrigem;						/* Origem do Caminho              */
	int i_aDestino;						/* Destino do Caminho             */
	float f_aGanho = 1 + EPS;           /* Ganho da linha                 */
	bool b_aCoberta = false;			/* Indica se a linha está coberta */
	std::vector<Coluna*> v_aColunas;	/* Colunas que cobrem a linha     */


	/*--------------*/
	/* Construtores */
	/*--------------*/
	//TODO: Ver como criar e deletar para não ter vazamento de memória
	Linha(){}
	Linha(int i_pOrigem, int i_pDestino){
		i_aOrigem = i_pOrigem;
		i_aDestino = i_pDestino;
	}
	Linha(Linha * other){
		i_aOrigem = other->i_aOrigem;
		i_aDestino = other->i_aDestino;
		f_aGanho = other->f_aGanho;
		b_aCoberta = other->b_aCoberta;
	}
	~Linha(){
		v_aColunas.clear();
	}

	/*--------------*/
	/* Métodos      */
	/*--------------*/

	/*-----------------------------------------------------------*/
	/* Método AddColuna                                          */
	/*   Adiciona uma coluna que cobre a linha                   */
	/* Parâmetros                                                */
	/*   Coluna* p_pColuna - input  - Ponteiro para uma coluna   */
	/*-----------------------------------------------------------*/
	void AddColuna(Coluna * p_pColuna){
		v_aColunas.push_back(p_pColuna);
	}

	/*--------------------------------------------------------------*/
	/* Método CobreLinha											*/
	/*   Realiza a corbertura da linha e atualiza colunas que		*/
	/*    cobrem a linha         									*/
	/* Parâmetros                                                   */
	/*   int i_pIndiceColuna - input - Índice da coluna selecionada */
	/*--------------------------------------------------------------*/
	//void CobreLinha(){
	//	int i_wI;
	//	if (!b_aCoberta){
	//		for (i_wI = 0; i_wI < v_aColunas.size(); i_wI++){
	//			v_aColunas[i_wI]->i_aLinhasCobertas--;
	//		}
	//	}
	//	b_aCoberta = true;
	//}
};


class Vertice{
public:
	/*--------------*/
	/* Atributos    */
	/*--------------*/
	int i_aID;                              /* Identificação do nó             */
	int i_aDistancia;                       /* Distancia do vértice até a raíz */
	int i_aPai;                             /* Predecessor do nó               */
	int f_aCusto;                         /* Custo do arco do nó             */

	Vertice(){}
	~Vertice(){}

};


class Grafo{
public:
	/*--------------*/
	/* Atributos    */
	/*--------------*/
	std::vector<Vertice> v_aListaVertice;		             /* Lista dos nós da rede               */
	std::vector<float> v_aCoordX;                            /* Coordenada no eixo x                */
	std::vector<float> v_aCoordY;                            /* Coordenada no eixo y                */
	std::vector<std::vector<Vertice> > l_aListaAdj;          /* Lista de adjacência do grafo        */
	std::vector<std::vector<Vertice> > v_aArvores;           /* Árvore resultado do dijkstra por nó */

	Grafo(){}
	~Grafo(){
		v_aListaVertice.clear();
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
		Vertice o_wVertex;
		std::string s_wLinhaArquivo;
		std::ifstream f_wArquivoGrafo;

		f_wArquivoGrafo.open(s_pNomeArquivo);

		f_wArquivoGrafo >> s_wLinhaArquivo;
		while(s_wLinhaArquivo.compare("COORD_X_Y")!=0)
			f_wArquivoGrafo >> s_wLinhaArquivo;

		f_wArquivoGrafo >> i_wNumVert;

		v_aListaVertice.resize(i_wNumVert);
		v_aCoordX.resize(i_wNumVert);
		v_aCoordY.resize(i_wNumVert);
		l_aListaAdj.resize(i_wNumVert);

		for(int i_wIt = 0; i_wIt < i_wNumVert; i_wIt++)
		{
			f_wArquivoGrafo >> v_aCoordX[i_wIt] >> v_aCoordY[i_wIt];
			v_aListaVertice[i_wIt].i_aID = i_wIt;
		}

		f_wArquivoGrafo >> s_wLinhaArquivo;
		while(s_wLinhaArquivo.compare("LINKS_SOURCE_DESTINATION_DISTANCE")!=0)
			f_wArquivoGrafo >> s_wLinhaArquivo;

		f_wArquivoGrafo >> i_wNumLinks;

		for(int i_wIt = 0; i_wIt < i_wNumLinks; i_wIt++)
		{
			f_wArquivoGrafo >> i_wOrigem >> o_wVertex.i_aID >> o_wVertex.f_aCusto;
			l_aListaAdj[i_wOrigem].push_back(o_wVertex);
			v_aListaVertice[o_wVertex.i_aID].f_aCusto = o_wVertex.f_aCusto;
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

	static bool ComparadorVertices (Vertice &v1, Vertice &v2)
	{
		return v1.i_aDistancia < v2.i_aDistancia;
	}

	static bool ComparadorVerticesID (Vertice &v1, Vertice &v2)
	{
		return v1.i_aID < v2.i_aID;
	}

	Vertice ExtrairVertice(std::vector<Vertice> &v_pListaVerticeQ, float f_pAlpha, int i_pControleLCR)
	{
		int i_wTamanhoListaLCR;
		int i_wElementoEscolhido;
		Vertice i_wVerticeEscolhido;
		std::sort(v_pListaVerticeQ.begin(),v_pListaVerticeQ.end(),ComparadorVertices);

		i_wTamanhoListaLCR = f_pAlpha*(i_pControleLCR - 1);
		if (i_wTamanhoListaLCR == 0) i_wTamanhoListaLCR = 1;

		i_wElementoEscolhido = rand()%i_wTamanhoListaLCR;

		i_wVerticeEscolhido = v_pListaVerticeQ[i_wElementoEscolhido];

		std::swap(v_pListaVerticeQ[i_wElementoEscolhido], v_pListaVerticeQ[v_pListaVerticeQ.size()-1]);

		v_pListaVerticeQ.pop_back();

		return i_wVerticeEscolhido;
	}

	void ImprimeGraphviz(int i_pID)
	{
		std::stringstream stringArquivoSaida;
		std::string stringComandoSistema;
		std::ofstream f_ArquivoSaida;

		stringArquivoSaida << "saida" << i_pID << ".dot";
		stringComandoSistema = "dot -Tpng " + stringArquivoSaida.str() + " -o " + stringArquivoSaida.str() + ".png";

		f_ArquivoSaida.open(stringArquivoSaida.str().data());

		f_ArquivoSaida << "strict graph G {\n";

		for(int i=0;i<v_aArvores[i_pID].size();i++)
		{
			if(v_aArvores[i_pID][i].i_aPai != -1)
				f_ArquivoSaida << v_aArvores[i_pID][i].i_aID << " -- " << v_aArvores[i_pID][i].i_aPai << std::endl;
		}

		f_ArquivoSaida << "\n}\n";

		f_ArquivoSaida.close();

		system(stringComandoSistema.data());
	}

	void ImprimeArvoresGraphviz()
	{
		for(int i=0;i<v_aListaVertice.size();i++)
		{
			ImprimeGraphviz(i);
		}
	}

	void Dijkstra (float f_pAlpha, Vertice o_pS)
	{
		int i_wControleLCR;
		Vertice o_wU;
		std::vector<Vertice> v_wListaVerticeQ;
			std::vector<Vertice> v_wArvore;
		std::vector<std::vector<Vertice> > l_wAdj;

		v_wArvore.clear();
		v_wListaVerticeQ = v_aListaVertice;
		l_wAdj = l_aListaAdj;

		for(int i_wI = 0; i_wI < v_wListaVerticeQ.size();i_wI++)
		{
			if (v_wListaVerticeQ[i_wI].i_aID != o_pS.i_aID) v_wListaVerticeQ[i_wI].i_aDistancia = l_wAdj.size()*1000;
			else v_wListaVerticeQ[i_wI].i_aDistancia = 0;
			v_wListaVerticeQ[i_wI].i_aPai = -1;
		}

		i_wControleLCR = 1;
		while(!v_wListaVerticeQ.empty())
		{
			o_wU = ExtrairVertice(v_wListaVerticeQ, f_pAlpha, i_wControleLCR);
			i_wControleLCR--;

			v_wArvore.push_back(o_wU);

			for(int i_wI = 0; i_wI < l_wAdj[o_wU.i_aID].size();i_wI++)
			{
				Vertice o_wV1 = l_wAdj[o_wU.i_aID][i_wI];

				for(int i_wJ=0; i_wJ < v_wListaVerticeQ.size();i_wJ++)
				{
					Vertice o_wV2 = v_wListaVerticeQ[i_wJ];

					if((o_wV1.i_aID == o_wV2.i_aID)&&(o_wV2.i_aDistancia > o_wU.i_aDistancia + o_wU.f_aCusto))
					{
						v_wListaVerticeQ[i_wJ].i_aDistancia = o_wU.i_aDistancia + o_wU.f_aCusto;
						v_wListaVerticeQ[i_wJ].i_aPai = o_wU.i_aID;
						i_wControleLCR++;
					}
				}
			}
		}
		std::sort(v_wArvore.begin(),v_wArvore.end(),ComparadorVerticesID);
		v_aArvores.push_back(v_wArvore);
	}

	void DijkstraTodosVertices(float f_pAlpha)
	{
		for (int i=0;i<v_aListaVertice.size();i++)
			Dijkstra(f_pAlpha, v_aListaVertice[i]);
	}

	std::vector<Vertice> MontaCaminho (int i_pOrigem, int i_pDestino)
	{
		Vertice o_wVertice;
		std::vector<Vertice> v_wCaminhoOriDest;
		std::vector<Vertice> v_wCaminhoDestOri;

		o_wVertice = v_aArvores[i_pOrigem][i_pDestino];
		while(o_wVertice.i_aPai != -1)
		{
			v_wCaminhoOriDest.push_back(o_wVertice);
			o_wVertice = v_aArvores[i_pOrigem][o_wVertice.i_aPai];
		}
		v_wCaminhoOriDest.push_back(o_wVertice);

		o_wVertice = v_aArvores[i_pDestino][i_pOrigem];
		while(o_wVertice.i_aPai != -1)
		{
			v_wCaminhoDestOri.push_back(o_wVertice);
			o_wVertice = v_aArvores[i_pDestino][o_wVertice.i_aPai];
		}
		v_wCaminhoDestOri.push_back(o_wVertice);

		if (v_wCaminhoOriDest.size() > v_wCaminhoDestOri.size())
			return v_wCaminhoOriDest;
		else
			return v_wCaminhoDestOri;

	}

};

/* Matriz Esparsa */
class MatrizEsparsa{
public:
	/*--------------*/
	/* Atributos    */
	/*--------------*/

	int i_aLinhasDescobertas;                         /* Quantidade de linhas Descobertas    */
	int i_aColunasSelecionadas;                       /* Quantidade de Colunas selecionadas  */
	float f_aFuncaoObjetivo = 0;                      /* Função objetivo da busca local      */
	std::vector<Linha*> v_aLinhas;		              /* Linhas da Matriz                    */
	std::vector<Coluna*> v_aColunas;	              /* Colunas da Matriz                   */
	std::string s_aNomeArquivo = "instGraph";         /* Nome do arquivo da Matriz lida      */

	/*--------------*/
	/* Construtores */
	/*--------------*/
	MatrizEsparsa(){}
	~MatrizEsparsa(){
		/*----------------*/
		/* Variáveis      */
		/*----------------*/
		int i_wI;

		// Deleta as linhas e colunas criadas
		for (i_wI = 0; i_wI < v_aColunas.size(); i_wI++){
			delete v_aColunas[i_wI];
		}
		for (i_wI = 0; i_wI < v_aLinhas.size(); i_wI++){
			delete v_aLinhas[i_wI];
		}

		//Clear the data
		v_aColunas.clear();
		v_aLinhas.clear();
	}

	/*--------------*/
	/* Métodos      */
	/*--------------*/

	/*-----------------------------------------------------------*/
	/* Método LeArquivoSSP                                       */
	/*   Lê um arquivo no formato de Shortest Paths (SSP) e cria */
	/*   a instância utilizada no problema                       */
	/* Parâmetros                                                */
	/*   char* arquivo - input  - Caminho completo arquivo SSP   */
	/*-----------------------------------------------------------*/
	void LeArquivSSP(char * s_pNomeArquivo){
		/*----------------*/
		/* Variáveis      */
		/*----------------*/
		int i_wQtdLinhas;
		int i_wQtdColunas;
		int i_wI;
		int i_wNode;
		int i_wOrigem;
		int i_wDestino;
		char c_wChar;
		bool b_wLeuPar;
		std::ifstream f_wArquivo;

		/*----------------*/
		/* Logic Start    */
		/*----------------*/
		b_wLeuPar = false;

		// Abre arquivo para leitura
		f_wArquivo.open(s_pNomeArquivo, std::istream::in);

		//Salva o nome do arquivo lido
		s_aNomeArquivo = s_pNomeArquivo;

		// Cria as colunas da matriz
		f_wArquivo >> i_wQtdColunas;
		i_aColunasSelecionadas = 0;
		v_aColunas.resize(i_wQtdColunas);
		for (i_wI = 0; i_wI < i_wQtdColunas; i_wI++){
			v_aColunas[i_wI] = new Coluna(i_wI);
		}

		// Cria as linhas da Matriz
		f_wArquivo >> i_wQtdLinhas;
		i_aLinhasDescobertas = i_wQtdLinhas;
		v_aLinhas.resize(i_wQtdLinhas);

		// Lê arquivo caracter por caracter
		i_wI = 0;
		while (f_wArquivo >> c_wChar) {

			// Realiza ação de acordo com caracter lido e estado da leitura
			switch (c_wChar)
			{
				/* Lendo início do par ordenado ou do caminho */
			case ('[') :
				if (!b_wLeuPar){
					// Se está lendo o par origem destino após o [ está a origem
					f_wArquivo >> i_wOrigem;
				}
				else {
					// Se está lendo o caminho após o [ deve ler outro [ e depois está o primeiro nó
					f_wArquivo >> c_wChar;
					f_wArquivo >> i_wNode;

					// Deve ser realizada referência cruzada entre Linha e Coluna
					v_aLinhas[i_wI]->AddColuna(v_aColunas[i_wNode]);
					v_aColunas[i_wNode]->AddLinha(v_aLinhas[i_wI]);
				}
				break;

				/* Lendo dentro do par ordenado ou do caminho */
			case (',') :
				if (!b_wLeuPar){
					// Se está lendo o par origem destino após a , está o Destino
					f_wArquivo >> i_wDestino;
				}
				else{
					// Se está lendo o caminho após a , está um nó
					f_wArquivo >> i_wNode;

					// Deve ser realizada referência cruzada entre Linha e Coluna
					v_aLinhas[i_wI]->AddColuna(v_aColunas[i_wNode]);
					v_aColunas[i_wNode]->AddLinha(v_aLinhas[i_wI]);
				}
				break;

				/* Terminou de ler o par ordenado ou o caminho */
			case (']') :
				if (!b_wLeuPar){
					// Terminou de ler o par, cria a coluna e seta flag para ler caminho
					v_aLinhas[i_wI] = new Linha(i_wOrigem, i_wDestino);
					b_wLeuPar = true;
				}
				else {
					// Deve ler outro ']'
					f_wArquivo >> c_wChar;

					// Terminou de ler caminho, aponta para ler a próxima linha e seta a flag para ler o Par
					i_wI++;
					b_wLeuPar = false;
				}
				break;

			default:
				break;
			}
		}

		f_wArquivo.close();
	}

	/*--------------------------------------------------------------*/
	/* Método AddColuna										*/
	/*   Realiza a corbertura das linhas apontadas pela coluna		*/
	/*    passada como parâmetro									*/
	/* Parâmetros                                                   */
	/*   int i_pIndiceColuna - input - Índice da coluna selecionada */
	/*--------------------------------------------------------------*/
	bool AddColuna(int i_pIndiceColuna){
		int i_wI;
		int i_wJ;

		/* Verifica se a coluna já foi selecionada */
		if (v_aColunas[i_pIndiceColuna]->b_aSelecionada) return false;

		// Atualiza os contadores de linhas cobertas e colunas selecionadas
		i_aColunasSelecionadas++;
		i_aLinhasDescobertas -= v_aColunas[i_pIndiceColuna]->i_aLinhasCobertas;

		// Realiza a cobertura das linhas
		//TODO: Era pra ter feito um método na coluna, mas não compila porque não reconhece o método da classe Linha
		v_aColunas[i_pIndiceColuna]->b_aSelecionada = true;
		f_aFuncaoObjetivo -= v_aColunas[i_pIndiceColuna]->f_aCusto;
		for (i_wI = 0; i_wI < v_aColunas[i_pIndiceColuna]->v_aLinhas.size(); i_wI++){
			if (!v_aColunas[i_pIndiceColuna]->v_aLinhas[i_wI]->b_aCoberta){
				for (i_wJ = 0; i_wJ < v_aColunas[i_pIndiceColuna]->v_aLinhas[i_wI]->v_aColunas.size(); i_wJ++){
					v_aColunas[i_pIndiceColuna]->v_aLinhas[i_wI]->v_aColunas[i_wJ]->i_aLinhasCobertas--;
				}
				v_aColunas[i_pIndiceColuna]->v_aLinhas[i_wI]->b_aCoberta = true;
				f_aFuncaoObjetivo += v_aColunas[i_pIndiceColuna]->v_aLinhas[i_wI]->f_aGanho;
			}
		}

		return true;
	}

	/*--------------------------------------------------------------*/
	/* Método RmvColuna      										*/
	/*   Realiza a descobertura das linhas apontadas pela coluna	*/
	/*    passada como parâmetro									*/
	/* Parâmetros                                                   */
	/*   int i_pIndiceColuna - input - Índice da coluna selecionada */
	/*--------------------------------------------------------------*/
	void RmvColuna(int i_pIndiceColuna){
		int i_wI;
		int i_wJ;

		// Atualiza os contadores de linhas cobertas e colunas selecionadas
		i_aColunasSelecionadas--;

		// Realiza a cobertura das linhas
		//TODO: Era pra ter feito um método na coluna, mas não compila porque não reconhece o método da classe Linha
		v_aColunas[i_pIndiceColuna]->b_aSelecionada = false;
		f_aFuncaoObjetivo += v_aColunas[i_pIndiceColuna]->f_aCusto;
		for (i_wI = 0; i_wI < v_aColunas[i_pIndiceColuna]->v_aLinhas.size(); i_wI++){
			for (i_wJ = 0; i_wJ < v_aColunas[i_pIndiceColuna]->v_aLinhas[i_wI]->v_aColunas.size(); i_wJ++){
				if (v_aColunas[i_pIndiceColuna]->v_aLinhas[i_wI]->v_aColunas[i_wJ]->b_aSelecionada) break;
			}
			if (i_wJ >= v_aColunas[i_pIndiceColuna]->v_aLinhas[i_wI]->v_aColunas.size()){
				v_aColunas[i_pIndiceColuna]->v_aLinhas[i_wI]->b_aCoberta = false;
				f_aFuncaoObjetivo -= v_aColunas[i_pIndiceColuna]->v_aLinhas[i_wI]->f_aGanho;
				i_aLinhasDescobertas++;
				for (i_wJ = 0; i_wJ < v_aColunas[i_pIndiceColuna]->v_aLinhas[i_wI]->v_aColunas.size(); i_wJ++){
					v_aColunas[i_pIndiceColuna]->v_aLinhas[i_wI]->v_aColunas[i_wJ]->i_aLinhasCobertas++;
				}
			}
		}
	}

	/*--------------------------------------------------------------*/
	/* Método FlipColuna      										*/
	/*   Realiza o 1-flip da coluna  								*/
	/* Parâmetros                                                   */
	/*   int i_pIndiceColuna - input - Índice da coluna selecionada */
	/*--------------------------------------------------------------*/
	void FlipColuna(int i_pIndiceColuna){
		if (v_aColunas[i_pIndiceColuna]->b_aSelecionada)RmvColuna(i_pIndiceColuna);
		else AddColuna(i_pIndiceColuna);
	}

	/*--------------------------------------------------------------*/
	/* Sobrescrita do operador =									*/
	/*   http://en.cppreference.com/w/cpp/language/operators        */
	/*   Atribuição por Cópia      									*/
	/*--------------------------------------------------------------*/
	MatrizEsparsa& operator=(const MatrizEsparsa& other) // copy assignment
	{
		/*----------------*/
		/* Variáveis      */
		/*----------------*/
		int i_wI;
		int i_wJ;

		if (this != &other) { // self-assignment check expected
			/* Copia estado da solução */
			i_aLinhasDescobertas = other.i_aLinhasDescobertas;
			i_aColunasSelecionadas = other.i_aColunasSelecionadas;
			f_aFuncaoObjetivo = other.f_aFuncaoObjetivo;
			s_aNomeArquivo = other.s_aNomeArquivo;

			/* Deleta as linhas e colunas criadas */
			for (i_wI = 0; i_wI < v_aColunas.size(); i_wI++){
				delete v_aColunas[i_wI];
			}
			for (i_wI = 0; i_wI < v_aLinhas.size(); i_wI++){
				delete v_aLinhas[i_wI];
			}

			/* Recria coluna */
			v_aColunas.clear();
			v_aLinhas.clear();
			v_aColunas.resize(other.v_aColunas.size());
			v_aLinhas.resize(other.v_aLinhas.size());

			/* Copia os dadas das linhas e colunas */
			for (i_wI = 0; i_wI < v_aColunas.size(); i_wI++){
				v_aColunas[i_wI] = new Coluna(other.v_aColunas[i_wI]);
			}
			for (i_wI = 0; i_wI < v_aLinhas.size(); i_wI++){
				v_aLinhas[i_wI] = new Linha(other.v_aLinhas[i_wI]);
				for (i_wJ = 0; i_wJ < other.v_aLinhas[i_wI]->v_aColunas.size(); i_wJ++){
					v_aLinhas[i_wI]->v_aColunas.push_back(v_aColunas[other.v_aLinhas[i_wI]->v_aColunas[i_wJ]->i_aID]);
					v_aColunas[other.v_aLinhas[i_wI]->v_aColunas[i_wJ]->i_aID]->v_aLinhas.push_back(v_aLinhas[i_wI]);
				}
			}
		}
		return *this;
	}

	/*--------------------------------------------------------------*/
	/* Método Imprime												*/
	/*   Imprime a matriz											*/
	/*--------------------------------------------------------------*/
	void Imprime(){
		int i_wI;
		int i_wJ;
		int i_wK;

		// Imprime cabeçalho das colunas, considera números de até 3 dígitos e um * para indicar se foi ou não selecionada
		std::cout << "|           ";
		for (i_wI = 0; i_wI < v_aColunas.size(); i_wI++){
			std::cout << "| ";
			if (v_aColunas[i_wI]->b_aSelecionada) std::cout << "*";
			else std::cout << " ";
			std::cout << std::setfill(' ') << std::setw(3) << v_aColunas[i_wI]->i_aID << " ";
		}
		std::cout << "|" << std::endl;

		// Imprime as linhas, considerando de até 3 dígitos no cabeçalho
		for (i_wI = 0; i_wI < v_aLinhas.size(); i_wI++){
			std::cout << "| ";
			if (v_aLinhas[i_wI]->b_aCoberta) std::cout << "*";
			else std::cout << " ";
			std::cout << std::setfill(' ') << std::setw(3) << v_aLinhas[i_wI]->i_aOrigem << "->" << std::setfill(' ') << std::setw(3) << v_aLinhas[i_wI]->i_aDestino << " ";
			for (i_wJ = 0; i_wJ < v_aColunas.size(); i_wJ++){
				for (i_wK = 0; i_wK < v_aLinhas[i_wI]->v_aColunas.size(); i_wK++){
					if (v_aColunas[i_wJ]->i_aID == v_aLinhas[i_wI]->v_aColunas[i_wK]->i_aID){
						std::cout << "|   1  ";
						break;
					}
				}
				if (i_wK >= v_aLinhas[i_wI]->v_aColunas.size()){
					std::cout << "|   0  ";
				}
			}
			std::cout << "|" << std::endl;
		}
	}

	/*--------------------------------------------------------------*/
	/* Método ImprimeGraphviz										*/
	/*   Imprime a rede para o graphviz, destacando os observadores */
	/*--------------------------------------------------------------*/
	void ImprimeGraphviz(int i_pSeq = 0, std::string s_pClassificacao = ""){
		std::size_t st_wPosStr;
		std::string s_wArquivoDot;
		std::string s_wTexto;
		std::string s_wHeader;
		std::string s_wCorpo;
		std::string s_wFooter;
		std::string s_wArquivoGraphviz;
		std::string s_wComandoSistema;
		std::stringstream s_wStream;
		std::ofstream f_wArquivo;
		int i_wI;
		int i_wJ;
		int i_wK;

		st_wPosStr = s_aNomeArquivo.find("instGraph");
		s_wArquivoDot = s_aNomeArquivo.substr(st_wPosStr);
		s_wArquivoDot.resize(s_wArquivoDot.size() - 4);
		s_wStream << "Seq_" << i_pSeq << "_";
		if(s_pClassificacao != "") s_wStream << s_pClassificacao << "_";
		s_wArquivoDot = s_wStream.str() + s_wArquivoDot;

		s_wArquivoGraphviz = s_wArquivoDot + "." + EXTENSAO;
		s_wArquivoDot += ".dot";

		s_wComandoSistema = (std::string) "dot -T" + EXTENSAO + " " + s_wArquivoDot + " -o " + s_wArquivoGraphviz;


		s_wHeader = "strict graph G {\n";
		s_wHeader += "size=\"8.5,11;\"\n";
		s_wHeader += "ratio = \"expand;\"\n";
		s_wHeader += "fixedsize=\"true;\"\n";
		s_wHeader += "overlap=\"scale;\"\n";
		s_wHeader += "node[shape=circle,width=.12,hight=.12,fontsize=12]\n";
		s_wHeader += "edge[fontsize=12]\n";
		s_wHeader += "\n";

		s_wCorpo = "";

		s_wFooter = "\n}\n";

		s_wStream.str("");

		for (i_wI = 0; i_wI < v_aColunas.size(); i_wI++){
			s_wStream << v_aColunas[i_wI]->i_aID << " [color=";
			if (v_aColunas[i_wI]->b_aSelecionada) s_wStream << "red";
			else s_wStream << "black";
			s_wStream << "];\n";

			s_wCorpo += s_wStream.str();
			s_wStream.str("");
		}

		s_wCorpo += "\n";
		s_wStream.str("");
		for (i_wI = 0; i_wI < v_aLinhas.size(); i_wI++){
			for (i_wJ = 0; i_wJ < v_aLinhas[i_wI]->v_aColunas.size(); i_wJ++){
				if(i_wJ < v_aLinhas[i_wI]->v_aColunas.size()-1)
					s_wStream << v_aLinhas[i_wI]->v_aColunas[i_wJ]->i_aID << " -- ";
				else
					s_wStream << v_aLinhas[i_wI]->v_aColunas[i_wJ]->i_aID << ";\n";
			}
			s_wCorpo += s_wStream.str();
			s_wStream.str("");

		}

		s_wTexto = s_wHeader + s_wCorpo + s_wFooter;

		f_wArquivo.open(s_wArquivoDot.c_str());
		f_wArquivo << s_wTexto;
		f_wArquivo.close();

		system(s_wComandoSistema.c_str());
	}

	/*-----------------------------------------------------------*/
	/* Método ConverteGrafo                                      */
	/*   Converte a classe grafo para classe matriz criando      */
	/*   a instância utilizada no problema                       */
	/* Parâmetros                                                */
	/*   Grafo o_pGrafo - input  - Objeto da classe Grafo        */
	/*-----------------------------------------------------------*/
	void ConverteGrafo(Grafo o_pGrafo){
		/*----------------*/
		/* Variáveis      */
		/*----------------*/
		int i_wQtdLinhas;
		int i_wQtdColunas;
		int i_wI;
		int i_wJ;
		int i_wK;
		int i_wNode;
		int i_wOrigem;
		int i_wDestino;
		std::vector<Vertice> v_wCaminho;

		/*----------------*/
		/* Logic Start    */
		/*----------------*/

		// Cria as colunas da matriz

		i_wQtdColunas = o_pGrafo.v_aListaVertice.size();
		i_aColunasSelecionadas = 0;
		v_aColunas.resize(i_wQtdColunas);
		for (i_wI = 0; i_wI < i_wQtdColunas; i_wI++){
			v_aColunas[i_wI] = new Coluna(i_wI);
		}

		// Cria as linhas da Matriz
		i_wQtdLinhas = 0;
		for(i_wI = 0;i_wI < i_wQtdColunas;i_wI++)
		{
			for (i_wJ = i_wI + 1;i_wJ < i_wQtdColunas;i_wJ++)
			{
				v_aLinhas.push_back(new Linha(i_wI, i_wJ));

				v_wCaminho = o_pGrafo.MontaCaminho(i_wI, i_wJ);

				for(i_wK = 0; i_wK < v_wCaminho.size();i_wK++)
				{
					v_aLinhas[i_wQtdLinhas]->AddColuna(v_aColunas[v_wCaminho[i_wK].i_aID]);
					v_aColunas[v_wCaminho[i_wK].i_aID]->AddLinha(v_aLinhas[i_wQtdLinhas]);
				}

				i_wQtdLinhas++;
			}
		}
	}

};

/*--------------------------------------*/
/* Funções                              */
/*--------------------------------------*/

/*-----------------------------------------------------------*/
/* Função ComparaColuna                                      */
/*   Função de ordenação das Colunas.						 */
/*	 Ordena o vetor de colunas de maneira que a coluna que   */
/*    cobre a maior quantiedade de linhas fique no início    */
/*	  do vector.		                                     */
/*   Utilizada apenas na função sort.                        */
/*-----------------------------------------------------------*/
bool ComparaColuna(Coluna *c1, Coluna *c2){
	return c1->i_aLinhasCobertas > c2->i_aLinhasCobertas;
}

/*-----------------------------------------------------------*/
/* Função getNomeSo                                          */
/*   Função que obtém o sistema operacional da máquina.      */
/*	 Retorna uma string com o nome do SO.                    */
/*-----------------------------------------------------------*/
std::string getNomeSo()
{
#ifdef _WIN32
	return "Windows 32-bit";
#elif _WIN64
	return "Windows 64-bit";
#elif __unix || __unix__
	return "Unix";
#elif __APPLE__ || __MACH__
	return "Mac OSX";
#elif __linux__
	return "Linux";
#elif __FreeBSD__
	return "FreeBSD";
#else
	return "Other";
#endif
}

/*-----------------------------------------------------------*/
/* Função getNomeSo                                          */
/*   Função que obtém o caminho da pasta de instâncias.      */
/*	 Retorna uma string com o caminho da instância.          */
/*-----------------------------------------------------------*/
std::string caminhoInput()
{
	if (getNomeSo() == "Unix" || getNomeSo() == "Linux")
		return "../GraphGenerator/input/";
	if (getNomeSo() == "Windows 32-bit" || getNomeSo() == "Windows 64-bit")
		return "..\\..\\GraphGenerator\\input\\";
	else
		return "";
}

/*-----------------------------------------------------------*/
/* Função listaArquivos                                      */
/*   Função que obtém lista de instancias dada uma extensao. */
/*	 Retorna uma lista de strings com os nomes dos arquivos  */
/*-----------------------------------------------------------*/
std::vector<std::string> listaArquivos(std::string extensao)
{
	std::vector<std::string> lista;

	DIR *dir = NULL;
	struct dirent *drnt = NULL;
	std::string nomeArquivo = "";
	std::string caminhoPasta = caminhoInput();

	dir = opendir(caminhoPasta.c_str());
	if (dir)
	{
		while (drnt = readdir(dir))
		{
			nomeArquivo = drnt->d_name;
			if (nomeArquivo.find(extensao) != std::string::npos)
			{
				lista.push_back(caminhoPasta + nomeArquivo);
			}
		}
		closedir(dir);
	}
	else
	{
		std::cout << "Can not open directory '" << caminhoPasta << "'" << std::endl;
		exit(1);
	}

	return lista;
}

/*-----------------------------------------------------------*/
/* Função GulosoRandomizado                                   */
/*   Agoritmo guloso randomizado                             */
/*-----------------------------------------------------------*/
void GulosoRandomizado(MatrizEsparsa &o_pMatriz, float f_pAlpha)
{
	/*-----------*/
	/* Variáveis */
	/*-----------*/
	int i_wTamanhoListaCandidatos;
	int i_wColunaSelecionada;
	int i_wColunaOrd;
	int i_wMaiorCobertura;
	int i_wMenorCobertura;
	int p_wLimiar;
	std::vector<Coluna *> v_aColunasOrd; /* Colunas da Matriz ordenadas         */

	/*------------------*/
	/* Início da Lógica */
	/*------------------*/
	v_aColunasOrd = o_pMatriz.v_aColunas;
	while (o_pMatriz.i_aLinhasDescobertas > 0){
		// Ordena as colunas com relação ao número de linhas cobertas
		std::sort(v_aColunasOrd.begin(), v_aColunasOrd.end() - o_pMatriz.i_aColunasSelecionadas, ComparaColuna);
		//std::sort(v_aColunasOrd.begin(), v_aColunasOrd.end(), ComparaColuna);
		/*
		for(int i=0;i<v_aColunasOrd.size();i++)
		{
			std::cout << "[" << v_aColunasOrd[i]->i_aID << " - " << v_aColunasOrd[i]->i_aLinhasCobertas << "] ";
		}
		std::cout << std::endl;
		*/
		// Calcula o tamanho da lista de candidatos
		//i_wTamanhoListaCandidatos = f_pAlpha != 0.0 ? (v_aColunasOrd.size() - o_pMatriz.i_aColunasSelecionadas) * f_pAlpha : 1;
		i_wTamanhoListaCandidatos = (v_aColunasOrd.size() - o_pMatriz.i_aColunasSelecionadas) * f_pAlpha;
		if(i_wTamanhoListaCandidatos <= 0) i_wTamanhoListaCandidatos = 1;
		//i_wMaiorCobertura = v_aColunasOrd[0]->i_aLinhasCobertas;
		//i_wMenorCobertura = v_aColunasOrd[v_aColunasOrd.size() - 1]->i_aLinhasCobertas;
		//p_wLimiar = i_wMaiorCobertura - f_pAlpha*(i_wMaiorCobertura - i_wMenorCobertura);

		//for(i_wTamanhoListaCandidatos=0;(i_wTamanhoListaCandidatos<v_aColunasOrd.size())&&(v_aColunasOrd[i_wTamanhoListaCandidatos]->i_aLinhasCobertas >= p_wLimiar);i_wTamanhoListaCandidatos++);

		//TODO: Verificar Possível Loop Infinito
		do{
			// Seleciona a coluna na lista de candidatos
			i_wColunaOrd = rand() % i_wTamanhoListaCandidatos;
			i_wColunaSelecionada = v_aColunasOrd[i_wColunaOrd]->i_aID;

			// Realiza a seleção da coluna na matriz
		} while (!o_pMatriz.AddColuna(i_wColunaSelecionada));

		// move a coluna selecionada para a última posição
		std::swap(v_aColunasOrd[i_wColunaOrd], v_aColunasOrd[v_aColunasOrd.size() - o_pMatriz.i_aColunasSelecionadas]);
		//std::swap(v_aColunasOrd[i_wColunaOrd], v_aColunasOrd[v_aColunasOrd.size() - 1]);
		//std::cout << "Candidato escolhido: " << v_aColunasOrd[v_aColunasOrd.size()-1]->i_aID << std::endl;
		//v_aColunasOrd.pop_back();

	}

}

/*-----------------------------------------------------------*/
/* Função BuscaLocal                                         */
/*   Busca Local                                             */
/*-----------------------------------------------------------*/
void BuscaLocal(MatrizEsparsa &o_pMatriz)
{
	/*-----------*/
	/* Variáveis */
	/*-----------*/
	int i_wI;
	int i_wCol;
	float f_wDelta;
	float f_wRatio;

	/*------------------*/
	/* Início da Lógica */
	/*------------------*/
	while (true)
	{
		/* Procura Melhor Vizinho */
		for (i_wI = 0; i_wI < o_pMatriz.v_aColunas.size(); i_wI++)
		{
			f_wDelta = o_pMatriz.f_aFuncaoObjetivo;
			o_pMatriz.FlipColuna(i_wI);
			f_wDelta = o_pMatriz.f_aFuncaoObjetivo - f_wDelta;
			if (i_wI == 0){
				f_wRatio = f_wDelta;
				i_wCol = i_wI;
			}
			else if ( f_wDelta > f_wRatio ){
				f_wRatio = f_wDelta;
				i_wCol = i_wI;
			}
			o_pMatriz.FlipColuna(i_wI);
		}

		/* Verifica se encontrou uma solução melhor */
		if (f_wRatio > 0) o_pMatriz.FlipColuna(i_wCol);
		else break;
	}

}

/*
void Grasp (grafo G, float f_pAlpha, int i_pMaxIteracao, int &i_pLoops)
{
	 int i_wI = 0;
	 MatrizEsparsa o_wMatrizAtual, o_wMelhorSolucao;

	 o_wMelhorSolucao = o_pMatriz;
	 i_pLoops = 0;

	 while(i_wI < i_pMaxIteracao)
	 {
		 o_wMatrizAtual = DIJKSTRAALEATORIO(G,alfa);
		 i_wI++;
		 i_pLoops++;
		 GulosoRandomizado(o_wMatrizAtual, 0);
		 BuscaLocal(o_wMatrizAtual);

		 if (o_wMatrizAtual.f_aFuncaoObjetivo > o_wMelhorSolucao.f_aFuncaoObjetivo)
		 {
			 o_wMelhorSolucao = o_wMatrizAtual;
			 i_wI = 0;
		 }

	 }
	 o_pMatriz = o_wMelhorSolucao;

}
*/

void Grasp (MatrizEsparsa &o_pMatriz, float f_pAlpha, int i_pMaxIteracao, int &i_pLoops)
{
	 int i_wI = 0;
	 MatrizEsparsa o_wMatrizAtual, o_wMelhorSolucao;

	 o_wMelhorSolucao = o_pMatriz;
	 i_pLoops = 0;

	 while(i_wI < i_pMaxIteracao)
	 {
		 o_wMatrizAtual = o_pMatriz;
		 i_wI++;
		 i_pLoops++;
		 GulosoRandomizado(o_wMatrizAtual, f_pAlpha);
		 BuscaLocal(o_wMatrizAtual);

		 if (o_wMatrizAtual.f_aFuncaoObjetivo > o_wMelhorSolucao.f_aFuncaoObjetivo)
		 {
			 o_wMelhorSolucao = o_wMatrizAtual;
			 i_wI = 0;
		 }

	 }
	 o_pMatriz = o_wMelhorSolucao;

}

void GraspReativo (MatrizEsparsa &o_pMatriz, int i_pMaxIteracao, int i_pB, int i_pGama, int &i_pLoops)
{
	 int i_wI = 0, i_wIndex;
	 int i_wConstTamAlpha = 10;
	 int i_wLoopsB = 0;
	 float f_wSorteio, f_wQsum, f_wPsum;
	 std::vector<float> v_wAlpha, v_wProb, v_wPontuacao, v_wQ, v_wContador;
	 MatrizEsparsa o_wMatrizAtual, o_wMelhorSolucao;

	 /*----------Variaveis para fazer distribuicao de escolha------------------*/
	 /*------------------------------------------------------------------------*/
	 std::vector<int> v_wContadorSolucao, v_wContadorAlfas;
	 std::ofstream f_wDistribuicao;

	 v_wContadorSolucao.resize(o_pMatriz.v_aColunas.size(),0);
	 v_wContadorAlfas.resize(i_wConstTamAlpha,0);
	 /*------------------------------------------------------------------------*/

	 o_wMelhorSolucao = o_pMatriz;
	 i_pLoops = 0;

	 v_wQ.resize(i_wConstTamAlpha,0.1);
	 v_wPontuacao.resize(i_wConstTamAlpha,0);
	 v_wContador.resize(i_wConstTamAlpha,0);
	 v_wAlpha.resize(i_wConstTamAlpha);
	 v_wProb.resize(i_wConstTamAlpha);

	 for(int i_wJ = 0;i_wJ < i_wConstTamAlpha;i_wJ++)
	 {
		 v_wAlpha[i_wJ] = (float) ((i_wJ+1)/(float)i_wConstTamAlpha);
		 v_wProb[i_wJ] = (float) ((i_wJ+1)/(float)i_wConstTamAlpha);
	 }


	 o_wMatrizAtual = o_pMatriz;
	 o_wMelhorSolucao.i_aColunasSelecionadas = o_wMelhorSolucao.v_aColunas.size()*10;

	 while(i_wI < i_pMaxIteracao)
	 {
		 f_wSorteio = (float) rand()/RAND_MAX;

		 for (int i_wJ =0;i_wJ<i_wConstTamAlpha;i_wJ++)
		 {
			 if(f_wSorteio<v_wProb[i_wJ])
			 {
				 i_wIndex = i_wJ;
				 break;
			 }
			 else
				i_wIndex=i_wConstTamAlpha-1;
		 }

		 GulosoRandomizado(o_wMatrizAtual, v_wAlpha[i_wIndex]);
		 BuscaLocal(o_wMatrizAtual);

		 /*---Contagem para grafico de distribuicao das solucoes do grasp e dos alfas escolhidos-----*/
		 /*------------------------------------------------------------------------------------------*/
		 v_wContadorSolucao[o_wMatrizAtual.i_aColunasSelecionadas-1] += 1;
		 v_wContadorAlfas[i_wIndex] += 1;
		 /*------------------------------------------------------------------------------------------*/

		 v_wPontuacao[i_wIndex] += (float) o_wMatrizAtual.i_aColunasSelecionadas;
		 //v_wPontuacao[i_wIndex] += o_wMatrizAtual.f_aFuncaoObjetivo;
		 v_wContador[i_wIndex] += 1;

		 if (o_wMatrizAtual.i_aColunasSelecionadas < o_wMelhorSolucao.i_aColunasSelecionadas)
		 //if (o_wMatrizAtual.f_aFuncaoObjetivo > o_wMelhorSolucao.f_aFuncaoObjetivo)
		 {
			 o_wMelhorSolucao = o_wMatrizAtual;
			 std::cout << "best solution: " << o_wMelhorSolucao.i_aColunasSelecionadas << " Iteration: " << i_wI << std::endl;
			 i_wI = 0;
		 }

		 if(i_wLoopsB == i_pB)
		 {
			 i_wLoopsB = 0;
			 f_wQsum = 0.0;
			 for(int i_wJ = 0;i_wJ < i_wConstTamAlpha; i_wJ++)
			 {
				 if (v_wContador[i_wJ] > 0)
				 {
					 float media = (float) (v_wPontuacao[i_wJ]/v_wContador[i_wJ]);
					 v_wQ[i_wJ] = pow(1.0/media,i_pGama);
				 }
				 f_wQsum += v_wQ[i_wJ];
			 }

			 f_wPsum = 0.0;
			 for(int i_wJ = 0; i_wJ < i_wConstTamAlpha; i_wJ++)
			 {
				 float p = v_wQ[i_wJ]/f_wQsum;
				 f_wPsum += p;
				 v_wContador[i_wJ] = 0;
				 v_wPontuacao[i_wJ] = 0;
				 v_wProb[i_wJ] = f_wPsum;
			 }
		 }
		 o_wMatrizAtual = o_pMatriz;
		 i_wI++;
		 i_pLoops++;
		 i_wLoopsB++;

	 }
	 o_pMatriz = o_wMelhorSolucao;

	 /*-----------------Salvar distribuicao das solucoes do grasp-----------------------------------------------*/
	 /*---------------------------------------------------------------------------------------------------------*/
	 f_wDistribuicao.open("../ComputeResult/distribuicaoGrasp.txt");
	 for(int i_wIt = 0; i_wIt < v_wContadorSolucao.size();i_wIt++)
	 {
		//if(v_wContadorSolucao[i_wIt] != 0)
		{
			f_wDistribuicao << (i_wIt+1) << " - " << v_wContadorSolucao[i_wIt] << std::endl;
		}
	 }
	 f_wDistribuicao << std::endl;
	 for(int i_wIt = 0; i_wIt < v_wContadorAlfas.size();i_wIt++)
	 {
		//if(v_wContadorAlfas[i_wIt] != 0)
		{
			f_wDistribuicao << v_wAlpha[i_wIt] << " - " << v_wContadorAlfas[i_wIt] << std::endl;
		}
	 }
	 f_wDistribuicao.close();
	 /*---------------------------------------------------------------------------------------------------------*/
}


/*--------------------------------------*/
/* Aplicação                            */
/*--------------------------------------*/
int main(int argc, char** argv){

	int i_wSeq = 1;
	int i_wMaxIteracao = 100;
	int i_wLoopsGrasp = 0;
	int i_wB = 10;
	int i_wGama = 8;
	float f_wAlpha = 1.0;
	double d_wInicio;
	double d_wFim;
	std::ofstream f_wArquivoGuloso;
	std::ofstream f_wArquivoBl;
	std::ofstream f_wArquivoGrasp;
	MatrizEsparsa o_wMatriz, o_wMatrizGrasp, o_wMatrizLoop;
	std::vector<std::string> pasta;

	Grafo grafo;

	/*---------------DELETAR---------------------------------------------*/
	std::vector<int> contador;
	std::ofstream distribuicaoGuloso;
	/*-------------------------------------------------------------------*/

	// Lê a instânica
	//pasta = listaArquivos(".ssp");
	//pasta = listaArquivos("instGraph_10_0.ssp");
	//pasta = listaArquivos(".sim");

	f_wArquivoGuloso.open("../ComputeResult/execGuloso.txt");
	f_wArquivoBl.open("../ComputeResult/execBl.txt");
	f_wArquivoGrasp.open("../ComputeResult/execGrasp.txt");

	/*----------------------DELETAR------------------------------------------------*/
	distribuicaoGuloso.open("../ComputeResult/distribuicaoGuloso.txt");
	/*----------------------DELETAR------------------------------------------------*/

	srand(42);
	//for (int it = 0; it < pasta.size(); it++)
	//{
		//o_wMatriz.LeArquivSSP((char *)pasta[it].data());
		//o_wMatrizGrasp = o_wMatriz;

		contador.resize(o_wMatriz.v_aColunas.size(),0);

		grafo.LeArquivoGrafo("..\\GraphGenerator\\instGraph_10_0.txt");
		grafo.DijkstraTodosVertices(1.0);
		o_wMatriz.ConverteGrafo(grafo);
		o_wMatriz.ImprimeGraphviz();
		o_wMatriz.Imprime();
		grafo.ImprimeArvoresGraphviz();

 /*
		for(int i=0;i<i_wMaxIteracao;i++)
		{
		 GulosoRandomizado(o_wMatriz, 0.0);
		 contador[o_wMatriz.i_aColunasSelecionadas-1] += 1;
		}
		for(int i=0;i<contador.size();i++)
		{
		distribuicaoGuloso << (i+1) << " - " << contador[i] << std::endl;
		}
*/
/*
		std::cout << "Executando guloso para instancia " << pasta[it].data() << std::endl;
		d_wInicio = getcputime();
		GulosoRandomizado(o_wMatriz, 0.0);
		d_wFim = getcputime();
		f_wArquivoGuloso << o_wMatriz.v_aColunas.size() << " " << o_wMatriz.i_aColunasSelecionadas << " " << (d_wFim - d_wInicio) << " " << " 1 " << std::endl;
		std::cout << "Algoritmo guloso finalizado!" << std::endl;

		std::cout << "Executando busca local para instancia " << pasta[it].data() << std::endl;
		d_wInicio = getcputime();
		BuscaLocal(o_wMatriz);
		d_wFim = getcputime();
		f_wArquivoBl << o_wMatriz.v_aColunas.size() << " " << o_wMatriz.i_aColunasSelecionadas << " " << (d_wFim - d_wInicio) << " " << " 1 " << std::endl;
		std::cout << "Busca local finalizada!" << std::endl;

		std::cout << "Executando GRASP para instancia " << pasta[it].data() << std::endl;
		d_wInicio = getcputime();
		//Grasp(o_wMatrizGrasp, f_wAlpha, i_wMaxIteracao, i_wLoopsGrasp);
		GraspReativo(o_wMatrizGrasp, i_wMaxIteracao, i_wB, i_wGama, i_wLoopsGrasp);
		d_wFim = getcputime();
		f_wArquivoGrasp << o_wMatrizGrasp.v_aColunas.size() << " " << o_wMatrizGrasp.i_aColunasSelecionadas << " " << (d_wFim - d_wInicio) << " " << i_wLoopsGrasp << std::endl;
		std::cout << "GRASP finalizado!" << std::endl;
*/
	//}

	f_wArquivoGuloso.close();
	f_wArquivoBl.close();
	f_wArquivoGrasp.close();

	/*----------------------DELETAR------------------------------------------------*/
	distribuicaoGuloso.close();
	/*----------------------DELETAR------------------------------------------------*/

	return 0;

}

