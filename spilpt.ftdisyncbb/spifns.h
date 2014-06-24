#ifndef SPIFNS_H
#define SPIFNS_H

#ifdef DLLEXPORT
# undef DLLEXPORT
#endif
#define DLLEXPORT  /* Empty */

#ifdef __cplusplus
extern "C" {
#endif

#define SPIFNS_VERSION 259

/* From BlueSuiteSource_V2_5.zip/CSRSource/result/include/spi/spi_common.h */

// Pre BC7 chips have version at this address
#define GBL_CHIP_VERSION_GEN1_ADDR  0xFF9A
// Unifi chips and post BC7 chips have version at this address
#define GBL_CHIP_VERSION_GEN2_ADDR  0xFE81
// PreBC7 chips have a analogue version
#define GBL_ANA_VERSION_ID          0xFF7D

/* From BlueSuiteSource_V2_5.zip/CSRSource/result/include/chiputil/XapHelper.h */
/* Macros to extract version information bits */
#define DIGITAL_CHIP_VERSION(reg_ff9a) (((reg_ff9a) >> 8) & 0x1F)
#define CHIP_VERSION_FE81(reg_fe81) ((reg_fe81) & 0xFF)
#define CHIP_VARIANT_FE81(reg_fe81) ((reg_fe81) & 0x0F00)

/**
 * Retrieves the ana version id from the register content
 * @param anaVersion the content of the register
 */
#define CHIP_ANA_VERSION_ID(anaVersion) ((anaVersion) & 0x00FF)


/* From BlueSuiteSource_V2_5.zip/CSRSource/interface/host/io/chipversions.h */
#if 0
typedef enum
{
    chip_bc01a = 0x01,
    chip_bc01b = 0x02,
    chip_bc02 = 0x03,
    chip_kato = 0x04,
    chip_kalimba = 0x05,
    chip_nicknack = 0x06,
    chip_paddywack = 0x07,
    chip_coyote = 0x08,
    chip_oddjob = 0x09,
    chip_pugwash = 0x0C,
    chip_stanley = 0x0D,
    chip_zebedee = 0x0E,
    chip_elvis = 0x10,
    chip_johnpeel = 0x11,
    chip_jumpinjack = 0x0F,
    chip_priscilla = 0x12,
    chip_herbie = 0x13,
    chip_fraggle = 0x14,
    chip_sugarlump = 0x15,
    chip_lisamarie = 0x16,
    chip_dash = 0x20,
    chip_jemima = 0x21,
    chip_cinderella = 0x22,
    chip_anastasia = 0x23
}
chipversion;
#endif
/* Continuation from BlueSuiteSource_V2_5.zip/CSRSource/result/include/chiputil/XapHelper.h */
#if 0
    RAW_CHIP_VERSION_LPC                = 0x24,
    RAW_CHIP_VERSION_OXY                = 0x27,
    RAW_CHIP_VERSION_GDN                = 0x28,
    RAW_CHIP_VERSION_GEM                = 0x29,
    RAW_CHIP_VERSION_NUT                = 0x2A,
    RAW_CHIP_VERSION_ROB                = 0x2B,
    RAW_CHIP_VERSION_LEO                = 0x2D,
    RAW_CHIP_VERSION_PUR                = 0x30,
    RAW_CHIP_VERSION_VGA                = 0x31,
    RAW_CHIP_VERSION_DAL                = 0x32,
    RAW_CHIP_VERSION_VUL                = 0x33,
    RAW_CHIP_VERSION_SS5                = 0x41,
    RAW_CHIP_VERSION_WAL                = 0x43,
    RAW_CHIP_VERSION_AMB                = 0x44,
#endif

/* From BlueSuiteSource_V2_5.zip/CSRSource/result/include/spi/spifns.h */

#define SPIFNS_SUCCESS (0)
#define SPIFNS_FAILURE (1)

/* Return type of spifns_bluecore_xap_stopped() and spifns_stream_bluecore_xap_stopped() */
enum spifns_xap_state
{
    SPIFNS_XAP_STOPPED = 1,
    SPIFNS_XAP_RUNNING = 0,
    SPIFNS_XAP_NO_REPLY = -1,
    SPIFNS_XAP_SPI_LOCKED = -2,
    SPIFNS_XAP_NOT_IMPL = -3,
};

enum spifns_spi_errors
{ 
    SPIFNS_ERROR_NO_ERROR  = 0x000, /* tests equal to SPIFNS_SUCCESS and PTTRANS_SUCCESS */
    SPIFNS_ERROR_GENERAL_FAILURE = SPIFNS_FAILURE, /* tests equal to SPIFNS_FAILURE and PTTRANS_FAILURE */
    /* the spifns error range is 0x100-0x1FF */
    SPIFNS_ERROR_MEMORY    = 0x101,
    SPIFNS_ERROR_CONNECT   = 0x102,
    SPIFNS_ERROR_READ_FAIL = 0x103, /* The checksum read from MISO after a read command was incorrect. */
    SPIFNS_ERROR_OS_ERROR  = 0x104,
    SPIFNS_ERROR_TOO_MANY_STREAMS = 0x105,
    SPIFNS_ERROR_INVALID_STREAM = 0x106,
    SPIFNS_ERROR_ALREADY_OPEN = 0x107,
    SPIFNS_ERROR_WRITE_FAIL = 0x108,
    SPIFNS_ERROR_INVALID_ADDRESS = 0x109,
    SPIFNS_ERROR_INVALID_PARAMETER = 0x10A,
    SPIFNS_ERROR_TIMEOUT   = 0x10B,
};  


#define SPIERR_NO_ERROR 0x100
#define SPIERR_MALLOC_FAILED 0x101
#define SPIERR_NO_LPT_PORT_SELECTED	0x102
#define SPIERR_READ_FAILED 0x103
#define SPIERR_IOCTL_FAILED 0x104

struct SPIVARDEF {
	const char *szName;
	const char *szDefault;
	int nUnknown;
};

struct SPISEQ {
	enum {
		TYPE_READ=0,
		TYPE_WRITE=1,
		TYPE_SETVAR=2
	} nType;
	union {
		struct {
			unsigned short nAddress;
			unsigned short nLength;
			unsigned short *pnData;
		} rw;
		struct {
			const char *szName;
			const char *szValue;
		} setvar;
	};
};

typedef void (__cdecl *spifns_enumerate_ports_callback)(unsigned int nPortNumber, const char *szPortName, void *pData);
typedef void (__cdecl *spifns_debug_callback)(const char *szDebug);

DLLEXPORT int __cdecl spifns_init(); //Return 0 on no error, negative on error
DLLEXPORT void __cdecl spifns_close();
DLLEXPORT void __cdecl spifns_getvarlist(const SPIVARDEF **ppList, unsigned int *pnCount);
DLLEXPORT const char * __cdecl spifns_getvar(const char *szName);
DLLEXPORT int __cdecl spifns_get_version(); //Should return 259
DLLEXPORT void __cdecl spifns_enumerate_ports(spifns_enumerate_ports_callback pCallback, void *pData);
#define CHIP_SELECT_XILINX      (0)
#define CHIP_SELECT_SPARTAN     (1)
#define CHIP_SELECT_NONE        (-1)
DLLEXPORT void __cdecl spifns_chip_select(int nUnknown);
DLLEXPORT const char* __cdecl spifns_command(const char *szCmd); //Return 0 on no error, or string on error.
/* returns the last error code, and if a pointer is passed in, the problematic address.*/
/* get_last_error and clear_last_error both deal with the error that occurred in the current thread */
DLLEXPORT unsigned int __cdecl spifns_get_last_error(unsigned short *pnErrorAddress, const char **szErrorString); //Returns where the error occured, or 0x100 for none
DLLEXPORT int __cdecl spifns_bluecore_xap_stopped(); //Returns -1 on error, 0 on XAP running, 1 on stopped
DLLEXPORT int __cdecl spifns_sequence(SPISEQ *pSequence, unsigned int nCount); //Return 0 on no error
DLLEXPORT void __cdecl spifns_set_debug_callback(spifns_debug_callback pCallback);


/* From BlueSuiteSource_V2_5.zip/CSRSource/result/include/spi/spifns.h
 * Included here for future reference. */

#if 0
SPIFNSDLL_API int spifns_stream_init(spifns_stream_t *p_stream);
SPIFNSDLL_API void spifns_stream_close(spifns_stream_t stream);
SPIFNSDLL_API unsigned int spifns_count_streams(void);
SPIFNSDLL_API int spifns_stream_sequence(spifns_stream_t stream, const SpiAction *seq, int length);
SPIFNSDLL_API int spifns_bccmd_init(uint16 slutid_spi_user_cmd,
                                    uint16 bccmd_spi_interface);
SPIFNSDLL_API int spifns_bccmd_cmd(uint16 *pdu, uint16 pdulen, int wait_for_result);
SPIFNSDLL_API int spifns_stream_bccmd_init(spifns_stream_t stream, uint16 slutid_spi_user_cmd,
                                           uint16 bccmd_spi_interface);
SPIFNSDLL_API int spifns_stream_bccmd_cmd(spifns_stream_t stream, uint16 *pdu, uint16 pdulen, int wait_for_result);
SPIFNSDLL_API const char* spifns_stream_command(spifns_stream_t stream, const char *command);
SPIFNSDLL_API const char* spifns_stream_getvar(spifns_stream_t stream, const char *var);
/* Returns an indication of SPI reliablity (0x0000 - Totally unreliable, 0x10000 - Totally reliable) */
SPIFNSDLL_API void spifns_get_reliablity(int *reliability);
SPIFNSDLL_API void spifns_stream_get_reliability(spifns_stream_t stream, int *reliability);
SPIFNSDLL_API void spifns_stream_chip_select(spifns_stream_t stream, int which);
SPIFNSDLL_API enum spifns_xap_state spifns_stream_bluecore_xap_stopped(spifns_stream_t stream);
/* select the subsystem id to send requests to. */
SPIFNSDLL_API int spifns_stream_select_subsystem(spifns_stream_t stream, unsigned int tb_sub_sys);
/* returns the last error code, and if a pointer is passed in, the problematic address.*/
/* get_last_error and clear_last_error both deal with the error that occurred in the current thread */
SPIFNSDLL_API int spifns_get_last_error32(uint32 *addr, const char ** buf);
SPIFNSDLL_API void spifns_clear_last_error(void);
SPIFNSDLL_API void spifns_stream_set_debug_callback(spifns_stream_t stream, SpiStreamDebugFn fn, void *pvcontext);
#define SPIFNS_MAX_DEVICE_ID_LEN 255
SPIFNSDLL_API int spifns_stream_get_device_id(spifns_stream_t stream, char *buf, size_t length);
SPIFNSDLL_API int spifns_stream_lock(spifns_stream_t stream, uint32 timeout);
SPIFNSDLL_API void spifns_stream_unlock(spifns_stream_t stream);
#endif /* 0 */

#ifdef __cplusplus
}   /* extern "C" */
#endif

#endif  /* SPIFNS_H */