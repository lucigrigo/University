#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10001


int main(int argc,char** argv){
  msg r;
  init(HOST,PORT);

  if (recv_message(&r)<0){
    perror("Receive message");
    return -1;
  }
  printf("[recv] Got msg with payload: <%s>, sending ACK...\n", r.payload);

  // Send ACK:
  sprintf(r.payload,"%s", "ACK");
  r.len = strlen(r.payload) + 1;
  send_message(&r);
  printf("[recv] ACK sent\n");

  return 0;
}
