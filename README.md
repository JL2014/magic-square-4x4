# magic-square-of-squares-4x4

https://en.wikipedia.org/wiki/Magic_square_of_squares \
http://www.multimagie.com/English/SquaresOfSquares.htm
- http://www.multimagie.com/English/SquaresOfSquares4_7.htm
- http://www.multimagie.com/English/Supplement.htm

```
| v01² | v02² | v03² | v04² |
| v05² | v06² | v07² | v08² |
| v09² | v10² | v11² | v12² |
| v13² | v14² | v15² | v16² |
```
Lines: S2 = v01² + v02² + v03² + v04² = v05² + v06² + v07² + v08² = v09² + v10² + v11² + v12² = v13² + v14² + v15² + v16²\
Rows:  S2 = v01² + v05² + v09² + v13² = v02² + v06² + v10² + v14² = v03² + v07² + v11² + v15² = v04² + v08² + v12² + v16²\
Diags: S2 = v01² + v06² + v11² + v16² = v04² + v07² + v10² + v13²

```
| (+ap+bq+cr+ds)² | (+ar–bs–cp+dq)² | (–as–br+cq+dp)² | (+aq–bp+cs–dr)² |
| (–aq+bp+cs–dr)² | (+as+br+cq+dp)² | (+ar–bs+cp–dq)² | (+ap+bq–cr–ds)² |
| (+ar+bs–cp–dq)² | (–ap+bq–cr+ds)² | (+aq+bp+cs+dr)² | (+as–br–cq+dp)² |
| (–as+br–cq+dp)² | (–aq–bp+cs+dr)² | (–ap+bq+cr–ds)² | (+ar+bs+cp+dq)² |
```
S2 = (a² + b² + c² + d²)(p² + q² + r² + s²)

For (a, b, c, d, p, q, r, s) between [-10,10], see list_4x4.csv (S2 up to 42845).

## usages

./magic_square_4x4\
./magic_square_4x4 68 29 41 37 17 31 79 32 59 28 23 61 11 77  8 49

./magic_square_4x4 48 23  6 19 21 26 33 32  1 36 13 42 22 27 44  9

./magic_square_4x4 37 23 21 22  1 18 47 17 38 11 13 33  3 43  2 31

With only prime numbers:\
./magic_square_4x4  29 191 673 137  71 647 139 257 277 211 163 601 653  97 101 251\
(S2 = 509020)
