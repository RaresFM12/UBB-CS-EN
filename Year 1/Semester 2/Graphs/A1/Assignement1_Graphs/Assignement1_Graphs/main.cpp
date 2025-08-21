#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <exception>
#include <map>


class DirectedGraph {
private:
	std::map<int, std::vector<int>> inbounds;
	std::map<int, std::vector<int>> outbounds;
	std::map<std::pair<int, int>, int> cost;

public:
	// Constructors
	DirectedGraph()
	{}

	DirectedGraph(int nrVertices)
	{
		for (int i = 0; i < nrVertices; ++i)
		{
			inbounds[i] = std::vector<int>();
			outbounds[i] = std::vector<int>();
		}
	}

	// Copy constructor
	DirectedGraph(const DirectedGraph& g)
	{
		inbounds = g.inbounds;
		outbounds = g.outbounds;
		cost = g.cost;
	}

	// Destructor
	~DirectedGraph()
	{}

	// Removes all vertices and edges
	void clear()
	{
		inbounds.clear();
		outbounds.clear();
		cost.clear();
	}

	// Checks if a vertex already exists
	bool is_vertex(int v) const
	{
		if (inbounds.find(v) != inbounds.end())
			return true;

		return false;
	}

	// Checks if an edge already exists
	bool is_edge(int v1, int v2) 
	{
		if (std::find(outbounds[v1].begin(), outbounds[v1].end(), v2) != outbounds[v1].end())
			return true;

		return false;
	}

	// Returns the number of vertices of the graph
	unsigned long get_nr_of_vertices() const
	{
		return outbounds.size();
	}

	// Returns the number of edges of the graph
	unsigned long get_nr_of_edges() const
	{
		return cost.size();
	}

	// Returns all the vertices of the graph
	std::vector<int> get_vertices() const noexcept
	{
		std::vector<int> v;
		for (auto it = inbounds.begin(); it != inbounds.end(); ++it)
			v.push_back(it->first);

		return v;
	}

	// Returns all the edges of the graph
	std::vector<std::pair<int, int>> get_edges() const
	{
		std::vector<std::pair<int, int>> e;
		for (auto it = cost.begin(); it != cost.end(); ++it)
			e.push_back(it->first);

		return e;
	}

	// Returns all the inbound vertices of a specific vertex
	std::vector<int> get_inbound_vertices(int v) 
	{
		if (!is_vertex(v))
			throw std::exception("This vertex is not in the list!");

		return inbounds[v];
	}

	// Returns all the outbound vertices of a specific vertex
	std::vector<int> get_outbound_vertices(int v) 
	{
		if (!is_vertex(v))
			throw std::exception("This vertex is not in the list!");

		return outbounds[v];
	}

	// Adds a vertex to the graph
	bool add_vertex(int v)
	{
		if (is_vertex(v))
			return false;

		inbounds[v] = std::vector<int>();
		outbounds[v] = std::vector<int>();
		return true;
	}

	// Removes a vertex from the graph
	bool remove_vertex(int v)
	{
		if (!is_vertex(v))
			return false;

		std::vector<int> vec = inbounds[v];
		for (auto v2 : vec)
			remove_edge(v2, v);

		inbounds.erase(v);

		vec = outbounds[v];
		for (auto v2 : outbounds[v])
			remove_edge(v, v2);

		outbounds.erase(v);
		return true;
	}

	// Adds an edge to the graph
	bool add_edge(int v1, int v2, int c)
	{
		if (!is_vertex(v1) || !is_vertex(v2) || is_edge(v1, v2))
			return false;

		cost[std::make_pair(v1, v2)] = c ;
		outbounds[v1].push_back(v2);
		inbounds[v2].push_back(v1);
		return true;
	}

	// Removes an edge from the graph
	bool remove_edge(int v1, int v2)
	{
		if (!is_edge(v1, v2))
			return false;

		for (auto& elem : cost)
			if (elem.first.second == v2 && elem.first.first == v1)
			{
				cost.erase(elem.first);
				break;
			}
		
		inbounds[v2].erase(find(inbounds[v2].begin(), inbounds[v2].end(), v1));
		outbounds[v1].erase(find(outbounds[v1].begin(), outbounds[v1].end(), v2));
		return true;
	}

	// Returns the in degree of a vertex
	unsigned long get_in_degree(int v)
	{
		if (!is_vertex(v))
			throw std::exception("This vertex is not in the list!");

		return get_inbound_vertices(v).size();
	}

	// Returns the out degree of a vertex
	unsigned long get_out_degree(int v)
	{
		if (!is_vertex(v))
			throw std::exception("This vertex is not in the list!");

		return get_outbound_vertices(v).size();
	}

	// Sets the cost of an edge
	void set_cost(int v1, int v2, int c)
	{
		if (!is_edge(v1, v2))
			throw std::exception("This edge is not in the list!");

		cost[std::make_pair(v1, v2)] = c;
	}

