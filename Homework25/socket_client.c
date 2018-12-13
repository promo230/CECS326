#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
int main() {
  int s;
  char message[1024];
  struct sockaddr_in      srv_addr;
  /* Get a socket. */
  s = socket(PF_INET, SOCK_STREAM, 0);
  /* Put server's address into a socket structure */
  //memset(&srv_addr, 0, sizeof(srv_addr));
  srv_addr.sin_addr.s_addr = inet_addr("134.139.248.3");
  srv_addr.sin_family = AF_INET;
  srv_addr.sin_port = htons(7);
  /* Request the connection to the server */
  connect(s, (struct sockaddr *) &srv_addr, sizeof(srv_addr));
  /*Get time from serve*/
  char *msg = "My name is hi";
  write(s, msg, sizeof(message));
  read(s, message, sizeof(message));
  
  printf("%s",message);
  close(s);
  return 0;
}
