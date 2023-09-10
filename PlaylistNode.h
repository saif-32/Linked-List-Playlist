#ifndef PLAYLISTNODE_H
#define PLAYLISTNODE_H

typedef struct PlaylistNode_struct {
    char uniqueID[50];
    char songName[50];
    char artistName[50];
    int songLength;
    struct PlaylistNode_struct* nextNodePtr;
} PlaylistNode;

void CreatePlaylistNode(PlaylistNode* thisNode, char id[], char songName[], char artistName[], int songLength, PlaylistNode* nextNode);
void InsertPlaylistNodeAfter(PlaylistNode* thisNode, PlaylistNode* newNode);
void SetNextPlaylistNode(PlaylistNode* thisNode, PlaylistNode* newNode);
PlaylistNode* GetNextPlaylistNode(PlaylistNode* thisNode);
void PrintPlaylistNode(PlaylistNode* thisNode);
int length(PlaylistNode* headNode);

#endif