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
#include <matrix.h>
#include <c_serial.h>
#include <math.h>
#include <stdint.h>
//=============================================================================
static c_serial_port_t* m_port = NULL;
//=============================================================================
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    int status = 0;
    int bytes_read = 0;
    int data_length = 0;
    uint8_t *data = NULL;
    mwSize total_num_of_elements = 0;
    mwSize index = 0;

    if (nrhs != 2) {
        mexErrMsgIdAndTxt("cserial:arrayProduct:nrhs", "Please send serial port object and msg.");
    }
    if (nlhs != 0) {
        mexErrMsgIdAndTxt("cserial:arrayProduct:nlhs", "No outputs here.");
    }
    if (mxGetClassID(prhs[1]) != mxUINT8_CLASS){
        mexErrMsgIdAndTxt("cserial:arrayProduct:nlhs", "Write data is not a vector of uint8 numbers, please convert.");
    }
    data = (uint8_t *)mxGetData(prhs[1]);
    data_length = mxGetNumberOfElements(prhs[1]);
    m_port =(c_serial_port_t*)(*((uint64_t *)mxGetData(prhs[0])));
    status = c_serial_write_data( m_port, data, &data_length );
    if( status < 0 ){
        mexPrintf("can't write data");
    }
}
//=============================================================================