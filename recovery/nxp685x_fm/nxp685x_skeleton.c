// SPDX-License-Identifier: GPL-2.0
/*
 * Auto-generated skeleton recovered from DWARF debug info of: /root/uis8581a/artifacts/socko/nxp685x_fm.ko
 * Function signatures + struct types are recovered from .debug_info.
 * Fill in bodies using 'gdb -batch /root/uis8581a/artifacts/socko/nxp685x_fm.ko -ex "disassemble /m <fn>"'.
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/device.h>
#include <linux/sysfs.h>
#include <linux/miscdevice.h>
#include <linux/mutex.h>

/* ---- recovered struct types ---- */
struct Radio_stuct {
    unsigned char CurrentBand;
    unsigned int Freq;
    unsigned int BackupFreq;
    unsigned int MaxFreq;
    unsigned int MinFreq;
    unsigned char Step;
    unsigned char SeekStep;
    unsigned char Area;
    signed char Direction;
    signed char Smeter;
    unsigned char Multipath;
    signed char AdjChannel;
    unsigned char Detuning;
    unsigned char Deviation;
    unsigned char MpxNoise;
    unsigned char SNR;
    unsigned char AddressBuff[3];
    unsigned char DataBuff[100];
    unsigned char IFBW;
    unsigned char IS;
    unsigned int F_ForceSetBuff : 1;
    unsigned int F_GoodStation : 1;
    unsigned int F_SeekFullCycle : 1;
    unsigned int F_AutoSeek : 1;
    unsigned int F_TunerDispReq : 1;
    unsigned int F_ManualSeek : 1;
    unsigned int F_LocDx : 1;
    unsigned int F_Scan : 1;
    unsigned int F_AlignDone : 1;
    unsigned int F_TDBusy : 1;
    unsigned int F_QualDisplay : 1;
    unsigned int F_Stereo : 1;
    eTuner_Channel TunerChannel;
}
struct SQLBCB_UPDATE_INFO {
    unsigned char signature[4];
    unsigned char curr;
    unsigned char max;
}
struct SqlRadioFunc_ops {
    int (*FMpowerup)(void *);
    int (*FMpowerdown)(void *);
    int (*FMtuneradio)(void *);
    int (*FMsetmute)(void *);
    int (*FMsetforcemono)(void *);
    int (*FMgetmonostero)(void *);
    int (*FMgetforcemono)(void *);
    int (*FMgetrssilevel)(void *);
    int (*FMgetseekquality)(void *);
    int (*FMstopseek)(void *);
    int (*FMesdcheckfunc)(void *);
    int (*FMgetradiomodulename)(void *);
    int (*FMgetradioSurportlist)(void *);
    int (*FMioctlcheck)(void *);
    int (*FMprobeinit)(void *);
    int (*FMgetdefaultparama)(void *);
    int (*FMsuspend)(void *);
    int (*FMresume)(void *);
    int (*FMgetradiosubname)(void *);
    int (*FMgetrdsblockdata)(void *);
    int (*FMrdsonoff)(void *);
    int (*FMrdsgetfixlevel)(void *);
    int (*FMrdsgetaflevel)(void *);
    int (*FMsetradioband)(void *);
    int (*FMseekcontrol)(void *);
    int (*FMgetseekstatus)(void *);
    int (*DualTunerControl)(void *);
    int (*FMremove)(void *);
    int (*FMrelease)(void);
}
struct SqlRaidoScan_ops {
    int (*ScanRadioType)(struct i2c_client *, const struct i2c_device_id *);
    struct SqlRadioFunc_ops *pradio_funcs;
    unsigned char addr;
    const char *name;
}
struct _RDSDATA_DECODE_STRUCT_ {
    RDSBufferStruct RawDataBuffer;
    RDSRawBlocksStruct BlocksBuffer;
    RDS_DataStructure DecodedData;
}
struct _RDSDATA_MNG_STRUCT_ {
    RDSData_Process RDSData_Main;
    RDSData_TimersStruct Timers;
}
struct _RDSDATA_TIMERStructure {
    U8 REAL_RDSStationDelayTimer;
}
struct _RDSSTRATEGY_TIMERStructure {
    U16 REAL_PISeekTimer;
    U8 REAL_AFTimer;
    U8 REAL_AFCheckStartTimer;
    U8 REAL_AFCheckWaitTimer;
    U8 REAL_AFSearchWaitTimer;
    U8 REAL_AFSmeterCheckFreqTimer;
    U8 REAL_AFDisableTimer;
    U8 REAL_BGAFCheckFreqTimer;
    U16 AutoTASeekTimer;
    U8 InTADelayTimer;
    U8 TAWaitAFCheckTimer;
    U8 EnterTADelayTimer;
    U8 EnterEONTADelayTimer;
}
struct _RDS_AFStructure {
    U8 REAL_AF[25];
    U8 REAL_AFFreqBackup;
    U8 REAL_AFNum;
    U8 REAL_AFMethod[2];
}
struct _RDS_AF_STRATEGY_SETTING {
    U8 REAL_AFStrengthDelta;
    U8 REAL_AFStrengthFast;
    U8 REAL_AFStrengthSlow;
    U8 REAL_AFStrengthDeltaReal;
}
struct _RDS_BLOCK_STRUCT_ {
    U16 REAL_BlockLastA;
    U16 REAL_BlockLastB;
    U16 REAL_BlockLastC;
    U16 REAL_BlockLastCp;
    U16 REAL_BlockLastD;
    U8 REAL_Level;
    U8 REAL_MaxLevel;
}
struct _RDS_BUFFER_STRUCT_ {
    U8 BlockCnt;
    U8 BufferData[100];
}
struct _RDS_DataStructure {
    RDS_Block_Infor Blocks;
    RDS_PI_Data PIInfor;
    RDS_PTY_Data PTYInfor;
    U8 REAL_Group;
    RDS_PS_Data PSInfor;
    RDS_MJD_Time_Data MJD_TimeInfor;
    RDS_AF_Data AFInfor;
    RDS_FLAGS Flags;
}
struct _RDS_MANAGE_FLAGS {
    unsigned int REAL_TP : 1;
    unsigned int REAL_TPLast : 1;
    unsigned int REAL_TA : 1;
    unsigned int REAL_TALast : 1;
    unsigned int REAL_EONTP : 1;
    unsigned int REAL_EONTPLast : 1;
    unsigned int REAL_EONTA : 1;
    unsigned int REAL_EONTALast : 1;
    unsigned int REAL_F_GetOneGroup : 1;
    unsigned int REAL_F_BlockA : 1;
    unsigned int REAL_F_BlockB : 1;
    unsigned int REAL_F_BlockC : 1;
    unsigned int REAL_F_BlockCp : 1;
    unsigned int REAL_F_BlockD : 1;
    unsigned int REAL_F_RDSStation : 1;
    unsigned int REAL_F_AFMethodB : 1;
    unsigned int REAL_F_GetNewPI : 1;
    unsigned int REAL_F_GetNewPTY : 1;
    unsigned int REAL_F_GetNewTP : 1;
    unsigned int REAL_F_GetNewTA : 1;
    unsigned int REAL_F_GetNewEONTP : 1;
    unsigned int REAL_F_GetNewEONTA : 1;
    unsigned int REAL_F_PSGet0 : 1;
    unsigned int REAL_F_PSGet1 : 1;
    unsigned int REAL_F_PSGet2 : 1;
    unsigned int REAL_F_PSGet3 : 1;
    unsigned int REAL_F_PSExist : 1;
    unsigned int REAL_F_GetNewPS : 1;
    unsigned int REAL_F_GetNewCT : 1;
    unsigned int REAL_F_GetNewAF : 1;
    unsigned int REAL_F_GetAFList : 1;
    unsigned int REAL_F_GetNewRT : 1;
    unsigned int REAL_F_RTABFlag : 1;
    unsigned int REAL_F_RDSStationSlow : 1;
    unsigned int REAL_F_InEONTA : 1;
    unsigned int REAL_F_InEONTAReal : 1;
    unsigned int REAL_F_NoMatchEON : 1;
}
struct _RDS_MJD_TimeStructure {
    U8 REAL_TimeHour;
    U8 REAL_TimeMin;
    U32 REAL_MJD;
}
struct _RDS_PIStructure {
    U16 REAL_PI;
    U16 REAL_PILast;
    U16 REAL_PILast2;
    U16 REAL_PIBackup;
}
struct _RDS_PSStucture {
    U8 REAL_PS[8];
    U16 REAL_PSCRC;
    U16 REAL_PSCRCTemp;
}
struct _RDS_PTYStructure {
    U8 REAL_PTY;
    U8 REAL_PTYLast;
}
struct _RDS_RAQDTAT_STRUCT_ {
    U8 BlockCnt;
    U8 LastBlockCnt;
    U16 BlockA;
    U16 BlockB;
    U16 BlockC;
    U16 BlockCp;
    U16 BlockD;
    U16 BlockLastA;
    U16 BlockLastB;
    U16 BlockLastC;
    U16 BlockLastCp;
    U16 BlockLastD;
    U8 RDSData[4];
    unsigned int F_GetOneGroup : 1;
    unsigned int F_GetBlockA : 1;
    unsigned int F_GetBlockB : 1;
    unsigned int F_GetBlockC : 1;
    unsigned int F_GetBlockCp : 1;
    unsigned int F_GetBlockD : 1;
    unsigned int F_BlockA : 1;
    unsigned int F_BlockB : 1;
    unsigned int F_BlockC : 1;
    unsigned int F_BlockCp : 1;
    unsigned int F_BlockD : 1;
    unsigned int F_RDSStation : 1;
}
struct _RDS_SIGANAL_QUALITY_Structure {
    S8 REAL_ReadSmeter;
    U8 REAL_ReadDetuning;
    U8 REAL_ReadMPXNoise;
    U8 REAL_ReadMultipath;
    U8 REAL_ReadSNR;
    S8 REAL_ReadAdjchannel;
    U16 REAL_CFReadQuality;
    U8 REAL_CFReadDetuning;
    S8 REAL_CFReadAdjchannel;
    U8 REAL_CFReadMultipath;
    S8 REAL_CFReadSmeter;
    U8 REAL_F_QUALITY_OK;
}
struct _RDS_STRATEGY_STRUCTURE {
    RDS_STRATEGY_AF_Setting AF_Settings;
    RDSStrategyAFDataStruct AFData;
    RDS_Signal_Quality SignalQaulity;
    RDSStrategy_TimersStruct Timers;
    RDSStrategy_TimerSetStruct TimersSet;
}
struct _RDS_STRATEGY_TIMERS_SET {
    U8 AFCheckDisable1sTimer;
    U8 AFCheckBetweenList1sTimer;
    U8 AFCheckBetweenFreq10msTimer;
    U8 AFFastCheckBetweenFreq10msTimer;
    U8 AFFastCheckBetweenList1sTimer;
    U16 PISeek100msTimer;
}
struct _RDS_STRATETY_AFDATA_STRUCT_ {
    U8 REAL_AFCheckMode;
    U8 REAL_AFCheckPoint;
    U8 REAL_AFCheckStartTimerSet;
    U8 REAL_AFCheckWaitTimerSet;
    S8 REAL_AFSmeterLevel;
    S8 REAL_AFSmeter[25];
    U8 REAL_AFDisable[25];
    U8 REAL_F_BG_AF_Checking;
}
struct _Star_RDS_Conifg {
    U32 CSR;
    U32 NBR;
}
struct _TunerStruct {
    U8 WorkMode;
    U8 WaitTimer10ms;
    U8 TunerError;
    U8 TunerErrorCnt;
    U8 VPAmode;
    U32 mainFreq;
    U32 backgroundFreq;
    eTuner_Mode Band;
    Star_RDS_Conifg rdsConfig[2];
}
struct __BACKCAR_SETTING__ {
    int signature;
    int setflag;
    unsigned char Brightness;
    unsigned char Contrast;
    unsigned char Satuation;
    unsigned char Hue;
    unsigned char Sharpness;
    char rsv[3];
}
struct __BKLIGHT_CTRL__ {
    int bl_signature;
    uint16_t bl_run_mode;
    uint16_t bl_polarity;
    uint16_t bl_max_brightness;
    uint16_t bl_min_brightness;
    uint16_t bl_default_brightness;
    uint16_t bl_bitrsv;
    uint16_t bl_max_current;
    uint16_t bl_min_current;
    int bl_CurrentSig;
    uint16_t m_BackLightIC;
    uint16_t rsv;
}
struct __BOARD_CFG__ {
    int signature;
    uint8_t CustormerInfo[64];
    int m_platformtype;
    int m_IsUseMultiKey;
    uint32_t m_SysDebug;
    uint8_t m_back_VideoIC;
    uint8_t m_front_VideoIC;
    uint16_t m_McuIC;
    struct SQLBCB_UPDATE_INFO rbctl;
    BKLIGHT_CTRL blctrl;
    BSETTING BackCarSettings;
    int BackCarMirror;
    int BackCarType;
    int ColorLedSig;
    int ColorLedValue;
    int VerticalSetSig;
    uint8_t m_Rotation;
    uint8_t m_Landscape;
    uint8_t m_back_0_VideoIC;
    uint8_t m_reserve[1];
    uint16_t m_H_VideoStart;
    uint16_t m_V_VideoStart;
    uint16_t m_H_VideoSize;
    uint16_t m_V_VideoSize;
    int USBSpeedSetSig;
    int USBSpeed;
    int BoardLangSig;
    int BoardLang;
    int special_signature;
    int special_def;
    sqlpair rsvpair[14];
    sqlpair radioresetdelay;
    sqlpair fotaRotation;
    sqlpair DefaultUSBDevice;
    uint8_t reserve[96];
    uint32_t barebox_signature;
    uint32_t emmc_type;
    uint32_t cs0_mr8765;
    uint32_t cs1_mr8765;
    int gVerticalSig;
    int gDDRsignature;
    int m_SqlDebugoff;
    uint8_t m_sqlaplog;
    uint8_t rsv;
    uint8_t evensum;
    uint8_t oddsum;
}
struct __SQLPANEL_CFG__ {
    int signature;
    uint8_t PanelInfo[64];
    struct sql_panel_cfg pnl_cfg;
    uint32_t extdatasize;
    uint8_t extdata[268];
    sqlpair spec_ctrl;
    int LcdPowerUpBeforeCLK;
    int LcdPowerUpBeforeCLK_Delay;
    uint8_t rsv[2];
    uint8_t evensum;
    uint8_t oddsum;
}
struct __SQL_INFO__ {
    int signature;
    int infoversion;
    int infoversionH;
    int infoposition;
    char chipstring[32];
    char ubootversion[32];
    char kernelversion[32];
    SQLPANEL_CFG sqlpanel;
    BOARD_CFG sqlcfg;
    char bspdata[404];
    lsec_fminfo lsfm;
    char customercfg[16];
    char customercfg_info[48];
    int serialIDSIG;
    char serialID[8];
    tchpanel_newcfg ntouch_cfgs;
    char appdata[2048];
    char gammadata[4096];
    unsigned char t136data[16384];
    union {
        unsigned char updateclear[4096];
        sql_uclear sqlclear;
    } uclear;
    unsigned char panel_initdata[4096];
    union {
        unsigned char exts[12288];
        lsec_extra extraparamas;
    } extradata;
}
struct __SQL_PAIR__ {
    uint32_t signature;
    uint32_t data;
}
struct __SubNmaeUse__ {
    unsigned short deviceid;
    unsigned char *subname;
}
struct __Used_Default__ {
    unsigned int fmdefaultrssi;
    unsigned int fmrssimin;
    unsigned int fmrssimax;
    unsigned int amdefaultrssi;
    unsigned int amrssimin;
    unsigned int amrssimax;
    unsigned int reserve[10];
}
struct __extra_device__ {
    int signature;
    unsigned char disc[32];
    unsigned char someata[32];
    int offset;
    int size;
}
struct __lsec_extra__ {
    int signatureused;
    int usedcnt;
    extra_device extdev[5];
}
struct __lsec_fminfo__ {
    int signature;
    int index;
    int changeIndex;
    char rsv[4];
    char name[16];
}
struct __lsec_radio_fw__ {
    int signature;
    unsigned int size;
    int checksum;
    unsigned char info[64];
    union {
        radio_nxp_fw nxpfw;
        radio_tda_fw tdafw;
    } usefw;
}
struct __radio_nxp_fw__ {
    int initdatasignature;
    int usefullfw;
    unsigned int tuner_init_para_offset;
    unsigned int tuner_init_para_size;
    unsigned int PatchByteValues_offset;
    unsigned int PatchByteValues_size;
    unsigned int LutByteValues_offset;
    unsigned int LutByteValues_size;
    unsigned int SubNmaeUse_offset;
    unsigned int SubNmaeUse_size;
    unsigned char fm_usn;
    unsigned char fm_wam;
    unsigned short fm_bandwidth;
    unsigned short fm_offset;
    unsigned short am_offset;
    int surportlist;
    unsigned int rsvdata[16];
}
struct __radio_tda_fw__ {
    int initdatasignature;
    int usefullfw;
    unsigned int I2CBootData_offset;
    unsigned int I2CBootData_size;
    unsigned char fm_ACp_th;
    unsigned int fm_AdjChannel_th;
    unsigned int fm_Multipath_th;
    unsigned int fm_Detuning_th;
    unsigned int am_Detuning_th;
    int surportlist;
    unsigned int rsvdata[16];
}
struct __sql_uclear__ {
    int signaturewrited;
    sqlpair flagneeduseUsb;
    sqlpair flaglsecdebug;
}
struct __sqlfm_rds__ {
    atomic_t rds_mode;
    wait_queue_head_t read_queue;
    u32 wr_idx;
    u32 rd_idx;
    atomic_t is_full;
    void *rds_rpt_buf;
    u32 array_len;
    atomic_t rpt_cnt;
}
struct _func_info_t {
    uint8_t FWMajor;
    uint8_t FWMinor1;
    uint8_t FWMinor2;
    uint8_t patchIdH;
    uint8_t patchIdL;
}
struct _npkarea_key_ {
    char area1_on;
    char area1_num;
    char area2_on;
    char area2_num;
    uint16_t left_border;
    uint16_t right_border;
    uint16_t top_border;
    uint16_t bottom_border;
    n_area_key area1_key[5];
    n_area_key area2_key[5];
}
struct _part_info_t {
    uint8_t chipRW;
    uint8_t PartNum;
    char FWMajorRW;
    char FWMinorRW;
    uint8_t FWBuildRW;
    uint8_t ROMId;
}
struct _rds_data_t {
    uint16_t pi;
    uint8_t ta;
    uint8_t pty;
    uint8_t ps[8];
    uint8_t ps_valid;
    uint8_t rt[64];
    uint8_t rt_valid;
    uint8_t af_index;
    uint8_t af_check_times;
    uint8_t af_count;
    uint16_t af_list[25];
}
struct _rds_ps_helper_t {
    uint8_t ps_high[8];
    uint8_t ps_low[8];
    uint8_t ps_cnt[8];
}
struct _rds_rt_helper_t {
    uint8_t ab_flag;
    uint8_t ab_flag_valid;
    uint8_t rt_high[64];
    uint8_t rt_low[64];
    uint8_t rt_cnt[64];
}
struct _rds_status_t {
    uint8_t ints;
    uint8_t flags;
    uint8_t tp;
    uint8_t pty;
    uint16_t pi;
    uint8_t fifoused;
    BLER blera;
    BLER blerb;
    BLER blerc;
    BLER blerd;
    uint16_t blocka;
    uint16_t blockb;
    uint16_t blockc;
    uint16_t blockd;
}
struct _rds_time_t {
    uint8_t day_high;
    uint16_t day_low;
    uint8_t hour;
    uint8_t minute;
    int8_t offset;
}
struct _si475x_info_t {
    int index;
    part_info_t partinfo;
    const char *partname;
    int surportlist;
}
struct _stTunerProcessFeature {
    U8 dum1;
    U8 dum2;
    U8 dum3;
    unsigned int VPA : 1;
    unsigned int HDBBFilter : 1;
}
struct _tchpanel_newcfg_ {
    int signature;
    int size;
    int filetype;
    int x2y;
    int have_areakey;
    int drivertype;
    struct ext_special_key sqlextspecial;
    struct special_key sqlspecial;
    npkarea_key sqlareakeys;
    char PanleType[36];
    int rsv[16];
    char parama[254];
    char evensum;
    char oddsum;
}
struct _tuner_metrics_t {
    uint8_t Valid;
    int8_t RSSI;
    int8_t SNR;
    int8_t FreqOff;
    uint16_t Freq;
    unsigned char mult;
    unsigned char usn;
}
struct acpi_device_id {
    __u8 id[9];
    kernel_ulong_t driver_data;
    __u32 cls;
    __u32 cls_msk;
}
struct address_space {
    struct inode *host;
    struct radix_tree_root page_tree;
    spinlock_t tree_lock;
    atomic_t i_mmap_writable;
    struct rb_root_cached i_mmap;
    struct rw_semaphore i_mmap_rwsem;
    unsigned long nrpages;
    unsigned long nrexceptional;
    unsigned long writeback_index;
    const struct address_space_operations *a_ops;
    unsigned long flags;
    spinlock_t private_lock;
    gfp_t gfp_mask;
    struct list_head private_list;
    void *private_data;
    errseq_t wb_err;
}
struct address_space_operations {
    int (*writepage)(struct page *, struct writeback_control *);
    int (*readpage)(struct file *, struct page *);
    int (*writepages)(struct address_space *, struct writeback_control *);
    int (*set_page_dirty)(struct page *);
    int (*readpages)(struct file *, struct address_space *, struct list_head *, unsigned int);
    int (*write_begin)(struct file *, struct address_space *, loff_t, unsigned int, unsigned int, struct page **, void **);
    int (*write_end)(struct file *, struct address_space *, loff_t, unsigned int, unsigned int, struct page *, void *);
    sector_t (*bmap)(struct address_space *, sector_t);
    void (*invalidatepage)(struct page *, unsigned int, unsigned int);
    int (*releasepage)(struct page *, gfp_t);
    void (*freepage)(struct page *);
    ssize_t (*direct_IO)(struct kiocb *, struct iov_iter *);
    int (*migratepage)(struct address_space *, struct page *, struct page *, enum migrate_mode);
    bool (*isolate_page)(struct page *, isolate_mode_t);
    void (*putback_page)(struct page *);
    int (*launder_page)(struct page *);
    int (*is_partially_uptodate)(struct page *, unsigned long, unsigned long);
    void (*is_dirty_writeback)(struct page *, bool *, bool *);
    int (*error_remove_page)(struct address_space *, struct page *);
    int (*swap_activate)(struct swap_info_struct *, struct file *, sector_t *);
    void (*swap_deactivate)(struct file *);
}
struct assoc_array {
    struct assoc_array_ptr *root;
    unsigned long nr_leaves_on_tree;
}
struct attribute {
    const char *name;
    umode_t mode;
}
struct attribute_group {
    const char *name;
    umode_t (*is_visible)(struct kobject *, struct attribute *, int);
    umode_t (*is_bin_visible)(struct kobject *, struct bin_attribute *, int);
    struct attribute **attrs;
    struct bin_attribute **bin_attrs;
}
struct bin_attribute {
    struct attribute attr;
    size_t size;
    void *private;
    ssize_t (*read)(struct file *, struct kobject *, struct bin_attribute *, char *, loff_t, size_t);
    ssize_t (*write)(struct file *, struct kobject *, struct bin_attribute *, char *, loff_t, size_t);
    int (*mmap)(struct file *, struct kobject *, struct bin_attribute *, struct vm_area_struct *);
}
struct block_device {
    dev_t bd_dev;
    int bd_openers;
    struct inode *bd_inode;
    struct super_block *bd_super;
    struct mutex bd_mutex;
    void *bd_claiming;
    void *bd_holder;
    int bd_holders;
    bool bd_write_holder;
    struct list_head bd_holder_disks;
    struct block_device *bd_contains;
    unsigned int bd_block_size;
    u8 bd_partno;
    struct hd_struct *bd_part;
    unsigned int bd_part_count;
    int bd_invalidated;
    struct gendisk *bd_disk;
    struct request_queue *bd_queue;
    struct backing_dev_info *bd_bdi;
    struct list_head bd_list;
    unsigned long bd_private;
    int bd_fsfreeze_count;
    struct mutex bd_fsfreeze_mutex;
}
struct bug_entry {
    int bug_addr_disp;
    unsigned short flags;
}
struct bus_type {
    const char *name;
    const char *dev_name;
    struct device *dev_root;
    const struct attribute_group **bus_groups;
    const struct attribute_group **dev_groups;
    const struct attribute_group **drv_groups;
    int (*match)(struct device *, struct device_driver *);
    int (*uevent)(struct device *, struct kobj_uevent_env *);
    int (*probe)(struct device *);
    int (*remove)(struct device *);
    void (*shutdown)(struct device *);
    int (*online)(struct device *);
    int (*offline)(struct device *);
    int (*suspend)(struct device *, pm_message_t);
    int (*resume)(struct device *);
    int (*num_vf)(struct device *);
    const struct dev_pm_ops *pm;
    const struct iommu_ops *iommu_ops;
    struct subsys_private *p;
    struct lock_class_key lock_key;
}
struct callback_head {
    struct callback_head *next;
    void (*func)(struct callback_head *);
}
struct class {
    const char *name;
    struct module *owner;
    const struct attribute_group **class_groups;
    const struct attribute_group **dev_groups;
    struct kobject *dev_kobj;
    int (*dev_uevent)(struct device *, struct kobj_uevent_env *);
    char *(*devnode)(struct device *, umode_t *);
    void (*class_release)(struct class *);
    void (*dev_release)(struct device *);
    int (*suspend)(struct device *, pm_message_t);
    int (*resume)(struct device *);
    int (*shutdown_pre)(struct device *);
    const struct kobj_ns_type_operations *ns_type;
    const void *(*namespace)(struct device *);
    const struct dev_pm_ops *pm;
    struct subsys_private *p;
}
struct compat_robust_list {
    compat_uptr_t next;
}
struct compat_robust_list_head {
    struct compat_robust_list list;
    compat_long_t futex_offset;
    compat_uptr_t list_op_pending;
}
struct compat_timespec {
    compat_time_t tv_sec;
    s32 tv_nsec;
}
struct completion {
    unsigned int done;
    wait_queue_head_t wait;
}
struct core_state {
    atomic_t nr_threads;
    struct core_thread dumper;
    struct completion startup;
}
struct core_thread {
    struct task_struct *task;
    struct core_thread *next;
}
struct cpu_context {
    unsigned long x19;
    unsigned long x20;
    unsigned long x21;
    unsigned long x22;
    unsigned long x23;
    unsigned long x24;
    unsigned long x25;
    unsigned long x26;
    unsigned long x27;
    unsigned long x28;
    unsigned long fp;
    unsigned long sp;
    unsigned long pc;
}
struct cpu_itimer {
    u64 expires;
    u64 incr;
}
struct cpumask {
    unsigned long bits[1];
}
struct cred {
    atomic_t usage;
    kuid_t uid;
    kgid_t gid;
    kuid_t suid;
    kgid_t sgid;
    kuid_t euid;
    kgid_t egid;
    kuid_t fsuid;
    kgid_t fsgid;
    unsigned int securebits;
    kernel_cap_t cap_inheritable;
    kernel_cap_t cap_permitted;
    kernel_cap_t cap_effective;
    kernel_cap_t cap_bset;
    kernel_cap_t cap_ambient;
    unsigned char jit_keyring;
    struct key *session_keyring;
    struct key *process_keyring;
    struct key *thread_keyring;
    struct key *request_key_auth;
    void *security;
    struct user_struct *user;
    struct user_namespace *user_ns;
    struct group_info *group_info;
    struct callback_head rcu;
}
struct debug_info {
    int suspended_step;
    int bps_disabled;
    int wps_disabled;
    struct perf_event *hbp_break[16];
    struct perf_event *hbp_watch[16];
}
struct delayed_call {
    void (*fn)(void *);
    void *arg;
}
struct delayed_work {
    struct work_struct work;
    struct timer_list timer;
    struct workqueue_struct *wq;
    int cpu;
}
struct dentry {
    unsigned int d_flags;
    seqcount_t d_seq;
    struct hlist_bl_node d_hash;
    struct dentry *d_parent;
    struct qstr d_name;
    struct inode *d_inode;
    unsigned char d_iname[32];
    struct lockref d_lockref;
    const struct dentry_operations *d_op;
    struct super_block *d_sb;
    unsigned long d_time;
    void *d_fsdata;
    union {
        struct list_head d_lru;
        wait_queue_head_t *d_wait;
    };
    struct list_head d_child;
    struct list_head d_subdirs;
    union {
        struct hlist_node d_alias;
        struct hlist_bl_node d_in_lookup_hash;
        struct callback_head d_rcu;
    } d_u;
}
struct dentry_operations {
    int (*d_revalidate)(struct dentry *, unsigned int);
    int (*d_weak_revalidate)(struct dentry *, unsigned int);
    int (*d_hash)(const struct dentry *, struct qstr *);
    int (*d_compare)(const struct dentry *, unsigned int, const char *, const struct qstr *);
    int (*d_delete)(const struct dentry *);
    int (*d_init)(struct dentry *);
    void (*d_release)(struct dentry *);
    void (*d_prune)(struct dentry *);
    void (*d_iput)(struct dentry *, struct inode *);
    char *(*d_dname)(struct dentry *, char *, int);
    struct vfsmount *(*d_automount)(struct path *);
    int (*d_manage)(const struct path *, bool);
    struct dentry *(*d_real)(struct dentry *, const struct inode *, unsigned int, unsigned int);
    void (*d_canonical_path)(const struct path *, struct path *);
}
struct dev_archdata {
    bool dma_coherent;
}
struct dev_links_info {
    struct list_head suppliers;
    struct list_head consumers;
    enum dl_dev_state status;
}
struct dev_pagemap {
    dev_page_fault_t page_fault;
    dev_page_free_t page_free;
    struct vmem_altmap *altmap;
    const struct resource *res;
    struct percpu_ref *ref;
    struct device *dev;
    void *data;
    enum memory_type type;
}
struct dev_pin_info {
    struct pinctrl *p;
    struct pinctrl_state *default_state;
    struct pinctrl_state *init_state;
    struct pinctrl_state *sleep_state;
    struct pinctrl_state *idle_state;
}
struct dev_pm_domain {
    struct dev_pm_ops ops;
    void (*detach)(struct device *, bool);
    int (*activate)(struct device *);
    void (*sync)(struct device *);
    void (*dismiss)(struct device *);
}
struct dev_pm_info {
    pm_message_t power_state;
    unsigned int can_wakeup : 1;
    unsigned int async_suspend : 1;
    bool in_dpm_list : 1;
    bool is_prepared : 1;
    bool is_suspended : 1;
    bool is_noirq_suspended : 1;
    bool is_late_suspended : 1;
    bool early_init : 1;
    bool direct_complete : 1;
    spinlock_t lock;
    struct list_head entry;
    struct completion completion;
    struct wakeup_source *wakeup;
    bool wakeup_path : 1;
    bool syscore : 1;
    bool no_pm_callbacks : 1;
    struct timer_list suspend_timer;
    unsigned long timer_expires;
    struct work_struct work;
    wait_queue_head_t wait_queue;
    struct wake_irq *wakeirq;
    atomic_t usage_count;
    atomic_t child_count;
    unsigned int disable_depth : 3;
    unsigned int idle_notification : 1;
    unsigned int request_pending : 1;
    unsigned int deferred_resume : 1;
    unsigned int runtime_auto : 1;
    bool ignore_children : 1;
    unsigned int no_callbacks : 1;
    unsigned int irq_safe : 1;
    unsigned int use_autosuspend : 1;
    unsigned int timer_autosuspends : 1;
    unsigned int memalloc_noio : 1;
    unsigned int links_count;
    enum rpm_request request;
    enum rpm_status runtime_status;
    int runtime_error;
    int autosuspend_delay;
    unsigned long last_busy;
    unsigned long active_jiffies;
    unsigned long suspended_jiffies;
    unsigned long accounting_timestamp;
    struct pm_subsys_data *subsys_data;
    void (*set_latency_tolerance)(struct device *, s32);
    struct dev_pm_qos *qos;
}
struct dev_pm_ops {
    int (*prepare)(struct device *);
    void (*complete)(struct device *);
    int (*suspend)(struct device *);
    int (*resume)(struct device *);
    int (*freeze)(struct device *);
    int (*thaw)(struct device *);
    int (*poweroff)(struct device *);
    int (*restore)(struct device *);
    int (*suspend_late)(struct device *);
    int (*resume_early)(struct device *);
    int (*freeze_late)(struct device *);
    int (*thaw_early)(struct device *);
    int (*poweroff_late)(struct device *);
    int (*restore_early)(struct device *);
    int (*suspend_noirq)(struct device *);
    int (*resume_noirq)(struct device *);
    int (*freeze_noirq)(struct device *);
    int (*thaw_noirq)(struct device *);
    int (*poweroff_noirq)(struct device *);
    int (*restore_noirq)(struct device *);
    int (*runtime_suspend)(struct device *);
    int (*runtime_resume)(struct device *);
    int (*runtime_idle)(struct device *);
}
struct device {
    struct device *parent;
    struct device_private *p;
    struct kobject kobj;
    const char *init_name;
    const struct device_type *type;
    struct mutex mutex;
    struct bus_type *bus;
    struct device_driver *driver;
    void *platform_data;
    void *driver_data;
    struct dev_links_info links;
    struct dev_pm_info power;
    struct dev_pm_domain *pm_domain;
    struct dev_pin_info *pins;
    const struct dma_map_ops *dma_ops;
    u64 *dma_mask;
    u64 coherent_dma_mask;
    unsigned long dma_pfn_offset;
    struct device_dma_parameters *dma_parms;
    struct list_head dma_pools;
    struct dma_coherent_mem *dma_mem;
    struct dev_archdata archdata;
    struct device_node *of_node;
    struct fwnode_handle *fwnode;
    dev_t devt;
    u32 id;
    spinlock_t devres_lock;
    struct list_head devres_head;
    struct klist_node knode_class;
    struct class *class;
    const struct attribute_group **groups;
    void (*release)(struct device *);
    struct iommu_group *iommu_group;
    struct iommu_fwspec *iommu_fwspec;
    bool offline_disabled : 1;
    bool offline : 1;
    bool of_node_reused : 1;
}
struct device_dma_parameters {
    unsigned int max_segment_size;
    unsigned long segment_boundary_mask;
}
struct device_driver {
    const char *name;
    struct bus_type *bus;
    struct module *owner;
    const char *mod_name;
    bool suppress_bind_attrs;
    enum probe_type probe_type;
    const struct of_device_id *of_match_table;
    const struct acpi_device_id *acpi_match_table;
    int (*probe)(struct device *);
    int (*remove)(struct device *);
    void (*shutdown)(struct device *);
    int (*suspend)(struct device *, pm_message_t);
    int (*resume)(struct device *);
    const struct attribute_group **groups;
    const struct dev_pm_ops *pm;
    struct driver_private *p;
}
struct device_node {
    const char *name;
    const char *type;
    phandle phandle;
    const char *full_name;
    struct fwnode_handle fwnode;
    struct property *properties;
    struct property *deadprops;
    struct device_node *parent;
    struct device_node *child;
    struct device_node *sibling;
    struct kobject kobj;
    unsigned long _flags;
    void *data;
}
struct device_type {
    const char *name;
    const struct attribute_group **groups;
    int (*uevent)(struct device *, struct kobj_uevent_env *);
    char *(*devnode)(struct device *, umode_t *, kuid_t *, kgid_t *);
    void (*release)(struct device *);
    const struct dev_pm_ops *pm;
}
struct dir_context {
    const filldir_t actor;
    loff_t pos;
}
struct dquot {
    struct hlist_node dq_hash;
    struct list_head dq_inuse;
    struct list_head dq_free;
    struct list_head dq_dirty;
    struct mutex dq_lock;
    spinlock_t dq_dqb_lock;
    atomic_t dq_count;
    struct super_block *dq_sb;
    struct kqid dq_id;
    loff_t dq_off;
    unsigned long dq_flags;
    struct mem_dqblk dq_dqb;
}
struct dquot_operations {
    int (*write_dquot)(struct dquot *);
    struct dquot *(*alloc_dquot)(struct super_block *, int);
    void (*destroy_dquot)(struct dquot *);
    int (*acquire_dquot)(struct dquot *);
    int (*release_dquot)(struct dquot *);
    int (*mark_dirty)(struct dquot *);
    int (*write_info)(struct super_block *, int);
    qsize_t *(*get_reserved_space)(struct inode *);
    int (*get_projid)(struct inode *, kprojid_t *);
    int (*get_inode_usage)(struct inode *, qsize_t *);
    int (*get_next_id)(struct super_block *, struct kqid *);
}
struct elf64_shdr {
    Elf64_Word sh_name;
    Elf64_Word sh_type;
    Elf64_Xword sh_flags;
    Elf64_Addr sh_addr;
    Elf64_Off sh_offset;
    Elf64_Xword sh_size;
    Elf64_Word sh_link;
    Elf64_Word sh_info;
    Elf64_Xword sh_addralign;
    Elf64_Xword sh_entsize;
}
struct elf64_sym {
    Elf64_Word st_name;
    unsigned char st_info;
    unsigned char st_other;
    Elf64_Half st_shndx;
    Elf64_Addr st_value;
    Elf64_Xword st_size;
}
struct exception_table_entry {
    int insn;
    int fixup;
}
struct ext_special_key {
    uint16_t special_keyvalue[4];
}
struct fasync_struct {
    spinlock_t fa_lock;
    int magic;
    int fa_fd;
    struct fasync_struct *fa_next;
    struct file *fa_file;
    struct callback_head fa_rcu;
}
struct fiemap_extent {
    __u64 fe_logical;
    __u64 fe_physical;
    __u64 fe_length;
    __u64 fe_reserved64[2];
    __u32 fe_flags;
    __u32 fe_reserved[3];
}
struct fiemap_extent_info {
    unsigned int fi_flags;
    unsigned int fi_extents_mapped;
    unsigned int fi_extents_max;
    struct fiemap_extent *fi_extents_start;
}
struct file {
    union {
        struct llist_node fu_llist;
        struct callback_head fu_rcuhead;
    } f_u;
    struct path f_path;
    struct inode *f_inode;
    const struct file_operations *f_op;
    spinlock_t f_lock;
    enum rw_hint f_write_hint;
    atomic_long_t f_count;
    unsigned int f_flags;
    fmode_t f_mode;
    struct mutex f_pos_lock;
    loff_t f_pos;
    struct fown_struct f_owner;
    const struct cred *f_cred;
    struct file_ra_state f_ra;
    u64 f_version;
    void *f_security;
    void *private_data;
    struct list_head f_ep_links;
    struct list_head f_tfile_llink;
    struct address_space *f_mapping;
    errseq_t f_wb_err;
}
struct file_lock {
    struct file_lock *fl_next;
    struct list_head fl_list;
    struct hlist_node fl_link;
    struct list_head fl_block;
    fl_owner_t fl_owner;
    unsigned int fl_flags;
    unsigned char fl_type;
    unsigned int fl_pid;
    int fl_link_cpu;
    wait_queue_head_t fl_wait;
    struct file *fl_file;
    loff_t fl_start;
    loff_t fl_end;
    struct fasync_struct *fl_fasync;
    unsigned long fl_break_time;
    unsigned long fl_downgrade_time;
    const struct file_lock_operations *fl_ops;
    const struct lock_manager_operations *fl_lmops;
    union {
        struct nfs_lock_info nfs_fl;
        struct nfs4_lock_info nfs4_fl;
        struct {...} afs;
    } fl_u;
}
struct file_lock_context {
    spinlock_t flc_lock;
    struct list_head flc_flock;
    struct list_head flc_posix;
    struct list_head flc_lease;
}
struct file_lock_operations {
    void (*fl_copy_lock)(struct file_lock *, struct file_lock *);
    void (*fl_release_private)(struct file_lock *);
}
struct file_operations {
    struct module *owner;
    loff_t (*llseek)(struct file *, loff_t, int);
    ssize_t (*read)(struct file *, char *, size_t, loff_t *);
    ssize_t (*write)(struct file *, const char *, size_t, loff_t *);
    ssize_t (*read_iter)(struct kiocb *, struct iov_iter *);
    ssize_t (*write_iter)(struct kiocb *, struct iov_iter *);
    int (*iterate)(struct file *, struct dir_context *);
    int (*iterate_shared)(struct file *, struct dir_context *);
    unsigned int (*poll)(struct file *, struct poll_table_struct *);
    long (*unlocked_ioctl)(struct file *, unsigned int, unsigned long);
    long (*compat_ioctl)(struct file *, unsigned int, unsigned long);
    int (*mmap)(struct file *, struct vm_area_struct *);
    int (*open)(struct inode *, struct file *);
    int (*flush)(struct file *, fl_owner_t);
    int (*release)(struct inode *, struct file *);
    int (*fsync)(struct file *, loff_t, loff_t, int);
    int (*fasync)(int, struct file *, int);
    int (*lock)(struct file *, int, struct file_lock *);
    ssize_t (*sendpage)(struct file *, struct page *, int, size_t, loff_t *, int);
    unsigned long (*get_unmapped_area)(struct file *, unsigned long, unsigned long, unsigned long, unsigned long);
    int (*check_flags)(int);
    int (*flock)(struct file *, int, struct file_lock *);
    ssize_t (*splice_write)(struct pipe_inode_info *, struct file *, loff_t *, size_t, unsigned int);
    ssize_t (*splice_read)(struct file *, loff_t *, struct pipe_inode_info *, size_t, unsigned int);
    int (*setlease)(struct file *, long, struct file_lock **, void **);
    long (*fallocate)(struct file *, int, loff_t, loff_t);
    void (*show_fdinfo)(struct seq_file *, struct file *);
    ssize_t (*copy_file_range)(struct file *, loff_t, struct file *, loff_t, size_t, unsigned int);
    int (*clone_file_range)(struct file *, loff_t, struct file *, loff_t, u64);
    ssize_t (*dedupe_file_range)(struct file *, u64, u64, struct file *, u64);
}
struct file_ra_state {
    unsigned long start;
    unsigned int size;
    unsigned int async_size;
    unsigned int ra_pages;
    unsigned int mmap_miss;
    loff_t prev_pos;
}
struct file_system_type {
    const char *name;
    int fs_flags;
    struct dentry *(*mount)(struct file_system_type *, int, const char *, void *);
    struct dentry *(*mount2)(struct vfsmount *, struct file_system_type *, int, const char *, void *);
    void *(*alloc_mnt_data)(void);
    void (*kill_sb)(struct super_block *);
    struct module *owner;
    struct file_system_type *next;
    struct hlist_head fs_supers;
    struct lock_class_key s_lock_key;
    struct lock_class_key s_umount_key;
    struct lock_class_key s_vfs_rename_key;
    struct lock_class_key s_writers_key[3];
    struct lock_class_key i_lock_key;
    struct lock_class_key i_mutex_key;
    struct lock_class_key i_mutex_dir_key;
}
struct firmware {
    size_t size;
    const u8 *data;
    struct page **pages;
    void *priv;
}
struct fm_dual_tuner {
    uint32_t cmd;
    uint32_t size;
    uint32_t channel;
    uint32_t rsv;
    uint32_t args[28];
}
struct fm_seek_parm {
    uint8_t err;
    uint8_t band;
    uint8_t space;
    uint8_t hilo;
    uint8_t seekdir;
    uint8_t seekth;
    uint16_t freq;
    uint16_t rssi;
}
struct fm_tune_parm {
    uint8_t err;
    uint8_t band;
    uint8_t space;
    uint8_t hilo;
    uint16_t freq;
}
struct fown_struct {
    rwlock_t lock;
    struct pid *pid;
    enum pid_type pid_type;
    kuid_t uid;
    kuid_t euid;
    int signum;
}
struct fpsimd_state {
    union {
        struct user_fpsimd_state user_fpsimd;
        struct {...};
    };
    unsigned int cpu;
}
struct fwnode_endpoint {
    unsigned int port;
    unsigned int id;
    const struct fwnode_handle *local_fwnode;
}
struct fwnode_handle {
    struct fwnode_handle *secondary;
    const struct fwnode_operations *ops;
}
struct fwnode_operations {
    void (*get)(struct fwnode_handle *);
    void (*put)(struct fwnode_handle *);
    bool (*device_is_available)(const struct fwnode_handle *);
    bool (*property_present)(const struct fwnode_handle *, const char *);
    int (*property_read_int_array)(const struct fwnode_handle *, const char *, unsigned int, void *, size_t);
    int (*property_read_string_array)(const struct fwnode_handle *, const char *, const char **, size_t);
    struct fwnode_handle *(*get_parent)(const struct fwnode_handle *);
    struct fwnode_handle *(*get_next_child_node)(const struct fwnode_handle *, struct fwnode_handle *);
    struct fwnode_handle *(*get_named_child_node)(const struct fwnode_handle *, const char *);
    int (*get_reference_args)(const struct fwnode_handle *, const char *, const char *, unsigned int, unsigned int, struct fwnode_reference_args *);
    struct fwnode_handle *(*graph_get_next_endpoint)(const struct fwnode_handle *, struct fwnode_handle *);
    struct fwnode_handle *(*graph_get_remote_endpoint)(const struct fwnode_handle *);
    struct fwnode_handle *(*graph_get_port_parent)(struct fwnode_handle *);
    int (*graph_parse_endpoint)(const struct fwnode_handle *, struct fwnode_endpoint *);
}
struct fwnode_reference_args {
    struct fwnode_handle *fwnode;
    unsigned int nargs;
    unsigned int args[8];
}
struct group_info {
    atomic_t usage;
    int ngroups;
    kgid_t gid[0];
}
struct hlist_bl_head {
    struct hlist_bl_node *first;
}
struct hlist_bl_node {
    struct hlist_bl_node *next;
    struct hlist_bl_node **pprev;
}
struct hlist_head {
    struct hlist_node *first;
}
struct hlist_node {
    struct hlist_node *next;
    struct hlist_node **pprev;
}
struct hrtimer {
    struct timerqueue_node node;
    ktime_t _softexpires;
    enum hrtimer_restart (*function)(struct hrtimer *);
    struct hrtimer_clock_base *base;
    u8 state;
    u8 is_rel;
}
struct hrtimer_clock_base {
    struct hrtimer_cpu_base *cpu_base;
    int index;
    clockid_t clockid;
    struct timerqueue_head active;
    ktime_t (*get_time)(void);
    ktime_t offset;
}
struct hrtimer_cpu_base {
    raw_spinlock_t lock;
    seqcount_t seq;
    struct hrtimer *running;
    unsigned int cpu;
    unsigned int active_bases;
    unsigned int clock_was_set_seq;
    bool migration_enabled;
    bool nohz_active;
    unsigned int in_hrtirq : 1;
    unsigned int hres_active : 1;
    unsigned int hang_detected : 1;
    ktime_t expires_next;
    struct hrtimer *next_timer;
    unsigned int nr_events;
    unsigned int nr_retries;
    unsigned int nr_hangs;
    unsigned int max_hang_time;
    struct hrtimer_clock_base clock_base[4];
}
struct i2c_adapter {
    struct module *owner;
    unsigned int class;
    const struct i2c_algorithm *algo;
    void *algo_data;
    const struct i2c_lock_operations *lock_ops;
    struct rt_mutex bus_lock;
    struct rt_mutex mux_lock;
    int timeout;
    int retries;
    struct device dev;
    int nr;
    char name[48];
    struct completion dev_released;
    struct mutex userspace_clients_lock;
    struct list_head userspace_clients;
    struct i2c_bus_recovery_info *bus_recovery_info;
    const struct i2c_adapter_quirks *quirks;
    struct irq_domain *host_notify_domain;
}
struct i2c_adapter_quirks {
    u64 flags;
    int max_num_msgs;
    u16 max_write_len;
    u16 max_read_len;
    u16 max_comb_1st_msg_len;
    u16 max_comb_2nd_msg_len;
}
struct i2c_algorithm {
    int (*master_xfer)(struct i2c_adapter *, struct i2c_msg *, int);
    int (*smbus_xfer)(struct i2c_adapter *, u16, unsigned short, char, u8, int, union i2c_smbus_data *);
    u32 (*functionality)(struct i2c_adapter *);
}
struct i2c_board_info {
    char type[20];
    unsigned short flags;
    unsigned short addr;
    void *platform_data;
    struct dev_archdata *archdata;
    struct device_node *of_node;
    struct fwnode_handle *fwnode;
    const struct property_entry *properties;
    const struct resource *resources;
    unsigned int num_resources;
    int irq;
}
struct i2c_bus_recovery_info {
    int (*recover_bus)(struct i2c_adapter *);
    int (*get_scl)(struct i2c_adapter *);
    void (*set_scl)(struct i2c_adapter *, int);
    int (*get_sda)(struct i2c_adapter *);
    void (*prepare_recovery)(struct i2c_adapter *);
    void (*unprepare_recovery)(struct i2c_adapter *);
    int scl_gpio;
    int sda_gpio;
}
struct i2c_client {
    unsigned short flags;
    unsigned short addr;
    char name[20];
    struct i2c_adapter *adapter;
    struct device dev;
    int irq;
    struct list_head detected;
}
struct i2c_device_id {
    char name[20];
    kernel_ulong_t driver_data;
}
struct i2c_driver {
    unsigned int class;
    int (*attach_adapter)(struct i2c_adapter *);
    int (*probe)(struct i2c_client *, const struct i2c_device_id *);
    int (*remove)(struct i2c_client *);
    int (*probe_new)(struct i2c_client *);
    void (*shutdown)(struct i2c_client *);
    void (*alert)(struct i2c_client *, enum i2c_alert_protocol, unsigned int);
    int (*command)(struct i2c_client *, unsigned int, void *);
    struct device_driver driver;
    const struct i2c_device_id *id_table;
    int (*detect)(struct i2c_client *, struct i2c_board_info *);
    const unsigned short *address_list;
    struct list_head clients;
    bool disable_i2c_core_irq_mapping;
}
struct i2c_lock_operations {
    void (*lock_bus)(struct i2c_adapter *, unsigned int);
    int (*trylock_bus)(struct i2c_adapter *, unsigned int);
    void (*unlock_bus)(struct i2c_adapter *, unsigned int);
}
struct i2c_msg {
    __u16 addr;
    __u16 flags;
    __u16 len;
    __u8 *buf;
}
struct iattr {
    unsigned int ia_valid;
    umode_t ia_mode;
    kuid_t ia_uid;
    kgid_t ia_gid;
    loff_t ia_size;
    struct timespec ia_atime;
    struct timespec ia_mtime;
    struct timespec ia_ctime;
    struct file *ia_file;
}
struct idr {
    struct radix_tree_root idr_rt;
    unsigned int idr_next;
}
struct incell_fourcfg {
    unsigned char first;
    unsigned char second;
    unsigned char third;
    unsigned char fourth;
}
struct incell_touch_cfg {
    unsigned int signature : 24;
    unsigned int cfggroup : 5;
    unsigned int invertx : 1;
    unsigned int inverty : 1;
    unsigned int swapxy : 1;
    union {
        unsigned int cfgdata;
        struct incell_twocfg twodata;
        struct incell_fourcfg fourdata;
    } data;
}
struct incell_twocfg {
    unsigned short first;
    unsigned short second;
}
struct inode {
    umode_t i_mode;
    unsigned short i_opflags;
    kuid_t i_uid;
    kgid_t i_gid;
    unsigned int i_flags;
    struct posix_acl *i_acl;
    struct posix_acl *i_default_acl;
    const struct inode_operations *i_op;
    struct super_block *i_sb;
    struct address_space *i_mapping;
    void *i_security;
    unsigned long i_ino;
    union {
        const unsigned int i_nlink;
        unsigned int __i_nlink;
    };
    dev_t i_rdev;
    loff_t i_size;
    struct timespec i_atime;
    struct timespec i_mtime;
    struct timespec i_ctime;
    spinlock_t i_lock;
    unsigned short i_bytes;
    unsigned int i_blkbits;
    enum rw_hint i_write_hint;
    blkcnt_t i_blocks;
    unsigned long i_state;
    struct rw_semaphore i_rwsem;
    unsigned long dirtied_when;
    unsigned long dirtied_time_when;
    struct hlist_node i_hash;
    struct list_head i_io_list;
    struct list_head i_lru;
    struct list_head i_sb_list;
    struct list_head i_wb_list;
    union {
        struct hlist_head i_dentry;
        struct callback_head i_rcu;
    };
    u64 i_version;
    atomic64_t i_sequence;
    atomic_t i_count;
    atomic_t i_dio_count;
    atomic_t i_writecount;
    const struct file_operations *i_fop;
    struct file_lock_context *i_flctx;
    struct address_space i_data;
    struct list_head i_devices;
    union {
        struct pipe_inode_info *i_pipe;
        struct block_device *i_bdev;
        struct cdev *i_cdev;
        char *i_link;
        unsigned int i_dir_seq;
    };
    __u32 i_generation;
    __u32 i_fsnotify_mask;
    struct fsnotify_mark_connector *i_fsnotify_marks;
    struct fscrypt_info *i_crypt_info;
    void *i_private;
}
struct inode_operations {
    struct dentry *(*lookup)(struct inode *, struct dentry *, unsigned int);
    const char *(*get_link)(struct dentry *, struct inode *, struct delayed_call *);
    int (*permission)(struct inode *, int);
    int (*permission2)(struct vfsmount *, struct inode *, int);
    struct posix_acl *(*get_acl)(struct inode *, int);
    int (*readlink)(struct dentry *, char *, int);
    int (*create)(struct inode *, struct dentry *, umode_t, bool);
    int (*link)(struct dentry *, struct inode *, struct dentry *);
    int (*unlink)(struct inode *, struct dentry *);
    int (*symlink)(struct inode *, struct dentry *, const char *);
    int (*mkdir)(struct inode *, struct dentry *, umode_t);
    int (*rmdir)(struct inode *, struct dentry *);
    int (*mknod)(struct inode *, struct dentry *, umode_t, dev_t);
    int (*rename)(struct inode *, struct dentry *, struct inode *, struct dentry *, unsigned int);
    int (*setattr)(struct dentry *, struct iattr *);
    int (*setattr2)(struct vfsmount *, struct dentry *, struct iattr *);
    int (*getattr)(const struct path *, struct kstat *, u32, unsigned int);
    ssize_t (*listxattr)(struct dentry *, char *, size_t);
    int (*fiemap)(struct inode *, struct fiemap_extent_info *, u64, u64);
    int (*update_time)(struct inode *, struct timespec *, int);
    int (*atomic_open)(struct inode *, struct dentry *, struct file *, unsigned int, umode_t, int *);
    int (*tmpfile)(struct inode *, struct dentry *, umode_t);
    int (*set_acl)(struct inode *, struct posix_acl *, int);
}
struct iov_iter {
    int type;
    size_t iov_offset;
    size_t count;
    union {
        const struct iovec *iov;
        const struct kvec *kvec;
        const struct bio_vec *bvec;
        struct pipe_inode_info *pipe;
    };
    union {
        unsigned long nr_segs;
        struct {...};
    };
}
struct iovec {
    void *iov_base;
    __kernel_size_t iov_len;
}
struct irq_affinity_notify {
    unsigned int irq;
    struct kref kref;
    struct work_struct work;
    void (*notify)(struct irq_affinity_notify *, const cpumask_t *);
    void (*release)(struct kref *);
}
struct irq_chip {
    struct device *parent_device;
    const char *name;
    unsigned int (*irq_startup)(struct irq_data *);
    void (*irq_shutdown)(struct irq_data *);
    void (*irq_enable)(struct irq_data *);
    void (*irq_disable)(struct irq_data *);
    void (*irq_ack)(struct irq_data *);
    void (*irq_mask)(struct irq_data *);
    void (*irq_mask_ack)(struct irq_data *);
    void (*irq_unmask)(struct irq_data *);
    void (*irq_eoi)(struct irq_data *);
    int (*irq_set_affinity)(struct irq_data *, const struct cpumask *, bool);
    int (*irq_retrigger)(struct irq_data *);
    int (*irq_set_type)(struct irq_data *, unsigned int);
    int (*irq_set_wake)(struct irq_data *, unsigned int);
    void (*irq_bus_lock)(struct irq_data *);
    void (*irq_bus_sync_unlock)(struct irq_data *);
    void (*irq_cpu_online)(struct irq_data *);
    void (*irq_cpu_offline)(struct irq_data *);
    void (*irq_suspend)(struct irq_data *);
    void (*irq_resume)(struct irq_data *);
    void (*irq_pm_shutdown)(struct irq_data *);
    void (*irq_calc_mask)(struct irq_data *);
    void (*irq_print_chip)(struct irq_data *, struct seq_file *);
    int (*irq_request_resources)(struct irq_data *);
    void (*irq_release_resources)(struct irq_data *);
    void (*irq_compose_msi_msg)(struct irq_data *, struct msi_msg *);
    void (*irq_write_msi_msg)(struct irq_data *, struct msi_msg *);
    int (*irq_get_irqchip_state)(struct irq_data *, enum irqchip_irq_state, bool *);
    int (*irq_set_irqchip_state)(struct irq_data *, enum irqchip_irq_state, bool);
    int (*irq_set_vcpu_affinity)(struct irq_data *, void *);
    void (*ipi_send_single)(struct irq_data *, unsigned int);
    void (*ipi_send_mask)(struct irq_data *, const struct cpumask *);
    unsigned long flags;
}
struct irq_chip_generic {
    raw_spinlock_t lock;
    void *reg_base;
    u32 (*reg_readl)(void *);
    void (*reg_writel)(u32, void *);
    void (*suspend)(struct irq_chip_generic *);
    void (*resume)(struct irq_chip_generic *);
    unsigned int irq_base;
    unsigned int irq_cnt;
    u32 mask_cache;
    u32 type_cache;
    u32 polarity_cache;
    u32 wake_enabled;
    u32 wake_active;
    unsigned int num_ct;
    void *private;
    unsigned long installed;
    unsigned long unused;
    struct irq_domain *domain;
    struct list_head list;
    struct irq_chip_type chip_types[0];
}
struct irq_chip_regs {
    unsigned long enable;
    unsigned long disable;
    unsigned long mask;
    unsigned long ack;
    unsigned long eoi;
    unsigned long type;
    unsigned long polarity;
}
struct irq_chip_type {
    struct irq_chip chip;
    struct irq_chip_regs regs;
    irq_flow_handler_t handler;
    u32 type;
    u32 mask_cache_priv;
    u32 *mask_cache;
}
struct irq_common_data {
    unsigned int state_use_accessors;
    void *handler_data;
    struct msi_desc *msi_desc;
    cpumask_var_t affinity;
    cpumask_var_t effective_affinity;
}
struct irq_data {
    u32 mask;
    unsigned int irq;
    unsigned long hwirq;
    struct irq_common_data *common;
    struct irq_chip *chip;
    struct irq_domain *domain;
    struct irq_data *parent_data;
    void *chip_data;
}
struct irq_desc {
    struct irq_common_data irq_common_data;
    struct irq_data irq_data;
    unsigned int *kstat_irqs;
    irq_flow_handler_t handle_irq;
    struct irqaction *action;
    unsigned int status_use_accessors;
    unsigned int core_internal_state__do_not_mess_with_it;
    unsigned int depth;
    unsigned int wake_depth;
    unsigned int tot_count;
    unsigned int irq_count;
    unsigned long last_unhandled;
    unsigned int irqs_unhandled;
    atomic_t threads_handled;
    int threads_handled_last;
    raw_spinlock_t lock;
    struct cpumask *percpu_enabled;
    const struct cpumask *percpu_affinity;
    const struct cpumask *affinity_hint;
    struct irq_affinity_notify *affinity_notify;
    unsigned long threads_oneshot;
    atomic_t threads_active;
    wait_queue_head_t wait_for_threads;
    unsigned int nr_actions;
    unsigned int no_suspend_depth;
    unsigned int cond_suspend_depth;
    unsigned int force_resume_depth;
    struct proc_dir_entry *dir;
    struct callback_head rcu;
    struct kobject kobj;
    struct mutex request_mutex;
    int parent_irq;
    struct module *owner;
    const char *name;
}
struct irq_domain {
    struct list_head link;
    const char *name;
    const struct irq_domain_ops *ops;
    void *host_data;
    unsigned int flags;
    unsigned int mapcount;
    struct fwnode_handle *fwnode;
    enum irq_domain_bus_token bus_token;
    struct irq_domain_chip_generic *gc;
    struct irq_domain *parent;
    irq_hw_number_t hwirq_max;
    unsigned int revmap_direct_max_irq;
    unsigned int revmap_size;
    struct radix_tree_root revmap_tree;
    unsigned int linear_revmap[];
}
struct irq_domain_chip_generic {
    unsigned int irqs_per_chip;
    unsigned int num_chips;
    unsigned int irq_flags_to_clear;
    unsigned int irq_flags_to_set;
    enum irq_gc_flags gc_flags;
    struct irq_chip_generic *gc[0];
}
struct irq_domain_ops {
    int (*match)(struct irq_domain *, struct device_node *, enum irq_domain_bus_token);
    int (*select)(struct irq_domain *, struct irq_fwspec *, enum irq_domain_bus_token);
    int (*map)(struct irq_domain *, unsigned int, irq_hw_number_t);
    void (*unmap)(struct irq_domain *, unsigned int);
    int (*xlate)(struct irq_domain *, struct device_node *, const u32 *, unsigned int, unsigned long *, unsigned int *);
    int (*alloc)(struct irq_domain *, unsigned int, unsigned int, void *);
    void (*free)(struct irq_domain *, unsigned int, unsigned int);
    void (*activate)(struct irq_domain *, struct irq_data *);
    void (*deactivate)(struct irq_domain *, struct irq_data *);
    int (*translate)(struct irq_domain *, struct irq_fwspec *, unsigned long *, unsigned int *);
}
struct irq_fwspec {
    struct fwnode_handle *fwnode;
    int param_count;
    u32 param[16];
}
struct irqaction {
    irq_handler_t handler;
    void *dev_id;
    void *percpu_dev_id;
    struct irqaction *next;
    irq_handler_t thread_fn;
    struct task_struct *thread;
    struct irqaction *secondary;
    unsigned int irq;
    unsigned int flags;
    unsigned long thread_flags;
    unsigned long thread_mask;
    const char *name;
    struct proc_dir_entry *dir;
}
struct k_sigaction {
    struct sigaction sa;
}
struct kernel_cap_struct {
    __u32 cap[2];
}
struct kernel_param {
    const char *name;
    struct module *mod;
    const struct kernel_param_ops *ops;
    const u16 perm;
    s8 level;
    u8 flags;
    union {
        void *arg;
        const struct kparam_string *str;
        const struct kparam_array *arr;
    };
}
struct kernel_param_ops {
    unsigned int flags;
    int (*set)(const char *, const struct kernel_param *);
    int (*get)(char *, const struct kernel_param *);
    void (*free)(void *);
}
struct kernel_symbol {
    unsigned long value;
    const char *name;
}
struct kernfs_elem_attr {
    const struct kernfs_ops *ops;
    struct kernfs_open_node *open;
    loff_t size;
    struct kernfs_node *notify_next;
}
struct kernfs_elem_dir {
    unsigned long subdirs;
    struct rb_root children;
    struct kernfs_root *root;
}
struct kernfs_elem_symlink {
    struct kernfs_node *target_kn;
}
struct kernfs_node {
    atomic_t count;
    atomic_t active;
    struct kernfs_node *parent;
    const char *name;
    struct rb_node rb;
    const void *ns;
    unsigned int hash;
    union {
        struct kernfs_elem_dir dir;
        struct kernfs_elem_symlink symlink;
        struct kernfs_elem_attr attr;
    };
    void *priv;
    union kernfs_node_id id;
    unsigned short flags;
    umode_t mode;
    struct kernfs_iattrs *iattr;
}
struct kernfs_open_file {
    struct kernfs_node *kn;
    struct file *file;
    struct seq_file *seq_file;
    void *priv;
    struct mutex mutex;
    struct mutex prealloc_mutex;
    int event;
    struct list_head list;
    char *prealloc_buf;
    size_t atomic_write_len;
    bool mmapped : 1;
    bool released : 1;
    const struct vm_operations_struct *vm_ops;
}
struct kernfs_ops {
    int (*open)(struct kernfs_open_file *);
    void (*release)(struct kernfs_open_file *);
    int (*seq_show)(struct seq_file *, void *);
    void *(*seq_start)(struct seq_file *, loff_t *);
    void *(*seq_next)(struct seq_file *, void *, loff_t *);
    void (*seq_stop)(struct seq_file *, void *);
    ssize_t (*read)(struct kernfs_open_file *, char *, size_t, loff_t);
    size_t atomic_write_len;
    bool prealloc;
    ssize_t (*write)(struct kernfs_open_file *, char *, size_t, loff_t);
    unsigned int (*poll)(struct kernfs_open_file *, struct poll_table_struct *);
    int (*mmap)(struct kernfs_open_file *, struct vm_area_struct *);
}
struct kernfs_root {
    struct kernfs_node *kn;
    unsigned int flags;
    struct idr ino_idr;
    u32 next_generation;
    struct kernfs_syscall_ops *syscall_ops;
    struct list_head supers;
    wait_queue_head_t deactivate_waitq;
}
struct kernfs_syscall_ops {
    int (*remount_fs)(struct kernfs_root *, int *, char *);
    int (*show_options)(struct seq_file *, struct kernfs_root *);
    int (*mkdir)(struct kernfs_node *, const char *, umode_t);
    int (*rmdir)(struct kernfs_node *);
    int (*rename)(struct kernfs_node *, struct kernfs_node *, const char *);
    int (*show_path)(struct seq_file *, struct kernfs_node *, struct kernfs_root *);
}
struct key {
    refcount_t usage;
    key_serial_t serial;
    union {
        struct list_head graveyard_link;
        struct rb_node serial_node;
    };
    struct rw_semaphore sem;
    struct key_user *user;
    void *security;
    union {
        time_t expiry;
        time_t revoked_at;
    };
    time_t last_used_at;
    kuid_t uid;
    kgid_t gid;
    key_perm_t perm;
    unsigned short quotalen;
    unsigned short datalen;
    short state;
    unsigned long flags;
    union {
        struct keyring_index_key index_key;
        struct {...};
    };
    union {
        union key_payload payload;
        struct {...};
    };
    struct key_restriction *restrict_link;
}
struct key_restriction {
    key_restrict_link_func_t check;
    struct key *key;
    struct key_type *keytype;
}
struct keyring_index_key {
    struct key_type *type;
    const char *description;
    size_t desc_len;
}
struct kiocb {
    struct file *ki_filp;
    loff_t ki_pos;
    void (*ki_complete)(struct kiocb *, long, long);
    void *private;
    int ki_flags;
    enum rw_hint ki_hint;
}
struct klist_node {
    void *n_klist;
    struct list_head n_node;
    struct kref n_ref;
}
struct kobj_ns_type_operations {
    enum kobj_ns_type type;
    bool (*current_may_mount)(void);
    void *(*grab_current_ns)(void);
    const void *(*netlink_ns)(struct sock *);
    const void *(*initial_ns)(void);
    void (*drop_ns)(void *);
}
struct kobj_type {
    void (*release)(struct kobject *);
    const struct sysfs_ops *sysfs_ops;
    struct attribute **default_attrs;
    const struct kobj_ns_type_operations *(*child_ns_type)(struct kobject *);
    const void *(*namespace)(struct kobject *);
}
struct kobj_uevent_env {
    char *argv[3];
    char *envp[32];
    int envp_idx;
    char buf[2048];
    int buflen;
}
struct kobject {
    const char *name;
    struct list_head entry;
    struct kobject *parent;
    struct kset *kset;
    struct kobj_type *ktype;
    struct kernfs_node *sd;
    struct kref kref;
    unsigned int state_initialized : 1;
    unsigned int state_in_sysfs : 1;
    unsigned int state_add_uevent_sent : 1;
    unsigned int state_remove_uevent_sent : 1;
    unsigned int uevent_suppress : 1;
}
struct kparam_array {
    unsigned int max;
    unsigned int elemsize;
    unsigned int *num;
    const struct kernel_param_ops *ops;
    void *elem;
}
struct kparam_string {
    unsigned int maxlen;
    char *string;
}
struct kqid {
    union {
        kuid_t uid;
        kgid_t gid;
        kprojid_t projid;
    };
    enum quota_type type;
}
struct kref {
    refcount_t refcount;
}
struct kset {
    struct list_head list;
    spinlock_t list_lock;
    struct kobject kobj;
    const struct kset_uevent_ops *uevent_ops;
}
struct kset_uevent_ops {
    int (* const filter)(struct kset *, struct kobject *);
    const char *(* const name)(struct kset *, struct kobject *);
    int (* const uevent)(struct kset *, struct kobject *, struct kobj_uevent_env *);
}
struct kstat {
    u32 result_mask;
    umode_t mode;
    unsigned int nlink;
    uint32_t blksize;
    u64 attributes;
    u64 attributes_mask;
    u64 ino;
    dev_t dev;
    dev_t rdev;
    kuid_t uid;
    kgid_t gid;
    loff_t size;
    struct timespec atime;
    struct timespec mtime;
    struct timespec ctime;
    struct timespec btime;
    u64 blocks;
}
struct kvec {
    void *iov_base;
    size_t iov_len;
}
struct latch_tree_node {
    struct rb_node node[2];
}
struct list_head {
    struct list_head *next;
    struct list_head *prev;
}
struct list_lru {
    struct list_lru_node *node;
    struct list_head list;
    bool memcg_aware;
}
struct list_lru_memcg {
    struct list_lru_one *lru[0];
}
struct list_lru_node {
    spinlock_t lock;
    struct list_lru_one lru;
    struct list_lru_memcg *memcg_lrus;
    long nr_items;
}
struct list_lru_one {
    struct list_head list;
    long nr_items;
}
struct llist_node {
    struct llist_node *next;
}
struct load_weight {
    unsigned long weight;
    u32 inv_weight;
}
struct lock_class_key {
    <no data fields>
}
struct lock_manager_operations {
    int (*lm_compare_owner)(struct file_lock *, struct file_lock *);
    unsigned long (*lm_owner_key)(struct file_lock *);
    fl_owner_t (*lm_get_owner)(fl_owner_t);
    void (*lm_put_owner)(fl_owner_t);
    void (*lm_notify)(struct file_lock *);
    int (*lm_grant)(struct file_lock *, int);
    bool (*lm_break)(struct file_lock *);
    int (*lm_change)(struct file_lock *, int, struct list_head *);
    void (*lm_setup)(struct file_lock *, void **);
}
struct lockref {
    union {
        __u64 lock_count;
        struct {...};
    };
}
struct lsec_panel_notifier_event {
    void *data;
}
struct mem_dqblk {
    qsize_t dqb_bhardlimit;
    qsize_t dqb_bsoftlimit;
    qsize_t dqb_curspace;
    qsize_t dqb_rsvspace;
    qsize_t dqb_ihardlimit;
    qsize_t dqb_isoftlimit;
    qsize_t dqb_curinodes;
    time64_t dqb_btime;
    time64_t dqb_itime;
}
struct mem_dqinfo {
    struct quota_format_type *dqi_format;
    int dqi_fmt_id;
    struct list_head dqi_dirty_list;
    unsigned long dqi_flags;
    unsigned int dqi_bgrace;
    unsigned int dqi_igrace;
    qsize_t dqi_max_spc_limit;
    qsize_t dqi_max_ino_limit;
    void *dqi_priv;
}
struct miscdevice {
    int minor;
    const char *name;
    const struct file_operations *fops;
    struct list_head list;
    struct device *parent;
    struct device *this_device;
    const struct attribute_group **groups;
    const char *nodename;
    umode_t mode;
}
struct mm_rss_stat {
    atomic_long_t count[4];
}
struct mm_struct {
    struct vm_area_struct *mmap;
    struct rb_root mm_rb;
    u64 vmacache_seqnum;
    unsigned long (*get_unmapped_area)(struct file *, unsigned long, unsigned long, unsigned long, unsigned long);
    unsigned long mmap_base;
    unsigned long mmap_legacy_base;
    unsigned long task_size;
    unsigned long highest_vm_end;
    pgd_t *pgd;
    atomic_t mm_users;
    atomic_t mm_count;
    atomic_long_t nr_ptes;
    atomic_long_t nr_pmds;
    int map_count;
    spinlock_t page_table_lock;
    struct rw_semaphore mmap_sem;
    struct list_head mmlist;
    unsigned long hiwater_rss;
    unsigned long hiwater_vm;
    unsigned long total_vm;
    unsigned long locked_vm;
    unsigned long pinned_vm;
    unsigned long data_vm;
    unsigned long exec_vm;
    unsigned long stack_vm;
    unsigned long def_flags;
    unsigned long start_code;
    unsigned long end_code;
    unsigned long start_data;
    unsigned long end_data;
    unsigned long start_brk;
    unsigned long brk;
    unsigned long start_stack;
    unsigned long arg_start;
    unsigned long arg_end;
    unsigned long env_start;
    unsigned long env_end;
    unsigned long saved_auxv[44];
    struct mm_rss_stat rss_stat;
    struct linux_binfmt *binfmt;
    cpumask_var_t cpu_vm_mask_var;
    mm_context_t context;
    unsigned long flags;
    struct core_state *core_state;
    atomic_t membarrier_state;
    spinlock_t ioctx_lock;
    struct kioctx_table *ioctx_table;
    struct task_struct *owner;
    struct user_namespace *user_ns;
    struct file *exe_file;
    atomic_t tlb_flush_pending;
    struct uprobes_state uprobes_state;
    struct work_struct async_put_work;
}
struct mod_arch_specific {
    struct mod_plt_sec core;
    struct mod_plt_sec init;
    struct plt_entry *ftrace_trampoline;
}
struct mod_kallsyms {
    Elf64_Sym *symtab;
    unsigned int num_symtab;
    char *strtab;
}
struct mod_plt_sec {
    struct elf64_shdr *plt;
    int plt_num_entries;
    int plt_max_entries;
}
struct mod_tree_node {
    struct module *mod;
    struct latch_tree_node node;
}
struct module {
    enum module_state state;
    struct list_head list;
    char name[56];
    struct module_kobject mkobj;
    struct module_attribute *modinfo_attrs;
    const char *version;
    const char *srcversion;
    struct kobject *holders_dir;
    const struct kernel_symbol *syms;
    const s32 *crcs;
    unsigned int num_syms;
    struct mutex param_lock;
    struct kernel_param *kp;
    unsigned int num_kp;
    unsigned int num_gpl_syms;
    const struct kernel_symbol *gpl_syms;
    const s32 *gpl_crcs;
    bool async_probe_requested;
    const struct kernel_symbol *gpl_future_syms;
    const s32 *gpl_future_crcs;
    unsigned int num_gpl_future_syms;
    unsigned int num_exentries;
    struct exception_table_entry *extable;
    int (*init)(void);
    struct module_layout core_layout;
    struct module_layout init_layout;
    struct mod_arch_specific arch;
    unsigned long taints;
    unsigned int num_bugs;
    struct list_head bug_list;
    struct bug_entry *bug_table;
    struct mod_kallsyms *kallsyms;
    struct mod_kallsyms core_kallsyms;
    struct module_sect_attrs *sect_attrs;
    struct module_notes_attrs *notes_attrs;
    char *args;
    void *percpu;
    unsigned int percpu_size;
    unsigned int num_tracepoints;
    struct tracepoint * const *tracepoints_ptrs;
    unsigned int num_trace_bprintk_fmt;
    const char **trace_bprintk_fmt_start;
    struct trace_event_call **trace_events;
    unsigned int num_trace_events;
    struct trace_eval_map **trace_evals;
    unsigned int num_trace_evals;
    struct list_head source_list;
    struct list_head target_list;
    void (*exit)(void);
    atomic_t refcnt;
}
struct module_attribute {
    struct attribute attr;
    ssize_t (*show)(struct module_attribute *, struct module_kobject *, char *);
    ssize_t (*store)(struct module_attribute *, struct module_kobject *, const char *, size_t);
    void (*setup)(struct module *, const char *);
    int (*test)(struct module *);
    void (*free)(struct module *);
}
struct module_kobject {
    struct kobject kobj;
    struct module *mod;
    struct kobject *drivers_dir;
    struct module_param_attrs *mp;
    struct completion *kobj_completion;
}
struct module_layout {
    void *base;
    unsigned int size;
    unsigned int text_size;
    unsigned int ro_size;
    unsigned int ro_after_init_size;
    struct mod_tree_node mtn;
}
struct modversion_info {
    unsigned long crc;
    char name[56];
}
struct mutex {
    atomic_long_t owner;
    spinlock_t wait_lock;
    struct optimistic_spin_queue osq;
    struct list_head wait_list;
}
struct new_area_key {
    short key_value;
    short key_x;
    short key_y;
    short x_delta;
    short y_delta;
}
struct nfs4_lock_info {
    struct nfs4_lock_state *owner;
}
struct nfs_lock_info {
    u32 state;
    struct nlm_lockowner *owner;
    struct list_head list;
}
struct notifier_block {
    notifier_fn_t notifier_call;
    struct notifier_block *next;
    int priority;
}
struct ns_common {
    atomic_long_t stashed;
    const struct proc_ns_operations *ops;
    unsigned int inum;
}
struct nsproxy {
    atomic_t count;
    struct uts_namespace *uts_ns;
    struct ipc_namespace *ipc_ns;
    struct mnt_namespace *mnt_ns;
    struct pid_namespace *pid_ns_for_children;
    struct net *net_ns;
    struct cgroup_namespace *cgroup_ns;
}
struct nxp685x_platform_data {
    int sqlradio_pow;
    int sqlradio_ant;
    int sqlfm_reset;
}
struct of_device_id {
    char name[32];
    char type[32];
    char compatible[128];
    const void *data;
}
struct of_phandle_args {
    struct device_node *np;
    int args_count;
    uint32_t args[16];
}
struct optimistic_spin_queue {
    atomic_t tail;
}
struct pacct_struct {
    int ac_flag;
    long ac_exitcode;
    unsigned long ac_mem;
    u64 ac_utime;
    u64 ac_stime;
    unsigned long ac_minflt;
    unsigned long ac_majflt;
}
struct page {
    unsigned long flags;
    union {
        struct address_space *mapping;
        void *s_mem;
        atomic_t compound_mapcount;
    };
    union {
        unsigned long index;
        void *freelist;
    };
    union {
        unsigned long counters;
        struct {...};
    };
    union {
        struct list_head lru;
        struct dev_pagemap *pgmap;
        struct {...};
        struct callback_head callback_head;
        struct {...};
    };
    union {
        unsigned long private;
        spinlock_t ptl;
        struct kmem_cache *slab_cache;
    };
    struct mem_cgroup *mem_cgroup;
}
struct page_frag {
    struct page *page;
    __u32 offset;
    __u32 size;
}
struct path {
    struct vfsmount *mnt;
    struct dentry *dentry;
}
struct percpu_ref {
    atomic_long_t count;
    unsigned long percpu_count_ptr;
    percpu_ref_func_t *release;
    percpu_ref_func_t *confirm_switch;
    bool force_atomic : 1;
    struct callback_head rcu;
}
struct percpu_rw_semaphore {
    struct rcu_sync rss;
    unsigned int *read_count;
    struct rw_semaphore rw_sem;
    struct rcuwait writer;
    int readers_block;
}
struct pid {
    atomic_t count;
    unsigned int level;
    struct hlist_head tasks[3];
    struct callback_head rcu;
    struct upid numbers[1];
}
struct pid_link {
    struct hlist_node node;
    struct pid *pid;
}
struct pid_namespace {
    struct kref kref;
    struct pidmap pidmap[128];
    struct callback_head rcu;
    int last_pid;
    unsigned int nr_hashed;
    struct task_struct *child_reaper;
    struct kmem_cache *pid_cachep;
    unsigned int level;
    struct pid_namespace *parent;
    struct vfsmount *proc_mnt;
    struct dentry *proc_self;
    struct dentry *proc_thread_self;
    struct fs_pin *bacct;
    struct user_namespace *user_ns;
    struct ucounts *ucounts;
    struct work_struct proc_work;
    kgid_t pid_gid;
    int hide_pid;
    int reboot;
    struct ns_common ns;
}
struct pidmap {
    atomic_t nr_free;
    void *page;
}
struct plist_node {
    int prio;
    struct list_head prio_list;
    struct list_head node_list;
}
struct plt_entry {
    __le32 mov0;
    __le32 mov1;
    __le32 mov2;
    __le32 br;
}
struct pm_message {
    int event;
}
struct pm_subsys_data {
    spinlock_t lock;
    unsigned int refcount;
    struct list_head clock_list;
    struct pm_domain_data *domain_data;
}
struct poll_table_struct {
    poll_queue_proc _qproc;
    unsigned long _key;
}
struct pollfd {
    int fd;
    short events;
    short revents;
}
struct prev_cputime {
    u64 utime;
    u64 stime;
    raw_spinlock_t lock;
}
struct property {
    char *name;
    int length;
    void *value;
    struct property *next;
    unsigned long _flags;
    unsigned int unique_id;
    struct bin_attribute attr;
}
struct property_entry {
    const char *name;
    size_t length;
    bool is_array;
    bool is_string;
    union {
        union {...} pointer;
        union {...} value;
    };
}
struct pwm_args {
    unsigned int period;
    enum pwm_polarity polarity;
}
struct pwm_capture {
    unsigned int period;
    unsigned int duty_cycle;
}
struct pwm_chip {
    struct device *dev;
    struct list_head list;
    const struct pwm_ops *ops;
    int base;
    unsigned int npwm;
    struct pwm_device *pwms;
    struct pwm_device *(*of_xlate)(struct pwm_chip *, const struct of_phandle_args *);
    unsigned int of_pwm_n_cells;
}
struct pwm_device {
    const char *label;
    unsigned long flags;
    unsigned int hwpwm;
    unsigned int pwm;
    struct pwm_chip *chip;
    void *chip_data;
    struct pwm_args args;
    struct pwm_state state;
}
struct pwm_ops {
    int (*request)(struct pwm_chip *, struct pwm_device *);
    void (*free)(struct pwm_chip *, struct pwm_device *);
    int (*config)(struct pwm_chip *, struct pwm_device *, int, int);
    int (*set_polarity)(struct pwm_chip *, struct pwm_device *, enum pwm_polarity);
    int (*capture)(struct pwm_chip *, struct pwm_device *, struct pwm_capture *, unsigned long);
    int (*enable)(struct pwm_chip *, struct pwm_device *);
    void (*disable)(struct pwm_chip *, struct pwm_device *);
    int (*apply)(struct pwm_chip *, struct pwm_device *, struct pwm_state *);
    void (*get_state)(struct pwm_chip *, struct pwm_device *, struct pwm_state *);
    void (*dbg_show)(struct pwm_chip *, struct seq_file *);
    struct module *owner;
}
struct pwm_state {
    unsigned int period;
    unsigned int duty_cycle;
    enum pwm_polarity polarity;
    bool enabled;
}
struct qc_dqblk {
    int d_fieldmask;
    u64 d_spc_hardlimit;
    u64 d_spc_softlimit;
    u64 d_ino_hardlimit;
    u64 d_ino_softlimit;
    u64 d_space;
    u64 d_ino_count;
    s64 d_ino_timer;
    s64 d_spc_timer;
    int d_ino_warns;
    int d_spc_warns;
    u64 d_rt_spc_hardlimit;
    u64 d_rt_spc_softlimit;
    u64 d_rt_space;
    s64 d_rt_spc_timer;
    int d_rt_spc_warns;
}
struct qc_info {
    int i_fieldmask;
    unsigned int i_flags;
    unsigned int i_spc_timelimit;
    unsigned int i_ino_timelimit;
    unsigned int i_rt_spc_timelimit;
    unsigned int i_spc_warnlimit;
    unsigned int i_ino_warnlimit;
    unsigned int i_rt_spc_warnlimit;
}
struct qc_state {
    unsigned int s_incoredqs;
    struct qc_type_state s_state[3];
}
struct qc_type_state {
    unsigned int flags;
    unsigned int spc_timelimit;
    unsigned int ino_timelimit;
    unsigned int rt_spc_timelimit;
    unsigned int spc_warnlimit;
    unsigned int ino_warnlimit;
    unsigned int rt_spc_warnlimit;
    unsigned long long ino;
    blkcnt_t blocks;
    blkcnt_t nextents;
}
struct qstr {
    union {
        struct {...};
        u64 hash_len;
    };
    const unsigned char *name;
}
struct quota_format_ops {
    int (*check_quota_file)(struct super_block *, int);
    int (*read_file_info)(struct super_block *, int);
    int (*write_file_info)(struct super_block *, int);
    int (*free_file_info)(struct super_block *, int);
    int (*read_dqblk)(struct dquot *);
    int (*commit_dqblk)(struct dquot *);
    int (*release_dqblk)(struct dquot *);
    int (*get_next_id)(struct super_block *, struct kqid *);
}
struct quota_format_type {
    int qf_fmt_id;
    const struct quota_format_ops *qf_ops;
    struct module *qf_owner;
    struct quota_format_type *qf_next;
}
struct quota_info {
    unsigned int flags;
    struct rw_semaphore dqio_sem;
    struct inode *files[3];
    struct mem_dqinfo info[3];
    const struct quota_format_ops *ops[3];
}
struct quotactl_ops {
    int (*quota_on)(struct super_block *, int, int, const struct path *);
    int (*quota_off)(struct super_block *, int);
    int (*quota_enable)(struct super_block *, unsigned int);
    int (*quota_disable)(struct super_block *, unsigned int);
    int (*quota_sync)(struct super_block *, int);
    int (*set_info)(struct super_block *, int, struct qc_info *);
    int (*get_dqblk)(struct super_block *, struct kqid, struct qc_dqblk *);
    int (*get_nextdqblk)(struct super_block *, struct kqid *, struct qc_dqblk *);
    int (*set_dqblk)(struct super_block *, struct kqid, struct qc_dqblk *);
    int (*get_state)(struct super_block *, struct qc_state *);
    int (*rm_xquota)(struct super_block *, unsigned int);
}
struct radix_tree_node {
    unsigned char shift;
    unsigned char offset;
    unsigned char count;
    unsigned char exceptional;
    struct radix_tree_node *parent;
    struct radix_tree_root *root;
    union {
        struct list_head private_list;
        struct callback_head callback_head;
    };
    void *slots[64];
    unsigned long tags[3][1];
}
struct radix_tree_root {
    gfp_t gfp_mask;
    struct radix_tree_node *rnode;
}
struct ravg {
    u64 mark_start;
    u32 sum;
    u32 demand;
    u32 sum_latest;
    u32 sum_history[6];
    u32 curr_window;
    u32 prev_window;
    u16 active_windows;
}
struct raw_spinlock {
    arch_spinlock_t raw_lock;
}
struct rb_node {
    unsigned long __rb_parent_color;
    struct rb_node *rb_right;
    struct rb_node *rb_left;
}
struct rb_root {
    struct rb_node *rb_node;
}
struct rb_root_cached {
    struct rb_root rb_root;
    struct rb_node *rb_leftmost;
}
struct rcu_sync {
    int gp_state;
    int gp_count;
    wait_queue_head_t gp_wait;
    int cb_state;
    struct callback_head cb_head;
    enum rcu_sync_type gp_type;
}
struct rcuwait {
    struct task_struct *task;
}
struct refcount_struct {
    atomic_t refs;
}
struct resource {
    resource_size_t start;
    resource_size_t end;
    const char *name;
    unsigned long flags;
    unsigned long desc;
    struct resource *parent;
    struct resource *sibling;
    struct resource *child;
}
struct restart_block {
    long (*fn)(struct restart_block *);
    union {
        struct {...} futex;
        struct {...} nanosleep;
        struct {...} poll;
    };
}
struct rlimit {
    __kernel_ulong_t rlim_cur;
    __kernel_ulong_t rlim_max;
}
struct rt_mutex {
    raw_spinlock_t wait_lock;
    struct rb_root_cached waiters;
    struct task_struct *owner;
}
struct rw_semaphore {
    atomic_long_t count;
    struct list_head wait_list;
    raw_spinlock_t wait_lock;
    struct optimistic_spin_queue osq;
    struct task_struct *owner;
}
struct sb_writers {
    int frozen;
    wait_queue_head_t wait_unfrozen;
    struct percpu_rw_semaphore rw_sem[3];
}
struct sched_avg {
    u64 last_update_time;
    u64 load_sum;
    u32 util_sum;
    u32 period_contrib;
    unsigned long load_avg;
    unsigned long util_avg;
    struct util_est util_est;
}
struct sched_dl_entity {
    struct rb_node rb_node;
    u64 dl_runtime;
    u64 dl_deadline;
    u64 dl_period;
    u64 dl_bw;
    u64 dl_density;
    s64 runtime;
    u64 deadline;
    unsigned int flags;
    int dl_throttled;
    int dl_boosted;
    int dl_yielded;
    int dl_non_contending;
    struct hrtimer dl_timer;
    struct hrtimer inactive_timer;
}
struct sched_entity {
    struct load_weight load;
    struct rb_node run_node;
    struct list_head group_node;
    unsigned int on_rq;
    u64 exec_start;
    u64 sum_exec_runtime;
    u64 vruntime;
    u64 prev_sum_exec_runtime;
    u64 s_sum_exec_runtime;
    u64 b_sum_exec_runtime;
    u64 nr_migrations;
    struct sched_statistics statistics;
    int depth;
    struct sched_entity *parent;
    struct cfs_rq *cfs_rq;
    struct cfs_rq *my_q;
    struct sched_avg avg;
}
struct sched_info {
    unsigned long pcount;
    unsigned long long run_delay;
    unsigned long long last_arrival;
    unsigned long long last_queued;
}
struct sched_rt_entity {
    struct list_head run_list;
    unsigned long timeout;
    unsigned long watchdog_stamp;
    unsigned int time_slice;
    unsigned short on_rq;
    unsigned short on_list;
    struct sched_rt_entity *back;
    struct sched_rt_entity *parent;
    struct rt_rq *rt_rq;
    struct rt_rq *my_q;
}
struct sched_statistics {
    u64 wait_start;
    u64 wait_max;
    u64 wait_count;
    u64 wait_sum;
    u64 iowait_count;
    u64 iowait_sum;
    u64 sleep_start;
    u64 sleep_max;
    s64 sum_sleep_runtime;
    u64 block_start;
    u64 block_max;
    u64 exec_max;
    u64 slice_max;
    u64 nr_migrations_cold;
    u64 nr_failed_migrations_affine;
    u64 nr_failed_migrations_running;
    u64 nr_failed_migrations_hot;
    u64 nr_forced_migrations;
    u64 nr_wakeups;
    u64 nr_wakeups_sync;
    u64 nr_wakeups_migrate;
    u64 nr_wakeups_local;
    u64 nr_wakeups_remote;
    u64 nr_wakeups_affine;
    u64 nr_wakeups_affine_attempts;
    u64 nr_wakeups_passive;
    u64 nr_wakeups_idle;
}
struct seccomp {
    int mode;
    struct seccomp_filter *filter;
}
struct semaphore {
    raw_spinlock_t lock;
    unsigned int count;
    struct list_head wait_list;
}
struct seq_file {
    char *buf;
    size_t size;
    size_t from;
    size_t count;
    size_t pad_until;
    loff_t index;
    loff_t read_pos;
    u64 version;
    struct mutex lock;
    const struct seq_operations *op;
    int poll_event;
    const struct file *file;
    void *private;
}
struct seq_operations {
    void *(*start)(struct seq_file *, loff_t *);
    void (*stop)(struct seq_file *, void *);
    void *(*next)(struct seq_file *, void *, loff_t *);
    int (*show)(struct seq_file *, void *);
}
struct seqcount {
    unsigned int sequence;
}
struct shrink_control {
    gfp_t gfp_mask;
    unsigned long nr_to_scan;
    unsigned long nr_scanned;
    int nid;
    struct mem_cgroup *memcg;
}
struct shrinker {
    unsigned long (*count_objects)(struct shrinker *, struct shrink_control *);
    unsigned long (*scan_objects)(struct shrinker *, struct shrink_control *);
    int seeks;
    long batch;
    unsigned long flags;
    struct list_head list;
    atomic_long_t *nr_deferred;
}
struct sigaction {
    __sighandler_t sa_handler;
    unsigned long sa_flags;
    __sigrestore_t sa_restorer;
    sigset_t sa_mask;
}
struct sighand_struct {
    atomic_t count;
    struct k_sigaction action[64];
    spinlock_t siglock;
    wait_queue_head_t signalfd_wqh;
}
struct siginfo {
    int si_signo;
    int si_errno;
    int si_code;
    union {
        int _pad[28];
        struct {...} _kill;
        struct {...} _timer;
        struct {...} _rt;
        struct {...} _sigchld;
        struct {...} _sigfault;
        struct {...} _sigpoll;
        struct {...} _sigsys;
    } _sifields;
}
struct signal_struct {
    atomic_t sigcnt;
    atomic_t live;
    int nr_threads;
    struct list_head thread_head;
    wait_queue_head_t wait_chldexit;
    struct task_struct *curr_target;
    struct sigpending shared_pending;
    int group_exit_code;
    int notify_count;
    struct task_struct *group_exit_task;
    int group_stop_count;
    unsigned int flags;
    unsigned int is_child_subreaper : 1;
    unsigned int has_child_subreaper : 1;
    int posix_timer_id;
    struct list_head posix_timers;
    struct hrtimer real_timer;
    ktime_t it_real_incr;
    struct cpu_itimer it[2];
    struct thread_group_cputimer cputimer;
    struct task_cputime cputime_expires;
    struct list_head cpu_timers[3];
    struct pid *leader_pid;
    struct pid *tty_old_pgrp;
    int leader;
    struct tty_struct *tty;
    seqlock_t stats_lock;
    u64 utime;
    u64 stime;
    u64 cutime;
    u64 cstime;
    u64 gtime;
    u64 cgtime;
    struct prev_cputime prev_cputime;
    unsigned long nvcsw;
    unsigned long nivcsw;
    unsigned long cnvcsw;
    unsigned long cnivcsw;
    unsigned long min_flt;
    unsigned long maj_flt;
    unsigned long cmin_flt;
    unsigned long cmaj_flt;
    unsigned long inblock;
    unsigned long oublock;
    unsigned long cinblock;
    unsigned long coublock;
    unsigned long maxrss;
    unsigned long cmaxrss;
    struct task_io_accounting ioac;
    unsigned long long sum_sched_runtime;
    struct rlimit rlim[16];
    struct pacct_struct pacct;
    struct taskstats *stats;
    unsigned int audit_tty;
    struct tty_audit_buf *tty_audit_buf;
    bool oom_flag_origin;
    short oom_score_adj;
    short oom_score_adj_min;
    struct mm_struct *oom_mm;
    struct mutex cred_guard_mutex;
}
struct sigpending {
    struct list_head list;
    sigset_t signal;
}
struct special_key {
    uint16_t key_num;
    uint16_t special_keyvalue[5];
}
struct spinlock {
    union {
        struct raw_spinlock rlock;
    };
}
struct sql_info_mcu {
    uint16_t bus_mode;
    uint16_t bus_width;
    uint16_t bpp;
    uint16_t te_pol;
    uint32_t te_sync_delay;
    struct sql_timing_mcu timing;
}
struct sql_info_mipi {
    uint16_t work_mode;
    uint16_t video_bus_width;
    uint32_t lan_number;
    uint32_t phy_feq;
    uint16_t h_sync_pol;
    uint16_t v_sync_pol;
    uint16_t de_pol;
    uint16_t te_pol;
    uint16_t color_mode_pol;
    uint16_t shut_down_pol;
    struct sql_timing_rgb timing;
}
struct sql_info_rgb {
    uint16_t cmd_bus_mode;
    uint16_t video_bus_width;
    uint16_t h_sync_pol;
    uint16_t v_sync_pol;
    uint16_t de_pol;
    struct sql_timing_rgb timing;
}
struct sql_panel_cfg {
    uint32_t lcd_id;
    struct sql_panel_spec panel;
}
struct sql_panel_spec {
    uint32_t cap;
    uint16_t width;
    uint16_t height;
    uint32_t fps;
    uint16_t type;
    uint16_t direction;
    uint16_t is_need_reset;
    union {
        struct sql_info_mcu mcu;
        struct sql_info_rgb rgb;
        struct sql_info_mipi mipi;
    } info;
    uint8_t m_LvdsFormat;
    uint8_t m_OutFace;
    uint8_t m_LcdRgbOrder;
    uint8_t m_Lcdbits;
    sqlpair ClockSourceSet;
    uint32_t pclock;
    uint32_t rot_sig;
    uint8_t resev[8];
    incelltcfg incelltouch;
}
struct sql_timing_mcu {
    uint16_t rcss;
    uint16_t rlpw;
    uint16_t rhpw;
    uint16_t wcss;
    uint16_t wlpw;
    uint16_t whpw;
}
struct sql_timing_rgb {
    uint16_t hfp;
    uint16_t hbp;
    uint16_t hsync;
    uint16_t vfp;
    uint16_t vbp;
    uint16_t vsync;
}
struct sqlfm_band_parm {
    unsigned char band;
    unsigned int MaxFreq;
    unsigned int MinFreq;
    unsigned int FreqStep;
    int reserve[4];
}
struct sqlfm_quality_parm {
    unsigned char rssilevel;
    unsigned char usn;
    unsigned char wam;
    unsigned char offset;
    uint16_t freq;
    unsigned char snr;
    unsigned char rxcca;
    unsigned char chsc;
    unsigned char isqualityok;
    unsigned char Qvalue;
    unsigned char Qtype;
    int reserve[4];
}
struct sqlfm_rds_report {
    void *rpt_array;
    u8 *rpt_cnt;
    u16 array_len;
}
struct sqlfm_rssi_parm {
    unsigned char rssilevel;
    unsigned char usn;
    unsigned char wam;
    unsigned char offset;
    uint16_t freq;
}
struct sqlfm_seek_parm {
    unsigned char type;
    unsigned char parama;
    unsigned char band;
    unsigned char rssilevel;
    uint16_t freq;
    unsigned char F_GoodStation;
    unsigned char Smeter;
    int reserve[4];
}
struct sqlfm_tune_parm {
    uint8_t err;
    uint8_t band;
    uint8_t space;
    uint8_t setfreqmode;
    uint16_t freq;
}
struct static_key {
    atomic_t enabled;
}
struct super_block {
    struct list_head s_list;
    dev_t s_dev;
    unsigned char s_blocksize_bits;
    unsigned long s_blocksize;
    loff_t s_maxbytes;
    struct file_system_type *s_type;
    const struct super_operations *s_op;
    const struct dquot_operations *dq_op;
    const struct quotactl_ops *s_qcop;
    const struct export_operations *s_export_op;
    unsigned long s_flags;
    unsigned long s_iflags;
    unsigned long s_magic;
    struct dentry *s_root;
    struct rw_semaphore s_umount;
    int s_count;
    atomic_t s_active;
    void *s_security;
    const struct xattr_handler **s_xattr;
    const struct fscrypt_operations *s_cop;
    struct key *s_master_keys;
    struct hlist_bl_head s_anon;
    struct list_head s_mounts;
    struct block_device *s_bdev;
    struct backing_dev_info *s_bdi;
    struct mtd_info *s_mtd;
    struct hlist_node s_instances;
    unsigned int s_quota_types;
    struct quota_info s_dquot;
    struct sb_writers s_writers;
    char s_id[32];
    uuid_t s_uuid;
    void *s_fs_info;
    unsigned int s_max_links;
    fmode_t s_mode;
    u32 s_time_gran;
    struct mutex s_vfs_rename_mutex;
    char *s_subtype;
    const struct dentry_operations *s_d_op;
    int cleancache_poolid;
    struct shrinker s_shrink;
    atomic_long_t s_remove_count;
    int s_readonly_remount;
    struct workqueue_struct *s_dio_done_wq;
    struct hlist_head s_pins;
    struct user_namespace *s_user_ns;
    struct list_lru s_dentry_lru;
    struct list_lru s_inode_lru;
    struct callback_head rcu;
    struct work_struct destroy_work;
    struct mutex s_sync_lock;
    int s_stack_depth;
    spinlock_t s_inode_list_lock;
    struct list_head s_inodes;
    spinlock_t s_inode_wblist_lock;
    struct list_head s_inodes_wb;
}
struct super_operations {
    struct inode *(*alloc_inode)(struct super_block *);
    void (*destroy_inode)(struct inode *);
    void (*dirty_inode)(struct inode *, int);
    int (*write_inode)(struct inode *, struct writeback_control *);
    int (*drop_inode)(struct inode *);
    void (*evict_inode)(struct inode *);
    void (*put_super)(struct super_block *);
    int (*sync_fs)(struct super_block *, int);
    int (*freeze_super)(struct super_block *);
    int (*freeze_fs)(struct super_block *);
    int (*thaw_super)(struct super_block *);
    int (*unfreeze_fs)(struct super_block *);
    int (*statfs)(struct dentry *, struct kstatfs *);
    int (*remount_fs)(struct super_block *, int *, char *);
    int (*remount_fs2)(struct vfsmount *, struct super_block *, int *, char *);
    void *(*clone_mnt_data)(void *);
    void (*copy_mnt_data)(void *, void *);
    void (*umount_begin)(struct super_block *);
    int (*show_options)(struct seq_file *, struct dentry *);
    int (*show_options2)(struct vfsmount *, struct seq_file *, struct dentry *);
    int (*show_devname)(struct seq_file *, struct dentry *);
    int (*show_path)(struct seq_file *, struct dentry *);
    int (*show_stats)(struct seq_file *, struct dentry *);
    ssize_t (*quota_read)(struct super_block *, int, char *, size_t, loff_t);
    ssize_t (*quota_write)(struct super_block *, int, const char *, size_t, loff_t);
    struct dquot **(*get_dquots)(struct inode *);
    int (*bdev_try_to_free_page)(struct super_block *, struct page *, gfp_t);
    long (*nr_cached_objects)(struct super_block *, struct shrink_control *);
    long (*free_cached_objects)(struct super_block *, struct shrink_control *);
}
struct sysfs_ops {
    ssize_t (*show)(struct kobject *, struct attribute *, char *);
    ssize_t (*store)(struct kobject *, struct attribute *, const char *, size_t);
}
struct ta_event {
    int val;
    const char *name;
}
struct task_cputime {
    u64 utime;
    u64 stime;
    unsigned long long sum_exec_runtime;
}
struct task_cputime_atomic {
    atomic64_t utime;
    atomic64_t stime;
    atomic64_t sum_exec_runtime;
}
struct task_io_accounting {
    u64 rchar;
    u64 wchar;
    u64 syscr;
    u64 syscw;
    u64 syscfs;
    u64 read_bytes;
    u64 write_bytes;
    u64 cancelled_write_bytes;
}
struct task_rss_stat {
    int events;
    int count[4];
}
struct task_struct {
    struct thread_info thread_info;
    volatile long state;
    void *stack;
    atomic_t usage;
    unsigned int flags;
    unsigned int ptrace;
    struct llist_node wake_entry;
    int on_cpu;
    unsigned int cpu;
    unsigned int wakee_flips;
    unsigned long wakee_flip_decay_ts;
    struct task_struct *last_wakee;
    int wake_cpu;
    int on_rq;
    int prio;
    int static_prio;
    int normal_prio;
    unsigned int rt_priority;
    const struct sched_class *sched_class;
    struct sched_entity se;
    struct sched_rt_entity rt;
    struct ravg ravg;
    u32 init_load_pct;
    u64 last_sleep_ts;
    struct task_group *sched_task_group;
    struct sched_dl_entity dl;
    unsigned int policy;
    int nr_cpus_allowed;
    cpumask_t cpus_allowed;
    int rcu_read_lock_nesting;
    union rcu_special rcu_read_unlock_special;
    struct list_head rcu_node_entry;
    struct rcu_node *rcu_blocked_node;
    unsigned long rcu_tasks_nvcsw;
    u8 rcu_tasks_holdout;
    u8 rcu_tasks_idx;
    int rcu_tasks_idle_cpu;
    struct list_head rcu_tasks_holdout_list;
    struct sched_info sched_info;
    struct list_head tasks;
    struct plist_node pushable_tasks;
    struct rb_node pushable_dl_tasks;
    struct mm_struct *mm;
    struct mm_struct *active_mm;
    struct vmacache vmacache;
    struct task_rss_stat rss_stat;
    int exit_state;
    int exit_code;
    int exit_signal;
    int pdeath_signal;
    unsigned long jobctl;
    unsigned int personality;
    unsigned int sched_reset_on_fork : 1;
    unsigned int sched_contributes_to_load : 1;
    unsigned int sched_migrated : 1;
    unsigned int sched_remote_wakeup : 1;
    unsigned int sched_psi_wake_requeue : 1;
    unsigned int in_execve : 1;
    unsigned int in_iowait : 1;
    unsigned int memcg_may_oom : 1;
    unsigned int memcg_kmem_skip_account : 1;
    unsigned int no_cgroup_migration : 1;
    unsigned long atomic_flags;
    struct restart_block restart_block;
    pid_t pid;
    pid_t tgid;
    unsigned long stack_canary;
    struct task_struct *real_parent;
    struct task_struct *parent;
    struct list_head children;
    struct list_head sibling;
    struct task_struct *group_leader;
    struct list_head ptraced;
    struct list_head ptrace_entry;
    struct pid_link pids[3];
    struct list_head thread_group;
    struct list_head thread_node;
    struct completion *vfork_done;
    int *set_child_tid;
    int *clear_child_tid;
    u64 utime;
    u64 stime;
    u64 gtime;
    u64 *time_in_state;
    unsigned int max_state;
    struct prev_cputime prev_cputime;
    unsigned long nvcsw;
    unsigned long nivcsw;
    u64 start_time;
    u64 real_start_time;
    unsigned long min_flt;
    unsigned long maj_flt;
    struct task_cputime cputime_expires;
    struct list_head cpu_timers[3];
    const struct cred *ptracer_cred;
    const struct cred *real_cred;
    const struct cred *cred;
    char comm[16];
    struct nameidata *nameidata;
    struct fs_struct *fs;
    struct files_struct *files;
    struct nsproxy *nsproxy;
    struct signal_struct *signal;
    struct sighand_struct *sighand;
    sigset_t blocked;
    sigset_t real_blocked;
    sigset_t saved_sigmask;
    struct sigpending pending;
    unsigned long sas_ss_sp;
    size_t sas_ss_size;
    unsigned int sas_ss_flags;
    struct callback_head *task_works;
    struct audit_context *audit_context;
    kuid_t loginuid;
    unsigned int sessionid;
    struct seccomp seccomp;
    u32 parent_exec_id;
    u32 self_exec_id;
    spinlock_t alloc_lock;
    raw_spinlock_t pi_lock;
    struct wake_q_node wake_q;
    struct rb_root_cached pi_waiters;
    struct task_struct *pi_top_task;
    struct rt_mutex_waiter *pi_blocked_on;
    void *journal_info;
    struct bio_list *bio_list;
    struct blk_plug *plug;
    struct reclaim_state *reclaim_state;
    struct backing_dev_info *backing_dev_info;
    struct io_context *io_context;
    unsigned long ptrace_message;
    siginfo_t *last_siginfo;
    struct task_io_accounting ioac;
    unsigned int psi_flags;
    u64 acct_rss_mem1;
    u64 acct_vm_mem1;
    u64 acct_timexpd;
    nodemask_t mems_allowed;
    seqcount_t mems_allowed_seq;
    int cpuset_mem_spread_rotor;
    int cpuset_slab_spread_rotor;
    struct css_set *cgroups;
    struct list_head cg_list;
    struct robust_list_head *robust_list;
    struct compat_robust_list_head *compat_robust_list;
    struct list_head pi_state_list;
    struct futex_pi_state *pi_state_cache;
    struct mutex futex_exit_mutex;
    unsigned int futex_state;
    struct perf_event_context *perf_event_ctxp[2];
    struct mutex perf_event_mutex;
    struct list_head perf_event_list;
    struct tlbflush_unmap_batch tlb_ubc;
    struct callback_head rcu;
    struct pipe_inode_info *splice_pipe;
    struct page_frag task_frag;
    int nr_dirtied;
    int nr_dirtied_pause;
    unsigned long dirty_paused_when;
    u64 timer_slack_ns;
    u64 default_timer_slack_ns;
    unsigned long trace;
    unsigned long trace_recursion;
    struct mem_cgroup *memcg_in_oom;
    gfp_t memcg_oom_gfp_mask;
    int memcg_oom_order;
    unsigned int memcg_nr_pages_over_high;
    int pagefault_disabled;
    struct task_struct *oom_reaper_list;
    struct vm_struct *stack_vm_area;
    atomic_t stack_refcount;
    void *security;
    struct thread_struct thread;
}
struct thread_group_cputimer {
    struct task_cputime_atomic cputime_atomic;
    bool running;
    bool checking_timer;
}
struct thread_info {
    unsigned long flags;
    mm_segment_t addr_limit;
    int preempt_count;
}
struct thread_struct {
    struct cpu_context cpu_context;
    unsigned long tp_value;
    unsigned long tp2_value;
    struct fpsimd_state fpsimd_state;
    unsigned long fault_address;
    unsigned long fault_code;
    struct debug_info debug;
}
struct timer_list {
    struct hlist_node entry;
    unsigned long expires;
    void (*function)(unsigned long);
    unsigned long data;
    u32 flags;
}
struct timerqueue_head {
    struct rb_root head;
    struct timerqueue_node *next;
}
struct timerqueue_node {
    struct rb_node node;
    ktime_t expires;
}
struct timespec {
    __kernel_time_t tv_sec;
    long tv_nsec;
}
struct tlbflush_unmap_batch {
    <no data fields>
}
struct tracepoint {
    const char *name;
    struct static_key key;
    int (*regfunc)(void);
    void (*unregfunc)(void);
    struct tracepoint_func *funcs;
}
struct tracepoint_func {
    void *func;
    void *data;
    int prio;
}
struct upid {
    int nr;
    struct pid_namespace *ns;
    struct hlist_node pid_chain;
}
struct uprobes_state {
    <no data fields>
}
struct user_fpsimd_state {
    __uint128_t vregs[32];
    __u32 fpsr;
    __u32 fpcr;
    __u32 __reserved[2];
}
struct user_struct {
    atomic_t __count;
    atomic_t processes;
    atomic_t sigpending;
    atomic_t fanotify_listeners;
    atomic_long_t epoll_watches;
    unsigned long locked_shm;
    unsigned long unix_inflight;
    atomic_long_t pipe_bufs;
    struct key *uid_keyring;
    struct key *session_keyring;
    struct hlist_node uidhash_node;
    kuid_t uid;
    atomic_long_t locked_vm;
}
struct util_est {
    unsigned int enqueued;
    unsigned int ewma;
}
struct v4l2_rds_data {
    __u8 lsb;
    __u8 msb;
    __u8 block;
}
struct vm_area_struct {
    unsigned long vm_start;
    unsigned long vm_end;
    struct vm_area_struct *vm_next;
    struct vm_area_struct *vm_prev;
    struct rb_node vm_rb;
    unsigned long rb_subtree_gap;
    struct mm_struct *vm_mm;
    pgprot_t vm_page_prot;
    unsigned long vm_flags;
    union {
        struct {...} shared;
        const char *anon_name;
    };
    struct list_head anon_vma_chain;
    struct anon_vma *anon_vma;
    const struct vm_operations_struct *vm_ops;
    unsigned long vm_pgoff;
    struct file *vm_file;
    void *vm_private_data;
    atomic_long_t swap_readahead_info;
    struct vm_userfaultfd_ctx vm_userfaultfd_ctx;
}
struct vm_fault {
    struct vm_area_struct *vma;
    unsigned int flags;
    gfp_t gfp_mask;
    unsigned long pgoff;
    unsigned long address;
    pmd_t *pmd;
    pud_t *pud;
    pte_t orig_pte;
    struct page *cow_page;
    struct mem_cgroup *memcg;
    struct page *page;
    pte_t *pte;
    spinlock_t *ptl;
    pgtable_t prealloc_pte;
}
struct vm_operations_struct {
    void (*open)(struct vm_area_struct *);
    void (*close)(struct vm_area_struct *);
    int (*split)(struct vm_area_struct *, unsigned long);
    int (*mremap)(struct vm_area_struct *);
    int (*fault)(struct vm_fault *);
    int (*huge_fault)(struct vm_fault *, enum page_entry_size);
    void (*map_pages)(struct vm_fault *, unsigned long, unsigned long);
    int (*page_mkwrite)(struct vm_fault *);
    int (*pfn_mkwrite)(struct vm_fault *);
    int (*access)(struct vm_area_struct *, unsigned long, void *, int, int);
    const char *(*name)(struct vm_area_struct *);
    struct page *(*find_special_page)(struct vm_area_struct *, unsigned long);
}
struct vm_struct {
    struct vm_struct *next;
    void *addr;
    unsigned long size;
    unsigned long flags;
    struct page **pages;
    unsigned int nr_pages;
    phys_addr_t phys_addr;
    const void *caller;
}
struct vm_userfaultfd_ctx {
    <no data fields>
}
struct vmacache {
    u64 seqnum;
    struct vm_area_struct *vmas[4];
}
struct vmem_altmap {
    const unsigned long base_pfn;
    const unsigned long reserve;
    unsigned long free;
    unsigned long align;
    unsigned long alloc;
}
struct wait_queue_entry {
    unsigned int flags;
    void *private;
    wait_queue_func_t func;
    struct list_head entry;
}
struct wait_queue_head {
    spinlock_t lock;
    struct list_head head;
}
struct wake_q_node {
    struct wake_q_node *next;
}
struct wakeup_source {
    const char *name;
    struct list_head entry;
    spinlock_t lock;
    struct wake_irq *wakeirq;
    struct timer_list timer;
    unsigned long timer_expires;
    ktime_t total_time;
    ktime_t max_time;
    ktime_t last_time;
    ktime_t start_prevent_time;
    ktime_t prevent_sleep_time;
    unsigned long event_count;
    unsigned long active_count;
    unsigned long relax_count;
    unsigned long expire_count;
    unsigned long wakeup_count;
    bool active : 1;
    bool autosleep_enabled : 1;
}
struct work_struct {
    atomic_long_t data;
    struct list_head entry;
    work_func_t func;
};

