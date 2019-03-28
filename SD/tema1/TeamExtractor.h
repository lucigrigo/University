#ifndef TEAM_EXTRACTOR_H_D
#define TEAM_EXTRACTOR_H_D

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FootballClub.h"

Player *union_teams(FootballClub *clubs, char *club_A, char *club_B)
{
	Player *playersList = NULL;
	FootballClub *clubPtr = clubs;
	while ((clubPtr != NULL) && (strcmp(clubPtr->name, club_A)))
	{
		clubPtr = clubPtr->next;
	}
	if (clubPtr != NULL)
	{
		playersList = clubPtr->players;
	}
	clubPtr = clubs;
	while ((clubPtr != NULL) && (strcmp(clubPtr->name, club_B)))
	{
		clubPtr = clubPtr->next;
	}
	if (clubPtr == NULL)
	{
		return playersList;
	}
	Player *playerPtr = clubPtr->players;
	if (playerPtr == NULL)
	{
		return playersList;
	}
	while (playerPtr->next != NULL)
	{
		playerPtr = playerPtr->next;
	}
	playerPtr->next = playersList;
	playersList = clubPtr->players;
	sortByAllPositions(playersList);
	sortByOnePosition(playersList, "atacant");
	sortByOnePosition(playersList, "fundas");
	sortByOnePosition(playersList, "mijlocas");
	sortByOnePosition(playersList, "portar");
	playerPtr = playersList;
	return playersList;
}

Player *get_best_player(FootballClub *clubs, char *position)
{
	Player *bestPlayer = (Player *)malloc(sizeof(Player)), *playerPtr = NULL;
	bestPlayer->next = NULL;
	bestPlayer->prev = NULL;
	bestPlayer->injured = 0;
	bestPlayer->score = 0;
	bestPlayer->position = position;
	bestPlayer->name = (char *)malloc(20);
	FootballClub *clubPtr = clubs;
	while (clubPtr != NULL)
	{
		if (clubPtr->players != NULL)
		{
			playerPtr = clubPtr->players;
			while (playerPtr != NULL)
			{
				if ((strcmp(position, playerPtr->position) == 0) &&
					(bestPlayer->score <= playerPtr->score))
				{
					if (strcmp("\0", bestPlayer->name) == 0)
					{
						strcpy(bestPlayer->name, playerPtr->name);
						bestPlayer->score = playerPtr->score;
					}
					else if (strcmp(bestPlayer->name, playerPtr->name) > 0)
					{
						strcpy(bestPlayer->name, playerPtr->name);
						bestPlayer->score = playerPtr->score;
					}
				}
				playerPtr = playerPtr->next;
			}
		}
		clubPtr = clubPtr->next;
	}

	bestPlayer->next = NULL;
	bestPlayer->prev = NULL;
	return bestPlayer;
}

Player *get_top_players(FootballClub *clubs, int N)
{
	Player *playersList = NULL;
	FootballClub *clubPtr = clubs;
	while (clubPtr != NULL)
	{
		if (clubPtr->players != NULL)
		{
			// addPlayersToList(&playersList, )
		}
		clubPtr = clubPtr->next;
	}
	return playersList;
}

Player *get_players_by_score(FootballClub *clubs, int score)
{
	return NULL;
}

Player *get_players_by_position(FootballClub *clubs, char *position)
{
	return NULL;
}

Player *get_best_team(FootballClub *clubs)
{
	return NULL;
}

#endif // TEAM_EXTRACTOR_H_INCLUDED