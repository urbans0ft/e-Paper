SRC_DIRS = lib/Config lib/Fonts lib/GUI \
		   examples
TARGET   = epd

export BIN_DIR = $(CURDIR)/bin

# compile and link settings
export CC      = g++
INCLUDES       = $(addprefix -I $(CURDIR)/, $(SRC_DIRS))
export CFLAGS  = -c -g -Wall $(INCLUDES) -DDEBUG
LFLAGS         = -lbcm2835 -lm

# create bin dir
$(shell mkdir -p ${BIN_DIR})

.PHONY: clean all $(SRC_DIRS)

all: $(TARGET)

$(TARGET): $(SRC_DIRS)
	$(CC) -o $(TARGET) bin/*.o $(LFLAGS)

$(SRC_DIRS):
	@echo -----------------
	@cd $@ && $(MAKE) --no-print-directory

clean:
	-rm -rf $(TARGET) $(BIN_DIR)
