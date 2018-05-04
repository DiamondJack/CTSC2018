@echo off
for /l %%i in (19,1,20) do (
		datamaker > %%i.in
		std < %%i.in > %%i.ans
		echo No.%%i Done
)
