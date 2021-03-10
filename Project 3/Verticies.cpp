#include "verticies.h"
#include <iostream>
#include <cmath>
#include<algorithm>

#define infinity 999999 //macro to represent infinity since INT_MAX causes overflow in program to - INT_MAX

using namespace std;

/*method that returns the degree of a vertex by counting the edges or "links" it contains*/
int Verticies::degree(Verticies* arr , int position) {
	int count = 0; 
	Verticies* temp = arr[position].next;
	while (temp != nullptr) {
		count++;
		temp = temp->next;
	}
	return count;
}

//Prints out the number of edges in an array of pointers
void Verticies::printEdges(Verticies* arr, int position) {
	Verticies* temp = arr[position].next;
	if (arr[position].next == nullptr) {
		cout << "has no edges\n";
	}
	else {
		while (temp != nullptr) {
			cout << temp->number << "\n";
			temp = temp->next;
		}
	}
}

/*Links the verticies together to make an edge between them*/
void Verticies::linkVert(int start, int end, Verticies* arr) {
	if (start != end) {
		Verticies* startVert = new Verticies(start);
		Verticies* endVert = new Verticies(end);
		startVert->next = arr[end].next;
		endVert->next = arr[start].next;
		arr[end].next = startVert;
		arr[start].next = endVert;
	}
	else {
		return;
	}
}

/*Default constructor of a vertex*/
Verticies::Verticies() {
	number = 0;
	marked = false;
	next = nullptr;
	key = infinity;
}

/*Constructor with variable*/
Verticies::Verticies(int num) {
	number = num;
	marked = false;
	next = nullptr;
	weight = 1;
	key = infinity;
}

/*Prints the Degree distribution of given graph */
void Verticies::distribution(Verticies* arr, int size) {
	if (size <= 100) {//if the number of vertecies is small
		cout << "X axis = Degree of Vertex\nY axis = Vertex number \n\n   ";
		for (int i = 1; i < size; i++) {
			cout << i << "    "; 
		}
		int degree[100];//new array to hold the degree of a vertex
		for (int i = 0; i < size; i++) {
			degree[i] = arr->degree(arr, i);//store the degree of each vertex
		}
		cout << "\n\n";
		for (int i = 0; i < size; i++) {
			cout << i;
			int x = degree[i];//get the  degree of each  vertex by index
			while (x > 0) {//while x isn't 0 print a asterisk
				cout << "  *  ";
				x--;
			}
			cout << "\n";
		}
	}
	 else if (size > 100) {

		int min = 1;
		int countOfNodes[12];//make an array of size 10 and have it hold the index
		int minCount[12];//holds the minimum value for a node count for a given range
		int countSize = size / 10;
		int i = 0;
		minCount[0] = 1;
		cout << "Node Count = X-axis\nDegree = Y-axis\n\n\t";
		while (min <= size) {
			cout << min  << "-" << min + countSize << " ";
			min = min + countSize + 1;
			minCount[i + 1] = min;
			countOfNodes[i] = min;//hold max value of for count aggreggate
			i++;
		}

		int bucketSize = size / 20;//we are going to have 20-21 buckets for histogram

		int buckets[21];//each index of bucket will hold the number of vertiicies that have n edges and fall into that index
		int maxBucketVal[21];//holds the max number possible before you have to move to a larer bucket

		i = 0;
		int x = 0;
		while (x < 21) {//set all of the values for maximumn values for node count
			maxBucketVal[x] = i + bucketSize;
			buckets[x] = 0;//initilizing all of the buckets to be 0
			i = i + bucketSize + 1;
			x++;
		}
		i = 0;
		min = 0;
		while (i < size) {//store the degree of each node and decide which bucket it will go in 
			x = 0;
			min = arr->degree(arr, i);
			while (min > maxBucketVal[x]) {//while min can keep going into a larger range
				x++;
			}
			buckets[x] = buckets[x] + 1;
			i++;
		}
		x = 1;
		min = 1;
		
		for (int i = 0; i < 21; i++) {//print out the number of nodes as stars that are in this bucket
			cout << "\n" << x << "-"<< maxBucketVal[i];
			int position = 0;//reset thr position to 0 before we enter this look every time

			while (buckets[i] >= minCount[position]) {//while the number in that bucket more than the bucket it is currently in
				cout << "    *    ";
					position++;
			}
			x = maxBucketVal[i];
			cout << "\n";
		}

	}

}

