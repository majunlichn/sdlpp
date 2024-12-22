# sdlpp
C++ wrappers for SDL (Simple DirectMedia Layer).

## Build

1. Make sure all submodules are updated:

    ```powershell
    git submodule update --init --recursive
    ```

2. Setup [microsoft/vcpkg: C++ Library Manager for Windows, Linux, and MacOS](https://github.com/microsoft/vcpkg)

    ```powershell
    git clone https://github.com/microsoft/vcpkg.git
    # Run the bootstrap script:
    cd vcpkg
    .\bootstrap-vcpkg.bat # Linux: ./bootstrap-vcpkg.sh
    # Configure the VCPKG_ROOT environment variable for convenience:
    $env:VCPKG_ROOT="C:\path\to\vcpkg" # Linux: export VCPKG_ROOT="/path/to/vcpkg"
    ```

3. Setup [radsdk](https://github.com/majunlichn/radsdk) for additional dependencies.

    ```powershell
    # Clone radsdk (requires Git LFS support):
    git clone https://github.com/majunlichn/radsdk.git
    # Execute setup.py to download and build additional libraries:
    cd radsdk
    python setup.py
    # Configure the RADSDK_ROOT environment variable for convenience:
    $env:RADSDK_ROOT="C:\path\to\radsdk" # Linux: export RADSDK_ROOT="/path/to/radsdk"
    ```

3. Generate project files with CMake and build.

    ```powershell
    # Generate project files and build (vcpkg will install packages to VCPKG_INSTALLED_DIR):
    cd sdlpp
    cmake -S . -B build -D VCPKG_MANIFEST_DIR=$env:RADSDK_ROOT -D VCPKG_INSTALLED_DIR=$env:RADSDK_ROOT/vcpkg_installed
    ```
