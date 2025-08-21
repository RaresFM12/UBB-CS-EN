from copy import deepcopy
from random import randint


class DirectedGraph:
    def __init__(self):
        self.__inbound = {}
        self.__outbound = {}
        self.__cost = {}

    def clear(self):
        self.__inbound.clear()
        self.__outbound.clear()
        self.__cost.clear()

    def isVertex(self, v):
        if v in self.__inbound:
            return True

        return False

    def isEdge(self, v1, v2):
        if v2 in self.__outbound[v1]:
            return True

        return False

    def getNrOfVertices(self):
        return len(self.__outbound)

    def getNrOfEdges(self):
        return len(self.__cost)

    def getVertices(self):
        l = []
        for v in self.__inbound:
            l.append(v)

        return l

    def getEdges(self):
        l = []
        for e in self.__cost:
            l.append(e)

        return l

    def getInboundVertices(self, v):
        if not self.isVertex(v):
            raise Exception("This vertex is not in the list!")

        return self.__inbound[v]

    def getOutboundVertices(self, v):
        if not self.isVertex(v):
            raise Exception("This vertex is not in the list!")

        return self.__outbound[v]

    def addVertex(self, v):
        if self.isVertex(v):
            return False

        self.__inbound[v] = []
        self.__outbound[v] = []
        return True

    def removeVertex(self, v):
        if not self.isVertex(v):
            return False

        l = deepcopy(self.__inbound[v])
        for v2 in l:
            self.removeEdge(v2, v)

        self.__inbound.pop(v)

        l = deepcopy(self.__outbound[v])
        for v2 in l:
            self.removeEdge(v, v2)

        self.__outbound.pop(v)
        return True

    def addEdge(self, v1, v2, c):
        if not self.isVertex(v1) or not self.isVertex(v2) or self.isEdge(v1, v2):
            return False

        self.__cost[(v1, v2)] = c
        self.__outbound[v1].append(v2)
        self.__inbound[v2].append(v1)
        return True

    def removeEdge(self, v1, v2):
        if not self.isEdge(v1, v2):
            return False

        for elem in self.__cost:
            if elem[0] == v1 and elem[1] == v2:
                self.__cost.pop(elem)
                break

        self.__inbound[v2].remove(v1)
        self.__outbound[v1].remove(v2)
        return True

    def getInDegree(self, v):
        if not self.isVertex(v):
            raise Exception("This vertex is not in the list!")

        return len(self.getInboundVertices(v))

    def getOutDegree(self, v):
        if not self.isVertex(v):
            raise Exception("This vertex is not in the list!")

        return len(self.getOutboundVertices(v))

    def setCost(self, v1, v2, c):
        if not self.isEdge(v1, v2):
            raise Exception("This edge is not in the graph!")

        self.__cost[(v1, v2)] = c

    def getCost(self, v1, v2):
        if not self.isEdge(v1, v2):
            raise Exception("This edge is not in the graph!")

        return self.__cost[(v1, v2)]

    def generateRandomGraph(self, nrv, nre):
        for i in range(0, nrv):
            self.addVertex(i)

        while(self.getNrOfEdges() < nre):
            v1 = randint(0, nrv - 1)
            v2 = randint(0, nrv - 1)
            c = randint(0, 100)
            self.addEdge(v1, v2, c)

    def copyGraph(self, g):
        graph = deepcopy(g)
        return graph

