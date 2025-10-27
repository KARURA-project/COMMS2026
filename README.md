### COMMS2026 cFS Repository
The basic core Flight System (cFS) is integrated in this repository.
cFS is a reusable, platform-independent software framework created by
NASA for building flight software for embedded systems.

## How to Run
After every edit, run the following:
```
make SIMULATION=native prep
make
make install
cd build/exe/cpu1/
./core-cpu1
```

## Note
A sample application was added. This was provided by NASA. It is what
runs by default when the above steps are executed.
