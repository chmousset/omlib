
INCDIR = -I ./
INCDIR += -I ./test

CC=gcc
COPT=-Wall -O2

bezier_test:
	$(CC) bezier.c test/bezier_test.c -o test/bezier_test.out $(INCDIR) -lm $(COPT)
	
tsfifo_test:
	$(CC) tsfifo.c test/tsfifo_test.c -o test/tsfifo_test.out $(INCDIR) $(COPT)

planner_test:
	$(CC) planner.c test/planner_test.c -o test/planner_test.out $(INCDIR) $(COPT)

tests: bezier_test planner_test tsfifo_test

clean:
	rm test/*.out