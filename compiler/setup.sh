
# doc:
# http://wiki.osdev.org/GCC_Cross-Compiler

PREFIX="$HOME/opt/cross"
TARGET=i686-elf
PATH="$PREFIX/bin:$PATH"

BINUTILS=binutils-2.44
GCC=gcc-14.2.0

# bin utils
mkdir build-binutils
cd build-binutils
../$BINUTILS/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install


# GDB

# ../gdb.x.y.z/configure --target=$TARGET --prefix="$PREFIX" --disable-werror
# make all-gdb
# make install-gdb

# GCC

cd ../

# The $PREFIX/bin dir _must_ be in the PATH. We did that above.
which -- $TARGET-as || echo $TARGET-as is not in the PATH

mkdir build-gcc
cd ./$GCC/
./contrib/download_prerequisites
cd ../build-gcc/

../$GCC/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers --disable-hosted-libstdcxx
make -j 8 all-gcc
make all-target-libgcc
make all-target-libstdc++-v3
make install-gcc
make install-target-libgcc
make install-target-libstdc++-v3