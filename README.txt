In order to run this, you will need a compiler that supports OpenMP.  Most GCC compilers should do fine.

The project also uses cmake, so install the latest version of that.  Yum in centos 7 gives you 2.6, but I patched mine to 3.6.  I think the default yum version should be fine.

You also need to install Armadillo, which I used for the matrix math operations.
Recommended packages for Fedora & Red Hat (installed before Armadillo): 
cmake, openblas-devel, lapack-devel, arpack-devel, SuperLU-devel

Installed for Centos 7 using:
wget http://dl.fedoraproject.org/pub/epel/7/x86_64/e/epel-release-7-8.noarch.rpm
rpm -ivh epel-release-7-8.noarch.rpm
sudo yum install armadillo-devel.x86_64

