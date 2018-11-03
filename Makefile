# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbarbier <cbarbier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/17 14:10:08 by cbarbier          #+#    #+#              #
#    Updated: 2018/10/19 10:17:22 by cbarbier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
# PROJECT CONFIGURATION                                                        #
# ---------------------------------------------------------------------------- #
# - The 'DIR*' variables describe all directories of the project.              #
# ---------------------------------------------------------------------------- #

DIR_SRCS	= srcs
DIR_INCS	= incs
DIR_LIBS	= libs
DIR_OBJS	= .objs

# ---------------------------------------------------------------------------- #
# EXTERNAL TOOLS SETTINGS                                                      #
# ---------------------------------------------------------------------------- #
# - Set the default external programs.                                         #
# ---------------------------------------------------------------------------- #

CC			= clang++
AR			= ar
ARFLAGS		= rc
RM			= rm -rf

# ---------------------------------------------------------------------------- #
#                                                                              #
# TARGET SETUP                                                                 #
#                                                                              #
# ---------------------------------------------------------------------------- #
# - The 'NAME' variable must contain the expected name of the output target.   #
# - The 'SRCS' variable must contain the list of the source files without the  #
# base prefix of the directory.                                                #
# ---------------------------------------------------------------------------- #

NAME		= abstractvm

SRCS = \
		main.cpp						\
		AbstractVM.cpp					\
		Utils.cpp						\
		Analyzer.cpp					\
		Operand.cpp						\


HDRS = \
		AbstractVM.hpp					\
		Utils.hpp						\
		Analyzer.hpp					\
		Operand.hpp						\
		IOperand.hpp					\

# ---------------------------------------------------------------------------- #
# /!\ COLOR FOR PRINTF /!\                                                     #
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
# PROJECT COMPILATION                                                          #
# ---------------------------------------------------------------------------- #
# - The 'LIBS' tells the compiler where to find libraries.                     #
# - The 'LDFLAGS' tells the linker where to find external libraries (-L flag). #
# - The 'LDLIBS' tells the linker the prefix of external libraries (-l flag).  #
# - The 'CPPFLAGS' tells the compiler where to find preprocessors (-I flag).   #
# - The 'CFLAGS' configures the compiler options.                              #
# ---------------------------------------------------------------------------- #

LIBS		= \

LDFLAGS		= \

LDLIBS		= \

CPPFLAGS	= \
			-I$(DIR_INCS)							\

FRAMEWORKS =  \

CFLAGS		= \
			-Wall -Werror -Wextra -O2 -pedantic -Wunreachable-code -pedantic-errors	\
			-g3							\
			-fsanitize=address					\


# ---------------------------------------------------------------------------- #
# /!\ SOURCE NORMALIZATION AND COMPILATION RULES /!\                           #
# ---------------------------------------------------------------------------- #

COMPILE.cpp	= \
			$(CC) $(CFLAGS) $(CPPFLAGS) -c \

C_SRCS = $(addprefix $(DIR_SRCS)/,$(SRCS))
O_SRCS = $(addprefix $(DIR_OBJS)/,$(SRCS:.cpp=.o))
H_HDRS = $(addprefix $(DIR_INCS)/,$(HDRS))


$(DIR_OBJS)	:
	@mkdir -p $(DIR_OBJS)

# ---------------------------------------------------------------------------- #
# PUBLIC RULES                                                                 #
# ---------------------------------------------------------------------------- #
# The rules must contain at least :                                            #
# - all        make libs and target                                            #
# - $(NAME)    make binaries and target                                        #
# - libs       build static libraries                                          #
# - clean      remove binaries                                                 #
# - fclean     remove binaries and target                                      #
# - fcleanlibs apply fclean rule on libraries                                  #
# - re         remove binaries, target and libraries and build the target      #
#                                                                              #
# To compile a static library, the $(NAME) rule should be :                    #
#     '$(AR) $(ARFLAGS) $(NAME) $(OBJ)'                                        #
#     'ranlib $(NAME)'                                                         #
#                                                                              #
# To compile a C binary, the $(NAME) rule should be :                          #
#     '$(CC) $(OBJ) -o $(NAME) $(LDFLAGS) $(LDLIBS)'                           #
# ---------------------------------------------------------------------------- #

all : $(NAME)

$(DIR_OBJS)/%.o	:	$(DIR_SRCS)/%.cpp
	$(CC) $(CFLAGS) -c $< $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)  $(FRAMEWORKS) -o $@
			
$(NAME)		: $(DIR_OBJS) $(O_SRCS) $(LIBS) $(H_HDRS)
	$(CC) $(O_SRCS) -o $(NAME) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(FRAMEWORKS)

clean		:
	$(RM) $(DIR_OBJS)
	$(RM) $(DIR_DEPS)


fclean		: clean
	$(RM)	$(NAME)

re			: fclean all

# ---------------------------------------------------------------------------- #

.PHONY	:	all clean fclean re $(DIR_OBJS)/%.o $(DIR_DEPS)/%.d libs

# ---------------------------------------------------------------------------- #
