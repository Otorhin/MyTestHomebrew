set -e

source $DEVKITPRO/switchvars.sh
rm -rf b
mkdir b
cd b
cmake ..
make
nxlink -a 192.168.0.101 otrh.nro
