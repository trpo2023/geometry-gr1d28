CFLAGS = -Wall -Werror -I src
CPPFLAGS = -MMD
APP_NAME = main
MAINWAY = src/geometry/
GEOMETRYWAY = src/libgeometry/
OBJECTWAY = obj/src/geometry/
LIBRARYWAY = obj/src/libgeometry/
APP_PATH = $(BIN_DIR)/$(APP_NAME)
BIN_DIR = bin

-include main.d geometry1.d

all:$(APP_PATH)

$(APP_PATH): $(OBJECTWAY)main.o $(LIBRARYWAY)libgeometry.a
	cc $(CFLAGS) $(CPPFLAGS) -o $@ $^ -lm

$(OBJECTWAY)main.o: $(MAINWAY)main.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -o $@ $^

$(LIBRARYWAY)libgeometry.a: $(LIBRARYWAY)geometry1.o
	ar rcs $@ $^

$(LIBRARYWAY)geometry1.o: $(GEOMETRYWAY)geometry1.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -o $@ $^ -lm

clean:
	$(RM) $(APP_PATH)
	find obj -name '*.o' -exec $(RM) '{}' \;
	find obj -name '*.d' -exec $(RM) '{}' \;
	find obj -name '*.a' -exec $(RM) '{}' \;


