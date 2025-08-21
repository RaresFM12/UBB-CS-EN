#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <exception>
#include <map>
#include "undirected_graph.h"

class UI {
private:
	UndirectedGraph g;

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
		std::cout << "9) Print the adjacent edges of a vertex\n";
		std::cout << "10) Modify the cost of an edge\n";
		std::cout << "11) Retrieve the cost of an edge\n";
		std::cout << "12) Add a vertex\n";
		std::cout << "13) Remove a vertex\n";
		std::cout << "14) Add an edge\n";
		std::cout << "15) Remove an edge\n";
		std::cout << "16) See all connected components\n";
		std::cout << "16) See all connected components\n";
		std::cout << "17) Find the minimal spanning tree with Kruskal\n";
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
		std::ifstream fin("graph1.in");

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

		if (g.is_edge(v1, v2) || g.is_edge(v2, v1))
			std::cout << "There is an edge between " << v1 << " and " << v2 << "\n";
		else
			std::cout << "There is no edge between " << v1 << " and " << v2 << "\n";
	}


	void printAdjacentEdgesOfVertex()
	{
		int v;
		std::cout << "The vertex: ";
		std::cin >> v;

		try {
			std::vector<int> out_edg = g.get_adjacent_vertices(v);

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

	void connected_components()
	{
		std::vector<int> vec = g.get_vertices();

		// We look for the max value in the vertices, in case we removed a vertex
		int max = -1;
		for (auto v : vec)
			if (v > max)
				max = v;

		bool* visited = new bool[max + 1];

		// Mark all the vertices as not visited
		for (int i = 0; i <= max; ++i)
			visited[i] = false;

		int cnt = 1;
		std::vector<int> comp;
		for (auto v : vec)
			if (!visited[v])
			{
				comp.clear(); 
				g.DFS(v, visited, comp); // we go through every component

				std::cout << cnt << ": ";
				for (int i = 0; i < comp.size(); ++i)
					std::cout << comp[i] << ' ';

				++cnt;
				std::cout << '\n';
			}

		// we deallocate the space
		delete[] visited;
	}

	void find_mst_ui()
	{
		std::pair<std::vector<std::pair<std::pair<int, int>, int>>, int> res =
			g.Kruskal_MST();

		std::vector<std::pair<std::pair<int, int>, int>> mst = res.first;
		int total_cost = res.second;

		if (mst.size() == g.get_nr_of_vertices() - 1)
		{
			std::cout << "Minimal Spanning Tree (MST) has been found and the total cost is: " << total_cost << '\n';
			for (auto edge : mst)
				std::cout << "Edge from " << edge.first.first << " to " <<
				edge.first.second << " with cost " << edge.second << '\n';
		}
		else
			std::cout << "Unable to find MST.The graph might not be connected.\n";
	}
};