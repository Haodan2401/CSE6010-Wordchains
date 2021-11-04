//
//  wordchains.c
//  wordchains
//
//  Created by Team 36 on 10/14/21.
//@author  Chen Wang(cwang784) Haodan Tan(htan74)

#include "additional.h"


void readFile(char* path, char* type, char* wordList){
    /* opening file for reading */
    FILE *fp;
    char singleLine[5];
    fp = fopen(path, type);
    // if failed return
    if(fp == NULL) {
        perror("Error opening file");
    }
    // read line by line
    int count = 0;
    while ((fscanf(fp, "%src", singleLine)) != EOF) {
        for (int i = 0; i < 4; i++) {
            wordList[count*4 + i] = singleLine[i];
        }
        count++;
    }
    // close file
    fclose(fp);
}

int judgeEdgeBetweenWords(char* word1, char* word2, int limit){
    // defualt no edge between two words
    int flag = 0;
    
    // Three of four characters keep the same
    // only the first element is not the same, but others all the same
    if (word1[1] == word2[1] && word1[2] == word2[2] && word1[3] == word2[3]){
        flag = 1;
    }
    // only the second element is not the same, but others all the same
    if (word1[2] == word2[2] && word1[3] == word2[3] && word1[0] == word2[0]){
        flag = 1;
    }
    // only the third element is not the same, but others all the same
    if (word1[3] == word2[3] && word1[1] == word2[1] && word1[0] == word2[0]){
        flag = 1;
    }
    // only the fourth element is not the same, but others all the same
    if (word1[2] == word2[2] && word1[1] == word2[1] && word1[0] == word2[0]){
        flag = 1;
    }
    
    if (limit) {
        // swap two adjacent letters
        // swap the first and second character
        if (word1[0] == word2[1] && word1[1] == word2[0] && word1[2] == word2[2] && word1[3] == word2[3]){
            flag = 1;
        }
        // swap the third and second character
        if (word1[0] == word2[0] && word1[1] == word2[2] && word1[2] == word2[1] && word1[3] == word2[3]){
            flag = 1;
        }
        // swap the third and fourth character
        if (word1[0] == word2[0] && word1[1] == word2[1] && word1[2] == word2[3] && word1[3] == word2[2]){
            flag = 1;
        }
    }
    // 1 for edge, 0 for no edge
    return flag;
}

// Create a Node
struct Node* createNode(int);
struct Node* createNode(int node) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->wordIndex = node; //node index
    newNode->next = NULL;
    return newNode;
}

// Create a graph
struct Graph* createAGraph(int words) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numWords = words; // total nodes number
    graph->adjLists = malloc(words * sizeof(struct Node*));
    int i;
    for (i = 0; i < words; i++)
        graph->adjLists[i] = NULL;
    
    return graph;
}

// Add edge
void addEdge(struct Graph* graph, int src, int det) {
    // Add edge from src to det
    struct Node* newNode = createNode(det);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    
    // Add edge from det to src
    newNode = createNode(src);
    newNode->next = graph->adjLists[det];
    graph->adjLists[det] = newNode;
}

// Print the graph (only for tested)
void printGraph(struct Graph* graph) {
    int node;
    for (node = 0; node < graph->numWords; node++) {
        struct Node* temp = graph->adjLists[node];
        printf("\n wordIndex %det\n: ", node);
        while (temp) {
            printf("%det -> ", temp->wordIndex);
            temp = temp->next;
        }
        printf("\n");
    }
}



struct MinHeapNode* newMinHeapNode(int node, int dist)
{
    struct MinHeapNode* minHeapNode = (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeapNode->node = node;
    minHeapNode->dist = dist;
    return minHeapNode;
}


struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}


void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    //swap two nodes
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}



void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
    
    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist ) smallest = left;
    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist ) smallest = right;
    
    if (smallest != idx)
    {
        
        struct MinHeapNode *smallestNode = minHeap->array[smallest];
        struct MinHeapNode *idxNode = minHeap->array[idx];
        
        // Swap positions
        minHeap->pos[smallestNode->node] = idx;
        minHeap->pos[idxNode->node] = smallest;
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}



int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}


struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (isEmpty(minHeap)) return NULL;
    struct MinHeapNode* root = minHeap->array[0];
    
    // Replace root node with last node
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
    
    // Update position of last node
    minHeap->pos[root->node] = minHeap->size-1;
    minHeap->pos[lastNode->node] = 0;
    
    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);
    
    return root;
}

void shortDis(struct MinHeap* minHeap, int node, int dist)
{
    //update the shortest distance
    int i = minHeap->pos[node];
    minHeap->array[i]->dist = dist;

    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        // Swap this node with its prev
        minHeap->pos[minHeap->array[i]->node] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->node] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}


int isInMinHeap(struct MinHeap *minHeap, int node)
{
    if (minHeap->pos[node] < minHeap->size) return 1;
    return 0;
}




void printArr(int dist[], int prev[], int src, int det, int n, char* wordSet)
{
    
    double totaldit = 0.0;
    int totalnum = 0;
    for (int i = 0; i < n; ++i){
        //calculte the total reachable nodes, and average distance
        if (dist[i] != 10000) {
            totalnum++;
            totaldit += dist[i];
        }
        // find the target source and destination word chain
        if (dist[i] != 10000 && i == det){
            printf("From '%c%c%c%c' to '%c%c%c%c', the distance is: %d and the path is:\n",wordSet[src*4+0],wordSet[src*4+1],wordSet[src*4+2],wordSet[src*4+3],wordSet[i*4+0],wordSet[i*4+1],wordSet[i*4+2],wordSet[i*4+3], dist[i]);
            printf("%c%c%c%c -> ", wordSet[src*4+0],wordSet[src*4+1],wordSet[src*4+2],wordSet[src*4+3]);
            printPath(prev, i, wordSet, det);
        }
        else{
            if (i == det) {
                printf("There is no shortest path from %c%c%c%c to %c%c%c%c. \n",wordSet[src*4+0],wordSet[src*4+1],wordSet[src*4+2],wordSet[src*4+3],wordSet[i*4+0],wordSet[i*4+1],wordSet[i*4+2],wordSet[i*4+3]);
            }
            
        }
    }
    printf("The total reachable words is %d, and average chain words are %f \n", totalnum, totaldit/totalnum);
}

void printPath(int prev[], int destination, char* wordSet, int det){
    if (prev[destination] == -1){
        return;
    }
    printPath(prev, prev[destination], wordSet, det);
    int i = destination;
    if (destination == det){
        printf("%c%c%c%c\n", wordSet[i*4+0],wordSet[i*4+1],wordSet[i*4+2],wordSet[i*4+3]);
    }
    else{
        printf("%c%c%c%c -> ", wordSet[i*4+0],wordSet[i*4+1],wordSet[i*4+2],wordSet[i*4+3]);
    }
    
}


void dijkstra(struct Graph* graph, int src, int det, char* wordSet)
{
    // define variables
    int numWords = graph->numWords;
    int dist[numWords];
    
    // record the previous node
    int prev[numWords];
    prev[src] = -1;

    //create minHeap by number of nodes in graph
    struct MinHeap* minHeap = createMinHeap(numWords);
    
    // Initialize min heap
    for (int node = 0; node < numWords; ++node)
    {
        dist[node] = 10000;
        minHeap->array[node] = newMinHeapNode(node, dist[node]);
        minHeap->pos[node] = node;
    }
    
    // set the distance of source is 0
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    minHeap->size = numWords;
    dist[src] = 0;
    shortDis(minHeap, src, dist[src]);
    
    //  loop untill all nodes found the shortest path
    while (!isEmpty(minHeap))
    {
        // find ndoes that has shortest path
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->node;
        
        // update the distance for adjance node of u
        struct Node* currentList = graph->adjLists[u];
        while (currentList != NULL)
        {
            int node = currentList->wordIndex;
            
            // update the shortest path
            if (isInMinHeap(minHeap, node) && dist[u] != 10000 && 1 + dist[u] < dist[node])
            {
                dist[node] = dist[u] + 1;
                prev[node] = u;
                shortDis(minHeap, node, dist[node]);
            }
            currentList = currentList->next;
        }
    }
    
    // print the calculated shortest distances
    printArr(dist, prev, src, det, numWords, wordSet);
}
