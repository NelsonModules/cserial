C MEX interface for serial port by implementing c_serial code base: 
https://github.com/rm5248/CSerial

To build:

On Nelson >= 0.4.6 :

```
run('builder.nls')
run('loader.nls')
help cserial
```

On others tools:

```
run('builder.m')
```

Builtin availables:

* getPortNames() returns a cell with available ports.
* id = openPort(port, baudrate [, databits [, stopbits, [parity, [flowcontrol, [rtscontrol]]]]])
    - supported baud rate: 0, 50, 100, 110, 134, 150, 200, 300, 600, 1200, 1800, 2400, 4800, 9600, 19200, 38400, 115200, or 921600.
    - data bits: 5, 6, 7, or 8.
    - stop bits: 0 or 1.
    - parity: 'none', 'odd' or 'even'.
    - flowcontrol: 'none', 'hard' or 'soft'.
    - rtscontrol: 'none', 'hard', 'soft', or 'best'.

* [data, nbBytesReceived] = readPort(id, numBytesToRead)
* writePort(id, data) write date on serial port. data must be uint8 or char.
* closePort(id) closes an port opened.
* flushPort(id) flushs desired port.
* st = getPortConfig(id) returns struct with port informations.


Example: https://github.com/NelsonModules/cserial/blob/master/example/example.m

This toolboxe is an good example to show how it is easy to use existing C MEX builtin with Nelson.
This toolbox works on Nelson and all others tools fully compatible with C MEX API.

Allan CORNET - 2020 
