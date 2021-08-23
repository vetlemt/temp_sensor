#include "transmission.h"

void getJSON(char s[200]){
    char line[50];
    char oldest[30];    
    char newest[30];
    stats tempStats;
    getOldestTime(oldest);
    getNewestTime(newest);
    tempStats = getTempStats();
    
    sprintf(s,"");
    strcat(s,"{\n");
    strcat(s,"\t\"time\": {\n"); 
    sprintf(line, "\t\t\"start\": \"%s\",\n",oldest); strcat(s,line);
    sprintf(line, "\t\t\"end\": \"%s\"\n",   newest); strcat(s,line);
    strcat(s,"\t},\n");
    sprintf(line, "\t\"min\": %02.2f,\n",    tempStats.min); strcat(s,line);
    sprintf(line, "\t\"max\": %02.2f,\n",    tempStats.max); strcat(s,line);
    sprintf(line, "\t\"avg\": %02.2f\n", tempStats.avg); strcat(s,line);
    strcat(s,"}");
}

int post(char *json[],char *dir[])
{
    /* first what are we going to send and where are we going to send it? */
    int portno =        5000;
    char *host =        "localhost";
    char *message_fmt = "POST %s HTTP/1.0\r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n%s";

    struct hostent *server;
    struct sockaddr_in serv_addr;
    int sockfd, bytes, sent, received, total;
    char message[1024],response[4096];

    int msg_size = strlen(json);
    sprintf(message,message_fmt,dir,msg_size,json);
    printf("Request:\n%s\n",message);

    /* create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) perror("ERROR opening socket");

    /* lookup the ip address */
    server = gethostbyname(host);
    if (server == NULL) perror("ERROR, no such host");

    /* fill in the structure */
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);

    /* connect the socket */
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        perror("ERROR connecting");

    /* send the request */
    total = strlen(message);
    sent = 0;
    do {
        bytes = write(sockfd,message+sent,total-sent);
        if (bytes < 0)
            perror("ERROR writing message to socket");
        if (bytes == 0)
            break;
        sent+=bytes;
    } while (sent < total);

    /* receive the response */
    memset(response,0,sizeof(response));
    total = sizeof(response)-1;
    received = 0;
    do {
        bytes = read(sockfd,response+received,total-received);
        if (bytes < 0)
            perror("ERROR reading response from socket");
        if (bytes == 0)
            break;
        received+=bytes;
    } while (received < total);

    if (received == total)
        perror("ERROR storing complete response from socket");

    /* close the socket */
    close(sockfd);

    /* process response */
    printf("Response:\n%s\n",response);

    return 0;
}