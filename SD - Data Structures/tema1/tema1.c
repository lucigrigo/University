#include <stdio.h>

#include "TeamExtractor.h"

void test0() {
	FILE *f = fopen("test0.out", "w");
	if (f == NULL) {
		printf("Error opening file test0.out!\n");
		return;
	}
	char **names = calloc(3, sizeof(char*));
	for (int i = 0; i < 3; i++) {
		names[i] = calloc(20, sizeof(char));
		sprintf(names[i], "club%d", i+1);
	}
	FootballClub *clubs = initialize_clubs(3, names);
	clubs = add_club(clubs, "club4");
	add_player(clubs, "club1", "n1", "atacant", 1);
	add_player(clubs, "club1", "n7", "atacant", -100);
	add_player(clubs, "club2", "n2", "fundas", 2);
	add_player(clubs, "club3", "n3", "mijlocas", 3);
	add_player(clubs, "club4", "n4", "portar", 4);
	add_player(clubs, "club4", "n5", "portar", 0);
	show_clubs_info(f, clubs);
	if (clubs) {
		show_list_reverse(f, clubs->players, 0);
	}
	add_injury(clubs, "club1", "n1", 10);
	add_injury(clubs, "club1", "n7", 10);
	remove_player(clubs, "club2", "n2");
	update_score(clubs, "club3", "n3", 5);
	update_game_position(clubs, "club4", "n5", "atacant", 0);
	show_clubs_info(f, clubs);
	recover_from_injury(clubs, "club1", "n1");
	transfer_player(clubs, "n3", "club3", "club2");
	show_clubs_info(f, clubs);
	destroy_club_list(clubs);
	for (int i = 0; i < 3; i++) {
		free(names[i]);
	}
	free(names);
	fclose(f);
}

void test1() {
	FILE *f = fopen("test1.out", "w");
	if (f == NULL) {
		printf("Error opening file test1.out!\n");
		return;
	}
	char **names = calloc(5, sizeof(char*));
	for (int i = 0; i < 5; i++) {
		names[i] = calloc(20, sizeof(char));
		sprintf(names[i], "club%d", i);
	}

	FootballClub *clubs = initialize_clubs(1, names);
	remove_player(clubs, "club1", "j1");
	add_player(clubs, "club1", "j1", "fundas", 20);
	remove_player(clubs, "club1", "j1");
	remove_player(clubs, "club1", "j1");
	remove_player(clubs, "club0", "j0");
	remove_player(clubs, "club19", "j19");
	add_player(clubs, "club0", "j0", "fundas", 20);
	show_clubs_info(f, clubs);
	remove_player(clubs, "club0", "j0");
	remove_player(clubs, "club0", "j0");
	show_clubs_info(f, clubs);
	clubs = add_club(clubs, "club2");
	add_player(clubs, "club0", "j0", "fundas", 20);
	add_player(clubs, "club1", "j1", "fundas", 20);
	add_player(clubs, "club2", "j2", "fundas", 20);
	remove_player(clubs, "club2", "j2");
	remove_player(clubs, "club2", "j2");
	remove_player(clubs, "club1", "j1");
	show_clubs_info(f, clubs);
	clubs = add_club(clubs, "club1");
	add_player(clubs, "club1", "j1", "fundas", 20);
	add_injury(clubs, "club1", "j1", 1);
	show_clubs_info(f, clubs);
	remove_player(clubs, "club1", "j1");
	show_clubs_info(f, clubs);
	destroy_club_list(clubs);
	for (int i = 0; i < 5; i++) {
		free(names[i]);
	}
	free(names);
	fclose(f);
}

