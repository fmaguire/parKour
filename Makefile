CC := g++
SRCDIR := src
BUILDDIR := build
TARGET := bin/parKour

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))

OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -Wall
LIB := -lmlpack 
INC := -I/usr/include/libxml2 
OUT := $(wildcard cluster*.fq)
TEST_FILES := test/test_files/test_r1.fastq test/test_files/test_r2.fastq

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
	$(TARGET) $(TEST_FILES) 

valgrind: $(TARGET)
	valgrind $(TARGET) $(TEST_FILES)

.PHONY: clean

