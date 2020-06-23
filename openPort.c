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
static c_serial_port_t* m_port = NULL;
//=============================================================================
static void closePortsAtExit(void)
{
    size_t nbPorts = 0;
    mxUint64 * portsIds = getOpenPorts(&nbPorts);
    for (size_t k = 0; k < nbPorts; ++k) {
        m_port = (c_serial_port_t*)(portsIds[k]);
        if (c_serial_is_open(m_port)) {
            c_serial_free(m_port);
        }
    }
    removeAllPortPtr();
}
//=============================================================================
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    int status = 0;

    char portName[255];
    double *baudRatePtr = NULL;
    double *dataBitsPtr = NULL;
    double *stopBitsPtr = NULL;
    char parityAsCharacter[255];
    char flowControlAsCharacter[255];
    char rtsControlAsCharacter[255];

    int baudRate = CSERIAL_BAUD_9600;
    int dataBits = CSERIAL_BITS_8;
    int stopBits = CSERIAL_STOP_BITS_1;
    int parity = CSERIAL_PARITY_NONE;
    int flowControl = CSERIAL_FLOW_NONE;
    int rtsControl = CSERIAL_RTS_NONE;

    mxArray *out = NULL;
    if (nrhs < 2 || nrhs > 6) {
        mexErrMsgTxt("Wrong numbers of input arguments.");
    }
    if (nlhs > 1) {
        mexErrMsgTxt("Wrong numbers of output arguments.");
    }

    mxGetString(prhs[0], portName, sizeof(portName));
    baudRatePtr = mxGetPr(prhs[1]);
    baudRate = (int)baudRatePtr[0];
    switch (baudRate) {
        case CSERIAL_BAUD_0:
        case CSERIAL_BAUD_50:
        case CSERIAL_BAUD_100:
        case CSERIAL_BAUD_110:
        case CSERIAL_BAUD_134:
        case CSERIAL_BAUD_150:
        case CSERIAL_BAUD_200:
        case CSERIAL_BAUD_300:
        case CSERIAL_BAUD_600:
        case CSERIAL_BAUD_1200:
        case CSERIAL_BAUD_1800:
        case CSERIAL_BAUD_2400:
        case CSERIAL_BAUD_4800:
        case CSERIAL_BAUD_9600:
        case CSERIAL_BAUD_19200:
        case CSERIAL_BAUD_38400:
        case CSERIAL_BAUD_115200:
        case CSERIAL_BAUD_921600: {
        } break;
        default:{
            mexErrMsgTxt("Unsupported baud rate value.");
        } break;
    }


    if (nrhs > 2) {
        dataBitsPtr = mxGetPr(prhs[2]);
        dataBits = (int)dataBitsPtr[0];
        switch (dataBits) {
            case CSERIAL_BITS_5:
            case CSERIAL_BITS_6:
            case CSERIAL_BITS_7:
            case CSERIAL_BITS_8: {
            } break;
            default:{
                mexErrMsgTxt("Unsupported data bits value.");
            } break;
        }
    } 

    if (nrhs > 3) {
        stopBitsPtr = mxGetPr(prhs[3]);
        stopBits = (int)stopBitsPtr[0];
        if (stopBits < 0 || stopBits > 2) {
            mexErrMsgTxt("Invalid stop bit value. 1 or 2 expected.");
        }
    }

    if (nrhs > 4) {
        mxGetString(prhs[4], parityAsCharacter, sizeof(parityAsCharacter));
        if (strcmp(parityAsCharacter, "none") == 0) {
            parity = CSERIAL_PARITY_NONE;
        } else if (strcmp(parityAsCharacter, "odd") == 0) {
            parity = CSERIAL_PARITY_ODD;
        } else if (strcmp(parityAsCharacter, "even") == 0) {
            parity = CSERIAL_PARITY_EVEN;
        } else {
            mexErrMsgTxt("Invalid parity value. 'none', 'odd', or 'even' expected.");    
        }
    }

    if (nrhs > 5) {
        mxGetString(prhs[5], flowControlAsCharacter, sizeof(flowControlAsCharacter));
        if (strcmp(flowControlAsCharacter, "none") == 0) {
            flowControl = CSERIAL_FLOW_NONE;
        } else if (strcmp(flowControlAsCharacter, "hard") == 0) {
            flowControl = CSERIAL_FLOW_HARDWARE;
        } else if (strcmp(flowControlAsCharacter, "soft") == 0) {
            flowControl = CSERIAL_FLOW_SOFTWARE;
        } else {
            mexErrMsgTxt("Invalid flow control value. 'none', 'hard', or 'soft' expected.");    
        }
    }

    if (nrhs > 6) {
        mxGetString(prhs[6], rtsControlAsCharacter, sizeof(rtsControlAsCharacter));
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
    }

    if (c_serial_new( &m_port, NULL ) < 0) {
        mexErrMsgTxt("Unable to create new serial port.");
    }
    if (c_serial_set_port_name( m_port, (const char*) portName ) < 0) {
        mexErrMsgTxt("Cannot set port name.");
    }

    c_serial_set_baud_rate( m_port, baudRate);
    c_serial_set_data_bits( m_port, dataBits );
    c_serial_set_stop_bits( m_port, stopBits);
    c_serial_set_parity(m_port, parity );
    c_serial_set_flow_control(m_port, flowControl);
    c_serial_set_rts_control(m_port, rtsControl);

    status = c_serial_open(m_port);
    
    if (status < 0) {
        mexErrMsgTxt("Cannot open serial port.");
    }
   addPortPtr((mxUint64)(m_port));
    out = mxCreateNumericMatrix(1, 1, mxUINT64_CLASS, mxREAL);
    *((mxUint64 *)mxGetData(out)) = (mxUint64)(m_port);
    plhs[0] = out;
    mexAtExit(closePortsAtExit);
}
//=============================================================================
