#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10001

int main(void)
{
	msg r;
	int i, res;

	printf("[RECEIVER] Starting.\n");
	init(HOST, PORT);

	// for (i = 0; i < COUNT; i++) {
	// 	/* wait for message */
	// 	res = recv_message(&r);
	// 	if (res < 0) {
	// 		perror("[RECEIVER] Receive error. Exiting.\n");
	// 		return -1;
	// 	}

	// 	/* send dummy ACK */
	// 	res = send_message(&r);
	// 	if (res < 0) {
	// 		perror("[RECEIVER] Send ACK error. Exiting.\n");
	// 		return -1;
	// 	}
	// }

	while (1)
	{
		// printf("asdjnad");
		res = recv_message(&r);
		if (res < 0)
		{
			perror("\n[RECEIVER] Receive error. Exiting.\n");
			return -1;
			// break;
		}
		if (r.done == 1)
		{
			break;
		}
		printf("\n[RECEIVER] S-a primit mesajul cu continutul: %s\n", r.payload);

		// if (!strcmp(r.payload, 0))
		// {
		// 	break;
		// }
		// sprintf(r.payload, "%s", "ACK");

		res = send_message(&r);
		if (res < 0)
		{
			perror("\n[RECEIVER] Send ACK error. Exiting.\n");
			return -1;
			// break;
		}
	}

	printf("\n[RECEIVER] Finished receiving..\n");
	return 0;
}
