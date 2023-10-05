git clone <repo>
git submodule update --init --recursive
git lfs pull
unzip BakedEngine3rdPartyLibs/windows/Vulkan-*.zip

cd Baked...Sdl
mkdir build
cd build
cmake ..
cmake --build .
cmake --build . --config Release 
cmake --install . --prefix ../build-install/
