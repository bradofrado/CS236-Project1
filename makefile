
# makefile for project 1 example tests

NUM:=1

numbers:=10 11 12 13 14 15 16 17 61 62

tests:=project$(NUM)-tests

.SILENT: all run

all: run
	@rm $(tests)/out.txt

run:
	for number in $(numbers) ; \
	do \
		echo "Running input $$number" ; \
		./lab$(NUM) < $(tests)/in$$number.txt > $(tests)/my$$number.txt ; \
		diff $(tests)/out$$number.txt $(tests)/my$$number.txt || (echo "diff failed on test $$number \n") ; \
	done

compile:
	g++ -std=c++17 -g *.cpp -o lab$(NUM)

