CC := g++
SRCDIR := src
BUILDDIR := build
TARGET := bin/parKour

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))

OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -Wall -std=c++11 
LIB := -lmlpack 
INC := -I /usr/include/libxml2 -I include/
OUT := $(wildcard cluster*.fq) run_log
TEST_PARAMS := test/test_files/test_r1.fastq test/test_files/test_r2.fastq 3

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)
	@echo " $(RM) $(OUT)"; $(RM) $(OUT)

# Tests
test: $(TARGET)
	$(TARGET) $(TEST_PARAMS) 

valgrind: $(TARGET)
	valgrind $(TARGET) $(TEST_PARAMS)

.PHONY: clean