void test2() {
	FILE *f = fopen("test2.out", "w");
	if (f == NULL) {
		printf("Error opening file test2.out!\n");
		return;
	}
	char **names = calloc(3, sizeof(char*));
	for (int i = 0; i < 3; i++) {
		names[i] = calloc(20, sizeof(char));
		sprintf(names[i], "club%d", i);
	}
	FootballClub *clubs = initialize_clubs(3, names);
	add_player(clubs, "club1", "n2", "fundas", 20);
	add_player(clubs, "club1", "n1", "atacant", 10);
	add_player(clubs, "club1", "n3", "portar", 50);
	add_player(clubs, "club1", "n4", "mijlocas", 50);
	show_clubs_info(f, clubs);
	add_player(clubs, "club1", "n5", "atacant", 50);
	add_player(clubs, "club1", "n6", "atacant", 0);
	add_player(clubs, "club1", "n7", "atacant", 10);
	add_player(clubs, "club1", "b8", "atacant", 10);
	add_player(clubs, "club1", "n9", "portar", 10);
	add_player(clubs, "club1", "f4", "portar", 50);
	add_player(clubs, "club1", "z4", "portar", 50);
	add_player(clubs, "club1", "z5", "portar", 10);
	show_clubs_info(f, clubs);
	add_player(clubs, "club1", "s1", "fundas", 7);
	add_player(clubs, "club1", "s2", "fundas", 27);
	add_player(clubs, "club1", "m1", "mijlocas", 50);
	add_player(clubs, "club1", "r1", "mijlocas", 50);
	show_clubs_info(f, clubs);
	add_player(clubs, "club0", "a1", "fundas", 15);
	add_player(clubs, "club0", "a2", "atacant", 100);
	add_player(clubs, "club0", "a3", "mijlocas", 12);
	show_list(f, union_teams(clubs, "club1", "club2"), 1);
	show_list_reverse(f, union_teams(clubs, "club1", "club2"), 1);
	show_list(f, union_teams(clubs, "club1", "club0"), 1);
	show_list_reverse(f, union_teams(clubs, "club1", "club0"), 1);
	show_list(f, get_best_player(clubs, "atacant"), 1);
	show_list_reverse(f, get_best_player(clubs, "atacant"), 1);
	show_list(f, get_best_player(clubs, "fundas"), 1);
	show_list_reverse(f, get_best_player(clubs, "fundas"), 1);
	show_list(f, get_best_player(clubs, "portar"), 1);
	show_list_reverse(f, get_best_player(clubs, "portar"), 1);
	show_list(f, get_best_player(clubs, "mijlocas"), 1);
	show_list_reverse(f, get_best_player(clubs, "mijlocas"), 1);
	add_player(clubs, "club2", "e1", "mijlocas", 10);
	show_list(f, get_top_players(clubs, 2), 1);
	show_list_reverse(f, get_top_players(clubs, 2), 1);
	show_list(f, get_players_by_position(clubs, "fundas"), 1);
	show_list_reverse(f, get_players_by_position(clubs, "fundas"), 1);
	show_list(f, get_players_by_score(clubs, 0), 1);
	show_list_reverse(f, get_players_by_score(clubs, 0), 1);
	show_list(f, get_best_team(clubs), 1);
	show_list_reverse(f, get_best_team(clubs), 1);
	destroy_club_list(clubs);
	for (int i = 0; i < 3; i++) {
		free(names[i]);
	}
	free(names);
	fclose(f);
}

