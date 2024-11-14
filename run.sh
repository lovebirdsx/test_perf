echo C
gcc test.c && ./a.out && rm ./a.out 

echo ''
echo Javascript
node test.js

echo ''
echo Lua
lua test.lua 

echo ''
echo Python
python3.10 test.py
