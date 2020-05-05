typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define pb push_back
#define mp make_pair

typedef pair<ll, int> pli; //Remeber to use this to save pair with ll for the distance
const int maxn = 1e5 + 100; //maximum of vertices
const ll inf = 0x3f3f3f3f3f3f3f3f; // approx 4*10^18 - 8 times 3f - hexadecimal repres

int n, m; //number of vertices and edges
vector<pii> g[maxn]; //pair(vertex "to", weight) - graph representation in adj list

ll dist[maxn]; //distance from the source to each item
bool mark[maxn]; //wheter it was visited or not

void dijkstra(int s){
	for(int i = 1; i <= n; i++) //initialize the distances
		dist[i] = inf;
	
	priority_queue<pli, vector<pli>, greater<pli>> q; //priority queue
	
	dist[s] = 0; //initalize distance to the source
	q.push(mp(0LL, s)); //adds source to the queue
	
	while(!q.empty()){ //while there still is someone to take in the queue
		
		int u = q.top().second; //vertex in the top of the list
		q.pop(); //remove it from the list
		
		if(mark[u]) //if already computed skip
			continue;
		
		mark[u] = 1; //mark as arealdy computed
		
		
		for(auto next : g[u]){ //for every adjacent node
			
			int v = next.first;	//index of the adjacent vertex	
			int w = next.second; //weight of the edge
			
			if(dist[v] > dist[u] + (ll)w){ //if the path to v through u is better than the current
				dist[v] = dist[u] + (ll) w; //relax the path - update the distance	
				q.push(mp(dist[v], v)); //add v to the queue
			}
		}
	}
}

//Remember to reverse the vector ans after it
void find_path(int u, vi &ans){ //given the endpoint in an undirected graph
								//find the path to the source
	ans.pb(u);
	
	for(auto next : g[u]){
		int v = next.first, w = next.second;
		if(dist[v] == dist[u] - w){
			find_path(v, ans);
			return;
		}
	}
}
