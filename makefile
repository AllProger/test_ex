all:
	cd strlib && make
	cd program1 && make
	cd program2 && make
	cp strlib/libstrlib.so program1/
	cp strlib/libstrlib.so program2/
    
clean:
	cd strlib && make clean
	cd program1 && make clean
	cd program2 && make clean
	rm -f program1/libstrlib.so program2/libstrlib.so
