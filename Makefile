CC = gcc
CFLAGS = -I./arquivos

# Coletar todos os arquivos .c da pasta arquivos
SRC_ARQUIVOS = $(wildcard ./Arquivos/*.c)

all: admin usuario

admin: ./Administrador/main.c $(SRC_ARQUIVOS)
	$(CC) ./Administrador/main.c $(SRC_ARQUIVOS) -o admin $(CFLAGS)

usuario: ./Usuario/main.c $(SRC_ARQUIVOS)
	$(CC) ./Usuario/main.c $(SRC_ARQUIVOS) -o usuario $(CFLAGS)

clean:
	rm -f admin usuario
