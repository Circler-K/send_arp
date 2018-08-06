#include <stdlib.h>
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
int getmac(char *name,unsigned char *dst){
        struct ifreq s;
        int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
        strcpy(s.ifr_name, name);
        if (0 == ioctl(fd, SIOCGIFHWADDR, &s)) {
        int i;
        for (i = 0; i < 6; ++i){
            dst[i] = s.ifr_addr.sa_data[i];
	    printf(" %02x",(unsigned char) s.ifr_addr.sa_data[i]);
	    printf("(%d)",i);
	}
        return 0;
        }
        return 1;
}
int main(int argc, char **argv){
	unsigned char packet[42];
	struct ether_header *eth_packet_handler;
	int i;
	if(argc < 4){
        	printf("./send_arp ens33 gateway_IP victim_IP]\n");
	        return -1;
	}
	unsigned char asdf[6];
	getmac(argv[1],asdf);
//	pcap_sendpacket();
	puts((char)asdf);

	while (true) {
		struct pcap_pkthdr* header;
		const u_char* packet;
	}
	return 0;
}
