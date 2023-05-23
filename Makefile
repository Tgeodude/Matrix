CC= g++ 
CFLAGS= -Wall -Wextra -Werror
STANDART= -std=c++17
TESTFLAGS=-lgtest
TESTFILES= *.cc

all: test gcov_report

s21_matrix_oop.a: build_lib 

build_lib: objects
	@ar rc s21_matrix_oop.a s21_matrix_oop.o
	@ranlib s21_matrix_oop.a

objects:
	@$(CC) $(CFLAGS) $(STANDART) -c s21_matrix_oop.cpp

test: s21_matrix_oop.a test.cc
	@$(CC) $(CFLAGS) $(STANDART) $(TESTFLAGS) $(TESTFILES) s21_matrix_oop.a -o unit_tests
	@./unit_tests

check: test
	@CK_FORK=no leaks --atExit -- ./unit_tests

clean:
	rm -rf *.o *.out s21_matrix_oop.a unit_tests
	rm -rf *.gcda *.gcno report gcov_report.* gcov_report *.info

rebuild: clean all

gcov_report: clean
	g++ $(STANDART) --coverage test.cc s21_matrix_oop.cpp -o gcov_report -lgtest -lstdc++
	./gcov_report
	lcov -t "stest" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	open ./report/index.html
