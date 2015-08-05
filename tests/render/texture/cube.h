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

const int kNumCubeVertices = 24;
const float kCubeVertices[] = {
	// Front face
	0.5, -0.5, 0.5, 1.0, 0.0,
	-0.5, -0.5, 0.5, 1.0, 1.0,
	-0.5, 0.5, 0.5, 0.0, 1.0,
	0.5, 0.5, 0.5, 0.0, 0.0,

	// Right side
	0.5, 0.5, 0.5, 1.0, 0.0,
	0.5, 0.5, -0.5, 1.0, 1.0,
	0.5, -0.5, -0.5, 0.0, 1.0,
	0.5, -0.5, 0.5, 0.0, 0.0,

	// Left side
	-0.5, 0.5, 0.5, 0.0, 0.0,
	-0.5, -0.5, 0.5, 1.0, 0.0,
	-0.5, -0.5, -0.5, 1.0, 1.0,
	-0.5, 0.5, -0.5, 0.0, 1.0,

	// Back
	0.5, 0.5, -0.5, 0.0, 0.0,
	-0.5, 0.5, -0.5, 1.0, 0.0,
	-0.5, -0.5, -0.5, 1.0, 1.0,
	0.5, -0.5, -0.5, 0.0, 1.0,

	// Top
	-0.5, 0.5, 0.5, 0.0, 0.0,
	-0.5, 0.5, -0.5, 1.0, 0.0,
	0.5, 0.5, -0.5, 1.0, 1.0,
	0.5, 0.5, 0.5, 0.0, 1.0,

	// Bottom
	0.5, -0.5, 0.5, 0.0, 0.0,
	0.5, -0.5, -0.5, 1.0, 0.0,
	-0.5, -0.5, -0.5, 1.0, 1.0,
	-0.5, -0.5, 0.5, 0.0, 1.0
};

const int kNumCubeIndices = 36;
const int kCubeIndices[] = {
	2, 1, 0, 
	0, 3, 2, 
	6, 5, 4, 
	4, 7, 6, 
	10, 9, 8, 
	8, 11, 10, 
	14, 13, 12, 
	12, 15, 14, 
	18, 17, 16, 
	16, 19, 18, 
	22, 21, 20, 
	20, 23, 22
};
