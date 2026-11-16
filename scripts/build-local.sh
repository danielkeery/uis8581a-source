#!/bin/bash
# build-local.sh - Build kernel locally on the head unit or any arm64 machine

set -e
KERNEL_DIR="/linux-sprd"
SOURCE_DIR="/root/uis8581a/uis8581a-source"
ARTIFACTS_DIR="/root/uis8581a/artifacts"
JOBS=$(nproc)
cd "$KERNEL_DIR"

case "${1:-all}" in
    clean)
        echo "Cleaning..."
        make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- clean
        make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- mrproper
        ;;
    config)
        echo "Setting up config..."
        cp "$SOURCE_DIR/running.config" .config
        make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- olddefconfig
        for patch in "$SOURCE_DIR/patches"/*.patch; do
            [ -f "$patch" ] && git apply "$patch" 2>/dev/null || patch -p1 < "$patch"
        done
        cp .config "$SOURCE_DIR/running.config"
        ;;
    build)
        echo "Building kernel..."
        make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -j$JOBS Image dtbs
        cp arch/arm64/boot/Image "$ARTIFACTS_DIR/zImage.new"
        cp arch/arm64/boot/dts/sprd/*.dtb "$ARTIFACTS_DIR/"
        echo "Kernel built: $ARTIFACTS_DIR/zImage.new"
        ;;
    modules)
        echo "Building modules..."
        make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -j$JOBS modules
        find . -name "*.ko" -path "./drivers/*" -exec cp {} "$ARTIFACTS_DIR/modules/" \;
        echo "Modules copied to $ARTIFACTS_DIR/modules/"
        ;;
    all)
        $0 config
        $0 build
        $0 modules
        ;;
    *)
        echo "Usage: $0 [clean|config|build|modules|all]"
        exit 1
        ;;
esac
