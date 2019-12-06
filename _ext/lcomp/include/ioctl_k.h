// ioctl defines for kernel driver win/linux

#ifndef _WINDLL

#define DIOC_SETUP                _IOWR(0x97,1,IOCTL_BUFFER)

/*
#define DIOC_SETEVENT \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 2, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
*/

#define DIOC_START                _IOWR(0x97,3,IOCTL_BUFFER)


#define DIOC_STOP                 _IOWR(0x97,4,IOCTL_BUFFER)


#define DIOC_OUTP                 _IOWR(0x97,5,IOCTL_BUFFER)

#define DIOC_INP                  _IOWR(0x97,6,IOCTL_BUFFER)

#define DIOC_OUTM                 _IOWR(0x97,7,IOCTL_BUFFER)

#define DIOC_INM                  _IOWR(0x97,8,IOCTL_BUFFER)

#define DIOC_SETBUFFER            _IOWR(0x97,9,IOCTL_BUFFER)

/*

#define DIOC_ADD_BOARDS \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 10, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define DIOC_CLEAR_BOARDS \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 11, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
*/    

#define DIOC_INIT_SYNC            _IOWR(0x97, 12,IOCTL_BUFFER)

/*
//
//#define DIOC_SETBUFFER_DAC \
//      CTL_CODE(FILE_DEVICE_UNKNOWN, 13, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
//

#define DIOC_SETEVENT_DAC \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 14, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define DIOC_SEND_COMMAND \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 15, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
*/

#define DIOC_SEND_COMMAND        _IOWR(0x97,15,IOCTL_BUFFER)

#define DIOC_COMMAND_PLX         _IOWR(0x97,16,IOCTL_BUFFER)


/*
#define DIOC_PUT_DATA_A \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 17, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_GET_DATA_A \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 18, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
*/

#define DIOC_PUT_DM_A           _IOWR(0x97,19,IOCTL_BUFFER)

#define DIOC_GET_DM_A           _IOWR(0x97,20,IOCTL_BUFFER)

#define DIOC_PUT_PM_A           _IOWR(0x97,21,IOCTL_BUFFER)

#define DIOC_GET_PM_A           _IOWR(0x97,22,IOCTL_BUFFER)

#define DIOC_GET_PARAMS         _IOWR(0x97, 23, IOCTL_BUFFER)

#define DIOC_SET_DSP_TYPE       _IOWR(0x97, 24, IOCTL_BUFFER)

#define DIOC_SETBUFFER_1        _IOWR(0x97, 25, IOCTL_BUFFER)


#define DIOC_SETUP_DAC          _IOWR(0x97, 26, IOCTL_BUFFER)

#define DIOC_READ_FLASH_WORD    _IOWR(0x97, 27, IOCTL_BUFFER)

#define DIOC_WRITE_FLASH_WORD   _IOWR(0x97, 28, IOCTL_BUFFER)

#define DIOC_ENABLE_FLASH_WRITE _IOWR(0x97, 29, IOCTL_BUFFER)

/*
#define DIOC_SETEVENT_1 \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 30, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_SETEVENT_2 \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 31, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_SETEVENT_3 \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 32, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_SETEVENT_4 \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 33, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_SETEVENT_5 \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 34, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
*/

#define DIOC_ADCSAMPLE              _IOWR(0x97, 35, IOCTL_BUFFER)

#define DIOC_LOAD_BIOS              _IOWR(0x97, 36, IOCTL_BUFFER)

#define DIOC_TTL_IN                 _IOWR(0x97, 37, IOCTL_BUFFER)
#define DIOC_TTL_OUT                _IOWR(0x97, 38, IOCTL_BUFFER)
#define DIOC_TTL_CFG                _IOWR(0x97, 39, IOCTL_BUFFER)
#define DIOC_DAC_OUT                _IOWR(0x97, 40, IOCTL_BUFFER)


#define DIOC_RESET_PLX              _IOWR(0x97, 41, IOCTL_BUFFER)

#define DIOC_WAIT_COMPLETE          _IOWR(0x97, 42, IOCTL_BUFFER)
#define DIOC_WAIT_COMPLETE_DAC      _IOWR(0x97, 43, IOCTL_BUFFER)

#define DIOC_SEND_BIOS              _IOWR(0x97, 44, IOCTL_BUFFER)

