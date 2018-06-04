#ifndef ExN03PixelROGeometry_h
#define ExN03PixelROGeometry_h 1

#include "G4VReadOutGeometry.hh"
#include "ExN03DetectorConstruction.hh" 

class ExN03PixelROGeometry : public G4VReadOutGeometry
{
public:
  ExN03PixelROGeometry();
  ExN03PixelROGeometry(G4String);
  ~ExN03PixelROGeometry();

private:
  G4VPhysicalVolume* Build();

#include "ExN03DetectorParameterDef.hh"

//  G4double           PixelSizeY;
//  G4double           PixelSizeZ;
//  G4double           PixelThickness;

//  G4double           LinlayerSizeY;
//  G4double           LinlayerSizeZ;
//  G4double           LinlayerThickness;

//  G4double           MatrixSizeY;
//  G4double           MatrixSizeZ;
//  G4double           MatrixThickness;
 
//  G4double           WorldSizeY;
//  G4double           WorldSizeZ;
//  G4double           WorldSizeX;

//  G4int              NbOfPixelsInY;
//  G4int              NbOfPixelsInZ;

  G4Box*             solidROWorld;    //pointer to the solid World 
  G4LogicalVolume*   logicROWorld;    //pointer to the logical World
  G4VPhysicalVolume* physiROWorld;    //pointer to the physical World

  G4Box*             solidROMatrix;    //pointer to the solid Matrix
  G4LogicalVolume*   logicROMatrix;    
  G4VPhysicalVolume* physiROMatrix;    

  G4Box*             solidROLinlayer;    //pointer to the solid Linlayer
  G4LogicalVolume*   logicROLinlayer;
  G4VPhysicalVolume* physiROLinlayer; 

  G4Box*             solidROPixel;    //pointer to the solid Pixel 
  G4LogicalVolume*   logicROPixel;    
  G4VPhysicalVolume* physiROPixel;   

};

#endif
