#pragma once
struct Verticies {

	//MEMBER VARIABLES///////////////////////////////////////////////////////
	int number;//contains the number of the node
	int weight;//the weight to get from one vertex to another
	int key;//key value of the node to be used in primm min spanning tree
	bool marked;//whether the  verticie is marked or unmarked
	Verticies* next;//pointer what the vertex is connected to
	



	//Struct member functions///////////////////////////////////////////////

	Verticies();//default costructor
	
	Verticies(int num);// constructor with parameter

	void linkVert(int start , int end , Verticies* );//links 2 verticies together

	void printEdges(Verticies*, int position);//prints the edges of a given vertex

	int degree(Verticies* arr, int position);//returns the degree of a Vertex in an array of Vertecies

	void distribution(Verticies*, int size);//prints out the degree distribution of graph as a histogram

	void components(Verticies* arr, int size );//returns the number of components of a graph using depth first search

	void shortestPath( Verticies* arr, int start, int end , int size);//prints out the shortest path in the graph from start to end

	int diameter(Verticies* graph, int size);

	void spaning_tree(Verticies* graph, int size);

};


///////////////////////////////////////////////////////////////////////////////////////////////////

struct Stack {
	Verticies* top;

	Stack();//default constructor
	bool isEmpty();
	void Push(int x);
	Verticies* Pop();
};
////////////////////////////////////////////////////////////////////////////////////////////////////

struct Queue {
	Verticies* front;
	Verticies* rear;
	Queue();//default constructor
	bool isEmpty();//
	void enqueue(int);
	void dequeue();
	Verticies* peek();
};
///////////////////////////////////////////////////////////////////////////////////////////////////

struct Heap { //heap implementation for use in dijkstras algorithm
	Verticies** arr;
	int capacity;
	int currentSize;

	Heap(int x);
	void insert(Verticies* graph, int size);
	int right(int position);
	int left(int position);
	int parent(int pos);

	void decreaseKey(int position, int distance);
	void decreaseKey(int position, int keyVal, int dummy);

	int deleteMin();
	int deleteMin(int dummy);

	void minHeapify(int position);
	

	void buildMinHeap();

	void swap(Verticies*, Verticies*);

	void bubbleUp(int pos);
	void bubbleUp(int pos, int dummy);


	bool isInHeap(int vertex);
	void PrintHeap();
};




