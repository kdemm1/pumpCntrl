all: pump_cntrl.o
	g++ -std=c++11 -Wall pump_cntrl.o -o generator.out

pump_cntrl.o:
	g++ -std=c++11 -Wall -c pump_cntrl.cpp

run:
	./generator.out

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#[
