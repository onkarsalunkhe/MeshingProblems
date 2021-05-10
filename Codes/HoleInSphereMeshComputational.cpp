#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class SphereMesh {
    /*
    This class creates provides the function to Check the validity of the Mesh
    The Input is Vector of trias with triangle node numbering
    */
private:
    vector<int> v;  // Member variable

public:
    // Constructor to assign the input vector to member variable
    SphereMesh(vector<int> v) {
        this->v = v;
    }

public:
    void CheckValidity() {

        /*
        This functions checks the validity of the Spherical surface mesh with triangulations
        It uses the idea that the Surface mesh is valid if all the edges of trianlges are shared at exactly two trianlges.
        If an edge is shared by 1 triangle or more than 3 triangles the mesh has a hole or it is invalid.
        
        @param  None
        @return None
        */

        // Assumption : At least 5 points are needed to create a coarse sphere in 3D

        if (v.size() >= 5)
        {
            // Creates the vector of edges where all the edges will be stored
            vector<vector<int>> edges;  

            for (int i = 0; i <= v.size() - 3; i += 3)
            {
                sort(v.begin() + i, v.begin() + i + 3);

                vector<vector<int>> vec;    // Temporory vector to make pairs and store them in sorted order

                for (int k = 0; k < 2; k++) {
                    vector<int> r;
                    for (int j = k + 1; j < 3; j++) {
                        r.push_back(v[i + k]);
                        r.push_back(v[i + j]);
                        vec.push_back(r);
                        r.clear();
                    }
                }

                // This loops checks where the edge is already present in the vector edges or not.
                // If it exists it deletes it
                // If it is absent it appends it
                for (int j = 0; j < 3; j++)
                {
                    auto itr = find(edges.begin(), edges.end(), vec[j]);
                    if ( itr != edges.end())
                    {
                        edges.erase(itr);
                    }
                    else
                        edges.push_back(vec[j]);
                }
            }

            // In the end is the edges vector is empty that means all the edges had pair and hence mesh is valid
            // Else one or more edge was not in pair hence mesh is invalid
            cout << "Edges " << edges.size() << endl;
            if (edges.size() == 0) {
                cout << "Valid : No holes" << endl;
            }
            else {
                cout << "Invalid : There exists a hole." << endl;
            }
        }
        else {
            cout << "Invalid input (Mesh vector should have at least 5 points to make a sphere mesh) " << endl;
        }
    }
};


int main()
{
    // Input trias vector
    vector<int> trias = { 13,14,15,
        100,101,102,
15,14,6,
13,12,14,
1,13,15,
15,16,17,
17,16, 2,
15, 6,16,
1,15,17,
17,18,19,
19,18, 8,
17, 2,18,
1,17,19,
19,20,21,
21,20,11,
19, 8,20,
1,19,21,
21,22,13,
13,22,12,
21,11,22,
1,21,13,
16,23,24,
24,23,10,
16, 6,23,
2,16,24,
14,25,26,
26,25, 5,
14,12,25,
6,14,26,
22,27,28,
28,27, 3,
22,11,27,
12,22,28,
20,29,30,
30,29, 7,
20, 8,29,
11,20,30,
18,31,32,
32,31, 9,
18, 2,31,
8,18,32,
33,34,35,
35,34, 5,
33,10,34,
4,33,35,
35,36,37,
37,36, 3,
35, 5,36,
4,35,37,
37,38,39,
39,38, 7,
37, 3,38,
4,37,39,
39,40,41,
41,40, 9,
39, 7,40,
4,39,41,
41,42,33,
33,42,10,
41, 9,42,
4,41,33,
34,23,26,
26,23, 6,
34,10,23,
5,34,26,
36,25,28,
28,25,12,
36, 5,25,
3,36,28,
38,27,30,
30,27,11,
38, 3,27,
7,38,30,
40,29,32,
32,29, 8,
40, 7,29,
9,40,32,
42,31,24,
24,31, 2,
42, 9,31,
10,42,24
    };

    // Object of class SphereMesh
    SphereMesh obj(trias);

    // Function call
    obj.CheckValidity();

    return 0;
}