
INCDIR = -I ./
INCDIR += -I ./test

CC=gcc

bezier_test:
	$(CC) bezier.c test/bezier_test.c -o test/bezier_test.out $(INCDIR) -lm

planner_test:
	$(CC) planner.c test/planner_test.c -o test/planner_test.out $(INCDIR)

tests: bezier_test planner_test