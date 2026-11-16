# UIS8581A (FYT8581) Android Head Unit Kernel Rebuild Project

## Environment
- **Host**: chroot on the head unit itself (Debian/Kali arm64 userspace over Android).
- **Root fs**: `/` is userdata f2fs (52G, ~21G free). `/sdcard` = /data/media. `/proc`, `/sys` live.
- **Source tree**: `/linux-sprd` (git clone of https://github.com/strongtz/linux-sprd, single commit d834a127a "Initial commit", branch main).
- **Kernel version match**: tree is Linux 4.14.133 — exact match to running kernel `4.14.133 #204 SMP PREEMPT Thu Jul 30 14:20:18 CST 2026 armv8l`.
- **Toolchain**: only binutils-aarch64-linux-gnu present (no gcc/clang yet). `apt-get install device-tree-compiler` already done. Cross gcc/clang still needed for build.

## Target hardware
- SoC: Unisoc UIS8581A (SC9863A family, sharkl3). `cpuinfo_hardware = "Unisoc UIS8581A"`.
- Board: `sprd,uis8581a2h10` (androidboot.hardware=uis8581a2h10). DT model "Spreadtrum UIS8581A2H10 Board".
- SC-ID: `<0x2687 0x01 0x20000>` (upstream sp9863a-2h10.dts uses `<9863 1 0x20000>`).
- LCD: icn6202_mipi2lvds, 1280x800, pixel_clock=64000000, lcd_base=fd482000, lcd_id=IDc16202ff.
- PMIC chipid 2721 (SC2721). crystal=3. ddrsize=4096M. ltemode=lcsfb. modem=shutdown. wifionly=1. rfboard.id=6, rfhw.id=1, lsecid=24.
- Boot cmdline (live): see /proc/cmdline; initrd root=/dev/ram0; boot_devices=soc/soc:ap-ahb/20600000.sdio.

## Artifacts collected (all under /root/uis8581a/artifacts/)
| File | Source | Notes |
|---|---|---|
| running.config | `/proc/config.gz` | 4933 lines, exact running kernel config |
| devtree.dts | `/sys/firmware/devicetree/base` via `dtc -I fs` | live DT (156KB) |
| dtbo.img | `/dev/block/mmcblk0p30` (8MB) | Android DTBO format (magic d7b7ab1e) |
| zImage | extracted from `/sdcard/.bak/stock_boot.img` via abootimg | ARM64 Image, 19.6MB, page size 2048 |
| bootimg.cfg | abootimg | kerneladdr 0x8000, ramdiskaddr 0x5400000 |
| initrd.img | abootimg | gzip cpio ramdisk; fstab.uis8581a2h10, overlay.d/magisk |
| config.gz | /proc/config.gz | raw |

## Loaded out-of-tree modules (/proc/modules) — REBUILD TARGETS
```
sprdwl_ng 327680 0 - Live ... (O)
flash_ic_ocp8137 16384 0 - Live ... (O)
sprdbt_tty 24576 2 - Live ... (O)
tcs3430 20480 0 - Live ... (O)
hxchipset 196608 0 - Live ...
jadardTS_ts 274432 0 - Live ...
nxp685x_fm 331776 0 - Live ... (O)
pvrsrvkm 1646592 244 - Live ... (O)
sprd_cpp 32768 0 - Live ... (O)
sprd_camera 442368 0 - Live ... (O)
sprd_flash_drv 16384 2 flash_ic_ocp8137,sprd_camera, Live ... (O)
sprd_sensor 118784 2 nxp685x_fm,sprd_camera, Live ... (O)
```
- /sys/module/<mod>/sections/* is readable (symtab, .text, .rodata.str1.1, etc.) → dump with scripts/dump_modules.sh.
- /proc/kallsyms exists but reads 0 bytes (restricted). /proc/modules shows addresses as 0x0 (kptr_restrict).

## Config comparison (running.config vs tree defconfigs)
- Closest defconfig: `arch/arm64/configs/sprd_sharkl3_defconfig` (148 diff lines).
- Notable running-config extras vs sprd_sharkle_defconfig: ARM_SPRD_HW_CPUFREQ_SHARKL3=y, ARM64_VHE=y, BLK_DEV_IO_TRACE=y, BPF_EVENTS=y, CHSC5XXX_TOUCHPANEL_DRIVER=y, etc.
- Running config header: "Linux/arm64 4.14.133 Kernel Configuration".

## Upstream DTS reference
- `arch/arm64/boot/dts/sprd/sp9863a-2h10.dts` — board DTS (SC9863A-2H10). Includes sc9863a.dtsi, sc9863a-wcn.dtsi, sp9863a-mach.dtsi, lcd/*.dtsi.
- Live DT adds vendor nodes: `lsec-apictrl`, `lsec-module` (with gpios-YF_P9/gpios-862/gpios-869/gpios-867/gpios-829/gpios-825 subnodes), `sprd-marlin3`, `saudio_lte`, `cpwcn_btwf`, `cpwcn_gnss`, `lsec_adaptive@78`, `btl_adaptive@2c`, `synaptics_tcm@0`, `sitronix@55`, `jadard_ts@68`, `ilitek@41`, `hy461x@38`, `ga657x@5d`, `atmel_mxt_ts_640u@4b`, `chipone_ts@30`, `gt9xx_ts@14`, `smtouch@2e`, `himax_ts@48`, `cst1xx@1a`, `focaltech@40`, `ltr308@53`, `lsm6dsm@6a`, `bh1750`, `nxp685x@64`, `sensor-main@44`, `sensor-sub@44`, `sensor-sub2@21`, `sensor-main2@6C`, `uis8581a` display/lcd nodes, `sound@0/1`, `sprd-headset`, `extcon-gpio`, `fingerprint@0`.

## Module signature/versioning (running.config)
- CONFIG_MODULES=y, CONFIG_MODULE_UNLOAD=y, CONFIG_MODVERSIONS=y, CONFIG_MODULES_TREE_LOOKUP=y
- CONFIG_MODULE_SIG: not set (modules unsigned). CONFIG_MODULE_FORCE_LOAD: not set. CONFIG_MODULE_COMPRESS: not set.
- => prebuilt socko .ko files will load if the rebuilt kernel exports symbols with matching CRCs (same config + source). Verify with insmod after build.

## OT/Running image relationship
- Running kernel #204 (Jul 30 2026) zImage (19.69MB) ≠ OTA 6316_1.zip boot.img kernel (18.1MB, 2024-04-30) — sha256 differ; OTA is older firmware.
- `/sdcard/.bak/stock_boot.img` (backed up Nov 7 2026, 36.7MB Android boot.img, page=2048, kerneladdr=0x8000) was extracted to `artifacts/zImage` (19.69MB) and is the correct reference for the RUNNING kernel. Ramdisk contains Magisk overlay (overlay.d/sbin/magisk32.xz, magisk64.xz, .backup/.magisk config) — boot ramdisk is root-patched; fstab.uis8581a2h10 shows dynamic partitions (system/vendor/product/elable + by-name metadata/oem).

## Firmware/OTA packages on device
- `/sdcard/Download/2026-05-07__FYT8581_FW_MD_EDITION.zip` → contains `6316_1.zip` (1.31GB, extracted to /tmp/6316_1.zip) with boot.img, dtbo.img, {system,vendor,product,elable,socko}.new.dat.br, modem bins (ltemodem.bin, ltegdsp.bin, ltedsp.bin, gnssmodem.bin, gnssbdmodem.bin, wcnmodem.bin, sml.bin, tos.bin, u-boot.bin, u-boot-spl-16k.bin, teecfg.bin, pmsys.bin, ltenvitem.bin, ltedeltanv.bin), lsec6316update tool.
- `/sdcard/Download/Fyt-Firmware-Kernel-5.0.1.zip` — scripts (00_import_original.sh ... 06_zip_and_sign.sh), config.ini, tools/ (common.py, sparse_img.py, blockimgdiff.py, rangelib.py, lsec6315update, lsec6316update), _mods/ (DocumentsUI-10.apk, hosts, sprd_performance_config.xml, privapp-permissions-ums512_1h10.xml).
- `/sdcard/.bak/stock_boot.img` — stock boot image (extracted). **This is the RUNNING kernel image** (#204, 19.6MB zImage, Magisk-patched ramdisk with overlay.d). OTA boot.img (from 6316_1.zip, 2024-04-30) has a DIFFERENT, older kernel (18.1MB zImage, build #<204) — confirmed sha256 differ. So use stock_boot.img zImage as the running-kernel reference, not the OTA one.
- `/sdcard/.bak/` also has AllAppUpdate.bin (802MB), lsec6315/6316/6521/6523 update tools, config.txt files.
- Vendor partition mounted ro at /mnt/vendor (dm-1): firmware/usbhub.bin, etc/sprd_hdr_tuning.param, etc/smart_amp_init.bin, bin/sprdstorageproxyd, bin/power/ddr/bm/tool/sharkl3_cm4_disable_smart_light.bin, UIS8581ES_power_*.xml, audio_para825, etc. No .ko files.
- Dynamic partitions: dm-0=product, dm-1=vendor, dm-2=/ (system root), dm-3=elable. /system mounted at /mnt/system (dm-0 labelled product? — verify).

## Out-of-tree modules FOUND — socko partition (KEY DISCOVERY)
- Partition `socko` = `/dev/block/mmcblk0p33` (ext4), mounted ro at `/mnt/socko`.
- Loaded via `${ro.vendor.ko.mount.point}/socko/<mod>.ko`; ro.vendor.ko.mount.point=/mnt/vendor (vendor build.prop). Real device path is /vendor/socko.
- **All 19 modules are prebuilt for exactly `4.14.133 SMP preempt mod_unload modversions aarch64`** — matches linux-sprd. Saved at `/root/uis8581a/artifacts/socko/` (56MB):
  ch7026.ko, flash_ic_ocp8137.ko, hxchipset.ko, jadardTS_ts.ko, lsec_audio.ko, ltr_308als.ko, microarray_fp.ko, nxp685x_fm.ko, pvrsrvkm.ko (24.5MB), qn8027.ko, sprd_camera.ko (10.5MB), sprd_cpp.ko, sprd_flash_drv.ko, sprd_fm.ko, sprd_sensor.ko, sprdbt_tty.ko, sprdwl_ng.ko (9.3MB), synaptics_dsx_td4310.ko, tcs3430.ko
- 12 currently loaded (see /proc/modules). Extra 7 are alternates/variants (different touch/ALS/audio/fm/fp parts for other board variants).
- **Implication**: no need to reimplement drivers from scratch. Use prebuilt .ko binaries; verify they load against rebuilt base kernel (vermagic matches; modversions CRCs should match with same config). Reverse-engineer only if a module must change (ABI change) — then pvrsrvkm/sprdwl_ng/jadardTS_ts/sprd_camera are the big ones.
- Init .rc files insmod them: /mnt/vendor/etc/init/init.sprd_flash.rc, init.vibdrv.rc, wcn.rc, factorytest.rc, camera.rc, init.tcs3430.rc, init.leddrv.rc, charge.rc; /mnt/vendor/etc/init/hw/init.syu.rc, init.cali.rc, init.common.rc, init.syu.rc (ch7026, nxp685x_fm, jadardTS_ts, pvrsrvkm, sprdbt_tty, sprd_fm); selinux label /vendor/etc/modules/sprdwl_ng.ko.
- `/sys/module/<m>/sections/<sec>` files contain section ADDRESSES only (zeroed by kptr_restrict) — not binaries. Use socko .ko files instead.

## Plan (phases)
1. Baseline: use running.config as .config in /linux-sprd; `make oldconfig`; build Image; diff vs zImage (strings/build-id/symbols).
2. Identify missing board support: create `sp9863a-2h10`-derived DTS for uis8581a2h10 (model/compatible/sc-id + vendor nodes from devtree.dts).
3. Use prebuilt out-of-tree modules from socko (vermagic matches). Verify load/CRC. Reverse-engineer/reimplement only if unusable.
4. Firmware: pull needed firmware blobs from /mnt/vendor/firmware + OTA vendor.new.dat.br (brotli) into source tree.
5. Build with matching toolchain (Android clang r353983c / clang 9.0.3 ideally; else gcc-aarch64-linux-gnu) targeting same features.
6. Verify functional equivalence: same module list, same DT nodes, same /proc configs, same behavior (wifi/bt/audio/touch/camera/display).

## Next actions
- [ ] Install cross toolchain (apt gcc-aarch64-linux-gnu / or fetch Android clang r353983c).
- [ ] Copy running.config → /linux-sprd/.config; make oldconfig; start baseline build.
- [ ] Update notes/artifacts with socko modules (done).
- [ ] Extract vendor.new.dat.br (brotli) from 6316_1.zip for firmware if needed.
- [ ] Parse dtbo.img (Android dtbo header) for overlay DTs.
- [ ] Compare stock (OTA) boot.img kernel vs running stock_boot.img kernel (diff strings/build-id) to know if running kernel was modified beyond Magisk.
- [ ] Check CONFIG_MODVERSIONS / CONFIG_MODULE_SIG settings in running.config (Module signature? load enforcement?).
- [ ] Determine exact boot device init: root=/dev/ram0 initrd is Magisk-patched; rebuilt boot.img must either keep this initrd or rebuild it (init fstab.uis8581a2h10 + overlay.d magisk32/64.xz).

## GitHub Source Hunt Results (Nov 14 2026)

10 repos cloned to `/root/uis8581a/github/`; file lists saved to `*_files.txt`. Symbol-verified matches via `scripts/symmatch.py`.

### Exact / near-exact public matches (symbol-verified)

| Module | Source | Match | Notes |
|---|---|---|---|
| `sprd_fm.ko` | `kanadenadi/android_kernel_sprd_sc9832e` → `sipc_modules/fm/driver/fm_sdio` | **97.7%** | only generated init/cleanup missing |
| `sprdbt_tty.ko` | same repo → `sipc_modules/bluetooth/driver/tty-sdio` | **93.9%** | same |
| `sprd_cpp.ko` | `Hadenix/android_kernel_zte_sc9863a` → `drivers/misc/sprd_camera/cpp/lite_r4p0` | **94.7%** | lite_r4p0 variant |
| `flash_ic_ocp8137.ko` | ZTE tree → `drivers/misc/sprd_camera/flash` | **85.7%** | flash IC driver |
| `sprd_flash_drv.ko` | ZTE tree → `drivers/misc/sprd_camera/flash` | **85.7%** | flash framework |
| `sprdwl_ng.ko` | `Yazz246/Aether_Kernel-A665L` → `drivers/unisoc_platform/wlan/marlin3_sipc` (+common) | **98.2%** | 9 misses: init/cleanup + 5 BSP-version funcs |
| `hxchipset.ko` | Aether `hxchipset_v3_3` (Himax HX83122B oncell) | **77%** | ~58 missing = IC-specific layer (hx83122_*) |

### Family matches (same codebase, different generation)

| Module | Source | Match | Notes |
|---|---|---|---|
| `sprd_sensor.ko` | ZTE `drivers/misc/sprd_camera/sensor` | 41.5% | common infrastructure matches, sensor-specific layer differs |
| `synaptics_dsx_td4310.ko` | ZTE `drivers/input/touchscreen/synaptics_dsx` | 51% | TD4310 variant not in ZTE tree (TD4320 SPI present) |

### NOT publicly available (ship prebuilt .ko)

| Module | Build path | Notes |
|---|---|---|
| `sprd_camera.ko` | `modules/camera/core/isp2.6/` | LSEC-specific isp2.6 build; official `sprd-linux/kernel4.14` + ZTE/Aether phone forks all lack it |
| `jadardTS_ts.ko` | `drivers/input/touchscreen/jdchipsetTS` | Jadard JD9261T/JD9366T/JD9366TP controller; not in any public repo |
| `tcs3430.ko` | `modules/input/misc/tcs3430/` | AMS TCS3430 color sensor; only Arduino/MicroPython libs exist |
| `ltr_308als.ko` | `modules/input/misc/ltr308als/` | Lite-On LTR-308ALS sensor; only userspace I2C libs |
| `microarray_fp.ko` | `modules/input/fingerprint/microarray` | Proprietary fingerprint; no public kernel driver |
| `ch7026.ko` | `modules/radio/ch7026/` | CH7026 HDMI encoder; only our device has it |
| `nxp685x_fm.ko` | `modules/radio/nxp685x/` | NXP TEF685X FM tuner; proprietary |
| `qn8027.ko` | `modules/radio/qn8027/` | QN8027 FM transmitter; only our device |
| `lsec_audio.ko` | `modules/radio/lsecaudio/` | LSEC audio DSP; completely proprietary |
| `pvrsrvkm.ko` (24.5MB) | `modules/gpu/rogue/` | PowerVR Rogue GPU — binary blob, 24.5MB, no public kernel source for this build |
| `pvrsrvkm.ko` | `modules/gpu/rogue/` | PowerVR Rogue kernel driver; IMG's official GitHub only has DDK 1.x/WebGL |

### Build path reference (from .ko strings)
All modules built from:  `/work/users/sharebsp/workdir/used8581/bsp/`
- Kernel: `kernel/kernel4.14/`
- Output: `out/uis8581a2h10/obj/kernel` + `obj/modules/<mod>/`
- BSP root: `/work/users/sharebsp/`
- Toolchain: `android.googlesource.c` → likely Android clang from AOSP

### Reusable artifacts
- `scripts/symmatch.py` — cross-compare .ko FUNC symbols against source trees
- `zte_files.txt`, `aether_files.txt`, `kernel4.14_files.txt`, `kanadenadi_files.txt` — full file indexes
- 10 cloned repos in `github/` (aether_a665l 151 files, zte_sc9863a 875MB full depth-1, etc.)

### Implications for rebuild
- **Can rebuild from source**: sprd_fm, sprdbt_tty, sprd_cpp, flash_ic_ocp8137, sprd_flash_drv, sprdwl_ng, hxchipset (if port HX83122B layer)
- **Ship prebuilt .ko**: sprd_camera, jadardTS_ts, tcs3430, ltr_308als, microarray_fp, ch7026, nxp685x_fm, qn8027, lsec_audio, pvrsrvkm, sprd_sensor (partial), synaptics_dsx_td4310 (partial)

---

## Project Vision (Nov 14 2026) — Full Platform Source Recovery PoC

### Goal
Create a **working, buildable source tree** for the UIS8581A (FYT8581) Android head unit platform. Use this as a **proof-of-concept** to create a reusable **skill for recovering Linux kernel sources** for any Android device (tablets, phones, watches, head units, etc.).

### Methodology
1. **Source discovery** → GitHub/opensource repos for Unisoc SoC family (SC9863A/sharkl3) and shared components
2. **Binary analysis** (REA tools) → decompile, trace, reverse-engineer modules with no public source  
3. **Binary similarity** → achieve 99% functional equivalence through analysis (emulation, symbol diffing, struct recovery)
4. **Parallel module workstreams** — independent .ko source ports running concurrently
5. **CI/CD pipeline** → speed up iterative builds (host CPU is a car radio SoC; offload where possible)
6. **Checkpoint often** → power to the head unit is volatile

### Module Priority Tiers
- **Tier 1 — Rebuild from public source**: sprdwl_ng, sprd_fm, sprdbt_tty, sprd_cpp, flash_ic_ocp8137, sprd_flash_drv, hxchipset
- **Tier 2 — Framework partial → port**: sprd_camera (isp2.6 → adapt from ZTE isp_r6pXXpX), sprd_sensor, synaptics_dsx_td4310
- **Tier 3 — Ship prebuilt .ko** (no public source, low customization value): tcs3430, ltr_308als, ch7026, qn8027, lsec_audio, nxp685x_fm
- **Tier 4 — REA reverse-engineer → reproduce**: pvrsrvkm (PowerVR Rogue), jadardTS_ts, microarray_fp