#define DIOC_WAIT_COMPLETE_ADC_OVF   _IOWR(0x97, 45, IOCTL_BUFFER)
#define DIOC_WAIT_COMPLETE_ADC_BUF   _IOWR(0x97, 46, IOCTL_BUFFER)
#define DIOC_WAIT_COMPLETE_DAC_UNF   _IOWR(0x97, 47, IOCTL_BUFFER)
#define DIOC_WAIT_COMPLETE_PWR       _IOWR(0x97, 48, IOCTL_BUFFER)

#else

#define DIOC_SETUP \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 1, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define DIOC_SETEVENT \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 2, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
        
#define DIOC_START \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 3, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define DIOC_STOP \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 4, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define DIOC_OUTP \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 5, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_INP \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 6, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define DIOC_OUTM \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 7, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_INM \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 8, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define DIOC_SETBUFFER \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 9, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define DIOC_ADD_BOARDS \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 10, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define DIOC_CLEAR_BOARDS \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 11, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define DIOC_INIT_SYNC \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 12, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
/*
#define DIOC_SETBUFFER_DAC \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 13, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
*/

#define DIOC_SETEVENT_DAC \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 14, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define DIOC_SEND_COMMAND \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 15, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define DIOC_COMMAND_PLX \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 16, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define DIOC_PUT_DATA_A \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 17, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_GET_DATA_A \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 18, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define DIOC_PUT_DM_A \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 19, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_GET_DM_A \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 20, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define DIOC_PUT_PM_A \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 21, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_GET_PM_A \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 22, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define DIOC_GET_PARAMS \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 23, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define DIOC_SET_DSP_TYPE \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 24, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define DIOC_SETBUFFER_1 \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 25, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define DIOC_SETUP_DAC \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 26, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define DIOC_READ_FLASH_WORD \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 27, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define DIOC_WRITE_FLASH_WORD \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 28, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_ENABLE_FLASH_WRITE \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 29, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_SETEVENT_1 \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 30, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_SETEVENT_2 \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 31, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_SETEVENT_3 \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 32, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_SETEVENT_4 \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 33, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_SETEVENT_5 \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 34, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_ADCSAMPLE \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 35, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define DIOC_LOAD_BIOS \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 36, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_TTL_IN \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 37, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define DIOC_TTL_OUT \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 38, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_TTL_CFG \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 39, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_DAC_OUT \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 40, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_RESET_PLX \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 41, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_SEND_BIOS \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 44, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_ENABLE_CORRECTION \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 50, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define DIOC_START_DAC \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 51, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

/*
#define DIOC_STOP_DAC \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 52, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define DIOC_INIT_SYNC_ADC \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 53, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define DIOC_INIT_SYNC_DAC \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 54, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
*/     

#define DIOC_ADC_CFG \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 55, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_DAC_CFG \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 56, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define DIOC_SETUP_DDS \
      CTL_CODE(FILE_DEVICE_UNKNOWN, 57, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)


// api from ldevusb
/*
#define DIOC_START \
   CTL_CODE (FILE_DEVICE_UNKNOWN,0x101,METHOD_OUT_DIRECT,FILE_ANY_ACCESS)

#define DIOC_STOP \
   CTL_CODE (FILE_DEVICE_UNKNOWN,0x102,METHOD_OUT_DIRECT,FILE_ANY_ACCESS)

#define DIOC_LOAD_BIOS_USB \
   CTL_CODE (FILE_DEVICE_UNKNOWN,0x103,METHOD_OUT_DIRECT,FILE_ANY_ACCESS)

#define DIOC_SEND_COMMAND \
   CTL_CODE (FILE_DEVICE_UNKNOWN,0x104,METHOD_OUT_DIRECT,FILE_ANY_ACCESS)
*/

#define DIOC_RESET_PIPE1 \
   CTL_CODE (FILE_DEVICE_UNKNOWN,0x105,METHOD_OUT_DIRECT,FILE_ANY_ACCESS)

#define DIOC_RESET_PIPE3 \
   CTL_CODE (FILE_DEVICE_UNKNOWN,0x106,METHOD_OUT_DIRECT,FILE_ANY_ACCESS)

#define DIOC_ABORT_PIPE1 \
   CTL_CODE (FILE_DEVICE_UNKNOWN,0x107,METHOD_OUT_DIRECT,FILE_ANY_ACCESS)

#define DIOC_ABORT_PIPE3 \
   CTL_CODE (FILE_DEVICE_UNKNOWN,0x108,METHOD_OUT_DIRECT,FILE_ANY_ACCESS)

#endif
