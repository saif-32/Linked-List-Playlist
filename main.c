#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PlaylistNode.h"

void PrintMenu(char playlistTitle[]) {
   printf("%s PLAYLIST MENU\n", playlistTitle);
   printf("a - Add song\nr - Remove song\nc - Change position of song\ns - Output songs by specific artist\nt - Output total time of playlist (in seconds)\no - Output full playlist\nq - Quit\n\n");
}

PlaylistNode* ExecuteMenu(char option, char playlistTitle[], PlaylistNode* headNode) {
   if (option == 'a') // Add song.
   {
       char id[100];
       char songName[100];
       char artistName[100];
       int songLength = 0;
       PlaylistNode* temp = headNode;
       PlaylistNode* newNode = (PlaylistNode*)malloc(sizeof(PlaylistNode));
       
       printf("ADD SONG\n");
       printf("Enter song's unique ID:\n");
       fgets(id, 100, stdin);
       id[strlen(id)-1] = '\0';
       printf("Enter song's name:\n");
       fgets(songName, 100, stdin);
       songName[strlen(songName)-1] = '\0';
       printf("Enter artist's name:\n");
       fgets(artistName, 100, stdin);
       artistName[strlen(artistName)-1] = '\0';
       printf("Enter song's length (in seconds):\n");
       scanf("%d", &songLength);
       printf("\n");
      
       CreatePlaylistNode(newNode, id, songName, artistName, songLength, NULL);
       
        if (temp == NULL) // If there is no head node.
        {
           return newNode;
        }
        while(temp->nextNodePtr != NULL)
        {
            temp = temp->nextNodePtr;
        }
        InsertPlaylistNodeAfter(temp, newNode);
        return headNode;
       
   }
   if (option == 'o')
   {
        printf("%s - OUTPUT FULL PLAYLIST\n", playlistTitle);
        int count = 0;
        PlaylistNode* temp = headNode;
        if (temp == NULL)
        {
            printf("Playlist is empty\n\n");
        }
        while(temp != NULL)
        {
            count++;
            printf("%d.\n", count);
            PrintPlaylistNode(temp);
            temp = temp->nextNodePtr;
        }
   }
   if (option == 'r')
   {
       char checkID[100];
       PlaylistNode* current = headNode;
       PlaylistNode* previous = NULL;
       printf("REMOVE SONG\n");
       printf("Enter song's unique ID:\n");
       fgets(checkID, 100, stdin);
       checkID[strlen(checkID)-1] = '\0';

       if(strcmp(current->uniqueID, checkID) == 0) // If the head is what they are removing
       {
            printf("\"%s\" removed.\n\n", current->songName);
            free(current);
            current = current->nextNodePtr;
            return current;
       }
       else
       {
            while(current != NULL)
            {
                if(strcmp(current->uniqueID, checkID) == 0)
                {
                    printf("\"%s\" removed.\n\n", current->songName);
                    previous->nextNodePtr = current->nextNodePtr;
                    free(current);
                }
                previous = current;
                current = current->nextNodePtr;
            }
        }
        return headNode;
   }
   if (option == 'c')
   {
        PlaylistNode* temp2 = headNode;
        PlaylistNode* previous = NULL;
        PlaylistNode* newPrevious = NULL;
        PlaylistNode* positionNew = NULL;
        PlaylistNode* temp3;
        int numSongs = 0;
        int currentPosition = 0;
        int newPosition = 0;
        int count = 0;
        numSongs = length(headNode);
        printf("CHANGE POSITION OF SONG\n");
        printf("Enter song's current position:\n");
        scanf("%d", &currentPosition);
        printf("Enter new position for song:\n");
        scanf("%d", &newPosition);

        if (newPosition < 1) // Want to place it as the header
        {
           while(temp2 != NULL) // Finds the position of the node that we want to switch
           {
                count++;
                if (count == currentPosition)
                {
                    break;
                }
                temp2 = temp2->nextNodePtr;
           }
           printf("\"%s\" moved to position %d\n", temp2->songName, newPosition);
           temp3->nextNodePtr = temp2->nextNodePtr;
           temp2->nextNodePtr = headNode;
           headNode->nextNodePtr = temp3->nextNodePtr;
           headNode = temp2;
        }
        else if (newPosition > numSongs) // Want to place it as the tail
        {
           while(temp2 != NULL) // Finds the position of the node that we want to switch
           {
                count++;
                if (count == currentPosition)
                {
                    temp3 = temp2; // Temp 3 is the node we're switching
                    break;
                }
                previous = temp2;
                temp2 = temp2->nextNodePtr; // Temp 2 is the tail
           }
           printf("\"%s\" moved to position %d\n", temp3->songName, newPosition);
           previous->nextNodePtr = temp3->nextNodePtr;
           while(temp2->nextNodePtr != NULL)
           {
            temp2 = temp2->nextNodePtr;
           }
           previous->nextNodePtr = temp3->nextNodePtr;
           temp2->nextNodePtr = temp3;
           temp3->nextNodePtr = NULL;
        }
        else if (currentPosition == 1)
        {
            printf("\"%s\" moved to position %d\n\n", headNode->songName, newPosition);
            PlaylistNode* firstNode = headNode;
            headNode = headNode->nextNodePtr;
            PlaylistNode* traverse = headNode;
            PlaylistNode* newAfter = NULL;
            while (traverse != NULL)
            {
                count++;
                if (count+1 == newPosition)
                {
                    newPrevious = traverse;
                }
                if (count-1 == newPosition)
                {
                    positionNew = traverse;
                }
                traverse = traverse->nextNodePtr;
            }
            newAfter = newPrevious->nextNodePtr;

            newPrevious->nextNodePtr = firstNode;
            firstNode->nextNodePtr = newAfter;
            // printf("New Position ID: %s\n", positionNew->uniqueID);
            // printf("Previous of New Position ID: %s\n", newPrevious->uniqueID);
            // printf("Next of New Position ID: %s\n", positionNew->nextNodePtr->uniqueID);
            // printf("First Node ID: %s\n", temp3->uniqueID);
            return headNode;
        }
        else if (newPosition == 1)
        {
            PlaylistNode* traverse = headNode;
            PlaylistNode* positionOld = NULL;
            while (traverse != NULL)
            {
                count++;
                if (count == newPosition)
                {
                    positionOld = traverse;
                }
                if (count+1 == currentPosition)
                {
                    newPrevious= traverse; // Position we want to switch it too
                }
                if (count == currentPosition)
                {
                    positionNew = traverse;
                }
                traverse = traverse->nextNodePtr;
            }
            printf("\"%s\" moved to position %d\n\n", positionOld->songName, newPosition);
            // printf("Previous of Current Position ID: %s\n", newPrevious->uniqueID); // Should be 3 
            // printf("Next of Current Position ID: %s\n", positionNew->nextNodePtr->uniqueID); // Should be 5
            // printf("Next of Current Position ID: %s\n", positionNew->nextNodePtr->uniqueID);
            newPrevious->nextNodePtr = positionNew->nextNodePtr;
            positionNew->nextNodePtr = positionOld;
            headNode = positionNew;

        }
        else if(currentPosition < newPosition)
        {
            PlaylistNode* traverse = headNode;
            PlaylistNode* previousCur;
            PlaylistNode* current;
            PlaylistNode* newpos;
            PlaylistNode* newposbefore;
            PlaylistNode* newposafter;
            while (traverse != NULL)
            {
                count++;
                if (count+1 == currentPosition)
                {
                    previousCur = traverse;
                }
                if (count == currentPosition)
                {
                    current = traverse;
                }
                if (count == newPosition)
                {
                    newpos = traverse;
                }
                traverse = traverse->nextNodePtr;
            }
            previousCur->nextNodePtr = current->nextNodePtr;
            current->nextNodePtr = newpos->nextNodePtr;
            newpos->nextNodePtr = current;

        }
        else
        {
            PlaylistNode* traverse = headNode;
            PlaylistNode* previousCur;
            PlaylistNode* current;
            PlaylistNode* newpos;
            PlaylistNode* newposbefore;
            PlaylistNode* newposafter;
            while (traverse != NULL)
            {
                count++;
                if (count+1 == currentPosition)
                {
                    previousCur = traverse;
                }
                if (count == currentPosition)
                {
                    current = traverse;
                }
                if (count+1 == newPosition)
                {
                    newposbefore = traverse;
                }
                if (count == newPosition)
                {
                    newpos = traverse;
                }

                traverse = traverse->nextNodePtr;
            }
            printf("\"%s\" moved to position %d\n\n", current->songName, newPosition);
            previousCur->nextNodePtr = current->nextNodePtr;
            newposbefore->nextNodePtr = current;
            current->nextNodePtr = newpos;

            return headNode;
        }
   }

   if (option == 's')
   {
        PlaylistNode* temp = headNode;
        char userChoice[100];
        int count = 0;
        printf("\nOUTPUT SONGS BY SPECIFIC ARTIST\n");
        printf("Enter artist's name:");
        fgets(userChoice, 100, stdin);
        userChoice[strlen(userChoice)-1] = '\0';

        while(temp!=NULL)
        {
            count++;
            if(strcmp(temp->artistName, userChoice) == 0)
            {
                printf("\n%d.\n", count);
                printf("Unique ID: %s\n", temp->uniqueID);
                printf("Song Name: %s\n", temp->songName);
                printf("Artist Name: %s\n", temp->artistName);
                printf("Song Length (in seconds): %d\n", temp->songLength);
            }
            temp = temp->nextNodePtr;
        }
        printf("\n");
        
   }
   if (option == 't')
   {
        int total = 0;
        PlaylistNode* temp = headNode;
        printf("\nOUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)\n");
        while (temp != NULL)
        {
            total += temp->songLength;
            temp = temp->nextNodePtr;
        }
        printf("Total time: %d seconds\n\n", total);
   }
   
   return headNode;
}

