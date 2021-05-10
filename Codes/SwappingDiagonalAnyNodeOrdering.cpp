#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;

class PlanarTriagMesh {

	/*
	This class provides the function to swap the diagonal of two incident trianlgles in Planar triangular mesh
	Incident trianlge are those who share a common edge
	It takes the vector of trias and adj from the main
	*/

public:
	// Member variables
	vector<int> & trias;
	vector<int> & adj;

public:
	// Passing by reference the information of vectors trias and adjs
	// It is useful as we have the update the existing vectors after swapping
	PlanarTriagMesh(vector<int>& trias_, vector<int>& adj_) : trias(trias_), adj(adj_) {
	}

public:
	void SwapDiag(int i, int j) {

		/*
		This function takes the arguments as ids of 2 incident triangles
		Firstly, it stores the node ordering of all the trianlges adjecent to swapping trianlges
		It creates an unordered map which stores the pairs of nodes (i.e. edges) as value and the triangle number as key
		Then it generates the vector of nodes after swapping the diaggonal and updates the vector trias
		Now, it will insert the triangle opposite to each node by searching for the triangle common to the opposite edge of that vertex
		
		This logic can be useful irrespective of the type of elements in the surface mesh (i.e. It can be trianlgles or any polygon)

		@param		i		index of first trianlge to swap
		@param		j		index of second incident trianlge to swap
		@return		None
		*/

		int arr[] = { i , j };		// Vector of ids of swapping trianlges

		vector<int> vec;			// Temporary vector to store the node numbers
		map<pair<int,int>, int> pairMap;		// Map of pairs and triangle index
		
		// Store the Node numbering of all adjecent tringles and create an unordered map of pairs
		// The pairs are nothing but the edges in that trianlges stored in sorted way so that they are easy to search for
		// 

		for (int t = 0; t < 2; t++) {
			for (int k = 3*arr[t] ; k < 3 * arr[t] + 3; k++) {
				if (adj[k] == arr[0] + 1 || adj[k] == arr[1] + 1 || adj[k] == -1) {
					continue;
				}
				else{
					vec.push_back(trias[3 * (adj[k] - 1)]); vec.push_back(trias[3 * (adj[k] - 1) + 1]); vec.push_back(trias[3 * (adj[k] - 1) + 2]);
					sort(vec.begin(), vec.end());

					for (int b = 0; b < 2; b++) {
						pair<int, int> r;
						for (int c = b + 1; c < 3; c++) {
							pairMap[make_pair(vec[b], vec[c])] = adj[k];
						}
					}
					vec.clear();
				}
			}
		}
		
		vec.push_back(trias[3*arr[0]]);		vec.push_back(trias[3*arr[0] + 1]);		vec.push_back(trias[3* arr[0] + 2]);
		vec.push_back(trias[3* arr[1]]);	vec.push_back(trias[3* arr[1] + 1]);	vec.push_back(trias[3* arr[1] + 2]);

		// It finds out the common edge in the given adjecent triangles and the uncommon nodes
		// Using those it updates the trias vector such that the diagonal has swapped

		vector<int> common;
		vector<int> uncommon;
		int n = 0;
		while (n < 3)
		{
			auto it = find(vec.begin() + 1, vec.end(), vec[0]);
			if (it != vec.end()) {
				common.push_back(vec[0]);
				vec.erase(it);
			}
			else {
				uncommon.push_back(vec[0]);
			}
			vec.erase(vec.begin());
			n++;
		}

		if (common.size() < 2) {
			common.push_back(vec[0]);
		}
		else {
			uncommon.push_back(vec[0]);
		}
		vec.clear();

		trias[3* arr[0]]		= uncommon[0];
		trias[3* arr[0] +1]		= uncommon[1];
		trias[3* arr[1]]		= uncommon[0];
		trias[3* arr[1] + 1]	= uncommon[1];
		trias[3* arr[0] + 2]	= common[0];
		trias[3* arr[1] + 2]	= common[1];

		// ****************************************************************************** //

		// ComVec stores the updated vector of adjecent triangles as it is used to find out the adjecent triangles

		vector<vector<int>> combVec;
		vec.push_back(uncommon[0]); vec.push_back(uncommon[1]); vec.push_back(common[0]);
		combVec.push_back(vec);
		vec.clear();

		vec.push_back(uncommon[0]); vec.push_back(uncommon[1]); vec.push_back(common[1]);
		combVec.push_back(vec);
		vec.clear();

		/* This loop runs through both the triangles 
			It starts with first node and finds out the triangle which shares the edge opposite to it in the map
			And it updates the position in the adj vector with the triangle index
			It does this for for first 2 nodes
			For the third node the triangle adjecent to it would the other triangle to which we are swapping
		*/

		for (int t = 0; t < 2; t++) {
			vec.push_back(combVec[t][1]); vec.push_back(combVec[t][2]);
			sort(vec.begin(), vec.end());

			auto itr = pairMap.find(make_pair(vec[0], vec[1]));
			if (itr != pairMap.end()) {
				adj[3 * arr[t]] = itr->second;
			}
			else {
				adj[3 * arr[t]] = -1;
			}
			vec.clear();

			vec.push_back(combVec[t][0]); vec.push_back(combVec[t][2]);
			sort(vec.begin(), vec.end());

			itr = pairMap.find(make_pair(vec[0], vec[1]));
			if (itr != pairMap.end()) {
				adj[3 * arr[t] + 1] = itr->second;
			}
			else {
				adj[3 * arr[t] + 1] = -1;
			}
			vec.clear();

			adj[3 * arr[t] + 2] = arr[1-t] + 1;

		}
	}
};

