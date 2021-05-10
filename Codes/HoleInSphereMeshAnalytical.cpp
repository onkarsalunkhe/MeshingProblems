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

    void CheckValidity() {

        /*
        This functions checks the validity of the Spherical surface mesh with triangulations
        It uses the idea that given the number of points on the surface of the sphere there exists exact number of triangulations
        
        The analytical formula can be stated as 
            No of Trianlges  = 2 * Number of Nodes - 4
            
        This can also be justified by the fact that addition of every new point on the surface add 2 new trianlges to the mesh
        So this functions finds the no of unique nodes present in the given vector trias and
        It checks the No of trianlges given in the vector trias by trias.size()/3 and compares them using the equation
        If it matches mesh is Valid else the mesh has a hole i.e. it is invalid

        This logic is useful only if the surface mesh has only triangulations and not any square and above

        @param  None
        @return None
         */


        int NumTriag = v.size() / 3;

        sort(v.begin(), v.end());

        auto itr = unique(v.begin(), v.end());
        v.resize(distance(v.begin(), itr)); // Forms the vector of uniqus nodes

        int uniqueNodes = v.size();

        if (NumTriag == 2 * uniqueNodes - 4) {
            cout << "Valid : No holes" << endl;
        }
        else {
            cout << "Invalid : There exists a hole." << endl;
        }
    }
};

int main()
{
    // Input trias vector

    vector<int> trias = { 13,14,15,
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