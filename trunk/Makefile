all:
	gcc -Wall --pedantic src/*.c -o bin/gauss

test: all
	@echo "\n    TEST 1: Dane poprawne (zwykle)  "
	@./bin/gauss dane/prosteA.txt dane/prosteB.txt

	@echo "\n    TEST 2: Pivot (czyli 0 na przekatnej)  "
	@./bin/gauss dane/A.txt dane/B.txt

	@echo "\n    TEST 3: Macierz osobliwa  "
	@./bin/gauss dane/osobliwaA.txt dane/osobliwaB.txt || echo "Program zakonczyl sie kodem bledu (tak jak mial-prawidlowo)"

	@echo "\n    TEST 4: Zly format badanej macierzy "
	@./bin/gauss dane/zlyformat.txt dane/B.txt || echo "Program wykryl blad formatu(tak jak mial-prawidlowo)"