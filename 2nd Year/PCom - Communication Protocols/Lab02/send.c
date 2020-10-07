#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "link_emulator/lib.h"
#include "my_msg.h"

#define HOST "127.0.0.1"
#define PORT 10000

int main(int argc, char **argv)
{
  init(HOST, PORT);
  msg t;

  //Send dummy message:
  printf("[send] Sending dummy...\n");
  sprintf(t.payload, "%s", "This is a dummy.");
  t.len = strlen(t.payload) + 1;
  send_message(&t);

  // Check response:
  if (recv_message(&t) < 0)
  {
    perror("Receive error ...");
    return -1;
  }
  else
  {
    printf("[send] Got reply with payload: %s\n", t.payload);
  }

  printf("[send] Sending file name...\n");

  my_msg msg2;
  char *filename = "test.txt";
  sprintf(msg2.payload, "%s", filename);
  msg2.type = 0;

  memcpy(t.payload, &msg2, sizeof(int) + strlen(msg2.payload) + 1);
  t.len = sizeof(int) + strlen(msg2.payload) + 1;
  send_message(&t);

  if (recv_message(&t) < 0)
  {
    perror("Receive error ...");
    return -1;
  }
  else
  {
    printf("[send] Got reply with payload: %s\n", t.payload);
  }

  printf("[send] Sending size of file...\n");

  int file_d = open(filename, O_RDONLY);
  int length = lseek(file_d, 0, SEEK_END);
  sprintf(msg2.payload, "%d", length);
  msg2.type = 1;

  memcpy(t.payload, &msg2, sizeof(int) + strlen(msg2.payload) + 1);
  t.len = sizeof(int) + strlen(msg2.payload) + 1;
  send_message(&t);

  if (recv_message(&t) < 0)
  {
    perror("Receive error ...");
    return -1;
  }
  else
  {
    printf("[send] Got reply with payload: %s\n", t.payload);
  }

  // printf("[send] Sending CONTENT of file...\n");
  char buf[2];
  int isValid;
  lseek(file_d, 0, SEEK_SET);

  while ((isValid = read(file_d, buf, sizeof(buf))))
  {
    if (isValid < 0)
    {
      perror("can't read from file!");
      exit(2);
    }
    msg2.type = 2;
    sprintf(msg2.payload, "%s", buf);

    memcpy(t.payload, &msg2, sizeof(int) + strlen(msg2.payload) + 1);
    t.len = sizeof(int) + strlen(msg2.payload) + 1;

    send_message(&t);
  }

  if (recv_message(&t) < 0)
  {
    perror("Receive error ...");
    return -1;
  }
  else
  {
    printf("[send] Got reply with payload: %s\n", t.payload);
  }

  return 0;
}
