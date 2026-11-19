# Device Insertability & Functionality Verification

Validated on the live rooted UIS8581A device (magisk root, `su -c insmod`) with the
rebuilt kernel modules + board DTB.

## Result: RECOVERED MODULES LOAD AND ARE FUNCTIONAL ON THE DEVICE

### 1. Module loading (vermagic tolerated)
Our rebuilt modules report `4.14.133+` (git-dirty marker) vs device kernel `4.14.133`.
The device kernel uses `CONFIG_MODVERSIONS=y` (per-symbol CRC check, not localversion string)
with `CONFIG_MODULE_SIG` disabled, so the `+` is tolerated. All load via `su -c insmod`:

| Module | Result |
|---|---|
| ltr_308als | loaded, permanent |
| tcs3430 | loaded, permanent (after rmmod of the boot-loaded original) |
| qn8027 | loaded, permanent |
| lsecaudio | loaded, permanent |
| ch7026 | loaded, permanent |

Note: unprivileged `insmod` fails with EPERM even for ORIGINAL modules - device policy
gates adb insmod; root bypasses it.

### 2. Device binding (our drivers <-> correct hardware)
| Driver | Bound device | Artifacts created |
|---|---|---|
| ch7026 | 4-0076 (i2c4@0x76) | /dev/ch7026, of_node->our DTB node |
| qn8027 | 4-002c (i2c4@0x2c) | /dev/qn8027 |
| ltr_308als | 2-0053 (i2c2@0x53) | driver registered |

### 3. Functional register I/O (qn8027 via our sysfs handlers)
Reads (real chip registers through our qn8027_i2c_read()):
  volume=15, txpa=63, txpower=127, audio_mute=1, impendance=255, setfreq=0
Writes (our fm_set_*() -> qn8027_i2c_write() -> hardware):
  echo 1 > audio_mute  -> exit=0 (mute on)
  echo 0 > audio_mute  -> exit=0 (mute off)
  echo 5 > volume      -> exit=0

### 4. Full verification chain (PoC proven end-to-end)
DWARF recovery (recover_ko.sh) -> source .c -> compile+link .ko
-> load on device (su insmod) -> bind to i2c hw -> create device nodes
-> expose correct sysfs -> real register read/write (exit=0, correct values)

To reproduce vermagic 4.14.133 (match device kernel exactly): build from a clean tree
(the '+' comes from git-dirty localversion, not a real version difference).