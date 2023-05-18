/**
 * Author: Tiago Domingos
 * Date: 2020-02-21
 * Description: Cria uma arvore isometrica com O(|K|) nos
 * Time: O(Klog(K))
 * Usage: mandar o conjunto de nos que a arvore tem que ter, e implementar uma funcao
 * lca(x,y) e dist(x,y)
 * K = vertices para adicionar na virtual tree
 * edge = (x,y,z). Aresta de x para y com custo z
 * Status:tested
 */


pair<vector<edge> ,int> build_virtual_tree(vi K){
    auto f = [&](int a , int b){
        return in[a] < in[b];
    };
    vector<edge> e;
    sort(all(K) , f);
    int m = sz(K);
    rep(i,1,m){
        K.push_back(lca(K[i] , K[i-1]));
    }
    sort(all(K) , f);
    K.erase(unique(all(K)) , K.end());
    rep(i,0,sz(K) -1){
        int z = lca(K[i] , K[i+1]);
        e.push_back({K[i+1] , z ,dist(z,K[i+1])});
    }
    return {e ,K[0]};
}
