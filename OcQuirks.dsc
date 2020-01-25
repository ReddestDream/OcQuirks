## @file
# Copyright (C) 2017, vit9696.  All rights reserved.<BR>
#
# Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
##

[Defines]
  PLATFORM_NAME           = OcQuirks
  PLATFORM_GUID           = 4FBFC810-9D3C-4BF3-ABF5-89A793C235B1
  PLATFORM_VERSION        = 1.0
  SUPPORTED_ARCHITECTURES = X64
  BUILD_TARGETS           = RELEASE|DEBUG|NOOPT
  SKUID_IDENTIFIER        = DEFAULT
  DSC_SPECIFICATION       = 0x00010006

[LibraryClasses]
  BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
  BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
  DebugLib|OcSupportPkg/Library/OcDebugLogLib/OcDebugLogLib.inf
  DebugPrintErrorLevelLib|MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf
  DevicePathLib|MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf
  FileHandleLib|MdePkg/Library/UefiFileHandleLib/UefiFileHandleLib.inf
  IoLib|MdePkg/Library/BaseIoLibIntrinsic/BaseIoLibIntrinsic.inf
  MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
  OcAppleBootCompatLib|OcSupportPkg/Library/OcAppleBootCompatLib/OcAppleBootCompatLib.inf
  OcAppleBootPolicyLib|OcSupportPkg/Library/OcAppleBootPolicyLib/OcAppleBootPolicyLib.inf
  OcAppleChunklistLib|OcSupportPkg/Library/OcAppleChunklistLib/OcAppleChunklistLib.inf
  OcBootManagementLib|OcSupportPkg/Library/OcBootManagementLib/OcBootManagementLib.inf
  OcAppleDiskImageLib|OcSupportPkg/Library/OcAppleDiskImageLib/OcAppleDiskImageLib.inf
  OcAppleKeysLib|OcSupportPkg/Library/OcAppleKeysLib/OcAppleKeysLib.inf
  OcAppleKeyMapLib|OcSupportPkg/Library/OcAppleKeyMapLib/OcAppleKeyMapLib.inf
  OcAppleRamDiskLib|OcSupportPkg/Library/OcAppleRamDiskLib/OcAppleRamDiskLib.inf
  OcCompressionLib|OcSupportPkg/Library/OcCompressionLib/OcCompressionLib.inf
  OcCpuLib|OcSupportPkg/Library/OcCpuLib/OcCpuLib.inf
  OcCryptoLib|OcSupportPkg/Library/OcCryptoLib/OcCryptoLib.inf
  OcDataHubLib|OcSupportPkg/Library/OcDataHubLib/OcDataHubLib.inf
  OcDevicePathLib|OcSupportPkg/Library/OcDevicePathLib/OcDevicePathLib.inf
  OcDeviceTreeLib|OcSupportPkg/Library/OcDeviceTreeLib/OcDeviceTreeLib.inf
  OcFileLib|OcSupportPkg/Library/OcFileLib/OcFileLib.inf
  OcGuardLib|OcSupportPkg/Library/OcGuardLib/OcGuardLib.inf
  OcMachoLib|OcSupportPkg/Library/OcMachoLib/OcMachoLib.inf
  OcMemoryLib|OcSupportPkg/Library/OcMemoryLib/OcMemoryLib.inf
  OcMiscLib|OcSupportPkg/Library/OcMiscLib/OcMiscLib.inf
  OcOSInfoLib|OcSupportPkg/Library/OcOSInfoLib/OcOSInfoLib.inf
  OcRngLib|OcSupportPkg/Library/OcRngLib/OcRngLib.inf
  OcRtcLib|OcSupportPkg/Library/OcRtcLib/OcRtcLib.inf
  OcStringLib|OcSupportPkg/Library/OcStringLib/OcStringLib.inf
  OcTimerLib|OcSupportPkg/Library/OcTimerLib/OcTimerLib.inf
  OcTemplateLib|OcSupportPkg/Library/OcTemplateLib/OcTemplateLib.inf
  OcSerializeLib|OcSupportPkg/Library/OcSerializeLib/OcSerializeLib.inf
  OcStorageLib|OcSupportPkg/Library/OcStorageLib/OcStorageLib.inf
  OcXmlLib|OcSupportPkg/Library/OcXmlLib/OcXmlLib.inf
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  PciLib|MdePkg/Library/BasePciLibCf8/BasePciLibCf8.inf
  PciCf8Lib|MdePkg/Library/BasePciCf8Lib/BasePciCf8Lib.inf
  PlatformHookLib|MdeModulePkg/Library/BasePlatformHookLibNull/BasePlatformHookLibNull.inf
  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
  SerialPortLib|MdeModulePkg/Library/BaseSerialPortLib16550/BaseSerialPortLib16550.inf
  UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
  UefiDriverEntryPoint|MdePkg/Library/UefiDriverEntryPoint/UefiDriverEntryPoint.inf
  UefiLib|MdePkg/Library/UefiLib/UefiLib.inf
  UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf
  OcConsoleLib|OcSupportPkg/Library/OcConsoleLib/OcConsoleLib.inf

[Components]
  OcQuirks/Platform/OcQuirks/OcQuirks.inf
  OcSupportPkg/Platform/FwRuntimeServices/FwRuntimeServices.inf

[PcdsFixedAtBuild]
  gEfiMdePkgTokenSpaceGuid.PcdMaximumAsciiStringLength|0
!if $(TARGET) == RELEASE
  # DEBUG_PRINT_ENABLED
  gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|2
  # DEBUG_ERROR | DEBUG_WARN
  gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|0x80000002
  gEfiMdePkgTokenSpaceGuid.PcdFixedDebugPrintErrorLevel|0x80000002
!else
  # DEBUG_ASSERT_ENABLED | DEBUG_PRINT_ENABLED | DEBUG_CODE_ENABLED | CLEAR_MEMORY_ENABLED | ASSERT_DEADLOOP_ENABLED
  gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x2f
  # DEBUG_ERROR | DEBUG_WARN | DEBUG_INFO
  gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|0x80000042
  gEfiMdePkgTokenSpaceGuid.PcdFixedDebugPrintErrorLevel|0x80000042
!endif

[BuildOptions]

  GCC:DEBUG_*_*_CC_FLAGS     = -D OC_TARGET_DEBUG=1
  GCC:NOOPT_*_*_CC_FLAGS     = -D OC_TARGET_NOOPT=1
  MSFT:DEBUG_*_*_CC_FLAGS    = -D OC_TARGET_DEBUG=1
  MSFT:NOOPT_*_*_CC_FLAGS    = -D OC_TARGET_NOOPT=1
  XCODE:DEBUG_*_*_CC_FLAGS   = -D OC_TARGET_DEBUG=1
  XCODE:NOOPT_*_*_CC_FLAGS   = -D OC_TARGET_NOOPT=1
  XCODE:RELEASE_*_*_CC_FLAGS = -D OC_TARGET_RELEASE=1 -Oz -flto
