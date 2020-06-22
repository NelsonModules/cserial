mex('getPortNames.c', 'c_serial.c', ['-I ', pwd()], '-DCSERIAL_STATIC');
mex('openPort.c', 'c_serial.c', ['-I ', pwd()], '-DCSERIAL_STATIC');
mex('writePort.c', 'c_serial.c', ['-I ', pwd()], '-DCSERIAL_STATIC');
mex('readPort.c', 'c_serial.c', ['-I ', pwd()], '-DCSERIAL_STATIC');
mex('closePort.c', 'c_serial.c', ['-I ', pwd()], '-DCSERIAL_STATIC');
mex('flushPort.c', 'c_serial.c', ['-I ', pwd()], '-DCSERIAL_STATIC');

