/*
 * server.c
 * 
 * Copyright 2012 Maximilien Rigaut <max[dot]rigaut[at]orange.fr>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 */

#include "server.h"


struct user allusers[MAX_USERS];
struct message allmessages[MAX_MESSAGES];
struct toidentify alltoidentify [MAX_PENDING];
int nbusers,nbmessages,nbtoidentify;

int main(void){
	char buffer[MAXBUFFER+1];
	char buffer2[MAXBUFFER+1] = "Welcome\n";
	int fd;
	int fddistant;
	int err;
	int nb;
	nbusers=0;nbmessages=0;nbtoidentify=0;
	
	fd=cree_socket_ecoute();
	create_user("Superman","clarkken");
	create_user("Batman","brucewayne");
	
	if ((fddistant = accept(fd, NULL, NULL))<0) ERROR("Impossible to accept");
	
	while(global_wait());
	
	return 0;
}

/* User Management */
int create_user(char*login,char*password){
	struct user usr;
	if (nbusers>=MAX_USERS) return -1;
	strcpy(usr.login,login);
	strcpy(usr.passwd,password);
	usr.status=1;
	usr.socket=-1;
	allusers[nbusers++]=usr;
	return nbusers;
}

int set_login_user(struct toidentify*ident){
	int i;
	for(i=0;i<nbusers;i++){
		if (strcmp(allusers[i].login,ident->login)==0){
			if (strcmp(allusers[i].passwd,ident->login)==0) {
				allusers[i].socket=ident->socket;
				allusers[i].status=1;
				return i;
			} else return -1;
		}
	}
	return -1;
}

int create_user_toidentify(int sck){
	struct toidentify pend;
	if (nbtoidentify>=MAX_PENDING) return -1;
	pend.socket=sck;
	alltoidentify[nbtoidentify++]=pend;
	return nbtoidentify-1;
}

/* */
int find_socket(int sck){
	int i;
	for(i=0;i<nbusers;i++)
		if (sck-=allusers[i].socket) return i;
	return -1;
}

int find_socket_toidentify(int sck){
	int i;
	for(i=0;i<nbtoidentify;i++)	if (alltoidentify[i].socket==sck) return i;
	return -1;
}

int add_message(char*msg,int sender,int send_to){
	struct message mess;
	if (nbmessages>=MAX_MESSAGES) return -1;
	strcpy(mess.message,msg);
	mess.sender=sender;
	mess.sendto=send_to;
	allmessages[nbmessages++]=mess;
	return nbmessages-1;
}

int get_message(struct message*msg,fd_set*liste){
	int i;
	if (nbmessages==0) return -1;
	for(i=0;i<nbmessages;i++){
		if (FD_ISSET(allusers[allmessages[i].sendto].socket,liste)){
			*msg=allmessages[i];
			allmessages[i]=allmessages[--nbmessages];
			break;
		}
	}
	return 0;
}

int send_message(struct message*mess){
	char buffer[1000];
	sprintf(buffer,"%s>%s",allusers[mess->sendto].login,mess->message);
	if (write(find_socket(mess->sendto),buffer,strlen(buffer))<0)
		ERROR("Impossible to write");
	return 0;
}

int cut_message(char*command,char*content,const char*message){
	return sscanf(message,"%s:%s",command,content);
}

int cree_socket_ecoute(){
	struct sockaddr_in local;
	int fd;
	int err;
	int optval=1;
	// Socket
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd<0){ perror("Socket"); exit(EXIT_FAILURE); }  
	
	// Bind
	memset(&local, 0,sizeof(local));
	local.sin_family = AF_INET;
	local.sin_port = htons(PORT);
	local.sin_addr.s_addr = INADDR_ANY;
	err = bind(fd, (struct sockaddr*) & local, sizeof(local));
	if(err<0) { perror("Bind"); exit(EXIT_FAILURE); }

	affiche_adresse_socket(fd);
	setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(int));
	// Listen 
	err = listen(fd, 10);
	if(err<0) { perror("listen"); exit(EXIT_FAILURE); }
	
	return fd;
}

void affiche_adresse_socket(int sock){
  struct sockaddr_in adresse;
  unsigned int longueur;
  int err;

  longueur = sizeof(adresse);
  err = getsockname(sock, (struct sockaddr*)&adresse, &longueur);
  if(err<0) { perror("getsockname"); exit(EXIT_FAILURE); }
  printf("IP = %s, Port = %u\n",
         inet_ntoa(adresse.sin_addr),
         ntohs(adresse.sin_port));
}

int prepare_read(fd_set *set){
	int i,max=0;
	FD_ZERO(set);
	for(i=0;i<nbusers;i++){
		max=MAX(allusers[i].socket,max);
		FD_SET(allusers[i].socket,set);
	}
	return max;
}

int prepare_write(fd_set *set){
	int i,max=0;
	FD_ZERO(set);
	for(i=0;i<nbmessages;i++){
		max=MAX(allmessages[i].sendto,max);
		FD_SET(allmessages[i].sendto,set);
	}
	
	return max;	
}

int global_wait(){
	
	return 1;
}
