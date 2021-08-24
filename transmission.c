#include "transmission.h"

static char jsons[10][200];
int order = 0;
bool filled = false;

void getJSON(char *s)
{
    char line[50];
    char oldest[30];
    char newest[30];
    stats tempStats;
    getOldestTime(oldest);
    getNewestTime(newest);
    tempStats = getTempStats();

    sprintf(s, "{\n");
    strcat(s, "\t\"time\": {\n");
    sprintf(line, "\t\t\"start\": \"%s\",\n", oldest);
    strcat(s, line);
    sprintf(line, "\t\t\"end\": \"%s\"\n", newest);
    strcat(s, line);
    strcat(s, "\t},\n");
    sprintf(line, "\t\"min\": %02.2f,\n", tempStats.min);
    strcat(s, line);
    sprintf(line, "\t\"max\": %02.2f,\n", tempStats.max);
    strcat(s, line);
    sprintf(line, "\t\"avg\": %02.2f\n", tempStats.avg);
    strcat(s, line);
    strcat(s, "}");

    storeJSON(s);
}

// saves the json message
void storeJSON(char *s)
{
    strcpy(jsons[order], s);
    order++;
    if (order == 10)
    {
        filled = true;
    }
    order = order % 10; // loop the counter
    printf("\norder:%d\n", order);
}

// get the last max 10 json messages
void getJSONHistory(char *history)
{
    int j = order;
    char buff[2000];
    char *p;
    p = buff;
    sprintf(p, "[\n");
    if (!filled)
    {
        for (size_t i = 0; i < order; i++)
        {
            strcat(p, jsons[i]);
            strcat(p, ",\n");
        }
    }
    else
    {
        do
        {
            strcat(p, jsons[j]);
            strcat(p, ",\n");
            j++;
            j = j % 10;
        } while (j != order);
    }

    p[strlen(p) - 2] = '\n';
    strcat(p, "]");
    strcpy(history, p);
}

// post the message to the server
int post(char *json, char *dir)
{
    /* first what are we going to send and where are we going to send it? */
    int portno = 5000;
    char *host = "localhost";
    char *message_fmt = "POST %s HTTP/1.0\r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n%s";

    struct hostent *server;
    struct sockaddr_in serv_addr;
    int sockfd, bytes, sent, received, total;
    char message[1024], response[4096];

    int msg_size = strlen(json);
    sprintf(message, message_fmt, dir, msg_size, json);
    printf("Request:\n%s\n", message);

    /* create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        perror("ERROR opening socket");

    /* lookup the ip address */
    server = gethostbyname(host);
    if (server == NULL)
        perror("ERROR, no such host");

    /* fill in the structure */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    /* connect the socket */
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        perror("ERROR connecting");

    /* send the request */
    total = strlen(message);
    sent = 0;
    do
    {
        bytes = write(sockfd, message + sent, total - sent);
        if (bytes < 0)
            perror("ERROR writing message to socket");
        if (bytes == 0)
            break;
        sent += bytes;
    } while (sent < total);

    /* receive the response */
    memset(response, 0, sizeof(response));
    total = sizeof(response) - 1;
    received = 0;
    do
    {
        bytes = read(sockfd, response + received, total - received);
        if (bytes < 0)
            perror("ERROR reading response from socket");
        if (bytes == 0)
            break;
        received += bytes;
    } while (received < total);

    if (received == total)
        perror("ERROR storing complete response from socket");

    /* close the socket */
    close(sockfd);

    /* process response */
    printf("Response:\n%s\n", response);

    char re_code[10];
    for (size_t i = 0; i < 3; i++)
    {
        re_code[i] = response[i + 9];
    }
    int re_int;
    char *ptr;
    re_int = strtol(re_code, &ptr, 10);

    return re_int;
}