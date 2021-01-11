# all *.c file in current directory
SRCS    = $(wildcard *.c)
# one *.o file for every source file
OBJS    = $(SRCS:%.c=%.o)
# targets are *.o files in the bin dir
TARGETS = $(foreach o, $(OBJS), $(addprefix ${BIN_DIR}/, $(o)))

.PHONY: all

all: $(TARGETS)
	@echo Object\(s\) '$(TARGETS)' Built!

# Compile the source
$(BIN_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