	// Returns the cost of an edge
	long long get_cost(int v1, int v2) 
	{
		if (!is_edge(v1, v2))
			throw std::exception("This edge is not in the list!");

		return cost[std::make_pair(v1, v2)];
	}

	// Generates a random graph
	void generate_random_graph(int nrv, int nre)
	{
		for (int i = 0; i < nrv; ++i)
			add_vertex(i);

		while (get_nr_of_edges() < nre)
		{
			int v1 = rand() % nrv;
			int v2 = rand() % nrv;
			int c = rand() % 100;

			add_edge(v1, v2, c);
		}
	}
};

class UI {
private:
	DirectedGraph g;

public:
	UI() {}

	~UI() {}

	void printMenu()
	{
		std::cout << "\n=========== The menu ===========\n";
		std::cout << "1) Create random graph\n";
		std::cout << "2) Print the number of vertices\n";
		std::cout << "3) Print the number of edges\n";
		std::cout << "4) Print the vertices of the graph\n";
		std::cout << "5) Print the edges of the graph\n";
		std::cout << "6) Read the graph from a file\n";
		std::cout << "7) Write the graph in a file\n";
		std::cout << "8) See if there is an edge\n";
		std::cout << "9) Print the in degree and out degree of a vertex\n";
		std::cout << "10) Print the inbound edges of a vertex\n";
		std::cout << "11) Print the outbound edges of a vertex\n";
		std::cout << "12) Modify the cost of an edge\n";
		std::cout << "13) Retrieve the cost of an edge\n";
		std::cout << "14) Add a vertex\n";
		std::cout << "15) Remove a vertex\n";
		std::cout << "16) Add an edge\n";
		std::cout << "17) Remove an edge\n";
		std::cout << "18) Print copy graph\n";
		std::cout << "0) Exit\n";
	}

	void createRandomGraph()
	{
		g.clear();
		int v = 0, e = 0;
		std::cout << "The number of vertices: ";
		std::cin >> v;
		std::cout << "The number of edges: ";
		std::cin >> e;

		if (v * v < e)
		{
			std::cout << "This graph cannot be generated!\n";
			return;
		}

		g.generate_random_graph(v, e);
	}

	void printNrOfVertices() const noexcept
	{
		std::cout << "The number of vertices is: " << g.get_nr_of_vertices() << "\n";
	}

	void printNrOfEdges() const noexcept
	{
		std::cout << "The number of edges is: " << g.get_nr_of_edges() << "\n";
	}

	void printVertices() const noexcept
	{
		std::cout << "The vertices of the graph are: ";
		std::vector<int> vertices = g.get_vertices();
		for (auto v : vertices)
			std::cout << v << ' ';
		std::cout << "\n";
	}

	void printEdges() noexcept
	{
		std::cout << "The edges of the graph are:\n";
		std::vector<std::pair<int, int>> edg = g.get_edges();
		for (auto e : edg)
			std::cout << e.first << " -> " << e.second << " and the cost is: " << g.get_cost(e.first, e.second) << "\n";
	}

	void readGraphFromFile() noexcept
	{
		g.clear();
		std::ifstream fin("graph.in");

		int v, e;
		int v1, v2, c;

		fin >> v >> e;
		if (v * v < e)
		{
			std::cout << "This graph cannot be generated!\n";
			return;
		}

		for (int i = 0; i < v; ++i)
			g.add_vertex(i);

		for (int i = 1; i <= e; ++i)
		{
			fin >> v1 >> v2 >> c;
			g.add_edge(v1, v2, c);
		}

		std::cout << "The graph was read succesfully!\n";
		fin.close();
	}

	void writeGraphInFile()
	{
		// Clear the content from the out file
		std::ofstream fout("graph.out");

		fout << g.get_nr_of_vertices() << ' ' << g.get_nr_of_edges() << "\n";
		std::vector<std::pair<int, int>> edg = g.get_edges();
		for (auto e : edg)
			fout << e.first << " " << e.second << " " << g.get_cost(e.first, e.second) << "\n";
		
		std::cout << "The graph was printed in the out file!\n";
		fout.close();
	}

	void seeIfIsEdge()
	{
		int v1, v2;
		std::cout << "Choose the edges: ";
		std::cin >> v1 >> v2;

		if (g.is_edge(v1, v2))
			std::cout << "There is an edge between " << v1 << " and " << v2 << "\n";
		else
			std::cout << "There is no edge between " << v1 << " and " << v2 << "\n";
	}

	void printDegreesOfVertices()
	{
		int v;
		std::cout << "The vertex: ";
		std::cin >> v;

		try {
			int nr_in = g.get_in_degree(v);
			int nr_out = g.get_out_degree(v);

			std::cout << "The in degree of the vertex is: " << nr_in << "\n";
			std::cout << "The out degree of the vertex is: " << nr_out << "\n";
		}
		catch (const std::exception& e) {
			std::cout << e.what() << "\n";
		}
	}

