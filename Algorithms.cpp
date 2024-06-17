//ID : 207723198
//Mail : yair852258@gmail.com
#include "Algorithms.hpp"
namespace ariel
{
        void Algorithms::dfs(const Graph &graph, vector<bool> &visited, size_t current_node)
        {
        	const vector<vector<int>> &adjMatrix = graph.getGraph();
            visited[current_node] = true;
            for (size_t neighbor = 0; neighbor < adjMatrix.size(); ++neighbor)
            {
                if ((adjMatrix[current_node][neighbor] > 0) && !visited[neighbor])
                {
                    dfs(graph, visited, neighbor);
                }
            }
        }

	string Algorithms::bfs(const Graph &graph, size_t start, size_t end)
        {
        	const auto &adjGraphMatrix = graph.getGraph();
        	size_t numVertices = graph.getNumVertices();


        	vector<size_t> predecessor(numVertices, static_cast<size_t>(-1)); // Cast -1 to size_t
        	vector<bool> visited(numVertices, false);

        	// Queue to manage the BFS traversal
        	queue<size_t> queue;
        	queue.push(start);
        	visited[start] = true;

        	while (!queue.empty())
        	{
        		size_t current = queue.front();
        		queue.pop();

        		// If we reached the destination node
        		if (current == end)
        		{
        			string path = to_string(end);
        			// Start building the path from the end vertex
        			for (size_t at = end; predecessor[current] != -1; current = predecessor[current])
        			{
        				path = to_string(predecessor[current]) + "->" + path;
        			}
        			return path;
        		}

        		// Scan only the neighbors of the current vertex that haven't been visited yet
        		for (size_t i = 0; i < numVertices; ++i)
        		{
        			if (adjGraphMatrix[current][i] && !visited[i])
        			{
        				queue.push(i);
        				visited[i] = true;
        				predecessor[i] = current;
        			}
        		}
        	}

        	return "-1";
        }

	string Algorithms::BellmanFord(const Graph& graph, size_t source, size_t dest)
        {
        	const vector<vector<int>>& adjMatrix = graph.getGraph();
        	size_t numVertices = graph.getNumVertices(); // Get the number of vertices
        	vector<int> distance(numVertices, numeric_limits<int>::max()); // Initialize distances to infinity
        	vector<int> predecessor(numVertices, -1);// Initialize predecessors to -1

        	distance[source] = 0; // Distance to the source is 0

        	// Relax edges V-1 times
        	for (size_t i = 0; i < numVertices; ++i)
        	{
        		for (size_t u = 0; u < numVertices; ++u)
        		{
        			for (size_t v = 0; v < numVertices; ++v)
        			{
        				if (adjMatrix[u][v] != 0)
        				{
        					int weight = adjMatrix[u][v];
        					// Relaxation step
        					if (distance[u] != numeric_limits<int>::max() && distance[u] + weight < distance[v])
        					{
        						if (i == numVertices - 1)
        						{
        							// Negative cycle detected - there is no shortest path
        							return "-1";
        						}
        						// Update the distance to v through u
        						distance[v] = distance[u] + weight;
        						predecessor[v] = u; // u is the predecessor of v
        					}
        				}
        			}
        		}
        	}
        	// No path exists from source to destination
        	if (distance[dest] == numeric_limits<int>::max())
        	{
        		return "-1";
        	}

        	// Construct the shortest path from source to destination
        	string path = to_string(dest);
        	for (size_t current = static_cast<size_t>(dest); predecessor[current] != -1; current = static_cast<size_t>(predecessor[current]))
        	{
        		path = std::to_string(predecessor[current]) + "->" + path;

        	}
        	return path;
        }

