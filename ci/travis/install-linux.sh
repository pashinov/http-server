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

# manually install yaml-cpp 0.5.3
wget https://github.com/jbeder/yaml-cpp/archive/yaml-cpp-0.6.2.tar.gz
tar -xzvf yaml-cpp-0.6.2.tar.gz
pushd yaml-cpp-0.6.2
mkdir build
pushd build
cmake -DBUILD_SHARED_LIBS=OFF ..
make
sudo make install
popd
popd
