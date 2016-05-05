# include ../rule.mk
CROSS_COMPILE=/opt/iTop-4412/4.3.2/bin/arm-linux-
CC=$(CROSS_COMPILE)gcc
all:
	$(CC) -o randmac.elf randmac.c $(LIB_DIR) $(LFLAGS) -std=gnu99
	$(CC) -o udiskupdate.elf udiskupdate.c $(LIB_DIR) $(LFLAGS) -std=gnu99
