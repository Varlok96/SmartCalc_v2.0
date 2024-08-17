CC = g++ -g -Wall -Werror -Wextra 
FLAGS = -std=c++17

GCOVFLAGS = -L. --coverage

OS = $(shell uname)

ifeq ($(OS), Linux)
	CTEST_FLAGS = -lgtest -lgmock -pthread
else
	CTEST_FLAGS = -lgtest
endif

all: install gcov_report

install: uninstall
	mkdir -p ../build
	qmake6 SmartCalc/SmartCalc.pro -o ../build/Makefile
	cd ../build; make > /dev/zero 2> /dev/zero

uninstall: clean
	rm -rf ../build

test: clean
	$(CC) $(FLAGS) -c ./tests/test_pars.cpp ./exampleModel.cpp
	$(CC) $(FLAGS) test_pars.o exampleModel.o -o test $(CTEST_FLAGS)
	./test

dvi:
	open dvi.html

dist:
	cd .. && tar -czvf SmartCalc.tar src

gcov_report: clean test
	@$(CC) -fprofile-arcs -ftest-coverage ./tests/test_pars.cpp ./exampleModel.cpp -o gcov_report $(FLAGS) $(CTEST_FLAGS)
	@./gcov_report 
	@lcov -o coverage.info -c -d .
	@genhtml coverage.info --output-directory report
	@open ./report/index.html
	@rm -rf *.gcno *.gcda *.gcov

clang:
	clang-format -i -style=Google ./*.cpp ./tests/*.cpp ./SmartCalc/*.cpp
	clang-format -i -style=Google ./*.h ./SmartCalc/*.h

valgrind: test
	CK_FORK=no valgrind  --leak-check=full  --track-origins=yes  ./test

clean:
	@rm -rf *.o *.a *test gcov_report *.gcno *.gcda *.gcov *.info ./report
