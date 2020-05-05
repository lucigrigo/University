#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10000

int main(int argc, char *argv[])
{
	msg t;
	// int i;
	int res;
	t.done = 0;

	printf("[SENDER] Starting.\n");
	init(HOST, PORT);

	/* printf("[SENDER]: BDP=%d\n", atoi(argv[1])); */

	// for (i = 0; i < COUNT; i++) {
	// 	/* cleanup msg */
	// 	memset(&t, 0, sizeof(msg));

	// 	/* gonna send an empty msg */
	// 	t.len = MSGSIZE;

	// 	/* send msg */
	// 	res = send_message(&t);
	// 	if (res < 0) {
	// 		perror("[SENDER] Send error. Exiting.\n");
	// 		return -1;
	// 	}

	// 	/* wait for ACK */
	// 	res = recv_message(&t);
	// 	if (res < 0) {
	// 		perror("[SENDER] Receive error. Exiting.\n");
	// 		return -1;
	// 	}
	// }

	int fd = open("input.txt", O_RDONLY);
	// int packages_sent = 0;
	int isValid;
	char buffer[1400];
	int bd = atoi(argv[1]);
	float window_size = (bd * 1000) / (sizeof(msg) * 8);
	int current_size = 0;
	// printf("WINDOW SIZE = %f\n", window_size);

	// while (1)
	// {

	while (current_size <= window_size)
	{
		isValid = read(fd, buffer, sizeof(buffer));

		if (isValid < 0)
		{
			perror("\ncan't read from file!");
			exit(1);
		}
		sprintf(t.payload, "%s", buffer);
		t.len = 2 * sizeof(int) + strlen(t.payload) + 1;
		// t.len = MSGSIZE;
		res = send_message(&t);
		printf("\n[SENDER] Se trimite pachetul cu continutul: %s\n", t.payload);

		// current_size += MSGSIZE;
		current_size++;

		// printf("asdjnad");
	}
	// while (current_size <= window_size)
	// {
	while ((isValid = read(fd, buffer, sizeof(buffer))))
	{
		while (1)
		{
			res = recv_message(&t);
			// packages_sent--;
			current_size -= t.len;
			if (res < 0)
			{
				perror("\n[SENDER] Receive error. Exiting.\n");
				return -1;
			}
			break;
		}
		if (isValid < 0)
		{
			perror("\ncan't read from file!");
			exit(1);
		}
		// printf("asdjnad");
		// memset(t.payload, 0, MSGSIZE);

		sprintf(t.payload, "%s", buffer);
		// t.len = 2 * sizeof(int) + strlen(t.payload) + 1;
		t.len = MSGSIZE;
		res = send_message(&t);
		printf("\n[SENDER] Se trimite pachetul cu continutul: %s\n", t.payload);

		// current_size += MSGSIZE;
		current_size++;
		// packages_sent++;
	}

	t.done = 1;
	send_message(&t);

	res = recv_message(&t);
	// packages_sent--;
	current_size -= t.len;
	if (res < 0)
	{
		perror("\n[SENDER] Receive error. Exiting.\n");
		return -1;
	}

	// memset(&t, 0, sizeof(msg));
	// memset(&t.payload, 0, strlen(t.payload));
	// send_message(&t);

	// 	if (current_size == 0)
	// 	{
	// 		break;
	// 	}
	// }

	// 	if (packages_sent == 0)
	// 	{
	// 		break;
	// 	}
	// }

	printf("[SENDER] Job done, all sent.\n");

	return 0;
}
