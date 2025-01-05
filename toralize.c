#include "toralize.h"
// ./toralise <ip we want to access> <port_name>

int main(int argc, char *argv[]) {

  char *host_name;
  int port, s;
  Req *req;
  Res res;
  char buf[RESSIZE];
  int success;
  char temp[512];

  struct sockaddr_in sock;

  if (argc < 3) {
    fprintf(stderr, "usage %s <host> <port>\n", argv[0]);
    return -1;
  }

  host_name = argv[1];
  port = atoi(argv[2]);
  s = socket(AF_INET, SOCK_STREAM, 0);

  if (s < 0) {
    perror("error while creating socket instance ");
    return -1;
  }
  sock.sin_family = AF_INET;
  sock.sin_port = htons(PROXY_PORT);
  sock.sin_addr.s_addr = inet_addr(PROXY);

  if (connect(s, (struct sockaddr *)&sock, sizeof(sock))) {
    perror("error binding the socket()");
    return -1;
  }
  printf("connected to proxy\n");
  req = request(host_name, port);
  write(s, req, REQSIZE);

  memset(buf, 0, RESSIZE);
  if (read(s, buf, RESSIZE) < 1) {
    perror("error while reading buffer");
    free(req);
    close(s);

    return -1;
  }
  memcpy(&res, buf, RESSIZE);
  success = (res.cd == 90);
  if (!success) {
    fprintf(stderr, "unable to traverse proxy, error code : %d\n", res.cd);
    close(s);
    free(req);
    return -1;
  }

  printf("Successfully connected through the  proxy to %s:%d\n", host_name,
         port);
  memset(temp, 0, 512);
  snprintf(temp, 511,
           "HEAD / HTTP/1.0\r\n"
           "Host: %s\r\n"
           "User-Agent: Mozilla/5.0\r\n"
           "Accept: */*\r\n"
           "Connection: close\r\n"
           "\r\n",
           "www.networktechnology.org");
  write(s, temp, strlen(temp));
  memset(temp, 0, 512);
  read(s, temp, 511);
  printf("'%s'\n", temp);

  close(s);
  free(req);
  return 0;
}

Req *request(const char *destIP, const int destport) {
  Req *req;
  req = malloc(REQSIZE);

  req->vn = 4;
  req->cd = 1;
  req->dstport = htons(destport);
  req->dstIP = inet_addr(destIP);
  strncpy((char *)req->userID, USERNAME, 8);

  return req;
}
