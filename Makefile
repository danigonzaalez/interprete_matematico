# Compilation
CC=gcc -Wall -g -O1

#Libraries
LIBS = -lm -ldl

# Header Folder
HEADER_FILES_DIR = .

# Localization of headers .h
INCLUDES = -I $(HEADER_FILES_DIR)

# Name of the executable
OUTPUT = executable

# Flex File
FLEX_FILE = analizador_lexico.l

# Bison File
BISON_FILE = analizador_sintactico.y

# Headers .h
HEADERS = $(HEADER_FILES_DIR)/abin.h analizador_sintactico.tab.h lex.yy.h definiciones.h errores.h tabla_simbolos.h comandos.h

# Sources:
SRCS = main.c abin.c analizador_sintactico.tab.c lex.yy.c tabla_simbolos.c errores.c comandos.c

# Files .o:
OBJS = $(SRCS:.c=.o)

# Rules
# Rule 1: generates de exe and the .o
$(OUTPUT): $(OBJS)
	$(CC) -o $(OUTPUT) $(OBJS) $(LIBS)
	
# Rule 2: generates .o when its needed
%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(INCLUDES)
	
# Rule 3: generates the code to Flex
flex:
	flex $(FLEX_FILE)

# Rule 4: generates the code to Bison
bison:
	bison -Wall -d $(BISON_FILE)

# Rule 5: removes the executable 
cleanall: clean
	rm -f $(OUTPUT) 

# Rule 6: removes all the .o and the backup ones (ended in ~)
clean:
	rm -f *.o *~