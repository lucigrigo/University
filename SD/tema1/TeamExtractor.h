// 		CURS: STRUCTURI DE DATE
// 				TEMA 1
// 		GRIGORE LUCIAN-FLORIN
// 				314CD

#ifndef TEAM_EXTRACTOR_H_D
#define TEAM_EXTRACTOR_H_D

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FootballClub.h"

// Functia intoarce o lista cu jucatorii neaccidentati a doua cluburi
Player *union_teams(FootballClub *clubs, char *club_A, char *club_B) {
  // crearea unui club de test temporar, ca sa pot folosi functiile
  // de la primul task
  FootballClub *clubDummy = (FootballClub *)malloc(sizeof(FootballClub));
  if (clubDummy == NULL)
    exit(1);
  addFirstClub(clubDummy, "club_dummy", 0);
  FootballClub *clubPtr = clubs;
  // cautarea celor doua cluburi
  // daca se gaseste un club, se adauga la clubul de test toti jucatorii
  while (clubPtr != NULL) {
    if (strcmp(clubPtr->name, club_A) == 0) {
      Player *playerPtr = clubPtr->players;
      while (playerPtr != NULL) {
        add_player(clubDummy, "club_dummy", playerPtr->name,
                   playerPtr->position, playerPtr->score);
        playerPtr = playerPtr->next;
      }
    }
    if (strcmp(clubPtr->name, club_B) == 0) {
      Player *playerPtr = clubPtr->players;
      while (playerPtr != NULL) {
        add_player(clubDummy, "club_dummy", playerPtr->name,
                   playerPtr->position, playerPtr->score);
        playerPtr = playerPtr->next;
      }
    }
    clubPtr = clubPtr->next;
  }
  // sortarea jucatorilor
  sortPlayers(&clubDummy, "club_dummy");
  Player *playerListPtr = clubDummy->players;
  free(clubDummy->name);
  free(clubDummy);
  return playerListPtr;
}

// Functia intoarce cel mai bun jucator de pe o anumita pozitie
Player *get_best_player(FootballClub *clubs, char *position) {
  // crearea jucatorului
  Player *bestPlayer = (Player *)malloc(sizeof(Player)), *playerPtr = NULL;
  if (bestPlayer == NULL)
    exit(1);
  bestPlayer->next = NULL;
  bestPlayer->prev = NULL;
  bestPlayer->injured = 0;
  bestPlayer->score = -100;
  bestPlayer->position = position;
  bestPlayer->name = (char *)malloc(20);
  if (bestPlayer->name == NULL)
    exit(1);
  strcpy(bestPlayer->name, "\0");
  FootballClub *clubPtr = clubs;
  // variabila indica daca un jucator este gasit
  int found = 0;
  // parcurgerea cluburilor
  while (clubPtr != NULL) {
    if (clubPtr->players != NULL) {
      playerPtr = clubPtr->players;
      // parcurgerea playerilor unui club
      while (playerPtr != NULL) {
        // jucatorul se afla pe pozitia dorita
        if ((strcmp(position, playerPtr->position) == 0) &&
            (bestPlayer->score <= playerPtr->score)) {
          found = 1;
          // daca este primul jucator gasit
          if (strcmp("\0", bestPlayer->name) == 0) {
            strcpy(bestPlayer->name, playerPtr->name);
            bestPlayer->score = playerPtr->score;
          }
          // daca are scorul mai mare decat jucatorul curent ales
          else if (bestPlayer->score < playerPtr->score) {
            strcpy(bestPlayer->name, playerPtr->name);
            bestPlayer->score = playerPtr->score;
          }
          // daca are numele mai mic lexicografic decat al
          // jucatorului curent ales
          else if (strcmp(bestPlayer->name, playerPtr->name) > 0) {
            strcpy(bestPlayer->name, playerPtr->name);
            bestPlayer->score = playerPtr->score;
          }
        }
        playerPtr = playerPtr->next;
      }
    }
    clubPtr = clubPtr->next;
  }
  // daca niciun jucator nu este gasit
  if (found == 0) {
    return NULL;
  }
  return bestPlayer;
}

