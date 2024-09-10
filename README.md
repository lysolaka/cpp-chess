# CPP-CHESS
A very crude chess game to show how C++ works

See also a version of this in Rust: [lysolaka/rust-chess](https://github.com/lysolaka/rust-chess)

## Building

```$
mkdir build && cd build
cmake ..
make
```
If your terminal doesn't support colour, add `-DUSE_COLOR=OFF` to the cmake command.

The binary is named `cpp-chess` and should be in the build directory, after compilation finishes.
