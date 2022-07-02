main.out: main.o arm.o
	g++ main.o arm.o -o main.out -Llib/ -lbox2d -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -c main.cpp

arm.o: include/arm.h source/arm.cpp lib/libbox2d.a include/box2d/box2d.h
	g++ -c source/arm.cpp -Llib/ -lbox2d -Wall
