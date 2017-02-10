/*------------------------------------*/
/* Includes                           */
/*------------------------------------*/
#include <iostream>
#include <fstream>
#include <vector>

/*------------------------------------*/
/* Namespaces                         */
/*------------------------------------*/


/*------------------------------------*/
/* Classes                            */
/*------------------------------------*/
class Linha;
class Coluna;

class Coluna{
private:
	/*--------------*/
	/* Atributos    */
	/*--------------*/
	int i_aID;                          /* ID do nó                                           */
	int i_aLinhasCobertas;				/* Quantidade de linhas que a coluna cobre no momento */
	std::vector<Linha*> v_aLinhas;		/* Linhas cobertas pela coluna                        */

public:
	/*--------------*/
	/* Construtores */
	/*--------------*/
	//TODO: Ver como criar e deletar para não ter vazamento de memória
	Coluna(){
		i_aLinhasCobertas = 0;
	}
	Coluna(int i_pID){
		i_aLinhasCobertas = 0;
		i_aID = i_pID;
	}
	~Coluna(){}

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

};

class Linha{
private:
	/*--------------*/
	/* Atributos    */
	/*--------------*/
	int i_aOrigem;						/* Origem do Caminho              */
	int i_aDestino;						/* Destino do Caminho             */
	bool b_aCoberta;					/* Indica se a linha está coberta */
	std::vector<Coluna*> v_aColunas;	/* Colunas que cobrem a linha     */

public:
	/*--------------*/
	/* Construtores */
	/*--------------*/
	//TODO: Ver como criar e deletar para não ter vazamento de memória
	Linha(){
		b_aCoberta = false;
	}
	Linha(int i_pOrigem, int i_pDestino){
		i_aOrigem = i_pOrigem;
		i_aDestino = i_pDestino;
		b_aCoberta = false;
	}
	~Linha(){}

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

};

/* Matriz Esparsa */
class MatrizEsparsa{
private:
	/*--------------*/
	/* Atributos    */
	/*--------------*/
	std::vector<Linha*> v_aLinhas;		/* Linhas da Matriz  */
	std::vector<Coluna*> v_aColunas;	/* Colunas da Matriz */

public:
	/*--------------*/
	/* Construtores */
	/*--------------*/
	MatrizEsparsa(){}
	~MatrizEsparsa(){}

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

		// Cria as colunas da matriz
		f_wArquivo >> i_wQtdColunas;
		v_aColunas.resize(i_wQtdColunas);
		for (i_wI = 0; i_wI < i_wQtdColunas; i_wI++){
			v_aColunas[i_wI] = new Coluna(i_wI);
		}

		// Cria as linhas da Matriz
		f_wArquivo >> i_wQtdLinhas;
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
					// Se está lendo o caminho após o [ está o primeiro nó
					// Deve ser realizada referência cruzada entre Linha e Coluna
					f_wArquivo >> i_wNode;
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
					// Deve ser realizada referência cruzada entre Linha e Coluna
					f_wArquivo >> i_wNode;
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

};

/*--------------------------------------*/
/* Aplicação                            */
/*--------------------------------------*/
int main(int argc, char** argv){

	MatrizEsparsa matriz;

	matriz.LeArquivSSP("D:\\Mestrado\\Projetos\\SetCoverGrasp\\GraphGenerator\\input\\instGraph_5_0_SSP");

	return 0;

}

