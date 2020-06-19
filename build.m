mex('getPortNames.c', 'c_serial.c', ['-I ', pwd()]);
mex('openPort.c', 'c_serial.c', ['-I ', pwd()]);
mex('writePort.c', 'c_serial.c', ['-I ', pwd()]);
mex('readPort.c', 'c_serial.c', ['-I ', pwd()]);
mex('closePort.c', 'c_serial.c', ['-I ', pwd()]);
