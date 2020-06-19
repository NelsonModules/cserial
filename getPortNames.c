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
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    const char** allPortList = NULL;
    int i = 0;
    int n = 0;   
    if (nrhs != 0) {
        mexErrMsgIdAndTxt("cserial:nrhs", "Wrong numbers of input arguments.");
    }
    allPortList = c_serial_get_serial_ports_list();
    while (allPortList[i] != NULL) {
        i++;        
    }
    n = i;
    for (int k = 0; k < nlhs; ++k) {
        if (k < n ){
            plhs[k] = mxCreateString(allPortList[k]);
        } else {
            plhs[k] = mxCreateString("NO PORT.");
        }
    }
    c_serial_free_serial_ports_list(allPortList);   
}
//=============================================================================
