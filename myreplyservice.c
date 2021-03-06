#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <uci.h>


int main(int argc, char **argv){
	char path[] = "myreplyservice.default.reply";
	struct uci_ptr ptr;
	struct uci_context *c = uci_alloc_context();

	if(!c) return 5;

	if((uci_lookup_ptr(c, &ptr, path, true) != UCI_OK) || (ptr.o == NULL || ptr.o->v.string==NULL)){
		uci_free_context(c);
		return 6;
	}
	if(!(ptr.flags & UCI_LOOKUP_COMPLETE)){
		fprintf(stderr, "Config File could not be read properly\n");
		return 7;
	}
	int len = strlen(ptr.o->v.string);
	char buffer[len+1];

	strncpy(buffer, ptr.o->v.string, len);
	buffer[len] = '\0';
//	printf("%s\n", buffer);

	uci_free_context(c);

	struct sockaddr_in serv_addr;
	int port = 5000;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	int addrlen = sizeof(serv_addr);
	if (sockfd < 0){
		fprintf(stderr, "socket error\n");
		return 1;
	}
	else{
		printf("Opened fd %d\n", sockfd);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;//port;
	serv_addr.sin_port = htons( port );

	int ret = bind(sockfd, (struct sockaddr *)&serv_addr, addrlen);
	if (ret < 0){
		printf("Bind Error\n");
		return 2;
	}

	if (listen(sockfd, 5) < 0){
		printf("listen failed\n"); 
		return 3;
	}

	while(1){
		int client_sock = accept(sockfd, (struct sockaddr *)&serv_addr, (socklen_t*)&addrlen);
		if (client_sock < 0){
			printf("accept failed\n");
			return 4;
		}
	
		send(client_sock, buffer, len, 0);	

	}

	return 0;
}
