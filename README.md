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
* [data, nbBytesReceived] = readPort(id, numBytesToRead)
* writePort(id, data)  write date on serial port. data must be uint8 or char.
* closePort(id) closes an port opened.
* flushPort(id) flushs desired port.
* rtsControl(id, rtsMethod) with rtsMethod 'hard', 'soft', 'none', 'best'.

Example: https://github.com/NelsonModules/cserial/blob/master/example.m

This toolboxe is an example to show how it is easy to use existing C MEX builtin with Nelson.
This toolbox works on Nelson and others tools fully compatible with C MEX API.

Allan CORNET - 2020 
