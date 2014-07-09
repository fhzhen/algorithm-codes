//1. You are given n activities with their start and finish times. Select the maximum number of activities that can be performed by a single person, assuming that a person can only work on a single activity at a time.
/*Example: Consider the following 6 activities. The maximum set of activities that can be executed by a single person is {0, 1, 3, 4}
     start[]  =  {1, 3, 0, 5, 8, 5};
     finish[] =  {2, 4, 6, 7, 9, 9};
1) Sort the activities according to their finishing time, 2) Select the first activity from the sorted array and print it.
3) Do following for remaining activities in the sorted array.a) If the start time of this activity is greater than the finish time of previously selected activity then select this activity and print it.*/
int maxActives(int s[], int f[], int n)
{
	cout<<"Following activities are selected"<<endl;
	int i = 0, cnt = 1;
	cout<<i<<", ";// The first activity always gets selected
	for(int j=1; j<n; ++j)
	{
		// If this activity has start time greater than or equal to the finish time of previously selected activity, then select it
		if(s[j] >= f[i])
		{
			cout<<j<<", ";
			i = j;
			++cnt;
		}
	}
	return cnt;
}

/*2. Kruskal’s Minimum Spanning Tree Algorithm--time O(ElogE) or O(ElogV)
1. Sort all the edges in non - decreasing order of their weight.
2. Pick the smallest edge.Check if it forms a cycle with the spanning tree formed so far.If cycle is not formed, include this edge.Else, discard it.
3. Repeat step#2 until there are(V - 1) edges in the spanning tree.*/
struct Edge
{
	int src;
	int dest;
	int weight;
};
struct Graph
{
	int v;//Number of vertice
	int e; // Number of edges
	Edge* edge;// graph is represented as an array of edges
	Graph(int v, int e)
	{
		this->v = v;
		this->e = e;
		edge = new Edge[e];
	}
	~Graph()
	{
		delete[] edge;
	}
};
Graph* creatGraph(int v, int e)
{
	Graph* graph = new Graph(v, e);
	return graph;
}
void deleteGraph(Graph* graph)
{
	delete graph;
}
struct Subset
{
	int parent;
	int rank;
};
int find(Subset subsets[], int i)//find the subset of an element i by using path compression technique
{
	// find root and make root as parent of i (path compression)
	if (subsets[i].parent != i)
		subsets[i].parent = find(subsets, subsets[i].parent);
	return subsets[i].parent;
}
void Union(Subset subsets[], int x, int y)//to do union of two subsets by uses union by rank
{
	int xroot = find(subsets, x);
	int yroot = find(subsets, y);
	// Attach smaller rank tree under root of high rank tree (Union by Rank)
	if (subsets[xroot].rank < subsets[yroot].rank)
		subsets[xroot].parent = yroot;
	else if (subsets[xroot].rank > subsets[yroot].rank)
		subsets[yroot].parent = xroot;
	else // If ranks are same, then make one as root and increment its rank by one
	{
		subsets[yroot].parent = xroot;
		++subsets[xroot].rank;
	}
}
int comp(const void* a, const void* b)
{
	return ((Edge*)a)->weight < ((Edge*)b)->weight;
}
void kruskalMST(Graph *graph)
{
	Edge *result = new Edge[graph->v];//store the resultant MST
	int e = 0, i = 0;
	// Step 1:  Sort all the edges in non-decreasing order of their weight
	qsort(graph->edge, graph->e, sizeof(graph->edge[0]), comp);
	Subset *subsets = new Subset[graph->v];
	// Create V subsets with single elements
	for (int v = 0; v < graph->v; ++v)
	{
		subsets[v].parent = v;
		subsets[v].rank = 0;
	}
	// Number of edges to be taken is equal to V-1
	while (e < graph->v - 1)
	{
		// Step 2: Pick the smallest edge. And increment the index for next iteration
		Edge edge = graph->edge[i++];
		int x = find(subsets, edge.src);
		int y = find(subsets, edge.dest);
		// If including this edge does't cause cycle, include it in result and increment the index of result for next edge
		if (x != y)
		{
			result[e++] = edge;
			Union(subsets, x, y);
		}
		// Else discard the next_edge
	}
	// print the contents of result[] to display the built MST
	printf("Following are the edges in the constructed MST\n");
	for (i = 0; i < e; ++i)
		printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
	delete[] subsets;
	delete[] result;
}
//beter c++11 version
struct Edge
{
	char src;
	char dest;
	int weight;
	Edge(char v1, char v2, int w)
	{
		src = v1;
		dest = v2;
		weight = w;
	}
};
struct Graph
{
	vector<char> vertices;
	vector<Edge> edges;// graph is represented as an array of edges	
};
struct Subset
{
	unordered_map<char, char> parent;
	unordered_map<char, int> rank;
};
char Find(Subset subsets, char v)//find the subset of an element v by using path compression technique
{
	// find root and make root as parent of v (path compression)
	if (subsets.parent[v] != v)
		return Find(subsets, subsets.parent[v]);
	else
		return subsets.parent[v];
}
void Union(Subset &subsets, char r1, char r2)//to do union of two subsets by uses union by rank
{
	if (subsets.rank[r1] > subsets.rank[r2])
		subsets.parent[r2] = r1;
	else if (subsets.rank[r1] < subsets.rank[r2])
		subsets.parent[r1] = r2;
	else
	{
		subsets.parent[r1] = r2;
		++subsets.rank[r2];
	}
}
void kruskal(Graph graph)
{
	vector<Edge> MST;
	Subset subsets;
	for (auto c : graph.vertices)
	{
		subsets.parent[c] = c;
		subsets.rank[c] = 0;
	}
	sort(graph.edges.begin(), graph.edges.end(), [](Edge e1, Edge e2){return e1.weight < e2.weight; });
	for (Edge e : graph.edges)
	{
		char r1 = Find(subsets, e.src);
		char r2 = Find(subsets, e.dest);
		if (r1 != r2)
		{
			MST.push_back(e);
			Union(subsets, r1, r2);
		}
	}
	for (Edge e : MST)
	{
		cout << e.src << " to " << e.dest << " w is " << e.weight << endl;
	}
}


