#/bin/sh

mkdir -p build
cd build
cmake ../.
make
cd release
upx -9 chromecons
mkdir chromepass
cp chromecons chromepass/chromecons
makeself chromepass chromepass.run "BastionPass Chrome password extractor" ./chromecons

