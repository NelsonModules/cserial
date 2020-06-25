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
#include <mex.h>
#include <math.h>
#include <stdint.h>
#include "portHelpers.h"
#include "c_serial.h"
//=============================================================================
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    c_serial_port_t* m_port = NULL;
    int status = 0;
    int bytes_read = 0;
    int data_length = 0;
    mxUint8 *data = NULL;
    mwSize total_num_of_elements = 0;
    mwSize index = 0;
    mxUint64 *ptrID = NULL; 
    bool isSupportedType = false;
    bool isVector = false;
    bool isSupportedID = false;

    if (nrhs != 2) {
        mexErrMsgTxt("Please send serial port object and msg.");
    }
    if (nlhs != 0) {
        mexErrMsgTxt("No outputs here.");
    }
    isSupportedType = mxGetClassID(prhs[1]) == mxUINT8_CLASS;
    isVector = mxGetM(prhs[1]) == 1 || mxGetN(prhs[1]) == 1;
    if (!isSupportedType || mxGetNumberOfDimensions(prhs[1]) != 2 || !isVector) {
        mexErrMsgTxt("Write data is not a vector of uint8 numbers, please convert.");
    }
    data = (mxUint8 *)mxGetData(prhs[1]);
    data_length = (int)mxGetNumberOfElements(prhs[1]);
    ptrID = (mxUint64*)mxGetData(prhs[0]);
    isSupportedID = mxIsScalar(prhs[0]) && mxGetClassID(prhs[0]) == mxUINT64_CLASS;
    if (!isSupportedID){
        mexErrMsgTxt("A valid scalar uint64 ID serial port expected.");
    }
    if (!isValidPortPtr(ptrID[0])) {
        mexErrMsgTxt("A valid ID serial port expected.");
    }
    m_port = (c_serial_port_t*)(ptrID[0]);

    if (c_serial_is_open(m_port) == 0) {
        mexErrMsgTxt("Port is not open.");
    }
    status = c_serial_write_data( m_port, data, &data_length );
    if( status < 0 ) {
        mexErrMsgTxt("Cannot write data.");
    }
}
//=============================================================================
