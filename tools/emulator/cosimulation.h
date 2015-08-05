// 
// Copyright 2011-2015 Jeff Bush
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// 


#ifndef __COSIMULATION_H
#define __COSIMULATION_H

#include "core.h"

int runCosimulation(Core *core, int verbose);
void cosimSetScalarReg(Core *core, uint32_t pc, int reg, uint32_t value);
void cosimSetVectorReg(Core *core, uint32_t pc, int reg, int mask, const uint32_t value[16]);
void cosimWriteBlock(Core *core, uint32_t pc, uint32_t address, int mask, const uint32_t values[16]);
void cosimWriteMemory(Core *core, uint32_t pc, uint32_t address, size_t size, uint32_t value);

#endif
