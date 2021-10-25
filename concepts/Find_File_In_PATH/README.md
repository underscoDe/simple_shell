
## HOW THIS WORKS
- user will call batch script "_which"
- _which will echo filename:PATH as input to c program, "_which_handler"
- the c program "_which_handler" will then process the PATH together with filename and display result

c file: _which_handler.c
    
## Using it
In order to be able to run _which directly without using ./_which, the executables in this directory should be placed in PATH. That includes:
- _which (bash script)
- _which_handler (C executable)

