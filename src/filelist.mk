# # 最小系统代码
SRCS += ../shell/minishell_core.c 

SRCS += ../src/main.c \
		../osnet/bipbuffer.c \
		../osnet/epollserver.c \
		../osnet/ossocket.c \
		../src/ep_app.c \
		../src/tms_app.c \
		../src/tmsxxdb.c 
		
		
		

SRCS += ../shell/cmd/cmd_server.c \
		../shell/cmd/cmd_tr485.c 
		

SRCS += ../protocol/glink.c \
		../protocol/tmsxx.c \
		../shell/cmd/cmd_tmsxx.c 
		# protocol/MD5.cpp
# SRCS +=protocol/tr485.c \
# 		protocol/tr485_hw.c 

# 最小系统代码
# SRCS +=  \
# 		osnet/bipbuffer.c \
# 		osnet/TMSepollserver.c \
# 		osnet/ossocket.c \
		# src/ep_app.c
