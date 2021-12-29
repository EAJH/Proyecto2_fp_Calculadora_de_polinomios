CC=gcc #definimos el compilador a usar
EXE=polinomio #nombre del ejecutable

CDEBUG= -g -Wall #definir las banderas de depuración
CSTD= -std=c99 # definir el estándar del lenguaje a utilizar

CFLAGS = -Wno-deprecated-register -O0 $(CDEBUG) $(CSTD)#No advierte sobre el uso de características obsoletas
#CLIBS = -lm #Enlace con la biblioteca matemática

COBJ = main funciones #Nombres de los archivos a compilar

FILES = $(addsuffix .c, $(COBJ))#crea los archivos con terminación .c
OBJS = $(addsuffix .o, $(COBJ))
CLEANLIST = $(addsuffix .o, $(COBJ))

.PHONY: all
all: wc

wc: $(FILES)
	$(MAKE) $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS) $(CLIBS)

.PHONY: clean
clean:	
	rm -rf $(CLEANLIST)