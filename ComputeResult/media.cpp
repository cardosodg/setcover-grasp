#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct lineFile
{
 double procTime, nbObservers, loops;
 int netSize;
} fileDeal;

const int nbInstances = 10;

bool MySort(fileDeal a, fileDeal b)
{
 return (a.netSize < b.netSize);
}

main(int argc, char** argv)
{
 ifstream inputFile;
 ofstream outputFile;
 double totalTime, totalObservers, loops;
 int netSize;

 vector<fileDeal> results;
 fileDeal object;

 // TODO: Alterar forma de entrada e saida de arquivos.
 inputFile.open(argv[1]);
 outputFile.open(argv[2]);

 while (inputFile >> object.netSize >> object.nbObservers >> object.procTime >> object.loops)
 {
	 results.push_back(object);
 }

 sort(results.begin(),results.end(),MySort);

 for(int i=0;i<results.size();i+=nbInstances)
 {
  totalTime=0.0;
  totalObservers=0.0;
  loops=0.0;
  for(int j=0;j<nbInstances;j++)
  {
   netSize = results[i+j].netSize;
   totalTime += results[i+j].procTime;
   totalObservers += results[i+j].nbObservers;
   loops += results[i+j].loops;
  }

  outputFile << netSize << " " << totalObservers/nbInstances << " " << totalTime/nbInstances << " " << loops/nbInstances << endl;

 }

 inputFile.close();
 outputFile.close();
}
