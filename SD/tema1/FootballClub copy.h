#ifndef FOOTBALL_CLUB_H_D
#define FOOTBALL_CLUB_H_D

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) (a) > (b) ? (a) : (b)
#define min(a, b) (a) < (b) ? (a) : (b)

// List node which contains information about one football player.
typedef struct Player
{
	char *name;			 // player's name
	char *position;		 // player's game position
	int score;			 // player's score
	int injured;		 // indicator for injury (1 true, 0 false)
	struct Player *next; // next list node
	struct Player *prev; // previous list node
} Player;

// Structure which contains information about one football club.
typedef struct FootballClub
{
	char *name;				   // club's name
	Player *players;		   // list with players in good shape
	Player *injured_players;   // list with injured players
	struct FootballClub *next; // next list node
} FootballClub;

void addFirstClub(FootballClub **clubs, char *clubName, int moreThanOneClub)
{
	(*clubs)->name = (char *)malloc(sizeof(char) * (strlen(clubName) + 1));
	// (*clubs)->name = clubName;
	memcpy((*clubs) -> name, clubName, strlen(clubName) + 1);
	(*clubs)->players = NULL;
	(*clubs)->injured_players = NULL;
	if (moreThanOneClub == 1)
	{
		(*clubs)->next = (FootballClub *)malloc(sizeof(FootballClub));
	}
	else
	{
		(*clubs)->next = NULL;
	}
}

FootballClub *initialize_clubs(int clubs_no, char **names)
{
	FootballClub *list = (FootballClub *)malloc(clubs_no * sizeof(FootballClub));
	if (list == NULL)
	{
		exit(1);
	}
	if(names == NULL){
		list -> next = NULL;
		list -> players = NULL;
		list -> injured_players = NULL;
		list -> name = NULL;
		return list;
	}
	int moreThanOneClub = (clubs_no > 1);
	addFirstClub(&list, names[0], moreThanOneClub);
	if (moreThanOneClub == 0)
	{
		return list;
	}
	FootballClub *club = list->next;
	int i = 1;
	while (i < clubs_no)
	{
		club->name = (char *)malloc(sizeof(char) * (strlen(names[i]) + 1));
		memcpy(club->name, names[i], strlen(names[i]) + 1);
		club->players = NULL;
		club->injured_players = NULL;
		if (i == (clubs_no - 1))
		{
			club->next = NULL;
			break;
		}
		club->next = (FootballClub *)malloc(sizeof(FootballClub));
		club = club->next;
		i++;
	}
	return list;
}

FootballClub *add_club(FootballClub *clubs, char *name)
{
	FootballClub *clubPtr = clubs;
	if(clubPtr -> name == NULL) {
		addFirstClub(&clubs, name, 0);
		return clubs;
	}
	while (clubPtr->next != NULL)
	{
		clubPtr = clubPtr->next;
	}
	FootballClub *newClub = (FootballClub*) calloc(sizeof(FootballClub),1);
	newClub -> name = (char*) calloc((strlen(name) + 1), sizeof(char));
	strcpy(newClub->name, name);
	newClub -> players = NULL;
	newClub -> injured_players = NULL;
	clubPtr -> next = newClub;
	newClub -> next = NULL;
	return clubs;
}

void swapPlayers(Player *player1, Player *player2)
{
	char *tempChar = player1->name;
	player1->name = player2->name;
	player2->name = tempChar;
	tempChar = player1->position;
	player1->position = player2->position;
	player2->position = tempChar;
	int tempInt = player1->score;
	player1->score = player2->score;
	player2->score = tempInt;
	tempInt = player1->injured;
	player1->injured = player2->injured;
	player2->injured = tempInt;
}

void sortByAllPositions(Player *playersList)
{
	Player *playerPtr = playersList, *playerPtrTwo = NULL;
	while (playerPtr != NULL)
	{
		playerPtrTwo = playerPtr;
		while (playerPtrTwo->next != NULL)
		{
			if (strcmp(playerPtrTwo->position, playerPtrTwo->next->position) > 0)
			{
				swapPlayers(playerPtrTwo, playerPtrTwo->next);
			}
			playerPtrTwo = playerPtrTwo->next;
		}
		playerPtr = playerPtr->next;
	}
}

void sortByScore(Player *playersList)
{
	Player *playerPtr = playersList, *playerPtrTwo = NULL;
	while (playerPtr != NULL)
	{
		playerPtrTwo = playerPtr;
		while (playerPtrTwo != NULL)
		{
			if (playerPtr->score < playerPtrTwo->score)
			{
				swapPlayers(playerPtr, playerPtrTwo);
			}
			playerPtrTwo = playerPtrTwo->next;
		}
		playerPtr = playerPtr->next;
	}
}