// Functia returneaza cei mai buni N jucatori de la fiecare club
// sau mai putini, daca clubul nu are destui
Player *get_top_players(FootballClub *clubs, int N) {
  // crearea unui club de test temporar, ca sa pot folosi functiile
  // de la primul task
  FootballClub *clubDummy = (FootballClub *)malloc(sizeof(FootballClub));
  if (clubDummy == NULL)
    exit(1);
  addFirstClub(clubDummy, "club_dummy", 0);
  FootballClub *clubPtr = clubs;
  // parcurgerea cluburilor
  while (clubPtr != NULL) {
    if (clubPtr->players != NULL) {
      // aranjarea jucatorilor dupa conditiile cerute (scor, nume)
      sortByScore(clubPtr->players);
      sortByName(clubPtr->players);
      int i = 0;
      Player *playerPtr = clubPtr->players;
      // parcurgerea jucatorilor
      while ((i < N) && (playerPtr != NULL)) {
        // adaugarea jucatorilor la lista temporara
        add_player(clubDummy, "club_dummy", playerPtr->name,
                   playerPtr->position, playerPtr->score);
        i++;
        playerPtr = playerPtr->next;
      }
      // restabilirea ordinii listei de jucatori
      sortPlayers(&clubs, clubPtr->name);
    }
    clubPtr = clubPtr->next;
  }
  // sortarea listei de jucatori obtinute
  sortByScore(clubDummy->players);
  sortByName(clubDummy->players);
  Player *playerListPtr = clubDummy->players;
  free(clubDummy->name);
  free(clubDummy);
  return playerListPtr;
}

// Functia returneaza toti jucatorii cu scorul cel putin egal cu un scor dat
Player *get_players_by_score(FootballClub *clubs, int score) {
  // crearea unui club de test temporar, ca sa pot folosi functiile
  // de la primul task
  FootballClub *clubDummy = (FootballClub *)malloc(sizeof(FootballClub));
  if (clubDummy == NULL)
    exit(1);
  addFirstClub(clubDummy, "club_dummy", 0);
  FootballClub *clubPtr = clubs;
  Player *playerPtr = NULL;
  // parcurgerea cluburilor
  while (clubPtr != NULL) {
    if (clubPtr->players != NULL) {
      playerPtr = clubPtr->players;
      // parcurgerea si adaugarea jucatorilor neaccidentati
      while (playerPtr != NULL) {
        if (playerPtr->score >= score) {
          add_player(clubDummy, "club_dummy", playerPtr->name,
                     playerPtr->position, playerPtr->score);
        }
        playerPtr = playerPtr->next;
      }
    }
    if (clubPtr->injured_players != NULL) {
      playerPtr = clubPtr->injured_players;
      // parcurgerea si adaugarea jucatorilor accidentati
      while (playerPtr != NULL) {
        if (playerPtr->score >= score) {
          add_player(clubDummy, "club_dummy", playerPtr->name,
                     playerPtr->position, playerPtr->score);
          updateStatus(&clubDummy->players, playerPtr->name,
                       playerPtr->injured);
        }
        playerPtr = playerPtr->next;
      }
    }
    clubPtr = clubPtr->next;
  }
  // sortarea listei de jucatori
  sortByScore(clubDummy->players);
  sortByName(clubDummy->players);
  Player *playerListPtr = clubDummy->players;
  free(clubDummy->name);
  free(clubDummy);
  return playerListPtr;
}

// Functia intoarce toti jucatorii de pe o anumita pozitie
Player *get_players_by_position(FootballClub *clubs, char *position) {
  // crearea unui club de test temporar, ca sa pot folosi functiile
  // de la primul task
  FootballClub *clubDummy = (FootballClub *)malloc(sizeof(FootballClub));
  if (clubDummy == NULL)
    exit(1);
  addFirstClub(clubDummy, "club_dummy", 0);
  FootballClub *clubPtr = clubs;
  Player *playerPtr = NULL;
  // parcurgerea cluburilor
  while (clubPtr != NULL) {
    if (clubPtr->players != NULL) {
      playerPtr = clubPtr->players;
      // parcurgerea si adaugarea jucatorilor neaccidentati
      while (playerPtr != NULL) {
        if (strcmp(playerPtr->position, position) == 0) {
          add_player(clubDummy, "club_dummy", playerPtr->name,
                     playerPtr->position, playerPtr->score);
        }
        playerPtr = playerPtr->next;
      }
    }
    if (clubPtr->injured_players != NULL) {
      playerPtr = clubPtr->injured_players;
      // parcurgerea si adaugarea jucatorilor accidentati
      while (playerPtr != NULL) {
        if (strcmp(playerPtr->position, position) == 0) {
          add_player(clubDummy, "club_dummy", playerPtr->name,
                     playerPtr->position, playerPtr->score);
          updateStatus(&clubDummy->players, playerPtr->name,
                       playerPtr->injured);
        }
        playerPtr = playerPtr->next;
      }
    }
    clubPtr = clubPtr->next;
  }
  // sortarea listei
  sortByScore(clubDummy->players);
  sortByName(clubDummy->players);
  Player *playerListPtr = clubDummy->players;
  free(clubDummy->name);
  free(clubDummy);
  return playerListPtr;
}