	void printInboundEdgesOfVertex()
	{
		int v;
		std::cout << "The vertex: ";
		std::cin >> v;

		try {
			std::vector<int> in_edg = g.get_inbound_vertices(v);

			for (auto e : in_edg)
				std::cout << e << " -> " << v << " and the cost is: " << g.get_cost(e, v) << "\n";
		}
		catch (const std::exception& e) {
			std::cout << e.what() << "\n";
		}
	}

	void printOutboundEdgesOfVertex()
	{
		int v;
		std::cout << "The vertex: ";
		std::cin >> v;

		try {
			std::vector<int> out_edg = g.get_outbound_vertices(v);

			for (auto e : out_edg)
				std::cout << v << " -> " << e << " and the cost is: " << g.get_cost(v, e) << "\n";
		}
		catch (const std::exception& e) {
			std::cout << e.what() << "\n";
		}
	}

	void modifyCostOfEdge()
	{
		int v1, v2, c;
		std::cout << "The vertices are: ";
		std::cin >> v1 >> v2;
		std::cout << "The new cost is: ";
		std::cin >> c;

		try {
			g.set_cost(v1, v2, c);
			std::cout << "The update was a succes!\n";
		}
		catch (const std::exception& e) {
			std::cout << e.what() << "\n";
		}
	}

	void retrieveCostOfEdge()
	{
		int v1, v2;
		std::cout << "The vertices are: ";
		std::cin >> v1 >> v2;

		try {
			int nr = g.get_cost(v1, v2);
			std::cout << "The edge " << v1 << " -> " << v2 << " has the cost " << nr << "\n";
		}
		catch (const std::exception& e) {
			std::cout << e.what() << "\n";
		}
	}

	void addVertex()
	{
		int v;
		std::cout << "The vertex you want to add: ";
		std::cin >> v;

		if (g.add_vertex(v))
			std::cout << "The vertex was succesfully added!\n";
		else
			std::cout << "The vertex is already in the graph!\n";
	}

	void removeVertex()
	{
		int v;
		std::cout << "The vertex you want to remove: ";
		std::cin >> v;

		if (g.remove_vertex(v))
			std::cout << "The vertex was succesfully removed!\n";
		else
			std::cout << "The vertex is not in the graph!\n";
	}

	void addEdge()
	{
		int v1, v2, c;
		std::cout << "The endpoints of the new edge: ";
		std::cin >> v1 >> v2;
		std::cout << "The cost: ";
		std::cin >> c;

		if (g.add_edge(v1, v2, c))
			std::cout << "The edge was succesfully added!\n";
		else
			std::cout << "The edge is already in the graph!\n";
	}

	void removeEdge()
	{
		int v1, v2;
		std::cout << "The endpoints of the edge you want to remove: ";
		std::cin >> v1 >> v2;

		if (g.remove_edge(v1, v2))
			std::cout << "The edge was succesfully removed!\n";
		else
			std::cout << "The edge is not in the graph!\n";
	}

	void printCopyGraph()
	{
		DirectedGraph gr = DirectedGraph(this->g);
		gr.remove_vertex(0);
		std::cout << "The edges of the copied graph are:\n";
		std::vector<std::pair<int, int>> edg = gr.get_edges();
		for (auto e : edg)
			std::cout << e.first << " -> " << e.second << " and the cost is: " << gr.get_cost(e.first, e.second) << "\n";
	}
};

int main()
{
	UI ui;
	int cmd = 0;
	bool ok = true;

	while (ok)
	{
		ui.printMenu();
		std::cout << "Please, choose one option: ";
		std::cin >> cmd;

		if (cmd == 0)
			ok = false;

		else if (cmd == 1)
			ui.createRandomGraph();

		else if (cmd == 2)
			ui.printNrOfVertices();

		else if (cmd == 3)
			ui.printNrOfEdges();

		else if (cmd == 4)
			ui.printVertices();

		else if (cmd == 5)
			ui.printEdges();

		else if (cmd == 6)
			ui.readGraphFromFile();

		else if (cmd == 7)
			ui.writeGraphInFile();

		else if (cmd == 8)
			ui.seeIfIsEdge();

		else if (cmd == 9)
			ui.printDegreesOfVertices();

		else if (cmd == 10)
			ui.printInboundEdgesOfVertex();

		else if (cmd == 11)
			ui.printOutboundEdgesOfVertex();

		else if (cmd == 12)
			ui.modifyCostOfEdge();

		else if (cmd == 13)
			ui.retrieveCostOfEdge();

		else if (cmd == 14)
			ui.addVertex();

		else if (cmd == 15)
			ui.removeVertex();

		else if (cmd == 16)
			ui.addEdge();

		else if (cmd == 17)
			ui.removeEdge();

		else if (cmd == 18)
			ui.printCopyGraph();

		else
			std::cout << "Bad command!\n";
	}
	
	return 0;
}