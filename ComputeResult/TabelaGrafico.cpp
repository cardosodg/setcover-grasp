#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

typedef struct lineFile
{
 double procTime, nbObservers;
 int netSize;
 
} fileDeal;


main(int argc, char** argv)
{
 ifstream inputGreed, inputLs, inputGrasp;
 ofstream outputTable;
 string header="", body="", footer="", table="";
 vector<fileDeal> resultGreed, resultLs, resultGrasp;
 fileDeal object;
 
 header = "\\begin {table}[h]\n";
 header += "\\centering\n";
 header += "\\caption{}\n";
 header += "\\begin{small}\n";
 header += "\\begin{tabular}{|c|r|r|r|r|r|r|}\n";
 header += "\\hline\n";
 header += "          & \\multicolumn{2}{c|}{GREED} & \\multicolumn{2}{c|}{LS} & \\multicolumn{2}{c|}{GRASP} \\\\ \n";
 header += "\\cline{2-7}\n";
 header += "  $|V|$   &  obser. & tempo (s)  & obser. & tempo (s) & obser. & tempo (s)\\\\ \n";
 header += "\\hline\n";

 footer = "\\hline\n";
 footer += "\\end{tabular} \\label{}\n";
 footer += "\\end{small}\n";
 footer += "\\end{table}\n";
 
 
 inputGreed.open("GREED.txt");
 while (inputGreed >> object.netSize >> object.nbObservers >> object.procTime)
 {
	 resultGreed.push_back(object);
 }
 inputGreed.close();
 
 inputLs.open("LS.txt");
 while (inputLs >> object.netSize >> object.nbObservers >> object.procTime)
 {
	 resultLs.push_back(object);
 }
 inputLs.close();
 
 inputGrasp.open("GRASP.txt");
 while (inputGrasp >> object.netSize >> object.nbObservers >> object.procTime)
 {
	 resultGrasp.push_back(object);
 }
 inputGrasp.close();

 for(int i=0;i<resultGreed.size();i++)
 {
	 ostringstream line;
	 line << resultGreed[i].netSize << " & " << resultGreed[i].nbObservers << " & " << resultGreed[i].procTime << " & ";
	 line << resultLs[i].nbObservers << " & " << resultLs[i].procTime << " & ";
	 line << resultGrasp[i].nbObservers << " & " << resultGrasp[i].procTime << " \\\\ ";
	 
	 body += line.str() + "\n";
 }

 table = header + body + footer;

 outputTable.open("Table_Latex.txt");
 outputTable << table;
 outputTable.close();

 system("gnuplot plot_observadores.plt");
 system("gnuplot plot_tempo.plt");

}
