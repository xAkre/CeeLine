CC = gcc
CFLAGS = -Wall -g -Iinclude

SRC_DIR = src
OUT_DIR = out
TEST_DIR = tests

# Library source and object files
LIB_SRC = $(wildcard $(SRC_DIR)/lib/*.c)
LIB_OBJS = $(patsubst $(SRC_DIR)/lib/%.c, $(OUT_DIR)/lib/%.o, $(LIB_SRC))
$(OUT_DIR)/lib/%.o: $(SRC_DIR)/lib/%.c | $(OUT_DIR)/lib
	@$(CC) $(CFLAGS) -c $< -o $@

# Library test source and object files
LIB_TEST_SRC = $(wildcard $(TEST_DIR)/lib/*.c)
LIB_TEST_OBJS = $(patsubst $(TEST_DIR)/lib/%.c, $(OUT_DIR)/tests/lib/%.o, $(LIB_TEST_SRC))
$(OUT_DIR)/tests/lib/%.o: $(TEST_DIR)/lib/%.c | $(OUT_DIR)/tests/lib
	@$(CC) $(CFLAGS) -c $< -o $@

TEST_OBJS = $(LIB_TEST_OBJS)

.PHONY: test
test: $(LIB_TEST_OBJS) $(LIB_OBJS) | $(OUT_DIR)/tests
	@for test in $(LIB_TEST_OBJS); do \
		$(CC) $(CFLAGS) $$test $(LIB_OBJS) -o $(OUT_DIR)/tests/$$(basename $$test .o); \
		$(OUT_DIR)/tests/$$(basename $$test .o); \
	done

.PHONY: clean
clean:
	rm -rf $(OUT_DIR)

# Order only prerequisites
$(OUT_DIR)/lib $(OUT_DIR)/tests $(OUT_DIR)/tests/lib:
	@mkdir -p $@