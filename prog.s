.start
  prep main
  call 0
  halt
.malloc
  resn 1
  push 0
  read
  dup
  set 1
  drop 1
  push 0
  read
  get 0
  add
  dup
  push 0
  write
  drop 1
  get 1
  ret
  push 0
  ret
.free
  resn 0
  push 0
  ret
.print
  resn 1
  push 0
  dup
  set 1
  drop 1
.l1_0
.l3_0
  push 1
  jumpf l1_1
  send
  get 0
  get 1
  add
  read
  push 10
  cmpeq
  jumpf l1_2
  jump l2_0
  jump l2_3
.l1_2
.l2_3
  get 1
  push 1
  add
  dup
  set 1
  drop 1
  jump l2_4
.l1_1
  jump l2_0
.l2_4
  jump l1_0
.l2_0
  push 0
  ret
Erreur de syntaxe à la ligne8
attendu : tok_parouv reçu : tok_pv
