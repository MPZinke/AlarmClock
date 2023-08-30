
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


---

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


---

# States

## Home
| Input          | Next State          | Action                                                                        |
|----------------|---------------------|-------------------------------------------------------------------------------|
| Encoder::Left  | Home                | Set volume up.                                                                |
| Encoder::Right | Home                | Set volume down.                                                              |
| Button::Center | Menu::Alarm         | Display menu.                                                                 |

## Menu::Alarm
| Input          | Next State          | Action                                                                        |
|----------------|---------------------|-------------------------------------------------------------------------------|
| Encoder::Right | Menu::Time          | Set menu selection time.                                                      |
| Encoder::Left  | Menu::Alarm         | None.                                                                         |
| Button::Center | Alarm::Menu::One    | Select alarm menu.                                                            |

## Menu::Time
| Input          | Next State          | Action                                                                        |
|----------------|---------------------|-------------------------------------------------------------------------------|
| Encoder::Right | Menu::Alarm         | Set volume up.                                                                |
| Encoder::Left  | Menu::Date          | None.                                                                         |
| Button::Center | Time::Menu          | Select alarm menu.                                                            |

## Menu::Date
| Input          | Next State          | Action                                                                        |
|----------------|---------------------|-------------------------------------------------------------------------------|
| Encoder::Right | Menu::Date          | None.                                                                         |
| Encoder::Left  | Menu::Alarm         | Set volume up.                                                                |
| Button::Center | Date::Year          | Select alarm menu.                                                            |


## Alarm::Menu::One
| Input          | Next State          | Action                                                                        |
|----------------|---------------------|-------------------------------------------------------------------------------|
| Encoder::Left  | Alarm::Menu::Two    | Set volume up.                                                                |
| Encoder::Right | Alarm::Menu::One    | None.                                                                         |
| Button::Center | Alarm::One::Menu    | Select alarm menu.                                                            |

## Alarm::Menu::Two
| Input          | Next State          | Action                                                                        |
|----------------|---------------------|-------------------------------------------------------------------------------|
| Encoder::Left  | Alarm::Menu::...    | Set volume up.                                                                |
| Encoder::Right | Alarm::Menu::One    | None.                                                                         |
| Button::Center | Alarm::Two::Menu    | Select alarm menu.                                                            |

## Alarm::Menu::...
| Input          | Next State          | Action                                                                        |
|----------------|---------------------|-------------------------------------------------------------------------------|
| Encoder::Left  | Alarm::Menu::New    | Set volume up.                                                                |
| Encoder::Right | Alarm::Menu::...-1  | None.                                                                         |
| Button::Center | Alarm::Two::Menu    | Select alarm menu.                                                            |

## Alarm::Menu::New
| Input          | Next State          | Action                                                                        |
|----------------|---------------------|-------------------------------------------------------------------------------|
| Encoder::Left  | Alarm::Menu::New    | Set volume up.                                                                |
| Encoder::Right | Alarm::Menu::...-1  | None.                                                                         |
| Button::Center | Alarm::Two::Menu    | Select alarm menu.                                                            |
