//
//  main.c
//  wordchains
//
//  Created by Team 36 on 10/13/21.
//@author  Chen Wang(cwang784) Haodan Tan(htan74)

#include <stdio.h>
#include <stdlib.h>
#include "additional.h"



int main (int argc, char * argv[]) {
    
    /*
     opening file for reading
     */
    //using relative path to read the txt file, and store each word to char[]
    char path[] = "wordlist.txt";
    char* type = "r";
    //def variables to store word list
    char wordlist[500*4] = {0};
    char wordSet[500][5] = {0};
    
    // read the arguments
    int src = atoi(argv[1]);
    int det = atoi(argv[2]);
    readFile(path, type, wordlist);
    for (int i = 0; i < 500; i++) {
        for (int j = 0; j < 4; j++) {
            wordSet[i][j] = wordlist[i*4 + j];
        }
    }

    
    /*
     creat the graph object
     */
    //initial the graph
    struct Graph* graph = createAGraph(500);
    
    //add the edge depends on whether includes swag or not
    int swag = 0;
    if (argc == 4) {
        swag = 1;
    }
    for (int i = 0; i < 500; i++) {
        for (int j = i+1; j < 500; j++) {
                int judge = judgeEdgeBetweenWords(wordSet[i], wordSet[j], swag);
                if (judge == 1) {
                    addEdge(graph, i, j);
            }
        }
    }
    
    
    /*
     find the shortest path and print the result
     */
    // using dijkstra method to find shortest path
    dijkstra(graph, src, det, wordlist);

    
    return(0);
}

