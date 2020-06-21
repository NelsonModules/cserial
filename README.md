C MEX interface for serial port by implementing c_serial code base: 
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

* getPortNames() returns a cell with available ports.
* id = openPort(port, baudrate [, databits [, stopbits, [parity, [flowcontrol]]]])
* res = readPort(id, numBytesToRead)
* writePort(id, data)
* closePort(id) closes an port opened.
* flushPort(id) flushs desired port.

This toolboxe is an example to show how it is easy to use existing C MEX builtin with Nelson.


Allan CORNET - 2020 
