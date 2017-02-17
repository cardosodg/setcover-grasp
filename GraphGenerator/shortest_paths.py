import glob
import networkx as nx

filesArray = glob.glob("instGraph*.txt")
for i in xrange(0,len(filesArray)):
    G = nx.Graph()
    numVert = 0
    numEdges = 0
    with open(filesArray[i]) as inputData:
		
		for line in inputData:
			if line.strip().split()[0] == 'COORD_X_Y':
				numVert = int(line.strip().split()[1])
				break
		
		for line in inputData:
			if line.strip().split()[0] == 'LINKS_SOURCE_DESTINATION_DISTANCE':
				break

		for line in inputData:
			data = line.split()
			origin = int(data[0])
			destiny = int(data[1])
			if(origin != destiny and origin < destiny):
				G.add_edge(origin, destiny)
	
	
    pairNode = []
    allPaths = []
    fileOutput = ""
    countPath = 0
	
    singleSP = inputData.name[:len(inputData.name)-4] + ".ssp"
    allSP = inputData.name[:len(inputData.name)-4] + ".esp"
    
    betweennessFile = inputData.name[:len(inputData.name)-4] + "_BETWEENNESS.cnt"
    closenessFile = inputData.name[:len(inputData.name)-4] + "_CLOSENESS.cnt"
    degreeFile = inputData.name[:len(inputData.name)-4] + "_DEGREE.cnt"
    loadFile = inputData.name[:len(inputData.name)-4] + "_LOAD.cnt"
    
    fileOut = open(singleSP, 'w')
    for j in xrange(0,numVert):
		for k in xrange(0,numVert):
			if(j != k and j < k):
				pairNode = [j, k]
				allPaths = ([[p for p in nx.shortest_path(G, source=j, target=k)]])
				fileOutput += str(pairNode) + " " + str(allPaths) + "\n"
				countPath += len(allPaths)
    fileOut.write(str(numVert) + " " + str(countPath) + "\n")
    fileOut.write(fileOutput)
    fileOut.close()
    
    pairNode = []
    allPaths = []
    fileOutput = ""
    countPath = 0

    fileOut = open(allSP, 'w')
    for j in xrange(0,numVert):
		for k in xrange(0,numVert):
			if(j != k and j < k):
				pairNode = [j, k]
				allPaths = ([p for p in nx.all_shortest_paths(G, source=j, target=k)])
				fileOutput += str(pairNode) + " " + str(allPaths) + "\n"
				countPath += len(allPaths)
    fileOut.write(str(numVert) + " " + str(countPath) + "\n")
    fileOut.write(fileOutput)
    fileOut.close()

    fileOut = open(betweennessFile, 'w')
    cc = nx.betweenness_centrality(G, normalized=False)
    fileOut.write(str(numVert) + "\n")
    for(k,v) in cc.items():
		fileOut.write(str(k) + " " + str(v) + "\n")
    fileOut.close();

    fileOut = open(closenessFile, 'w')
    cc = nx.closeness_centrality(G, normalized=False)
    fileOut.write(str(numVert) + "\n")
    for(k,v) in cc.items():
		fileOut.write(str(k) + " " + str(v) + "\n")
    fileOut.close();

    fileOut = open(degreeFile, 'w')
    cc = nx.degree_centrality(G)
    fileOut.write(str(numVert) + "\n")
    for(k,v) in cc.items():
		fileOut.write(str(k) + " " + str(v) + "\n")
    fileOut.close();
    
    fileOut = open(loadFile, 'w')
    cc = nx.load_centrality(G, normalized=False)
    fileOut.write(str(numVert) + "\n")
    for(k,v) in cc.items():
		fileOut.write(str(k) + " " + str(v) + "\n")
    fileOut.close();
