#include <arpa/inet.h>
#include <math.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PROXY "127.0.0.1"
#define PROXY_PORT 9050
#define REQSIZE sizeof(struct proxy_request)
#define RESSIZE sizeof(struct proxy_response)
#define USERNAME "torali"

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;

/*
        format of request (source: https://www.openssh.com/txt/socks4.protocol)
        +----+----+----+----+----+----+----+----+----+----+....+----+
                | VN | CD | DSTPORT |      DSTIP        | USERID       |NULL|
                +----+----+----+----+----+----+----+----+----+----+....+----+
#bytes:   1    1      2              4           variable       1
implementing this in form of struct
*/

struct proxy_request {
  int8 vn;
  int8 cd;
  int16 dstport;
  int32 dstIP;
  unsigned char userID[8]; // making this of 8 bytes for 8 bytes userid
};

typedef struct proxy_request Req;

/*
        response header
        +----+----+----+----+----+----+----+----+
                | VN | CD | DSTPORT |      DSTIP        |
                +----+----+----+----+----+----+----+----+
#bytes:   1    1      2              4
*/
struct proxy_response {
  int8 vn; // 0 for response
  int8 cd; // 90 for success
  int16 _;
  int32 __;
};

typedef struct proxy_response Res;

Req *request(const char *, const int);
int main(int, char **);
