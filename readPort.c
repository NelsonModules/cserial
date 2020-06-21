//=============================================================================
// Copyright 2018 Robert Middleton (rm5248)
// Copyright 2020 Allan CORNET (Nelson)
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//  http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=============================================================================
#include <math.h>
#include <mex.h>
#include <matrix.h>
#include <stdint.h>
#include <c_serial.h>
#include "portHelpers.h"
//=============================================================================
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    c_serial_port_t* m_port = NULL;
    int status = 0;
    uint8_t *msgData = NULL;               /* output  vector */
    double *bytesLeft = NULL;               /* output  vector */
    double *numBytesToRead = NULL;
    numBytesToRead = mxGetPr(prhs[1]);
    int data_length = 0;
    int bytes_remaining = 0;
    uint8_t data[255];
    uint64_t *ptrID = NULL; 

    if(nrhs!=2) {
        mexErrMsgTxt("Wrong numbers of input arguments.");
    }
    if(nlhs != 1 && nlhs != 2) {
        mexErrMsgTxt("Wrong numbers of output arguments.");
    }
    numBytesToRead = mxGetPr(prhs[1]);

    ptrID = (uint64_t *)mxGetData(prhs[0]);
    if (!isValidPortPtr(ptrID[0])) {
        mexErrMsgTxt("A valid ID serial port expected.");
    }
    m_port = (c_serial_port_t*)(ptrID[0]);
    if (c_serial_is_open(m_port) == 0) {
        mexErrMsgTxt("Port is not open.");
    }
    data_length = (int) numBytesToRead[0];
 
    status = c_serial_read_data( m_port, data, &data_length, &bytes_remaining,  NULL);
    if( status < 0 ) {
        mexErrMsgTxt("Cannot read data.");
    }
    plhs[0] = mxCreateNumericMatrix(1,(mwSize)data_length,mxUINT8_CLASS,mxREAL);
    msgData = (uint8_t *) mxGetData(plhs[0]);
    for (int j = 0; j < data_length; j++){
        msgData[j] = data[j];
    }
    if( nlhs ==2 ) {
        plhs[1] = mxCreateDoubleMatrix(1,1,mxREAL);
        bytesLeft = mxGetPr(plhs[1]);
	    bytesLeft[0] = (double) bytes_remaining;
    }
}
//=============================================================================
