CXX	= gcc
OPTIONS	= -O3 -Wall -m32
LIBS	= -lufrn_lynx -lm

EXECDEMO	= demo
MAINDEMO	= demo.c

EXECP2	= armkeyboard
MAINP2	= arm_keyboard.c

main:	clean
	$(CXX) $(OPTIONS) $(MAINDEMO) -I./include/ -L./lib/ $(LIBS) -o $(EXECDEMO)
	$(CXX) $(OPTIONS) $(MAINP2) -I./include/ -L./lib/ $(LIBS) -o $(EXECP2)

clean:
	clear
	rm -f include/*~
	rm -f lib/*~
	rm -f *~
