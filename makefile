all:
	cd strlib && make
	cd program1 && make
	cd program2 && make
	xcopy strlib\strlib.dll program1\strlib.dll
	xcopy strlib\strlib.dll program2\strlib.dll

clean:
	cd strlib && make clean
	cd program1 && make clean
	cd program2 && make clean