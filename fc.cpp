#include <bits/stdc++.h>
using namespace std;

class Graph{
public:
	int n;
	vector< vector<int> > adjl;
	vector< vector<int> > D;
	Graph(int nodes){
		n = nodes;
		adjl.resize(n);
	}
	Graph(){
		n=0;
	}
	void addEdge(int i, int j){
		adjl[i].push_back(j);
		adjl[j].push_back(i);
	}
};
Graph G;
vector<int> assignment;
int dom;
int counter=0;

int assigned = 0;
void buildGraph(char *file){
	ifstream in(file);
	int nn,ne;
	in>>dom;
	in>>nn>>ne;
	G.n = nn;
	G.adjl.resize(nn);
	G.D.resize(nn);
	assignment.resize(nn);
	for(int i=0;i<G.n;i++){
		assignment[i] = -1;
		for(int j=1;j<=dom;j++){
			G.D[i].push_back(j);
		}
	}
	for(int i=0;i<ne;i++){
		int j,k;
		in>>j>>k;
		G.addEdge(j,k);
	}
}

int select_unassigned_var(void){
	return assigned;
}
queue< pair<int,int> > q;

bool revise(int f,int l){
	bool revised = false;
	int dd = G.D[f].size();
	for(int i=0;i<dd;i++){
		int val = G.D[f][i];
		if(G.D[l].size()<1 || (G.D[l].size()==1 && G.D[l][0]==val)){
			G.D[f].erase(G.D[f].begin()+i);
			dd--;
			revised = true;
		}
	}
	return revised;
}

bool AC3(void){
	while(!q.empty()){
		counter++;
		pair<int,int> pi = q.front();
		q.pop();
		if(revise(pi.first,pi.second)){
			if(G.D[pi.first].size()==0){
				return false;
			}
		}
	}
	return true;
}

vector<int> recursive_backtracking(void){
	if(assigned==G.n)return assignment;
	int var = select_unassigned_var();
	int num = G.D[var].size();
	if(num==0){
		vector<int> failed;
		return failed;
	}
	for(int val =0;val<num;val++){
		//counter++;
		int value = G.D[var][val];
		int adj = G.adjl[var].size();
		assignment[var] = value;
		vector<int> backup(G.D[var].begin(),G.D[var].end());
		G.D[var].clear();
		G.D[var].push_back(value);
		for(int i=0;i<adj;i++){
			if(assignment[G.adjl[var][i]]==-1){
				pair<int,int> pp(G.adjl[var][i],var);
				q.push(pp);
			}
		}
		bool done = AC3();
		if(done){
			assigned++;
			vector<int> result = recursive_backtracking();
			if(result.size()==0){
				assignment[var] = -1;
				G.D[var] = backup;
				continue;
			}
			else
				return result;
		}
		else{
			assignment[var]=-1;
			G.D[var] = backup;
			continue;
		}
	}
	vector<int> failed;
	return failed;
}

vector<int> backtracking_search(void){
	return recursive_backtracking();
}

string func(int color){
	if(color==0)return "Red";
	else if(color==1) return "Green";
	else if(color==3) return "Blue";
	else return "Black";
}

int main(){
	char infile[] = "input3.txt";
	buildGraph(infile);
	vector<int> soln = backtracking_search();
	if(soln.size()==0){
		cout<<"Failure\n";
	}
	else{
		int n = soln.size();
		for(int i=0;i<n;i++){
			cout<<" Node "<<i+1<<" = "<<func(soln[i])<<endl;
		}
		cout<<"Success\n";
	}
	//cout<<"Count = "<<counter<<endl;
}