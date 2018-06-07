myreplyservice: myreplyservice.o
	$(CC) $(LDFLAGS) myreplyservice.o -o myreplyservice -luci
myreplyservice.o: myreplyservice.c
	$(CC) $(CFLAGS) -c myreplyservice.c
clean:
	rm *.o myreplyservice
