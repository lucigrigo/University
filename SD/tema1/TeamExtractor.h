#ifndef TEAM_EXTRACTOR_H_D
#define TEAM_EXTRACTOR_H_D

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FootballClub.h"

Player *union_teams(FootballClub *clubs, char *club_A, char *club_B)
{
	FootballClub *clubDummy = (FootballClub *) malloc(sizeof(FootballClub));
	addFirstClub(&clubDummy, "club_dummy", 0);
	FootballClub *clubPtr = clubs;
	while(clubPtr != NULL){
		if(strcmp(clubPtr -> name, club_A) == 0) {
			Player *playerPtr = clubPtr -> players;
			while(playerPtr != NULL){
				add_player(clubDummy, "club_dummy", playerPtr -> name,
						playerPtr -> position, playerPtr -> score);
				playerPtr = playerPtr->next;
			}
		}
		if(strcmp(clubPtr -> name, club_B) == 0) {
			Player *playerPtr = clubPtr -> players;
			while(playerPtr != NULL){
				add_player(clubDummy, "club_dummy", playerPtr -> name,
						playerPtr -> position, playerPtr -> score);
				playerPtr = playerPtr->next;
			}
		}
		clubPtr = clubPtr -> next;
	}
	sortPlayers(&clubDummy, "club_dummy");
	Player *playerListPtr = clubDummy -> players;
	free(clubDummy);
	return playerListPtr;
}

