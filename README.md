## How to Compile

This example is based on top of the existing [openCilk](https://github.com/OpenCilk) infrastructure. To compile:

`make`

or

`make <target>`

where `<target>` is one of the following: 
- `cilk_sum`
- `cilk_max`

You can use `opt=<opt-flag>` to define your optimization flag. `<opt-flag>` can be one of the following:

- `-O0` (default)
- `-O1`
- `-O2`
- `-O3`


## Visualize Performance

Use the `graph.py` simple script to visualize the speedup after running the binaries.

### Example

```make cilk_max opt=-O3
./bin/cilk_max
chmod +x graph.py
./graph.py
```