/* ---- extern kernel API (from undefined symbols) ---- */
/* recovered automatically; see extern_symbols.txt */

/* ---- recovered function skeletons ---- */
/* L1789: unsigned int Ls8035AfSetFreq(unsigned int) */
__maybe_unused unsigned int Ls8035AfSetFreq(unsigned int)
{
	return 0;
}

/* L334: void QND_Delay(UINT16) */
__maybe_unused void QND_Delay(UINT16)
{
	return;
}

/* L1783: unsigned int QND_FREQ2CHREG(unsigned int) */
__maybe_unused unsigned int QND_FREQ2CHREG(unsigned int)
{
	return 0;
}

/* L347: UINT8 QND_GetRSSI(UINT16) */
__maybe_unused UINT8 QND_GetRSSI(UINT16)
{
	return 0;
}

/* L486: UINT8 QND_Init(void) */
__maybe_unused UINT8 QND_Init(void)
{
	return 0;
}

/* L492: void QND_Init_8_6m(void) */
__maybe_unused void QND_Init_8_6m(void)
{
	return;
}

/* L1263: UINT8 QND_RDSCheckBufferReady(void) */
__maybe_unused UINT8 QND_RDSCheckBufferReady(void)
{
	return 0;
}

/* L1214: UINT8 QND_RDSDetectSignal(void) */
__maybe_unused UINT8 QND_RDSDetectSignal(void)
{
	return 0;
}

