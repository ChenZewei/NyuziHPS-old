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


#pragma once

typedef void (*ParallelFunc)(void *context, int index);

#ifdef __cplusplus
extern "C" {
#endif

// parallelSpawn should only be called from the main thread. It waits for
// all jobs to complete before returning.
void parallelExecute(ParallelFunc func, void *context, int numElements);

// main should call this function for all threads other than 0.
void workerThread() __attribute__ ((noreturn));

#ifdef __cplusplus
}
#endif

