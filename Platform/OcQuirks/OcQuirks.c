#include <Library/MemoryAllocationLib.h>
#include <Library/OcStorageLib.h>
#include <Library/OcSerializeLib.h>
#include <Library/OcTemplateLib.h>
#include <Library/OcAppleBootCompatLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include <Protocol/LoadedImage.h>
#include <Protocol/SimpleFileSystem.h>

#define ROOT_PATH   L"EFI\\CLOVER"
#define CONFIG_PATH L"drivers\\UEFI\\OcQuirks.plist"

#define MAX_DATA_SIZE 10000

#define OC_MMIO_WL_STRUCT_FIELDS(_, __) \
  _(BOOLEAN   , Enabled , , FALSE , ()) \
  _(UINT64    , Address , , 0     , ()) \
  _(OC_STRING , Comment , , OC_STRING_CONSTR ("", _, __), OC_DESTR (OC_STRING))
  OC_DECLARE (OC_MMIO_WL_STRUCT)

#define OC_MMIO_WL_ARRAY_FIELDS(_, __) \
  OC_ARRAY (OC_MMIO_WL_STRUCT, _, __)
  OC_DECLARE (OC_MMIO_WL_ARRAY)

#define OC_QUIRKS_FIELDS(_, __) \
  _(BOOLEAN , AvoidRuntimeDefrag      ,   , TRUE  ,()) \
  _(BOOLEAN , DevirtualiseMmio        ,   , FALSE ,()) \
  _(BOOLEAN , DisableSingleUser       ,   , FALSE ,()) \
  _(BOOLEAN , DisableVariableWrite    ,   , FALSE ,()) \
  _(BOOLEAN , DiscardHibernateMap     ,   , FALSE ,()) \
  _(BOOLEAN , EnableSafeModeSlide     ,   , TRUE  ,()) \
  _(BOOLEAN , EnableWriteUnprotector  ,   , TRUE  ,()) \
  _(BOOLEAN , ForceExitBootServices   ,   , TRUE  ,()) \
  _(OC_MMIO_WL_ARRAY , MmioWhitelist  ,   , OC_CONSTR2 (OC_MMIO_WL_ARRAY, _, __) , OC_DESTR (OC_MMIO_WL_ARRAY)) \
  _(BOOLEAN , ProtectCsmRegion        ,   , FALSE ,()) \
  _(BOOLEAN , ProvideConsoleGopEnable ,   , TRUE  ,()) \
  _(BOOLEAN , ProvideCustomSlide      ,   , TRUE  ,()) \
  _(BOOLEAN , SetupVirtualMap         ,   , TRUE  ,()) \
  _(BOOLEAN , ShrinkMemoryMap         ,   , FALSE ,()) \
  _(BOOLEAN , SignalAppleOS           ,   , FALSE ,())
  OC_DECLARE (OC_QUIRKS)

OC_STRUCTORS        (OC_MMIO_WL_STRUCT, ())
OC_ARRAY_STRUCTORS  (OC_MMIO_WL_ARRAY)
OC_STRUCTORS        (OC_QUIRKS, ())

STATIC
OC_SCHEMA
mMmioWhitelistEntry[] = {
  OC_SCHEMA_INTEGER_IN  ("Address", OC_MMIO_WL_STRUCT, Address),
  OC_SCHEMA_STRING_IN   ("Comment", OC_MMIO_WL_STRUCT, Comment),
  OC_SCHEMA_BOOLEAN_IN  ("Enabled", OC_MMIO_WL_STRUCT, Enabled),
};

STATIC
OC_SCHEMA
mMmioWhitelist = OC_SCHEMA_DICT (NULL, mMmioWhitelistEntry);

STATIC
OC_SCHEMA
mConfigNodes[] = {
  OC_SCHEMA_BOOLEAN_IN ("AvoidRuntimeDefrag"      , OC_QUIRKS, AvoidRuntimeDefrag),
  OC_SCHEMA_BOOLEAN_IN ("DevirtualiseMmio"        , OC_QUIRKS, DevirtualiseMmio),
  OC_SCHEMA_BOOLEAN_IN ("DisableSingleUser"       , OC_QUIRKS, DisableSingleUser),
  OC_SCHEMA_BOOLEAN_IN ("DisableVariableWrite"    , OC_QUIRKS, DisableVariableWrite),
  OC_SCHEMA_BOOLEAN_IN ("DiscardHibernateMap"     , OC_QUIRKS, DiscardHibernateMap),
  OC_SCHEMA_BOOLEAN_IN ("EnableSafeModeSlide"     , OC_QUIRKS, EnableSafeModeSlide),
  OC_SCHEMA_BOOLEAN_IN ("EnableWriteUnprotector"  , OC_QUIRKS, EnableWriteUnprotector),
  OC_SCHEMA_BOOLEAN_IN ("ForceExitBootServices"   , OC_QUIRKS, ForceExitBootServices),
  OC_SCHEMA_ARRAY_IN   ("MmioWhitelist"           , OC_QUIRKS, MmioWhitelist, &mMmioWhitelist),
  OC_SCHEMA_BOOLEAN_IN ("ProtectCsmRegion"        , OC_QUIRKS, ProtectCsmRegion),
  OC_SCHEMA_BOOLEAN_IN ("ProvideConsoleGopEnable" , OC_QUIRKS, ProvideConsoleGopEnable),
  OC_SCHEMA_BOOLEAN_IN ("ProvideCustomSlide"      , OC_QUIRKS, ProvideCustomSlide),
  OC_SCHEMA_BOOLEAN_IN ("SetupVirtualMap"         , OC_QUIRKS, SetupVirtualMap),
  OC_SCHEMA_BOOLEAN_IN ("ShrinkMemoryMap"         , OC_QUIRKS, ShrinkMemoryMap),
  OC_SCHEMA_BOOLEAN_IN ("SignalAppleOS"           , OC_QUIRKS, SignalAppleOS)
};

