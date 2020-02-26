#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10001

int main(int argc, char **argv)
{
  msg r;
  init(HOST, PORT);

  if (recv_message(&r) < 0)
  {
    perror("Receive message");
    return -1;
  }
  printf("[recv] Got msg with payload: <%s>, sending ACK...\n", r.payload);

  // Send ACK:
  sprintf(r.payload, "%s", "ACK1");
  r.len = strlen(r.payload) + 1;
  send_message(&r);
  printf("[recv] ACK1 sent\n");

  msg msg2;
  if (recv_message(&msg2) < 0)
  {
    perror("eroare la primit nume fisier");
    return 01;
  }

  printf("[receiver] filename: %s\n", msg2.payload + sizeof(int));

  // Send ACK:
  sprintf(r.payload, "%s", "ACK2");
  r.len = strlen(r.payload) + 1;
  send_message(&r);
  printf("[recv] ACK2 sent\n");

  if (recv_message(&msg2) < 0)
  {
    perror("eroare la primit dimensiune");
    return 01;
  }

  printf("[receiver] size of file: %s\n", msg2.payload + sizeof(int));

  // Send ACK:
  sprintf(r.payload, "%s", "ACK3");
  r.len = strlen(r.payload) + 1;
  send_message(&r);
  printf("[recv] ACK3 sent\n");

  int i = 4;
  while (1)
  {
    if (recv_message(&msg2) < 0)
    {
      perror("eroare la primit nume fisier");
      return 01;
    }

    printf("[receiver] content of file in buffer[%d]: %s\n", (i - 4), msg2.payload + sizeof(int));

    // Send ACK:
    sprintf(r.payload, "%s", "ACK-read");
    r.len = strlen(r.payload) + 1;
    send_message(&r);
    printf("[recv] ACK%d sent\n", i++);
  }

  return 0;
}
