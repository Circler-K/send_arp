#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <netdb.h>
#include <string.h>
#include <pcap.h>
#include <stdio.h>
#include <netinet/ether.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
int getmac(char *name){
        struct ifreq s;
        int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
        strcpy(s.ifr_name, name);
        if (0 == ioctl(fd, SIOCGIFHWADDR, &s)) {
        int i;
        for (i = 0; i < 6; ++i)
            printf(" %02x", (unsigned char) s.ifr_addr.sa_data[i]);
        return 0;
        }
    return 1;
}
int GetSvrMacAddress()
{
 int nSD; // Socket descriptor
 struct ifreq *ifr; // Interface request
 struct ifconf ifc;
 int i, numif;

 memset(&ifc, 0, sizeof(ifc));
 ifc.ifc_ifcu.ifcu_req = NULL;
 ifc.ifc_len = 0;

 // Create a socket that we can use for all of our ioctls
 nSD = socket( PF_INET, SOCK_DGRAM, 0 );
 if ( nSD < 0 )  return 0;
 if(ioctl(nSD, SIOCGIFCONF, &ifc) < 0) return 0;
 if ((ifr = (ifreq*)  malloc(ifc.ifc_len)) == NULL) 
 {
   return 0;
 }
 else
 {
  ifc.ifc_ifcu.ifcu_req = ifr;
  if (ioctl(nSD, SIOCGIFCONF, &ifc) < 0) 
  {
   return 0;
  }
  numif = ifc.ifc_len / sizeof(struct ifreq);
  for (i = 0; i < numif; i++) 
  {
   struct ifreq *r = &ifr[i];
   struct sockaddr_in *sin = (struct sockaddr_in *)&r->ifr_addr;
   if (!strcmp(r->ifr_name, "lo"))
    continue; // skip loopback interface
 
   if(ioctl(nSD, SIOCGIFHWADDR, r) < 0) 
    return 0;
   char macaddr[100];
   sprintf(macaddr, "[%s] %02X:%02X:%02X:%02X:%02X:%02X",
       r->ifr_name,
       (unsigned char)r->ifr_hwaddr.sa_data[0],
       (unsigned char)r->ifr_hwaddr.sa_data[1],
       (unsigned char)r->ifr_hwaddr.sa_data[2],
       (unsigned char)r->ifr_hwaddr.sa_data[3],
       (unsigned char)r->ifr_hwaddr.sa_data[4],
       (unsigned char)r->ifr_hwaddr.sa_data[5]);
   return 0;
  }
 }
 close(nSD);
 free(ifr);
 
 return( 1 );
 }

