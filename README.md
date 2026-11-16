# UIS8581A Kernel Source Recovery Platform

**UIS8581A** = Unisoc SC9863A (sharkl3) used in FYT Android head units.

**Goal**: Full buildable kernel + all vendor modules. Uses ccache for fast rebuilds.

## GitHub Actions

Push → builds kernel Image + dtbs + vendor modules in ~5-10 min (32-core runners, ccache).
Download from workflow artifacts.

## Build Architecture

| Component | Source | Match |
|---|---|---|
| Base kernel 4.14.133 | `strongtz/linux-sprd` | exact |
| WLAN (sprdwl_ng) | `Yazz246/Aether_Kernel-A665L` → marlin3_sipc | 98.2% |
| BT (sprdbt_tty) | `kanadenadi/android_kernel_sprd_sc9832e` → tty-sdio | 93.9% |
| FM (sprd_fm) | same → fm_sdio | 97.7% |
| CPP (sprd_cpp) | `Hadenix/android_kernel_zte_sc9863a` → lite_r4p0 | 94.7% |
| Flash (flash_ic_ocp8137) | ZTE → sprd_camera/flash | 85.7% |
| HXchipset touch | Aether → hxchipset_v3_3 | 77% |
| Camera ISP2.6 | unreleased (LSEC BSP) | REA pending |
| pvrsrvkm, jadardTS, etc | shipped prebuilt .ko | n/a |

## Local Dev

```bash
# On the head unit or any aarch64 Linux:
apt install gcc-aarch64-linux-gnu ccache device-tree-compiler make
cp running.config source/.config
make -j$(nproc) ARCH=arm64 CROSS_COMPILE="ccache aarch64-linux-gnu-" olddefconfig Image
```

## Patches

Patches in `patches/` fix GCC 16+ compat issues:
- dtc `-fcommon` (multiple yylloc defs)
- WCN_BOUND_XO_MODE for UMW2653
- vdso-offsets.h for sigtramp