int main(void) {
    
    char playlistTitle[100];
    printf("Enter playlist's title:\n\n");
    fgets(playlistTitle, 100, stdin);
    playlistTitle[strlen(playlistTitle)-1] = '\0';
    
    PlaylistNode* headNode = NULL;
    
    int keepGoing = 0;
    char userOption = ' ';
    
    while(keepGoing == 0)
    {
        PrintMenu(playlistTitle);
        printf("Choose an option:\n");
        scanf(" %c%*c", &userOption);
        switch(userOption)
        {
            case 'a': // Add song
                headNode = ExecuteMenu('a', playlistTitle, headNode);
                break;
            case 'r': // Remove song
                headNode = ExecuteMenu('r', playlistTitle, headNode);
                break;
            case 'c': // Change position of song
                headNode = ExecuteMenu('c', playlistTitle, headNode);
                break;
            case 's': // Output songs by specific artist
                headNode = ExecuteMenu('s', playlistTitle, headNode);
                break;
            case 't': // Output total time of playlist (in seconds)
                headNode = ExecuteMenu('t', playlistTitle, headNode);
                break;
            case 'o': // Output full playlist
                headNode = ExecuteMenu('o', playlistTitle, headNode);
                break;
            case 'q': // Quit
                keepGoing = 1;
                break;
        }
    }
   
    return 0;
}