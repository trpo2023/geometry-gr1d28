CFLAGS = -Wall -Werror
CPPFLAGS = -MMD
MAINWAY = src/geometry/
GEOMETRYWAY = src/libgeometry/
OBJECTWAY = obj/src/geometry/
LYBRARYWAY = obj/src/libgeometry/
-include main.d geometry1.d

all:bin/main

bin/main: $(OBJECTWAY)main.o $(LYBRARYWAY)libgeometry.a
	cc $(CFLAGS) $(CPPFLAGS)  -o $@ $^ -lm

$(OBJECTWAY)main.o: $(MAINWAY)main.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -o $@ $^

$(LYBRARYWAY)libgeometry.a: $(OBJECTWAY)geometry1.o
	ar rcs $@ $^

$(OBJECTWAY)geometry1.o: $(GEOMETRYWAY)geometry1.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -o $@ $^ -lm

clean: $(OBJECTWAY)*.o $(LYBRARYWAY)*.a
	rm $^

