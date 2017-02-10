import networkx as nx

filesArray = ["abilene_TOPOLOGY","AS1221_TOPOLOGY","AS1239_TOPOLOGY","AS2914_TOPOLOGY","AS3257_TOPOLOGY","AS3356_TOPOLOGY","AS7018_TOPOLOGY","Fossi_TOPOLOGY","geant_TOPOLOGY"]

for i in xrange(0,len(filesArray)):
    G = nx.Graph()
    numVert = 0
    numEdges = 0
    with open(filesArray[i]) as f:
        header = f.readline()
        headerData = header.split()
        numVert = int(headerData[0])
        numEdges = int(headerData[1])
        for line in f:
            data = line.split()
            G.add_edge(int(data[0]), int(data[1]))

    pairNode = []
    allPaths = []

    fileName = filesArray[i] + "_ASP"
    fileNameCC = filesArray[i] + "_CLOSENESS"
    fileNameDC = filesArray[i] + "_DEGREE"
    fileNameCFBC = filesArray[i] + "_CURRENTFLOW"
    fileNameLC = filesArray[i] + "_LOAD"
    fileNameDP = filesArray[i] + "_DSP"

    fileOut = open(fileName, 'w')
    for i in xrange(1,numVert+1):
        for j in xrange(1,numVert+1):
            if(i != j and i < j):
                pairNode = [i, j]
                allPaths = ([p for p in nx.all_shortest_paths(G, source=i, target=j)])
                fileOut.write(str(pairNode) + " " + str(allPaths) + "\n")

    fileOut.close()

    fileOut = open(fileNameDP, 'w')
    paths = nx.all_pairs_dijkstra_path(G)
    for i in xrange(1,numVert+1):
        for j in xrange(1,numVert+1):
            if(i != j and i < j):
                fileOut.write("[%d, %d] " %(i,j) + "[" + str(paths[i][j]) + "]" + "\n")
    fileOut.close()



    fileOut = open(fileNameCC, 'w')
    cc = nx.closeness_centrality(G, normalized=False)
    fileOut.write(str(numVert) + "\n")
    for (k,v) in cc.items():
        fileOut.write((str(k) + " " + str(v) + "\n"))
    fileOut.close()

    fileOut = open(fileNameDC, 'w')
    dc = nx.degree_centrality(G)
    fileOut.write(str(numVert) + "\n")
    for (k,v) in dc.items():
        fileOut.write((str(k) + " " + str(v) + "\n"))
    fileOut.close()

#    fileOut = open(fileNameCFBC, 'w')
#    cfbc = nx.current_flow_betweenness_centrality(G, normalized=False)
#    fileOut.write(str(numVert) + "\n")
#    for (k, v) in cfbc.items():
#        fileOut.write((str(k) + " " + str(v) + "\n"))
#    fileOut.close()

    fileOut = open(fileNameLC, 'w')
    lc = nx.load_centrality(G, normalized=False)
    fileOut.write(str(numVert) + "\n")
    for (k, v) in lc.items():
        fileOut.write((str(k) + " " + str(v) + "\n"))
    fileOut.close()
