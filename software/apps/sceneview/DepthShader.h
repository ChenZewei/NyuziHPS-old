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

#ifndef __DEPTH_SHADER_H
#define __DEPTH_SHADER_H

#include <Matrix.h>
#include <Shader.h>

using namespace librender;

struct DepthUniforms
{
	Matrix fMVPMatrix;
};

// Represents depth as a brightness
class DepthShader : public Shader
{
public:
	DepthShader()
		:	Shader(8, 5)
	{
	}

	void shadeVertices(vecf16_t *outParams, const vecf16_t *inAttribs, const void *_uniforms,
        int) const override
	{
        const DepthUniforms *uniforms = static_cast<const DepthUniforms*>(_uniforms);
        
		// Multiply vertex position by mvp matrix
		vecf16_t coord[4];
		for (int i = 0; i < 3; i++)
			coord[i] = inAttribs[i];
			
		coord[3] = splatf(1.0f);
		uniforms->fMVPMatrix.mulVec(outParams, coord); 

		// Copy depth
		outParams[4] = outParams[2];
	}

	void shadePixels(vecf16_t outColor[4], const vecf16_t inParams[16],
		const void *, const Texture * const [kMaxActiveTextures],
		unsigned short ) const override
	{
		// Scale depth value.
		// XXX this is hardcoded based on the size of the model. The last parameter
		// may need to be changed for other ones.
		vecf16_t depthval = splatf(1.0) - ((-inParams[0] - splatf(1.0)) / splatf(20.0));

		outColor[kColorR] = depthval;
		outColor[kColorG] = depthval;
		outColor[kColorB] = depthval;
		outColor[kColorA] = splatf(1.0);
	}
};

#endif

