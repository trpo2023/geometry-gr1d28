CFLAGS = -Wall -Werror -I src -g 
CPPFLAGS = -MMD
APP_NAME = main
MAINWAY = src/geometry/
GEOMETRYWAY = src/libgeometry/
OBJECTWAY = obj/src/geometry/
LIBRARYWAY = obj/src/libgeometry/
APP_PATH = $(BIN_DIR)/$(APP_NAME)
BIN_DIR = bin

TEST_NAME = main-test
TEST_PATH = $(BIN_DIR)/$(TEST_NAME)
CTEST_PATH = test/
TEST_OBJ_PATH = obj/test/
TEST_CFLAGS = -Wall -Werror -Ithirdparty -Isrc -MP -g

-include main.d geometry1.d

all:$(APP_PATH)

$(APP_PATH): $(OBJECTWAY)main.o $(LIBRARYWAY)libgeometry.a
	gcc $(CFLAGS) $(CPPFLAGS) -o $@ $^ -lm

$(OBJECTWAY)main.o: $(MAINWAY)main.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -o $@ $^ -lm

$(LIBRARYWAY)libgeometry.a: $(LIBRARYWAY)geometry1.o
	ar rcs $@ $^

$(LIBRARYWAY)geometry1.o: $(GEOMETRYWAY)geometry1.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -o $@ $^ -lm

clean:
	$(RM) $(APP_PATH) $(TEST_PATH)
	find obj -name '*.o' -exec $(RM) '{}' \;
	find obj -name '*.d' -exec $(RM) '{}' \;
	find obj -name '*.a' -exec $(RM) '{}' \;

test:$(TEST_PATH)

$(TEST_PATH): $(TEST_OBJ_PATH)main.o $(TEST_OBJ_PATH)parser_test.o $(LIBRARYWAY)libgeometry.a
	$(CC) $(TEST_CFLAGS) $(LDFLAGS) -o $@ $^ -lm

$(TEST_OBJ_PATH)main.o: $(CTEST_PATH)main.c
	$(CC) -c $(TEST_CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $^ -lm

$(TEST_OBJ_PATH)parser_test.o: $(CTEST_PATH)parser_test.c
	$(CC) -c $(TEST_CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $^ -lm

runtest:$(TEST_PATH)
	./$(TEST_PATH)