/*3. Prim’s Minimum Spanning Tree (MST)-can be inproved by save key by min heap time O(ELogV)
1) Create a set mstSet that keeps track of vertices already included in MST.
2) Assign a key value to all vertices in the input graph. Initialize all key values as INFINITE. 
Assign key value as 0 for the first vertex so that it is picked first.
3) While mstSet doesn’t include all vertices
….a) Pick a vertex u which is not there in mstSet and has minimum key value.
….b) Include u to mstSet.
….c) Update key value of all adjacent vertices of u. To update the key values, iterate through all adjacent vertices. For every adjacent vertex v, 
if weight of edge u-v is less than the previous key value of v, update the key value as weight of u-v */
struct Edge
{
	char src;
	char dest;
	int weight;
	Edge(char v1, char v2, int w)
	{
		src = v1;
		dest = v2;
		weight = w;
	}
};
struct Graph
{
	vector<char> vertices;
	vector<Edge> edges;// graph is represented as an array of edges	
	vector<pair<char, Edge>> adjacent(char u)
	{
		vector<pair<char, Edge>> res;
		for (Edge e : edges)
		{
			if (e.src == u)
				res.push_back(make_pair(e.dest, e));
			else if (e.dest == u)
				res.push_back(make_pair(e.src, e));
		}
		return res;
	}
};
void prim(Graph g)//time O(V^2)
{
	unordered_map<char, char> mst;
	unordered_map<char, char> parent;
	unordered_map<char, int> key;
	for (auto c : g.vertices)
	{
		parent[c] = '\0';
		key[c] = INT_MAX;
	}
	key['a'] = 0;//root
	vector<char> q = g.vertices;
	while (!q.empty())
	{
		char u = *min_element(q.begin(), q.end(), [&](char x, char y){return key[x] < key[y]; });
		vector<char>::iterator i = remove(q.begin(), q.end(), u);
		q.erase(i, q.end());
		if (parent[u] != '\0')
		{
			mst[u] = parent[u];
		}
		vector<pair<char, Edge>> adj = g.adjacent(u);
		for (pair<char, Edge> v : adj)
		{
			if (find(q.begin(), q.end(), v.first) != q.end())
			{
				if (v.second.weight < key[v.first])
				{
					parent[v.first] = u;
					key[v.first] = v.second.weight;
				}
			}
		}
	}
	for (auto e : mst)
		cout << e.first << " - " << e.second << endl;
}

