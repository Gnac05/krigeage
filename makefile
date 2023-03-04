SRC = main.c fonc_g.c metho_krigeage.c power.c
LEADING = main.h
EXE = krigeage
CC = gcc
O = -o
BLAS = -lblas
LAPACK = -llapacke
Clean = clean

krigeage : $(Clean)
	$(CC) $(SRC) $(LEADING) $(O) $(EXE) $(BLAS) $(LAPACK)
	./$(EXE) 

clean: 
	touch $(EXE)
	rm $(EXE)
	
