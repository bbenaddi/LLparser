# LLparser
Left-to-right, Leftmost derivation

## Grammar :

we will consider the following small LL(1) grammar: 
G : R -> RR | R+R | R* | (R) | a | b

## Remove ambiguous and left recursion:

the grammar is ambiguous. so we construct an equivalent unambiguous grammar G' :
     R -> R + E | E
G':  E -> ET | T
     T -> T* | F
     F -> (R) | a | b

then remove left recursion :
     R  -> EA         [1]
     A -> +EA| e      [2,3]
     E  -> TB         [4]
G''' B -> TB | e      [5,6]
     T  -> FC         [7]
     C -> *C | e      [8,9]
     F -> (R) | a | b [10,11,12]
 
## Build the FIRST and FOLLOW table :
SYMBOL	     FIRST	      FOLLOW
  R         (,a,b          ),$
  A         +,e            ),$
  E         (,a,b          +,),$
  B         (,a,b,e        +,),$ 
  T         (,a,b          a,b,+,(,),$
  C         *,e            a,b,+,(,),$
  F         (,a,b          a,b,*,+,(,),$
  
## Finally let's build the table of LL :
SYMBOL    +   *   (   )   a   b   $
  R               1       1   1         
  A       2           3           3
  E               4       4   4
  B       6       5   6   5   5   6
  T               7       7   7
  C       9   8   9   9   9   9   9
  F               10      11  12
 This table is declare(M) and intilized in our program, normally we set rule in the table but to simplify we set numbers.
 
 ## LL Algorithm:
 ```
 push $R to our stack.
 DO
    X sommet of the stack
    a current lettre
    IF
      IF M[X,a] == X -> Y1...Y3 THEN
        pop the X.
        push Yn...Y1 (in revrse order)
      ELSE
        ERROR
      FI
    ELSE
      IF X == $ THEN
        IF a == $ THEN
          ACC
        ELSE
          ERROR
        FI
      ELSE
        IF X == a THEN
            pop X.
            move a forward.
        ELSE
            ERROR
        FI
      FI
    FI
 WHILE !ERROR or !ACC
```
