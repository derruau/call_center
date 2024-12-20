TARGET_EXEC := call_center

BUILD_DIR := ./build
SRC_DIR := ./src
HEADER_DIR := ./include

ifneq (,$(findstring w, $(MAKEFLAGS)))
FIND = C:/msys64/usr/bin/find
LNKFLAGS = -lregex
else
FIND = find
LNKFLAGS = 
endif

# Recursively finds any C files in $(SRC_DIR) 
SRCS = $(shell $(FIND) $(SRC_DIR) -name '*.c')

# Every files in $(SRCS) but as object files with extension .c.o
OBJS = $(SRCS:%=$(BUILD_DIR)/%.o)

# Every files in $(OBJS) but as dependency files with extenion .c.d
DEPS = $(OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS = $(shell $(FIND) $(HEADER_DIR) -type d)
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA
# This makes gcc aware that those folders contain header files
INC_FLAGS = $(addprefix -I,$(INC_DIRS))

# The -MMD and -MP flags together autogenerate Makefiles
# These files will have .d instead of .o as the output.
CPPFLAGS = $(INC_FLAGS) -MMD -MP

# Final build step
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	@echo Linking...
	@$(CXX) $(OBJS) $(LNKFLAGS) -o $@ $(LDFLAGS)
	@echo
	@echo Build Complete!

# Intermediate build step
$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@echo Assembling '$(shell basename -s .c.o $@)'...
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@rm -r $(BUILD_DIR)
	@mkdir $(BUILD_DIR) 
	@echo Cleaned build directory !

.PHONY: debug
debug: clean
debug: CPPFLAGS += -ggdb -g
debug: $(BUILD_DIR)/$(TARGET_EXEC)

# Includes the .d makefiles
-include $(DEPS)