        string Algorithms::Dijkstra(const Graph& graph, size_t start, size_t end)
		{
    		const vector<vector<int>>& adjMatrix = graph.getGraph();
    		size_t numVertices = graph.getNumVertices(); // Get the number of vertices
    		// Initialize distances and predecessors
    		vector<int> distance(numVertices, numeric_limits<int>::max()); // Initialize distances to infinity
    		vector<int> predecessor(numVertices, -1);// Initialize predecessors to -1

    		distance[start] = 0; // Distance to the start vertex is 0

    		// Priority queue to store vertices by their distance from the start vertex
    		priority_queue<pair<int, size_t>, vector<pair<int, size_t>>, greater<pair<int, size_t>>> pq;
    		pq.push({0, start});

    		// Dijkstra's algorithm main loop
    		while (!pq.empty())
    		{
        		size_t curr = pq.top().second;
        		pq.pop();

        		// Iterate over all neighbors of the current vertex
        		for (size_t i = 0; i < numVertices; ++i)
        		{
            		if (adjMatrix[curr][i] != 0) // Check if there is an edge from curr to i
            		{
                		size_t next = i;
                		int weight = adjMatrix[curr][i];
                		// Relaxation step
                		if (distance[curr] != numeric_limits<int>::max() && distance[curr] + weight < distance[next])
                		{
                    		// Update the distance to next through curr
                    		distance[next] = distance[curr] + weight;
                    		predecessor[next] = curr; // curr is the predecessor of next
                    		pq.push({distance[next], next});
                		}
            		}
        		}
    		}

    		// If there's no path from start to end, return "-1"
    		if (distance[end] == numeric_limits<int>::max())
    		{
        		return "-1";
    		}

    		// Construct the shortest path from start to end
    		size_t current = end;
        	string path = to_string(current);
    		while (current != start)
    		{
    			current = static_cast<size_t>(predecessor[current]);
        		path = to_string(current) + "->" + path;
    		}
    		return path;
		}

	bool Algorithms::dfsCycleHelper(const vector<vector<int>> &adjMatrix, size_t node, int parentNode, vector<bool> &visited, vector<bool> &detectBackEdges, vector<size_t> &cyclePath)
        {
        	visited[node] = true;
        	detectBackEdges[node] = true;

        	for (size_t neighbor = 0; neighbor < adjMatrix[node].size(); ++neighbor) {
        		if (adjMatrix[node][neighbor] != 0) {
        			if (!visited[neighbor]) {
        				if (dfsCycleHelper(adjMatrix, neighbor, node, visited, detectBackEdges, cyclePath))
        				{
        					cyclePath.push_back(node);
        					return true;
        				}
        			}
        			//detecting back edge
        			else if (detectBackEdges[neighbor] && neighbor != parentNode)
        			{
        				cyclePath.push_back(neighbor);
        				cyclePath.push_back(node);
        				return true;
        			}
        		}
        	}

        	detectBackEdges[node] = false;
        	return false;
        }

	//build string of cycle path
	string Algorithms::formatCyclePath(const vector<size_t> &pathCycle)
        {
        	string stringCycle;
        	for (size_t j = 0; j < pathCycle.size(); ++j)
        	{
        		stringCycle += to_string(pathCycle[j]);
        		if (j < pathCycle.size() - 1)
        			stringCycle += " -> ";
        	}
        	return stringCycle;
        }

        bool Algorithms::isConnected(const Graph& graph)
        {
            vector<bool> visited(graph.getNumVertices(), false); //set all vertices to not visited
        	size_t start_vertex = 0;
            dfs(graph, visited, start_vertex); //run DFS from vertex 0 (rendom vertex)
            for (bool visit : visited) {
                if (!visit)
                {
                    //if we didnt visit at least one of the vertices with DFS the graph is not connected
                    return false;
                }
            }
        	if(graph.isDirected())
        	{
        		fill(visited.begin(), visited.end(), false); //Set all vertices to not visited once again
        		for (size_t i = 1; i < visited.size(); ++i)
        		{
        			if (graph.getGraph()[i][0] > 0)
        			{ // Check for incoming edge to vertex i from vertex 0
        				start_vertex = i; // Use this vertex i as the starting point
        				break;
        			}
        		}
        		start_vertex = (start_vertex + 1) % visited.size(); // Choose a different starting vertex
        		dfs(graph, visited, start_vertex);

        		// The graph is not connected if any vertex is not visited in the second DFS
        		for (bool visit : visited)
        		{
        			if (!visit)
        			{
        				return false;
        			}
        		}
        	}
            return true;
        }

		string Algorithms::shortestPath(const Graph& graph, int start, int end)
		{
    		const vector<vector<int>>& adjMatrix = graph.getGraph();
        	size_t numVertices = graph.getNumVertices();

    		if (start < 0 || start >= static_cast<int>(numVertices))
    		{
        		throw invalid_argument("Invalid start vertex");
    		}
    		if (end < 0 || end >= static_cast<int>(numVertices))
    		{
        		throw invalid_argument("invalid end vertex");
    		}

    		size_t startVertex = static_cast<size_t>(start);
    		size_t endVertex = static_cast<size_t>(end);

    		// Determine the appropriate algorithm based on graph properties
    		if (graph.isWeighted() == 0)
    		{
        		// Use BFS for unweighted graphs
        		return bfs(graph, startVertex, endVertex);
    		}
    		else if (graph.isWeighted() == -1)
    		{
        		// Use Bellman-Ford for graphs with negative edges
        		return BellmanFord(graph, startVertex, endVertex);
    		}
    		else
    		{
        		// Use Dijkstra's algorithm for weighted graphs with non-negative edges
        		return Dijkstra(graph, startVertex, endVertex);
    		}
		}

