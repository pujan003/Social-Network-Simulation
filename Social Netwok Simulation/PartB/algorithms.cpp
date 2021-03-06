
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "network.h"
#include "algorithms.h"
#include <algorithm>
#include <set>

ofstream out("PartB/DistMatrix2.txt");



void Algorithms::FloydWarshall(){
	D = new int* [vertices];

	for(int i = 0; i <vertices; i++)
		D[i] = new int[vertices];

	//initialize distances
	for(int i=0; i<vertices;i++)
		for(int j=0; j<vertices;j++)
			D[i][j] = vertices+1;

	// initialize diagonal
	for(int i=0; i < vertices; i++)
		D[i][i]=0;

	// initialize distances
	for(int i =0; i<vertices; i++)
		for(unsigned int j=0; j<G[i]->friend_list.size(); j++)
			D[i][G[i]->friend_list[j]->number] = 1;

	//Floyd-Warshall
	for(int k=0; k<vertices; k++)
	{	
		for(int i=0; i<vertices; i++){
			for(int j=0; j<vertices; j++){
				if(D[i][k]+D[k][j] < D[i][j]){
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}

	// Save final distance matrix
	for(int i = 0; i < vertices; i++){
		for(int j = 0; j < vertices; j++)
		{
			if(D[i][j] == vertices+1)
				out<<"∞ ";
			else
				out << D[i][j] << " ";
		}
		out << endl;
	}
	out << endl;


}

void Algorithms::init(GraphNode* a){
	for(int i=0;i<G.size();i++){
		G[i]->distance_till_here=2e9;
		G[i]->is_visited=false;
	}
	a->distance_till_here=0;
	a->is_visited=true;
	
}

void Algorithms::bfs(GraphNode* a){
	queue<GraphNode*> Q;
	init(a);
	Q.push(a);
	while(!Q.empty()){
		GraphNode* temp=Q.front();
		Q.pop();
		cout<<"algorithm: "<<temp->name<<endl;
		for(int i=0;i<temp->friend_list.size();i++){
			if(!temp->friend_list[i]->is_visited){
				temp->friend_list[i]->is_visited=true;
				temp->friend_list[i]->distance_till_here=temp->distance_till_here+1;
				Q.push(temp->friend_list[i]);
			}
		}
		
	}
}

void Algorithms::dfs(GraphNode* temp){
	init(temp);
	mainDfs(temp);
}

void Algorithms::mainDfs(GraphNode* temp){
	
	for(int i=0;i<temp->friend_list.size();i++){
		if(!temp->friend_list[i]->is_visited){
			temp->friend_list[i]->is_visited=true;
			temp->friend_list[i]->distance_till_here=temp->distance_till_here+1;
			mainDfs(temp->friend_list[i]);
		}
	}
}


int Algorithms::bfs_shortest(GraphNode* a,GraphNode* b){
	bfs(a);
	return b->distance_till_here;
}

int Algorithms::dfs_shortest(GraphNode* a,GraphNode* b){
	dfs(a);
	return b->distance_till_here;
}

bool caseInsensitiveStringCompare(const string& str1, const string& str2) {
    if (str1.size() != str2.size()) {
        return false;
    }
    for (string::const_iterator c1 = str1.begin(), c2 = str2.begin(); c1 != str1.end(); ++c1, ++c2) {
        if (tolower(*c1) != tolower(*c2)) {
            return false;
        }
    }
    return true;
}

GraphNode* Algorithms::findByName(string s){
	int size=G.size();
	for(int i=0;i<G.size();i++){
		if(caseInsensitiveStringCompare(G[i]->name,s))return G[i];
	}
	return NULL;
}

GraphNode* Algorithms::findByID(string s){
	int size=G.size();
	for(int i=0;i<G.size();i++){
		if(caseInsensitiveStringCompare(G[i]->entry_code,s))return G[i];
	}
	return NULL;
}

set<GraphNode*> Algorithms::clique(set< GraphNode* > data,GraphNode * parent,int traversed){
	if(traversed>=(int)parent->friend_list.size()-1){
		return data;
	}
	GraphNode* curNode=parent->friend_list[traversed+1];
	set<GraphNode*> data1=clique(data,parent,traversed+1);
	set<GraphNode*> data2;
	bool flag=1;
	set<GraphNode*>::iterator it=data.end();
	for(it=data.begin() ; it!=data.end(); it++ ){
		flag=0;
		for(vector<GraphNode*>::iterator it1=(*it)->friend_list.begin() ; it1!=(*it)->friend_list.end(); it1++ ){
			if(caseInsensitiveStringCompare((*it1)->name,curNode->name)){
				flag=1;
				break;
			}
		}
		if(flag==0)break;
	}
	if(it==data.end() ){
		data.insert(parent->friend_list[traversed+1]);
		data2=clique(data,parent,traversed+1);
	}
	return data1.size()>data2.size()?data1:data2;
}

struct Node{
	int number;
	GraphNode* person;
};

struct comp{
	bool operator()(const pair<  int ,GraphNode* > &a,const pair< int ,GraphNode* > &b){
		return a.first>b.first;
	}
};

struct compare{
	bool operator()(const struct Node &a,const struct Node &b){
		return a.number>b.number;
	}
};


void Algorithms::dijkstra(GraphNode* stud1,GraphNode* stud2){
	int index=stud1->number;
	bool visited[G.size()];
	int pathLength[G.size()];
	GraphNode* parent[G.size()];
	memset(visited,false,sizeof(visited)/sizeof(bool));
	for(int i=0;i<G.size();i++){
		visited[i]=false;
		parent[i]=NULL;
		pathLength[i]=2e9;
	}
	pathLength[index]=0;

	priority_queue< pair<int,GraphNode*> , vector< pair<int,GraphNode*> > , comp >  heap;
	//priority_queue< Node , vector< Node > , comp >  heap;
	GraphNode* topNode;
	int dist;
	Node pair;
	pair.number=0;
	pair.person=stud1;
	heap.push( make_pair( 0 , stud1) );

	while(!heap.empty() ){
		dist = heap.top().first;
		topNode = heap.top().second;
		heap.pop();
		if(visited[topNode -> number])
			continue;
		visited[topNode -> number] = true;

		for(int i = 0 ; i < topNode->friend_list.size() ; i++){
			if(!visited[topNode->friend_list[i]->number]){
				if(pathLength[topNode->friend_list[i] ->number] >= dist + 1){
					parent[topNode->friend_list[i]->number] = topNode;
					pathLength[ topNode->friend_list[i]->number ] = dist + 1;
					heap.push( make_pair( dist + 1 , topNode->friend_list[i]) );
				}
			}
		}
	}

	if(pathLength[stud2->number]==2e9){
		cout<<"No path exists";
	}
	else{
		for(GraphNode* paren = stud2 ; paren!=stud1 ; paren=parent[paren->number]){
			if(paren!=NULL and paren->name!="")cerr << paren->name << " --> ";
			else{
				cerr<<"NULL pointer"<<endl;
				exit(-1);
			}
		}
		cout<< stud1->name << endl;
	}
}