void test3() {
	FILE *f = fopen("test3.out", "w");
	if (f == NULL) {
		printf("Error opening file test3.out!\n");
		return;
	}
	FootballClub *clubs = initialize_clubs(0, NULL);
	clubs = add_club(clubs, "club1");
	clubs = add_club(clubs, "club2");
	add_player(clubs, "club1", "bogdan", "atacant", 27);
	add_player(clubs, "club1", "andra", "portar", 27);
	add_player(clubs, "club1", "dragos", "mijlocas", 27);
	add_player(clubs, "club1", "cosmin", "atacant", 13);
	add_player(clubs, "club1", "andrei", "fundas", 10);
	add_player(clubs, "club1", "alex", "atacant", 100);
	add_player(clubs, "club1", "cristina", "portar", 10);
	add_player(clubs, "club1", "mihai", "mijlocas", 40);
	add_player(clubs, "club1", "diana", "fundas", -100);
	add_player(clubs, "club1", "ioana", "atacant", 12);
	add_player(clubs, "club1", "emilia", "mijlocas", 40);
	remove_player(clubs, "club1", "bogdan");
	transfer_player(clubs, "alex", "club1", "club2");
	transfer_player(clubs, "emilia", "club1", "club2");
	transfer_player(clubs, "cristina", "club1", "club2");
	remove_player(clubs, "club1", "bogdan");
	add_player(clubs, "club1", "bogdan", "atacant", 27);
	add_injury(clubs, "club1", "bogdan", 12);
	update_score(clubs, "club1", "ioana", 20);
	update_score(clubs, "club1", "ioana", 20);
	update_game_position(clubs, "club1", "andra", "atacant", 20);
	update_score(clubs, "club1", "mihai", 12);
	add_injury(clubs, "club1", "ioana", 10);
	add_injury(clubs, "club1", "mihai", 10);
	add_injury(clubs, "club1", "andrei", 10);
	transfer_player(clubs, "bogdan", "club1", "club2");
	recover_from_injury(clubs, "club2", "bogdan");
	recover_from_injury(clubs, "club2", "ioana");
	recover_from_injury(clubs, "club1", "ioana");
	recover_from_injury(clubs, "club1", "mihai");
	update_game_position(clubs, "club1", "andrei", "fundas", 20);
	update_score(clubs, "club1", "andrei", 15);
	show_list(f, union_teams(clubs, "club1", "club2"), 1);
	show_list(f, get_best_player(clubs, "atacant"), 1);
	show_list(f, get_best_player(clubs, "fundas"), 1);
	show_list(f, get_best_player(clubs, "portar"), 1);
	show_list(f, get_best_player(clubs, "mijlocas"), 1);
	show_list(f, get_top_players(clubs, 1), 1);
	show_list(f, get_players_by_position(clubs, "fundas"), 1);
	show_list(f, get_players_by_score(clubs, 0), 1);
	show_list(f, get_best_team(clubs), 1);
	destroy_club_list(clubs);
	fclose(f);
}

