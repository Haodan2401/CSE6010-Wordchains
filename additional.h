//
//  wordchains.h
//  wordchains
//
//  Created by Team 36 on 10/14/21.
// @author  Chen Wang(cwang784) Haodan Tan(htan74)
//

#ifndef wordchains_h
#define wordchains_h

#include <stdio.h>
#include <stdlib.h>
//_______________________________Part  A: read file and graph_________________________
/**
 *@brief    read the word txt file by relative path
 *@param path   relative path
 *@Param type   define open type
 */
void readFile(char* path, char* type, char* wordList);

/**
 *@brief    determine the edge between two words
 *@param word1  the source word
 *@param word2  the destination word
 *@param limit  whether use swag or not
 *@return 1 for having edge, 0 for na edge
 */
int judgeEdgeBetweenWords(char* word1, char* word2, int limit);


/**
 *@brief  Define Graph elements including Node, Graph
 */
struct Node {
  int wordIndex;
  struct Node* next;
};


struct Graph {
  int numWords;
  struct Node** adjLists;
};

struct Node* createNode(int);
/**
 *@brief create a new node
 *@param node is the index of words
 */
struct Node* createNode(int node);

/**
 *@brief create a new graph
 *@param words number of total nodes
 */
struct Graph* createAGraph(int words);

/**
 *@param graph this the words graph
 *@param src source of the edge
 *@param det destination of the edge
 */
void addEdge(struct Graph* graph, int src, int det) ;

/**
 *@brief print the graph (used for tested)
 *@param graph the graph required to print
 */
void printGraph(struct Graph* graph);

//___________________________________________Part B: find shortest path__________________-


/**
 *@brief define the struture used to find shortest path
 */
struct MinHeapNode
{
    int  node;
    int dist;
};

// Structure to represent a min heap
struct MinHeap
{
     
    // Number of heap nodes present currently
    int size;
   
    // Capacity of min heap
    int capacity;
   
    // This is needed for shortDis()
    int *pos;
    struct MinHeapNode **array;
};


/**
*@brief create a new Min Heap Node
*@param node current node
*@param dist distance recorded
*/
struct MinHeapNode* newMinHeapNode(int node, int dist);


/**
 *@brief recording current heap capacity
 *@param capacity current heap capacity
 */
struct MinHeap* createMinHeap(int capacity);

/**
 *@brief swap two path nde
 *@param a minheapnode
 *@param b minheapnode
 */
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b);


/**
 *@brief find the shortest current path
 *@param minHeap the shortest path
 *@param idx the current node index
 */
void minHeapify(struct MinHeap* minHeap, int idx);


/**
 *@brief check whether the minheap is empty or not
 *@param minHeap the minHeap required to check
 */
int isEmpty(struct MinHeap* minHeap);
 
/**
 *@brief find the shortest node in minHeap
 */
struct MinHeapNode* extractMin(struct MinHeap* minHeap);
 
/**
 *@brief find the shortest path for current node
 *@param minHeap current minHeap
 *@param node current node
 *@param dist  distance
 */
void shortDis(struct MinHeap* minHeap, int node, int dist);
 
/**
 *@brief check whether one node is in the minHeap or not
 *@param minHeap minheap
 *@param node current node
 */
int isInMinHeap(struct MinHeap *minHeap, int node);
 
/**
 *@brief print the shortest path
 *@param dist the distance from source to destination
 *@param prev the prev nodes
 *@param src the source node
 *@param det the destionation node
 *@param n total nodes
 *@param wordSet total words
 */
void printArr(int dist[], int prev[], int src, int det, int n, char* wordSet);

/**
 *@brief the main function to calculate the shortest path
 *@param graph the graph we created
 *@param src source node
 *@param det destination node
 *@param wordSet the word list
 */
void dijkstra(struct Graph* graph, int src, int det, char* wordSet);

/**
 *@brief print the shortest path nodes
 *@param prev] prev node lists
 *@param destinatin the current destination node
 *@param wordSet the word list
 *@param the final destination
 */
void printPath(int prev[], int destination, char* wordSet, int det);
#endif /* wordchains_h */
