#include "Model.h"
#include "Graphic.h"


Model::Model(void)
{
	g_enableTextures = true;

	mColorTint[0] = 0.0;
	mColorTint[1] = 0.0;
	mColorTint[2] = 0.0;

	mRotateAxis = Vector3(0, 1, 0);
	mAngleRotate = 0;

	mWaitIsCalled = false;

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

Model::Model( const Model* other )
{
	memcpy(this, other, sizeof(*other));
}

void Model::setColorTint( GLfloat red, GLfloat green, GLfloat blue)
{
	mColorTint[0] = red;
	mColorTint[1] = green;
	mColorTint[2] = blue;
}

void Model::draw()
{
	const ModelOBJ::Mesh *pMesh = 0;
	const ModelOBJ::Material *pMaterial = 0;
	const ModelOBJ::Vertex *pVertices = 0;
	ModelTextures::const_iterator iter;

	for (int i = 0; i < getNumberOfMeshes(); ++i)
	{
		pMesh = &getMesh(i);
		pMaterial = pMesh->pMaterial;
		pVertices = getVertexBuffer();

		GLfloat ambi[4];
		GLfloat diff[4];

		for (int i = 0; i < 3; i++)
		{
			ambi[i] = pMaterial->ambient[i] + mColorTint[i];
			diff[i] = pMaterial->diffuse[i] + mColorTint[i];

			if (ambi[i] > 1.0) ambi[i] = 1.0;
			if (diff[i] > 1.0) diff[i] = 1.0;
		}

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambi);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pMaterial->specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pMaterial->shininess * 128.0f);

		if (g_enableTextures)
		{
			iter = mModelTextures.find(pMaterial->colorMapFilename);

			if (iter == mModelTextures.end())
			{
				glDisable(GL_TEXTURE_2D);
			}
			else
			{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, iter->second);
			}
		}
		else
		{
			glDisable(GL_TEXTURE_2D);
		}

		if (hasPositions())
		{
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, getVertexSize(),
				getVertexBuffer()->position);
		}

		if (hasTextureCoords())
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, getVertexSize(),
				getVertexBuffer()->texCoord);
		}

		if (hasNormals())
		{
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT, getVertexSize(),
				getVertexBuffer()->normal);
		}

		glDrawElements(GL_TRIANGLES, pMesh->triangleCount * 3, GL_UNSIGNED_INT,
			getIndexBuffer() + pMesh->startIndex);

		if (hasNormals())
			glDisableClientState(GL_NORMAL_ARRAY);

		if (hasTextureCoords())
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		if (hasPositions())
			glDisableClientState(GL_VERTEX_ARRAY);
	}

}

void Model::loadModel(const char *pszFilename)
{
	// Import the OBJ file and normalize to unit length.


	if (!import(pszFilename))
	{
		throw std::runtime_error("Failed to load model.");
	}

	minVec.set( - getWidth()/2,  - getHeight()/2,  - getLength()/2);
	maxVec.set( + getWidth()/2,  + getHeight()/2,  + getLength()/2);

	// Load any associated textures.
	// Note the path where the textures are assumed to be located.

	const ModelOBJ::Material *pMaterial = 0;
	GLuint textureId = 0;
	std::string::size_type offset = 0;
	std::string filename;

	for (int i = 0; i < getNumberOfMaterials(); ++i)
	{
		pMaterial = &getMaterial(i);

		// Look for and load any diffuse color map textures.

		if (pMaterial->colorMapFilename.empty())
			continue;

		// Try load the texture using the path in the .MTL file.
		textureId = loadTexture(pMaterial->colorMapFilename.c_str());

		if (!textureId)
		{
			offset = pMaterial->colorMapFilename.find_last_of('\\');

			if (offset != std::string::npos)
				filename = pMaterial->colorMapFilename.substr(++offset);
			else
				filename = pMaterial->colorMapFilename;

			// Try loading the texture from the same directory as the OBJ file.
			textureId = loadTexture((getPath() + filename).c_str());
		}

		if (textureId)
			mModelTextures[pMaterial->colorMapFilename] = textureId;

		// Look for and load any normal map textures.

		if (pMaterial->bumpMapFilename.empty())
			continue;

		// Try load the texture using the path in the .MTL file.
		textureId = loadTexture(pMaterial->bumpMapFilename.c_str());

		if (!textureId)
		{
			offset = pMaterial->bumpMapFilename.find_last_of('\\');

			if (offset != std::string::npos)
				filename = pMaterial->bumpMapFilename.substr(++offset);
			else
				filename = pMaterial->bumpMapFilename;

			// Try loading the texture from the same directory as the OBJ file.
			textureId = loadTexture((getPath() + filename).c_str());
		}

		if (textureId)
			mModelTextures[pMaterial->bumpMapFilename] = textureId;
	}
}

GLuint Model::loadTexture(const char *pszFilename)
{
	GLuint id = SOIL_load_OGL_texture(
		pszFilename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	if( 0 != id )
	{
		glBindTexture(GL_TEXTURE_2D, id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	return id;
}

void Model::drawModel()
{
	update();
}

void Model::update()
{

}

void Model::shadowMatrix(GLfloat shadowMat[4][4], GLfloat groundplane[4], GLfloat lightpos[4])
{
	GLfloat dot;

	/* Find dot product between light position vector and ground plane normal. */
	dot = groundplane[0] * lightpos[0] +
		groundplane[1] * lightpos[1] +
		groundplane[2] * lightpos[2] +
		groundplane[3] * lightpos[3];

	shadowMat[0][0] = dot - lightpos[0] * groundplane[0];
	shadowMat[1][0] = 0.f - lightpos[0] * groundplane[1];
	shadowMat[2][0] = 0.f - lightpos[0] * groundplane[2];
	shadowMat[3][0] = 0.f - lightpos[0] * groundplane[3];

	shadowMat[0][1] = 0.f - lightpos[1] * groundplane[0];
	shadowMat[1][1] = dot - lightpos[1] * groundplane[1];
	shadowMat[2][1] = 0.f - lightpos[1] * groundplane[2];
	shadowMat[3][1] = 0.f - lightpos[1] * groundplane[3];

	shadowMat[0][2] = 0.f - lightpos[2] * groundplane[0];
	shadowMat[1][2] = 0.f - lightpos[2] * groundplane[1];
	shadowMat[2][2] = dot - lightpos[2] * groundplane[2];
	shadowMat[3][2] = 0.f - lightpos[2] * groundplane[3];

	shadowMat[0][3] = 0.f - lightpos[3] * groundplane[0];
	shadowMat[1][3] = 0.f - lightpos[3] * groundplane[1];
	shadowMat[2][3] = 0.f - lightpos[3] * groundplane[2];
	shadowMat[3][3] = dot - lightpos[3] * groundplane[3];

}

BoundingBox Model::boundingbox()
{
	minVec.set( - getWidth()/2,  - getHeight()/2,  - getLength()/2);
	maxVec.set( + getWidth()/2,  + getHeight()/2,  + getLength()/2);
	Vector3 mAnchorOffset(mAnchor.x*getWidth(), mAnchor.y*getHeight(),
		mAnchor.z*getLength());
	return BoundingBox(minVec+mPos-mAnchorOffset, maxVec+mPos-mAnchorOffset);
}

Model::~Model(void)
{
}
