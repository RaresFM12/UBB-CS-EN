#pragma once
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <exception>
#include <map>

class DijointSet {
private:
	std::vector<int> parent;
	std::vector<int> rank; // the height of the tree

public:
	DijointSet(int n)
	{
		// initially all the vertices are in different sets
		for (int i = 0; i < n; ++i)
		{
			parent.push_back(i); // every element is parent of itself
			rank.push_back(0);
		}
	}

	// Finds the parent of a node v
	int Find(int v)
	{
		if (parent[v] != v)
			parent[v] = Find(parent[v]);

		return parent[v];
	}

	void Union(int u, int v)
	{
		int root_u = Find(u);
		int root_v = Find(v);

		// if the vertices are from different components
		if (root_u != root_v)
		{
			// make a tree with the smaller height
			// we minimize the height of the tree
			if (rank[root_u] > rank[root_v])
				parent[root_v] = root_u;

			else if (rank[root_u] < rank[root_v])
				parent[root_u] = root_v;

			else
			{
				parent[root_v] = root_u;
				rank[root_u] += 1;
			}
		}
	}
};


class UndirectedGraph {
private:
	std::vector<int> vertices;
	std::map<std::pair<int, int>, int> edges;

public:
	// Constructors
	UndirectedGraph()
	{}

	UndirectedGraph(int nrVertices)
	{
		for (int i = 0; i < nrVertices; ++i)
			vertices.push_back(i);
	}

	// Copy constructor
	UndirectedGraph(const UndirectedGraph& g)
	{
		vertices = g.vertices;
		edges = g.edges;
	}

	// Destructor
	~UndirectedGraph()
	{}

	// Removes all vertices and edges
	void clear()
	{
		edges.clear();
	}

	// Checks if a vertex already exists
	bool is_vertex(int v) const
	{
		for (int i = 0; i < vertices.size(); ++i)
			if (vertices[i] == v)
				return true;

		return false;
	}

	// Checks if an edge already exists
	bool is_edge(int v1, int v2)
	{
		if (edges.find(std::make_pair(v1, v2)) != edges.end())
			return true;

		return false;
	}

	// Returns the number of vertices of the graph
	unsigned long get_nr_of_vertices() const
	{
		return vertices.size();
	}

	// Returns the number of edges of the graph
	unsigned long get_nr_of_edges() const
	{
		return edges.size();
	}

	// Returns all the vertices of the graph
	std::vector<int> get_vertices() const noexcept
	{
		return vertices;
	}

	// Returns all the edges of the graph
	std::vector<std::pair<int, int>> get_edges() const
	{
		std::vector<std::pair<int, int>> e;
		for (auto it = edges.begin(); it != edges.end(); ++it)
			e.push_back(it->first);

		return e;
	}

	// Returns all the outbound vertices of a specific vertex
	std::vector<int> get_adjacent_vertices(int v)
	{
		if (!is_vertex(v))
			throw std::exception("This vertex is not in the list!");

		std::vector<int> e;
		for (auto it = edges.begin(); it != edges.end(); ++it)
		{
			if (it->first.first == v)
				e.push_back(it->first.second);

			else if (it->first.second == v)
				e.push_back(it->first.first);
		}

		return e;
	}

	// Adds a vertex to the graph
	bool add_vertex(int v)
	{
		if (is_vertex(v))
			return false;

		vertices.push_back(v);
		return true;
	}

	// Removes a vertex from the graph
	bool remove_vertex(int v)
	{
		if (!is_vertex(v))
			return false;

		
		std::vector<std::pair<int, int>> e = get_edges();
		for (int i = 0; i < e.size(); ++i)
			if (e[i].first == v || e[i].second == v)
				remove_edge(e[i].first, e[i].second);

		vertices.erase(find(vertices.begin(), vertices.end(), v));
		return true;
	}

	// Adds an edge to the graph
	bool add_edge(int v1, int v2, int c)
	{
		if (!is_vertex(v1) || !is_vertex(v2) || (is_edge(v1, v2) || is_edge(v2, v1)))
			return false;

		if (is_edge(v1, v2))
		{
			edges[std::make_pair(v1, v2)] = c;
			return true;
		}

		edges[std::make_pair(v2, v1)] = c;
		return true;
	}

	// Removes an edge from the graph
	bool remove_edge(int v1, int v2)
	{
		if (!is_edge(v1, v2) && !is_edge(v2, v1))
			return false;

		for (auto& elem : edges)
			if ((elem.first.second == v2 && elem.first.first == v1) || elem.first.second == v1 && elem.first.first == v2)
			{
				edges.erase(elem.first);
				break;
			}

		return true;
	}

	// Sets the cost of an edge
	void set_cost(int v1, int v2, int c)
	{
		if (!is_edge(v1, v2) && !is_edge(v2, v1))
			throw std::exception("This edge is not in the list!");

		if (is_edge(v1, v2))
			edges[std::make_pair(v1, v2)] = c;

		if (is_edge(v2, v1))
			edges[std::make_pair(v2, v1)] = c;
	}

	// Returns the cost of an edge
	long long get_cost(int v1, int v2)
	{
		if (!is_edge(v1, v2) && !is_edge(v2, v1))
			throw std::exception("This edge is not in the list!");

		if (is_edge(v1, v2))
			return edges[std::make_pair(v1, v2)];

		return edges[std::make_pair(v2, v1)];
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

	// The depth-first search algorithm
	void DFS(int v, bool visited[], std::vector<int>& comp)
	{
		// Mark the current vertex as visited
		visited[v] = true;
		comp.push_back(v);  // we push onto the vector

		// Recur all the vertices adjacent to this vertex
		std::vector<int> list = get_adjacent_vertices(v);
		for (auto l : list)
			if(visited[l] == false)
				DFS(l, visited, comp);
	}

	void SortEdges(std::vector<std::pair<std::pair<int, int>, int>>& edges)
	{
		for (int i = 0; i < edges.size() - 1; ++i)
			for (int j = i + 1; j < edges.size(); ++j)
				if (edges[i].second > edges[j].second)
					swap(edges[i], edges[j]);
	}

	/// <summary>
	/// Kruskal's algorithm finds the Minimum Spanning Tree for an 
	/// undirected graph. Pick the smallest edge. Check if it forms 
	/// a cycle with the spanning tree formed so far. 
	/// If the cycle is not formed, include this edge. Else, discard it. 
	/// </summary>
	/// <returns></returns>
	std::pair<std::vector<std::pair<std::pair<int, int>, int>>, int> Kruskal_MST()
	{
		std::vector<std::pair<int, int>> ed = get_edges();

		// the vector of edges + cost
		std::vector<std::pair<std::pair<int, int>, int>> edges;
		for (auto e : ed)
			edges.push_back(std::make_pair(e, get_cost(e.first, e.second)));

		SortEdges(edges); // sort the edges by cost, to have the 
						  // the smallest values at the beggining

		// form a disjoint set of the vertices
		DijointSet ds(get_nr_of_vertices()); 

		// the minimum spanning tree vector
		std::vector<std::pair<std::pair<int, int>, int>> mst;

		int total_cost = 0;
		for (auto edge : edges)
			// if the endpoints are in different components(sets)
			if (ds.Find(edge.first.first) != ds.Find(edge.first.second))
			{
				// Unite the vertices to form one component
				ds.Union(edge.first.first, edge.first.second);
				mst.push_back(edge);
				total_cost += edge.second;

				// if the size is n - 1 it's done
				if (mst.size() == get_nr_of_vertices() - 1)
					break;
			}
		
		return std::make_pair(mst, total_cost);
	}

};

