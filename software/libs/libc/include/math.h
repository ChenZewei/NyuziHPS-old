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

#define M_PI 3.1415

#ifdef __cplusplus
extern "C" {
#endif

double fmod(double val1, double val2);
double sin(double angle);
double cos(double angle);
double fabs(double value);
float sinf(float angle);
float cosf(float angle);
double sqrt(double value);
float sqrtf(float value);
float floorf(float value);
float ceilf(float value);

#ifdef __cplusplus
}
#endif
