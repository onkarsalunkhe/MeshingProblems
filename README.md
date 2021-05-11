# MeshingProblems
Altair

## Problem 1
  Given and triangular surface mesh check where the mesh is Valid or not. An invalid mesh is that where it has a hole or void in it.
  Devise an algorithm.
  
  Given :The list of triangles is given in a vector ofvintegers trias, such that the (i + 1)th triangle ti is formed by vertices with  
  ids: trias[3 ∗ i], trias[3 ∗ i + 1], and trias[3 ∗ i + 2], ∀0 ≤ i ≤ trias.size() − 3,
                                  
## Solution 1 : Analytical approach
The Given surface mesh has only triangle mesh elements.  
It uses the idea that given the number of points on the surface of the sphere there exists exact number of triangulations.   

The analytical formula can be stated as  

                No of Trianlges  = 2 * Number of Nodes - 4
<p align="center">
    <img width="250" height="250" src="https://user-images.githubusercontent.com/29740347/117611194-0e845700-b131-11eb-97c7-1fc8e5c3db6c.png">
</p>

Imagine the Combined tetrahedron is nothing but a coarse spherical mesh.  
It has 6 unique nodes in total. The number of triangles formed on the surface mesh are 8.  
Using the derived equation,  

                No of triangles = 2*6 - 4 = 8  
Now, if you add 1 more point on the surface then we can connect the new point to the vertices of the triangle closest to it.  
It will create 3 new triangles and it will delete the orignal triangle.  
Hence, addition of each point will add 2 new triangles everytime.  
So, the problem is linear and hence can be formulated in the equation.  

### *Fun Fact :*  

<p align="center">
   <img width="300" height="300" src="https://user-images.githubusercontent.com/29740347/117783788-de13ea00-b210-11eb-99db-c7c22e1b38fc.png">
</p>

We can validate this formula for the structure of **Fullerene C60 - Allotrope of carbon.**  
It has 20 hexagoans and 12 pentagons.  

<p align="center">
   <img width="250" height="250" src="https://user-images.githubusercontent.com/29740347/117783966-0d2a5b80-b211-11eb-8199-25d2fca7e7e0.png">
   <img width="250" height="250" src="https://user-images.githubusercontent.com/29740347/117783968-0dc2f200-b211-11eb-8d36-b4cdee0702fe.png">
</p>

A convex hexagon creates 4 triangles and convex pentagon creates 3 triangle.

                Total number of triangles = 20*4 + 12*3 = 116

Using analytical equation,  

                Total number of triangles = 2*60 - 4 = 116

## Solution 2 : Computational approach  

<p align="center">
  <img width="250" height="250" src="https://user-images.githubusercontent.com/29740347/117613657-37a6e680-b135-11eb-9144-ad707b753c8e.PNG">
</p>

## Flowchart  
<p align="center">
   <img width="400" height="700" src="https://user-images.githubusercontent.com/29740347/117618918-9d4aa100-b13c-11eb-9124-7849498f0ace.png">
</p>

## Problem 2  
Given a triangular planar mesh. Incident trianlges are thoose who shares an edge.  
The task is to swap the edge and update the mesh.   
The list of triangles is given in a vector ofvintegers trias, such that the (i + 1)th triangle ti is formed by vertices with  
ids: trias[3 ∗ i], trias[3 ∗ i + 1], and trias[3 ∗ i + 2], ∀0 ≤ i ≤ trias.size() − 3  
Vector adj stores triangle ids, such that, adj[3 ∗ i], adj[3 ∗ i + 1], and adj[3 ∗ i+ 2] store the triangle id opposite of the first, second, and third vertex of triangle ti, respectively.  
After swapping the vectors trias and adj has to be updated.  

<p align="center">
   <img width="400" height="300" src="https://user-images.githubusercontent.com/29740347/117624948-7d6aab80-b143-11eb-9eba-42250107562e.PNG">
</p>

## Solution : Computational approach  

## Flowchart  
<p align="center">
   <img width="300" height="800" src="https://user-images.githubusercontent.com/29740347/117623042-4e533a80-b141-11eb-8788-eda1d70ee4ed.png">
</p>

