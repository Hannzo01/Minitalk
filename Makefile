CLIENT_SRC = client.c
SERVER_SRC = server.c

CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Define executable names
NAME = client server


# Rule to create object files
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Default rule to build both programs

all : $(NAME)

#client: Compiles and links client.c into the client executable.
# Rule for building the client
client: $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) -o client

server : $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) -o server

clean :
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ)

#Removes executables (client and server) in addition to object files
fclean : clean
	rm -f $(NAME)

re: fclean all	