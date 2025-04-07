
# doc:
# http://wiki.osdev.org/GCC_Cross-Compiler

PREFIX="$PWD/i386_elf_gcc"
TARGET=i386-elf
PATH="$PREFIX/bin:$PATH"

BINUTILS=binutils-2.44
GCC=gcc-14.2.0

# Make sure we have some minimum for that project to compile
sudo apt update
sudo apt upgrade
sudo apt install make
sudo apt install gcc
sudo apt install c++
sudo apt install nasm
sudo apt-get install qemu-system
sudo apt-get install qemu-user-static

# download BINUTILS AND GCC and uncompress it
wget https://ftp.gnu.org/gnu/binutils/$BINUTILS.tar.gz
wget https://ftp.gnu.org/gnu/gcc/$GCC/$GCC.tar.gz
tar xf $BINUTILS.tar.gz
tar xf $GCC.tar.gz

#If your development system is booted from EFI it may be that you don't have the PC-BIOS version of the grub binaries installed anywhere.
#If you install them then grub-mkrescue will by default produce a hybrid ISO that will work in QEMU.
#On Ubuntu this can be achieved with `grub-pc-bin` from `apt-get install`
sudo apt-get install grub-pc-bin

# bin utils
mkdir build-binutils
cd build-binutils
../$BINUTILS/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install


# GCC

cd ../

# The $PREFIX/bin dir _must_ be in the PATH. We did that above.
which -- $TARGET-as || echo $TARGET-as is not in the PATH

mkdir build-gcc
cd ./$GCC/
./contrib/download_prerequisites
cd ../build-gcc/

../$GCC/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --disable-libssp --enable-languages=c,c++ --without-headers --disable-hosted-libstdcxx
make -j 8 all-gcc
make all-target-libgcc
make all-target-libstdc++-v3
make install-gcc
make install-target-libgcc
make install-target-libstdc++-v3
