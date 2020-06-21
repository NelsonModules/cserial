//=============================================================================
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
#pragma once
//=============================================================================
#include <mex.h>
#include <matrix.h>
//=============================================================================
bool isValidPortPtr(mxUint64 id) {
    mxArray *mxGlobalPorts = mexGetVariable("global", "CSERIAL_OPENED_PORTS");
    if (mxGlobalPorts != NULL) {
        if (!mxIsEmpty(mxGlobalPorts)) {
            size_t nbValues = mxGetNumberOfElements(mxGlobalPorts);
            mxUint64 *values = mxGetData(mxGlobalPorts);
            for (size_t k = 0; k < nbValues; ++k) {
                if (values[k] == id) {
                    return true;
                }
            }
        }
    }
    return false;
}
//=============================================================================
bool addPortPtr(mxUint64 id) {
    mxArray *mxGlobalPorts = mexGetVariable("global", "CSERIAL_OPENED_PORTS");
    if (mxGlobalPorts == NULL) {
         mxArray *mxNewGlobalPorts = mxCreateNumericMatrix(1, 1, mxUINT64_CLASS, mxREAL);
        *((mxUint64 *)mxGetData(mxNewGlobalPorts)) = id;        
        mexPutVariable("global", "CSERIAL_OPENED_PORTS", mxNewGlobalPorts);
        return true;
    } else {
        if (mxIsEmpty(mxGlobalPorts)) {
            mxArray *mxNewGlobalPorts = mxCreateNumericMatrix(1, 1, mxUINT64_CLASS, mxREAL);
            *((mxUint64 *)mxGetData(mxNewGlobalPorts)) = id;        
            mexPutVariable("global", "CSERIAL_OPENED_PORTS", mxNewGlobalPorts);
            mxDestroyArray(mxGlobalPorts);
            return true;
        } else {
            size_t nbValues = mxGetNumberOfElements(mxGlobalPorts);
            mxUint64 *values = mxGetData(mxGlobalPorts);
            mwSize ndim = 2;
            mwSize dims[2] = {1, 0};
            dims[1] = nbValues + 1;
            mxArray *mxNewGlobalPorts = mxCreateNumericArray(
            ndim, dims, mxUINT64_CLASS, mxREAL);
            mxUint64 *newValues = mxGetData(mxNewGlobalPorts);
            for (size_t k = 0; k < nbValues; ++k){
                newValues[k] = values[k]; 
            }
            newValues[nbValues] = (mxUint64)id;
            mexPutVariable("global", "CSERIAL_OPENED_PORTS", mxNewGlobalPorts);
            mxDestroyArray(mxGlobalPorts);
            return true;
        }
    }
    return false;
}
//=============================================================================
bool removePortPtr(mxUint64 id) {
    mxArray *mxGlobalPorts = mexGetVariable("global", "CSERIAL_OPENED_PORTS");
    if (mxGlobalPorts != NULL) {
        if (isValidPortPtr(id)) {
            size_t nbValues = mxGetNumberOfElements(mxGlobalPorts);
            mxUint64 *values = mxGetData(mxGlobalPorts);
            mwSize ndim = 2;
            mwSize dims[2] = {1, 0};
            dims[1] = nbValues - 1;
            mxArray *mxNewGlobalPorts = mxCreateNumericArray(
            ndim, dims, mxUINT64_CLASS, mxREAL);
            mxUint64 *newValues = mxGetData(mxNewGlobalPorts);
            size_t l = 0;
            for (size_t k = 0; k < nbValues; ++k) {
                if (values[k] != id) {
                    newValues[l] = values[k];
                    l++;  
                }
            }
            mxDestroyArray(mxGlobalPorts);
            return true;
        }
    }
    return false;
}
//=============================================================================
