
# OcQuirks

OcQuirks is a drop in replacement EFI driver for Clover that replaces AptioMemoryFix and all OsxAptioFix variants.  It is built against the OpenCore source tree, and supports OpenCore's quirks model.

## Prerequisites
The OcQuirks EFI driver has a dependency on FwRuntimeServices.efi, and they must be installed together in the CLOVER EFI drivers directory.  FwRuntimeServices.efi can be found in the release zip and is built along with OcQuirks.

## Installation
To install OcQuirks, download the latest release or build it using the instructions below and then install it into your EFI replacing any existing memory fix driver.

- Mount your EFI volume.
- Back your EFI volume up to a bootable USB drive and verify that it works.
- Remove AptioMemoryFix, and any OsxAptioFix variants from the Clover drivers folder on your EFI volume.
- Add OcQuirks.efi, FwRuntimeServices.efi, and OcQuirks.plist to the Clover drivers folder on your EFI volume.
- Reboot.

If your system has trouble booting, use your USB stick to boot back into macOS and revert by reversing the process.  Inspect the parameters below and configure OcQuirks.plist with parameters that better match your system.

Default settings are based on AptioMemoryFix and are designed with Intel 100, 200, and Z370 systems in mind. 
Other systems may require custom settings, (e.g., Z390 may need DevirtualiseMmio). It is also assumed that all slides are valid (no slide=X).

## Configuration
The parameters listed below can be changed by dropping in OcQuirks.plist into your Clover drivers folder. This can be found in either the release zip or the root of the OcQuirks repository. If no plist is found, then the defaults below are used.

|Quirk|Default Value|Description|
|---|---|---|
|AvoidRuntimeDefrag|True|Fix UEFI runtime services support on many firmwares.|
|DevirtualiseMmio|False|Reduce stolen memory footprint from memory map, incompatible with some systems|
|DisableSingleUser|False|A security option to ignore single user mode arguments.|
|DisableVariableWrite|False|A security option to protect macOS NVRAM write access.|
|DiscardHibernateMap|False|A legacy parameter to work around buggy memory maps.  Preserves runtime memory size and location after wake from S4 sleep.|
|EnableSafeModeSlide|True|Patch the bootloader to enable KASLR in safe mode.|
|EnableWriteUnprotector|True|Permits write access to UEFI runtime services code.|
|ForceExitBootServices|True|Ensures that calls to ExitBootServices succeed even with an outdated MemoryMap key.|
|ProtectCsmRegion|False|Prevents CSM memory regions from relocation or use.|
|ProtectSecureBoot|False|Protect UEFI Secure Boot variables from being written.|
|ProtectUefiServices|False|Protect UEFI services from being overridden by the firmware.|
|ProvideCustomSlide|True|Force macOS to use a pseudorandom value among available slide values.|
|SetupVirtualMap|True|Workaround issues in some firmwares that access memory after SetVirtualAddress calls often resulting in boot crashes.|
|ShrinkMemoryMap|False|Rarely needed on Haswell or newer, attempts to unify contiguous slots of similar types to prevent boot failures.|
|ProvideConsoleGopEnable|True|Install Graphics Output Protocol if missing from the console handle.|
|SignalAppleOS|False|This quirk is useful on Mac firmwares, which behave differently in different OS.|

For a more indepth description of quirks, review the [OpenCore Configuration Manual](https://github.com/acidanthera/OpenCorePkg/blob/master/Docs/Configuration.pdf).

## Building
Building OcQuirks is simple, you just need macOS and time.  You do not need to configure OcQuirks before building now, so all you need to do is follow the process below to build.

### Clone the Repository

```
$ git clone https://github.com/ReddestDream/OcQuirks.git
$ cd OcQuirks
```

### Build OcQuirks
Now build OcQuirks using the macbuild tool.  You may be prompted to install additional tools before compilation begins.

```
$ ./macbuild.tool
```

### Installation
Follow the installation procedures found earlier in the documentation, using the newly compiled version of OcQuirks which can be found in the OcQuirks/Binaries/RELEASE folder.

## Credits
- [Apple](https://www.apple.com) for macOS
- [vit9696](https://github.com/vit9696) for [OpenCore](https://github.com/acidanthera/OpenCorePkg/blob/master/README.md) and AptioMemoryFix
- [Download-Fritz](https://github.com/Download-Fritz) and [al3x](https://github.com/al3xtjames) for ideas and code contributions
- [CorpNewt](https://github.com/corpnewt) for the configuration scripts