/*The function returns the number of componets of the graph using a depth first algorithhm and a stack*/
void Verticies::components(Verticies* arr, int size ) {
	int dummy = 0;
	int  count = 0;//count of components of the graph
	for (int i = 0; i < size; i++) {
		dummy = 0;
		if (arr[i].marked == false) {
			Stack* stack = new Stack();//create a new stack

			stack->Push(arr[i].number);//push i onto the stack

			while (stack->isEmpty() != true) {//while the stack isn't empty
				Verticies* x = stack->Pop();//get the value of the pointer on top

				if (arr[x->number].marked == false) {//if we haven't visited the node
					arr[x->number].marked = true;//mark the vertex
					dummy++;//increment size;
					
				}
				Verticies* temp = arr[x->number].next;// head of index
				while (temp != nullptr) {//while we havent walked on off of the adjacency list
					if (arr[temp->number].marked == false) {//if we haven't visited the vertex
						stack->Push(temp->number);//push the node onto the stack
					}
					temp = temp->next;//move the pointer down the list
				}
				delete x;//deallocate the ptr
			}
			count++;//increment the number of components 
			cout << "component " << count << " has size of " << dummy<<"\n";
		}
	}
	for (int i = 0; i < size; i++) {//reset the verticies back to be unmarked
		arr[i].marked = false;
	}
	
}

//prints out the shortest path from starting vertex to ending vertex
void Verticies::shortestPath(Verticies* graph, int start, int end, int size) {
	int* distance = new int[size];//make an array to hold the distance
	Verticies* parent = new Verticies[size];//dyamic array to hold set of nodes that have been finalized
	for (int i = 0; i < size; i++) {
		distance[i] = infinity;
		parent[i] = i;//initialize all of the nodes in parent array to be null
		parent[i].next = nullptr;
		parent[i].weight = infinity;

	}
	Heap* minHeap = new Heap(size);//make a new heap
	minHeap->insert(graph, size);//inser the graph into the heap
	minHeap->decreaseKey(start, 0);//set the starting vertex of the graph distance we 0
	distance[start] = 0;//set the starting vertex distance to 0

	while (minHeap->isInHeap(end) != false ) {//while we havent 
		int u = minHeap->deleteMin();//extract the minimum weight node in the heap
		Verticies* temp = graph[u].next;
		while (temp != nullptr) {
			int v = temp->number;//the number of the vertex of temp while it walks down the list
			if (minHeap->isInHeap(v) == true && distance[u] != infinity && distance[v] > temp->weight + distance[u]) {//if the vertex hasnt been chosen into set and distance is not infinity, and the distance is shorter than previous min
				distance[v] = distance[u] + temp->weight;//update the distance to be the the new min
				Verticies* x = new Verticies(u);//create a new pointer x to insert into the set
				x->weight = distance[v];
				parent[v].next = x;//set temp to be next of set for display of path
				minHeap->decreaseKey(v, distance[v]);//decrease the weight  of the vertex v to be new min distance
			}
			temp = temp->next;//move the pointer down the list
		}

	}
	//print the path of the the start to end in reverse order from end to start
	int i = end;
	bool connected = true;
	do {
		cout << i << " to \n";
		if (parent[i].next != nullptr)
			i = parent[i].next->number;
		else {
			cout << "vertexes are not connected\n";
			connected = false;
			break;//break from the loop
		}

	} while (i != start);
	if(connected == true)//if the graph is connected print out the distance
	cout << parent[start].number << "\ndistance  = " << parent[end].next->weight;
}

