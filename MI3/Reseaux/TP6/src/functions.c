/*
 * utils.c
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

/* User Management */
int create_user(char*login,char*password){
	struct user usr;
	if (nbusers>=MAX_USERS) return -1;
	strcpy(usr.login,login);
	// Double encryption means, user have to make a collision to authenticate
	strcpy(usr.passwd,lcrypt(lcrypt(password))); 
	usr.status=0;
	usr.socket=NULL;
	allusers[nbusers++]=usr;
	return nbusers;
}

int create_user_toidentify(lsocket*sck){
	struct toidentify pend;
	if (nbtoidentify>=MAX_PENDING) return -1;
	pend.socket=sck;
	alltoidentify[nbtoidentify++]=pend;
	return nbtoidentify-1;
}

int find_user(char*name){
	int i;
	for(i=0;i<nbusers;i++) if (!strcmp(name,allusers[i].login)) return i;
	return -1;
}

int find_socket_toidentify(lsocket*sck){
	int i;
	for(i=0;i<nbtoidentify;i++)	if (alltoidentify[i].socket->file==sck->file) return i;
	return -1;
}

int find_socket(lsocket*sck){
	int i;
	for(i=0;i<nbusers;i++) if (sck->file==allusers[i].socket->file) return i;
	return -1;
}

/*
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
*/
