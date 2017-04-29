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
		assignment[i] = rand()%dom;
		for(int j=1;j<=dom;j++){
			G.D[i].push_back(j-1);
		}
	}
	for(int i=0;i<ne;i++){
		int j,k;
		in>>j>>k;
		G.addEdge(j,k);
	}
}

int select_unassigned_var(void){
    return rand()%(G.n);
}

int noofconflict(int val, int node){
    int totalconflict =0;
    int tmp = G.adjl[node].size();
        for(int j=0;j<tmp;j++){
            if(assignment[G.adjl[node][j]]==val){
                totalconflict++;
            }
        }
    return totalconflict;
}
bool noofconflict1(){
    //int number=0;
    for(int i=0;i<G.n;i++){
        int tmp = G.adjl[i].size();
        for(int j=0;j<tmp;j++){
            if(assignment[i]==assignment[G.adjl[i][j]])
                return false;
        }
    }
    return true;
}
int currconflict= INT_MAX;


vector<int> min_conflict(int max_step){
    int value =0;
    for(int i=1;i<=max_step;i++){
        currconflict = INT_MAX;
        if(noofconflict1())
            return assignment;
        int var = select_unassigned_var();
        int tttt=G.D[var].size();
        for(int j=0;j<tttt;j++){
            int tmp = noofconflict(G.D[var][j], var);
            if(tmp<currconflict){
                value = j;
                currconflict = tmp;
            }
        }
        assignment[var] = value;
    }
    vector<int> emptyvector;
    return emptyvector;
}

string func(int color){
	if(color==0)return "Red";
	else if(color==1) return "Green";
	else if(color==2) return "Blue";
	else return "Black";
}

int main(){
	char infile[] = "input3.txt";
	buildGraph(infile);
	vector<int> soln = min_conflict(4200000);
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
}
