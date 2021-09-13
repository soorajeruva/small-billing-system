cc=g++
std=-std=c++17
name=-o
obj=-c
out=obj_file
exe=bin

main.exe: ${exe} main.o interface.o item_control.o bill_control.o container.o item.o
	${cc} ${std} ${out}/item.o ${out}/main.o ${out}/interface.o ${out}/item_control.o ${out}/bill_control.o ${out}/container.o ${name} ${exe}/main

main.o: out main.cpp
	${cc} ${std} ${obj} main.cpp ${name} ${out}/main.o

interface.o: out src/interface.cpp
	${cc} ${std} ${obj} src/interface.cpp ${name} ${out}/interface.o

item_control.o: out src/item_control.cpp
	${cc} ${std} ${obj} src/item_control.cpp ${name} ${out}/item_control.o

bill_control.o: out src/bill_control.cpp
	${cc} ${std} ${obj} src/bill_control.cpp ${name} ${out}/bill_control.o

container.o: out src/container.cpp
	${cc} ${std} ${obj} src/container.cpp ${name} ${out}/container.o
	
item.o: out src/item.cpp
	${cc} ${std} ${obj} src/item.cpp ${name} ${out}/item.o

out:
	mkdir ${out}
bin:
	mkdir ${exe}
run:
	${exe}/main
clear:
	find ./ -type f \( -iname \*.o -o -iname \*.h.gch -o -iname \*.out -o -iname \*.txt \) -delete &&  rm -f -d ${out}