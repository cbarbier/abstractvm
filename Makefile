# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/17 14:10:08 by cbarbier          #+#    #+#              #
#    Updated: 2019/02/22 16:26:06 by cbarbier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
# DIRECTORIES                                                                  #
# ---------------------------------------------------------------------------- #

DIR_SRCS	= srcs
DIR_INCS	= incs
DIR_LIBS	= libs
DIR_OBJS	= .objs

# ---------------------------------------------------------------------------- #
# EXTERNAL TOOLS SETTINGS                                                      #
# ---------------------------------------------------------------------------- #

CC			= clang++
AR			= ar
ARFLAGS		= rc
RM			= /bin/rm -rf

# ---------------------------------------------------------------------------- #
# BIN & SRCS & HDRS VARIABLES                                                  #
# ---------------------------------------------------------------------------- #

NAME		= abstractvm

SRCS = \
		main.cpp						\
		AbstractVM.cpp					\
		Utils.cpp						\
		Analyzer.cpp					\
		Operand.cpp						\
		AVMException.cpp				\


HDRS = \
		AbstractVM.hpp					\
		Utils.hpp						\
		Analyzer.hpp					\
		Operand.hpp						\
		IOperand.hpp					\
		AVMException.hpp				\

# ---------------------------------------------------------------------------- #
# /!\ SHELL COLOR      /!\                                                     #
# ---------------------------------------------------------------------------- #

RED   =		\x1B[31m
GRN   =		\x1B[32m
YEL   =		\x1B[33m
BLU   =		\x1B[34m
MAG   =		\x1B[35m
CYN   =		\x1B[36m
WHT   =		\x1B[37m
RST   =		\x1B[0m

# ---------------------------------------------------------------------------- #
# COMPILATION SETTINGS                                                         #
# ---------------------------------------------------------------------------- #

LIBS		= \

LDFLAGS		= \

LDLIBS		= \

CPPFLAGS	= \
			-I$(DIR_INCS)							\

FRAMEWORKS =  \

CFLAGS		= \
			-Wall -Werror -Wextra \
			-pedantic             \
			-Wunreachable-code    \
			-pedantic-errors	  \
			-O2                   \
			-fsanitize=address    \


# ---------------------------------------------------------------------------- #
# PREFIX DIRECTORIES TO VARIABLES                                              #
# ---------------------------------------------------------------------------- #

C_SRCS = $(addprefix $(DIR_SRCS)/,$(SRCS))
O_SRCS = $(addprefix $(DIR_OBJS)/,$(SRCS:.cpp=.o))
H_HDRS = $(addprefix $(DIR_INCS)/,$(HDRS))


$(DIR_OBJS)	:
	@mkdir -p $(DIR_OBJS)

# ---------------------------------------------------------------------------- #
# RULES                                                                        #
# ---------------------------------------------------------------------------- #

all : $(NAME)

$(DIR_OBJS)/%.o	:	$(DIR_SRCS)/%.cpp $(H_HDRS)
	$(CC) $(CFLAGS) -c $< $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)  $(FRAMEWORKS) -o $@
			
$(NAME)		: $(DIR_OBJS) $(O_SRCS) $(LIBS) $(H_HDRS)
	$(CC) $(O_SRCS) -o $(NAME) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(FRAMEWORKS)

clean		:
	$(RM) $(DIR_OBJS)
#   $(RM) $(DIR_DEPS)


fclean		: clean
	$(RM)	$(NAME)

re			: fclean all


# ---------------------------------------------------------------------------- #
# EXTRA OPTIONAL RULES                                                         #
# ---------------------------------------------------------------------------- #

.PHONY	:	all clean fclean re $(DIR_OBJS)/%.o $(DIR_DEPS)/%.d libs

# ---------------------------------------------------------------------------- #