/*4. Dijkstra’s shortest path algorithm
1) Create a set sptSet (shortest path tree set) that keeps track of vertices included in shortest path tree, i.e., whose minimum distance from source is calculated and finalized. Initially, this set is empty.
2) Assign a distance value to all vertices in the input graph. Initialize all distance values as INFINITE. Assign distance value as 0 for the source vertex so that it is picked first.
3) While sptSet doesn’t include all vertices
….a) Pick a vertex u which is not there in sptSetand has minimum distance value.
….b) Include u to sptSet.
….c) Update distance value of all adjacent vertices of u. To update the distance values, iterate through all adjacent vertices. For every adjacent vertex v,
if sum of distance value of u (from source) and weight of edge u-v, is less than the distance value of v, then update the distance value of v.*/
//a. use adjacency matrix representation of the graph
const int V = 9; // Number of vertices in the graph
// Find the vertex with minimum distance value, from the set of vertices not yet included in shortest path tree
int minDist(int dist[], bool sptSet[])
{
	int min = INT_MAX, minIndex = 0;
	for (int v = 0; v < V; ++v)
	{
		if (!sptSet[v] && dist[v] <= min)
		{
			min = dist[v];
			minIndex = v;
		}
	}
	return minIndex;
}
void dijkstra(int graph[V][V], int src)// time O(V ^ 2)
{
	int dist[V] = { 0 };// The output array.  dist[i] will hold the shortest distance from src to i
	bool sptSet[V] = { false };// sptSet[i] will true if vertex i is included in shortest path tree or shortest distance from src to i is finalized
	for (int i = 0; i < V; ++i)
		dist[i] = INT_MAX;
	dist[src] = 0;// Distance of source vertex from itself is always 0
	// Find shortest path for all vertices
	for (int e = 0; e < V - 1; ++e)
	{
		// Pick the minimum distance vertex from the set of vertices not yet processed. u is always equal to src in first iteration.
		int u = minDist(dist, sptSet);
		sptSet[u] = true;// Mark the picked vertex as processed
		// Update dist value of the adjacent vertices of the picked vertex.
		for (int v = 0; v < V; ++v)
		{
			// Update dist[v] only if is not in sptSet, there is an edge from u to v, and total weight of path from src to  v through u is smaller than current value of dist[v]
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
		}
	}
	printf("Vertex Distance from Source:\n");
	for (int i = 0; i < V; ++i)
		printf("%d \t\t %d\n", i, dist[i]);
}
//second method
struct Edge
{
	char src;
	char dest;
	int weight;
	Edge(char v1, char v2, int w)
	{
		src = v1;
		dest = v2;
		weight = w;
	}
};
struct Graph
{
	vector<char> vertices;
	vector<Edge> edges;
	vector<pair<char, Edge>> adjacent(char u)
	{
		vector<pair<char, Edge>> res;
		for (auto e : edges)
		{
			if (e.src == u)
				res.push_back(make_pair(e.dest, e));
			else if (e.dest == u)
				res.push_back(make_pair(e.src, e));
		}
		return res;
	}
};
void dijkstra(Graph g)//
{
	unordered_map<char, char> shortest;
	unordered_map<char, char> parent;
	unordered_map<char, int> distance;
	for (auto c : g.vertices)
	{
		parent[c] = '\0';
		distance[c] = INT_MAX;
	}
	distance['a'] = 0;//root
	vector<char> q = g.vertices;
	while (!q.empty())//O(V)
	{
		char u = *min_element(q.begin(), q.end(), [&](char x, char y){return distance[x] < distance[y]; });
		vector<char>::iterator i = remove(q.begin(), q.end(), u);
		q.erase(i, q.end());
		if (parent[u] != '\0')
			shortest[u] = parent[u];
		vector<pair<char, Edge>> adj = g.adjacent(u);
		for (auto v : adj)
		{
			if (find(q.begin(), q.end(), v.first) != q.end())
			{
				if (distance[u] + v.second.weight < distance[v.first])
				{
					parent[v.first] = u;
					distance[v.first] = distance[u] + v.second.weight;
				}
			}
		}
	}
	for (auto e : shortest)
		cout << e.first << " to " << e.second << endl;
	for (auto e : distance)
		cout << e.first << " is " << e.second << endl;
}