/* L1137: UINT8 QND_RDSEnable(UINT8) */
__maybe_unused UINT8 QND_RDSEnable(UINT8)
{
	return 0;
}

/* L1168: void QND_RDSHighSpeedEnable(UINT8) */
__maybe_unused void QND_RDSHighSpeedEnable(UINT8)
{
	return;
}

/* L1237: void QND_RDSLoadData(UINT8 *, UINT8) */
__maybe_unused void QND_RDSLoadData(UINT8 *, UINT8)
{
	return;
}

/* L1185: INT8 QND_RDSModeDetect(void) */
__maybe_unused INT8 QND_RDSModeDetect(void)
{
	return 0;
}

/* L1084: void QND_RXConfigAudio(UINT8, UINT8) */
__maybe_unused void QND_RXConfigAudio(UINT8, UINT8)
{
	return;
}

/* L900: INT16 QND_RXSeekCH(UINT16, UINT16, UINT8, UINT8, UINT8) */
__maybe_unused INT16 QND_RXSeekCH(UINT16, UINT16, UINT8, UINT8, UINT8)
{
	return 0;
}

/* L1018: UINT8 QND_RXSeekCHAll(UINT16, UINT16, UINT8, UINT8, UINT8) */
__maybe_unused UINT8 QND_RXSeekCHAll(UINT16, UINT16, UINT8, UINT8, UINT8)
{
	return 0;
}

