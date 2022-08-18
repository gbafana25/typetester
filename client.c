#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <ctype.h>

#include "config.h"
#include "client.h"
#include "term.h"

int connect_to_server(char *un) {
	user_data ud; 
	ud.uname = un;
	struct sockaddr_in sr;
	int seg_size = 0;
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	memset(&sr, 0, sizeof(sr));
	sr.sin_family = AF_INET;
	sr.sin_port = htons(9001);
	inet_pton(AF_INET, srv_address, &sr.sin_addr.s_addr);
	int con = connect(sock, (struct sockaddr *) &sr, sizeof(sr));
	if(con < 0) {
		printf("Connection failed\n");
	}
	char in;
	send(sock, ud.uname, strlen(ud.uname), 0);
	recv(sock, &seg_size, sizeof(int), 0);
	seg_size += 1;
	//printf("%d\n", seg_size);
	char tx[seg_size];
	recv(sock, tx, sizeof(tx) - 1, 0);
	tx[seg_size] = '\0';
	// save current cursor position
	write(STDOUT_FILENO, "\e7", 3);
	clr_screen();
	// restore saved cursor position
	write(STDOUT_FILENO, "\e8", 3);
	printf("%s\n", tx);
	while(1) {
		read(STDIN_FILENO, &in, 1);
		
		//write(STDOUT_FILENO, &in, 1);
		send(sock, (void *) &in, sizeof(char), 0);
	}
	close(sock);


}
