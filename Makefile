main.out: main.o lib/libarm.a include/arm.h
	g++ main.o -o main.out -Llib/ -larm -lbox2d -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp include/arm.h
	g++ -c main.cpp

lib/libarm.a: bin/libarm.a
	cp bin/libarm.a lib/libarm.a

bin/libarm.a: arm.o
	ar rcs bin/libarm.a arm.o

arm.o: include/arm.h source/arm.cpp lib/libbox2d.a include/box2d/box2d.h
	g++ -c source/arm.cpp -Llib/ -lbox2d -Wall