/*this function returns the diameter of the graph*/
int Verticies::diameter(Verticies* graph, int size) {
	int** matrix = new int*[size];// made a dynamic 2D array to hold the edges
	for (int i = 0; i < size; i++) {
		matrix[i] = new int[size];
		for (int j = 0; j < size; j++) {
			if (i == j) {// if we are at a vertex we set the distance to be 0
				matrix[i][j] = 0;
			}
			else {
				matrix[i][j] = infinity;//assign all of the elements in the matrix to hold the value of infinity
			}
		}
	}
	Verticies* temp;
	for (int i = 0; i < size; i++) {
		temp = graph[i].next;
			while (temp != nullptr) {
				matrix[i][temp->number] = temp->weight;// go through ans assign all of the edges in the graph of adjacencies
				temp = temp->next;//move the temp down the linked list
		}
	}


//floyd warshall algorithmn to implement the min-pairs 
	for (int k = 0; k < size; k++) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (matrix[i][k] + matrix[k][j] < matrix[i][j]) {// if there is a shorter path than before overwrite what we had in the matrix			
					matrix[i][j] = matrix[i][k] + matrix[k][j];			
				}
			}
		}
	}

	int max = 0;
	//goes through the matrix and find the largest of the min paths 
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (matrix[i][j] > max && matrix[i][j] != infinity)
				max = matrix[i][j];
		}
	}

	return max;

}