/*b. time O(ELogV), use Min Heap to save distance, Adjacency List Representation the graph--need implement min heap by self
1) Create a Min Heap of size V where V is the number of vertices in the given graph. Every node of min heap contains vertex number and distance value of the vertex.
2) Initialize Min Heap with source vertex as root (the distance value assigned to source vertex is 0). The distance value assigned to all other vertices is INF (infinite).
3) While Min Heap is not empty, do following
…..a) Extract the vertex with minimum distance value node from Min Heap. Let the extracted vertex be u.
…..b) For every adjacent vertex v of u, check if v is in Min Heap. If v is in Min Heap and distance value is more than weight of u-v plus distance value of u, then update the distance value of v.*/

/*5. Graph Coloring -- NP Complete problem, Time O(V ^ 2 + E) in worst case
1. Color first vertex with first color.
2. For remaining V-1 vertices, Consider the currently picked vertex and color it with the lowest numbered color that has not been used on any previously
colored vertices adjacent to it. If all previously used colors appear on vertices adjacent to v, assign a new color to it.*/
class Graph
{
private:
	int V;//No. of vertices
	list<int> *adj;// A dynamic array of adjacency lists
public:
	Graph(int v)
	{
		V = v;
		adj = new list<int>[V];
	}
	~Graph()
	{
		delete[] adj;
	}
	void addEdge(int v, int w)
	{
		adj[w].push_back(v);
		adj[v].push_back(w);
	}
	void coloring()// Assigns colors (starting from 0) to all vertices and prints the assignment of colors
	{
		int *color = new int[V];
		memset(color, -1, sizeof(int)* V);
		color[0] = 0;// Assign the first color to first vertex
		// use unavailable[c] to store the unavailable colors, if true - the color c is assigned to one of its adjacent vertices
		bool *ua = new bool[V];
		memset(ua, false, V);
		// Assign colors to remaining V-1 vertices
		for (int u = 1; u < V; ++u)
		{
			// Process all adjacent vertices and flag their colors as unavailable
			list<int>::iterator i;
			for (i = adj[u].begin(); i != adj[u].end(); ++i)
			{
				if (color[*i] != -1)
					ua[color[*i]] = true;
			}
			int c = 0;
			for (c = 0; c < V; ++c) // Find the first available color
			{
				if (ua[c] == false)
					break;
			}
			color[u] = c;// Assign the found color
			// Reset the values back to false for the next iteration
			memset(ua, false, V);
		}
		for (int u = 0; u < V; ++u)
			cout << "Vertex " << u << " --->  Color " << color[u] << endl;
		delete[] color;
		delete[] ua;
	}
};