STATIC
OC_SCHEMA_INFO
mConfigInfo = {
  .Dict = {mConfigNodes, ARRAY_SIZE (mConfigNodes)}
};

STATIC
VOID
QuirksProvideConsoleGop (
  VOID
  )
{
  EFI_STATUS  Status;
  VOID        *Gop;

  Gop = NULL;
  Status = gBS->HandleProtocol (gST->ConsoleOutHandle, &gEfiGraphicsOutputProtocolGuid, &Gop);

  if (EFI_ERROR (Status)) {
    Status = gBS->LocateProtocol (&gEfiGraphicsOutputProtocolGuid, NULL, &Gop);
    if (!EFI_ERROR (Status)) {
      Status = gBS->InstallMultipleProtocolInterfaces (
                      &gST->ConsoleOutHandle,
                      &gEfiGraphicsOutputProtocolGuid,
                      Gop,
                      NULL
                     );
    }
  }
}

STATIC
BOOLEAN
QuirksProvideConfig (
  OUT OC_QUIRKS *Config,
  IN EFI_HANDLE Handle
  )
{
  EFI_STATUS                        Status;
  EFI_LOADED_IMAGE_PROTOCOL         *LoadedImage;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL   *FileSystem;
  OC_STORAGE_CONTEXT                Storage;
  CHAR8                             *ConfigData;
  UINT32                            ConfigDataSize;
  
  // Load SimpleFileSystem Protocol
  Status = gBS->HandleProtocol (
    Handle,
    &gEfiLoadedImageProtocolGuid,
    (VOID **) &LoadedImage
    );
  
  if (EFI_ERROR (Status)) {
    goto failLoadFS;
  }
  
  FileSystem = LocateFileSystem (
    LoadedImage->DeviceHandle,
    LoadedImage->FilePath
    );
  
  if (FileSystem == NULL) {
    goto failLoadFS;
  }
  
  // Init OcStorage as it already handles
  // reading Unicode files
  Status = OcStorageInitFromFs (
    &Storage,
    FileSystem,
    ROOT_PATH,
    NULL
    );
  
  if (EFI_ERROR (Status)) {
    goto failInitStorage;
  }
  
  ConfigData = OcStorageReadFileUnicode (
    &Storage,
    CONFIG_PATH,
    &ConfigDataSize
    );
  
  // If no config data or greater than max size, fail and use defaults
  if(!ConfigDataSize || ConfigDataSize > MAX_DATA_SIZE) {
    goto failGetConfig;
  }
  
  BOOLEAN Success = ParseSerialized (Config, &mConfigInfo, ConfigData, ConfigDataSize);
  
  gBS->FreePool(&Status);
  gBS->FreePool(ConfigData);
  gBS->FreePool(&ConfigDataSize);
  gBS->FreePool(&Storage);
  
  return Success;

failGetConfig:
  gBS->FreePool(ConfigData);
  gBS->FreePool(&ConfigDataSize);
failInitStorage:
  gBS->FreePool(&Storage);
failLoadFS:
  gBS->FreePool(&Status);
  
  return FALSE;
}

EFI_STATUS
EFIAPI
QuirksEntryPoint (
  IN EFI_HANDLE        Handle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  OC_QUIRKS Config;
  
  OC_QUIRKS_CONSTRUCT (&Config, sizeof (Config));
  QuirksProvideConfig(&Config, Handle);
    
  OC_ABC_SETTINGS AbcSettings = {
  
    .AvoidRuntimeDefrag	    = Config.AvoidRuntimeDefrag,
    .SetupVirtualMap        = Config.SetupVirtualMap,
    .ProvideCustomSlide     = Config.ProvideCustomSlide,
    .DevirtualiseMmio       = Config.DevirtualiseMmio,
    .DisableSingleUser      = Config.DisableSingleUser,
    .DiscardHibernateMap    = Config.DiscardHibernateMap,
    .EnableSafeModeSlide    = Config.EnableSafeModeSlide,
    .ProtectCsmRegion       = Config.ProtectCsmRegion,
    .ShrinkMemoryMap        = Config.ShrinkMemoryMap,
    .ForceExitBootServices  = Config.ForceExitBootServices,
    .DisableVariableWrite   = Config.DisableVariableWrite,
    .EnableWriteUnprotector = Config.EnableWriteUnprotector
  };
  
  if (Config.DevirtualiseMmio && Config.MmioWhitelist.Count > 0) {
    AbcSettings.MmioWhitelist = AllocatePool (
      Config.MmioWhitelist.Count * sizeof (AbcSettings.MmioWhitelist[0])
      );
    
    if (AbcSettings.MmioWhitelist != NULL) {
      UINT32 abcIndex = 0;
      UINT32 configIndex = 0;
      
      for (configIndex = 0; configIndex < Config.MmioWhitelist.Count; configIndex++) {
        if (Config.MmioWhitelist.Values[configIndex]->Enabled) {
          AbcSettings.MmioWhitelist[abcIndex] = Config.MmioWhitelist.Values[configIndex]->Address;
          abcIndex++;
        }
      }
      
      gBS->FreePool(&abcIndex);
      gBS->FreePool(&configIndex);
      
      AbcSettings.MmioWhitelistSize = abcIndex;
    } // Else couldn't allocate slots for mmio addresses
  }
  
  if (Config.ProvideConsoleGopEnable) {
  	QuirksProvideConsoleGop ();
  }
  
  OC_QUIRKS_DESTRUCT (&Config, sizeof (Config));
  
  return OcAbcInitialize (&AbcSettings);
}
