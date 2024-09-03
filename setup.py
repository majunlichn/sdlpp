import os
import sys
import subprocess
import shutil

working_dir_before_execute = os.getcwd()
script_root = os.path.dirname(os.path.realpath(__file__))
working_dir_stack = list()

def chdir(path: str):
    os.chdir(path)
    print("Working dir:", os.getcwd())

def pushd(dir):
    working_dir_stack.append(os.getcwd())
    os.chdir(dir)
    print("Working dir:", os.getcwd())

def popd():
    os.chdir(working_dir_stack.pop())
    print("Working dir:", os.getcwd())

def run(command : str, env = os.environ):
    print("Execute:", command)
    subprocess.run(command, shell=True, env=env)

def remove_dir(dir : str):
    if os.path.isdir(str):
        shutil.rmtree(dir)

def build_SDL():
    chdir(script_root + "/imported")
    if not os.path.exists("SDL"):
        run("git clone https://github.com/libsdl-org/SDL.git")
    chdir(script_root + "/imported/SDL")
    chdir(script_root + "/imported")
    build_dir = script_root + "/imported/build/SDL"
    install_dir = script_root + "/imported/installed/SDL"
    run(f"cmake -S SDL -B \"{build_dir}\" -DCMAKE_INSTALL_PREFIX=\"{install_dir}\"")
    run(f"cmake --build \"{build_dir}\" --target install --config Release")

def build_SDL_mixer():
    chdir(script_root + "/imported")
    if not os.path.exists("SDL_mixer"):
        run("git clone https://github.com/libsdl-org/SDL_mixer.git")
    chdir(script_root + "/imported/SDL_mixer")
    run("git submodule update --init --recursive")
    chdir(script_root + "/imported")
    build_dir = script_root + "/imported/build/SDL_mixer"
    install_dir = script_root + "/imported/installed/SDL_mixer"
    sdl3_install_dir = script_root + "/imported/installed/SDL"
    run(f"cmake -S SDL_mixer -B \"{build_dir}\" -DSDL3MIXER_MP3_MPG123=ON -DCMAKE_INSTALL_PREFIX=\"{install_dir}\"",
                   env=dict(os.environ, SDL3_DIR=sdl3_install_dir))
    run(f"cmake --build \"{build_dir}\" --target install --config Release")

def main() -> int:
    try:
        chdir(script_root)
        run("git submodule update --init --recursive")
        build_SDL()
        build_SDL_mixer()
        chdir(script_root)
        run("cmake -S . -B build")
        chdir(working_dir_before_execute)
        return 0
    except Exception as e:
        print(e)
        chdir(working_dir_before_execute)
        return -1

if __name__ == '__main__':
    sys.exit(main())
