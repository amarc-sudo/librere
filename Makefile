NAME = librere.a

CC = gcc

INCLUDE = .

CFLAGS = #-Werror -Wall -Wextra

CPPFLAGS = -I$(INCLUDE)

SRC = sorting/treesort.c \
      print/putchar.c \
      print/put_int.c \
	  print/putstr.c \
	  print/puterr.c \
	  print/print_address.c \
	  string/strlen.c \
	  string/str_reverse.c \
	  string/charindex.c \
	  string/str_tolower.c  \
	  string/charoccur.c \
	  conversion/atoi.c \
	  conversion/itoa.c \
	  conversion/itohex.c \
	  conversion/itob.c \
	  conversion/btoi.c \
	  conversion/btob.c \
	  util/intlen.c \
	  util/intbaselen.c \
	  OOP/linkedlist/linkedlist.c \

.c.o:
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(<:.c=.o)
	@echo "\033[1;32m[\033[1;35mLibRere\033[1;32m]\033[1;33m created \033[1;32m$(<:.c=.o)\033[0m"

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo  "\033[1;32m[\033[1;35mLibRere\033[1;32m] \033[1;35m$(NAME) \033[0m \033[1;33mhas been successfully created!\033[0m"

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
