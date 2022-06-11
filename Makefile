main.out: main.o arm.o
	g++ main.o arm.o -o main.out

main.o: main.cpp lib/libbox2d.a include/box2d/box2d.h
	g++ -c main.cpp -lbox2d

arm.o: include/arm.h source/arm.cpp
	g++ -c source/arm.cpp
