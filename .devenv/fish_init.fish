set LOCAL_PATH .local
set VCPKG_PATH $LOCAL_PATH/vcpkg
set CMAKE_OUT $LOCAL_PATH/cmake
set CMAKE_BUILD $CMAKE_OUT/build
set CMAKE_DIST $CMAKE_OUT/dist

function setup
  bash vcpkg_install.sh
  cmake_prepare
end

function clean
  cmake_clean
  vcpkg_clean
end

function cmake_clean
  rm -rf $CMAKE_OUT
end

function cmake_prepare
  # Note: $argv forwards argument so you can add additional arguments
  # e.g: cmake_prepare -DCMAKE_BUILD_TYPE=Release to configure the build solution in release mode with gcc
  cmake -DCMAKE_TOOLCHAIN_FILE=$VCPKG_PATH/scripts/buildsystems/vcpkg.cmake \
    -S . \
    -B $CMAKE_BUILD \
    -DCMAKE_INSTALL_PREFIX=$CMAKE_DIST \
    -DBUILD_TESTING=1 \
    $argv
end

function cmake_prepare_release
  cmake_prepare -DCMAKE_BUILD_TYPE=Release $argv
end

function cmake_prepare_debug
  cmake_prepare -DCMAKE_BUILD_TYPE=Debug $argv
end

function cmake_build
  # Note: $argv forwards argument so you can add additional arguments
  # e.g: cmake_build --config release to build in release mode with Visual Studio Compiler
  cmake --build $CMAKE_BUILD -j $argv
end

function cmake_build_release
  cmake_build --config Release $argv
end

function cmake_build_debug
  cmake_build --config Debug $argv
end

function cmake_install
  # Note: $argv forwards argument so you can add additional arguments
  # e.g: cmake_install --config release to build in release mode, then install, with Visual Studio Compiler
  cmake --build $CMAKE_BUILD -j --target install $argv
end

function cmake_install_release
  cmake_install --config Release
end

function cmake_install_debug
  cmake_install --config Debug
end

function ctest_release
  cmake_build_release
  ctest --test-dir $CMAKE_BUILD -C Release -V
end

function ctest_debug
  cmake_build_debug
  ctest --test-dir $CMAKE_BUILD -C Debug -V
end

function vcpkg_export_dependencies
  $VCPKG_PATH/vcpkg export --x-all-installed --zip --output=precompiled-third-party
end

function vcpkg_clean
  rm -rf $VCPKG_PATH
end
