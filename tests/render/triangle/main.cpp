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


//
// Validates alpha blending
//

#include <math.h>
#include <schedule.h>
#include <stdlib.h>
#include <Matrix.h>
#include <RenderTarget.h>
#include <RenderContext.h>
#include "ColorShader.h"

using namespace librender;

const int kFbWidth = 640;
const int kFbHeight = 480;

static float kTriangleVertices[] = {
	// Position            Color (RGBA)
	 0.0,  -0.9, -1.0,     1.0, 0.0, 0.0, 1.0,
	 0.9, 0.9, -1.0,       0.0, 1.0, 0.0, 1.0,
	 -0.9, 0.9, -1.0,      0.0, 0.0, 1.0, 1.0,
};

static int kTriangleIndices[] = { 0, 1, 2 };

// All threads start execution here.
int main()
{
	if (__builtin_nyuzi_read_control_reg(0) != 0)
		workerThread();

	// Start worker threads
	__builtin_nyuzi_write_control_reg(30, 0xffffffff);

	const RenderBuffer vertexBuffer(kTriangleVertices, 3, 7 * sizeof(float));
	const RenderBuffer indexBuffer(kTriangleIndices, 3, 4);
	RenderContext *context = new RenderContext();
	RenderTarget *renderTarget = new RenderTarget();
	Surface *colorBuffer = new Surface(kFbWidth, kFbHeight, (void*) 0x200000);
	renderTarget->setColorBuffer(colorBuffer);
	context->clearColorBuffer();
	context->bindTarget(renderTarget);
	context->bindShader(new ColorShader());
	context->bindVertexAttrs(&vertexBuffer);
	context->drawElements(&indexBuffer);
	context->finish();

	exit(1);	// Stop worker threads

	return 0;
}
