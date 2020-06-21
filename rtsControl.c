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
#include <string.h>
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
    char rtsControlAsCharacter[255];
    int rtsControl = CSERIAL_RTS_NONE;
    int res = 0;
    mxUint64 *ptrID = NULL;
    if (nrhs != 2) {
        mexErrMsgTxt("Wrong numbers of input arguments.");
    }
    if (nlhs > 1) {
        mexErrMsgTxt("Wrong numbers of output arguments.");
    }
    ptrID = (mxUint64 *)mxGetData(prhs[0]);
    if (!isValidPortPtr(ptrID[0])) {
        mexErrMsgTxt("A valid ID serial port expected.");
    }
    m_port = (c_serial_port_t*)(ptrID[0]);
    if (c_serial_is_open(m_port) == 0) {
        mexErrMsgTxt("Port is not open.");
    }
    mxGetString(prhs[1], rtsControlAsCharacter, sizeof(rtsControlAsCharacter));
    if (strcmp(rtsControlAsCharacter, "none") == 0) {
        rtsControl = CSERIAL_RTS_NONE;
    } else if (strcmp(rtsControlAsCharacter, "hard") == 0) {
        rtsControl = CSERIAL_RTS_HARDWARE;
    } else if (strcmp(rtsControlAsCharacter, "soft") == 0) {
        rtsControl = CSERIAL_RTS_SOFTWARE;
    } else if (strcmp(rtsControlAsCharacter, "best") == 0) {
        rtsControl = CSERIAL_RTS_BEST_AVAILABLE;
    } else {
        mexErrMsgTxt("Invalid RTS control value. 'none', 'hard', 'soft' or 'best' expected.");    
    }
    res = c_serial_set_rts_control(m_port, rtsControl);
    plhs[0] = mxCreateLogicalScalar(res);
}
//=============================================================================
