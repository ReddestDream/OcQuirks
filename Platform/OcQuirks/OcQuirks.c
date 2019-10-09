#include <Library/OcAppleBootCompatLib.h>
#include <Library/UefiBootServicesTableLib.h>

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

EFI_STATUS
EFIAPI
QuirksEntryPoint (
  IN EFI_HANDLE        Handle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  
  //
  // Set this value to 1 to enable or 0 to disable ProvideConsoleGop.
  //
  
  int QuirksProvideConsoleGopEnable = 1;
  
  OC_ABC_SETTINGS AbcSettings = {
  	
  	//
    // Set these values as appropriate based on OC Booter Quirks required.
    //
    
    .AvoidRuntimeDefrag		= TRUE,
    .SetupVirtualMap		= TRUE,
    .ProvideCustomSlide		= TRUE,
    .DevirtualiseMmio		= FALSE,
    .DisableSingleUser		= FALSE,
    .DiscardHibernateMap	= FALSE,
    .EnableSafeModeSlide	= TRUE,
    .ProtectCsmRegion		= FALSE,
    .ShrinkMemoryMap		= FALSE,
    .ForceExitBootServices	= TRUE,
    .DisableVariableWrite	= FALSE,
    .EnableWriteUnprotector	= TRUE
  };
  
  if (QuirksProvideConsoleGopEnable) {
  	QuirksProvideConsoleGop ();
  }
  
  return OcAbcInitialize (&AbcSettings);
}
