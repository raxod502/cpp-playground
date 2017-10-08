#!/usr/bin/env zsh

cd $0:A:h/
mkdir -p local/
prefix=$PWD/local/
cd unittest-cpp/
git clean -fdx
autoreconf -fvi
./configure --prefix=$prefix
make install
