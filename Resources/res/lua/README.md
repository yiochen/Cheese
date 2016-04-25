# Note on lua file creation.

You can use multiple files (actually it is encouraged). But you cannot use "require" or "dofile". Which means the lua files should not have any relationship with each other. 

## Datatype
The types of function parameter and return types are limited. Following are the accepted types:
- LuaTable
- LuaCoroutine
- LuaFunction
- LuaUserdata
- float
- double
- bool
- signed char
- unsigned char
- short
- unsigned short
- int
- unsigned int
- long
- unsigned long
- long long
- unsigned long long
- char*
- const char*
- std::string
- std::wstring

> note that those are C++ types. But you should be able to find out the corresponding lua types.  

Lua function can return void. If a function returns multiple values. return a table instead. The table could contain those values. 

## naming convention
I named all the lua files, functions and  variables using small case connected by underscore. ex. sprite_config, next_file...  
You should try to encapsulate things using lua table. Do not leave everything in the global scope. 

## IDE
There are a bunch of IDE's for lua. You can run lua on them. You can use print statement to test your lua script. Those print statement will not affect the game output. Also make sure the lua script compiles and runs as expected. 

# Example
You can checkout the sprite_config.lua