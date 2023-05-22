RED		=	"\x1B[31m"
GRN		=	"\x1B[32m"
YEL		=	"\x1B[33m"
BLU		=	"\x1B[34m"
MAG		=	"\x1B[35m"
CYN		=	"\x1B[36m"
WHT		=	"\x1B[37m"
RESET	=	"\x1B[0m"
CLE 	=	\e[1;1H\e[2J

NAME	=	philo

# Compiler and flags
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -g -pthread -fsanitize=thread
RM		=	rm -f

#-fsanitize=thread


#-Wall -Werror -Wextra -FD_CLOEXEC
#-fsanitize=address
#--recurse-submodules

# Sources are all .c files
SRCS	=	\
			task.c\
			utils.c\
			philo.c\
			verif.c\
			ft_free.c\
			utils_ph.c\
			main_utils.c\

OBJS	=	$(SRCS:.c=.o)

USER = $(shell whoami)

all: $(NAME)
	@echo $(shell reset)$(GRN)
	@echo "				$(NAME) made by anboisve\n "
	@cat .logo.txt
	@echo $(CYN) "\n\n			correction is made by $(USER)\n\n " $(RESET)
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) -c $(SRCS)


# Generates output file
# Removes objects
clean:
	@$(RM) $(OBJS)
	@echo $(shell clear)
	@echo -n $(GRN)
	@echo clean *.o$(RESET)

# Removes objects and executables
fclean: clean
	@$(RM) $(NAME)
	@echo $(shell clear)$(GRN)clean all$(RESET)

mc: all clean

# Removes objects and executables and remakes
re: fclean all

.PHONY: all clean fclean re