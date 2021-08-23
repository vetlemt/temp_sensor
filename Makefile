CC = gcc
CFLAGS  = -g -Wall

default: temp

temp:	main.o temp_sensor.o readings.o timev.o transmission.o
	$(CC) $(CFLAGS) -o temp main.o temp_sensor.o readings.o timev.o transmission.o

main.o:  main.c temp_sensor.h readings.h timev.h 
	$(CC) $(CFLAGS) -c main.c

temp_sensor.o:  temp_sensor.c temp_sensor.h readings.h timev.h 
	$(CC) $(CFLAGS) -c temp_sensor.c

readings.o:  readings.c readings.h timev.h 
	$(CC) $(CFLAGS) -c readings.c

timev.o:  timev.c timev.h 
	$(CC) $(CFLAGS) -c timev.c 

transmission.o:  transmission.c readings.h timev.h 
	$(CC) $(CFLAGS) -c transmission.c

clean: 
	$(RM) temp *.o *~
