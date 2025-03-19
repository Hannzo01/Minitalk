CLIENT_SRC = client.c
SERVER_SRC = server.c

CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = client server


%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@


all : $(NAME)

client: $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) -o client

server : $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) -o server

clean :
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ)

fclean : clean
	rm -f $(NAME)

re: fclean all	
