all:
	gcc -Wall --pedantic src/*.c -o bin/gauss

test: all
	@echo "\n    TEST 1: Dane prawidlowe dla 2x2 i 5x5"
	@./bin/gauss dane/prawidlowe2A.txt dane/prawidlowe5A.txt || echo "Prawidlowe dzialanie programu"

	@echo "\n    TEST 2: Element diagonalny równy 0" || echo "Prawidlowe dzialanie programu"
	@./bin/gauss dane/zero.txt zero1.txt

	@echo "\n    TEST 3: Macierz osobliwa"
	@./bin/gauss dane/osobliwa.txt dane/osobliwa1.txt || echo "Kod bledu - test zakonczyl sie prawidlowo"

	@echo "\n    TEST 4: Nieprawidlowy format macierzy "
	@./bin/gauss dane/zlyformat.txt dane/zlyformat1.txt || echo "Blad formatu - test zakonczyl sie prawidlowo"
