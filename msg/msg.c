#include "msg.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

msg_t *msg_create(int init_size){
   msg_t *new_message = malloc(sizeof(msg_t));
   new_message->msg = malloc(init_size);
   new_message->maxlen = init_size;
   new_message->datalen = 0;
   return new_message;
}

msg_t *msg_create_from(char *str){
   msg_t *new_message = malloc(sizeof(msg_t));
   new_message->msg = strdup(str);
   new_message->maxlen = new_message->datalen = strlen(str);
   return new_message;
}

void msg_resize_for(msg_t *msg, int newsize){
   if( msg->maxlen < newsize ){
      msg->maxlen = newsize;
      msg->msg = realloc(msg->msg, newsize * sizeof(char));
   }
}

//Note: currently, I assume the message is long enough
//      without resizing.
void msg_write(msg_t *msg, char *format, ...){
   va_list fmtargs;
   va_start(fmtargs, format);

   int iformat = 0;
   int ioutput = 0;
   while( format[iformat] != 0 ){
      
      if( format[iformat] == '%' ){
         if( format[iformat+1] == 'd' ){
            ioutput += sprintf(&msg->msg[ioutput], "%d", va_arg(fmtargs, int));
         }else if( format[iformat+1] == 's' ){
            ioutput += sprintf(&msg->msg[ioutput], "%s", va_arg(fmtargs, char*));
         }else if( format[iformat+1] == 'b' ){
            char *data = va_arg(fmtargs, char*);
            int datalen = va_arg(fmtargs, int);
            for(int i = 0; i < datalen; i++)
               msg->msg[ioutput+i] = data[i];
            ioutput += datalen;
         }else if( format[iformat+1] == '%' ){
            msg->msg[ioutput++] = '%';
         }
         iformat += 2;
      }else{
         msg->msg[ioutput++] = format[iformat++];
      }
   }
   msg->msg[ioutput++] = '\0';
   msg->datalen = ioutput;
}

void msg_free(msg_t *msg){
   free(msg->msg);
   free(msg);
}

msg_t *msg_receive(int client_fd){
   int datalen = 0;
   ssize_t r = read(client_fd, &datalen, sizeof(int));
   
   msg_t *msg = msg_create(datalen);
   r = read(client_fd, msg_message(msg), datalen);

   return msg;
}

void msg_send(int fd, msg_t *msg){
   write(fd, &msg_datalen(msg), sizeof(msg_datalen(msg)));
   write(fd, msg_message(msg), msg_datalen(msg));
}
