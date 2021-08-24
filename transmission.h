#define transmissionh

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <unistd.h> /* read, write, close */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */
#ifndef readingsh
    #include "readings.h"
#endif

void getJSON(char *s);
void storeJSON(char *s);
void getJSONHistory(char *history);
int post(char *json, char *dir);
