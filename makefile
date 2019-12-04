final: final.o CPUsched.o pcb.o queue.o p.o
	gcc -o final final.o CPUsched.o pcb.o queue.o p.o

final.o: final.c
	gcc -c final.c