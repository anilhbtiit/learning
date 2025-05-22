Code:
encryption.cc

Compile:
setenv LD_LIBRARY_PATH "/in/d2sdft1/conan2/p/gcc3ddaebcc70a64/p/lib64:/home/hdldft/Projects/scons_hdle_b/installDir-dbg/inhouse/lnx-x86/lib64:/usr/lib64/:/usr/lib:/usr/local/lib"
g++ -g -I /project/dfttools/current_devtools/lnx-x86-rhel6/include/openssl/ -std=c++20 -lcrypto encryption.cc -o encryption.o | & tee log

Run:
./encryption.o
