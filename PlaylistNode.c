#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PlaylistNode.h"

void CreatePlaylistNode(PlaylistNode* thisNode, char id[], char songName[], char artistName[], int songLength, PlaylistNode* nextNode)
{
    strcpy(thisNode->uniqueID, id);
    strcpy(thisNode->songName, songName);
    strcpy(thisNode->artistName, artistName);
    thisNode->songLength = songLength;
    thisNode->nextNodePtr = NULL;
}

void InsertPlaylistNodeAfter(PlaylistNode* thisNode, PlaylistNode* newNode)
{
    PlaylistNode* temp = NULL;
    temp = thisNode->nextNodePtr;
    thisNode->nextNodePtr = newNode;
    newNode->nextNodePtr = temp;
}

void SetNextPlaylistNode(PlaylistNode* thisNode, PlaylistNode* newNode)
{
    thisNode->nextNodePtr = newNode;
}

PlaylistNode* GetNextPlaylistNode(PlaylistNode* thisNode)
{
    return thisNode->nextNodePtr;
}

void PrintPlaylistNode(PlaylistNode* thisNode)
{
    printf("Unique ID: %s\n", thisNode->uniqueID);
    printf("Song Name: %s\n", thisNode->songName);
    printf("Artist Name: %s\n", thisNode->artistName);
    printf("Song Length (in seconds): %d\n\n", thisNode->songLength);
}

int length(PlaylistNode* headNode)
{
    int n=0;
    PlaylistNode* t = headNode;
    while(t != NULL)
    {
        t = t->nextNodePtr;
        n++;
    }
    return n;

}