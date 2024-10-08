NAME = libftprintf.a

HEADERS = /libft.h ft_printf.h minitalk.h

SOURCES = sources_ft_printf/ft_printf.c sources_ft_printf/ft_putcharlen.c sources_ft_printf/ft_putnbrhexlen.c \
		sources_ft_printf/ft_putnbrlen.c sources_ft_printf/ft_putptrlen.c sources_ft_printf/ft_putstrlen.c \
		sources_libft/ft_strlen.c sources_libft/ft_atoi.c sources_libft/ft_itoa.c sources_libft/ft_isdigit.c \

OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -Werror -Wall -Wextra

CC = cc

AR = ar rcs

RM = rm -f

# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

all: $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	$(AR) $@ $^
	@echo "$(YELLOW) **** >>>>> Compiling: $< <<<<< **** $(DEF_COLOR)"
	@echo ""
	@echo "$(MAGENTA)>>>>> ft_printf compiled!$(DEF_COLOR)"

all: client.c
	@echo "$(GREEN)          () ()$(DEF_COLOR)"
	@echo "$(GREEN)          (>.<) $(DEF_COLOR)"
	@echo "$(GREEN)          ( . ) $(DEF_COLOR)"
	@echo "$(GREEN)           n_n $(DEF_COLOR)"
	$(CC) $(CFLAGS) client.c $(NAME) -o client
	@echo "$(MAGENTA)>>>>> Client compiled!$(DEF_COLOR)"
	$(CC) $(CFLAGS) server.c $(NAME) -o server
	@echo "$(MAGENTA)>>>>> Server compiled!$(DEF_COLOR)"

clean:
	$(RM) $(OBJECTS)
	@echo "$(MAGENTA)Cleaned OBJECTS for ft_printf!$(DEF_COLOR)"
	
fclean: clean
	$(RM) $(NAME)
	@echo "$(MAGENTA)Cleaned NAME for ft_printf!$(DEF_COLOR)"


re: fclean all

.PHONY: clean fclean all re
