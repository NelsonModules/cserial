C MEX interface for serial by implementing c_serial code base: 
https://github.com/rm5248/CSerial

To build:

On Nelson:
```
run('build.nls')
```

On others tools:
```
run('build.m')
```


Builtin availables:

* getPortNames
* openPort
* readPort
* writePort
* closePort

This toolboxe is an example to show how it is easy to use existing C MEX builtin with Nelson.


Allan CORNET - 2020 
