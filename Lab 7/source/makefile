all: test_1 test_2 test_3 test_4 count_multiples

test_1: test-threads_1.c
	gcc -o test_1 test-threads_1.c -lpthread

test_2: test-threads_2.c
	gcc -o test_2 test-threads_2.c -lpthread

test_3: test-threads_3.c
	gcc -o test_3 test-threads_3.c -lpthread

test_4: test-threads_4.c
	gcc -o test_4 test-threads_4.c -lpthread

count_multiples: exercise-8-serial.c
	gcc -o count_multiples exercise-8-serial.c -lpthread