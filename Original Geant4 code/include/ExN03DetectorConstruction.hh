// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: ExN03DetectorConstruction.hh,v 1.1.10.1 1999/12/07 20:47:28 gunter Exp $
// GEANT4 tag $Name: geant4-01-00 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef ExN03DetectorConstruction_h
#define ExN03DetectorConstruction_h 1


#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class ExN03DetectorMessenger;
class ExN03PixelSD;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class ExN03DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  
    ExN03DetectorConstruction();
   ~ExN03DetectorConstruction();

  public:
    
     void PrintPixelParameters(); 
     void SetPixelThickness(G4double);
     void SetPixelMaterial(G4String);     
     void SetCeramicMaterial(G4String);
 
     G4VPhysicalVolume* Construct();

     void UpdateGeometry();
     
  public:
  
//     void PrintCalorParameters(); 
                    
     G4double GetWorldSizeX()           {return WorldSizeX;}; 
     G4double GetWorldSizeY()           {return WorldSizeY;};
     G4double GetWorldSizeZ()           {return WorldSizeZ;};
 
     G4double GetMatrixThickness()      {return MatrixThickness;};
     G4double GetMatrixSizeY()          {return MatrixSizeY;};
     G4double GetMatrixSizeX()          {return MatrixSizeX;};


     G4double GetPixelThickness()      {return PixelThickness;};
     G4double GetPixelSizeY()          {return PixelSizeY;};
     G4double GetPixelSizeX()          {return PixelSizeX;}; 

 
     const G4VPhysicalVolume* GetphysiWorld()  {return physiWorld;};
     const G4VPhysicalVolume* GetphysiMatrix() {return physiMatrix;};

                 
  private:

#include "ExN03DetectorParameterDef.hh"
     
            
  G4Box*             solidWorld;    //pointer to the solid World 
  G4LogicalVolume*   logicWorld;    //pointer to the logical World
  G4VPhysicalVolume* physiWorld;    //pointer to the physical World

  G4Box*             solidMatrix;   //pointer to the solid Matrix
  G4LogicalVolume*   logicMatrix;   //pointer to the logical Matrix
  G4VPhysicalVolume* physiMatrix;   //pointer to the physical Matrix 

  G4Box*             solidPixel;    //pointer to the solid Pixel 
  G4LogicalVolume*   logicPixel;    
  G4VPhysicalVolume* physiPixel;

     G4Material*        PixelMaterial;
     G4Material*        CeramicMaterial;
     G4Material*        defaultMaterial;



  ExN03DetectorMessenger* detectorMessenger;  //pointer to the Messenger
  ExN03PixelSD* pixelSD;  //pointer to the sensitive detector
      
  private:
    
     void DefineMaterials();
  //   void ComputePixelParameters();
     G4VPhysicalVolume* ConstructPixel();     
};

#endif