void sortByOnePosition(Player *playersList, char *position)
{
	// sortare dupa scorul pe fiecare pozitie (descrescator)
	Player *playerPtr = playersList, *playerPtrTwo = NULL;
	while (playerPtr != NULL)
	{
		if (strcmp(playerPtr->position, position) == 0)
		{
			playerPtrTwo = playerPtr;
			while (playerPtrTwo->next != NULL)
			{
				if (strcmp(playerPtrTwo->position, position) != 0)
				{
					break;
				}
				if (playerPtr->score < playerPtrTwo->score)
				{
					swapPlayers(playerPtr, playerPtrTwo);
				}
				// sorteaza alfabetic jucatorii care au acelasi scor
				if ((playerPtr->score == playerPtrTwo->score) &&
					(strcmp(playerPtr->name, playerPtrTwo->name) > 0))
				{
					swapPlayers(playerPtr, playerPtrTwo);
				}
				playerPtrTwo = playerPtrTwo->next;
			}
		}
		playerPtr = playerPtr->next;
	}
}

void sortByName(Player *playersList){
	Player *playerPtr = playersList, *playerPtrTwo = NULL;
	while (playerPtr != NULL)
	{
		playerPtrTwo = playerPtr;
		while (playerPtrTwo != NULL)
		{
			if ((playerPtr->score == playerPtrTwo->score) &&
					(strcmp(playerPtr->name, playerPtrTwo->name) > 0))
			{
				swapPlayers(playerPtr, playerPtrTwo);
			}
			playerPtrTwo = playerPtrTwo->next;
		}
		playerPtr = playerPtr->next;
	}
}

void sortPlayers(FootballClub **clubsList, char *clubName)
{
	FootballClub *clubPtr = *clubsList;
	while ((clubPtr != NULL) && (strcmp(clubName, clubPtr->name)))
	{
		clubPtr = clubPtr->next;
	}
	if (clubPtr == NULL)
	{
		return;
	}
	if ((clubPtr->players == NULL) ||
		 ((clubPtr->players->next == NULL) &&
		 (clubPtr->players->prev == NULL)))
	{
		return;
	}
	sortByAllPositions(clubPtr->players);
	sortByOnePosition(clubPtr->players, "atacant");
	sortByOnePosition(clubPtr->players, "fundas");
	sortByOnePosition(clubPtr->players, "mijlocas");
	sortByOnePosition(clubPtr->players, "portar");
}

void sortInjuredPlayers(FootballClub **clubsList, char *clubName)
{
	FootballClub *clubPtr = *clubsList;
	while ((clubPtr != NULL) && (strcmp(clubName, clubPtr->name)))
	{
		clubPtr = clubPtr->next;
	}
	if (clubPtr == NULL)
	{
		return;
	}
	if ((clubPtr->injured_players == NULL) ||
		((clubPtr->injured_players->next == NULL) &&
		 (clubPtr->injured_players->prev == NULL)))
	{
		return;
	}
	Player *playerPtr = clubPtr->injured_players, *playerPtrTwo = NULL;
	// sortare dupa nume
	while (playerPtr != NULL)
	{
		playerPtrTwo = playerPtr;
		while (playerPtrTwo != NULL)
		{
			if (strcmp(playerPtr->name, playerPtrTwo->name) > 0)
			{
				swapPlayers(playerPtr, playerPtrTwo);
			}
			playerPtrTwo = playerPtrTwo->next;
		}
		playerPtr = playerPtr->next;
	}
}

void addToInjuredPlayers(FootballClub *clubsList, char *clubName, Player *playerToAdd)
{
	FootballClub *clubPtr = clubsList;
	// printf("%s\n", playerToAdd->name);
	while ((clubPtr != NULL) && (strcmp(clubName, clubPtr->name) != 0))
	{
		clubPtr = clubPtr->next;
	}
	if (clubPtr == NULL)
	{
		return;
	}
	Player *playerPtr = clubPtr->injured_players;
	if (playerPtr == NULL)
	{
		clubPtr->injured_players = playerToAdd;
		playerToAdd->next = NULL;
		playerToAdd->prev = NULL;
		sortInjuredPlayers(&clubsList, clubName);
		return;
	}
	while (playerPtr->next != NULL)
	{
		playerPtr = playerPtr->next;
	}
	playerPtr->next = playerToAdd;
	playerToAdd->next = NULL;
	playerToAdd->prev = playerPtr;
	sortInjuredPlayers(&clubsList, clubName);
}

