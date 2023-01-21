@REM #change current directory to this file

@rem change driver letter
@%~d0

@rem change current directory
@cd %~dp0

@cd ../../

@rem set testlib_dir=external\testlib
@rem mkdir %testlib_dir%
@rem git clone --recurse https://github.com/wai3aa1sam/testlib.git %testlib_dir%
@rem PUSHD %testlib_dir%
@rem git checkout main
@rem git pull
@rem POPD

cmake -G "Visual Studio 17 2022" -B ./build/nmsplib-x64-windows .

@pause