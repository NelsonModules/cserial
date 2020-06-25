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
#include <stdint.h>
#include "c_serial.h"
#include "portHelpers.h"
//=============================================================================
#define FIELDNAME_NAME "name"
#define FIELDNAME_BAUDRATE "baudrate"
#define FIELDNAME_DATABITS "databits"
#define FIELDNAME_STOPBITS "stopbits"
#define FIELDNAME_PARITY "parity"
#define FIELDNAME_FLOWCONTROL "flowcontrol"
#define FIELDNAME_RTSCONTROL "rtscontrol"
//=============================================================================
static const char *parityToChar(enum CSerial_Parity parity);
static const char *flowControlToChar(enum CSerial_Flow_Control flowControl);
static const char *rtsControlToChar(enum CSerial_RTS_Handling rtsControl);
//=============================================================================
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    c_serial_port_t* m_port = NULL;
    mxUint64 *ptrID = NULL; 
    bool isSupported = false;
    if (nrhs != 1) {
        mexErrMsgTxt("Wrong numbers of input arguments.");
    }
    if (nlhs > 1) {
        mexErrMsgTxt("Wrong numbers of output arguments.");
    }
    isSupported = mxIsScalar(prhs[0]) && (mxGetClassID(prhs[0]) == mxUINT64_CLASS);
    if (!isSupported){
        mexErrMsgTxt("A valid scalar uint64 ID serial port expected.");
    }
    ptrID = (mxUint64 *)mxGetData(prhs[0]);
    if (!isValidPortPtr(ptrID[0])) {
        mexErrMsgTxt("A valid ID serial port expected.");
    }
    m_port = (c_serial_port_t*)(ptrID[0]);

    const char* portName = c_serial_get_port_name( m_port);
    int baudRate = (int)c_serial_get_baud_rate(m_port);
    int dataBits = (int)c_serial_get_data_bits(m_port);
    int stopBits = (int)c_serial_get_stop_btis(m_port);

    const char* field_names[] = {FIELDNAME_NAME, 
    FIELDNAME_BAUDRATE, 
    FIELDNAME_DATABITS, 
    FIELDNAME_STOPBITS,
    FIELDNAME_PARITY,
    FIELDNAME_FLOWCONTROL, 
    FIELDNAME_RTSCONTROL};

    mwSize dims[2] = {1, 1};
    plhs[0] = mxCreateStructArray(2, dims, sizeof(field_names) / sizeof(*field_names), field_names);

    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], FIELDNAME_NAME), mxCreateString(portName));
   
    mxArray* value = mxCreateDoubleMatrix(1, 1, mxREAL);
    *mxGetPr(value) = (double)baudRate;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], FIELDNAME_BAUDRATE), value);
   
    value = mxCreateDoubleMatrix(1, 1, mxREAL);
    *mxGetPr(value) = (double)dataBits;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], FIELDNAME_DATABITS), value);

    value = mxCreateDoubleMatrix(1, 1, mxREAL);
    *mxGetPr(value) = (double)stopBits;
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], FIELDNAME_STOPBITS), value);

    const char *parity = parityToChar(c_serial_get_parity(m_port));
    const char *flowControl = flowControlToChar(c_serial_get_flow_control(m_port));
    const char *rtsControl = rtsControlToChar(c_serial_get_rts_control(m_port));

    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], FIELDNAME_PARITY), mxCreateString(parity));
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], FIELDNAME_FLOWCONTROL), mxCreateString(flowControl));
    mxSetFieldByNumber(plhs[0], 0, mxGetFieldNumber(plhs[0], FIELDNAME_RTSCONTROL), mxCreateString(rtsControl));
}
//=============================================================================
const char *parityToChar(enum CSerial_Parity parity) {
    switch (parity) {
        case CSERIAL_PARITY_NONE:
            return "none";
        case CSERIAL_PARITY_ODD:
            return "odd";
        case CSERIAL_PARITY_EVEN:
            return "even";
        default:
            return "";
    }
    return "";
}
//=============================================================================
const char *flowControlToChar(enum CSerial_Flow_Control flowControl) {
    switch (flowControl) {
        case CSERIAL_FLOW_NONE:
            return "none";
        case CSERIAL_FLOW_HARDWARE:
            return "hard";
        case CSERIAL_FLOW_SOFTWARE:
            return "soft";
        default:
            return "";
    }
    return "";
}
//=============================================================================
const char *rtsControlToChar(enum CSerial_RTS_Handling rtsControl) {
    switch (rtsControl) {
        case CSERIAL_RTS_NONE:
            return "none";
        case CSERIAL_RTS_HARDWARE:
            return "hard";
        case CSERIAL_RTS_SOFTWARE:
            return "soft";
        case CSERIAL_RTS_BEST_AVAILABLE:
            return "best";
        default:
            return "";
    }
    return "";
    
}
//=============================================================================