int main()
{
	// Input trias and adj vectors

	vector<int> trias = {
1,2,5,
2,6,5,
2,3,6,
3,7,6,
3,4,7,
4,8,7,
5,6,9,
6,10,9,
6,7,10,
7,11,10,
7,8,11,
8,12,11,
9,10,13,
10,14,13,
10,11,14,
11,15,14,
11,12,15,
12,16,15
	};

	vector<int> adj = {
		2,-1,-1,
		7,1,3,
		4,2,-1,
		9,3,5,
		6,4,-1,
		11,5,-1,
		8,-1,2,
		13,7,9,
		10,8,4,
		15,9,11,
		12,10,6,
		17,11,-1,
		14,-1,8,
		-1,13,15,
		16,14,10,
		-1,15,17,
		18,16,12,
		-1,17,-1
	};

	// Object of class SphereMesh
	PlanarTriagMesh obj(trias,adj);

	int i, j;

	cout << "Enter the ids of adjecent triangles : " << endl;
	cin >> i >> j;

	// We need to decrement it because we can access the vextices in easy way in c++ style where the index starts with 0
	i = i - 1;
	j = j - 1;

	cout << "Orignal trias = " << endl;
	cout << trias[3 * i] << ',' << trias[3 * i + 1] << ',' << trias[3 * i + 2] << endl;
	cout << trias[3 * j] << ',' << trias[3 * j + 1] << ',' << trias[3 * j + 2] << endl;


	cout << "Orignal adjs = " << endl;
	cout << adj[3 * i] << ',' << adj[3 * i + 1] << ',' << adj[3 * i + 2] << endl;
	cout << adj[3 * j] << ',' << adj[3 * j + 1] << ',' << adj[3 * j + 2] << endl;

	// Call to function
	obj.SwapDiag(i ,j);

	cout << "Updated trias = " << endl;
	cout << trias[3 * i] << ',' << trias[3 * i + 1] << ',' << trias[3 * i + 2] << endl;
	cout << trias[3 * j] << ',' << trias[3 * j + 1] << ',' << trias[3 * j + 2] << endl;


	cout << "Updated adjs = " << endl;
	cout << adj[3 * i] << ',' << adj[3 * i + 1] << ',' << adj[3 * i + 2] << endl;
	cout << adj[3 * j] << ',' << adj[3 * j + 1] << ',' << adj[3 * j + 2] << endl;

}