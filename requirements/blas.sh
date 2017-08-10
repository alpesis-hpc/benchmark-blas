# clblast
git clone https://github.com/CNugteren/CLBlast.git
cd CLBlast
mkdir _build
cd _build
cmake -DCMAKE_INSTALL_PREFIX=benchmarks/lib/clblast
make -j8
make install