void add_player(FootballClub *clubs, char *club_name,
				char *player_name, char *position, int score)
{
	FootballClub *clubPtr = clubs;
	while ((clubPtr != NULL) && (strcmp(club_name, clubPtr->name) != 0))
	{
		clubPtr = clubPtr->next;
	}
	if (clubPtr == NULL)
	{
		return;
	}
	if (clubPtr->players == NULL)
	{
		Player *player = (Player *)malloc(sizeof(Player));
		player->name = (char*) malloc((strlen(player_name) + 1) * sizeof(char));
		strcpy(player->name,player_name);
		player->position = position;
		player->score = min(100, score);
		player->injured = 0;
		player->prev = NULL;
		player->next = NULL;
		clubPtr->players = player;
		return;
	}
	Player *playerPtr = clubPtr->players;
	while (playerPtr->next != NULL)
	{
		playerPtr = playerPtr->next;
	}
	Player *newPlayer = (Player *)malloc(sizeof(Player));
	newPlayer->name = (char*) malloc((strlen(player_name) + 1) * sizeof(char));
	strcpy(newPlayer->name, player_name);
	newPlayer->next = NULL;
	newPlayer->position = position;
	newPlayer -> score = min(100, score);
	newPlayer -> injured = 0;
	newPlayer -> prev = playerPtr;
	playerPtr -> next = newPlayer;
	sortPlayers(&clubs, club_name);
}

void transfer_player(FootballClub *clubs, char *player_name,
					 char *old_club, char *new_club)
{
	FootballClub *clubPtr = clubs;
	while ((clubPtr != NULL) && (strcmp(old_club, clubPtr->name)))
	{
		clubPtr = clubPtr->next;
	}
	if (clubPtr == NULL)
	{
		return;
	}
	Player *playerPtr = clubPtr->players;
	while ((playerPtr != NULL) && (strcmp(player_name, playerPtr->name) != 0))
	{
		playerPtr = playerPtr->next;
	}
	if (playerPtr == NULL)
	{
		playerPtr = clubPtr -> injured_players;
		while ((playerPtr != NULL) && (strcmp(player_name, playerPtr->name) != 0))
		{
			playerPtr = playerPtr->next;
		}
		if(playerPtr == NULL){
			return;
		}
	}
	if ((playerPtr->prev == NULL) && (playerPtr->next == NULL))
	{
		if(playerPtr -> injured == 0) {
			clubPtr->players = NULL;
		} else if (playerPtr -> injured == 1){
			clubPtr->injured_players = NULL;
		}
	}
	else if ((playerPtr->prev == NULL) && (playerPtr -> next != NULL))
	{
		if(playerPtr -> injured == 0) {
			clubPtr->players = playerPtr->next;
			clubPtr->players->prev = NULL;
		} else {
			clubPtr->injured_players = playerPtr -> next;
			clubPtr -> injured_players -> prev = NULL;
		}
	}
	else if ((playerPtr->next == NULL) && (playerPtr -> prev != NULL))
	{
		playerPtr->prev->next = NULL;
	}
	else
	{
		playerPtr->next->prev = playerPtr->prev;
		playerPtr->prev->next = playerPtr->next;
	}
	playerPtr -> next = NULL;
	playerPtr->prev = NULL;
	if(playerPtr -> injured == 1) {
		addToInjuredPlayers(clubs, new_club, playerPtr);
		return;
	}
	clubPtr = clubs;
	while ((clubPtr != NULL) && (strcmp(new_club, clubPtr->name) != 0))
	{
		clubPtr = clubPtr->next;
	}
	if (clubPtr == NULL)
	{
		return;
	}
	Player *playerPtrTwo = clubPtr->players;
	if (playerPtrTwo == NULL)
	{
		clubPtr->players = playerPtr;
		playerPtr->next = NULL;
		return;
	}
	while (playerPtrTwo->next != NULL)
	{
		playerPtrTwo = playerPtrTwo->next;
	}
	playerPtrTwo -> next = playerPtr;
	playerPtr -> prev = playerPtrTwo;
	sortPlayers(&clubs, new_club);
}