/* L776: void QND_RXSetTH(UINT8) */
__maybe_unused void QND_RXSetTH(UINT8)
{
	return;
}

/* L832: INT8 QND_RXValidCH(UINT16, UINT8) */
__maybe_unused INT8 QND_RXValidCH(UINT16, UINT8)
{
	return 0;
}

/* L37: unsigned char QND_ReadReg(unsigned char) */
__maybe_unused unsigned char QND_ReadReg(unsigned char)
{
	return 0;
}

/* L727: void QND_SetCountry(UINT8) */
__maybe_unused void QND_SetCountry(UINT8)
{
	return;
}

/* L593: void QND_SetSysMode(UINT16) */
__maybe_unused void QND_SetSysMode(UINT16)
{
	return;
}

/* L641: void QND_TuneToCH(UINT16) */
__maybe_unused void QND_TuneToCH(UINT16)
{
	return;
}

/* L47: void QND_WriteReg(unsigned char, unsigned char) */
__maybe_unused void QND_WriteReg(unsigned char, unsigned char)
{
	return;
}

/* L299: void QNF_ConfigScan(UINT16, UINT16, UINT8) */
__maybe_unused void QNF_ConfigScan(UINT16, UINT16, UINT8)
{
	return;
}

/* L175: UINT16 QNF_GetCh(void) */
__maybe_unused UINT16 QNF_GetCh(void)
{
	return 0;
}

/* L86: void QNF_RXInit(void) */
__maybe_unused void QNF_RXInit(void)
{
	return;
}

/* L199: void QNF_SetCh(UINT16) */
__maybe_unused void QNF_SetCh(UINT16)
{
	return;
}

/* L233: void QNF_SetChN(unsigned int, unsigned int, unsigned char) */
__maybe_unused void QNF_SetChN(unsigned int, unsigned int, unsigned char)
{
	return;
}

/* L111: void QNF_SetMute(UINT8) */
__maybe_unused void QNF_SetMute(UINT8)
{
	return;
}

/* L149: void QNF_SetRegBit(UINT8, UINT8, UINT8) */
__maybe_unused void QNF_SetRegBit(UINT8, UINT8, UINT8)
{
	return;
}

/* L390: void QN_ChipInitialization(void) */
__maybe_unused void QN_ChipInitialization(void)
{
	return;
}

/* L1301: unsigned char Radio8035_GetCHSC(void) */
__maybe_unused unsigned char Radio8035_GetCHSC(void)
{
	return 0;
}

/* L1292: unsigned char Radio8035_GetLevel(void) */
__maybe_unused unsigned char Radio8035_GetLevel(void)
{
	return 0;
}

/* L1305: unsigned char Radio8035_GetRXCCA(void) */
__maybe_unused unsigned char Radio8035_GetRXCCA(void)
{
	return 0;
}

/* L1682: unsigned char Radio8035_GetResetStatue(void) */
__maybe_unused unsigned char Radio8035_GetResetStatue(void)
{
	return 0;
}

/* L1297: unsigned char Radio8035_GetSNR(void) */
__maybe_unused unsigned char Radio8035_GetSNR(void)
{
	return 0;
}

/* L1315: void RadioInit_8035(int) */
__maybe_unused void RadioInit_8035(int)
{
	return;
}

/* L1345: void RadioInit_8035fixerror(int) */
__maybe_unused void RadioInit_8035fixerror(int)
{
	return;
}

/* L1334: void RadioInit_8035new(int) */
__maybe_unused void RadioInit_8035new(int)
{
	return;
}

/* L1746: void RadioReset(void) */
__maybe_unused void RadioReset(void)
{
	return;
}

/* L1354: unsigned char RadioSetFreq(unsigned int) */
__maybe_unused unsigned char RadioSetFreq(unsigned int)
{
	return 0;
}

/* L1310: unsigned char SQLQNM_GetMonoMode(void) */
__maybe_unused unsigned char SQLQNM_GetMonoMode(void)
{
	return 0;
}

/* L25: unsigned short Safe_GetCh(void) */
__maybe_unused unsigned short Safe_GetCh(void)
{
	return 0;
}

/* L5: unsigned char Safe_ReadReg(unsigned char) */
__maybe_unused unsigned char Safe_ReadReg(unsigned char)
{
	return 0;
}

/* L1911: void dumpRegs(void) */
__maybe_unused void dumpRegs(void)
{
	return;
}

/* L1606: int isRadio8035GetResetStatueOK(void) */
__maybe_unused int isRadio8035GetResetStatueOK(void)
{
	return 0;
}

/* L337: void si475x_abortseeking(void) */
__maybe_unused void si475x_abortseeking(void)
{
	return;
}

/* L332: uint8_t si475x_am_autoseek(seek_process_callback, seek_found_callback) */
__maybe_unused uint8_t si475x_am_autoseek(seek_process_callback, seek_found_callback)
{
	return 0;
}

/* L57: uint16_t si475x_am_get_frequency(void) */
__maybe_unused uint16_t si475x_am_get_frequency(void)
{
	return 0;
}

/* L327: uint8_t si475x_am_seek(uint8_t, uint8_t, seek_process_callback) */
__maybe_unused uint8_t si475x_am_seek(uint8_t, uint8_t, seek_process_callback)
{
	return 0;
}

/* L308: void si475x_am_tune(uint16_t) */
__maybe_unused void si475x_am_tune(uint16_t)
{
	return;
}

/* L283: void si475x_bandswitch(uint8_t) */
__maybe_unused void si475x_bandswitch(uint8_t)
{
	return;
}

