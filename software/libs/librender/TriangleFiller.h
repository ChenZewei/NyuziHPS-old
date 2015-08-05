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

#include <stdint.h>
#include "LinearInterpolator.h"
#include "RenderState.h"
#include "RenderTarget.h"
#include "Shader.h"

namespace librender
{

const int kMaxParams = 16;

// This represents the state for one triangle at a time. It's called by the 
// rasterizer for each 4x4 batch of pixels. It computes the colors for 
// them by calling into the shader, then writes them back to the render target.  
class TriangleFiller
{
public:
	TriangleFiller(RenderTarget *target);
	
	TriangleFiller(const TriangleFiller&) = delete;
	TriangleFiller& operator=(const TriangleFiller&) = delete;

	// Called by rasterizer to fill a 4x4 block.  The left and top coordinates
	// are in raster space, representing the count of pixels from the upper
	// left corner. 
	void fillMasked(int left, int top, unsigned short mask);

	// Set up interpolation for triangle
	void setUpTriangle(const RenderState *state,
		float x1, float y1, float z1, 
		float x2, float y2, float z2,
		float x3, float y3, float z3);
	void setUpParam(float c1, float c2, float c3);

private:
	void setUpInterpolator(LinearInterpolator &interpolator, float c0, float c1, 
		float c2);
	
	const RenderState *fState = nullptr;
	RenderTarget *fTarget;
	
	// 2.0 divided by the resolution of the screen in pixels. Used to convert
	// from raster coordinates to screen space (-1.0 to 1.0).
	float fTwoOverWidth;
	float fTwoOverHeight;

	// Parameter interpolation
	LinearInterpolator fOneOverZInterpolator;
	struct 
	{
		bool isConstant;
		float constantValue;
		LinearInterpolator linearInterpolator;
	} fParameters[kMaxParams];
	int fNumParams = 0;
	float fZ0;
	float fZ1;
	float fZ2;
	float fX0;
	float fY0;
	bool fNeedPerspective;
	
	// Inverse gradient matrix
	float fInvGradientMatrix00;
	float fInvGradientMatrix01;
	float fInvGradientMatrix10;
	float fInvGradientMatrix11;
};

}
