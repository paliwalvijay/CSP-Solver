#include <bits/stdc++.h>
using namespace std;

class Graph{
public:
	int n;
	vector< vector<int> > adjl;
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
int D;
int counter = 0;
int assigned = 0;
void buildGraph(char *file){
	ifstream in(file);
	int nn,ne;
	in>>D;
	in>>nn>>ne;
	G.n = nn;
	G.adjl.resize(nn);
	assignment.resize(nn);
	for(int i=0;i<G.n;i++){
		assignment[i] = -1;
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

vector<int> recursive_backtracking(void){
	if(assigned==G.n)return assignment;
	int var = select_unassigned_var();
	for(int value =0;value<D;value++){
		int cons=1;
		int adj = G.adjl[var].size();
		for(int i=0;i<G.adjl[var].size();i++){
			counter++;
			if(assignment[G.adjl[var][i]]!=-1){
				if(assignment[G.adjl[var][i]]==value){
					cons=0;
					break;
				}
			}
		}
		if(cons==1){
			assignment[var] = value;
			assigned++;
			vector<int> result = recursive_backtracking();
			if(result.size()==0){
				assignment[var] = -1;
				assigned--;
			}
			else
				return result;
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
	else return "Blue";
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
	//printf("Time = %d\n",counter);
}