    	string Algorithms::isContainsCycle(const Graph &graph)
    	{
        	const vector<vector<int>>& adjMatrix = graph.getGraph();
        	size_t numVertices = graph.getNumVertices();
        	vector<bool> visited(numVertices, false);
        	vector<size_t> cyclePath;

        	for (size_t i = 0; i < numVertices; ++i)
        	{
        		if (!visited[i])
        		{
        			// This vector keeps track of the nodes currently in the recursion stack of the DFS.
        			// It helps in detecting cycles by identifying back edges.
        			vector<bool> detectBackEdges(numVertices, false);
        			if (dfsCycleHelper(adjMatrix, i, -1, visited, detectBackEdges, cyclePath))
        			{
        				//bulid the cycle path
        				return formatCyclePath(cyclePath);
        			}
        		}
        	}

        	return "0";
        }

		string Algorithms::isBipartite(const Graph &graph)
		{
        	const vector<vector<int>>& adjMatrix = graph.getGraph();
        	size_t numVertices = graph.getNumVertices();
    		vector<int> vertexColors(numVertices, -1); // -1: uncolored, 0 and 1: two colors
    		queue<size_t> queue;
    		vector<size_t> setA, setB;

			//Start BFS from each vertex that has not been colored
    		for (size_t vertex = 0; vertex < numVertices; ++vertex)
    		{
        		if (vertexColors[vertex] == -1)
        		{
            		queue.push(vertex);
            		vertexColors[vertex] = 0; // Color the first vertex with color 0
            		setA.push_back(vertex);

            		while (!queue.empty())
            		{
                		size_t current = queue.front();
                		queue.pop();

                		for (size_t neighbor = 0; neighbor < numVertices; ++neighbor)
                		{
                    		if (adjMatrix[current][neighbor] != 0)
                    		{
                        		if (vertexColors[neighbor] == -1)
                        		{
                        			// Color neighbor vertex with opposite color of current vertex
                            		vertexColors[neighbor] = 1 - vertexColors[current];
                            		queue.push(neighbor);
                            		if (vertexColors[neighbor] == 0)
                            		{
                                		setA.push_back(neighbor);
                            		}
                            		else
                            		{
                                		setB.push_back(neighbor);
                            		}
                        		}
                        		else if (vertexColors[neighbor] == vertexColors[current])
                        		{
                            		return "0"; //graph is not bipartite
                        		}
                    		}
                		}
            		}
        		}
    		}

    		string result = "The graph is bipartite: A={";
    		for (size_t i = 0; i < setA.size(); ++i)
    		{
        		result += to_string(setA[i]);
        		if (i != setA.size() - 1)
        		{
            		result += ", ";
        		}
    		}
    		result += "}, B={";
    		for (size_t i = 0; i < setB.size(); ++i)
    		{
        		result += to_string(setB[i]);
        		if (i != setB.size() - 1)
        		{
            		result += ", ";
        		}
    		}
    		result += "}";
    		return result;
		}

    	string Algorithms::negativeCycle(const Graph& graph)
        {
        	const vector<vector<int>>& adjMatrix = graph.getGraph();
        	size_t numVertices = graph.getNumVertices(); // Get the number of vertices
        	vector<int> distance(numVertices, numeric_limits<int>::max()); // Initialize distances to infinity
        	vector<int> predecessor(numVertices, -1);// Initialize predecessors to -1

        	distance[0] = 0; // Distance to the source is 0

        	// Relax edges V-1 times
        	for (int i = 0; i < numVertices; ++i)
        	{
        		for (size_t u = 0; u < numVertices; ++u)
        		{
        			for (size_t v = 0; v < numVertices; ++v)
        			{
        				if (adjMatrix[u][v] != 0)
        				{
        					int weight = adjMatrix[u][v];
        					// Relaxation step
        					if (distance[u] != numeric_limits<int>::max() && distance[u] + weight < distance[v])
        					{
        						// Update the distance to v through u
        						distance[v] = distance[u] + weight;
        						predecessor[v] = u; // u is the predecessor of v
        						if(i==numVertices-1)
        						{
        						return "There is negative cycle";
        						}
        					}
        				}
        			}
        		}
        	}
        	return "There is no negative cycle";
        }
}
