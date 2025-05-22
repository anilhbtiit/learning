#!/bin/csh -f

rm -rf out.o log.txt
#g++ -g -std=c++11 -fpermissive auto.cc main.cc -o out.o | &tee log.txt
#g++ -g -std=c++17 -fpermissive auto.h auto.cc cpp20.cc main.cc -o out.o | &tee log.txt
#g++ -g -std=c++20 -fpermissive template.cc auto.h auto.cc cpp20.cc main.cc -o out.o | &tee log.txt
#g++ -g -std=c++20 -fpermissive auto.h auto.cc cpp20.cc main.cc -o out.o | &tee log.txt
g++ -g -std=c++20 -fpermissive bitset.cc -o out.o | &tee log.txt

./out.o
