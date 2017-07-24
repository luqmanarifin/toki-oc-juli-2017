#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair

const int N = 1e5;


int n, k;
int c[N + 5];
vector<int> ve[N + 5];
int min_dist[N + 5];
int level[N + 5];
vector<int> sparse[N + 5];
pii farthest[N + 5];

int lca(int x, int y){
	int tempx = x;
	int tempy = y;
	if(level[tempx] > level[tempy]) swap(tempx, tempy);
	/* Same the level first */
	while(level[tempx] < level[tempy]){
		int sel = level[tempy] - level[tempx];
		int now = 0;
		while((1 << now) <= sel){
			now++;
		}
		now--;
		tempy = sparse[tempy][now];
	}
	while(tempx != tempy){
		int now = 0;
		while(now < (int)sparse[tempx].size() && sparse[tempx][now] != sparse[tempy][now]) ++now;
		if(now > 0){
			now--;
			tempx = sparse[tempx][now];
			tempy = sparse[tempy][now];
		}
		else{
			tempx = sparse[tempx][now];
			tempy = sparse[tempy][now];
		}
	}
	
	return tempx;
}

int dist(int x, int y){
	int LCA = lca(x, y);
	return level[x] + level[y] - 2 * level[LCA];
}

inline void dfsGraph(int now, int par){
	level[now] = level[par] + 1;
	sparse[now].push_back(par);
	int par_now = par;
	int idx_now = 0;
	while((int)sparse[par_now].size() > idx_now){
		sparse[now].push_back(sparse[par_now][idx_now]);
		par_now = sparse[par_now][idx_now];
		idx_now++;
	}

	for(int i = 0; i < (int) ve[now].size(); ++i){
		int v = ve[now][i];
		if(v != par){
			dfsGraph(v, now);
		}
	}
}

inline void generateGraph(){
	level[0] = 0;
	level[1] = 1;
	for(int i = 0;i < (int) ve[1].size(); ++i){
		int now = ve[1][i];
		dfsGraph(now, 1);
	}
}
int main(){
	scanf("%d%d", &n, &k);
	for(int i = 0;i <= k; ++i) farthest[i] = mp(-1, -1);
	for(int i = 1;i <= n; ++i){
		scanf("%d", &c[i]);
	}
	for(int i = 1; i < n; ++i){
		int x, y;
		scanf("%d%d", &x, &y);
		ve[x].push_back(y);
		ve[y].push_back(x);
	}
	generateGraph();
	for(int i = 1;i <= n; ++i){
		int color = c[i];
		if(farthest[c[i]].fi == -1){
			farthest[c[i]].fi = i;
		}
		else if(farthest[c[i]].se == -1){
			farthest[c[i]].se = i;
			min_dist[c[i]] = dist(farthest[c[i]].fi, farthest[c[i]].se);
		}
		else{
			int nowfi = farthest[c[i]].fi;
			int nowse = farthest[c[i]].se;
			int distA = dist(i, nowfi);
			int distB = dist(i, nowse);
			int distC = dist(nowfi, nowse);
			if(distA >= distB && distA >= distC){
				farthest[c[i]] = mp(i, nowfi);
			}
			else if(distB >= distA && distB >= distC){
				farthest[c[i]] = mp(i, nowse);
			}
			else if(distC >= distA && distC >= distB){
				farthest[c[i]] = mp(nowfi, nowse);
			}
			min_dist[c[i]] = dist(farthest[c[i]].fi, farthest[c[i]].se);
		}
	}
	for(int i = 1; i <= k; ++i){
		printf("%d%c", int(ceil(1.0 * min_dist[i] / 2.0)), i == k ? '\n' : ' ');
	}
	return 0;
}