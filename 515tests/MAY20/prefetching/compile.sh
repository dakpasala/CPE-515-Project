docker run --rm -v $(pwd):/work ubuntu bash -c "
  apt update -qq && apt install -y -qq g++-x86-64-linux-gnu &&
  x86_64-linux-gnu-g++ -O1 -static /work/fastlz.c /work/bench-fastlz.cpp -o /work/bench-fastlz
"