void remove_player(FootballClub *clubs, char *club_name, char *player_name)
{
	FootballClub *clubPtr = clubs;
	while ((clubPtr != NULL) && (strcmp(club_name, clubPtr->name)))
	{
		clubPtr = clubPtr->next;
	}
	if (clubPtr == NULL)
	{
		return;
	}
	Player *playerPtr = clubPtr->players;
	while ((playerPtr != NULL) && (strcmp(player_name, playerPtr->name)))
	{
		playerPtr = playerPtr->next;
	}
	if (playerPtr == NULL)
	{
		playerPtr = clubPtr->injured_players;
		while ((playerPtr != NULL) && (strcmp(player_name, playerPtr->name)))
		{
			playerPtr = playerPtr->next;
		}
		if (playerPtr == NULL)
		{
			return;
		}
	}
	if ((playerPtr->prev == NULL) && (playerPtr->next == NULL))
	{
		if (clubPtr->players == playerPtr)
		{
			clubPtr->players = NULL;
		}
		else
		{
			clubPtr->injured_players = NULL;
		}
	}
	else if (playerPtr->prev == NULL)
	{
		if (clubPtr->players == playerPtr)
		{
			clubPtr->players = playerPtr->next;
			clubPtr->players->prev = NULL;
		}
		else
		{
			clubPtr->injured_players = playerPtr->next;
			clubPtr->injured_players->prev = NULL;
		}
	}
	else if (playerPtr->next == NULL)
	{
		playerPtr->prev->next = NULL;
	}
	else
	{
		playerPtr->next->prev = playerPtr->prev;
		playerPtr->prev->next = playerPtr->next;
	}
	// free(playerPtr->name);
	free(playerPtr);
	sortPlayers(&clubs, club_name);
}

void update_score(FootballClub *clubs, char *club_name,
				  char *player_name, int score)
{
	FootballClub *clubPtr = clubs;
	while ((clubPtr != NULL) && (strcmp(club_name, clubPtr->name)))
	{
		clubPtr = clubPtr->next;
	}
	if (clubPtr == NULL)
	{
		return;
	}
	Player *playerPtr = clubPtr->players;
	while ((playerPtr != NULL) && (strcmp(player_name, playerPtr->name)))
	{
		playerPtr = playerPtr->next;
	}
	if (playerPtr == NULL)
	{
		playerPtr = clubPtr -> injured_players;
		while ((playerPtr != NULL) && (strcmp(player_name, playerPtr->name)))
		{
			playerPtr = playerPtr->next;
		}
		if(playerPtr == NULL){
			return;
		}
	}
	playerPtr->score = score;
	sortPlayers(&clubs, club_name);
	sortInjuredPlayers(&clubs, club_name);
}

void updateStatus(Player **list, char *playerName, int status) {
	Player *playerPtr = *list;
	while((playerPtr != NULL) && (strcmp(playerPtr->name, playerName) != 0)){
		playerPtr = playerPtr -> next;
	}
	if(playerPtr == NULL){
			return;
	}
	playerPtr -> injured = status;
}

void update_game_position(FootballClub *clubs, char *club_name,
						  char *player_name, char *position, int score)
{
	FootballClub *clubPtr = clubs;
	while ((clubPtr != NULL) && (strcmp(club_name, clubPtr->name)))
	{
		clubPtr = clubPtr->next;
	}
	if (clubPtr == NULL)
	{
		return;
	}
	Player *playerPtr = clubPtr->players;
	while ((playerPtr != NULL) && (strcmp(player_name, playerPtr->name)))
	{
		playerPtr = playerPtr->next;
	}
	if (playerPtr == NULL)
	{
		playerPtr = clubPtr -> injured_players;
		while ((playerPtr != NULL) && (strcmp(player_name, playerPtr->name)))
		{
			playerPtr = playerPtr->next;
		}
		if(playerPtr == NULL){
			return;
		}
	}
	playerPtr->position = position;
	playerPtr->score = min(100, score);
	sortPlayers(&clubs, club_name);
}

void add_injury(FootballClub *clubs, char *club_name,
				char *player_name, int days_no)
{
	FootballClub *clubPtr = clubs;
	while ((clubPtr != NULL) && (strcmp(club_name, clubPtr->name)))
	{
		clubPtr = clubPtr->next;
	}
	if (clubPtr == NULL)
	{
		return;
	}
	Player *playerPtr = clubPtr->players;
	while ((playerPtr != NULL) && (strcmp(player_name, playerPtr->name)))
	{
		playerPtr = playerPtr->next;
	}
	if (playerPtr == NULL)
	{
		return;
	}
	if ((playerPtr->prev == NULL) && (playerPtr->next == NULL))
	{
		clubPtr->players = NULL;
	}
	else if (playerPtr->prev == NULL)
	{
		clubPtr->players = playerPtr->next;
		clubPtr->players->prev = NULL;
	}
	else if (playerPtr->next == NULL)
	{
		playerPtr->prev->next = NULL;
	}
	else
	{
		playerPtr->next->prev = playerPtr->prev;
		playerPtr->prev->next = playerPtr->next;
	}
	sortPlayers(&clubs, club_name);
	playerPtr->score = max(((playerPtr->score) - ((0.1) * days_no)), -100);
	playerPtr->injured = 1;
	addToInjuredPlayers(clubs, club_name, playerPtr);
	sortInjuredPlayers(&clubs, club_name);
}

