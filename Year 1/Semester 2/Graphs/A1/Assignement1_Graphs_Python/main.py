from ui import UI

if __name__ == '__main__':
    ui = UI()
    ok = True

    while ok:
        ui.printMenu()
        cmd = int(input("Please, choose one option: "))

        if cmd == 0:
            ok = False

        elif cmd == 1:
            ui.createRandomGraph()

        elif cmd == 2:
            ui.printNrOfVertices()

        elif cmd == 3:
            ui.printNrOfEdges()

        elif cmd == 4:
            ui.printVertices()

        elif cmd == 5:
            ui.printEdges()

        elif cmd == 6:
            ui.readGraphFromFile()

        elif cmd == 7:
            ui.writeGraphInFile()

        elif cmd == 8:
            ui.seeIfIsEdge()

        elif cmd == 9:
            ui.printDegreesOfVertices()

        elif cmd == 10:
            ui.printInboundEdgesOfVertex()

        elif cmd == 11:
            ui.printOutboundEdgesOfVertex()

        elif cmd == 12:
            ui.modifyCostOfEdge()

        elif cmd == 13:
            ui.retrieveCostOfEdge()

        elif cmd == 14:
            ui.addVertex()

        elif cmd == 15:
            ui.removeVertex()

        elif cmd == 16:
            ui.addEdge()

        elif cmd == 17:
            ui.removeEdge()

        else:
            print("Bad command!")