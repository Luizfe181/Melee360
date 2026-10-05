#ifndef MELEE360_GX_MESH_H
#define MELEE360_GX_MESH_H
struct Melee360MeshVertex {float position[3],normal[3],uv[2];unsigned int color,matrix,envelope;};
// Raw, unrelocated big-endian archive data. Caller releases vertices with free().
// Returns 1 on success, 0 on malformed data, -1 for an unsupported GX feature.
int Melee360DecodeGxMesh(const unsigned char* data,unsigned int bytes,unsigned int pobj,
    Melee360MeshVertex** vertices,unsigned int* count,unsigned int* unsupported);
#endif
