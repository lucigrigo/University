#include "skel.h"

int main(int argc, char *argv[])
{
	packet m;
	int rc;

	init();

	while (1) {
		rc = get_packet(&m);
		DIE(rc < 0, "get_message");
		/* Students will write code here */
	}
}
