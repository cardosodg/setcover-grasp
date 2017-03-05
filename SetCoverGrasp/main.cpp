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

/*------------------------------------*/
/* Namespaces                         */
/*------------------------------------*/


/*------------------------------------*/
/* Classes                            */
/*------------------------------------*/
class Linha;
class Coluna;

class Coluna{
public:
	/*--------------*/
	/* Atributos    */
	/*--------------*/
	int i_aID;                          /* ID do n�                                           */
	int i_aLinhasCobertas;				/* Quantidade de linhas que a coluna cobre no momento */
	bool b_aSelecionada;                /* Indica se a coluna foi selecionada                 */
	std::vector<Linha*> v_aLinhas;		/* Linhas cobertas pela coluna                        */

	/*--------------*/
	/* Construtores */
	/*--------------*/
	//TODO: Ver como criar e deletar para n�o ter vazamento de mem�ria
	Coluna(){
		b_aSelecionada = false;
		i_aLinhasCobertas = 0;
	}
	Coluna(int i_pID){
		b_aSelecionada = false;
		i_aLinhasCobertas = 0;
		i_aID = i_pID;
	}
	~Coluna(){}

	/*--------------*/
	/* M�todos      */
	/*--------------*/

	/*-----------------------------------------------------------*/
	/* M�todo AddLinha                                           */
	/*   Adiciona uma linha que a coluna cobre                   */
	/* Par�metros                                                */
	/*   Coluna* p_pLinha - input  - Ponteiro para uma coluna    */
	/*-----------------------------------------------------------*/
	void AddLinha(Linha * p_pLinha){
		v_aLinhas.push_back(p_pLinha);
		i_aLinhasCobertas++;
	}

	/*--------------------------------------------------------------*/
	/* M�todo CobreLinhas											*/
	/*   Realiza a corbertura das linhas apontadas pela coluna		*/
	/*    passada como par�metro									*/
	/* Par�metros                                                   */
	/*   int i_pIndiceColuna - input - �ndice da coluna selecionada */
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
	bool b_aCoberta;					/* Indica se a linha est� coberta */
	std::vector<Coluna*> v_aColunas;	/* Colunas que cobrem a linha     */


	/*--------------*/
	/* Construtores */
	/*--------------*/
	//TODO: Ver como criar e deletar para n�o ter vazamento de mem�ria
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
	/* M�todos      */
	/*--------------*/

	/*-----------------------------------------------------------*/
	/* M�todo AddColuna                                          */
	/*   Adiciona uma coluna que cobre a linha                   */
	/* Par�metros                                                */
	/*   Coluna* p_pColuna - input  - Ponteiro para uma coluna   */
	/*-----------------------------------------------------------*/
	void AddColuna(Coluna * p_pColuna){
		v_aColunas.push_back(p_pColuna);
	}

	/*--------------------------------------------------------------*/
	/* M�todo CobreLinha											*/
	/*   Realiza a corbertura da linha e atualiza colunas que		*/
	/*    cobrem a linha         									*/
	/* Par�metros                                                   */
	/*   int i_pIndiceColuna - input - �ndice da coluna selecionada */
	/*--------------------------------------------------------------*/
	void CobreLinha(){
		int i_wI;
		if (!b_aCoberta){
			for (i_wI = 0; i_wI < v_aColunas.size(); i_wI++){
				v_aColunas[i_wI]->i_aLinhasCobertas--;
			}
		}
		b_aCoberta = true;
	}
};

/* Matriz Esparsa */
class MatrizEsparsa{
public:
	/*--------------*/
	/* Atributos    */
	/*--------------*/
	int i_aLinhasDescobertas;           /* Quantidade de linhas Descobertas    */
	int i_aColunasSelecionadas;         /* Quantidade de Colunas selecionadas  */
	std::vector<Linha*> v_aLinhas;		/* Linhas da Matriz                    */
	std::vector<Coluna*> v_aColunas;	/* Colunas da Matriz                   */
	std::string s_aNomeArquivo;         /* Nome do arquivo da Matriz lida      */

	/*--------------*/
	/* Construtores */
	/*--------------*/
	MatrizEsparsa(){}
	~MatrizEsparsa(){}

	/*--------------*/
	/* M�todos      */
	/*--------------*/

