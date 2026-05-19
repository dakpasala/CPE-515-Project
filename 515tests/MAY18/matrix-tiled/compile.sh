docker run --rm -v $(pwd):/work ubuntu bash -c "
apt update &&
apt install -y g++-x86-64-linux-gnu &&
x86_64-linux-gnu-g++ -O0 -static /work/matrix-tiled.cpp -o /work/matrix-tiled
"