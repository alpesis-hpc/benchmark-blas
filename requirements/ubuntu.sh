# install blas, openblas, atlas, lapack
sudo apt-get install libblas3gf libopenblas-base libatlas3gf-base liblapack3gf libopenblas-dev liblapack-dev libatlas-dev

# update-alternatives
sudo update-alternatives --config libblas.so.3 ## select from 3 versions of blas: blas, atlas, openblas
sudo update-alternatives --config liblapack.so.3 ## select from 2 versions of lapack: lapack and atlas-lapack