/* L31: void si475x_command(uint8_t, uint8_t *, uint8_t, uint8_t *) */
__maybe_unused void si475x_command(uint8_t, uint8_t *, uint8_t, uint8_t *)
{
	return;
}

/* L321: uint8_t si475x_fm_autoseek(seek_process_callback, seek_found_callback) */
__maybe_unused uint8_t si475x_fm_autoseek(seek_process_callback, seek_found_callback)
{
	return 0;
}

/* L52: uint16_t si475x_fm_get_frequency(void) */
__maybe_unused uint16_t si475x_fm_get_frequency(void)
{
	return 0;
}

/* L314: uint8_t si475x_fm_seek(uint8_t, uint8_t, seek_process_callback) */
__maybe_unused uint8_t si475x_fm_seek(uint8_t, uint8_t, seek_process_callback)
{
	return 0;
}

/* L299: void si475x_fm_tune(uint8_t, uint16_t) */
__maybe_unused void si475x_fm_tune(uint8_t, uint16_t)
{
	return;
}

/* L68: void si475x_mute(uint8_t) */
__maybe_unused void si475x_mute(uint8_t)
{
	return;
}

/* L278: void si475x_powerdown(void) */
__maybe_unused void si475x_powerdown(void)
{
	return;
}

/* L271: void si475x_powerup(uint8_t) */
__maybe_unused void si475x_powerup(uint8_t)
{
	return;
}

/* L73: void si475x_powerup_without_reset(uint8_t) */
__maybe_unused void si475x_powerup_without_reset(uint8_t)
{
	return;
}

/* L36: void si475x_set_property(uint16_t, uint16_t) */
__maybe_unused void si475x_set_property(uint16_t, uint16_t)
{
	return;
}

/* L62: void si475x_set_volume(uint8_t) */
__maybe_unused void si475x_set_volume(uint8_t)
{
	return;
}

/* L25: void si475x_some_init(void) */
__maybe_unused void si475x_some_init(void)
{
	return;
}

/* L58: int8_t si475x_am_get_RSSI(void) */
__maybe_unused int8_t si475x_am_get_RSSI(void)
{
	return 0;
}

/* L62: int8_t si475x_am_get_SNR(void) */
__maybe_unused int8_t si475x_am_get_SNR(void)
{
	return 0;
}

/* L67: int8_t si475x_am_get_valid(void) */
__maybe_unused int8_t si475x_am_get_valid(void)
{
	return 0;
}

/* L24: int8_t si475x_fm_get_RSSI(void) */
__maybe_unused int8_t si475x_fm_get_RSSI(void)
{
	return 0;
}

/* L28: int8_t si475x_fm_get_SNR(void) */
__maybe_unused int8_t si475x_fm_get_SNR(void)
{
	return 0;
}

/* L38: uint8_t si475x_fm_get_blend(void) */
__maybe_unused uint8_t si475x_fm_get_blend(void)
{
	return 0;
}

/* L33: int8_t si475x_fm_get_valid(void) */
__maybe_unused int8_t si475x_fm_get_valid(void)
{
	return 0;
}

/* L72: uint8_t si475x_get_DieTemp(void) */
__maybe_unused uint8_t si475x_get_DieTemp(void)
{
	return 0;
}

/* L48: void si475x_get_FuncInfo(void) */
__maybe_unused void si475x_get_FuncInfo(void)
{
	return;
}

/* L53: void si475x_get_PartInfo(void) */
__maybe_unused void si475x_get_PartInfo(void)
{
	return;
}

/* L43: uint8_t si475x_get_space(void) */
__maybe_unused uint8_t si475x_get_space(void)
{
	return 0;
}

/* L818: int RDSFetchBlockDataSi475x(unsigned short *, unsigned short *, unsigned short *, unsigned short *) */
__maybe_unused int RDSFetchBlockDataSi475x(unsigned short *, unsigned short *, unsigned short *, unsigned short *)
{
	return 0;
}

/* L712: uint16_t rds_af_check(void) */
__maybe_unused uint16_t rds_af_check(void)
{
	return 0;
}

/* L775: uint8_t rds_af_tune(uint16_t) */
__maybe_unused uint8_t rds_af_tune(uint16_t)
{
	return 0;
}

/* L497: void rds_process(void) */
__maybe_unused void rds_process(void)
{
	return;
}

/* L609: uint8_t rds_ps_available(void) */
__maybe_unused uint8_t rds_ps_available(void)
{
	return 0;
}

/* L619: uint8_t *rds_ps_data(void) */
__maybe_unused uint8_t *rds_ps_data(void)
{
	return 0;
}

/* L600: void rds_reset(void) */
__maybe_unused void rds_reset(void)
{
	return;
}

/* L614: uint8_t rds_rt_available(void) */
__maybe_unused uint8_t rds_rt_available(void)
{
	return 0;
}

/* L625: uint8_t *rds_rt_data(void) */
__maybe_unused uint8_t *rds_rt_data(void)
{
	return 0;
}

/* L294: static void display_rt(void) */
static void display_rt(void);
static void display_rt(void)
{
	return;
}

/* L46: static void get_rds_status(rds_status_t *) */
static void get_rds_status(rds_status_t *);
static void get_rds_status(rds_status_t *)
{
	return;
}

/* L202: static void update_ps(uint8_t, uint8_t) */
static void update_ps(uint8_t, uint8_t);
static void update_ps(uint8_t, uint8_t)
{
	return;
}

/* L348: static void update_rt_advance(uint8_t, uint8_t, uint8_t, uint8_t *) */
static void update_rt_advance(uint8_t, uint8_t, uint8_t, uint8_t *);
static void update_rt_advance(uint8_t, uint8_t, uint8_t, uint8_t *)
{
	return;
}

/* L43: void si475x6x_af_rsq(uint16_t, tuner_metrics_t *) */
__maybe_unused void si475x6x_af_rsq(uint16_t, tuner_metrics_t *)
{
	return;
}

/* L24: void si475x6x_rds_status(uint8_t, uint8_t, uint8_t) */
__maybe_unused void si475x6x_rds_status(uint8_t, uint8_t, uint8_t)
{
	return;
}

/* L25: int Issi475x6x_Ready(void) */
__maybe_unused int Issi475x6x_Ready(void)
{
	return 0;
}

/* L322: void dump_PartInfo(void) */
__maybe_unused void dump_PartInfo(void)
{
	return;
}

/* L407: int si475x6x_CheckCTSAndErr(void) */
__maybe_unused int si475x6x_CheckCTSAndErr(void)
{
	return 0;
}

/* L360: int8_t si475x6x_am_get_RSSI(void) */
__maybe_unused int8_t si475x6x_am_get_RSSI(void)
{
	return 0;
}

/* L364: int8_t si475x6x_am_get_SNR(void) */
__maybe_unused int8_t si475x6x_am_get_SNR(void)
{
	return 0;
}

/* L166: uint16_t si475x6x_am_get_frequency(void) */
__maybe_unused uint16_t si475x6x_am_get_frequency(void)
{
	return 0;
}

/* L369: int8_t si475x6x_am_get_valid(void) */
__maybe_unused int8_t si475x6x_am_get_valid(void)
{
	return 0;
}

/* L118: void si475x6x_am_rsq_status(uint8_t, uint8_t, uint8_t, tuner_metrics_t *) */
__maybe_unused void si475x6x_am_rsq_status(uint8_t, uint8_t, uint8_t, tuner_metrics_t *)
{
	return;
}

/* L50: void si475x6x_command(uint8_t, uint8_t *, uint8_t, uint8_t *) */
__maybe_unused void si475x6x_command(uint8_t, uint8_t *, uint8_t, uint8_t *)
{
	return;
}

/* L151: int si475x6x_fm_get_Quality(unsigned char *, unsigned char *, unsigned char *, unsigned char *) */
__maybe_unused int si475x6x_fm_get_Quality(unsigned char *, unsigned char *, unsigned char *, unsigned char *)
{
	return 0;
}

/* L249: int8_t si475x6x_fm_get_RSSI(void) */
__maybe_unused int8_t si475x6x_fm_get_RSSI(void)
{
	return 0;
}

/* L253: int8_t si475x6x_fm_get_SNR(void) */
__maybe_unused int8_t si475x6x_fm_get_SNR(void)
{
	return 0;
}

/* L265: uint8_t si475x6x_fm_get_blend(void) */
__maybe_unused uint8_t si475x6x_fm_get_blend(void)
{
	return 0;
}

/* L142: uint16_t si475x6x_fm_get_frequency(void) */
__maybe_unused uint16_t si475x6x_fm_get_frequency(void)
{
	return 0;
}

/* L258: int8_t si475x6x_fm_get_valid(void) */
__maybe_unused int8_t si475x6x_fm_get_valid(void)
{
	return 0;
}

/* L93: void si475x6x_fm_rsq_status(uint8_t, uint8_t, uint8_t, tuner_metrics_t *) */
__maybe_unused void si475x6x_fm_rsq_status(uint8_t, uint8_t, uint8_t, tuner_metrics_t *)
{
	return;
}

/* L376: uint8_t si475x6x_get_DieTemp(void) */
__maybe_unused uint8_t si475x6x_get_DieTemp(void)
{
	return 0;
}

/* L293: void si475x6x_get_FuncInfo(void) */
__maybe_unused void si475x6x_get_FuncInfo(void)
{
	return;
}

/* L305: void si475x6x_get_PartInfo(void) */
__maybe_unused void si475x6x_get_PartInfo(void)
{
	return;
}

/* L279: uint8_t si475x6x_get_space(void) */
__maybe_unused uint8_t si475x6x_get_space(void)
{
	return 0;
}

/* L193: void si475x6x_loadPatch(const uint8_t *, uint16_t) */
__maybe_unused void si475x6x_loadPatch(const uint8_t *, uint16_t)
{
	return;
}

/* L185: void si475x6x_mute(uint8_t) */
__maybe_unused void si475x6x_mute(uint8_t)
{
	return;
}

/* L209: void si475x6x_powerdown(void) */
__maybe_unused void si475x6x_powerdown(void)
{
	return;
}

/* L87: void si475x6x_set_chipAddress(uint8_t) */
__maybe_unused void si475x6x_set_chipAddress(uint8_t)
{
	return;
}

/* L67: void si475x6x_set_property(uint16_t, uint16_t) */
__maybe_unused void si475x6x_set_property(uint16_t, uint16_t)
{
	return;
}

/* L176: void si475x6x_set_volume(uint8_t) */
__maybe_unused void si475x6x_set_volume(uint8_t)
{
	return;
}

/* L37: static void si475x6x_waitForCTS(void) */
static void si475x6x_waitForCTS(void);
static void si475x6x_waitForCTS(void)
{
	return;
}

/* L39: int i2c_read(uint8_t *, uint8_t, uint8_t) */
__maybe_unused int i2c_read(uint8_t *, uint8_t, uint8_t)
{
	return 0;
}

/* L27: int i2c_write(uint8_t, uint8_t *, uint8_t) */
__maybe_unused int i2c_write(uint8_t, uint8_t *, uint8_t)
{
	return 0;
}

/* L94: void init_si475x6x_tuner(void) */
__maybe_unused void init_si475x6x_tuner(void)
{
	return;
}

/* L57: void sleep_ms(uint16_t) */
__maybe_unused void sleep_ms(uint16_t)
{
	return;
}

/* L51: void sleep_us(uint16_t) */
__maybe_unused void sleep_us(uint16_t)
{
	return;
}

/* L367: void si475x6x_abortseeking(void) */
__maybe_unused void si475x6x_abortseeking(void)
{
	return;
}

/* L319: uint8_t si475x6x_am_autoseek(_seek_process_callback, _seek_found_callback) */
__maybe_unused uint8_t si475x6x_am_autoseek(_seek_process_callback, _seek_found_callback)
{
	return 0;
}

/* L232: uint8_t si475x6x_am_seek(uint8_t, uint8_t, _seek_process_callback) */
__maybe_unused uint8_t si475x6x_am_seek(uint8_t, uint8_t, _seek_process_callback)
{
	return 0;
}

/* L416: uint8_t si475x6x_am_seekstatus(int8_t, unsigned char *) */
__maybe_unused uint8_t si475x6x_am_seekstatus(int8_t, unsigned char *)
{
	return 0;
}

/* L54: void si475x6x_am_tune(uint16_t) */
__maybe_unused void si475x6x_am_tune(uint16_t)
{
	return;
}

/* L169: uint8_t si475x6x_fm_autoseek(_seek_process_callback, _seek_found_callback) */
__maybe_unused uint8_t si475x6x_fm_autoseek(_seek_process_callback, _seek_found_callback)
{
	return 0;
}

/* L88: uint8_t si475x6x_fm_seek(uint8_t, uint8_t, _seek_process_callback) */
__maybe_unused uint8_t si475x6x_fm_seek(uint8_t, uint8_t, _seek_process_callback)
{
	return 0;
}

/* L373: uint8_t si475x6x_fm_seekstatus(int8_t, unsigned char *) */
__maybe_unused uint8_t si475x6x_fm_seekstatus(int8_t, unsigned char *)
{
	return 0;
}

/* L41: void si475x6x_fm_tune(uint8_t, uint16_t) */
__maybe_unused void si475x6x_fm_tune(uint8_t, uint16_t)
{
	return;
}

/* L210: static uint8_t si475x6x_am_validate(uint16_t) */
static uint8_t si475x6x_am_validate(uint16_t);
static uint8_t si475x6x_am_validate(uint16_t)
{
	return 0;
}

/* L64: static uint8_t si475x6x_fm_validate(uint16_t) */
static uint8_t si475x6x_fm_validate(uint16_t);
static uint8_t si475x6x_fm_validate(uint16_t)
{
	return 0;
}

/* L2257: void LSEC_TunerChangeBand(eTuner_Channel, U8, U32, U32, U32, U32) */
__maybe_unused void LSEC_TunerChangeBand(eTuner_Channel, U8, U32, U32, U32, U32)
{
	return;
}

/* L173: unsigned char RadioGetBandReq(void) */
__maybe_unused unsigned char RadioGetBandReq(void)
{
	return 0;
}

/* L123: void RadioGetMaxMinFreq(unsigned char, unsigned int *, unsigned int *, unsigned int *, unsigned char *) */
__maybe_unused void RadioGetMaxMinFreq(unsigned char, unsigned int *, unsigned int *, unsigned int *, unsigned char *)
{
	return;
}

/* L2732: void RadioRefreshFreq(unsigned long) */
__maybe_unused void RadioRefreshFreq(unsigned long)
{
	return;
}

/* L327: void Star_CmdProtocol_WR(U8, U8) */
__maybe_unused void Star_CmdProtocol_WR(U8, U8)
{
	return;
}

/* L979: void Star_Cmd_Tuner_AF_Check(eTuner_Channel, U32, U32) */
__maybe_unused void Star_Cmd_Tuner_AF_Check(eTuner_Channel, U32, U32)
{
	return;
}

/* L955: void Star_Cmd_Tuner_AF_End(eTuner_Channel, U32) */
__maybe_unused void Star_Cmd_Tuner_AF_End(eTuner_Channel, U32)
{
	return;
}

/* L908: void Star_Cmd_Tuner_AF_Start(eTuner_Channel, U32, U32) */
__maybe_unused void Star_Cmd_Tuner_AF_Start(eTuner_Channel, U32, U32)
{
	return;
}

/* L1013: void Star_Cmd_Tuner_AF_Switch(eTuner_Channel, U32) */
__maybe_unused void Star_Cmd_Tuner_AF_Switch(eTuner_Channel, U32)
{
	return;
}

/* L740: void Star_Cmd_Tuner_Audio_Mute(eMuteAction) */
__maybe_unused void Star_Cmd_Tuner_Audio_Mute(eMuteAction)
{
	return;
}

/* L805: void Star_Cmd_Tuner_BB_IF_On_Off(U8) */
__maybe_unused void Star_Cmd_Tuner_BB_IF_On_Off(U8)
{
	return;
}

/* L561: void Star_Cmd_Tuner_Change_Band(eTuner_Channel, eTuner_Mode, uTunerProcessFeature, U32, U32, U32) */
__maybe_unused void Star_Cmd_Tuner_Change_Band(eTuner_Channel, eTuner_Mode, uTunerProcessFeature, U32, U32, U32)
{
	return;
}

/* L1337: void Star_Cmd_Tuner_Conf_BB_SAI(U32, U32) */
__maybe_unused void Star_Cmd_Tuner_Conf_BB_SAI(U32, U32)
{
	return;
}

/* L1237: void Star_Cmd_Tuner_Conf_HD_Blend(U32, U32, U32, U32) */
__maybe_unused void Star_Cmd_Tuner_Conf_HD_Blend(U32, U32, U32, U32)
{
	return;
}

/* L1377: void Star_Cmd_Tuner_Conf_JESD204(U32, U32, U32, U32, U32, U32) */
__maybe_unused void Star_Cmd_Tuner_Conf_JESD204(U32, U32, U32, U32, U32, U32)
{
	return;
}

/* L761: void Star_Cmd_Tuner_FM_Stereo_Mode(eStereoMode) */
__maybe_unused void Star_Cmd_Tuner_FM_Stereo_Mode(eStereoMode)
{
	return;
}

/* L1040: void Star_Cmd_Tuner_Get_AF_Quality(eTuner_Channel) */
__maybe_unused void Star_Cmd_Tuner_Get_AF_Quality(eTuner_Channel)
{
	return;
}

/* L712: void Star_Cmd_Tuner_Get_Channel_Quality(U8, eTuner_Channel) */
__maybe_unused void Star_Cmd_Tuner_Get_Channel_Quality(U8, eTuner_Channel)
{
	return;
}

/* L684: void Star_Cmd_Tuner_Get_Reception_Quality(eTuner_Channel) */
__maybe_unused void Star_Cmd_Tuner_Get_Reception_Quality(eTuner_Channel)
{
	return;
}

/* L1154: void Star_Cmd_Tuner_Get_Seek_Status(eTuner_Channel) */
__maybe_unused void Star_Cmd_Tuner_Get_Seek_Status(eTuner_Channel)
{
	return;
}

/* L1464: void Star_Cmd_Tuner_Get_WSP_Status(void) */
__maybe_unused void Star_Cmd_Tuner_Get_WSP_Status(void)
{
	return;
}

/* L429: void Star_Cmd_Tuner_Ping(U32) */
__maybe_unused void Star_Cmd_Tuner_Ping(U32)
{
	return;
}

/* L884: void Star_Cmd_Tuner_RDSBuffer_Read(eTuner_Channel) */
__maybe_unused void Star_Cmd_Tuner_RDSBuffer_Read(eTuner_Channel)
{
	return;
}

/* L858: void Star_Cmd_Tuner_RDSBuffer_Set(eTuner_Channel, U32, U32) */
__maybe_unused void Star_Cmd_Tuner_RDSBuffer_Set(eTuner_Channel, U32, U32)
{
	return;
}

/* L451: void Star_Cmd_Tuner_Read(U32, U8) */
__maybe_unused void Star_Cmd_Tuner_Read(U32, U8)
{
	return;
}

/* L1128: void Star_Cmd_Tuner_Seek_End(eTuner_Channel, U32) */
__maybe_unused void Star_Cmd_Tuner_Seek_End(eTuner_Channel, U32)
{
	return;
}

/* L1083: void Star_Cmd_Tuner_Seek_Start(eTuner_Channel, U32, U32) */
__maybe_unused void Star_Cmd_Tuner_Seek_Start(eTuner_Channel, U32, U32)
{
	return;
}

/* L1286: void Star_Cmd_Tuner_Set_Audio_IF(U8, U32) */
__maybe_unused void Star_Cmd_Tuner_Set_Audio_IF(U8, U32)
{
	return;
}

/* L1307: void Star_Cmd_Tuner_Set_BB_IF(U32) */
__maybe_unused void Star_Cmd_Tuner_Set_BB_IF(U32)
{
	return;
}

/* L830: void Star_Cmd_Tuner_Set_BB_Proc(void) */
__maybe_unused void Star_Cmd_Tuner_Set_BB_Proc(void)
{
	return;
}

/* L1211: void Star_Cmd_Tuner_Set_Blend(U8) */
__maybe_unused void Star_Cmd_Tuner_Set_Blend(U8)
{
	return;
}

/* L1435: void Star_Cmd_Tuner_Set_DISS(eTuner_Channel, U32, U32) */
__maybe_unused void Star_Cmd_Tuner_Set_DISS(eTuner_Channel, U32, U32)
{
	return;
}

/* L660: void Star_Cmd_Tuner_Set_FM_Proc(U8) */
__maybe_unused void Star_Cmd_Tuner_Set_FM_Proc(U8)
{
	return;
}

/* L1181: void Star_Cmd_Tuner_Set_Seek_Threshold(eTuner_Channel, U8, U8, U8, U8, U8, U8, U8) */
__maybe_unused void Star_Cmd_Tuner_Set_Seek_Threshold(eTuner_Channel, U8, U8, U8, U8, U8, U8, U8)
{
	return;
}

/* L783: void Star_Cmd_Tuner_Set_VICS_Output(eTuner_Channel) */
__maybe_unused void Star_Cmd_Tuner_Set_VICS_Output(eTuner_Channel)
{
	return;
}

/* L621: void Star_Cmd_Tuner_Tune(eTuner_Channel, U32, U32, U32) */
__maybe_unused void Star_Cmd_Tuner_Tune(eTuner_Channel, U32, U32, U32)
{
	return;
}

/* L476: void Star_Cmd_Tuner_Write(U32, U32 *, U8) */
__maybe_unused void Star_Cmd_Tuner_Write(U32, U32 *, U8)
{
	return;
}

/* L1518: void Star_Download_BootCode(void) */
__maybe_unused void Star_Download_BootCode(void)
{
	return;
}

/* L1583: void Star_Download_CustomizedCoeffs(void) */
__maybe_unused void Star_Download_CustomizedCoeffs(void)
{
	return;
}

/* L1741: void Star_GetAverageQuality(U8) */
__maybe_unused void Star_GetAverageQuality(U8)
{
	return;
}

/* L1853: U8 Star_GetTunerBusyStatus(eTuner_Channel) */
__maybe_unused U8 Star_GetTunerBusyStatus(eTuner_Channel)
{
	return 0;
}

/* L1703: void Star_RDSReadTunerStatus(U8) */
__maybe_unused void Star_RDSReadTunerStatus(U8)
{
	return;
}

/* L283: void Star_Read(eTuner_Access_Mode, U8, U8 *, U8 *) */
__maybe_unused void Star_Read(eTuner_Access_Mode, U8, U8 *, U8 *)
{
	return;
}

/* L1649: void Star_ReadTunerStatus(U8) */
__maybe_unused void Star_ReadTunerStatus(U8)
{
	return;
}

/* L1830: void Star_StartAutoSeek(eTuner_Channel, U8, U8, U8, U32, U8) */
__maybe_unused void Star_StartAutoSeek(eTuner_Channel, U8, U8, U8, U32, U8)
{
	return;
}

/* L1803: void Star_StartManualSeek(eTuner_Channel, U8, U32) */
__maybe_unused void Star_StartManualSeek(eTuner_Channel, U8, U32)
{
	return;
}

/* L1635: void Star_VPA_Switch(U8) */
__maybe_unused void Star_VPA_Switch(U8)
{
	return;
}

/* L243: void Star_Write(eTuner_Access_Mode, U8, U8 *) */
__maybe_unused void Star_Write(eTuner_Access_Mode, U8, U8 *)
{
	return;
}

/* L1881: void Tuner10msTimer(void) */
__maybe_unused void Tuner10msTimer(void)
{
	return;
}

/* L2438: void TunerChangeBand(eTuner_Channel, U8) */
__maybe_unused void TunerChangeBand(eTuner_Channel, U8)
{
	return;
}

/* L3580: int TunerDSPStuckCheck(void) */
__maybe_unused int TunerDSPStuckCheck(void)
{
	return 0;
}

/* L1893: void TunerInit(void) */
__maybe_unused void TunerInit(void)
{
	return;
}

/* L2082: U8 TunerPreChecking(void) */
__maybe_unused U8 TunerPreChecking(void)
{
	return 0;
}

/* L1982: void TunerPreSetting(void) */
__maybe_unused void TunerPreSetting(void)
{
	return;
}

/* L3654: void TunerRDSBufferDisable(eTuner_Channel) */
__maybe_unused void TunerRDSBufferDisable(eTuner_Channel)
{
	return;
}

/* L3625: void TunerRDSBufferEnable(eTuner_Channel, U8) */
__maybe_unused void TunerRDSBufferEnable(eTuner_Channel, U8)
{
	return;
}

/* L3608: void TunerRDSBufferRead(eTuner_Channel) */
__maybe_unused void TunerRDSBufferRead(eTuner_Channel)
{
	return;
}

/* L3672: void TunerRDSBufferReset(eTuner_Channel) */
__maybe_unused void TunerRDSBufferReset(eTuner_Channel)
{
	return;
}

/* L2762: void TunerReadSeekStatus(eTuner_Channel, struct sqlfm_seek_parm *) */
__maybe_unused void TunerReadSeekStatus(eTuner_Channel, struct sqlfm_seek_parm *)
{
	return;
}

/* L1943: void TunerReset(void) */
__maybe_unused void TunerReset(void)
{
	return;
}

/* L2721: void TunerSeekContinue(eTuner_Channel) */
__maybe_unused void TunerSeekContinue(eTuner_Channel)
{
	return;
}

/* L2692: void TunerSeekOff(eTuner_Channel, U8) */
__maybe_unused void TunerSeekOff(eTuner_Channel, U8)
{
	return;
}

/* L2640: void TunerSeekOn(eTuner_Channel, long) */
__maybe_unused void TunerSeekOn(eTuner_Channel, long)
{
	return;
}

/* L2612: void TunerSetFreq(eTuner_Channel, U32) */
__maybe_unused void TunerSetFreq(eTuner_Channel, U32)
{
	return;
}

/* L2122: void TunerStartupSeq(void) */
__maybe_unused void TunerStartupSeq(void)
{
	return;
}

/* L3566: void TunerStatusUpdate(void) */
__maybe_unused void TunerStatusUpdate(void)
{
	return;
}

/* L1959: void TunerWaitReady(eTuner_Channel) */
__maybe_unused void TunerWaitReady(eTuner_Channel)
{
	return;
}

/* L221: static void Star_SetBuffer_CheckSum(U8) */
static void Star_SetBuffer_CheckSum(U8);
static void Star_SetBuffer_CheckSum(U8)
{
	return;
}

/* L2121: static void LSEC_TunerChangeBand(eTuner_Channel, U8, U32, U32, U32, U32) */
static void LSEC_TunerChangeBand(eTuner_Channel, U8, U32, U32, U32, U32);
static void LSEC_TunerChangeBand(eTuner_Channel, U8, U32, U32, U32, U32)
{
	return;
}

/* L134: static void RadioGetMaxMinFreq(unsigned char, unsigned int *, unsigned int *, unsigned int *, unsigned char *) */
static void RadioGetMaxMinFreq(unsigned char, unsigned int *, unsigned int *, unsigned int *, unsigned char *);
static void RadioGetMaxMinFreq(unsigned char, unsigned int *, unsigned int *, unsigned int *, unsigned char *)
{
	return;
}

/* L2594: static void RadioRefreshFreq(unsigned long) */
static void RadioRefreshFreq(unsigned long);
static void RadioRefreshFreq(unsigned long)
{
	return;
}

/* L338: static void Star_CmdProtocol_WR(U8, U8) */
static void Star_CmdProtocol_WR(U8, U8);
static void Star_CmdProtocol_WR(U8, U8)
{
	return;
}

/* L565: static void Star_Cmd_Tuner_Change_Band(eTuner_Channel, eTuner_Mode, uTunerProcessFeature, U32, U32, U32) */
static void Star_Cmd_Tuner_Change_Band(eTuner_Channel, eTuner_Mode, uTunerProcessFeature, U32, U32, U32);
static void Star_Cmd_Tuner_Change_Band(eTuner_Channel, eTuner_Mode, uTunerProcessFeature, U32, U32, U32)
{
	return;
}

/* L862: static void Star_Cmd_Tuner_RDSBuffer_Set(eTuner_Channel, U32, U32) */
static void Star_Cmd_Tuner_RDSBuffer_Set(eTuner_Channel, U32, U32);
static void Star_Cmd_Tuner_RDSBuffer_Set(eTuner_Channel, U32, U32)
{
	return;
}

/* L1087: static void Star_Cmd_Tuner_Seek_Start(eTuner_Channel, U32, U32) */
static void Star_Cmd_Tuner_Seek_Start(eTuner_Channel, U32, U32);
static void Star_Cmd_Tuner_Seek_Start(eTuner_Channel, U32, U32)
{
	return;
}

/* L294: static void Star_Read(eTuner_Access_Mode, U8, U8 *, U8 *) */
static void Star_Read(eTuner_Access_Mode, U8, U8 *, U8 *);
static void Star_Read(eTuner_Access_Mode, U8, U8 *, U8 *)
{
	return;
}

/* L1593: static void Star_ReadTunerStatus(U8) */
static void Star_ReadTunerStatus(U8);
static void Star_ReadTunerStatus(U8)
{
	return;
}

/* L232: static void Star_SetBuffer_CheckSum(U8) */
static void Star_SetBuffer_CheckSum(U8);
static void Star_SetBuffer_CheckSum(U8)
{
	return;
}

/* L3479: static void TunerRDSBufferDisable(eTuner_Channel) */
static void TunerRDSBufferDisable(eTuner_Channel);
static void TunerRDSBufferDisable(eTuner_Channel)
{
	return;
}

/* L3497: static void TunerRDSBufferReset(eTuner_Channel) */
static void TunerRDSBufferReset(eTuner_Channel);
static void TunerRDSBufferReset(eTuner_Channel)
{
	return;
}

/* L2555: static void TunerSeekOff(eTuner_Channel, U8) */
static void TunerSeekOff(eTuner_Channel, U8);
static void TunerSeekOff(eTuner_Channel, U8)
{
	return;
}

/* L2503: static void TunerSeekOn(eTuner_Channel, long) */
static void TunerSeekOn(eTuner_Channel, long);
static void TunerSeekOn(eTuner_Channel, long)
{
	return;
}

/* L2475: static void TunerSetFreq(eTuner_Channel, U32) */
static void TunerSetFreq(eTuner_Channel, U32);
static void TunerSetFreq(eTuner_Channel, U32)
{
	return;
}

/* L1906: static void TunerWaitReady(eTuner_Channel) */
static void TunerWaitReady(eTuner_Channel);
static void TunerWaitReady(eTuner_Channel)
{
	return;
}

/* L186: unsigned short GF35_freq_to_chan(unsigned short) */
__maybe_unused unsigned short GF35_freq_to_chan(unsigned short)
{
	return 0;
}

