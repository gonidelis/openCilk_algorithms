## How to Compile

This example is based on top of the existing [openCilk](https://github.com/OpenCilk) infrastructure. Use the Tapir-LLVM `clang++` compiler like:

`clang++ opencilk_reducer.cpp cilk_sum.cpp -o cilk_sum -fopencilk`