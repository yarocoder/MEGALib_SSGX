// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: ExN03DetectorMessenger.cc,v 1.2.8.1 1999/12/07 20:47:30 gunter Exp $
// GEANT4 tag $Name: geant4-01-00 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "ExN03DetectorMessenger.hh"

#include "ExN03DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

ExN03DetectorMessenger::ExN03DetectorMessenger(ExN03DetectorConstruction * ExN03Det)
:ExN03Detector(ExN03Det)
{ 
  ExN03detDir = new G4UIdirectory("/matrix/");
  ExN03detDir->SetGuidance("ExN03 detector control.");
      
  PixelMaterCmd = new G4UIcmdWithAString("/matrix/setPixelMat",this);
  PixelMaterCmd->SetGuidance("Select Material of the Matrix.");
  PixelMaterCmd->SetParameterName("choice",false);
  PixelMaterCmd->AvailableForStates(G4State_Idle);
  
    
  PixelThickCmd = new G4UIcmdWithADoubleAndUnit("/matrix/setPixelThick",this);
  PixelThickCmd->SetGuidance("Set Thickness of the Pixel");
  PixelThickCmd->SetParameterName("Size",false);
  PixelThickCmd->SetRange("Size>=0.");
  PixelThickCmd->SetUnitCategory("Length");
  PixelThickCmd->AvailableForStates(G4State_Idle);
  
//  NbPixelsCmd = new G4UIcmdWithAnInteger("/matrix/setNbOfPixels",this);
//  NbPixelsCmd->SetGuidance("Set number of pixels.");
//  NbPixelsCmd->SetParameterName("NbPixels",false);
//  NbPixelsCmd->SetRange("NbPixels>0 && NbPixels<50");
//  NbPixelsCmd->AvailableForStates(G4State_Idle);

  UpdateCmd = new G4UIcmdWithoutParameter("/matrix/update",this);
  UpdateCmd->SetGuidance("Update matrix geometry.");
  UpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  UpdateCmd->SetGuidance("if you changed geometrical value(s).");
  UpdateCmd->AvailableForStates(G4State_Idle);
      
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

ExN03DetectorMessenger::~ExN03DetectorMessenger()
{
  delete PixelMaterCmd; delete PixelThickCmd; 
//  delete NbPixelsCmd;
  delete UpdateCmd;
  delete ExN03detDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void ExN03DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == PixelMaterCmd )
   { ExN03Detector->SetPixelMaterial(newValue);}

  if( command == PixelThickCmd )
   { ExN03Detector->SetPixelThickness(PixelThickCmd->GetNewDoubleValue(newValue));}

//  if( command == NbPixelsCmd )
//   { ExN03Detector->SetLinpitchSizeZ(NbPixelsCmd->GetNewIntValue(newValue));}
 
  if( command == UpdateCmd )
   { ExN03Detector->UpdateGeometry(); }

}

