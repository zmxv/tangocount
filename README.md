# TangoCount

A C program to calculate the number of valid [LinkedIn Tango](https://linkedin.com/games/tango) puzzle grids of a given size.

## Building

```bash
gcc -Ofast tangocount.c -o tangocount
```

## Results

| Grid Size | Valid Solutions |
|-----------|----------------|
| 2x2       | 2             |
| 4x4       | 90            |
| 6x6       | 11,222        |
| 8x8       | 12,413,918    |
| 10x10     | 117,925,227,108|

## License

MIT License
