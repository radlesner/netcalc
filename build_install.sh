mkdir -p build
cd build

cmake -DCMAKE_BUILD_TYPE=Release ..
make

read -p "Install project? [N/Y]" install
if [ "$install" = "Y" ] || [ "$install" = "y" ] ; then
    sudo make install
fi