/* L223: unsigned short GF35_get_freq(void) */
__maybe_unused unsigned short GF35_get_freq(void)
{
	return 0;
}

/* L288: unsigned char GF35_get_rssi(void) */
__maybe_unused unsigned char GF35_get_rssi(void)
{
	return 0;
}

/* L299: unsigned char GF35_get_snr(void) */
__maybe_unused unsigned char GF35_get_snr(void)
{
	return 0;
}

/* L332: unsigned char GF35_get_stereo(void) */
__maybe_unused unsigned char GF35_get_stereo(void)
{
	return 0;
}

/* L165: void GF35_power_0ff(void) */
__maybe_unused void GF35_power_0ff(void)
{
	return;
}

/* L92: unsigned char GF35_power_on(void) */
__maybe_unused unsigned char GF35_power_on(void)
{
	return 0;
}

/* L211: void GF35_set_freq(unsigned short) */
__maybe_unused void GF35_set_freq(unsigned short)
{
	return;
}

/* L173: void GF35_set_mute(unsigned char) */
__maybe_unused void GF35_set_mute(unsigned char)
{
	return;
}

/* L346: void GF35_set_stereo(unsigned char) */
__maybe_unused void GF35_set_stereo(unsigned char)
{
	return;
}

/* L309: void GF35_set_volume(unsigned char) */
__maybe_unused void GF35_set_volume(unsigned char)
{
	return;
}

/* L259: int GF35_valid_check(unsigned short, int) */
__maybe_unused int GF35_valid_check(unsigned short, int)
{
	return 0;
}

/* L232: int GF35_valid_stop(unsigned short) */
__maybe_unused int GF35_valid_stop(unsigned short)
{
	return 0;
}

/* L169: int GetCurrentIndex(void) */
__maybe_unused int GetCurrentIndex(void)
{
	return 0;
}

/* L79: int GetPreSetRadioIndex(void) */
__maybe_unused int GetPreSetRadioIndex(void)
{
	return 0;
}

/* L147: struct SqlRadioFunc_ops *GetRadioFuncs(struct i2c_client *, const struct i2c_device_id *) */
__maybe_unused struct SqlRadioFunc_ops *GetRadioFuncs(struct i2c_client *, const struct i2c_device_id *)
{
	return 0;
}

/* L118: struct SqlRadioFunc_ops *ScanPresetRadio(struct i2c_client *, const struct i2c_device_id *) */
__maybe_unused struct SqlRadioFunc_ops *ScanPresetRadio(struct i2c_client *, const struct i2c_device_id *)
{
	return 0;
}

/* L128: struct SqlRadioFunc_ops *ScanRadioAll(struct i2c_client *, const struct i2c_device_id *) */
__maybe_unused struct SqlRadioFunc_ops *ScanRadioAll(struct i2c_client *, const struct i2c_device_id *)
{
	return 0;
}

/* L94: static struct SqlRadioFunc_ops *ScanOneRadio(struct i2c_client *, struct SqlRaidoScan_ops *, const struct i2c_device_id *) */
static struct SqlRadioFunc_ops *ScanOneRadio(struct i2c_client *, struct SqlRaidoScan_ops *, const struct i2c_device_id *);
static struct SqlRadioFunc_ops *ScanOneRadio(struct i2c_client *, struct SqlRaidoScan_ops *, const struct i2c_device_id *)
{
	return 0;
}

/* L1050: int CheckRestRadio(void) */
__maybe_unused int CheckRestRadio(void)
{
	return 0;
}

/* L2304: void PowerOnAndReset(int) */
__maybe_unused void PowerOnAndReset(int)
{
	return;
}

/* L390: void RadioDelayAfterReset(void) */
__maybe_unused void RadioDelayAfterReset(void)
{
	return;
}

/* L2295: void RadioResetfunc_all(int) */
__maybe_unused void RadioResetfunc_all(int)
{
	return;
}

/* L1071: void dumpcmd(unsigned int) */
__maybe_unused void dumpcmd(unsigned int)
{
	return;
}

/* L670: int getrssi_radio(void *) */
__maybe_unused int getrssi_radio(void *)
{
	return 0;
}

/* L1941: int lsec_gpio_request(int, const char *) */
__maybe_unused int lsec_gpio_request(int, const char *)
{
	return 0;
}

/* L661: int mute_radio(void *) */
__maybe_unused int mute_radio(void *)
{
	return 0;
}

/* L1154: long nxp685x_ioctl(struct file *, unsigned int, unsigned long) */
__maybe_unused long nxp685x_ioctl(struct file *, unsigned int, unsigned long)
{
	return 0;
}

/* L471: int nxp685x_open(struct inode *, struct file *) */
__maybe_unused int nxp685x_open(struct inode *, struct file *)
{
	return 0;
}

/* L541: unsigned int nxp685x_poll(struct file *, struct poll_table_struct *) */
__maybe_unused unsigned int nxp685x_poll(struct file *, struct poll_table_struct *)
{
	return 0;
}

/* L491: ssize_t nxp685x_read_rds_data(struct file *, char *, size_t, loff_t *) */
__maybe_unused ssize_t nxp685x_read_rds_data(struct file *, char *, size_t, loff_t *)
{
	return 0;
}

/* L1577: int nxp685x_release(struct inode *, struct file *) */
__maybe_unused int nxp685x_release(struct inode *, struct file *)
{
	return 0;
}

/* L607: int powerdown_radio(void) */
__maybe_unused int powerdown_radio(void)
{
	return 0;
}

/* L580: int powerup_radio(void *) */
__maybe_unused int powerup_radio(void *)
{
	return 0;
}

/* L368: int radio_ant_power(int) */
__maybe_unused int radio_ant_power(int)
{
	return 0;
}

/* L449: int radio_init(struct i2c_client *) */
__maybe_unused int radio_init(struct i2c_client *)
{
	return 0;
}

/* L333: int radio_mute3702(int) */
__maybe_unused int radio_mute3702(int)
{
	return 0;
}

/* L340: int radio_power(int) */
__maybe_unused int radio_power(int)
{
	return 0;
}

/* L426: int radio_reset_ctl(int) */
__maybe_unused int radio_reset_ctl(int)
{
	return 0;
}

/* L410: int radio_reset_req(void) */
__maybe_unused int radio_reset_req(void)
{
	return 0;
}

/* L455: int radio_var_init(void) */
__maybe_unused int radio_var_init(void)
{
	return 0;
}

/* L624: int seek_radio(void *) */
__maybe_unused int seek_radio(void *)
{
	return 0;
}

/* L1005: int sqlfm_dualtunerctrl(void *) */
__maybe_unused int sqlfm_dualtunerctrl(void *)
{
	return 0;
}

/* L808: int sqlfm_forcemono(void *) */
__maybe_unused int sqlfm_forcemono(void *)
{
	return 0;
}

/* L1035: int sqlfm_getdefault(void *) */
__maybe_unused int sqlfm_getdefault(void *)
{
	return 0;
}

/* L831: int sqlfm_getfmono(void *) */
__maybe_unused int sqlfm_getfmono(void *)
{
	return 0;
}

/* L868: int sqlfm_getindex(void *) */
__maybe_unused int sqlfm_getindex(void *)
{
	return 0;
}

/* L793: int sqlfm_getlevel(void *) */
__maybe_unused int sqlfm_getlevel(void *)
{
	return 0;
}

/* L893: int sqlfm_getmodulename(void *) */
__maybe_unused int sqlfm_getmodulename(void *)
{
	return 0;
}

/* L940: int sqlfm_getrdsaflevel(void *) */
__maybe_unused int sqlfm_getrdsaflevel(void *)
{
	return 0;
}

/* L928: int sqlfm_getrdsfixlevel(void *) */
__maybe_unused int sqlfm_getrdsfixlevel(void *)
{
	return 0;
}

/* L880: int sqlfm_getseekquality(void *) */
__maybe_unused int sqlfm_getseekquality(void *)
{
	return 0;
}

/* L976: int sqlfm_getseekstatus(void *) */
__maybe_unused int sqlfm_getseekstatus(void *)
{
	return 0;
}

/* L913: int sqlfm_getsubname(void *) */
__maybe_unused int sqlfm_getsubname(void *)
{
	return 0;
}

/* L1019: int sqlfm_getsurportlist(void *) */
__maybe_unused int sqlfm_getsurportlist(void *)
{
	return 0;
}

/* L847: int sqlfm_isstereo(void *) */
__maybe_unused int sqlfm_isstereo(void *)
{
	return 0;
}

/* L751: int sqlfm_mute(void *) */
__maybe_unused int sqlfm_mute(void *)
{
	return 0;
}

/* L727: int sqlfm_powerdown(void) */
__maybe_unused int sqlfm_powerdown(void)
{
	return 0;
}

/* L702: int sqlfm_powerup(void *) */
__maybe_unused int sqlfm_powerup(void *)
{
	return 0;
}

/* L988: int sqlfm_reportta(void *) */
__maybe_unused int sqlfm_reportta(void *)
{
	return 0;
}

/* L964: int sqlfm_seekcontrol(void *) */
__maybe_unused int sqlfm_seekcontrol(void *)
{
	return 0;
}

/* L952: int sqlfm_setband(void *) */
__maybe_unused int sqlfm_setband(void *)
{
	return 0;
}

/* L838: int sqlfm_stopseek(void *) */
__maybe_unused int sqlfm_stopseek(void *)
{
	return 0;
}

/* L676: int sqlfm_tune(void *) */
__maybe_unused int sqlfm_tune(void *)
{
	return 0;
}

/* L586: int tune_radio(void *) */
__maybe_unused int tune_radio(void *)
{
	return 0;
}

/* L2353: static void exit_sradio_driver(void) */
static void exit_sradio_driver(void);
static void exit_sradio_driver(void)
{
	return;
}

/* L1617: static void fm_esd_check_func(struct work_struct *) */
static void fm_esd_check_func(struct work_struct *);
static void fm_esd_check_func(struct work_struct *)
{
	return;
}

/* L1827: static int fm_lsec_notifier_callback(struct notifier_block *, unsigned long, void *) */
static int fm_lsec_notifier_callback(struct notifier_block *, unsigned long, void *);
static int fm_lsec_notifier_callback(struct notifier_block *, unsigned long, void *)
{
	return 0;
}

/* L1863: static void fm_lsec_resume_work(struct work_struct *) */
static void fm_lsec_resume_work(struct work_struct *);
static void fm_lsec_resume_work(struct work_struct *)
{
	return;
}

/* L1777: static int fm_pm_resume(struct device *) */
static int fm_pm_resume(struct device *);
static int fm_pm_resume(struct device *)
{
	return 0;
}

/* L1769: static int fm_pm_suspend(struct device *) */
static int fm_pm_suspend(struct device *);
static int fm_pm_suspend(struct device *)
{
	return 0;
}

/* L2323: static int init_sradio_driver(void) */
static int init_sradio_driver(void);
static int init_sradio_driver(void)
{
	return 0;
}

/* L1566: static long nxp685x_compat_ioctl(struct file *, unsigned int, unsigned long) */
static long nxp685x_compat_ioctl(struct file *, unsigned int, unsigned long);
static long nxp685x_compat_ioctl(struct file *, unsigned int, unsigned long)
{
	return 0;
}

/* L1971: static int nxp685x_probe(struct i2c_client *, const struct i2c_device_id *) */
static int nxp685x_probe(struct i2c_client *, const struct i2c_device_id *);
static int nxp685x_probe(struct i2c_client *, const struct i2c_device_id *)
{
	return 0;
}

/* L2180: static int nxp685x_remove(struct i2c_client *) */
static int nxp685x_remove(struct i2c_client *);
static int nxp685x_remove(struct i2c_client *)
{
	return 0;
}

/* L259: static ssize_t sqlfm_read_proc(struct file *, char *, size_t, loff_t *) */
static ssize_t sqlfm_read_proc(struct file *, char *, size_t, loff_t *);
static ssize_t sqlfm_read_proc(struct file *, char *, size_t, loff_t *)
{
	return 0;
}

/* L296: static ssize_t sqlfm_write_proc(struct file *, const char *, size_t, loff_t *) */
static ssize_t sqlfm_write_proc(struct file *, const char *, size_t, loff_t *);
static ssize_t sqlfm_write_proc(struct file *, const char *, size_t, loff_t *)
{
	return 0;
}

/* L2442: unsigned char APPL_Get_Operation_Status(TUNER_STATE *) */
__maybe_unused unsigned char APPL_Get_Operation_Status(TUNER_STATE *)
{
	return 0;
}

/* L2674: unsigned char APPL_Get_Operation_Status_C(TUNER_STATE *, struct i2c_client *) */
__maybe_unused unsigned char APPL_Get_Operation_Status_C(TUNER_STATE *, struct i2c_client *)
{
	return 0;
}

/* L2472: unsigned char Radio6851_CheckStereo(void) */
__maybe_unused unsigned char Radio6851_CheckStereo(void)
{
	return 0;
}

/* L2514: unsigned char Radio6851_ForeceMono(unsigned char) */
__maybe_unused unsigned char Radio6851_ForeceMono(unsigned char)
{
	return 0;
}

/* L2586: unsigned char Radio6851_Get_AFLevel(void) */
__maybe_unused unsigned char Radio6851_Get_AFLevel(void)
{
	return 0;
}

/* L2483: unsigned char Radio6851_Get_Level(unsigned char) */
__maybe_unused unsigned char Radio6851_Get_Level(unsigned char)
{
	return 0;
}

/* L2504: unsigned char Radio6851_Get_Quality_Data(unsigned char, unsigned char *, unsigned char *, unsigned short *, unsigned short *) */
__maybe_unused unsigned char Radio6851_Get_Quality_Data(unsigned char, unsigned char *, unsigned char *, unsigned short *, unsigned short *)
{
	return 0;
}

/* L2524: unsigned char Radio6851_ReadChipStatus(void) */
__maybe_unused unsigned char Radio6851_ReadChipStatus(void)
{
	return 0;
}

/* L275: unsigned char Tuner_Boot(void) */
__maybe_unused unsigned char Tuner_Boot(void)
{
	return 0;
}

/* L81: unsigned char Tuner_Patch_Load(const unsigned char *, int) */
__maybe_unused unsigned char Tuner_Patch_Load(const unsigned char *, int)
{
	return 0;
}

/* L59: unsigned char Tuner_ReadBuffer(unsigned char *, unsigned char) */
__maybe_unused unsigned char Tuner_ReadBuffer(unsigned char *, unsigned char)
{
	return 0;
}

/* L2635: unsigned char Tuner_ReadBuffer_C(unsigned char *, unsigned char, struct i2c_client *) */
__maybe_unused unsigned char Tuner_ReadBuffer_C(unsigned char *, unsigned char, struct i2c_client *)
{
	return 0;
}

/* L107: unsigned char Tuner_Set_ReferenceClock(int) */
__maybe_unused unsigned char Tuner_Set_ReferenceClock(int)
{
	return 0;
}

/* L214: unsigned char Tuner_Table_ConfigWrite(const unsigned char *, int) */
__maybe_unused unsigned char Tuner_Table_ConfigWrite(const unsigned char *, int)
{
	return 0;
}

/* L135: unsigned char Tuner_Table_Write(const unsigned char *, int) */
__maybe_unused unsigned char Tuner_Table_Write(const unsigned char *, int)
{
	return 0;
}

/* L67: void Tuner_WaitMs(unsigned int) */
__maybe_unused void Tuner_WaitMs(unsigned int)
{
	return;
}

/* L52: unsigned char Tuner_WriteBuffer(unsigned char *, unsigned char) */
__maybe_unused unsigned char Tuner_WriteBuffer(unsigned char *, unsigned char)
{
	return 0;
}

/* L2628: unsigned char Tuner_WriteBuffer_C(unsigned char *, unsigned char, struct i2c_client *) */
__maybe_unused unsigned char Tuner_WriteBuffer_C(unsigned char *, unsigned char, struct i2c_client *)
{
	return 0;
}

/* L1918: unsigned char devTEF668x_APPL_Activate(unsigned short) */
__maybe_unused unsigned char devTEF668x_APPL_Activate(unsigned short)
{
	return 0;
}

/* L2342: unsigned char devTEF668x_APPL_Get_GPIO_Status(unsigned short *) */
__maybe_unused unsigned char devTEF668x_APPL_Get_GPIO_Status(unsigned short *)
{
	return 0;
}

/* L2385: unsigned char devTEF668x_APPL_Get_Identification(unsigned short *, unsigned short *, unsigned short *) */
__maybe_unused unsigned char devTEF668x_APPL_Get_Identification(unsigned short *, unsigned short *, unsigned short *)
{
	return 0;
}

/* L2428: unsigned char devTEF668x_APPL_Get_LastWrite(unsigned char *, int) */
__maybe_unused unsigned char devTEF668x_APPL_Get_LastWrite(unsigned char *, int)
{
	return 0;
}

/* L2314: unsigned char devTEF668x_APPL_Get_Operation_Status(unsigned char *) */
__maybe_unused unsigned char devTEF668x_APPL_Get_Operation_Status(unsigned char *)
{
	return 0;
}

/* L2657: unsigned char devTEF668x_APPL_Get_Operation_Status_C(unsigned char *, struct i2c_client *) */
__maybe_unused unsigned char devTEF668x_APPL_Get_Operation_Status_C(unsigned char *, struct i2c_client *)
{
	return 0;
}

/* L1874: unsigned char devTEF668x_APPL_Set_GPIO(unsigned short, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_APPL_Set_GPIO(unsigned short, unsigned short, unsigned short)
{
	return 0;
}

/* L1837: unsigned char devTEF668x_APPL_Set_OperationMode(unsigned short) */
__maybe_unused unsigned char devTEF668x_APPL_Set_OperationMode(unsigned short)
{
	return 0;
}

/* L1900: unsigned char devTEF668x_APPL_Set_ReferenceClock(unsigned short, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_APPL_Set_ReferenceClock(unsigned short, unsigned short, unsigned short)
{
	return 0;
}

/* L1700: unsigned char devTEF668x_Audio_Set_Ana_Out(unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Audio_Set_Ana_Out(unsigned short, unsigned short)
{
	return 0;
}

/* L1742: unsigned char devTEF668x_Audio_Set_Dig_IO(unsigned short, unsigned short, unsigned short, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Audio_Set_Dig_IO(unsigned short, unsigned short, unsigned short, unsigned short, unsigned short)
{
	return 0;
}

/* L1649: unsigned char devTEF668x_Audio_Set_Input(unsigned short) */
__maybe_unused unsigned char devTEF668x_Audio_Set_Input(unsigned short)
{
	return 0;
}

/* L1766: unsigned char devTEF668x_Audio_Set_Input_Scaler(unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Audio_Set_Input_Scaler(unsigned short, unsigned short)
{
	return 0;
}

/* L1626: unsigned char devTEF668x_Audio_Set_Mute(unsigned short) */
__maybe_unused unsigned char devTEF668x_Audio_Set_Mute(unsigned short)
{
	return 0;
}

/* L1676: unsigned char devTEF668x_Audio_Set_Output_Source(unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Audio_Set_Output_Source(unsigned short, unsigned short)
{
	return 0;
}

/* L1606: unsigned char devTEF668x_Audio_Set_Volume(unsigned short) */
__maybe_unused unsigned char devTEF668x_Audio_Set_Volume(unsigned short)
{
	return 0;
}

/* L1816: unsigned char devTEF668x_Audio_Set_WaveGen(unsigned short, unsigned short, unsigned short, unsigned short, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Audio_Set_WaveGen(unsigned short, unsigned short, unsigned short, unsigned short, unsigned short, unsigned short)
{
	return 0;
}

/* L398: unsigned char devTEF668x_Get_Cmd(TEF668x_MODULE, unsigned char, unsigned char *, int) */
__maybe_unused unsigned char devTEF668x_Get_Cmd(TEF668x_MODULE, unsigned char, unsigned char *, int)
{
	return 0;
}

/* L2642: unsigned char devTEF668x_Get_Cmd_C(TEF668x_MODULE, unsigned char, unsigned char *, int, struct i2c_client *) */
__maybe_unused unsigned char devTEF668x_Get_Cmd_C(TEF668x_MODULE, unsigned char, unsigned char *, int, struct i2c_client *)
{
	return 0;
}

/* L2201: unsigned char devTEF668x_Radio_Get_AGC(unsigned char, unsigned short *, unsigned short *) */
__maybe_unused unsigned char devTEF668x_Radio_Get_AGC(unsigned char, unsigned short *, unsigned short *)
{
	return 0;
}

/* L2286: unsigned char devTEF668x_Radio_Get_Interface_Status(unsigned char, unsigned short *) */
__maybe_unused unsigned char devTEF668x_Radio_Get_Interface_Status(unsigned char, unsigned short *)
{
	return 0;
}

/* L2257: unsigned char devTEF668x_Radio_Get_Processing_Status(unsigned char, unsigned short *, unsigned short *, unsigned short *) */
__maybe_unused unsigned char devTEF668x_Radio_Get_Processing_Status(unsigned char, unsigned short *, unsigned short *, unsigned short *)
{
	return 0;
}

/* L2054: unsigned char devTEF668x_Radio_Get_Quality_Data(unsigned char, unsigned char *, unsigned char *, unsigned short *, unsigned short *) */
__maybe_unused unsigned char devTEF668x_Radio_Get_Quality_Data(unsigned char, unsigned char *, unsigned char *, unsigned short *, unsigned short *)
{
	return 0;
}

/* L2023: unsigned char devTEF668x_Radio_Get_Quality_Level(unsigned char, unsigned char *, unsigned short *) */
__maybe_unused unsigned char devTEF668x_Radio_Get_Quality_Level(unsigned char, unsigned char *, unsigned short *)
{
	return 0;
}

/* L1979: unsigned char devTEF668x_Radio_Get_Quality_Status(unsigned char, unsigned char *) */
__maybe_unused unsigned char devTEF668x_Radio_Get_Quality_Status(unsigned char, unsigned char *)
{
	return 0;
}

/* L2147: unsigned char devTEF668x_Radio_Get_RDS_Data(unsigned char, unsigned short *, unsigned short *, unsigned short *, unsigned short *, unsigned short *, unsigned short *) */
__maybe_unused unsigned char devTEF668x_Radio_Get_RDS_Data(unsigned char, unsigned short *, unsigned short *, unsigned short *, unsigned short *, unsigned short *, unsigned short *)
{
	return 0;
}

/* L2167: unsigned char devTEF668x_Radio_Get_RDS_DataRaw(unsigned char, unsigned short *, unsigned short *, unsigned short *) */
__maybe_unused unsigned char devTEF668x_Radio_Get_RDS_DataRaw(unsigned char, unsigned short *, unsigned short *, unsigned short *)
{
	return 0;
}

/* L2132: unsigned char devTEF668x_Radio_Get_RDS_Status(unsigned char, unsigned short *) */
__maybe_unused unsigned char devTEF668x_Radio_Get_RDS_Status(unsigned char, unsigned short *)
{
	return 0;
}

/* L2230: unsigned char devTEF668x_Radio_Get_Signal_Status(unsigned char, unsigned short *) */
__maybe_unused unsigned char devTEF668x_Radio_Get_Signal_Status(unsigned char, unsigned short *)
{
	return 0;
}

/* L1994: unsigned char devTEF668x_Radio_Is_AF_Update_Available(void) */
__maybe_unused unsigned char devTEF668x_Radio_Is_AF_Update_Available(void)
{
	return 0;
}

/* L2008: unsigned char devTEF668x_Radio_Is_RDAV_Available(void) */
__maybe_unused unsigned char devTEF668x_Radio_Is_RDAV_Available(void)
{
	return 0;
}

/* L561: unsigned char devTEF668x_Radio_Set_Antenna(unsigned char, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Antenna(unsigned char, unsigned short)
{
	return 0;
}

/* L513: unsigned char devTEF668x_Radio_Set_Bandwidth(unsigned char, unsigned short, unsigned short, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Bandwidth(unsigned char, unsigned short, unsigned short, unsigned short, unsigned short)
{
	return 0;
}

/* L600: unsigned char devTEF668x_Radio_Set_ChannelEqualizer(unsigned char, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_ChannelEqualizer(unsigned char, unsigned short)
{
	return 0;
}

/* L1543: unsigned char devTEF668x_Radio_Set_DR_Blend(unsigned char, unsigned short, unsigned short, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_DR_Blend(unsigned char, unsigned short, unsigned short, unsigned short, unsigned short)
{
	return 0;
}

/* L1565: unsigned char devTEF668x_Radio_Set_DR_Options(unsigned char, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_DR_Options(unsigned char, unsigned short)
{
	return 0;
}

/* L736: unsigned char devTEF668x_Radio_Set_Deemphasis(unsigned char, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Deemphasis(unsigned char, unsigned short)
{
	return 0;
}

/* L716: unsigned char devTEF668x_Radio_Set_DigitalRadio(unsigned char, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_DigitalRadio(unsigned char, unsigned short)
{
	return 0;
}

/* L1058: unsigned char devTEF668x_Radio_Set_Highcut_Level(unsigned char, unsigned short, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Highcut_Level(unsigned char, unsigned short, unsigned short, unsigned short)
{
	return 0;
}

/* L1154: unsigned char devTEF668x_Radio_Set_Highcut_Max(unsigned char, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Highcut_Max(unsigned char, unsigned short, unsigned short)
{
	return 0;
}

/* L1180: unsigned char devTEF668x_Radio_Set_Highcut_Min(unsigned char, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Highcut_Min(unsigned char, unsigned short, unsigned short)
{
	return 0;
}

/* L1025: unsigned char devTEF668x_Radio_Set_Highcut_Mod(unsigned char, unsigned short, unsigned short, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Highcut_Mod(unsigned char, unsigned short, unsigned short, unsigned short, unsigned short)
{
	return 0;
}

/* L1126: unsigned char devTEF668x_Radio_Set_Highcut_Mph(unsigned char, unsigned short, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Highcut_Mph(unsigned char, unsigned short, unsigned short, unsigned short)
{
	return 0;
}

/* L1092: unsigned char devTEF668x_Radio_Set_Highcut_Noise(unsigned char, unsigned short, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Highcut_Noise(unsigned char, unsigned short, unsigned short, unsigned short)
{
	return 0;
}

/* L989: unsigned char devTEF668x_Radio_Set_Highcut_Time(unsigned char, unsigned short, unsigned short, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Highcut_Time(unsigned char, unsigned short, unsigned short, unsigned short, unsigned short)
{
	return 0;
}

/* L804: unsigned char devTEF668x_Radio_Set_LevelOffset(unsigned char, int) */
__maybe_unused unsigned char devTEF668x_Radio_Set_LevelOffset(unsigned char, int)
{
	return 0;
}

/* L785: unsigned char devTEF668x_Radio_Set_LevelStep(unsigned char, int, int, int, int, int, int, int) */
__maybe_unused unsigned char devTEF668x_Radio_Set_LevelStep(unsigned char, int, int, int, int, int, int, int)
{
	return 0;
}

/* L1206: unsigned char devTEF668x_Radio_Set_Lowcut_Min(unsigned char, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Lowcut_Min(unsigned char, unsigned short, unsigned short)
{
	return 0;
}

/* L581: unsigned char devTEF668x_Radio_Set_MphSuppression(unsigned char, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_MphSuppression(unsigned char, unsigned short)
{
	return 0;
}

/* L673: unsigned char devTEF668x_Radio_Set_NoiseBlanker(unsigned char, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_NoiseBlanker(unsigned char, unsigned short, unsigned short)
{
	return 0;
}

/* L697: unsigned char devTEF668x_Radio_Set_NoiseBlanker_Audio(unsigned char, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_NoiseBlanker_Audio(unsigned char, unsigned short, unsigned short)
{
	return 0;
}

/* L1506: unsigned char devTEF668x_Radio_Set_QualityStatus(unsigned char, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_QualityStatus(unsigned char, unsigned short, unsigned short)
{
	return 0;
}

/* L1480: unsigned char devTEF668x_Radio_Set_RDS(unsigned char, unsigned short, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_RDS(unsigned char, unsigned short, unsigned short, unsigned short)
{
	return 0;
}

/* L541: unsigned char devTEF668x_Radio_Set_RFAGC(unsigned char, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_RFAGC(unsigned char, unsigned short, unsigned short)
{
	return 0;
}

/* L1444: unsigned char devTEF668x_Radio_Set_Scaler(unsigned char, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Scaler(unsigned char, unsigned short)
{
	return 0;
}

/* L865: unsigned char devTEF668x_Radio_Set_Softmute_Level(unsigned char, unsigned short, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Softmute_Level(unsigned char, unsigned short, unsigned short, unsigned short)
{
	return 0;
}

/* L953: unsigned char devTEF668x_Radio_Set_Softmute_Max(unsigned char, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Softmute_Max(unsigned char, unsigned short, unsigned short)
{
	return 0;
}

/* L927: unsigned char devTEF668x_Radio_Set_Softmute_Mph(unsigned char, unsigned short, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Softmute_Mph(unsigned char, unsigned short, unsigned short, unsigned short)
{
	return 0;
}

/* L896: unsigned char devTEF668x_Radio_Set_Softmute_Noise(unsigned char, unsigned short, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Softmute_Noise(unsigned char, unsigned short, unsigned short, unsigned short)
{
	return 0;
}

/* L838: unsigned char devTEF668x_Radio_Set_Softmute_Time(unsigned char, unsigned short, unsigned short, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Softmute_Time(unsigned char, unsigned short, unsigned short, unsigned short, unsigned short)
{
	return 0;
}

/* L1586: unsigned char devTEF668x_Radio_Set_Specials(unsigned char, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Specials(unsigned char, unsigned short)
{
	return 0;
}

/* L649: unsigned char devTEF668x_Radio_Set_StHiBlend_Time(unsigned char, unsigned short, unsigned short, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_StHiBlend_Time(unsigned char, unsigned short, unsigned short, unsigned short, unsigned short)
{
	return 0;
}

/* L617: unsigned char devTEF668x_Radio_Set_StereoImprovement(unsigned char, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_StereoImprovement(unsigned char, unsigned short)
{
	return 0;
}

/* L1312: unsigned char devTEF668x_Radio_Set_Stereo_Level(unsigned char, unsigned short, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Stereo_Level(unsigned char, unsigned short, unsigned short, unsigned short)
{
	return 0;
}

/* L1397: unsigned char devTEF668x_Radio_Set_Stereo_Max(unsigned char, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Stereo_Max(unsigned char, unsigned short)
{
	return 0;
}

/* L1424: unsigned char devTEF668x_Radio_Set_Stereo_Min(unsigned char, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Stereo_Min(unsigned char, unsigned short, unsigned short)
{
	return 0;
}

/* L1279: unsigned char devTEF668x_Radio_Set_Stereo_Mod(unsigned char, unsigned short, unsigned short, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Stereo_Mod(unsigned char, unsigned short, unsigned short, unsigned short, unsigned short)
{
	return 0;
}

/* L1376: unsigned char devTEF668x_Radio_Set_Stereo_Mph(unsigned char, unsigned short, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Stereo_Mph(unsigned char, unsigned short, unsigned short, unsigned short)
{
	return 0;
}

/* L1345: unsigned char devTEF668x_Radio_Set_Stereo_Noise(unsigned char, unsigned short, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Stereo_Noise(unsigned char, unsigned short, unsigned short, unsigned short)
{
	return 0;
}

/* L1242: unsigned char devTEF668x_Radio_Set_Stereo_Time(unsigned char, unsigned short, unsigned short, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Stereo_Time(unsigned char, unsigned short, unsigned short, unsigned short, unsigned short)
{
	return 0;
}

/* L474: unsigned char devTEF668x_Radio_Set_Tune_Options(unsigned char, unsigned short, unsigned short, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Set_Tune_Options(unsigned char, unsigned short, unsigned short, unsigned short, unsigned short)
{
	return 0;
}

/* L440: unsigned char devTEF668x_Radio_Tune_To(unsigned char, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Radio_Tune_To(unsigned char, unsigned short, unsigned short)
{
	return 0;
}

/* L357: unsigned char devTEF668x_Set_Cmd(TEF668x_MODULE, unsigned char, int, unsigned short, unsigned short, unsigned short, unsigned short, unsigned short, unsigned short, unsigned short, unsigned short) */
__maybe_unused unsigned char devTEF668x_Set_Cmd(TEF668x_MODULE, unsigned char, int, unsigned short, unsigned short, unsigned short, unsigned short, unsigned short, unsigned short, unsigned short, unsigned short)
{
	return 0;
}