	/*-----------------------------------------------------------*/
	/* M�todo LeArquivoSSP                                       */
	/*   L� um arquivo no formato de Shortest Paths (SSP) e cria */
	/*   a inst�ncia utilizada no problema                       */
	/* Par�metros                                                */
	/*   char* arquivo - input  - Caminho completo arquivo SSP   */
	/*-----------------------------------------------------------*/
	void LeArquivSSP(char * s_pNomeArquivo){
		/*----------------*/
		/* Vari�veis      */
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

		// L� arquivo caracter por caracter
		i_wI = 0;
		while (f_wArquivo >> c_wChar) {

			// Realiza a��o de acordo com caracter lido e estado da leitura
			switch (c_wChar)
			{
				/* Lendo in�cio do par ordenado ou do caminho */
			case ('[') :
				if (!b_wLeuPar){
					// Se est� lendo o par origem destino ap�s o [ est� a origem
					f_wArquivo >> i_wOrigem;
				}
				else {
					// Se est� lendo o caminho ap�s o [ deve ler outro [ e depois est� o primeiro n�
					f_wArquivo >> c_wChar;
					f_wArquivo >> i_wNode;

					// Deve ser realizada refer�ncia cruzada entre Linha e Coluna
					v_aLinhas[i_wI]->AddColuna(v_aColunas[i_wNode]);
					v_aColunas[i_wNode]->AddLinha(v_aLinhas[i_wI]);
				}
				break;

				/* Lendo dentro do par ordenado ou do caminho */
			case (',') :
				if (!b_wLeuPar){
					// Se est� lendo o par origem destino ap�s a , est� o Destino
					f_wArquivo >> i_wDestino;
				}
				else{
					// Se est� lendo o caminho ap�s a , est� um n�
					f_wArquivo >> i_wNode;

					// Deve ser realizada refer�ncia cruzada entre Linha e Coluna
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

					// Terminou de ler caminho, aponta para ler a pr�xima linha e seta a flag para ler o Par
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
	/* M�todo SelecionaColuna										*/
	/*   Realiza a corbertura das linhas apontadas pela coluna		*/
	/*    passada como par�metro									*/
	/* Par�metros                                                   */
	/*   int i_pIndiceColuna - input - �ndice da coluna selecionada */
	/*--------------------------------------------------------------*/
	void SelecionaColuna(int i_pIndiceColuna){
		int i_wI;

		// Atualiza os contadores de linhas cobertas e colunas selecionadas
		i_aColunasSelecionadas++;
		i_aLinhasDescobertas -= v_aColunas[i_pIndiceColuna]->i_aLinhasCobertas;

		// Realiza a cobertura das linhas
		//TODO: Era pra ter feito um m�todo na coluna, mas n�o compila porque n�o reconhece o m�todo da classe Linha
		v_aColunas[i_pIndiceColuna]->b_aSelecionada = true;
		for (i_wI = 0; i_wI < v_aColunas[i_pIndiceColuna]->v_aLinhas.size(); i_wI++){
			v_aColunas[i_pIndiceColuna]->v_aLinhas[i_wI]->CobreLinha();
		}
	}

	/*--------------------------------------------------------------*/
	/* M�todo Imprime												*/
	/*   Imprime a matriz											*/
	/*--------------------------------------------------------------*/
	void Imprime(){
		int i_wI;
		int i_wJ;
		int i_wK;

		// Imprime cabe�alho das colunas, considera n�meros de at� 3 d�gitos e um * para indicar se foi ou n�o selecionada
		std::cout << "|           ";
		for (i_wI = 0; i_wI < v_aColunas.size(); i_wI++){
			std::cout << "| ";
			if (v_aColunas[i_wI]->b_aSelecionada) std::cout << "*";
			else std::cout << " ";
			std::cout << std::setfill(' ') << std::setw(3) << v_aColunas[i_wI]->i_aID << " ";
		}
		std::cout << "|" << std::endl;

		// Imprime as linhas, considerando de at� 3 d�gitos no cabe�alho
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
	/* M�todo ImprimeDot											*/
	/*   Imprime a rede para o graphviz, destacando os observadores */
	/*--------------------------------------------------------------*/
	void ImprimeDot(int i_pSeq){
		std::size_t st_wPosStr;
		std::string s_wArquivoDot;
		std::string s_wTexto;
		std::string s_wHeader;
		std::string s_wCorpo;
		std::string s_wFooter;
		std::stringstream s_wStream;
		std::ofstream f_wArquivo;
		int i_wI;
		int i_wJ;
		int i_wK;
		
		st_wPosStr = s_aNomeArquivo.find("instGraph");
		s_wArquivoDot = s_aNomeArquivo.substr(st_wPosStr);
		s_wArquivoDot.resize(s_wArquivoDot.size() - 4);
		s_wStream << "_Seq_" << i_pSeq << ".dot";
		s_wArquivoDot += s_wStream.str();
		
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
			if (v_aColunas[i_wI]->b_aSelecionada) s_wStream << "blue";
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
	}
};

/*--------------------------------------*/
/* Fun��es                              */
/*--------------------------------------*/

/*-----------------------------------------------------------*/
/* Fun��o ComparaColuna                                      */
/*   Fun��o de ordena��o das Colunas.						 */
/*	 Ordena o vetor de colunas de maneira que a coluna que   */
/*    cobre a maior quantiedade de linhas fique no in�cio    */
/*	  do vector.		                                     */
/*   Utilizada apenas na fun��o sort.                        */
/*-----------------------------------------------------------*/
bool ComparaColuna(Coluna *c1, Coluna* c2){
	return c1->i_aLinhasCobertas > c2->i_aLinhasCobertas;
}

/*-----------------------------------------------------------*/
/* Fun��o getNomeSo                                          */
/*   Fun��o que obt�m o sistema operacional da m�quina.      */
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
/* Fun��o getNomeSo                                          */
/*   Fun��o que obt�m o caminho da pasta de inst�ncias.      */
/*	 Retorna uma string com o caminho da inst�ncia.          */
/*-----------------------------------------------------------*/
std::string caminhoInput()
{
	if (getNomeSo() == "Unix" || getNomeSo() == "Linux")
		return "../GraphGenerator/input/";
	if (getNomeSo() == "Windows 32-bit" || getNomeSo() == "Windows 64-bit")
		return "..\\GraphGenerator\\input\\";
	else
		return "";
}

/*-----------------------------------------------------------*/
/* Fun��o listaArquivos                                      */
/*   Fun��o que obt�m lista de instancias dada uma extensao. */
/*	 Retorna uma lista de strings com os nomes dos arquivos  */
/*-----------------------------------------------------------*/
std::vector<std::string> listaArquivos(std::string extensao)
{
	std::vector<std::string> lista;
	
    DIR *dir = NULL;
    struct dirent *drnt = NULL;
    std::string nomeArquivo = "";
    std::string caminhoPasta = caminhoInput();

    dir=opendir(caminhoPasta.c_str());
    if(dir)
    {
        while(drnt = readdir(dir))
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

/*--------------------------------------*/
/* Aplica��o                            */
/*--------------------------------------*/
int main(int argc, char** argv){

	MatrizEsparsa o_wMatriz;
	float f_wAlpha = 0;
	int i_wTamanhoListaCandidatos;
	int i_wColunaSelecionada;
	int i_wSeq = 1;
	std::vector<std::string> pasta;

	// L� a inst�nica
	//TODO: Fazer um loop para ler a pasta 
	
	pasta = listaArquivos(".ssp");
	
	for(int it=0;it<pasta.size();it++)
	{
		i_wSeq = 1;
		o_wMatriz.LeArquivSSP((char *)pasta[it].data());
		o_wMatriz.ImprimeDot(i_wSeq);
		i_wSeq++;
		
		//o_wMatriz.Imprime();
		while (o_wMatriz.i_aLinhasDescobertas > 0){
			// Ordena as colunas com rela��o ao n�mero de linhas cobertas
			std::sort(o_wMatriz.v_aColunas.begin(), o_wMatriz.v_aColunas.end() - o_wMatriz.i_aColunasSelecionadas, ComparaColuna);
			
			// Calcula o tamanho da lista de candidatos
			i_wTamanhoListaCandidatos = (o_wMatriz.v_aColunas.size() - o_wMatriz.i_aColunasSelecionadas) * 1;
			
			// Seleciona a coluna na lista de candidatos
			i_wColunaSelecionada = rand() % i_wTamanhoListaCandidatos;
			
			// Realiza a sele��o da coluna na matriz
			o_wMatriz.SelecionaColuna(i_wColunaSelecionada);
			
			// move a coluna selecionada para a �ltima posi��o
			std::swap(o_wMatriz.v_aColunas[i_wColunaSelecionada], o_wMatriz.v_aColunas[o_wMatriz.v_aColunas.size() - o_wMatriz.i_aColunasSelecionadas]);
		}
		o_wMatriz.ImprimeDot(i_wSeq);
		i_wSeq++;
	}
	
	return 0;

}

