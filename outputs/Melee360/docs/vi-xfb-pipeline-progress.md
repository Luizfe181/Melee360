# Original VI/XFB pipeline on Xbox — 2026-10-03

## Implemented

The running XEX compiles all original video.c function bodies, including HSD_VIInit, HSD_VICopyXFBAsync, draw-done/retrace callbacks, framebuffer state transitions and configuration helpers. Relative includes and the compiler-specific alignment declaration are adapted; the base checkout is unchanged. The original HSD color/alpha/Z state-setter bodies are extracted into hsd_copy_state.c and share their real cache variables with the audit remainder.

Native bootstrap creates two GPU-backed XFB textures and a black scanout texture. The HSD framebuffer addresses are registered native texture handles, treated as opaque by the original state machine. GXCopyDisp resolves real EDRAM rendering into the selected XFB and performs requested color/depth clears. A GPU fence triggers the original draw-done callback. Original pre/post retrace callbacks select NEXT, commit the VI buffer, release the old DISPLAY and advance the queue. Native presentation uses synchronized D3D Swap on the selected XFB rather than the former direct Present on the render target.

VIConfigure, VISetNextFrameBuffer and VISetBlack stage changes; VIFlush commits them under the native interrupt lock. VIWaitForRetrace performs a real synchronized repeat swap and dispatches the original callbacks. It does not sleep and invent a retrace. VIGetNextField reports the supported progressive field. Callbacks remain tied to the render thread/presentation boundary; physical interrupt timing is not emulated.

GX display-copy adapters now supply source/destination size, identity Y scale, copy clear, full clamp, identity gamma and disabled AA/vertical filtering. Unsupported configurations assert explicitly. None of these adapters silently ignores a requested AA/filter/scaling mode. The normal path is full-size progressive RGB8/Z24.

## Validation

XDK Release/Compat build passed with existing warnings. Xenia TrainingPreview passed with 45 GPU texture cases, 694 TEV cases, native VIWaitForRetrace, staged buffer/black commit tests and 120 real synchronized XFB swaps. Every normal presentation verifies a DISPLAY buffer matching the active native VI buffer, no waiting fence and exactly one FREE buffer. The wait probe introduces one real repeat swap before normal frames, so the 120-swap marker appears at normal frame 119; the separate 120-frame marker also passes.

Battlefield StagePreview passed four variants with 120 animation updates each, no skipped meshes and the existing unsupported callbacks (4/4/4/2). That run preceded removal of the unused third XFB allocation; final TrainingPreview was repeated with two allocations. No native rendering logic changed in that cleanup. Logs: ../logs/xfb-build.txt, ../logs/xfb-xenia.txt, ../logs/xfb-stage-xenia.txt. Original-body provenance: ../logs/hsd-xfb-original-provenance.json.

Mario/Link audits: 69 unresolved symbols, zero duplicates in normal and extended HSD paths (previous 83). The fourteen removed linker dependencies are six VI services and eight GX display-copy APIs. They have the constrained implementations described above; symbol resolution does not mean every hardware mode is finished. Fighter_Create still neither links nor executes. Audio AI/AX voices, remaining GX features, OS reset/thread services, MCC and THP helpers remain.

## Real remaining limitations

AA/interlaced modes are NOT complete or enabled. GXSetPixelFmt still rejects RGB565/Z16 and nonlinear Z encodings. GXSetCopyFilter rejects AA and the original seven-tap vertical filter. Display-copy resampling, custom sample positions, gamma 1.7/2.2, TOPHALF/BOTTOMHALF overlap copies and field-rendering raster masks still need actual implementations and GPU tests. Merely accepting those flags would be incorrect. Next work must supply quantized color/depth targets or verified shader conversion, sample/filter behavior and field assembly before enabling those original modes.

These native XFB handles are not raw GameCube YUYV memory. CPU reads/writes, snapshots or unregistered buffers require an additional encoding/registration bridge; unregistered pointers are rejected. Original HSD_AllocateXFB is not the allocator used by this bootstrap. The original no-yield flush loop would require asynchronous callback progress if entered with a pending queue; this render-thread adapter does not claim that path works. Swap has a void XDK API, so verification observes subsequent state/callback/frame progress rather than an invented success HRESULT from Swap.

Copy/fence synchronization may add cost; no hardware performance test or optimization is claimed. Production is published only after successful verification. Previous production image is saved to workspace work/default-before-xfb-pipeline.xex; SHA256 is recorded in ../logs/RGH-image-sha256.json.
