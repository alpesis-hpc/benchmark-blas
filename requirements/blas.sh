# clblast
git clone https://github.com/CNugteren/CLBlast.git
cd CLBlast
mkdir _build
cd _build
cmake -DCMAKE_INSTALL_PREFIX=benchmarks/lib/clblast ..
make -j8
make install

# openblas
git clone https://github.com/xianyi/OpenBLAS.git
cd OpenBLAS
mkdir _build
cd _build
cmake -DCMAKE_INSTALL_PREFIX=benchmarks/lib/openblas ..
make -j8
make install

# atlas
# ref: https://www.ibm.com/support/knowledgecenter/en/linuxonibm/liaai.hpcrh/installmath.htm
# download atlas 3.10.x at http://sourceforge.net/projects/math-atlas/files/
tar -jxf atlas3.10.x.tar.bz2
cd ALTAS
mkdir _build
cd _build
../configure -b 64
make
make install
ls /usr/local/atlas
#link: -lc -L/usr/local/ATLAS/obj64/lib/   -llapack   -lptcblas   -lptf77blas   -latlas 
# issue: cpu throttling apparently enabled
# ref: https://vincent.jousse.org/en/tech/archlinux-compile-lapack-atlas-kaldi/
for CPUFREQ in /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor; do [ -f $CPUFREQ ] || continue; echo -n performance > $CPUFREQ; done
cpupower frequency-set -g performance
