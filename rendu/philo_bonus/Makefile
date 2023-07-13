# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rahmed <rahmed@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/24 13:51:13 by rahmed            #+#    #+#              #
#    Updated: 2022/01/31 14:57:23 by rahmed           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libphilosophers.a

SRCS		=	philosophers_bonus.c \
				timing_bonus.c \
				useful_bonus.c \
				process_bonus.c \
				state_bonus.c \
				utils_bonus.c

MSRC		= 	philosophers_bonus.c

NB_PHILOSOPHERS		=	200
TIME_TO_DIE_MS		=	2500
TIME_TO_EAT_MS		=	200
TIME_TO_SLEEP_MS	=	60
NB_EACH_PHILO_EAT	=	10

#ARG		=	${NB_PHILOSOPHERS} ${TIME_TO_DIE_MS} ${TIME_TO_EAT_MS} ${TIME_TO_SLEEP_MS}
ARG		=	${NB_PHILOSOPHERS} ${TIME_TO_DIE_MS} ${TIME_TO_EAT_MS} ${TIME_TO_SLEEP_MS} ${NB_EACH_PHILO_EAT}
#ARG		=

OBJS		=	${SRCS:.c=.o}

CC			=	gcc
THREAD		=	-lpthread
RM			=	rm -f
AR			=	ar rcs
CFLAGS		=	-Wall -Wextra -Werror
FSFLAGS		=	-fsanitize=address

HEADER		=	-I.
LDFLAGS		=	-L.

TARGET_SRV	=	philo_bonus

TXT_RED		=	\033[1;31m
TXT_GREEN	=	\033[1;32m
TXT_YELLOW	=	\033[1;33m
TXT_BLUE	=	\033[1;34m
TXT_MAGENTA	=	\033[1;35m
TXT_CYAN	=	\033[1;36m
BCK_RED		=	\033[0;41m
BCK_GREEN	=	\033[0;42m
BCK_YELLOW	=	\033[0;43m
BCK_BLUE	=	\033[0;44m
BCK_MAGENTA	=	\033[0;45m
BCK_CYAN	=	\033[0;46m
FANCY_RESET	=	\033[0m

%.o			:	%.c
				@echo "${TXT_BLUE}"
				${CC} -c ${CFLAGS} -o $@ $< ${HEADER}
				@echo "${FANCY_RESET}"

${NAME}		:	${OBJS}
				@echo "${TXT_YELLOW}"
				${AR} ${NAME} ${OBJS}
				make exec
				@echo "${FANCY_RESET}"

all			:	${NAME}
#bonus 		:

clean		:
				@echo "${TXT_YELLOW}"
				@echo "\n~~~~~~~~~~ CLEAN ~~~~~~~~~~"
				@echo "${TXT_RED}"
				${RM} ${OBJS}
				@echo "$(FANCY_RESET)"

fclean		:
				@echo "${TXT_YELLOW}"
				@echo "\n~~~~~~~~~~ FCLEAN ~~~~~~~~~~"
				@echo "${TXT_RED}"
				${RM} ${OBJS}
				@echo "${TXT_MAGENTA}"
				${RM} ${NAME}
				@echo "$(FANCY_RESET)"

re			:	fclean all

.PHONY		:	all clean fclean re
############### PARTIE TEST ###############
test		:
				make all
				@echo "${TXT_YELLOW}"
				@echo "\n~~~~~~~~~~   TEST    ~~~~~~~~~~"
				@echo "${FANCY_RESET}"
				./${TARGET_SRV} ${ARG}

exec		:	${NAME}
				@echo "${TXT_YELLOW}"
				@echo "\n~~~~~~~~~~ COMPILATION ~~~~~~~~~~"
				@echo "${TXT_GREEN}"
				${CC} ${CFLAGS} ${LDFLAGS} ${NAME} ${MSRC} -o ${TARGET_SRV} ${THREAD}
				@echo "${FANCY_RESET}"

norm		:
				@echo "${TXT_YELLOW}"
				@echo "\n~~~~~~~~~~ CHECK NORM ~~~~~~~~~~"
				@echo "${TXT_GREEN}"
				norminette *.c -R CheckForbiddenSourceHeader
				norminette *.h -R CheckDefine
				@echo "${FANCY_RESET}"

flush		:	fclean
				@echo "${TXT_YELLOW}"
				@echo "\n~~~~~~~~~~ Extra-CLEANING  ~~~~~~~~~~"
				@echo "${TXT_RED}"
				${RM} ${TARGET_SRV}
				${RM} .DS_STORE
				${RM} *.out
				${RM} *.a
				${RM} -R *.dSYM
				@echo "${FANCY_RESET}"
###########################################
