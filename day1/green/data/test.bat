@echo off
for /l %%i in (1,1,9) do (
		brute < %%i.in > .out
		fc .out %%i.ans || exit

)