/* L197: int get_crystal_index(PSQL_INFO) */
__maybe_unused int get_crystal_index(PSQL_INFO)
{
	return 0;
}

/* L764: int Check4730AM_SeekStatus(int, unsigned char *) */
__maybe_unused int Check4730AM_SeekStatus(int, unsigned char *)
{
	return 0;
}

/* L740: int Check4730FM_SeekStatus(int, unsigned char *) */
__maybe_unused int Check4730FM_SeekStatus(int, unsigned char *)
{
	return 0;
}

/* L308: int RDS4731_FetchBlockData(unsigned char, unsigned short *, unsigned short *, unsigned short *, unsigned short *) */
__maybe_unused int RDS4731_FetchBlockData(unsigned char, unsigned short *, unsigned short *, unsigned short *, unsigned short *)
{
	return 0;
}

/* L555: unsigned char Radio4730SetFreq(unsigned int) */
__maybe_unused unsigned char Radio4730SetFreq(unsigned int)
{
	return 0;
}

/* L467: void Radio4730_Disable_Stereo(void) */
__maybe_unused void Radio4730_Disable_Stereo(void)
{
	return;
}

/* L443: void Radio4730_Enable_Stereo(void) */
__maybe_unused void Radio4730_Enable_Stereo(void)
{
	return;
}

/* L526: unsigned char Set_AM(unsigned int) */
__maybe_unused unsigned char Set_AM(unsigned int)
{
	return 0;
}

/* L496: unsigned char Set_FM(unsigned int) */
__maybe_unused unsigned char Set_FM(unsigned int)
{
	return 0;
}

/* L76: unsigned char Si4730_Power_Up(void) */
__maybe_unused unsigned char Si4730_Power_Up(void)
{
	return 0;
}

/* L704: unsigned char Si47XX_AM_Tune_Status(void) */
__maybe_unused unsigned char Si47XX_AM_Tune_Status(void)
{
	return 0;
}

/* L614: unsigned char Si47XX_FM_Get_RSSI(void) */
__maybe_unused unsigned char Si47XX_FM_Get_RSSI(void)
{
	return 0;
}

/* L665: unsigned char Si47XX_FM_Tune_Status(void) */
__maybe_unused unsigned char Si47XX_FM_Tune_Status(void)
{
	return 0;
}

/* L159: unsigned char Si47XX_Set_Property(unsigned int, unsigned int) */
__maybe_unused unsigned char Si47XX_Set_Property(unsigned int, unsigned int)
{
	return 0;
}

/* L255: unsigned char Si47XX_Set_Property_RDS_config(void) */
__maybe_unused unsigned char Si47XX_Set_Property_RDS_config(void)
{
	return 0;
}

/* L232: unsigned char Si47XX_Set_Property_RDS_int_FIFO_count(void) */
__maybe_unused unsigned char Si47XX_Set_Property_RDS_int_FIFO_count(void)
{
	return 0;
}

/* L210: unsigned char Si47XX_Set_Property_RDS_int_source(void) */
__maybe_unused unsigned char Si47XX_Set_Property_RDS_int_source(void)
{
	return 0;
}

/* L112: unsigned char Si47XX_Wait_STC(void) */
__maybe_unused unsigned char Si47XX_Wait_STC(void)
{
	return 0;
}

/* L39: unsigned char Wait_CTS(void) */
__maybe_unused unsigned char Wait_CTS(void)
{
	return 0;
}

/* L275: unsigned char Wait_Rds_CTS(void) */
__maybe_unused unsigned char Wait_Rds_CTS(void)
{
	return 0;
}

/* L589: void si4730_Mute(int) */
__maybe_unused void si4730_Mute(int)
{
	return;
}

/* L189: void si47xxRX_set_volume(unsigned char) */
__maybe_unused void si47xxRX_set_volume(unsigned char)
{
	return;
}

/* L253: void Radio4730_HW_Init(void) */
__maybe_unused void Radio4730_HW_Init(void)
{
	return;
}

/* L198: int SearchRadioSi4730(struct i2c_client *, const struct i2c_device_id *) */
__maybe_unused int SearchRadioSi4730(struct i2c_client *, const struct i2c_device_id *)
{
	return 0;
}

/* L124: int radio_i2c_read_4730(struct i2c_client *, unsigned char *, int) */
__maybe_unused int radio_i2c_read_4730(struct i2c_client *, unsigned char *, int)
{
	return 0;
}

/* L175: int radio_i2c_write_4730(struct i2c_client *, unsigned char *, int) */
__maybe_unused int radio_i2c_write_4730(struct i2c_client *, unsigned char *, int)
{
	return 0;
}

/* L387: int si4730_esdcheck(void *) */
__maybe_unused int si4730_esdcheck(void *)
{
	return 0;
}

/* L425: int si4730_getdefaultparama(void *) */
__maybe_unused int si4730_getdefaultparama(void *)
{
	return 0;
}

/* L381: int si4730_getmodulename(void *) */
__maybe_unused int si4730_getmodulename(void *)
{
	return 0;
}

/* L518: int si4730_getrdsaflevel(void *) */
__maybe_unused int si4730_getrdsaflevel(void *)
{
	return 0;
}

/* L441: int si4730_getrdsblockdata(void *) */
__maybe_unused int si4730_getrdsblockdata(void *)
{
	return 0;
}

/* L483: int si4730_getrdsfixlevel(void *) */
__maybe_unused int si4730_getrdsfixlevel(void *)
{
	return 0;
}

/* L337: int si4730_getrssi(void *) */
__maybe_unused int si4730_getrssi(void *)
{
	return 0;
}

/* L352: int si4730_getseekquality(void *) */
__maybe_unused int si4730_getseekquality(void *)
{
	return 0;
}

/* L432: int si4730_getsubname(void *) */
__maybe_unused int si4730_getsubname(void *)
{
	return 0;
}

/* L418: int si4730_getsurportlist(void *) */
__maybe_unused int si4730_getsurportlist(void *)
{
	return 0;
}

/* L399: int si4730_ioctlcheck(void *) */
__maybe_unused int si4730_ioctlcheck(void *)
{
	return 0;
}

/* L331: int si4730_issteromode(void *) */
__maybe_unused int si4730_issteromode(void *)
{
	return 0;
}

/* L294: int si4730_powerdown(void *) */
__maybe_unused int si4730_powerdown(void *)
{
	return 0;
}

/* L288: int si4730_powerup(void *) */
__maybe_unused int si4730_powerup(void *)
{
	return 0;
}

/* L219: int si4730_probeinit(void *) */
__maybe_unused int si4730_probeinit(void *)
{
	return 0;
}

/* L470: int si4730_rdsonoff(void *) */
__maybe_unused int si4730_rdsonoff(void *)
{
	return 0;
}

/* L409: int si4730_resume(void *) */
__maybe_unused int si4730_resume(void *)
{
	return 0;
}

/* L545: int si4730_seekcontrol(void *) */
__maybe_unused int si4730_seekcontrol(void *)
{
	return 0;
}

/* L320: int si4730_setforcemono(void *) */
__maybe_unused int si4730_setforcemono(void *)
{
	return 0;
}

/* L312: int si4730_setmute(void *) */
__maybe_unused int si4730_setmute(void *)
{
	return 0;
}

/* L404: int si4730_suspend(void *) */
__maybe_unused int si4730_suspend(void *)
{
	return 0;
}

/* L299: int si4730_tuneradio(void *) */
__maybe_unused int si4730_tuneradio(void *)
{
	return 0;
}

/* L314: int Check475XAM_SeekStatus(int, unsigned char *) */
__maybe_unused int Check475XAM_SeekStatus(int, unsigned char *)
{
	return 0;
}

/* L310: int Check475XFM_SeekStatus(int, unsigned char *) */
__maybe_unused int Check475XFM_SeekStatus(int, unsigned char *)
{
	return 0;
}

/* L283: int GetCurrentRssi(void) */
__maybe_unused int GetCurrentRssi(void)
{
	return 0;
}

/* L305: int GetRDSQuality(unsigned char *, unsigned char *, unsigned char *, unsigned char *) */
__maybe_unused int GetRDSQuality(unsigned char *, unsigned char *, unsigned char *, unsigned char *)
{
	return 0;
}

/* L350: int LsecGetPartIsNeedLoadPatch(void) */
__maybe_unused int LsecGetPartIsNeedLoadPatch(void)
{
	return 0;
}

/* L321: const char *LsecGetPartName(void) */
__maybe_unused const char *LsecGetPartName(void)
{
	return 0;
}

/* L335: int LsecGetPartSurpportlist(void) */
__maybe_unused int LsecGetPartSurpportlist(void)
{
	return 0;
}

/* L196: int Radio475xSetFreq(unsigned int) */
__maybe_unused int Radio475xSetFreq(unsigned int)
{
	return 0;
}

/* L365: int SearchRadioSi475x(struct i2c_client *, const struct i2c_device_id *) */
__maybe_unused int SearchRadioSi475x(struct i2c_client *, const struct i2c_device_id *)
{
	return 0;
}

/* L273: void SwitchStereoMono(int) */
__maybe_unused void SwitchStereoMono(int)
{
	return;
}

/* L248: void radio475x_Mute(int) */
__maybe_unused void radio475x_Mute(int)
{
	return;
}

/* L717: int radio475x_esdcheck(void *) */
__maybe_unused int radio475x_esdcheck(void *)
{
	return 0;
}

/* L552: int radio475x_getdefaultparama(void *) */
__maybe_unused int radio475x_getdefaultparama(void *)
{
	return 0;
}

/* L478: int radio475x_getmodulename(void *) */
__maybe_unused int radio475x_getmodulename(void *)
{
	return 0;
}

/* L685: int radio475x_getrdsaflevel(void *) */
__maybe_unused int radio475x_getrdsaflevel(void *)
{
	return 0;
}

/* L573: int radio475x_getrdsblockdata(void *) */
__maybe_unused int radio475x_getrdsblockdata(void *)
{
	return 0;
}

/* L614: int radio475x_getrdsfixlevel(void *) */
__maybe_unused int radio475x_getrdsfixlevel(void *)
{
	return 0;
}

/* L466: int radio475x_getrssi(void *) */
__maybe_unused int radio475x_getrssi(void *)
{
	return 0;
}

/* L485: int radio475x_getseekquality(void *) */
__maybe_unused int radio475x_getseekquality(void *)
{
	return 0;
}

/* L560: int radio475x_getsubname(void *) */
__maybe_unused int radio475x_getsubname(void *)
{
	return 0;
}

/* L543: int radio475x_getsurportlist(void *) */
__maybe_unused int radio475x_getsurportlist(void *)
{
	return 0;
}

/* L518: int radio475x_ioctlcheck(void *) */
__maybe_unused int radio475x_ioctlcheck(void *)
{
	return 0;
}

/* L455: int radio475x_issteromode(void *) */
__maybe_unused int radio475x_issteromode(void *)
{
	return 0;
}

/* L412: int radio475x_powerdown(void *) */
__maybe_unused int radio475x_powerdown(void *)
{
	return 0;
}

/* L395: int radio475x_powerup(void *) */
__maybe_unused int radio475x_powerup(void *)
{
	return 0;
}

/* L374: int radio475x_probeinit(void *) */
__maybe_unused int radio475x_probeinit(void *)
{
	return 0;
}

/* L603: int radio475x_rdsonoff(void *) */
__maybe_unused int radio475x_rdsonoff(void *)
{
	return 0;
}

/* L531: int radio475x_resume(void *) */
__maybe_unused int radio475x_resume(void *)
{
	return 0;
}

/* L637: int radio475x_seekcontrol(void *) */
__maybe_unused int radio475x_seekcontrol(void *)
{
	return 0;
}

/* L446: int radio475x_setforcemono(void *) */
__maybe_unused int radio475x_setforcemono(void *)
{
	return 0;
}

/* L437: int radio475x_setmute(void *) */
__maybe_unused int radio475x_setmute(void *)
{
	return 0;
}

/* L524: int radio475x_suspend(void *) */
__maybe_unused int radio475x_suspend(void *)
{
	return 0;
}

/* L423: int radio475x_tuneradio(void *) */
__maybe_unused int radio475x_tuneradio(void *)
{
	return 0;
}

/* L117: int radio_i2c_read_475x(struct i2c_client *, unsigned char *, int) */
__maybe_unused int radio_i2c_read_475x(struct i2c_client *, unsigned char *, int)
{
	return 0;
}

/* L168: int radio_i2c_write_475x(struct i2c_client *, unsigned char *, int) */
__maybe_unused int radio_i2c_write_475x(struct i2c_client *, unsigned char *, int)
{
	return 0;
}

/* L346: unsigned char Radio6851_CheckSeekLevel(unsigned int) */
__maybe_unused unsigned char Radio6851_CheckSeekLevel(unsigned int)
{
	return 0;
}

/* L262: unsigned char Radio6851_Mute(unsigned char) */
__maybe_unused unsigned char Radio6851_Mute(unsigned char)
{
	return 0;
}

/* L629: unsigned char Radio685x_CheckSeekLevel(unsigned int, unsigned int, unsigned char *) */
__maybe_unused unsigned char Radio685x_CheckSeekLevel(unsigned int, unsigned int, unsigned char *)
{
	return 0;
}

/* L359: unsigned int RadioSeek_685x(unsigned int, int) */
__maybe_unused unsigned int RadioSeek_685x(unsigned int, int)
{
	return 0;
}

/* L278: unsigned char RadioSetFreq_685x(unsigned int) */
__maybe_unused unsigned char RadioSetFreq_685x(unsigned int)
{
	return 0;
}

/* L313: void ResetNxp685x(void) */
__maybe_unused void ResetNxp685x(void)
{
	return;
}

/* L417: int SearchRadioNxp685x(struct i2c_client *, const struct i2c_device_id *) */
__maybe_unused int SearchRadioNxp685x(struct i2c_client *, const struct i2c_device_id *)
{
	return 0;
}

/* L890: int fm685x_getdefaultparama(void *) */
__maybe_unused int fm685x_getdefaultparama(void *)
{
	return 0;
}

/* L759: int fm685x_getrdsaflevel(void *) */
__maybe_unused int fm685x_getrdsaflevel(void *)
{
	return 0;
}

/* L911: int fm685x_getrdsblockdata(void *) */
__maybe_unused int fm685x_getrdsblockdata(void *)
{
	return 0;
}

/* L732: int fm685x_getrdsfixlevel(void *) */
__maybe_unused int fm685x_getrdsfixlevel(void *)
{
	return 0;
}

/* L570: int fm685x_getsubname(void *) */
__maybe_unused int fm685x_getsubname(void *)
{
	return 0;
}

/* L880: int fm685x_getsurportlist(void *) */
__maybe_unused int fm685x_getsurportlist(void *)
{
	return 0;
}

/* L898: int fm685x_rdsonoff(void *) */
__maybe_unused int fm685x_rdsonoff(void *)
{
	return 0;
}

/* L851: int fm685x_resume(void *) */
__maybe_unused int fm685x_resume(void *)
{
	return 0;
}

/* L846: int fm685x_suspend(void *) */
__maybe_unused int fm685x_suspend(void *)
{
	return 0;
}

/* L118: int isconfig_configdata(void) */
__maybe_unused int isconfig_configdata(void)
{
	return 0;
}

/* L122: int isconfig_configsubname(void) */
__maybe_unused int isconfig_configsubname(void)
{
	return 0;
}

/* L114: int isconfig_initdata(void) */
__maybe_unused int isconfig_initdata(void)
{
	return 0;
}

/* L110: int isconfig_surportlist(void) */
__maybe_unused int isconfig_surportlist(void)
{
	return 0;
}

/* L816: int nxp685x_esdcheck(void *) */
__maybe_unused int nxp685x_esdcheck(void *)
{
	return 0;
}

/* L554: int nxp685x_getrssi(void *) */
__maybe_unused int nxp685x_getrssi(void *)
{
	return 0;
}

/* L647: int nxp685x_getseekquality(void *) */
__maybe_unused int nxp685x_getseekquality(void *)
{
	return 0;
}

/* L841: int nxp685x_ioctlcheck(void *) */
__maybe_unused int nxp685x_ioctlcheck(void *)
{
	return 0;
}

/* L538: int nxp685x_issteromode(void *) */
__maybe_unused int nxp685x_issteromode(void *)
{
	return 0;
}

/* L499: int nxp685x_powerdown(void *) */
__maybe_unused int nxp685x_powerdown(void *)
{
	return 0;
}

/* L492: int nxp685x_powerup(void *) */
__maybe_unused int nxp685x_powerup(void *)
{
	return 0;
}

/* L438: int nxp685x_probeinit(void *) */
__maybe_unused int nxp685x_probeinit(void *)
{
	return 0;
}

/* L530: int nxp685x_setforcemono(void *) */
__maybe_unused int nxp685x_setforcemono(void *)
{
	return 0;
}

/* L518: int nxp685x_setmute(void *) */
__maybe_unused int nxp685x_setmute(void *)
{
	return 0;
}

/* L505: int nxp685x_tuneradio(void *) */
__maybe_unused int nxp685x_tuneradio(void *)
{
	return 0;
}

/* L78: int nxp_checkisusefullfw(plsec_radio_fw) */
__maybe_unused int nxp_checkisusefullfw(plsec_radio_fw)
{
	return 0;
}

/* L182: int radio_i2c_read_685x(struct i2c_client *, unsigned char *, int) */
__maybe_unused int radio_i2c_read_685x(struct i2c_client *, unsigned char *, int)
{
	return 0;
}

/* L233: int radio_i2c_write_685x(struct i2c_client *, unsigned char *, int) */
__maybe_unused int radio_i2c_write_685x(struct i2c_client *, unsigned char *, int)
{
	return 0;
}

/* L990: int sqlfm_getquality(void *) */
__maybe_unused int sqlfm_getquality(void *)
{
	return 0;
}

/* L184: void RadioSetFreq_tda7703(unsigned int) */
__maybe_unused void RadioSetFreq_tda7703(unsigned int)
{
	return;
}

/* L455: void ResetTda7703(void) */
__maybe_unused void ResetTda7703(void)
{
	return;
}

/* L239: int SearchRadiotda7703(struct i2c_client *, const struct i2c_device_id *) */
__maybe_unused int SearchRadiotda7703(struct i2c_client *, const struct i2c_device_id *)
{
	return 0;
}

/* L108: int radio_i2c_read_7703(struct i2c_client *, unsigned char *, int) */
__maybe_unused int radio_i2c_read_7703(struct i2c_client *, unsigned char *, int)
{
	return 0;
}

/* L159: int radio_i2c_write_7703(struct i2c_client *, unsigned char *, int) */
__maybe_unused int radio_i2c_write_7703(struct i2c_client *, unsigned char *, int)
{
	return 0;
}

/* L290: int tda7703_change_band(void *) */
__maybe_unused int tda7703_change_band(void *)
{
	return 0;
}

/* L461: int tda7703_esdcheck(void *) */
__maybe_unused int tda7703_esdcheck(void *)
{
	return 0;
}

/* L497: int tda7703_getdefaultparama(void *) */
__maybe_unused int tda7703_getdefaultparama(void *)
{
	return 0;
}

/* L555: int tda7703_getmodulename(void *) */
__maybe_unused int tda7703_getmodulename(void *)
{
	return 0;
}

/* L538: int tda7703_getrdsaflevel(void *) */
__maybe_unused int tda7703_getrdsaflevel(void *)
{
	return 0;
}

/* L421: int tda7703_getrdsblockdata(void *) */
__maybe_unused int tda7703_getrdsblockdata(void *)
{
	return 0;
}

/* L525: int tda7703_getrdsfixlevel(void *) */
__maybe_unused int tda7703_getrdsfixlevel(void *)
{
	return 0;
}

/* L378: int tda7703_getrssi(void *) */
__maybe_unused int tda7703_getrssi(void *)
{
	return 0;
}

/* L394: int tda7703_getseekquality(void *) */
__maybe_unused int tda7703_getseekquality(void *)
{
	return 0;
}

/* L332: int tda7703_getseekstatus(void *) */
__maybe_unused int tda7703_getseekstatus(void *)
{
	return 0;
}

/* L503: int tda7703_getsubname(void *) */
__maybe_unused int tda7703_getsubname(void *)
{
	return 0;
}

/* L490: int tda7703_getsurportlist(void *) */
__maybe_unused int tda7703_getsurportlist(void *)
{
	return 0;
}

/* L472: int tda7703_ioctlcheck(void *) */
__maybe_unused int tda7703_ioctlcheck(void *)
{
	return 0;
}

/* L372: int tda7703_issteromode(void *) */
__maybe_unused int tda7703_issteromode(void *)
{
	return 0;
}

/* L273: int tda7703_powerdown(void *) */
__maybe_unused int tda7703_powerdown(void *)
{
	return 0;
}

/* L267: int tda7703_powerup(void *) */
__maybe_unused int tda7703_powerup(void *)
{
	return 0;
}

/* L251: int tda7703_probeinit(void *) */
__maybe_unused int tda7703_probeinit(void *)
{
	return 0;
}

/* L510: int tda7703_rdsonoff(void *) */
__maybe_unused int tda7703_rdsonoff(void *)
{
	return 0;
}

/* L482: int tda7703_resume(void *) */
__maybe_unused int tda7703_resume(void *)
{
	return 0;
}

/* L305: int tda7703_seekcontrol(void *) */
__maybe_unused int tda7703_seekcontrol(void *)
{
	return 0;
}

/* L364: int tda7703_setforcemono(void *) */
__maybe_unused int tda7703_setforcemono(void *)
{
	return 0;
}

/* L355: int tda7703_setmute(void *) */
__maybe_unused int tda7703_setmute(void *)
{
	return 0;
}

/* L477: int tda7703_suspend(void *) */
__maybe_unused int tda7703_suspend(void *)
{
	return 0;
}

/* L279: int tda7703_tuneradio(void *) */
__maybe_unused int tda7703_tuneradio(void *)
{
	return 0;
}

/* L227: static void PowerOnAndReset7703(int) */
static void PowerOnAndReset7703(int);
static void PowerOnAndReset7703(int)
{
	return;
}

/* L245: void RadioSetFreq_tda7706(unsigned int) */
__maybe_unused void RadioSetFreq_tda7706(unsigned int)
{
	return;
}

/* L316: unsigned char RadioTdaGetType(struct i2c_client *) */
__maybe_unused unsigned char RadioTdaGetType(struct i2c_client *)
{
	return 0;
}

/* L298: unsigned char Radio_Check_7706_7703_ChipID(struct i2c_client *) */
__maybe_unused unsigned char Radio_Check_7706_7703_ChipID(struct i2c_client *)
{
	return 0;
}

/* L643: void ResetTda7706(void) */
__maybe_unused void ResetTda7706(void)
{
	return;
}

/* L393: int SearchRadiotda7706(struct i2c_client *, const struct i2c_device_id *) */
__maybe_unused int SearchRadiotda7706(struct i2c_client *, const struct i2c_device_id *)
{
	return 0;
}

/* L168: int radio_i2c_read_7706(struct i2c_client *, unsigned char *, int) */
__maybe_unused int radio_i2c_read_7706(struct i2c_client *, unsigned char *, int)
{
	return 0;
}

/* L219: int radio_i2c_write_7706(struct i2c_client *, unsigned char *, int) */
__maybe_unused int radio_i2c_write_7706(struct i2c_client *, unsigned char *, int)
{
	return 0;
}

/* L478: int tda7706_change_band(void *) */
__maybe_unused int tda7706_change_band(void *)
{
	return 0;
}

/* L649: int tda7706_esdcheck(void *) */
__maybe_unused int tda7706_esdcheck(void *)
{
	return 0;
}

/* L701: int tda7706_getdefaultparama(void *) */
__maybe_unused int tda7706_getdefaultparama(void *)
{
	return 0;
}

/* L769: int tda7706_getmodulename(void *) */
__maybe_unused int tda7706_getmodulename(void *)
{
	return 0;
}

/* L751: int tda7706_getrdsaflevel(void *) */
__maybe_unused int tda7706_getrdsaflevel(void *)
{
	return 0;
}

/* L608: int tda7706_getrdsblockdata(void *) */
__maybe_unused int tda7706_getrdsblockdata(void *)
{
	return 0;
}

/* L737: int tda7706_getrdsfixlevel(void *) */
__maybe_unused int tda7706_getrdsfixlevel(void *)
{
	return 0;
}

/* L564: int tda7706_getrssi(void *) */
__maybe_unused int tda7706_getrssi(void *)
{
	return 0;
}

/* L580: int tda7706_getseekquality(void *) */
__maybe_unused int tda7706_getseekquality(void *)
{
	return 0;
}

/* L521: int tda7706_getseekstatus(void *) */
__maybe_unused int tda7706_getseekstatus(void *)
{
	return 0;
}

/* L708: int tda7706_getsubname(void *) */
__maybe_unused int tda7706_getsubname(void *)
{
	return 0;
}

/* L685: int tda7706_getsurportlist(void *) */
__maybe_unused int tda7706_getsurportlist(void *)
{
	return 0;
}

/* L667: int tda7706_ioctlcheck(void *) */
__maybe_unused int tda7706_ioctlcheck(void *)
{
	return 0;
}

/* L558: int tda7706_issteromode(void *) */
__maybe_unused int tda7706_issteromode(void *)
{
	return 0;
}

/* L462: int tda7706_powerdown(void *) */
__maybe_unused int tda7706_powerdown(void *)
{
	return 0;
}

/* L456: int tda7706_powerup(void *) */
__maybe_unused int tda7706_powerup(void *)
{
	return 0;
}

/* L436: int tda7706_probeinit(void *) */
__maybe_unused int tda7706_probeinit(void *)
{
	return 0;
}

/* L722: int tda7706_rdsonoff(void *) */
__maybe_unused int tda7706_rdsonoff(void *)
{
	return 0;
}

/* L677: int tda7706_resume(void *) */
__maybe_unused int tda7706_resume(void *)
{
	return 0;
}

/* L492: int tda7706_seekcontrol(void *) */
__maybe_unused int tda7706_seekcontrol(void *)
{
	return 0;
}

/* L551: int tda7706_setforcemono(void *) */
__maybe_unused int tda7706_setforcemono(void *)
{
	return 0;
}

/* L542: int tda7706_setmute(void *) */
__maybe_unused int tda7706_setmute(void *)
{
	return 0;
}

/* L672: int tda7706_suspend(void *) */
__maybe_unused int tda7706_suspend(void *)
{
	return 0;
}

/* L468: int tda7706_tuneradio(void *) */
__maybe_unused int tda7706_tuneradio(void *)
{
	return 0;
}

/* L112: int tda_checkisusefullfw(plsec_radio_fw) */
__maybe_unused int tda_checkisusefullfw(plsec_radio_fw)
{
	return 0;
}

/* L150: int tdaisconfig_configdata(void) */
__maybe_unused int tdaisconfig_configdata(void)
{
	return 0;
}

/* L146: int tdaisconfig_initdata(void) */
__maybe_unused int tdaisconfig_initdata(void)
{
	return 0;
}

/* L142: int tdaisconfig_surportlist(void) */
__maybe_unused int tdaisconfig_surportlist(void)
{
	return 0;
}

/* L289: static void PowerOnAndReset7706(int) */
static void PowerOnAndReset7706(int);
static void PowerOnAndReset7706(int)
{
	return;
}

/* L999: void BackgroundSeekOff(U8) */
__maybe_unused void BackgroundSeekOff(U8)
{
	return;
}

/* L950: void BackgroundSetFreq(U16) */
__maybe_unused void BackgroundSetFreq(U16)
{
	return;
}

/* L912: void LsecRadioChangeBand(unsigned char, unsigned int, U32, U32, U32) */
__maybe_unused void LsecRadioChangeBand(unsigned char, unsigned int, U32, U32, U32)
{
	return;
}

/* L1435: int RDSFetchBlockData7707(unsigned short *, unsigned short *, unsigned short *, unsigned short *) */
__maybe_unused int RDSFetchBlockData7707(unsigned short *, unsigned short *, unsigned short *, unsigned short *)
{
	return 0;
}

/* L205: void Radio7707_Mute(unsigned char) */
__maybe_unused void Radio7707_Mute(unsigned char)
{
	return;
}

/* L434: void RadioSetFreq_7707(unsigned int) */
__maybe_unused void RadioSetFreq_7707(unsigned int)
{
	return;
}

/* L696: void ResetTda7707(void) */
__maybe_unused void ResetTda7707(void)
{
	return;
}

/* L126: int radio_i2c_read_7707(struct i2c_client *, unsigned char *, int) */
__maybe_unused int radio_i2c_read_7707(struct i2c_client *, unsigned char *, int)
{
	return 0;
}

/* L176: int radio_i2c_write_7707(struct i2c_client *, unsigned char *, int) */
__maybe_unused int radio_i2c_write_7707(struct i2c_client *, unsigned char *, int)
{
	return 0;
}

/* L1546: int tda7707_DualTunerControl(void *) */
__maybe_unused int tda7707_DualTunerControl(void *)
{
	return 0;
}

/* L926: int tda7707_change_band(void *) */
__maybe_unused int tda7707_change_band(void *)
{
	return 0;
}

/* L700: int tda7707_esdcheck(void *) */
__maybe_unused int tda7707_esdcheck(void *)
{
	return 0;
}