void  Verticies::spaning_tree(Verticies* graph, int size) {
	int* key = new int[size]; //dynamic array to hold keys
	Verticies* parent = new Verticies[size];//make a dynamic array to hold the info about the edges indexes
	int* set = new int[size];

	for (int i = 0; i < size; i++) {
		parent[i].next = nullptr;//set all of the parent nodes in the parent array to be set to null
		key[i] = infinity;
		set[i] = -1;
	}
	Heap* minHeap = new Heap(size);//make a new heap to hold the vertexes
	minHeap->insert(graph, size);
	minHeap->decreaseKey(0, 0, 0);//decrease the key value of the node so it comes to top of heap
	for (int i = 0; i < size; i++) {
		minHeap->arr[i]->weight = 1;
	}

	while (minHeap->currentSize > 0) {
		
		int u = minHeap->deleteMin();//get the index u to be the start 

		Verticies* temp = graph[u].next; {//check all the adjacencies of the vertex in the graph
			while (temp != nullptr) {
				int v = temp->number;
				if (minHeap->isInHeap(v) == true && temp->weight < key[v]) {//if it is in the min heap and weight is less than the key
					Verticies* x = new Verticies();
					x->key = temp->weight;
					x->number = u;
					key[v] = temp->weight;
					parent[v].next = x;
					set[v] = u;
					minHeap->decreaseKey(v, key[v], 0);
					
				}

				temp = temp->next;
			}

		}
	}
	int count = 0;
	for (int i = 0; i < size; i++) {

			cout << i << " and " << set[i] << "\n";
			count++;
	}
	cout << "number of edges is of spanning tree is " << count << endl;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//stack implementation
Stack::Stack() {
	top = nullptr;
}
//pushes a new node onto the stack
void Stack::Push(int x) {
	Verticies* temp = new Verticies(x);//make a new node 
	if (top == nullptr) {//if the stack is empty
		top = temp;
	}
	else {//link with temp with previous top and its contents
		temp->next = top;
		top = temp;//make temp be the new top
	}
}
//removes the top node on the stack
Verticies* Stack::Pop() {
	if (top == nullptr) {
		return nullptr;//empty stack so there is nothing to pop
	}
	else {
		 Verticies* temp = top;//make temp hold the top
		 top = top->next;//move the top to the 2nd element in stack
		 int i = temp->number;//get the value of the ptr
		 return temp;
	}
}

//checks if the stack is empty
bool Stack::isEmpty() {
	if (top == nullptr)
		return true;
	else
		return false;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Queue::Queue() {
	front = nullptr;
	rear = nullptr;
}

bool Queue::isEmpty() {
	if (front == nullptr)
		return true;
	else
		return false;
}

void Queue::enqueue( int x) {
	Verticies* temp = new Verticies(x);//make a new node
	if (rear == nullptr && front == nullptr) {
		front = rear = temp;
		return;
	}
	rear->next = temp;
	rear = temp;
}


void Queue::dequeue() {
	Verticies* temp = front;
	if (front == nullptr)
		return;
	if (front == rear) {
		front = nullptr;
		rear = nullptr;
	}
	else {
		front = front->next;
	}
	delete temp;
}

Verticies* Queue::peek() {
	if (front == nullptr)
		return nullptr;
	else
		return front;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Heap Implementation
Heap::Heap(int x) {
	arr = new Verticies*[x];//make a dynamic double pointer to hold the nodes of the graph as a heap
	capacity = x;//maximum capacity of a heap
	currentSize = 0;//initialize the size to be 0
}

/*inserts the graph into a heap*/
void Heap::insert(Verticies* graph, int size) {
	for (int i = 0; i < size; i++) {
		Verticies* temp = new Verticies(i);
		temp->weight = infinity;
		temp->key = infinity;
		currentSize++;
		arr[i] = temp;
	}
}

//get right child of node
int Heap::right(int position) {
	return 2*position +2;
}

//get left child of node
int Heap::left(int position) {
	return (2*position)+1;
}

//get parent of a node
int Heap::parent(int pos) {
	return (pos - 1) / 2;
}

/*used to fix a node that violates heap property by bubbling down*/
void Heap::minHeapify(int position) {
	int smallest;
	int left = this->left(position);
	int right = this->right(position);
	if (left < currentSize && arr[left]->weight < arr[position]->weight)
		smallest = left;
	else
		smallest  = position;
	if (right < currentSize && arr[right]->weight < arr[position]->weight) {
		smallest = right;
		}
	if (smallest != position) {
		swap(arr[position],arr[smallest]);
		minHeapify(smallest);
	}
}

/*builds  min heap */
void Heap::buildMinHeap() {
	int i = floor(double(currentSize / 2));
	for (i ; i >= 0; i--) {
		minHeapify(i);
	}
}

//swaps 2 verticies pointers in an a verticies double pointer
void Heap::swap(Verticies* v1, Verticies* v2) {
	Verticies temp = *v1;
	*v1 = *v2;
	*v2 = temp;
}

//takes a index in the heap and bubbles the value up if needed
void Heap::bubbleUp(int index) {
	while (index > 0 && arr[parent(index)]->weight > arr[index]->weight) {//while we havent gotten to the root of the heap and the inserted node is violating min heap property
		swap(arr[index], arr[parent(index)]);
		index = parent(index);
		
	}
}

//overloaded to make it work for spanning tree
void Heap::bubbleUp(int index, int dummy) {
	while (index > 0 && arr[parent(index)]->key > arr[index]->key) {
		swap(arr[index], arr[parent(index)]);
		index = parent(index);
	}

}

/*this function decreases the key at a given index of a heap and bubbles it up to the correct position if needed*/
void Heap::decreaseKey(int vertex, int distance) {
	int j;//will hold index of the node in the heap if it exists
	for (int i = 0; i < this->currentSize; i++) {
		if (arr[i]->number == vertex) {//we found the node in the heap
			arr[i]->weight = distance;//update the distance value
			j = i;//store the index in j
		}
	}
	this->bubbleUp(j);//bubble up the node until it satisfies min-heap property
}

/*overloaded function to be used in min-spanning tree*/
void Heap::decreaseKey(int vertex, int keyVal, int dummy) {
	int j;
	for (int i = 0; i < this->currentSize; i++) {
		if (arr[i]->number == vertex) {
			arr[i]->key = keyVal;
			j = i;
		}
	}
	this->bubbleUp(j, dummy);
}

//deletes the minimum from the heap - fix the tree and return the vertex number
int Heap::deleteMin() {
	int min = arr[0]->number;
	swap(this->arr[0], this->arr[currentSize-1]);//swap the node with the last one in the heap
	currentSize--;//decrease the current size by 1
	minHeapify(0);
	delete arr[currentSize];//delete the node from the min heap
	arr[currentSize] = nullptr;//set the node to be a null pointer
	return  min;//return the node;

}

int Heap::deleteMin(int dummy) {
	return -1;
}
//checks to see if a given vertex is in the tree or has been extracted
bool Heap::isInHeap(int vertex) {
	for (int i = 0; i < currentSize; i++) {
		if (vertex == arr[i]->number) {//if the node is in he heap
			return true;
		}
	}
	return false;
}

//debugging function to print contents of a heap at a given point
void Heap::PrintHeap() {
	for (int i = 0; i < currentSize; i++) {
		cout << arr[i]->number << " weight " << arr[i]->weight << " key " << arr[i]->key<< endl;
	}
	cout << "\n\n";
}









////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

