# Free DSP coefficient tables

Source: dolphin-emu/dolphin at commit `eb236466c4f0ec8bef619add0972353d3996fe6c`, `Data/Sys/GC/dsp_coef.bin` and `docs/DSP/free_dsp_rom/dsp_rom_readme.txt`.

SHA256 of the unmodified coefficient binary: `d7741279c2e8ec5c5fb318f8fbdd6de6bf583520d288e836a5383233a4238179`.

The included COPYING contains Dolphin's GPL-2.0-or-later license. Preserve attribution and license with redistribution of these tables and their generated representation. `diagnostics/generate_ax_src.py` reads big-endian signed 16-bit words and emits the first three 512-word banks into `src/ax_src_coefficients.inc`. They are free replacement coefficients, not a Nintendo DSP ROM dump or a promise of bit-exact equivalence.
