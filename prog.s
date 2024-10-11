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
  resn 2
  push 0
  dup
  set 2
  drop 1
  get 0
  push 0
  cmpeq
  jumpf l1_0
  send
  push 0
  ret
  jump l2_1
.l1_0
.l2_1
.l1_2
.l3_2
  get 0
  push 0
  cmpgt
  jumpf l1_3
  get 2
  push 10
  mul
  get 0
  push 10
  mod
  add
  dup
  set 2
  drop 1
  get 0
  push 10
  div
  dup
  set 0
  drop 1
  jump l2_4
.l1_3
  jump l2_2
.l2_4
  jump l1_2
.l2_2
.l1_5
.l3_5
  get 2
  push 0
  cmpgt
  jumpf l1_6
  get 2
  push 10
  mod
  dup
  set 1
  drop 1
  send
  get 2
  push 10
  div
  dup
  set 2
  drop 1
  jump l2_7
.l1_6
  jump l2_5
.l2_7
  jump l1_5
.l2_5
  push 0
  ret
  push 0
  ret
.read
  resn 2
  push 0
  dup
  set 0
  drop 1
  recv
  drop 1
  push 0
  read
  dup
  set 1
  drop 1
  get 1
  push 48
  cmpge
  get 1
  push 57
  cmple
  and
  jumpf l1_8
  get 1
  push 48
  sub
  dup
  set 0
  drop 1
  jump l2_9
.l1_8
.l2_9
  get 0
  ret
  push 0
  ret
.main
  resn 0
  prep read
  call 0
  drop 1
  prep print
  push 89
  call 1
  drop 1
  push 0
  ret
  push 0
  ret
