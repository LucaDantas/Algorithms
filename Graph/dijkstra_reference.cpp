typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define pb push_back
#define mp make_pair

typedef pair<ll, int> pli;
const int maxn = 1e5 + 100;
const ll inf = 0x3f3f3f3f3f3f3f3f;

int n, m;
//vector<pii> g[maxn];  //--Those two need to be set inside 
						//--the function to be passed as reference
//ll dist[maxn];

void dijkstra(int s, vector<pii>(&g)[maxn], ll (&dist)[maxn]){
	for(int i = 1; i <= n; i++) 
		dist[i] = inf;
	
	priority_queue<pli, vector<pli>, greater<pli>> q; 
	
	dist[s] = 0; 
	q.push(mp(0LL, s)); 
	
	bool mark[maxn]; 
	memset(mark, 0, sizeof mark);
	
	while(!q.empty()){ 
		
		int u = q.top().second; 
		q.pop(); 
		
		if(mark[u])
			continue;
		
		mark[u] = 1; 
		
		
		for(auto next : g[u]){
			
			int v = next.first;
			int w = next.second; 
			
			if(dist[v] > dist[u] + (ll)w){ 
				dist[v] = dist[u] + (ll) w; 	
				q.push(mp(dist[v], v));
			}
		}
	}
}

//Remember to reverse the vector ans after it
void find_path(int u, vi &ans, vector<pii>(&g)[maxn], ll (&dist)[maxn]){ 
	ans.pb(u);
	
	for(auto next : g[u]){
		int v = next.first, w = next.second;
		if(dist[v] == dist[u] - w){
			find_path(v, ans, g, dist);
			return;
		}
	}
}
