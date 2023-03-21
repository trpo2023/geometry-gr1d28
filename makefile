CFLAGS = -Wall -Werror
CPPFLAGS = -MMD
MAINWAY = src/geometry/
GEOMETRYWAY = src/libgeometry/
OBJECTWAY = obj/src/geometry/
LYBRARYWAY = obj/src/libgeometry/

main: $(OBJECTWAY)main.o $(LYBRARYWAY)libgeometry.a
	cc $(CFLAGS) $(CPPFLAGS) $^ -o $@ -lm
	mv geometry1.d $(LYBRARYWAY)geometry1.d
	mv main.d $(LYBRARYWAY)main.d

$(OBJECTWAY)main.o: $(MAINWAY)main.c
	gcc $(CFLAGS) $(CPPFLAGS) $< -c
	mv main.o $(OBJECTWAY)main.o

$(LYBRARYWAY)libgeometry.a: $(OBJECTWAY)geometry1.o
	ar rcs $@ $^
	mv libgeometry.a $(LYBRARYWAY)libgeometry.a

$(OBJECTWAY)geometry1.o: $(GEOMETRYWAY)geometry1.c
	gcc $(CFLAGS) $(CPPFLAGS) $< -c -lm
	mv geometry1.o $(OBJECTWAY)geometry1.o

clean: $(OBJECTWAY)geometry1.o $(OBJECTWAY)main.o $(LYBRARYWAY)libgeometry.a $(LYBRARYWAY)geometry1.d $(LYBRARYWAY)main.d
	rm $^
#-include main.d geometry1.d

