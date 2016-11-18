@rem Build firmware, using following Post-build event command line, to get ni_fp1000_fw.h:
@rem cd $(SolutionDir)
@rem NI_FW_Encryptor-crc20pages.exe "$(OutputDirectory)\$(OutputFileName).bin"

del ni_fp1000_fw.h
copy C:\Proj\firmware\Firmware-Raw\NI_FP1000\Debug\ni_fp1000_fw.h .
