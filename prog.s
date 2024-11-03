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
.read
  resn 3
  prep malloc
  push 30
  call 1
  dup
  set 0
  drop 1
  push 0
  dup
  set 1
  drop 1
.l1_5
.l3_5
  push 1
  jumpf l1_6
  recv
  dup
  set 2
  drop 1
  get 2
  push 10
  cmpeq
  get 1
  push 29
  cmpge
  or
  get 2
  push 0
  push 1
  sub
  cmpeq
  or
  jumpf l1_7
  push 10
  dup
  get 0
  get 1
  add
  write
  drop 1
  jump l2_5
  jump l2_8
.l1_7
.l2_8
  get 2
  dup
  get 0
  get 1
  add
  write
  drop 1
  get 1
  push 1
  add
  dup
  set 1
  drop 1
  jump l2_9
.l1_6
  jump l2_5
.l2_9
  jump l1_5
.l2_5
  get 0
  ret
  push 0
  ret
.main
  resn 1
  prep read
  call 0
  dup
  set 0
  drop 1
  prep print
  get 0
  call 1
  drop 1
  push 0
  ret
  push 0
  ret
