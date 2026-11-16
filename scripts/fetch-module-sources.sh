#!/bin/bash
# fetch-module-sources.sh - Clone upstream sources for out-of-tree modules

set -e
BASE_DIR="$(dirname "$0")/../.."
MODULE_DIR="$BASE_DIR/module_sources"
mkdir -p "$MODULE_DIR"
echo "Fetching module sources..."

# sprdwl_ng - Aether marlin3_sipc WLAN
if [ ! -d "$MODULE_DIR/sprdwl_ng" ]; then
    git clone --depth 1 https://github.com/Yazz246/Aether_Kernel-A665L "$MODULE_DIR/sprdwl_ng" 2>/dev/null || true
    mkdir -p "$MODULE_DIR/drivers/unisoc_platform/wlan/marlin3_sipc"
    cp -r "$MODULE_DIR/sprdwl_ng/drivers/unisoc_platform/wlan/marlin3_sipc"/* "$MODULE_DIR/drivers/unisoc_platform/wlan/marlin3_sipc/" 2>/dev/null || true
fi

# sprd_fm & sprdbt_tty - kanadenadi WCN
if [ ! -d "$MODULE_DIR/kanadenadi" ]; then
    git clone --depth 1 https://github.com/kanadenadi/android_kernel_sprd_sc9832e "$MODULE_DIR/kanadenadi" 2>/dev/null || true
fi
mkdir -p "$MODULE_DIR/drivers/misc/sprdwcn/fm"
mkdir -p "$MODULE_DIR/drivers/misc/sprdwcn/bluetooth"
cp -r "$MODULE_DIR/kanadenadi/sipc_modules/fm/driver/fm_sdio"/* "$MODULE_DIR/drivers/misc/sprdwcn/fm/" 2>/dev/null || true
cp -r "$MODULE_DIR/kanadenadi/sipc_modules/bluetooth/driver/tty-sdio"/* "$MODULE_DIR/drivers/misc/sprdwcn/bluetooth/" 2>/dev/null || true

# sprd_cpp, flash_ic_ocp8137, sprd_flash_drv - ZTE SC9863A
if [ ! -d "$MODULE_DIR/zte" ]; then
    git clone --depth 1 https://github.com/Hadenix/android_kernel_zte_sc9863a "$MODULE_DIR/zte" 2>/dev/null || true
fi
mkdir -p "$MODULE_DIR/drivers/misc/sprd_camera/cpp/lite_r4p0"
mkdir -p "$MODULE_DIR/drivers/misc/sprd_camera/flash"
cp -r "$MODULE_DIR/zte/drivers/misc/sprd_camera/cpp/lite_r4p0"/* "$MODULE_DIR/drivers/misc/sprd_camera/cpp/lite_r4p0/" 2>/dev/null || true
cp -r "$MODULE_DIR/zte/drivers/misc/sprd_camera/flash"/* "$MODULE_DIR/drivers/misc/sprd_camera/flash/" 2>/dev/null || true

# hxchipset - Aether Himax HX83122B
if [ ! -d "$MODULE_DIR/aether_hx" ]; then
    git clone --depth 1 https://github.com/Yazz246/Aether_Kernel-A665L "$MODULE_DIR/aether_hx" 2>/dev/null || true
fi
mkdir -p "$MODULE_DIR/drivers/gpu/drm/hxchipset"
cp -r "$MODULE_DIR/aether_hx/drivers/gpu/drm/hxchipset_v3_3"/* "$MODULE_DIR/drivers/gpu/drm/hxchipset/" 2>/dev/null || true

# synaptics_dsx_td4310 - ZTE Synaptics
mkdir -p "$MODULE_DIR/drivers/input/touchscreen/synaptics_dsx"
cp -r "$MODULE_DIR/zte/drivers/input/touchscreen/synaptics_dsx"/* "$MODULE_DIR/drivers/input/touchscreen/synaptics_dsx/" 2>/dev/null || true

echo "Module sources fetched to $MODULE_DIR/drivers/"
echo "Run: git add module_sources && git commit -m 'Add module sources for CI'"
