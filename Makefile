myreplyservice: myreplyservice.o
	$(CC) $(LDFLAGS) myreplyservice.o -o myreplyservice -luci -L/home/gaganjotbhullar/Desktop/openwrt/staging_dir/target-mips_24kc_musl/root-ar71xx/lib/
myreplyservice.o: myreplyservice.c
	$(CC) $(CFLAGS) -c myreplyservice.c
clean:
	rm *.o myreplyservice
