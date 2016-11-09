#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *hostname = NULL;

void ping(const char *host)
{
  struct hostent *h;
  struct sockaddr_in pingaddr;
  struct icmp *pkt;
  int pingsock, c;
  char packet[192];
  pingsock = socket(AF_INET, SOCK_RAW, 1);
  if (pingsock < 0) {       
    printf("ping: creating a raw socket");
    exit(1);
  }
  
  
  memset(&pingaddr, 0, sizeof(struct sockaddr_in));
  
  pingaddr.sin_family = AF_INET;
  if (!(h = gethostbyname(host))) {
    printf("ping: unknown host %s\n", host);
    exit(1);
  }
  memcpy(&pingaddr.sin_addr, h->h_addr, sizeof(pingaddr.sin_addr));
  hostname = h->h_name;
  
  pkt = (struct icmp *) packet;
  memset(pkt, 0, sizeof(packet));
  pkt->icmp_type = ICMP_ECHO;
  pkt->icmp_cksum = 65527;
  
  c = sendto(pingsock, packet, sizeof(packet), 0, (struct sockaddr *) &pingaddr, sizeof(struct sockaddr_in));
  
  if (c < 0 || c != sizeof(packet)) {
    if (c < 0)
      perror("ping: sendto");
    printf("ping: write incomplete\n");
    exit(1);
  }
  
  while (1) {
    struct sockaddr_in from;
    size_t fromlen = sizeof(from);
    
    if ((c = recvfrom(pingsock, packet, sizeof(packet), 0, (struct sockaddr *) &from, &fromlen)) < 0) {
      continue;
    }
    if (c >= 76) {                   
      struct iphdr *iphdr = (struct iphdr *) packet;
      
      pkt = (struct icmp *) (packet + (iphdr->ihl << 2));      
      if (pkt->icmp_type == ICMP_ECHOREPLY)
        printf("reply %s successfully received\n", hostname);
        break;
    }
  }
  printf("%s is alive!\n", hostname);
  return;
}

int main ()
{
  ping ("www.facebook.com");

}