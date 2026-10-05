#include "gx_direct.hlsl"
// Diagnostic only: bypass TEV, textures, fog, alpha test and packing.
float4 PSDiagnostic(VertexOut i):COLOR0{return i.color;}