// Functia intoarce cel mai bun 11 format din toti jucatorii de la toate
// cluburile. Am creat o lista intermediara de jucatori in care am pus toti
// jucatorii de la toate cluburile, urmand apoi sa selectez pe cei mai buni
// de pe fiecare pozitie si sa formez lista/echipa finala
Player *get_best_team(FootballClub *clubs) {
  // crearea unui club de test temporar, ca sa pot folosi functiile
  // de la primul task
  FootballClub *clubDummy = (FootballClub *)malloc(sizeof(FootballClub)),
               *clubPtr = clubs;
  if (clubDummy == NULL)
    exit(1);
  Player *playerPtr;
  addFirstClub(clubDummy, "club_dummy", 0);
  // parcurgerea cluburilor
  while (clubPtr != NULL) {
    if (clubPtr->players != NULL) {
      playerPtr = clubPtr->players;
      // parcurgerea si adaugarea jucatorilor neaccidentati
      // la lista temporara
      while (playerPtr != NULL) {
        add_player(clubDummy, "club_dummy", playerPtr->name,
                   playerPtr->position, playerPtr->score);
        playerPtr = playerPtr->next;
      }
    }
    if (clubPtr->injured_players != NULL) {
      playerPtr = clubPtr->injured_players;
      // parcurgerea  si adaugarea jucatorilor accidentati
      // la lista temporara
      while (playerPtr != NULL) {
        add_player(clubDummy, "club_dummy", playerPtr->name,
                   playerPtr->position, playerPtr->score);
        updateStatus(&clubDummy->players, playerPtr->name, playerPtr->injured);
        playerPtr = playerPtr->next;
      }
    }
    clubPtr = clubPtr->next;
  }
  int i = 0;
  // sortarea (tuturor) jucatorilor
  sortPlayers(&clubDummy, "club_dummy");
  playerPtr = clubDummy->players;
  // adaugarea unui nou club, care sa gazduiasca lista finala
  add_club(clubDummy, "second_club_dummy");
  // adaugarea la lista finala a celor mai buni 3 atacanti
  while ((i < 3) && playerPtr != NULL &&
         (strcmp(playerPtr->position, "atacant") == 0)) {
    add_player(clubDummy, "second_club_dummy", playerPtr->name,
               playerPtr->position, playerPtr->score);
    // daca jucatorul este accidentat
    if (playerPtr->injured) {
      updateStatus(&clubDummy->next->players, playerPtr->name,
                   playerPtr->injured);
    }
    i++;
    playerPtr = playerPtr->next;
  }
  // cautarea primului fundas
  while (playerPtr != NULL && strcmp(playerPtr->position, "fundas")) {
    playerPtr = playerPtr->next;
  }
  i = 0;
  // adaugarea la lista finala a celor mai buni 4 fundasi
  while ((i < 4) && (playerPtr != NULL) &&
         (strcmp(playerPtr->position, "fundas") == 0)) {
    add_player(clubDummy, "second_club_dummy", playerPtr->name,
               playerPtr->position, playerPtr->score);
    // daca jucatorul este accidentat
    if (playerPtr->injured) {
      updateStatus(&clubDummy->next->players, playerPtr->name,
                   playerPtr->injured);
    }
    i++;
    playerPtr = playerPtr->next;
  }
  // cautarea primului mijlocas
  while (playerPtr != NULL && strcmp(playerPtr->position, "mijlocas")) {
    playerPtr = playerPtr->next;
  }
  i = 0;
  // adaugarea la lista finala a celor mai buni 3 mijlocasi
  while ((i < 3) && playerPtr != NULL &&
         (strcmp(playerPtr->position, "mijlocas") == 0)) {
    add_player(clubDummy, "second_club_dummy", playerPtr->name,
               playerPtr->position, playerPtr->score);
    // daca jucatorul este accidentat
    if (playerPtr->injured) {
      updateStatus(&clubDummy->next->players, playerPtr->name,
                   playerPtr->injured);
    }
    i++;
    playerPtr = playerPtr->next;
  }
  // cautarea primului portar
  while (playerPtr != NULL && strcmp(playerPtr->position, "portar") != 0) {
    playerPtr = playerPtr->next;
  }
  // adaugarea la lista finala a celui mai bun portar
  if (playerPtr != NULL) {
    add_player(clubDummy, "second_club_dummy", playerPtr->name,
               playerPtr->position, playerPtr->score);
    // daca jucatorul este accidentat
    if (playerPtr->injured) {
      updateStatus(&clubDummy->next->players, playerPtr->name,
                   playerPtr->injured);
    }
  }
  // sortarea jucatorilor din lista finala
  sortByScore(clubDummy->next->players);
  sortByName(clubDummy->next->players);
  destroy_player_list(clubDummy->players);
  clubPtr = clubDummy->next;
  free(clubDummy->name);
  free(clubDummy);
  playerPtr = clubPtr->players;
  free(clubPtr->name);
  free(clubPtr);
  return playerPtr;
}

#endif // TEAM_EXTRACTOR_H_INCLUDED
