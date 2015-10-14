export TOP_DIR = /mnt/linuxProject/TMSxxTC/TMSxxTC-1.1.0.xxx-Bate

export OUTPUT  = ../script/output2.mk

include $(OUTPUT)


include filelist.mk

export SRCS
export OUTPUT_DIR
# SRCS = main.c

# OBJS = main.o

OBJS = 	$(patsubst %.S,%.o,\
		$(patsubst %.cpp,%.o,\
		$(patsubst %.c,%.o,$(SRCS))))

ARCH=x86
# go:
# 	echo $(OUTPUT_DIR)
all: $(ARCH)
	
	# @$(MAKE) -C $(TOP_DIR)

include $(TOP_DIR)/script/rules.mk


# include $(TOP_DIR)/script/rules.mk


# clean: 
# 	$(MAKE) -C ./
clean:
	echo $(TOP_DIR)
	rm 	$(OBJS) \
		$(OUTPUT_DIR)/$(NAME_DIS) \
		$(OUTPUT_DIR)/$(NAME_ELF) \
		core