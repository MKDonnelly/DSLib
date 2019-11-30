#pragma once

typedef struct msg{
   //This is a buffer that contains
   //the message.
   char *msg;
   
   //This is the size of the buffer "msg"
   int maxlen;

   //This is the size of valid data in "msg"
   int datalen;

   //Points to metadata within the message.
   //This is mostly a convenience pointer.
   char *header;
}msg_t;

#define msg_maxlen(msg) ((msg)->maxlen)
#define msg_datalen(msg) ((msg)->datalen)
#define msg_message(message) ((message)->msg)

msg_t *msg_create(int init_size);
msg_t *msg_create_from(char *str);

//TODO make this inteligentelly resize;
//     we must always have at least newsize
//     bytes available, but if the message starts
//     larger than it, we need not resize.
void msg_resize_for(msg_t *msg, int newsize);
void msg_write(msg_t *msg, char *format, ...);
void msg_free(msg_t *msg);

//Send/receive messages from socket
msg_t *msg_receive(int client_fd);
void msg_send(int fd, msg_t *msg);
