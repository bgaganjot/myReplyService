#include <stdio.h>
#include <stdlib.h>
#include <uci.h>


int main(int argc, char **argv){
	char path[] = "myreplyservice.default.reply";
	char buffer[80];
	struct uci_ptr ptr;
	struct uci_context *c = uci_alloc_context();

	if(!c) return 1;

	if((uci_lookup_ptr(c, &ptr, path, true) != UCI_OK) || (ptr.o == NULL || ptr.o->v.string==NULL)){
		uci_free_context(c);
		return 2;
	}
	if(ptr.flags & UCI_LOOKUP_COMPLETE) strcpy(buffer, ptr.o->v.string);
	printf("%s\n", buffer);

	ptr.value = "1234";

	if(uci_commit(c, &ptr.p, false) != UCI_OK){
		uci_free_context(c);
		uci_perror(c, "UCI ERROR");
		return 3;
	}

	uci_free_context(c);
	return 0;
}
