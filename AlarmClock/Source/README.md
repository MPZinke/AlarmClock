
<!----------------------------------------------------------------------------------------------------------------------
-                                                                                                                      -
-    Created by: MPZinke on 2023.08.28                                                                                 -
-                                                                                                                      -
-    DESCRIPTION:                                                                                                      -
-    BUGS:                                                                                                             -
-    FUTURE:                                                                                                           -
-                                                                                                                      -
----------------------------------------------------------------------------------------------------------------------->

## Decisions

### Benefits Of Using An Interrupt
- Interrupt allows for immediate recognition of hardware input

### Disadvantages Of Using An Interrupt
- Stops operating code
- Returning to context needs to occur quickly, meaning delay in an Interrupt callback is impractical

### Benefits Of Checking On Each Iteration
- Does not interrupt time based operations like SPI
- Can begin operations when ready to

### Final Decision
- 


## Encoder

### Signal
```
    1   4   8   12  16  20  24
	|   |   |   |   |   |   |
    .........................
         ___     ___     ___
 A  |___|   |___|   |___|   |
    .........................
       ___     ___     ___
 B  __|   |___|   |___|   |__
    .........................
```

### As Binary Where A Is 2^0 And B Is 2^1:
```
    1   4   8   12  16  20  24
	|   |   |   |   |   |   |
 A  0000111100001111000011110
 B  0011110000111100001111000
```

### Above Binar As Decimal:
```
    1   4   8   12  16  20  24
	|   |   |   |   |   |   |
 BA 0022331100223311002233110
```

### Mapping
| PREVIOUS |   NEW   | DIRECTION |
|----------|---------|-----------|
|    0     |    0    |     0     |
|    1     |    1    |     0     |
|    2     |    2    |     0     |
|    3     |    3    |     0     |
|    0     |    2    |     1     |
|    1     |    0    |     1     |
|    2     |    3    |     1     |
|    3     |    1    |     1     |
|    0     |    1    |    -1     |
|    1     |    3    |    -1     |
|    2     |    0    |    -1     |
|    3     |    2    |    -1     |

### Mapping As 2-D List `PULLS[PREVIOUS][NEW]`
|     -     | Col 1 | Col 2 | Col 3 | Col 4 |
|-----------|-------|-------|-------|-------|
| **Row 1** |   0   |  -1   |   1   |   0   |
| **Row 2** |   1   |   0   |   0   |  -1   |
| **Row 3** |  -1   |   0   |   0   |   1   |
| **Row 4** |   0   |   1   |  -1   |   0   |

```c++
{
	{ 0, -1,  1,  0},
	{ 1,  0,  0, -1},
	{-1,  0,  0,  1},
	{ 0,  1, -1,  0}
}
```