Player *get_best_player(FootballClub *clubs, char *position)
{
	Player *bestPlayer = (Player *)malloc(sizeof(Player)), *playerPtr = NULL;
	bestPlayer->next = NULL;
	bestPlayer->prev = NULL;
	bestPlayer->injured = 0;
	bestPlayer->score = -100;
	bestPlayer->position = position;
	bestPlayer->name = (char *)malloc(20);
	FootballClub *clubPtr = clubs;
	int found = 0;
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
					found = 1;
					if (strcmp("", bestPlayer->name) == 0)
					{
						strcpy(bestPlayer->name, playerPtr->name);
						bestPlayer->score = playerPtr->score;
					}
					else if(bestPlayer -> score < playerPtr -> score) {
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
	if(found == 0) {
		return NULL;
	}
	return bestPlayer;
}

Player *get_top_players(FootballClub *clubs, int N)
{
	FootballClub *clubDummy = (FootballClub *) malloc(sizeof(FootballClub));
	addFirstClub(&clubDummy, "club_dummy", 0);
	FootballClub *clubPtr = clubs;
	while(clubPtr != NULL){
		if(clubPtr -> players != NULL) {
			sortByScore(clubPtr->players);
			sortByName(clubPtr->players);
			int i = 0;
			Player *playerPtr = clubPtr-> players;
			while((i < N) && (playerPtr != NULL)) {
				add_player(clubDummy, "club_dummy", playerPtr -> name,
						playerPtr -> position, playerPtr -> score);
				i++;
				playerPtr = playerPtr -> next;
			}
			sortPlayers(&clubs, clubPtr -> name);
		}
		clubPtr = clubPtr -> next;
	}
	sortByScore(clubDummy -> players);
	sortByName(clubDummy -> players);
	Player *playerListPtr = clubDummy -> players;
	free(clubDummy);
	return playerListPtr;
}

Player *get_players_by_score(FootballClub *clubs, int score)
{
	FootballClub *clubDummy = (FootballClub *) malloc(sizeof(FootballClub));
	addFirstClub(&clubDummy, "club_dummy", 0);
	FootballClub *clubPtr = clubs;
	Player *playerPtr = NULL;
	while(clubPtr != NULL){
		if(clubPtr -> players != NULL){
				playerPtr = clubPtr -> players;
				while(playerPtr != NULL){
					if(playerPtr -> score >= score) {
						add_player(clubDummy, "club_dummy", playerPtr -> name,
								playerPtr -> position, playerPtr -> score);
					}
					playerPtr = playerPtr -> next;
				}
			}
			if(clubPtr->injured_players != NULL) {
				playerPtr = clubPtr -> injured_players;
				while(playerPtr != NULL){
					if(playerPtr -> score >= score) {
						add_player(clubDummy, "club_dummy", playerPtr -> name,
								playerPtr -> position, playerPtr -> score);
						updateStatus(&clubDummy->players, playerPtr->name,
							playerPtr->injured);
					}
					playerPtr = playerPtr->next;
				}
			}
			clubPtr = clubPtr -> next;
		}
	sortByScore(clubDummy -> players);
	sortByName(clubDummy -> players);
	Player *playerListPtr = clubDummy -> players;
	free(clubDummy->name);
	free(clubDummy);
	playerPtr = playerListPtr;
	return playerListPtr;
}

Player *get_players_by_position(FootballClub *clubs, char *position)
{
	FootballClub *clubDummy = (FootballClub *) malloc(sizeof(FootballClub));
	addFirstClub(&clubDummy, "club_dummy", 0);
	FootballClub *clubPtr = clubs;
	Player *playerPtr = NULL;
	while(clubPtr != NULL){
		if(clubPtr -> players != NULL){
				playerPtr = clubPtr -> players;
				while(playerPtr != NULL){
					if(strcmp(playerPtr ->position, position) == 0) {
						add_player(clubDummy, "club_dummy", playerPtr -> name,
								playerPtr -> position, playerPtr -> score);
					}
					playerPtr = playerPtr -> next;
				}
		}
		if(clubPtr->injured_players != NULL) {
			playerPtr = clubPtr -> injured_players;
			while(playerPtr != NULL){
				if(strcmp(playerPtr ->position, position) == 0) {
					add_player(clubDummy, "club_dummy", playerPtr -> name,
							playerPtr -> position, playerPtr -> score);
					updateStatus(&clubDummy->players, playerPtr->name,
						playerPtr->injured);
				}
				playerPtr = playerPtr->next;
			}
		}
		clubPtr = clubPtr -> next;
	}
	sortByScore(clubDummy -> players);
	sortByName(clubDummy -> players);
	Player *playerListPtr = clubDummy -> players;
	free(clubDummy);
	return playerListPtr;
}

Player *get_best_team(FootballClub *clubs)
{
	FootballClub *clubDummy = (FootballClub*) malloc(sizeof(FootballClub)), *clubPtr = clubs;
	Player *playerPtr;
	addFirstClub(&clubDummy, "club_dummy", 0);
	while(clubPtr != NULL) {
		if(clubPtr -> players != NULL) {
			playerPtr = clubPtr -> players;
			while(playerPtr != NULL){
				add_player(clubDummy, "club_dummy", playerPtr -> name,
						playerPtr -> position, playerPtr -> score);
				playerPtr = playerPtr->next;
			}
		}
		if(clubPtr->injured_players != NULL) {
			playerPtr = clubPtr -> injured_players;
			while(playerPtr != NULL){
				add_player(clubDummy, "club_dummy", playerPtr -> name,
						playerPtr -> position, playerPtr -> score);
				updateStatus(&clubDummy->players, playerPtr->name,
					playerPtr->injured);
				playerPtr = playerPtr->next;
			}
		}
		clubPtr = clubPtr -> next;
	}
	int i = 0;
	sortPlayers(&clubDummy, "club_dummy");
	playerPtr = clubDummy->players;
	add_club(clubDummy, "second_club_dummy");
	while((i < 3) && playerPtr != NULL && (strcmp(playerPtr -> position, "atacant") == 0)) {
		add_player(clubDummy, "second_club_dummy", playerPtr -> name,
				playerPtr -> position, playerPtr -> score);
		if(playerPtr->injured) {
			updateStatus(&clubDummy->next->players, playerPtr->name,
				playerPtr->injured);
		}
		i++;
		playerPtr = playerPtr -> next;
	}
	while(playerPtr != NULL && strcmp(playerPtr->position, "fundas")) {
		playerPtr = playerPtr -> next;
	}
	i = 0;
	while((i < 4) && (playerPtr != NULL) && (strcmp(playerPtr -> position, "fundas") == 0)) {
		add_player(clubDummy, "second_club_dummy", playerPtr -> name,
				playerPtr -> position, playerPtr -> score);
		if(playerPtr->injured) {
			updateStatus(&clubDummy->next->players, playerPtr->name,
				playerPtr->injured);
		}
		i++;
		playerPtr = playerPtr -> next;
	}
	while(playerPtr != NULL && strcmp(playerPtr->position, "mijlocas")) {
		playerPtr = playerPtr -> next;
	}
	i = 0;
	while((i < 3) && playerPtr != NULL && (strcmp(playerPtr -> position, "mijlocas") == 0)) {
		add_player(clubDummy, "second_club_dummy", playerPtr -> name,
				playerPtr -> position, playerPtr -> score);
		if(playerPtr->injured) {
			updateStatus(&clubDummy->next->players, playerPtr->name,
				playerPtr->injured);
		}
		i++;
		playerPtr = playerPtr -> next;
	}
	while(playerPtr != NULL && strcmp(playerPtr->position, "portar") != 0) {
		playerPtr = playerPtr -> next;
	}
	if(playerPtr != NULL){
		add_player(clubDummy, "second_club_dummy", playerPtr -> name,
				playerPtr -> position, playerPtr -> score);
		if(playerPtr->injured) {
			updateStatus(&clubDummy->next->players, playerPtr->name,
				playerPtr->injured);
		}
	}
	sortByScore(clubDummy->next->players);
	sortByName(clubDummy->next->players);
	destroy_player_list(clubDummy->players);
	clubPtr = clubDummy -> next;
	free(clubDummy);
	playerPtr = clubPtr -> players;
	free(clubPtr);
	return playerPtr;
}

#endif // TEAM_EXTRACTOR_H_INCLUDED
