from graph import DirectedGraph


class UI:
    def __init__(self):
        self.__graph = DirectedGraph()

    def printMenu(self):
        print("\n=========== The menu ===========")
        print("1) Create random graph")
        print("2) Print the number of vertices")
        print("3) Print the number of edges")
        print("4) Print the vertices of the graph")
        print("5) Print the edges of the graph")
        print("6) Read the graph from a file")
        print("7) Write the graph in a file")
        print("8) See if there is an edge")
        print("9) Print the in degree and out degree of a vertex")
        print("10) Print the inbound edges of a vertex")
        print("11) Print the outbound edges of a vertex")
        print("12) Modify the cost of an edge")
        print("13) Retrieve the cost of an edge")
        print("14) Add a vertex")
        print("15) Remove a vertex")
        print("16) Add an edge")
        print("17) Remove an edge")
        print("0) Exit")

    def createRandomGraph(self):
        self.__graph.clear()

        v = int(input("The number of vertices: "))
        e = int(input("The number of edges: "))

        if v * v < e:
            print("THis graph cannot be generated!")
            return

        self.__graph.generateRandomGraph(v, e)

    def printNrOfVertices(self):
        print(f"The number of vertices is: {self.__graph.getNrOfVertices()}")

    def printNrOfEdges(self):
        print(f"The number of edges is: {self.__graph.getNrOfEdges()}")

    def printVertices(self):
        print("The vertices of the graph are: ", end="")

        l = self.__graph.getVertices()
        for v in l:
            print(v, end=" ")

        print()

    def printEdges(self):
        print("The edges of the graph are: ")

        l = self.__graph.getEdges()
        for e in l:
            print(f"{e[0]} -> {e[1]} and the cost is: {self.__graph.getCost(e[0], e[1])}")

    def readGraphFromFile(self):
        self.__graph.clear()
        file = open("graph.in", "r")
        v, e = file.readline().split()
        v, e = int(v), int(e)

        if v * v < e:
            print("THis graph cannot be generated!")
            return

        for i in range(0, v):
            self.__graph.addVertex(i)

        for i in range(0, e):
            cost = 0
            v1, v2, cost = file.readline().split()
            v1, v2, cost = int(v1), int(v2), int(cost)
            self.__graph.addEdge(v1, v2, cost)

        print("The graph was read succesfully!")

    def writeGraphInFile(self):
        file = open("graph.out", "w")
        edg = self.__graph.getEdges()

        file.write(f"{self.__graph.getNrOfVertices()} {self.__graph.getNrOfEdges()}\n")
        for e in edg:
            file.write(f"{e[0]} {e[1]} {self.__graph.getCost(e[0], e[1])}\n")

        print("The graph was printed in the out file!")

    def seeIfIsEdge(self):
        v1, v2 = input("Choose the edge: ").split()
        v1, v2 = int(v1), int(v2)

        if not self.__graph.isVertex(v1):
            print(f"There is no edge between {v1} and {v2}")
        else:
            if self.__graph.isEdge(v1, v2):
                print(f"There is an edge between {v1} and {v2}")
            else:
                print(f"There is no edge between {v1} and {v2}")

    def printDegreesOfVertices(self):
        v = int(input("The vertex: "))

        try:
            nr_in = self.__graph.getInDegree(v)
            nr_out = self.__graph.getOutDegree(v)

            print(f"The in degree of the vertex: {nr_in}")
            print(f"The out degree of the vertex: {nr_out}")

        except Exception as ex:
            print(ex)

    def printInboundEdgesOfVertex(self):
        v = int(input("The vertex: "))

        try:
            in_edg = self.__graph.getInboundVertices(v)
            for e in in_edg:
                print(f"{e} -> {v} and the cost is: {self.__graph.getCost(e, v)}")

        except Exception as ex:
            print(ex)

    def printOutboundEdgesOfVertex(self):
        v = int(input("The vertex: "))

        try:
            out_edg = self.__graph.getOutboundVertices(v)
            for e in out_edg:
                print(f"{v} -> {e} and the cost is: {self.__graph.getCost(v, e)}")

        except Exception as ex:
            print(ex)

    def modifyCostOfEdge(self):
        v1, v2 = input("The vertices are: ").split()
        v1, v2 = int(v1), int(v2)
        c = int(input("The new cost is: "))

        try:
            self.__graph.setCost(v1, v2, c)
            print("The update was a succes!")

        except Exception as ex:
            print(ex)

    def retrieveCostOfEdge(self):
        v1, v2 = input("The vertices are: ").split()
        v1, v2 = int(v1), int(v2)

        try:
            cost = self.__graph.getCost(v1, v2)
            print(f"{v1} -> {v2} and the cost is: {cost}\n")

        except Exception as ex:
            print(ex)

    def addVertex(self):
        v = int(input("The vertex you want to add: "))

        if self.__graph.addVertex(v):
            print("The vertex was successfully added!")
        else:
            print("The vertex is already in the graph!")

    def removeVertex(self):
        v = int(input("The vertex you want to remove: "))

        if self.__graph.removeVertex(v):
            print("The vertex was successfully removed!")
        else:
            print("The vertex is not in the graph!")

    def addEdge(self):
        v1, v2 = input("The edge you want to add: ").split()
        v1, v2 = int(v1), int(v2)
        c = int(input("The cost of the edge: "))

        if self.__graph.addEdge(v1, v2, c):
            print("The edge was successfully added!")
        else:
            print("The edge is already in the graph!")

    def removeEdge(self):
        v1, v2 = input("The edge you want to add: ").split()
        v1, v2 = int(v1), int(v2)

        if self.__graph.removeEdge(v1, v2):
            print("The edge was successfully removed!")
        else:
            print("The edge is not in the graph!")

    def copyGraph(self):
        gr = self.__graph.copyGraph(self.__graph)
        return gr


