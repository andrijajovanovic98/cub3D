CC := cc
CFLAGS := -Wall -Wextra -Werror

NAME := libft.a

SRC := ft_atoi.c ft_calloc.c ft_isalpha.c ft_isdigit.c ft_memchr.c ft_memcpy.c ft_memset.c \
		  ft_strdup.c ft_strlcpy.c ft_strncmp.c ft_toupper.c ft_bzero.c ft_isalnum.c ft_isascii.c \
		  ft_isprint.c ft_memcmp.c ft_memmove.c ft_strchr.c ft_strrchr.c ft_strlcat.c ft_strlen.c \
		  ft_strnstr.c ft_tolower.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
		  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_strmapi.c ft_striteri.c ft_putnbr_fd.c \
		  ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
		  ft_lstclear.c ft_lstiter.c ft_lstmap.c get_next_line.c get_next_line_utils.c stringlist.c \
		  ft_printf/char_str_handlers.c ft_printf/format_parser.c ft_printf/ft_itoa.c ft_printf/ft_printf.c \
		  ft_printf/ft_itoa_base.c ft_printf/numeric_handlers.c


OBJDIR := obj
OBJ := $(patsubst %.c, $(OBJDIR)/%.o, $(SRC))
DEPS := $(patsubst %.c, $(OBJDIR)/%.d, $(SRC))

-include $(DEPS)

all: $(NAME)

$(NAME): $(OBJ)
	@echo " [✓]"
	ar rcs $(NAME) $(OBJ)

$(OBJDIR)/%.o: %.c display | $(OBJDIR)/ft_printf
	@echo -n "■"
	@$(CC) -MMD -MP $(CFLAGS) -I. -c $< -o $@

$(OBJDIR)/ft_printf:
	mkdir -p $(OBJDIR)/ft_printf

display:
	@echo -n "Compiling libft:   "

clean:
	@if [ -d "$(OBJDIR)/ft_printf" ]; then \
		echo -n "Removing libft .o and .d files."; \
		rm -f $(OBJ) $(DEPS); \
		echo "[✓]"; \
		if [ -z "$$(ls -A $(OBJDIR)/ft_printf)" ]; then \
			echo -n "Removing libft/obj/ft_printf/ directory."; rmdir $(OBJDIR)/ft_printf; echo "[✓]"; \
			if [ -z "$$(ls -A $(OBJDIR))" ]; then \
				echo -n "Removing libft/obj/ directory."; rmdir $(OBJDIR); echo "[✓]"; \
			else \
				echo "Unexpected files in libft/obj/ directory. Manual cleanup required."; \
			fi \
		else \
			echo "Unexpected files in libft/obj/ft_printf/ directory. Manual cleanup required."; \
		fi \
	elif [ -d "$(OBJDIR)" ]; then \
		echo -n "Removing libft .o and .d files."; \
		rm -f $(OBJ) $(DEPS); \
		echo "[✓]"; \
		if [ -z "$$(ls -A $(OBJDIR))" ]; then \
			echo -n "Removing libft/obj/ directory."; rmdir $(OBJDIR); echo "[✓]";\
		else \
			echo "Unexpected files in libft/obj/ directory. Manual cleanup required."; \
		fi \
	else \
		echo "Removing libft/obj/ directory [❌] (doesn't exist)"; \
	fi

fclean: clean
	if [ -f $(NAME) ]; then \
		echo -n "Deleting libft.a"; \
		rm -f $(NAME); \
		echo "[✓]"; \
	else \
		echo "Removing libft.a [❌] (doesn't exist)"; \
	fi

re: fclean all

.PHONY: all clean fclean re
.INTERMEDIATE: display