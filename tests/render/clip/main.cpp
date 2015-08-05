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
// Validates near plane clipping by rendering triangles who's Z coordinate
// is less than one.
//

#include <math.h>
#include <Matrix.h>
#include <RenderContext.h>
#include <RenderTarget.h>
#include <schedule.h>
#include <stdlib.h>
#include "CheckerboardShader.h"
#include "room.h"

using namespace librender;

const int kFbWidth = 640;
const int kFbHeight = 480;
	
// All threads start execution here.
int main()
{
	if (__builtin_nyuzi_read_control_reg(0) != 0)
		workerThread();

	// Start worker threads
	__builtin_nyuzi_write_control_reg(30, 0xffffffff);

	RenderContext *context = new RenderContext();
	RenderTarget *renderTarget = new RenderTarget();
	Surface *colorBuffer = new Surface(kFbWidth, kFbHeight, (void*) 0x200000);
	Surface *depthBuffer = new Surface(kFbWidth, kFbHeight);
	renderTarget->setColorBuffer(colorBuffer);
	renderTarget->setDepthBuffer(depthBuffer);
	context->bindTarget(renderTarget);
	context->enableDepthBuffer(true);
	context->bindShader(new CheckerboardShader());

	const RenderBuffer kVertices(kRoomVertices, kNumRoomVertices, 5 * sizeof(float));
	const RenderBuffer kIndices(kRoomIndices, kNumRoomIndices, sizeof(int));
	context->bindVertexAttrs(&kVertices);

	Matrix projectionMatrix = Matrix::getProjectionMatrix(kFbWidth, kFbHeight);
	Matrix modelViewMatrix = Matrix::getRotationMatrix(M_PI / 3, Vec3(0.0f, 1.0f, 0.0f));
	Matrix rotationMatrix = Matrix::getRotationMatrix(M_PI / 16, Vec3(0.0f, 1.0f, 0.0f));

	for (int frame = 0; frame < 1; frame++)
	{
		CheckerboardUniforms uniforms;
		uniforms.fMVPMatrix = projectionMatrix * modelViewMatrix;
		context->bindUniforms(&uniforms, sizeof(uniforms));
		context->drawElements(&kIndices);
		context->finish();
		modelViewMatrix *= rotationMatrix;
	}
	
	exit(1);	// Stop worker threads
	return 0;
}
