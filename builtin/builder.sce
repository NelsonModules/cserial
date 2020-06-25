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
// Scilab cannot build multiple mex as other tools ...
//=============================================================================
functionsName = ["openPort";
"closePort";
"writePort";
"readPort";
"getPortNames";
"flushPort";
"getPortConfig"];
//=============================================================================
for n = functionsName'
    libname = strcat(['mexsci', n]);
    fun_table = [n, n, 'cmex'];
    files = [strcat([n, '.c']), 'c_serial.c'];
    ilib_mex_build(libname, fun_table, files, [], '', '', '', '', '-I.');
end
//=============================================================================
deletefile('cleaner.sce');
deletefile('loader.sce');
//=============================================================================
txt = ['mex_path = get_absolute_file_path(''loader.sce'');'];
for n = functionsName'
    libname = strcat(['mexsci', n]);
    l = 'addinter(mex_path + filesep() + ''' + libname + ''' + getdynlibext(), ''' + libname + ''', ''' + n + ''');'
    txt = [txt; l];
end
mputl(txt, 'loader.sce');
//=============================================================================
