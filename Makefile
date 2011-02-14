# Makefile for cs455 project 2

CC=	g++ -g -Wall
OBJS= obj/pvn.o obj/controller.o obj/engine.o obj/render.o obj/state.o \
	obj/objParser.o obj/model.o obj/3dPt.o obj/3vec.o obj/textUtil.o \
	obj/face.o obj/player.o obj/camera.o obj/BMPLoader.o

LIBS= -lglut -lGLU -lGL -lXi -lXmu
#deprecated?: -ljpeg
INC= -I./

CCFLAGS= -c

all: pvn

pvn: $(OBJS)
	$(CC) $(LIBS) -o pvn $(OBJS)

obj/pvn.o: main.cpp main.h obj/controller.o obj/engine.o obj/render.o obj/state.o obj/objParser.o obj/model.o obj/3dPt.o obj/3vec.o obj/textUtil.o obj/face.o obj/player.o obj/camera.o
	$(CC) $(CCFLAGS) $(INC) -o obj/pvn.o main.cpp

obj/controller.o: controller.cpp controller.h obj/state.o obj/camera.o flags.h obj/engine.o obj/objParser.o obj/render.o
	$(CC) $(CCFLAGS) $(INC) -o obj/controller.o controller.cpp

obj/engine.o: engine.cpp engine.h obj/3vec.o obj/3dPt.o obj/model.o obj/state.o obj/camera.o flags.h
	$(CC) $(CCFLAGS) $(INC) -o obj/engine.o engine.cpp

obj/render.o: render.cpp render.h obj/model.o obj/state.o obj/camera.o obj/BMPLoader.o
	$(CC) $(CCFLAGS) $(INC) -o obj/render.o render.cpp

obj/state.o: state.cpp state.h obj/model.o obj/camera.o flags.h
	$(CC) $(CCFLAGS) $(INC) -o obj/state.o state.cpp

obj/objParser.o: objParser.cpp objParser.h obj/face.o obj/3dPt.o obj/textUtil.o obj/model.o
	$(CC) $(CCFLAGS) $(INC) -o obj/objParser.o objParser.cpp

obj/model.o: model.cpp model.h obj/face.o obj/3dPt.o flags.h obj/BMPLoader.o
	$(CC) $(CCFLAGS) $(INC) -o obj/model.o model.cpp

obj/3dPt.o: 3dPt.cpp 3dPt.h
	$(CC) $(CCFLAGS) $(INC) -o obj/3dPt.o 3dPt.cpp

obj/3vec.o: 3vec.cpp 3vec.h obj/3dPt.o
	$(CC) $(CCFLAGS) $(INC) -o obj/3vec.o 3vec.cpp

obj/textUtil.o: textUtil.cpp textUtil.h obj/3vec.o obj/3dPt.o
	$(CC) $(CCFLAGS) $(INC) -o obj/textUtil.o textUtil.cpp

obj/face.o: face.cpp face.h obj/textUtil.o
	$(CC) $(CCFLAGS) $(INC) -o obj/face.o face.cpp

obj/player.o: player.cpp player.h flags.h
	$(CC) $(CCFLAGS) $(INC) -o obj/player.o player.cpp

obj/camera.o: camera.cpp camera.h obj/3dPt.o obj/3vec.o flags.h obj/model.o
	$(CC) $(CCFLAGS) $(INC) -o obj/camera.o camera.cpp

obj/BMPLoader.o: BMPLoader.h BMPLoader.cpp
	$(CC) $(CCFLAGS) $(INC) -o obj/BMPLoader.o BMPLoader.cpp

clean:
	rm -f obj/*.o
	rm -f ./pvn

realclean: clean
	rm -f *~
	rm -f *.bak

run: all
	./pvn

git:
	git commit -a

