curl -LOC - https://github.com/uyjulian/pacman-packages/releases/download/v2.2.3-1-pkgbuild-helpers/devkitpro-pkgbuild-helpers-2.2.3-1-any.pkg.tar.xz
/bin/bash -c 'dkp-pacman -U --noconfirm devkitpro-pkgbuild-helpers-2.2.3-1-any.pkg.tar.xz'
/bin/bash -c 'sed -i'"'"'.bak'"'"' '"'"'s/set(CMAKE_EXE_LINKER_FLAGS_INIT "/set(CMAKE_EXE_LINKER_FLAGS_INIT "-fPIC /'"'"' $DEVKITPRO/switch.cmake' 