# all *.c file in current directory
SRCS    = $(wildcard *.c) $(wildcard *.cpp)
# one *.o file for every source file
OBJS    = $(addsuffix .o, $(basename $(SRCS)))
# targets are *.o files in the bin dir
TARGETS = $(foreach o, $(OBJS), $(addprefix ${BIN_DIR}/, $(o)))

.PHONY: all

all: $(TARGETS)
	@echo Object\(s\) '$(TARGETS)' Built!

# Compile the source
$(BIN_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

$(BIN_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

