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
#include "c_serial.h"
//=============================================================================
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    c_serial_port_t* m_port;
    if (nrhs != 1) {
        mexErrMsgIdAndTxt("cserial:arrayProduct:nrhs","Please send serial port object.");
    }
    if (nlhs > 0) {
        mexErrMsgIdAndTxt("cserial:arrayProduct:nlhs", "");
    }
    m_port = (c_serial_port_t*)(*((uint64_t *)mxGetData(prhs[0])));
    c_serial_free(m_port);
}
//=============================================================================
