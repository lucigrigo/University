							// CURS: STRUCTURI DE DATE 
							// 		TEMA 1
							// GRIGORE LUCIAN-FLORIN
							// 		314CD

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


//  Functia addFirstClub() adauga primul club dintr-o lista de cluburi
void addFirstClub(FootballClub **clubs, char *clubName, int moreThanOneClub)
{
	(*clubs)->name = (char *)malloc(sizeof(char) * (strlen(clubName) + 1));
	if((*clubs)->name == NULL) exit(1);
	strcpy((*clubs)->name, clubName);
	(*clubs)->players = NULL;
	(*clubs)->injured_players = NULL;
	if (moreThanOneClub == 1)
	{
		(*clubs)->next = (FootballClub *)malloc(sizeof(FootballClub));
		if((*clubs) -> next == NULL) exit(1);
	}
	else
	{
		(*clubs)->next = NULL;
	}
}

//	Functia initializeaza o lista de cluburi
FootballClub *initialize_clubs(int clubs_no, char **names)
{
	FootballClub *list = (FootballClub *)malloc(clubs_no * sizeof(FootballClub));
	if (list == NULL) exit(1);
	// cazul in care se doreste o lista vida, fara niciun club initial
	if(names == NULL){
		list -> next = NULL;
		list -> players = NULL;
		list -> injured_players = NULL;
		list -> name = NULL;
		return list;
	}
	int moreThanOneClub = (clubs_no > 1);
	addFirstClub(&list, names[0], moreThanOneClub);
	// daca se initializeaza un singur club in lista
	if (moreThanOneClub == 0)
	{
		return list;
	}
	FootballClub *club = list->next;
	int i = 1;
	// initializarea celorlalte cluburi, daca este cazul
	while (i < clubs_no)
	{
		club->name = (char *)malloc(sizeof(char) * (strlen(names[i]) + 1));
		if(club->name == NULL) exit(1);
		memcpy(club->name, names[i], strlen(names[i]) + 1);
		club->players = NULL;
		club->injured_players = NULL;
		if (i == (clubs_no - 1))
		{
			club->next = NULL;
			break;
		}
		club->next = (FootballClub *)malloc(sizeof(FootballClub));
		if(club->next == NULL) exit(1);
		club = club->next;
		i++;
	}
	return list;
}

// Functia adauga un club nou intr-o lista de cluburi
FootballClub *add_club(FootballClub *clubs, char *name)
{
	FootballClub *clubPtr = clubs;
	// cazul in care lista nu are niciun club adaugat
	if(clubPtr -> name == NULL) {
		addFirstClub(&clubs, name, 0);
		return clubs;
	}
	// parcurgerea pana la final a listei
	while (clubPtr->next != NULL)
	{
		clubPtr = clubPtr->next;
	}
	// adaugarea clubului nou
	FootballClub *newClub = (FootballClub*) malloc(sizeof(FootballClub));
	if(newClub == NULL) exit(1);
	newClub -> name = (char*) malloc((strlen(name) + 1) * sizeof(char));
	if(newClub -> name == NULL) exit(1);
	strcpy(newClub->name, name);
	newClub -> players = NULL;
	newClub -> injured_players = NULL;
	clubPtr -> next = newClub;
	newClub -> next = NULL;
	return clubs;
}

// Functia inverseaza 2 playeri (doar datele, nu si pointerii in sine)
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

// Functia sorteaza dupa pozitii o lista de playeri
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

// Functia sorteaza dupa scor o lista de playeri
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

