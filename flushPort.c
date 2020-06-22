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
    mxUint64 *ptrID = NULL; 
    bool isSupported = false;

    if (nrhs != 1) {
        mexErrMsgTxt("Wrong numbers of input arguments.");
    }
    if (nlhs > 0) {
        mexErrMsgTxt("Wrong numbers of output arguments.");
    }
    isSupported = mxIsScalar(prhs[0]) && mxGetClassID(prhs[0]) == mxUINT64_CLASS;
    if (!isSupported){
        mexErrMsgTxt("A valid scalar uint64 ID serial port expected.");
    }
    ptrID = (mxUint64 *)mxGetData(prhs[0]);
    if (!isValidPortPtr(ptrID[0])) {
        mexErrMsgTxt("A valid ID serial port expected.");
    }
    m_port = (c_serial_port_t*)(ptrID[0]);
    if (c_serial_is_open(m_port) == 0) {
        mexErrMsgTxt("Port is not open.");
    }
    c_serial_flush(m_port);
}
//=============================================================================
