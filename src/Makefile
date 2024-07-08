CC = gcc
SOURSE = calculator/s21_calc.c calculator/s21_steck.c calculator/s21_valid.c
GCOVFLAGS= -fprofile-arcs -ftest-coverage
CFLAGS= -Wall -Werror -Wextra -std=c11 -g
TESTFLAGS= -lcheck -lm

ifeq ($(shell uname -s), Linux)
	TESTFLAGS+=-lpthread -lrt -lsubunit
endif


all: clean test

dvi:
	open Document


install:
	cd calculator && make install && cd ..

uninstall:
		rm -rf calculator/calculator

test: clean s21_smartcalc.a
	$(CC) $(CFLAGS) test.c calculator/s21_smartcalc.a -o test $(TESTFLAGS)
	./test

s21_smartcalc.a:
	$(CC) -c calculator/s21_*.c
	ar rcs calculator/s21_smartcalc.a s21_*.o

clean:
	rm -rf calculator/a.out
	rm -rf calculator/a.out*
	rm -rf calculator/*.o
	rm -rf *.o
	rm -rf *.out
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf test
	rm -rf report
	rm -rf calculator/*.a
	rm -rf calculator/*.cfg
	rm -rf calculator/moc_*
	rm -rf build

dist:
	mkdir build
	tar -cf build/dist.tar calculator/calculator

valgrind:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes --log-file="val_out.txt" test

style:
	clang-format -style=Google -i calculator/s21_*.c calculator/s21_*.h *.c
	clang-format -style=Google -n calculator/s21_*.c calculator/s21_*.h *.c

gcov_report: s21_smartcalc.a test.c
	$(CC) $(GCOVFLAGS) test.c calculator/*.c -o report.out $(TESTFLAGS)
	./report.out
	lcov -t "gcov_report" -o coverage_table.info -c -d .
	genhtml -o ./report coverage_table.info

