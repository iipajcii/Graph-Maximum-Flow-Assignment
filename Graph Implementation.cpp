#include <iostream>
#include <vector>
#include <tuple>
#include <string>
using namespace std;

class Graph {
	public:
		Graph (vector<int> &v, vector<tuple<int, int, int>> &e): v_(v), e_(e){}

		void edges() 
		{
			for(auto item: e_){cout << letter(std::get<0>(item)) << ":" << letter(std::get<1>(item)) << ":" << std::get<2>(item) << endl;}
		}

		void vertices()
		{
			for(auto item: v_){cout << letter(item) << endl;}
		}

		char letter(int i)
		{
			return 65 + i; //Chars are stored as int//65 is the ascii value of A
		}

		int pipeline_count()
		{
			int pipelines = 0, source_count = 0, sink_count = 0;
			int source = v_.front();
			int sink = v_.back();

			for(auto e : e_){if( std::get<0>(e) == source){source_count++;}}
			for(auto e : e_){if( std::get<1>(e) == sink){sink_count++;}}
			return source_count > sink_count ? sink_count : source_count;
		}

	private:
		vector<int> v_;
		vector<tuple<int,int,int>> e_;
};


int main()
{
	enum Edges {A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z};
	vector<int> v = {A,B,C,D,E};
	vector<tuple<int, int, int>> e = {{A,B,2},{B,C,7},{C,E,9},{A,D,4},{D,E,8}};
	Graph graph(v,e);
	cout << "Vertices" << endl;graph.vertices();
	cout << endl << "Weighted Edges" << endl; graph.edges();
	cout << endl <<"Connections to Source: " << graph.pipeline_count() << endl;

}
