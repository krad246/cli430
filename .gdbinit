set pagination off
set mem inaccessible-by-default off
set  disassemble-next-line on
show disassemble-next-line

target remote localhost:2000
monitor reset halt

load
break main
set $sr = 0