//6. Rearrange a string so that all same characters become d distance away
bool rearrange(char str[], int d)
{
	if (str == NULL || d < 0 || *str == '\0')
		return false;
	bool success = false;
	int n = strlen(str), i = 0;
	unordered_map<char, int> freq;
	for (i = 0; i < n; ++i)
	{
		if (freq[str[i]] == 0)
			freq[str[i]] = 1;
		else
			++freq[str[i]];
		str[i] = '\0';
	}
	//as max heap store all characters and their frequencies
	multimap<int, char, greater<>> maxheap;
	for (auto f : freq)
	{
		maxheap.insert(pair<int, char>(f.second, f.first));
	}
	// extract all distinct characters one by one from max heap and put them back in str[] with the d distance constraint
	i = 0;
	for (auto m : maxheap)
	{
		// Find the first available position in str[]
		int p = i;
		while (str[p] != '\0')
			++p;
		// Fill m.second at p, p+d, p+2d, .. p+(f-1)d		
		for (int k = 0; k < freq.at(m.second); ++k)
		{
			// If the index goes beyond size, then string cannot be rearranged.
			if (p + d*k >= n)
			{
				success = false;
				cout << "Cannot be rearranged";
				exit(0);
			}
			str[p + d * k] = m.second;
			success = true;
		}
		++i;
	}
	return success;
}
//no good
//Given a string of lowercase characters, reorder them such that the same characters are at least distance d from each other.
//Input: { a, b, b }, distance = 2, Output : { b, a, b }
int find_max(int freq[], bool excep[])
{
	int max_i = -1;
	int max = -1;
	for (char c = 'a'; c <= 'z'; ++c)
	{
		if (!excep[c] && freq[c] > 0 && freq[c] > max)
		{
			max = freq[c];
			max_i = c;
		}
	}
	return max_i;
}
void create(char *str, int d, char ans[])
{
	int n = strlen(str);
	int freq[256] = { 0 }; //character count
	for (int i = 0; i < n; ++i)
		++freq[str[i]];
	int used[256] = { 0 };
	for (int i = 0; i < n; ++i)
	{
		bool excep[256] = { false };
		bool done = false;
		while (!done)
		{
			int j = find_max(freq, excep);
			if (j == -1)
			{
				cout << "error!" << endl;
				return;
			}
			excep[j] = true;
			if (used[j] <= 0)
			{
				ans[i] = j;
				freq[j]--;
				used[j] = d;
				done = true;
			}
		}
		for (int i = 0; i < 256; ++i)
			used[i]--;
	}
	ans[n] = '\0';
}

//7. Given an array of non-negative integers, you are initially positioned at the first index of the array. Each element in the array represents
//your maximum jump length at that position. Determine if you are able to reach the last index. 由于每层最多可以跳A[i] 步，也可以跳0 或1 步，因此如果能到达最高层，则说明每一层都可以到达
//正向，从0 出发，一层一层网上跳，看最后能不能超过最高层，能超过，说明能到达，否则不能到达。时间复杂度O(n)，空间复杂度O(1)
bool jump(int a[], int n)
{
	int reach = 1; //can jump to far right
	for (int i = 0; i < reach && reach < n; ++i)
		reach = max(reach, i + 1 + a[i]);
	return reach >= n;
}
//逆向，从最高层下楼梯，一层一层下降，看最后能不能下降到第0 层。时间复杂度O(n)，空间复杂度O(1)
bool jump(int a[], int n)
{
	if (n == 0)
		return true;
	int left = n - 1;//backward to far left
	for (int i = n - 2; i >= 0; --i)
	{
		if (i + a[i] >= left)
			left = i;
	}
	return left == 0;
}
//动规,时间复杂度O(n)，空间复杂度O(n)，设状态为f[i]，表示从第0 层出发，走到A[i] 时剩余的最大步数，则状态转移方程为：f[i] = max(f[i-1], A[i-1])-1; i > 0
bool jump(int a[], int n)
{
	vector<int> f(n, 0);
	f[0] = 0;
	for (int i = 1; i < n; ++i)
	{
		f[i] = max(f[i - 1], a[i - 1]) - 1;
		if (f[i] < 0)
			return false;
	}
	return f[n - 1] >= 0;
}

//b. Your goal is to reach the last index in the minimum number of jumps,时间复杂度O(n)，空间复杂度O(1)
int jump(int a[], int n)
{
	int step = 0;
	int left = 0, right = 0;//[left, right] 是当前能覆盖的区间
	if (n == 1)
		return 0;
	while (left <= right)// 尝试从每一层跳最远
	{
		++step;
		int oldRight = right;
		for (int i = left; i <= oldRight; ++i)
		{
			int newRight = i + a[i];
			if (newRight >= n - 1)
				return step;
			if (newRight > right)
				right = newRight;
		}
		left = oldRight + 1;
	}
	return 0;
}
// 时间复杂度O(n)，空间复杂度O(1)
int jump(int a[], int n)
{
	int step = 0;
	int last = 0;// the maximum distance that has been reached
	int cur = 0;// the maximum distance that can be reached by using "step+1" steps
	for (int i = 0; i < n; ++i)
	{
		if (i > last)
		{
			last = cur;
			++step;
		}
		cur = max(cur, i + a[i]);
	}
	return step;
}