// Functia sorteaza intr-o lista de playeri o singura pozitie:
// descrescator dupa scor si crescator lexicografic playerii cu 
// acelasi scor, daca exista
void sortByOnePosition(Player *playersList, char *position)
{
	// sortare dupa scor (descrescator)
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

// Functia sorteaza dupa nume o lista de playeri
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
// Functia sorteaza o lista de playeri dupa toate criiteriile din cerinta:
// - alfabetic dupa pozitie
// - descrescator dupa scor
// - crescator alfabetic playerii cu acelasi scor
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

// Functia sorteaza o lista de playeri accidentati dupa criteriile din cerinta
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
	// sortare dupa nume a jucatorilor
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

// Functia adauga un jucator la playerii accidentati ai unui club
void addToInjuredPlayers(FootballClub *clubsList, char *clubName, Player *playerToAdd)
{
	FootballClub *clubPtr = clubsList;
	// cautarea clubului
	while ((clubPtr != NULL) && (strcmp(clubName, clubPtr->name) != 0))
	{
		clubPtr = clubPtr->next;
	}
	// cazul in care clubul nu exista
	if (clubPtr == NULL)
	{
		return;
	}
	Player *playerPtr = clubPtr->injured_players;
	// cazul in care clubul nu are niciun jucator accidentat
	if (playerPtr == NULL)
	{
		clubPtr->injured_players = playerToAdd;
		playerToAdd->next = NULL;
		playerToAdd->prev = NULL;
		sortInjuredPlayers(&clubsList, clubName);
		return;
	}
	// parcurgerea listei de jucatori
	while (playerPtr->next != NULL)
	{
		playerPtr = playerPtr->next;
	}
	// adaugarea jucatorului
	playerPtr->next = playerToAdd;
	playerToAdd->next = NULL;
	playerToAdd->prev = playerPtr;
	sortInjuredPlayers(&clubsList, clubName);
}

// Functia adauga un jucator la un club anume
void add_player(FootballClub *clubs, char *club_name,
				char *player_name, char *position, int score)
{
	FootballClub *clubPtr = clubs;
	// cautarea clubului
	while ((clubPtr != NULL) && (strcmp(club_name, clubPtr->name) != 0))
	{
		clubPtr = clubPtr->next;
	}
	// cazul in care clubul nu exista
	if (clubPtr == NULL)
	{
		return;
	}
	// cazul in care clubul nu are jucatori momentan
	if (clubPtr->players == NULL)
	{
		Player *player = (Player *)malloc(sizeof(Player));
		if(player == NULL) exit(1);
		player->name = (char*) malloc((strlen(player_name) + 1) * sizeof(char));
		if(player -> name == NULL) exit(1);
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
	// parcurgerea pana la final a jucatorilor
	while (playerPtr->next != NULL)
	{
		playerPtr = playerPtr->next;
	}
	// adaugarea noului jucator
	Player *newPlayer = (Player *)malloc(sizeof(Player));
	if(newPlayer == NULL) exit(1);
	newPlayer->name = (char*) malloc((strlen(player_name) + 1) * sizeof(char));
	if(newPlayer ->name == NULL) exit(1);
	strcpy(newPlayer->name, player_name);
	newPlayer->next = NULL;
	newPlayer->position = position;
	newPlayer -> score = min(100, score);
	newPlayer -> injured = 0;
	newPlayer -> prev = playerPtr;
	playerPtr -> next = newPlayer;
	sortPlayers(&clubs, club_name);
}

// Functia transfera un jucator de la un club la altul
void transfer_player(FootballClub *clubs, char *player_name,
					 char *old_club, char *new_club)
{
	FootballClub *clubPtr = clubs;
	// cautarea vechiului club
	while ((clubPtr != NULL) && (strcmp(old_club, clubPtr->name)))
	{
		clubPtr = clubPtr->next;
	}
	// cazul in care vechiul club nu exista
	if (clubPtr == NULL)
	{
		return;
	}
	Player *playerPtr = clubPtr->players;
	// cautarea jucatorului printre jucatorii neaccidentati
	while ((playerPtr != NULL) &&
		   (strcmp(player_name, playerPtr->name) != 0))
	{
		playerPtr = playerPtr->next;
	}
	if (playerPtr == NULL)
	{
		playerPtr = clubPtr -> injured_players;
		// cautarea jucatorului printre cei accidentati
		while ((playerPtr != NULL) &&
			   (strcmp(player_name, playerPtr->name) != 0))
		{
			playerPtr = playerPtr->next;
		}
		// cazul in care jucatorul nu exista nici printre cei accidentati
		if(playerPtr == NULL){
			return;
		}
	}
	// cazul in care este singurul jucator
	if ((playerPtr->prev == NULL) && (playerPtr->next == NULL))
	{
		if(playerPtr -> injured == 0) {
			clubPtr->players = NULL;
		} else if (playerPtr -> injured == 1){
			clubPtr->injured_players = NULL;
		}
	}
	// cazul in care este primul din lista de jucatori
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
	// cazul in care este ultimul din lista de jucatori
	else if ((playerPtr->next == NULL) && (playerPtr -> prev != NULL))
	{
		playerPtr->prev->next = NULL;
	}
	// cazul general in care nu este nici ultimul, nici primul
	else
	{
		playerPtr->next->prev = playerPtr->prev;
		playerPtr->prev->next = playerPtr->next;
	}
	playerPtr -> next = NULL;
	playerPtr->prev = NULL;
	// cazul in care jucatorul este accidentat
	if(playerPtr -> injured == 1) {
		addToInjuredPlayers(clubs, new_club, playerPtr);
		return;
	}
	clubPtr = clubs;
	// cautarea noului club
	while ((clubPtr != NULL) && (strcmp(new_club, clubPtr->name) != 0))
	{
		clubPtr = clubPtr->next;
	}
	// cazul in care noul club nu exista
	if (clubPtr == NULL)
	{
		return;
	}
	Player *playerPtrTwo = clubPtr->players;
	// cazul in care noul club nu are jucatori momentan
	if (playerPtrTwo == NULL)
	{
		clubPtr->players = playerPtr;
		playerPtr->next = NULL;
		return;
	}
	// parcurgerea jucatorilor pana la final
	while (playerPtrTwo->next != NULL)
	{
		playerPtrTwo = playerPtrTwo->next;
	}
	playerPtrTwo -> next = playerPtr;
	playerPtr -> prev = playerPtrTwo;
	sortPlayers(&clubs, new_club);
}

// Functia elimina un jucator de la un club
void remove_player(FootballClub *clubs, char *club_name, char *player_name)
{
	FootballClub *clubPtr = clubs;
	// cautarea clubului
	while ((clubPtr != NULL) &&
	 		(strcmp(club_name, clubPtr->name)))
	{
		clubPtr = clubPtr->next;
	}
	// cazul in care clubul nu exista
	if (clubPtr == NULL)
	{
		return;
	}
	Player *playerPtr = clubPtr->players;
	// cautarea jucatorului printre cei neaccidentati
	while ((playerPtr != NULL) &&
	 		(strcmp(player_name, playerPtr->name)))
	{
		playerPtr = playerPtr->next;
	}
	if (playerPtr == NULL)
	{
		// cautarea jucatorului printre cei accidentati
		playerPtr = clubPtr->injured_players;
		while ((playerPtr != NULL) &&
		 		(strcmp(player_name, playerPtr->name)))
		{
			playerPtr = playerPtr->next;
		}
		// cazul in care jucatorul nu este gasit
		if (playerPtr == NULL)
		{
			return;
		}
	}
	// jucatorul este singurul din lista de jucatori
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
	// jucatorul este primul din lista
	else if ((playerPtr->prev == NULL) && (playerPtr->next != NULL))
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
	// jucatorul este ultimul din lista
	else if ((playerPtr->next == NULL) && (playerPtr->prev != NULL))
	{
		playerPtr->prev->next = NULL;
	}
	// jucatorul este in interiorul listei
	else
	{
		playerPtr->next->prev = playerPtr->prev;
		playerPtr->prev->next = playerPtr->next;
	}
	free(playerPtr->name);
	free(playerPtr);
	sortPlayers(&clubs, club_name);
}

// Functia reinnoieste scorul unui jucator
void update_score(FootballClub *clubs, char *club_name,
				  char *player_name, int score)
{
	FootballClub *clubPtr = clubs;
	// cautarea clubului
	while ((clubPtr != NULL) &&
			(strcmp(club_name, clubPtr->name)))
	{
		clubPtr = clubPtr->next;
	}
	// clubul nu exista
	if (clubPtr == NULL)
	{
		return;
	}
	Player *playerPtr = clubPtr->players;
	// cautarea jucatorului printre cei neaccidentati
	while ((playerPtr != NULL) &&
			(strcmp(player_name, playerPtr->name)))
	{
		playerPtr = playerPtr->next;
	}
	if (playerPtr == NULL)
	{
		playerPtr = clubPtr -> injured_players;
		// cautarea jucatorului printre cei accidentati
		while ((playerPtr != NULL) &&
				(strcmp(player_name, playerPtr->name)))
		{
			playerPtr = playerPtr->next;
		}
		// jucatorul nu exista
		if(playerPtr == NULL){
			return;
		}
	}
	// reinnoirea scorului
	playerPtr->score = score;
	sortPlayers(&clubs, club_name);
	sortInjuredPlayers(&clubs, club_name);
}

// Functia reinnoieste statusul (injured sau nu) unui jucator
void updateStatus(Player **list, char *playerName, int status) {
	Player *playerPtr = *list;
	// cautarea jucatorului
	while((playerPtr != NULL) &&
			(strcmp(playerPtr->name, playerName) != 0)){
		playerPtr = playerPtr -> next;
	}
	// jucatorul nu exista
	if(playerPtr == NULL){
			return;
	}
	playerPtr -> injured = status;
}

// Functia reinnoieste pozitia de joc si scorul unui jucator
void update_game_position(FootballClub *clubs, char *club_name,
						  char *player_name, char *position, int score)
{
	FootballClub *clubPtr = clubs;
	// cautarea clublui
	while ((clubPtr != NULL) &&
			(strcmp(club_name, clubPtr->name)))
	{
		clubPtr = clubPtr->next;
	}
	// clubul nu exista
	if (clubPtr == NULL)
	{
		return;
	}
	Player *playerPtr = clubPtr->players;
	// cautarea jucatorului printre cei neaccidentati
	while ((playerPtr != NULL) &&
			(strcmp(player_name, playerPtr->name)))
	{
		playerPtr = playerPtr->next;
	}
	if (playerPtr == NULL)
	{
		playerPtr = clubPtr -> injured_players;
		// cautarea jucatorului printre cei accidentati
		while ((playerPtr != NULL) &&
				(strcmp(player_name, playerPtr->name)))
		{
			playerPtr = playerPtr->next;
		}
		if(playerPtr == NULL){
			return;
		}
	}
	// reinnoirea datelor
	playerPtr->position = position;
	playerPtr->score = min(100, score);
	sortPlayers(&clubs, club_name);
}

// Functia trateaza o accidentare a unui jucator 
void add_injury(FootballClub *clubs, char *club_name,
				char *player_name, int days_no)
{
	FootballClub *clubPtr = clubs;
	// cautarea clubului
	while ((clubPtr != NULL) &&
			(strcmp(club_name, clubPtr->name)))
	{
		clubPtr = clubPtr->next;
	}
	// clubul nu exista
	if (clubPtr == NULL)
	{
		return;
	}
	Player *playerPtr = clubPtr->players;
	// cautarea jucatorului
	while ((playerPtr != NULL) &&
			(strcmp(player_name, playerPtr->name)))
	{
		playerPtr = playerPtr->next;
	}
	// jucatorul nu exista
	if (playerPtr == NULL)
	{
		return;
	}
	// jucatorul este singurul din lista
	if ((playerPtr->prev == NULL) && (playerPtr->next == NULL))
	{
		clubPtr->players = NULL;
	}
	// jucatorul este primul din lista
	else if ((playerPtr->prev == NULL) && (playerPtr->next != NULL))
	{
		clubPtr->players = playerPtr->next;
		clubPtr->players->prev = NULL;
	}
	// jucatorul este ultimul din lista
	else if ((playerPtr->next == NULL) && (playerPtr->prev != NULL))
	{
		playerPtr->prev->next = NULL;
	}
	// jucatorul este in interiorul listei
	else
	{
		playerPtr->next->prev = playerPtr->prev;
		playerPtr->prev->next = playerPtr->next;
	}
	sortPlayers(&clubs, club_name);
	// innoirea atributelor jucatorului
	playerPtr->score = max(((playerPtr->score) - ((0.1) * days_no)), -100);
	playerPtr->injured = 1;
	// mutarea jucatorului
	addToInjuredPlayers(clubs, club_name, playerPtr);
	// mentinerea ordinii listei de jucatori accidentati
	sortInjuredPlayers(&clubs, club_name);
}

// Functia trateaza situatia cand un jucator revine dupa o accidentare
void recover_from_injury(FootballClub *clubs, char *club_name,
						 char *player_name)
{
	FootballClub *clubPtr = clubs;
	// cautarea clubului
	while ((clubPtr != NULL) &&
			(strcmp(club_name, clubPtr->name)))
	{
		clubPtr = clubPtr->next;
	}
	// clubul nu exista
	if (clubPtr == NULL)
	{
	 	return;
	}
	Player *playerPtr = clubPtr->injured_players;
	// clubul nu are niciun jucator accidentat
	if (playerPtr == NULL)
	{
		return;
	}
	// cautarea jucatorului
	while ((playerPtr != NULL) &&
			(strcmp(player_name, playerPtr->name) != 0))
	{
		playerPtr = playerPtr->next;
	}
	// jucatorul nu exista
	if (playerPtr == NULL)
	{
		return;
	}
	// jucatorul este singurul din lista
	if ((playerPtr->prev == NULL) && (playerPtr->next == NULL))
	{
		clubPtr->injured_players = NULL;
	}
	// jucatorul este primul din lista
	else if ((playerPtr->prev == NULL) && (playerPtr->next != NULL))
	{
		clubPtr->injured_players = playerPtr->next;
		clubPtr->injured_players->prev = NULL;
	}
	// jucatorul este ultimul din lista
	else if ((playerPtr->next == NULL) && (playerPtr->prev != NULL))
	{
		playerPtr->prev->next = NULL;
	}
	// jucatorul este in interiorul listei
	else
	{
		playerPtr->next->prev = playerPtr->prev;
		playerPtr->prev->next = playerPtr->next;
	}
	Player *playerPtrTwo = clubPtr->players;
	playerPtr->injured = 0;
	// jucatorul va fi singurul jucator neaccidentat al clubului
	if (playerPtrTwo == NULL)
	{
		clubPtr->players = playerPtr;
		playerPtr->next = NULL;
		return;
	}
	// cautarea sfarsitului jucatorilor
	while (playerPtrTwo->next != NULL)
	{
		playerPtrTwo = playerPtrTwo->next;
	}
	if (playerPtrTwo == NULL)
	{
		return;
	}
	// adaugarea jucatorului la lista de jucatori neaccidentati
	playerPtrTwo->next = playerPtr;
	playerPtr->prev = playerPtrTwo;
	playerPtr->next = NULL;
	// mentinerea ordinii normale a listei de jucatori neaccidentati
	sortPlayers(&clubs, club_name);
}

// Frees memory for a list of Player.
void destroy_player_list(Player *player)
{
	// if (player == NULL)
	// 	return;
	// Player *nextPtr = player->next;
	// 	free(player->name);
	// 	free(player);
	// destroy_player_list(nextPtr);
}

// Frees memory for a list of FootballClub.
void destroy_club_list(FootballClub *clubs)
{
	// if (clubs == NULL)
	// 	return;
	// 	destroy_player_list(clubs->players);
	// 	destroy_player_list(clubs->injured_players);
	// 	free(clubs->name);
	// 	free(clubs);
	//  destroy_club_list(clubs->next);
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