void test4() {
	FILE *f = fopen("test4.out", "w");
	if (f == NULL) {
		printf("Error opening file test4.out!\n");
		return;
	}
	char **names = calloc(3, sizeof(char*));
	for (int i = 0; i < 3; i++) {
		names[i] = calloc(20, sizeof(char));
		sprintf(names[i], "fc%d", i);
	}
	char *s1, *s2, *s3;
	FootballClub *clubs = initialize_clubs(3, names);
	for (int i = 3; i < 100; i++) {
		s1 = calloc(20, sizeof(char));
		sprintf(s1, "fc%d", i);
		clubs = add_club(clubs, s1);
		free(s1);
	}
	for (int i = 0; i < 100; i += 4) {
		s1 = calloc(20, sizeof(char));
		s2 = calloc(20, sizeof(char));
		sprintf(s1, "fc%d", i);
		sprintf(s2, "pym%d", i);
		add_player(clubs, s1, s2, "mijlocas", i);
		remove_player(clubs, s1, s2);
		remove_player(clubs, s1, s2);
		add_player(clubs, s1, s2, "mijlocas", i);
		free(s1);
		free(s2);
	}
	for (int i = 1; i < 100; i += 4) {
		s1 = calloc(20, sizeof(char));
		s2 = calloc(20, sizeof(char));
		sprintf(s1, "fc%d", i);
		sprintf(s2, "pyp%d", i);
		add_player(clubs, s1, s2, "portar", i);
		remove_player(clubs, s1, s2);
		remove_player(clubs, s1, s2);
		add_player(clubs, s1, s2, "portar", i);
		free(s1);
		free(s2);
	}
	for (int i = 2; i < 100; i += 4) {
		s1 = calloc(20, sizeof(char));
		s2 = calloc(20, sizeof(char));
		sprintf(s1, "fc%d", i);
		sprintf(s2, "pyf%d", i);
		add_player(clubs, s1, s2, "fundas", i);
		remove_player(clubs, s1, s2);
		remove_player(clubs, s1, s2);
		add_player(clubs, s1, s2, "fundas", i);
		free(s1);
		free(s2);
	}
	for (int i = 3; i < 100; i += 4) {
		s1 = calloc(20, sizeof(char));
		s2 = calloc(20, sizeof(char));
		sprintf(s1, "fc%d", i);
		sprintf(s2, "pya%d", i);
		add_player(clubs, s1, s2, "atacant", i);
		remove_player(clubs, s1, s2);
		remove_player(clubs, s1, s2);
		add_player(clubs, s1, s2, "atacant", i);
		free(s1);
		free(s2);
	}
	for (int i = 0; i < 99; i += 2) {
		s1 = calloc(20, sizeof(char));
		s2 = calloc(20, sizeof(char));
		s3 = calloc(20, sizeof(char));
		sprintf(s1, "fc%d", i);
		sprintf(s2, "fc%d", i+1);
		sprintf(s3, "pym%d", i);
		transfer_player(clubs, s3, s1, s2);
		transfer_player(clubs, s3, s2, s1);
		update_score(clubs, s1, s3, 50);
		transfer_player(clubs, s3, s1, s2);
		add_injury(clubs, s2, s3, 100);
		transfer_player(clubs, s3, s2, s1);
		transfer_player(clubs, s3, s1, s2);
		free(s1);
		free(s2);
		free(s3);
	}
	for (int i = 1; i < 99; i += 2) {
		s1 = calloc(20, sizeof(char));
		s2 = calloc(20, sizeof(char));
		s3 = calloc(20, sizeof(char));
		sprintf(s1, "fc%d", i);
		sprintf(s2, "fc%d", i+1);
		sprintf(s3, "pyp%d", i);
		transfer_player(clubs, s3, s1, s2);
		transfer_player(clubs, s3, s2, s1);
		update_score(clubs, s1, s3, 50);
		transfer_player(clubs, s3, s1, s2);
		add_injury(clubs, s2, s3, 100);
		transfer_player(clubs, s3, s2, s1);
		transfer_player(clubs, s3, s1, s2);
		free(s1);
		free(s2);
		free(s3);
	}
	show_clubs_info(f, clubs);
	for (int i = 0; i < 99; i++) {
		s1 = calloc(20, sizeof(char));
		s2 = calloc(20, sizeof(char));
		sprintf(s1, "fc%d", i);
		sprintf(s2, "fc%d", i+1);
		show_list(f, union_teams(clubs, s1, s2), 1);
		show_list_reverse(f, union_teams(clubs, s1, s2), 1);
		free(s1);
		free(s2);
	}
	show_list(f, get_best_player(clubs, "atacant"), 1);
	show_list(f, get_best_player(clubs, "fundas"), 1);
	show_list(f, get_best_player(clubs, "portar"), 1);
	show_list(f, get_best_player(clubs, "mijlocas"), 1);
	show_list(f, get_top_players(clubs, 10), 1);
	show_list(f, get_players_by_position(clubs, "portar"), 1);
	show_list_reverse(f, get_players_by_position(clubs, "portar"), 1);
	show_list(f, get_players_by_position(clubs, "atacant"), 1);
	show_list_reverse(f, get_players_by_position(clubs, "atacant"), 1);
	show_list(f, get_players_by_score(clubs, 50), 1);
	show_list(f, get_players_by_score(clubs, 0), 1);
	show_list(f, get_best_team(clubs), 1);

	destroy_club_list(clubs);
	for (int i = 0; i < 3; i++) {
		free(names[i]);
	}
	free(names);
	fclose(f);
}

int main() {
	test0();
	test1();
	test2();
	test3();
	test4();
	return 0;
}
