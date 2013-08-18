//
//  GLMapRenderer.h
//  OpenSpades
//
//  Created by yvt on 7/13/13.
//  Copyright (c) 2013 yvt.jp. All rights reserved.
//

#pragma once

#include "../Client/IGameMapListener.h"
#include "../Core/Math.h"
#include "IGLDevice.h"
#include "../Client/IRenderer.h"
#include "GLDynamicLight.h"

namespace spades {
	namespace draw {
		class GLRenderer;
		class GLMapChunk;
		class GLProgram;
		class GLImage;
		class GLMapRenderer{
			
			friend class GLMapChunk;
			
		protected:
			GLRenderer *renderer;
			IGLDevice *device;
			
			GLProgram *basicProgram;
			GLProgram *dlightProgram;
			GLImage *aoImage;
			GLImage *detailImage;
			
			IGLDevice::UInteger squareVertexBuffer;
			
			struct ChunkRenderInfo {
				bool rendered;
				float distance;
			};
			GLMapChunk **chunks;
			ChunkRenderInfo *chunkInfos;
			
			client::GameMap *gameMap;
			
			int numChunkWidth, numChunkHeight;
			int numChunkDepth, numChunks;
			
			inline int GetChunkIndex(int x, int y, int z){
				return (x * numChunkHeight + y) * numChunkDepth + z;
			}
			
			inline GLMapChunk *GetChunk(int x, int y, int z) {
				return chunks[GetChunkIndex(x, y, z)];
			}
			
			void RealizeChunks(Vector3 eye);
			
			void DrawColumnSunlight(int cx, int cy, int cz, Vector3 eye);
			void DrawColumnDLight(int cx, int cy, int cz, Vector3 eye, const std::vector<GLDynamicLight>& lights);
			
		public:
			GLMapRenderer(client::GameMap *, GLRenderer *);
			virtual ~GLMapRenderer();
			
			void GameMapChanged(int x, int y, int z, client::GameMap *);
			
			client::GameMap *GetMap() { return gameMap; }
			
			void Prerender();
			void RenderSunlightPass();
			void RenderDynamicLightPass(std::vector<GLDynamicLight> lights);
		};
	}
}