/* L740: int tda7707_getdefaultparama(void *) */
__maybe_unused int tda7707_getdefaultparama(void *)
{
	return 0;
}

/* L1510: int tda7707_getmodulename(void *) */
__maybe_unused int tda7707_getmodulename(void *)
{
	return 0;
}

/* L872: int tda7707_getrdsaflevel(void *) */
__maybe_unused int tda7707_getrdsaflevel(void *)
{
	return 0;
}

/* L1475: int tda7707_getrdsblockdata(void *) */
__maybe_unused int tda7707_getrdsblockdata(void *)
{
	return 0;
}

/* L772: int tda7707_getrdsfixlevel(void *) */
__maybe_unused int tda7707_getrdsfixlevel(void *)
{
	return 0;
}

/* L648: int tda7707_getrssi(void *) */
__maybe_unused int tda7707_getrssi(void *)
{
	return 0;
}

/* L664: int tda7707_getseekquality(void *) */
__maybe_unused int tda7707_getseekquality(void *)
{
	return 0;
}

/* L1144: int tda7707_getseekstatus(void *) */
__maybe_unused int tda7707_getseekstatus(void *)
{
	return 0;
}

/* L747: int tda7707_getsubname(void *) */
__maybe_unused int tda7707_getsubname(void *)
{
	return 0;
}

/* L606: int tda7707_getsurportlist(void *) */
__maybe_unused int tda7707_getsurportlist(void *)
{
	return 0;
}

/* L723: int tda7707_ioctlcheck(void *) */
__maybe_unused int tda7707_ioctlcheck(void *)
{
	return 0;
}

/* L634: int tda7707_issteromode(void *) */
__maybe_unused int tda7707_issteromode(void *)
{
	return 0;
}

/* L587: int tda7707_powerdown(void *) */
__maybe_unused int tda7707_powerdown(void *)
{
	return 0;
}

/* L581: int tda7707_powerup(void *) */
__maybe_unused int tda7707_powerup(void *)
{
	return 0;
}

/* L509: int tda7707_probeinit(void *) */
__maybe_unused int tda7707_probeinit(void *)
{
	return 0;
}

/* L1164: int tda7707_rdsonoff(void *) */
__maybe_unused int tda7707_rdsonoff(void *)
{
	return 0;
}

/* L733: int tda7707_resume(void *) */
__maybe_unused int tda7707_resume(void *)
{
	return 0;
}

/* L1110: int tda7707_seekcontrol(void *) */
__maybe_unused int tda7707_seekcontrol(void *)
{
	return 0;
}

/* L624: int tda7707_setforcemono(void *) */
__maybe_unused int tda7707_setforcemono(void *)
{
	return 0;
}

/* L616: int tda7707_setmute(void *) */
__maybe_unused int tda7707_setmute(void *)
{
	return 0;
}

/* L728: int tda7707_suspend(void *) */
__maybe_unused int tda7707_suspend(void *)
{
	return 0;
}

/* L592: int tda7707_tuneradio(void *) */
__maybe_unused int tda7707_tuneradio(void *)
{
	return 0;
}

/* L1187: static void RDSDataPushToGroup(eTuner_Channel) */
static void RDSDataPushToGroup(eTuner_Channel);
static void RDSDataPushToGroup(eTuner_Channel)
{
	return;
}

/* L250: U8 ChangFreq16BitTo8Bit(U16) */
__maybe_unused U8 ChangFreq16BitTo8Bit(U16)
{
	return 0;
}

/* L262: U16 ChangFreq8BitTo16Bit(U8) */
__maybe_unused U16 ChangFreq8BitTo16Bit(U8)
{
	return 0;
}

/* L273: U32 ChangFreq8BitTo32Bit(unsigned short) */
__maybe_unused U32 ChangFreq8BitTo32Bit(unsigned short)
{
	return 0;
}

/* L999: void RDSAFCheck(eTuner_Channel, unsigned short) */
__maybe_unused void RDSAFCheck(eTuner_Channel, unsigned short)
{
	return;
}

/* L1439: void RDSBufferFetchBlocks(eTuner_Channel) */
__maybe_unused void RDSBufferFetchBlocks(eTuner_Channel)
{
	return;
}

/* L224: void RDSBufferInit(eTuner_Channel, U8) */
__maybe_unused void RDSBufferInit(eTuner_Channel, U8)
{
	return;
}

/* L1315: void RDSDataProcessBlock(eTuner_Channel) */
__maybe_unused void RDSDataProcessBlock(eTuner_Channel)
{
	return;
}

/* L1229: void RDSDataPushToGroup(eTuner_Channel) */
__maybe_unused void RDSDataPushToGroup(eTuner_Channel)
{
	return;
}

/* L1478: int RDSFetchBlockData7708(unsigned short *, unsigned short *, unsigned short *, unsigned short *) */
__maybe_unused int RDSFetchBlockData7708(unsigned short *, unsigned short *, unsigned short *, unsigned short *)
{
	return 0;
}

/* L896: signed char RDSGetSMeter(void) */
__maybe_unused signed char RDSGetSMeter(void)
{
	return 0;
}

/* L939: signed char RDSReadQualityFromBuffer(void) */
__maybe_unused signed char RDSReadQualityFromBuffer(void)
{
	return 0;
}

/* L975: signed char RDSReadSmeterQuality(eTuner_Channel) */
__maybe_unused signed char RDSReadSmeterQuality(eTuner_Channel)
{
	return 0;
}

/* L203: void Radio7708_Mute(unsigned char) */
__maybe_unused void Radio7708_Mute(unsigned char)
{
	return;
}

/* L425: void RadioSetFreq_7708(unsigned int) */
__maybe_unused void RadioSetFreq_7708(unsigned int)
{
	return;
}

/* L688: void ResetTda7708(void) */
__maybe_unused void ResetTda7708(void)
{
	return;
}

/* L127: int radio_i2c_read_7708(struct i2c_client *, unsigned char *, int) */
__maybe_unused int radio_i2c_read_7708(struct i2c_client *, unsigned char *, int)
{
	return 0;
}

/* L177: int radio_i2c_write_7708(struct i2c_client *, unsigned char *, int) */
__maybe_unused int radio_i2c_write_7708(struct i2c_client *, unsigned char *, int)
{
	return 0;
}

/* L1044: int tda7708_change_band(void *) */
__maybe_unused int tda7708_change_band(void *)
{
	return 0;
}

/* L812: int tda7708_esdcheck(void *) */
__maybe_unused int tda7708_esdcheck(void *)
{
	return 0;
}

/* L854: int tda7708_getdefaultparama(void *) */
__maybe_unused int tda7708_getdefaultparama(void *)
{
	return 0;
}

/* L1575: int tda7708_getmodulename(void *) */
__maybe_unused int tda7708_getmodulename(void *)
{
	return 0;
}

/* L1007: int tda7708_getrdsaflevel(void *) */
__maybe_unused int tda7708_getrdsaflevel(void *)
{
	return 0;
}

/* L1541: int tda7708_getrdsblockdata(void *) */
__maybe_unused int tda7708_getrdsblockdata(void *)
{
	return 0;
}

/* L904: int tda7708_getrdsfixlevel(void *) */
__maybe_unused int tda7708_getrdsfixlevel(void *)
{
	return 0;
}

/* L640: int tda7708_getrssi(void *) */
__maybe_unused int tda7708_getrssi(void *)
{
	return 0;
}

/* L656: int tda7708_getseekquality(void *) */
__maybe_unused int tda7708_getseekquality(void *)
{
	return 0;
}

/* L1186: int tda7708_getseekstatus(void *) */
__maybe_unused int tda7708_getseekstatus(void *)
{
	return 0;
}

/* L879: int tda7708_getsubname(void *) */
__maybe_unused int tda7708_getsubname(void *)
{
	return 0;
}

/* L596: int tda7708_getsurportlist(void *) */
__maybe_unused int tda7708_getsurportlist(void *)
{
	return 0;
}

/* L835: int tda7708_ioctlcheck(void *) */
__maybe_unused int tda7708_ioctlcheck(void *)
{
	return 0;
}

/* L624: int tda7708_issteromode(void *) */
__maybe_unused int tda7708_issteromode(void *)
{
	return 0;
}

/* L578: int tda7708_powerdown(void *) */
__maybe_unused int tda7708_powerdown(void *)
{
	return 0;
}

/* L572: int tda7708_powerup(void *) */
__maybe_unused int tda7708_powerup(void *)
{
	return 0;
}

/* L500: int tda7708_probeinit(void *) */
__maybe_unused int tda7708_probeinit(void *)
{
	return 0;
}

/* L1206: int tda7708_rdsonoff(void *) */
__maybe_unused int tda7708_rdsonoff(void *)
{
	return 0;
}

/* L845: int tda7708_resume(void *) */
__maybe_unused int tda7708_resume(void *)
{
	return 0;
}

/* L1165: int tda7708_seekcontrol(void *) */
__maybe_unused int tda7708_seekcontrol(void *)
{
	return 0;
}

/* L614: int tda7708_setforcemono(void *) */
__maybe_unused int tda7708_setforcemono(void *)
{
	return 0;
}

/* L606: int tda7708_setmute(void *) */
__maybe_unused int tda7708_setmute(void *)
{
	return 0;
}

/* L840: int tda7708_suspend(void *) */
__maybe_unused int tda7708_suspend(void *)
{
	return 0;
}

/* L583: int tda7708_tuneradio(void *) */
__maybe_unused int tda7708_tuneradio(void *)
{
	return 0;
}

/* L446: void G35RadioReset(void) */
__maybe_unused void G35RadioReset(void)
{
	return;
}

/* L140: void GF35_read_data(u8, u16 *) */
__maybe_unused void GF35_read_data(u8, u16 *)
{
	return;
}

/* L117: void GF35_write_data(u8, u16) */
__maybe_unused void GF35_write_data(u8, u16)
{
	return;
}

/* L577: int g35_change_band(void *) */
__maybe_unused int g35_change_band(void *)
{
	return 0;
}

/* L482: int g35_esdcheck(void *) */
__maybe_unused int g35_esdcheck(void *)
{
	return 0;
}

/* L550: int g35_getdefaultparama(void *) */
__maybe_unused int g35_getdefaultparama(void *)
{
	return 0;
}

/* L557: int g35_getmodulename(void *) */
__maybe_unused int g35_getmodulename(void *)
{
	return 0;
}

/* L389: int g35_getrssi(void *) */
__maybe_unused int g35_getrssi(void *)
{
	return 0;
}

/* L410: int g35_getseekquality(void *) */
__maybe_unused int g35_getseekquality(void *)
{
	return 0;
}

/* L320: int g35_getsteroinesd(void) */
__maybe_unused int g35_getsteroinesd(void)
{
	return 0;
}

/* L563: int g35_getsubname(void *) */
__maybe_unused int g35_getsubname(void *)
{
	return 0;
}

/* L540: int g35_getsurportlist(void *) */
__maybe_unused int g35_getsurportlist(void *)
{
	return 0;
}

/* L508: int g35_ioctlcheck(void *) */
__maybe_unused int g35_ioctlcheck(void *)
{
	return 0;
}

/* L351: int g35_issteromode(void *) */
__maybe_unused int g35_issteromode(void *)
{
	return 0;
}

/* L224: int g35_powerdown(void *) */
__maybe_unused int g35_powerdown(void *)
{
	return 0;
}

/* L202: int g35_powerup(void *) */
__maybe_unused int g35_powerup(void *)
{
	return 0;
}

/* L169: int g35_probeinit(void *) */
__maybe_unused int g35_probeinit(void *)
{
	return 0;
}

/* L632: int g35_release(void) */
__maybe_unused int g35_release(void)
{
	return 0;
}

/* L625: int g35_remove(void *) */
__maybe_unused int g35_remove(void *)
{
	return 0;
}

/* L525: int g35_resume(void *) */
__maybe_unused int g35_resume(void *)
{
	return 0;
}

/* L597: int g35_seekcontrol(void *) */
__maybe_unused int g35_seekcontrol(void *)
{
	return 0;
}

/* L308: int g35_setforcemono(void *) */
__maybe_unused int g35_setforcemono(void *)
{
	return 0;
}

/* L289: int g35_setmute(void *) */
__maybe_unused int g35_setmute(void *)
{
	return 0;
}

/* L514: int g35_suspend(void *) */
__maybe_unused int g35_suspend(void *)
{
	return 0;
}

/* L254: int g35_tuneradio(void *) */
__maybe_unused int g35_tuneradio(void *)
{
	return 0;
}

/* L44: int radio_g35_read(struct i2c_client *, unsigned char *, int) */
__maybe_unused int radio_g35_read(struct i2c_client *, unsigned char *, int)
{
	return 0;
}

/* L95: int radio_g35_write(struct i2c_client *, unsigned char *, int) */
__maybe_unused int radio_g35_write(struct i2c_client *, unsigned char *, int)
{
	return 0;
}

/* L270: int DisablePwm(void) */
__maybe_unused int DisablePwm(void)
{
	return 0;
}

/* L119: int DisablePwm_clk(void) */
__maybe_unused int DisablePwm_clk(void)
{
	return 0;
}

/* L191: int DisablePwm_pwm(void) */
__maybe_unused int DisablePwm_pwm(void)
{
	return 0;
}

/* L277: int EnablePwm(int) */
__maybe_unused int EnablePwm(int)
{
	return 0;
}

/* L124: int EnablePwm_clk(int) */
__maybe_unused int EnablePwm_clk(int)
{
	return 0;
}

/* L204: int EnablePwm_pwm(int) */
__maybe_unused int EnablePwm_pwm(int)
{
	return 0;
}

/* L258: int GetPwmDevice(struct i2c_client *) */
__maybe_unused int GetPwmDevice(struct i2c_client *)
{
	return 0;
}

/* L152: int GetPwmDevice_clk(struct i2c_client *) */
__maybe_unused int GetPwmDevice_clk(struct i2c_client *)
{
	return 0;
}

/* L176: int GetPwmDevice_pwm(struct i2c_client *) */
__maybe_unused int GetPwmDevice_pwm(struct i2c_client *)
{
	return 0;
}

/* L623: int SearchRadio8035(struct i2c_client *, const struct i2c_device_id *) */
__maybe_unused int SearchRadio8035(struct i2c_client *, const struct i2c_device_id *)
{
	return 0;
}

/* L897: int count_seekoffset(unsigned int) */
__maybe_unused int count_seekoffset(unsigned int)
{
	return 0;
}

/* L909: int delay_checkCHSC(unsigned int) */
__maybe_unused int delay_checkCHSC(unsigned int)
{
	return 0;
}

/* L1284: int ls8035_change_band(void *) */
__maybe_unused int ls8035_change_band(void *)
{
	return 0;
}

/* L992: int ls8035_esdcheck(void *) */
__maybe_unused int ls8035_esdcheck(void *)
{
	return 0;
}

/* L1118: int ls8035_getdefaultparama(void *) */
__maybe_unused int ls8035_getdefaultparama(void *)
{
	return 0;
}

/* L1125: int ls8035_getmodulename(void *) */
__maybe_unused int ls8035_getmodulename(void *)
{
	return 0;
}

/* L1228: int ls8035_getrdsaflevel(void *) */
__maybe_unused int ls8035_getrdsaflevel(void *)
{
	return 0;
}

/* L1165: int ls8035_getrdsblockdata(void *) */
__maybe_unused int ls8035_getrdsblockdata(void *)
{
	return 0;
}

/* L1210: int ls8035_getrdsfixlevel(void *) */
__maybe_unused int ls8035_getrdsfixlevel(void *)
{
	return 0;
}

/* L877: int ls8035_getrssi(void *) */
__maybe_unused int ls8035_getrssi(void *)
{
	return 0;
}

/* L926: int ls8035_getseekquality(void *) */
__maybe_unused int ls8035_getseekquality(void *)
{
	return 0;
}

/* L1131: int ls8035_getsubname(void *) */
__maybe_unused int ls8035_getsubname(void *)
{
	return 0;
}

/* L1104: int ls8035_getsurportlist(void *) */
__maybe_unused int ls8035_getsurportlist(void *)
{
	return 0;
}

/* L1065: int ls8035_ioctlcheck(void *) */
__maybe_unused int ls8035_ioctlcheck(void *)
{
	return 0;
}

/* L826: int ls8035_issteromode(void *) */
__maybe_unused int ls8035_issteromode(void *)
{
	return 0;
}

/* L730: int ls8035_powerdown(void *) */
__maybe_unused int ls8035_powerdown(void *)
{
	return 0;
}

/* L710: int ls8035_powerup(void *) */
__maybe_unused int ls8035_powerup(void *)
{
	return 0;
}

/* L678: int ls8035_probeinit(void *) */
__maybe_unused int ls8035_probeinit(void *)
{
	return 0;
}

/* L252: void ls8035_pwm_init(void) */
__maybe_unused void ls8035_pwm_init(void)
{
	return;
}

/* L110: void ls8035_pwm_init_clk(void) */
__maybe_unused void ls8035_pwm_init_clk(void)
{
	return;
}

/* L165: void ls8035_pwm_init_pwm(void) */
__maybe_unused void ls8035_pwm_init_pwm(void)
{
	return;
}

/* L1147: int ls8035_rdsonoff(void *) */
__maybe_unused int ls8035_rdsonoff(void *)
{
	return 0;
}

/* L1339: int ls8035_release(void) */
__maybe_unused int ls8035_release(void)
{
	return 0;
}

/* L1331: int ls8035_remove(void *) */
__maybe_unused int ls8035_remove(void *)
{
	return 0;
}

/* L1089: int ls8035_resume(void *) */
__maybe_unused int ls8035_resume(void *)
{
	return 0;
}

/* L1304: int ls8035_seekcontrol(void *) */
__maybe_unused int ls8035_seekcontrol(void *)
{
	return 0;
}

/* L817: int ls8035_setforcemono(void *) */
__maybe_unused int ls8035_setforcemono(void *)
{
	return 0;
}

/* L798: int ls8035_setmute(void *) */
__maybe_unused int ls8035_setmute(void *)
{
	return 0;
}

/* L1078: int ls8035_suspend(void *) */
__maybe_unused int ls8035_suspend(void *)
{
	return 0;
}

/* L757: int ls8035_tuneradio(void *) */
__maybe_unused int ls8035_tuneradio(void *)
{
	return 0;
}

/* L536: int radio_i2c_read(struct i2c_client *, unsigned char *, int) */
__maybe_unused int radio_i2c_read(struct i2c_client *, unsigned char *, int)
{
	return 0;
}

/* L590: int radio_i2c_write(struct i2c_client *, unsigned char *, int) */
__maybe_unused int radio_i2c_write(struct i2c_client *, unsigned char *, int)
{
	return 0;
}

/* L284: int setpwmclock(unsigned int) */
__maybe_unused int setpwmclock(unsigned int)
{
	return 0;
}

/* L1390: int sqlfm_getCHSC(void *) */
__maybe_unused int sqlfm_getCHSC(void *)
{
	return 0;
}

/* L1378: int sqlfm_getRXCCA(void *) */
__maybe_unused int sqlfm_getRXCCA(void *)
{
	return 0;
}

/* L1402: int sqlfm_getsnr(void *) */
__maybe_unused int sqlfm_getsnr(void *)
{
	return 0;
}

/* L1783: int RDSFetchBlockData7703(unsigned short *, unsigned short *, unsigned short *, unsigned short *) */
__maybe_unused int RDSFetchBlockData7703(unsigned short *, unsigned short *, unsigned short *, unsigned short *)
{
	return 0;
}

/* L1545: void Radio7703_Mute(unsigned char) */
__maybe_unused void Radio7703_Mute(unsigned char)
{
	return;
}

/* L34: int formatwritebuff(unsigned char, unsigned char, unsigned char, unsigned char *) */
__maybe_unused int formatwritebuff(unsigned char, unsigned char, unsigned char, unsigned char *)
{
	return 0;
}

/* L1205: static void HIT_Change_Band(unsigned char, unsigned int, unsigned int, unsigned char) */
static void HIT_Change_Band(unsigned char, unsigned int, unsigned int, unsigned char);
static void HIT_Change_Band(unsigned char, unsigned int, unsigned int, unsigned char)
{
	return;
}

/* L691: static void HIT_CmdSetFEReg(unsigned char, unsigned char, unsigned char) */
static void HIT_CmdSetFEReg(unsigned char, unsigned char, unsigned char);
static void HIT_CmdSetFEReg(unsigned char, unsigned char, unsigned char)
{
	return;
}

/* L893: static void HIT_CmdWaitIdle(unsigned short) */
static void HIT_CmdWaitIdle(unsigned short);
static void HIT_CmdWaitIdle(unsigned short)
{
	return;
}

/* L905: static void HIT_CmdWriteBeCoeff(unsigned char *) */
static void HIT_CmdWriteBeCoeff(unsigned char *);
static void HIT_CmdWriteBeCoeff(unsigned char *)
{
	return;
}

/* L380: static unsigned char HIT_CmdWriteRead(unsigned char, unsigned char, unsigned char) */
static unsigned char HIT_CmdWriteRead(unsigned char, unsigned char, unsigned char);
static unsigned char HIT_CmdWriteRead(unsigned char, unsigned char, unsigned char)
{
	return 0;
}

/* L622: static void HIT_ForeceMono(unsigned char) */
static void HIT_ForeceMono(unsigned char);
static void HIT_ForeceMono(unsigned char)
{
	return;
}

/* L550: static void HIT_GetCFQuality(unsigned char, int) */
static void HIT_GetCFQuality(unsigned char, int);
static void HIT_GetCFQuality(unsigned char, int)
{
	return;
}

/* L2013: static void RDSHITRead(unsigned int, unsigned char *, unsigned char) */
static void RDSHITRead(unsigned int, unsigned char *, unsigned char);
static void RDSHITRead(unsigned int, unsigned char *, unsigned char)
{
	return;
}

/* L2289: unsigned char GetRDSAF_Level(unsigned int) */
__maybe_unused unsigned char GetRDSAF_Level(unsigned int)
{
	return 0;
}

/* L2258: unsigned char GetRDSFix_Level(void) */
__maybe_unused unsigned char GetRDSFix_Level(void)
{
	return 0;
}

/* L930: unsigned char HIT_BootcodeDownload(void) */
__maybe_unused unsigned char HIT_BootcodeDownload(void)
{
	return 0;
}

/* L897: unsigned char HIT_BootcodeDownload_cfg(unsigned char *) */
__maybe_unused unsigned char HIT_BootcodeDownload_cfg(unsigned char *)
{
	return 0;
}

/* L1308: void HIT_Change_Band(unsigned char, unsigned int, unsigned int, unsigned char) */
__maybe_unused void HIT_Change_Band(unsigned char, unsigned int, unsigned int, unsigned char)
{
	return;
}

/* L1278: void HIT_CmdMuSICA(unsigned char) */
__maybe_unused void HIT_CmdMuSICA(unsigned char)
{
	return;
}

/* L565: unsigned char HIT_CmdReadMem(unsigned int, unsigned char) */
__maybe_unused unsigned char HIT_CmdReadMem(unsigned int, unsigned char)
{
	return 0;
}

/* L1761: unsigned char HIT_CmdReadSeekStatus(struct sqlfm_seek_parm *) */
__maybe_unused unsigned char HIT_CmdReadSeekStatus(struct sqlfm_seek_parm *)
{
	return 0;
}

/* L1010: void HIT_CmdReadTDSR(void) */
__maybe_unused void HIT_CmdReadTDSR(void)
{
	return;
}

/* L1721: void HIT_CmdSeekEnd(unsigned char) */
__maybe_unused void HIT_CmdSeekEnd(unsigned char)
{
	return;
}

/* L1177: void HIT_CmdSetBand(unsigned char, unsigned int, unsigned int, unsigned char) */
__maybe_unused void HIT_CmdSetBand(unsigned char, unsigned int, unsigned int, unsigned char)
{
	return;
}

/* L1264: void HIT_CmdSetDDC(void) */
__maybe_unused void HIT_CmdSetDDC(void)
{
	return;
}

/* L1660: void HIT_CmdSetDiss(unsigned char, unsigned char) */
__maybe_unused void HIT_CmdSetDiss(unsigned char, unsigned char)
{
	return;
}

/* L1620: void HIT_CmdSetFreq(unsigned int) */
__maybe_unused void HIT_CmdSetFreq(unsigned int)
{
	return;
}

/* L1704: void HIT_CmdStartManualSeek(int) */
__maybe_unused void HIT_CmdStartManualSeek(int)
{
	return;
}

/* L1045: void HIT_CmdWaitIdle(unsigned short) */
__maybe_unused void HIT_CmdWaitIdle(unsigned short)
{
	return;
}

/* L537: unsigned char HIT_CmdWriteMem(unsigned int, unsigned long) */
__maybe_unused unsigned char HIT_CmdWriteMem(unsigned int, unsigned long)
{
	return 0;
}

/* L473: unsigned char HIT_CmdWriteRead(unsigned char, unsigned char, unsigned char) */
__maybe_unused unsigned char HIT_CmdWriteRead(unsigned char, unsigned char, unsigned char)
{
	return 0;
}

/* L1270: void HIT_Cmd_IBOC_Blender(void) */
__maybe_unused void HIT_Cmd_IBOC_Blender(void)
{
	return;
}

/* L383: unsigned char HIT_DirectRead(struct i2c_client *, unsigned int, unsigned char) */
__maybe_unused unsigned char HIT_DirectRead(struct i2c_client *, unsigned int, unsigned char)
{
	return 0;
}

/* L321: unsigned char HIT_DirectWrite(struct i2c_client *, unsigned char, unsigned char, unsigned char) */
__maybe_unused unsigned char HIT_DirectWrite(struct i2c_client *, unsigned char, unsigned char, unsigned char)
{
	return 0;
}

/* L718: void HIT_ForeceMono(unsigned char) */
__maybe_unused void HIT_ForeceMono(unsigned char)
{
	return;
}

/* L646: void HIT_GetCFQuality(unsigned char, int) */
__maybe_unused void HIT_GetCFQuality(unsigned char, int)
{
	return;
}

/* L158: unsigned char HIT_ReadChipStatus(void) */
__maybe_unused unsigned char HIT_ReadChipStatus(void)
{
	return 0;
}

/* L458: void HIT_SetDataBuff345_24bit(unsigned int) */
__maybe_unused void HIT_SetDataBuff345_24bit(unsigned int)
{
	return;
}

/* L450: void HIT_SetDataBuff345_8bit(unsigned char) */
__maybe_unused void HIT_SetDataBuff345_8bit(unsigned char)
{
	return;
}

/* L1522: void HIT_Startup_Seq(void) */
__maybe_unused void HIT_Startup_Seq(void)
{
	return;
}

/* L735: unsigned char HIT_StereoIndicator(void) */
__maybe_unused unsigned char HIT_StereoIndicator(void)
{
	return 0;
}

/* L1976: void RDSDataInitPlus(void) */
__maybe_unused void RDSDataInitPlus(void)
{
	return;
}

/* L1985: int RDSFetchBlockData7706(unsigned short *, unsigned short *, unsigned short *, unsigned short *) */
__maybe_unused int RDSFetchBlockData7706(unsigned short *, unsigned short *, unsigned short *, unsigned short *)
{
	return 0;
}

/* L2241: void RDSHITRead(unsigned int, unsigned char *, unsigned char) */
__maybe_unused void RDSHITRead(unsigned int, unsigned char *, unsigned char)
{
	return;
}

/* L2215: void RDSHITWrite(unsigned int *, unsigned char) */
__maybe_unused void RDSHITWrite(unsigned int *, unsigned char)
{
	return;
}

/* L1683: void Radio7706_Mute(unsigned char) */
__maybe_unused void Radio7706_Mute(unsigned char)
{
	return;
}

/* L1752: void SeekOff(unsigned char) */
__maybe_unused void SeekOff(unsigned char)
{
	return;
}

/* L1741: void SeekOn(int) */
__maybe_unused void SeekOn(int)
{
	return;
}

/* L196: unsigned char TunerSubChipChecking(struct i2c_client *) */
__maybe_unused unsigned char TunerSubChipChecking(struct i2c_client *)
{
	return 0;
}

/* L124: int formatbootbuff(unsigned char, int, unsigned char *) */
__maybe_unused int formatbootbuff(unsigned char, int, unsigned char *)
{
	return 0;
}

/* L789: static void HIT_CmdSetFEReg(unsigned char, unsigned char, unsigned char) */
static void HIT_CmdSetFEReg(unsigned char, unsigned char, unsigned char);
static void HIT_CmdSetFEReg(unsigned char, unsigned char, unsigned char)
{
	return;
}

/* L1057: static void HIT_CmdWriteBeCoeff(unsigned char *) */
static void HIT_CmdWriteBeCoeff(unsigned char *);
static void HIT_CmdWriteBeCoeff(unsigned char *)
{
	return;
}

/* L218: static unsigned char HIT_ReadChip_ResetStatus(struct i2c_client *) */
static unsigned char HIT_ReadChip_ResetStatus(struct i2c_client *);
static unsigned char HIT_ReadChip_ResetStatus(struct i2c_client *)
{
	return 0;
}

/* L218: int DeInitRDS(void) */
__maybe_unused int DeInitRDS(void)
{
	return 0;
}

/* L182: int InitRDS(struct i2c_client *) */
__maybe_unused int InitRDS(struct i2c_client *)
{
	return 0;
}

/* L234: int isRdsOn(void) */
__maybe_unused int isRdsOn(void)
{
	return 0;
}

/* L347: int isrdsread_needexit(void) */
__maybe_unused int isrdsread_needexit(void)
{
	return 0;
}

/* L241: int sqlfm_disable_rds(int) */
__maybe_unused int sqlfm_disable_rds(int)
{
	return 0;
}

/* L280: int sqlfm_enable_rds(void) */
__maybe_unused int sqlfm_enable_rds(void)
{
	return 0;
}

/* L354: int sqlfm_rds_pause_start(int) */
__maybe_unused int sqlfm_rds_pause_start(int)
{
	return 0;
}

/* L323: int sqlfm_rdsonoff(void *) */
__maybe_unused int sqlfm_rdsonoff(void *)
{
	return 0;
}

/* L124: static void sqlfm_rds_handle(void *) */
static void sqlfm_rds_handle(void *);
static void sqlfm_rds_handle(void *)
{
	return;
}

/* L42: static void sqlfm_rds_work_func(struct work_struct *) */
static void sqlfm_rds_work_func(struct work_struct *);
static void sqlfm_rds_work_func(struct work_struct *)
{
	return;
}

static int __init mod_init(void)
{
	pr_info("nxp685x_fm.ko skeleton loaded\n");
	return 0;
}
static void __exit mod_exit(void)
{
}
module_init(mod_init);
module_exit(mod_exit);
MODULE_LICENSE("GPL");