void recover_from_injury(FootballClub *clubs, char *club_name,
						 char *player_name)
{
	FootballClub *clubPtr = clubs;
	while ((clubPtr != NULL) && (strcmp(club_name, clubPtr->name)))
	{
		clubPtr = clubPtr->next;
	}
	if (clubPtr == NULL)
	{
	 	return;
	}
	Player *playerPtr = clubPtr->injured_players;
	if (playerPtr == NULL)
	{
		return;
	}
	while ((playerPtr != NULL) && (strcmp(player_name, playerPtr->name) != 0))
	{
		playerPtr = playerPtr->next;
	}
	if (playerPtr == NULL)
	{
		return;
	}
	if ((playerPtr->prev == NULL) && (playerPtr->next == NULL))
	{
		clubPtr->injured_players = NULL;
	}
	else if (playerPtr->prev == NULL)
	{
		clubPtr->injured_players = playerPtr->next;
		clubPtr->injured_players->prev = NULL;
	}
	else if (playerPtr->next == NULL)
	{
		playerPtr->prev->next = NULL;
	}
	else
	{
		playerPtr->next->prev = playerPtr->prev;
		playerPtr->prev->next = playerPtr->next;
	}
	Player *playerPtrTwo = clubPtr->players;
	playerPtr->injured = 0;
	if (playerPtrTwo == NULL)
	{
		clubPtr->players = playerPtr;
		playerPtr->next = NULL;
		return;
	}
	while (playerPtrTwo->next != NULL)
	{
		playerPtrTwo = playerPtrTwo->next;
	}
	if (playerPtrTwo == NULL)
	{
		return;
	}
	playerPtrTwo->next = playerPtr;
	playerPtr->prev = playerPtrTwo;
	playerPtr->next = NULL;
	sortPlayers(&clubs, club_name);
}

// Frees memory for a list of Player.
void destroy_player_list(Player *player)
{
	if (player == NULL)
	{
		return;
	}
	Player *playerPtr;
	while (player != NULL)
	{
		playerPtr = player->next;
		if(player->name) {
			// free(player->name);
		}
		free(player);
		player = playerPtr;
	}
}

// Frees memory for a list of FootballClub.
void destroy_club_list(FootballClub *clubs)
{
	if (clubs == NULL)
	{
		return;
	}
	if(clubs == NULL){
		destroy_player_list(clubs->players);
		destroy_player_list(clubs->injured_players);
		free(clubs->name);
		free(clubs);
		return;
	}
	FootballClub *clubPtr = clubs->next;
	while (clubs != NULL)
	{
		destroy_player_list(clubs->players);
		destroy_player_list(clubs->injured_players);
		clubPtr = clubs->next;
		free(clubs->name);
		free(clubs);
		clubs = clubPtr;
	}
}

// Displays a list of players.
void show_list(FILE *f, Player *players, int free_memory)
{
	fprintf(f, "P: ");
	Player *player = players;
	while (player)
	{
		fprintf(f, "(%s, %s, %d, %c) ",
				player->name,
				player->position,
				player->score,
				player->injured ? 'Y' : '_');
		player = player->next;
	}
	if (free_memory)
	{
		destroy_player_list(players);
	}
	fprintf(f, "\n");
}

// Displays a list of players in reverse.
void show_list_reverse(FILE *f, Player *players, int free_memory)
{
	fprintf(f, "P: ");
	Player *player = players;
	if (player)
	{
		while (player->next)
		{
			player = player->next;
		}
		while (player)
		{
			fprintf(f, "(%s, %s, %d, %c) ",
					player->name,
					player->position,
					player->score,
					player->injured ? 'Y' : '_');
			player = player->prev;
		}
	}
	if (free_memory)
	{
		destroy_player_list(players);
	}
	fprintf(f, "\n");
}

// Displays information about a football club.
void show_clubs_info(FILE *f, FootballClub *clubs)
{
	fprintf(f, "FCs:\n");
	while (clubs)
	{
		fprintf(f, "%s\n", clubs->name);
		fprintf(f, "\t");
		show_list(f, clubs->players, 0);
		fprintf(f, "\t");
		show_list(f, clubs->injured_players, 0);
		clubs = clubs->next;
	}
}

#endif // FOOTBALL_CLUB_H_INCLUDED
