# manually install gcc
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get update -qq

sudo apt-get install -qq g++-6
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-6 90
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-6 90

# manually install CMake 3.7.2
CMAKE_VERSION=3.7.2
CMAKE_VERSION_DIR=v3.7

CMAKE_OS=Linux-x86_64
CMAKE_TAR=cmake-$CMAKE_VERSION-$CMAKE_OS.tar.gz
CMAKE_URL=http://www.cmake.org/files/$CMAKE_VERSION_DIR/$CMAKE_TAR
CMAKE_DIR=$(pwd)/cmake-$CMAKE_VERSION

wget --quiet $CMAKE_URL
mkdir -p $CMAKE_DIR
tar --strip-components=1 -xzf $CMAKE_TAR -C $CMAKE_DIR
export PATH=$CMAKE_DIR/bin:$PATH

# manually install boost latest version
sudo apt-get install libboost-all-dev

# manually install yaml-cpp 0.5.3
git clone --depth=50 --branch=yaml-cpp-0.5.3 https://github.com/jbeder/yaml-cpp.git
pushd yaml-cpp
mkdir build
pushd build
cmake -DBUILD_SHARED_LIBS=OFF ..
make
sudo make install
popd
popd
