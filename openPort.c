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
//=============================================================================
static c_serial_port_t* m_port = NULL;
//=============================================================================
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    int status;
    char portName[255];
    double *baudRate = NULL;
    mxArray *out = NULL;
    if (nrhs != 2) {
        mexErrMsgIdAndTxt("cserial:nrhs", "Wrong numbers of input arguments.");
    }
    if (nlhs > 1) {
        mexErrMsgIdAndTxt("cserial:nlhs", "Wrong numbers of output arguments.");
    }

    mxGetString(prhs[0], portName, sizeof(portName));
    baudRate = mxGetPr(prhs[1]);
    if (c_serial_new( &m_port, NULL ) < 0) {
        mexErrMsgTxt("Unable to create new serial port.");
    }
    if (c_serial_set_port_name( m_port, (const char*) portName ) < 0) {
        mexErrMsgTxt("Cannot set port name.");
    }
    c_serial_set_baud_rate( m_port,((int)  baudRate[0]));
    c_serial_set_data_bits( m_port, CSERIAL_BITS_8 );
    c_serial_set_stop_bits( m_port, CSERIAL_STOP_BITS_1 );
    c_serial_set_parity( m_port, CSERIAL_PARITY_NONE );
    c_serial_set_flow_control( m_port, CSERIAL_FLOW_NONE );
    status = c_serial_open( m_port );
    if (status < 0) {
        mexErrMsgTxt("Cannot open serial port.");
    }
    out = mxCreateNumericMatrix(1, 1, mxUINT64_CLASS, mxREAL);
    *((uint64_t *)mxGetData(out)) = (uint64_t)(m_port);
    plhs[0] = out;
}
//=============================================================================
