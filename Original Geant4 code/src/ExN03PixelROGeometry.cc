#include "ExN03PixelROGeometry.hh"
#include "ExN03DetectorConstruction.hh"
#include "ExN03DummySD.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4PVParameterised.hh"
#include "G4SDManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4ThreeVector.hh"
#include "G4Material.hh"
 

ExN03PixelROGeometry::ExN03PixelROGeometry()
{
#include "ExN03DetectorParameterDef.icc"
}



ExN03PixelROGeometry::ExN03PixelROGeometry(G4String aString)
  : G4VReadOutGeometry(aString)  
{
#include "ExN03DetectorParameterDef.icc"
}


ExN03PixelROGeometry::~ExN03PixelROGeometry()
{
}

G4VPhysicalVolume* ExN03PixelROGeometry::Build()
{
// A dummy material is used to fill the volumes of the readout geometry.
// ( It will be allowed to set a NULL pointer in volumes of such virtual
// division in future, since this material is irrelevant for tracking.)
  G4Material* dummyMat  = new G4Material(name="dummyMat", 1., 1.*g/mole, 1.*g/cm3);

  //
  //Builds the ReadOut World:
  //
  solidROWorld = new G4Box("ROWorld", WorldSizeX/2, WorldSizeY/2, WorldSizeZ/2);
  logicROWorld = new G4LogicalVolume(solidROWorld, dummyMat,"ROWorld");
  physiROWorld = new G4PVPlacement(0,G4ThreeVector(),
					 "ROWorld",
					 logicROWorld,
  					 0,false,0);
  //
  // Pixel Matrix volume:
  //
  solidROMatrix = new G4Box("ROMatrix",MatrixSizeX/2,MatrixSizeY/2,
                          MatrixThickness/2);
  logicROMatrix = new G4LogicalVolume(solidROMatrix, dummyMat, "ROMatrix");
  physiROMatrix = new G4PVPlacement(0,                     //no rotation
                                 G4ThreeVector(),       //at (0,0,0)
                                 "ROMatrix",        //its name
                                 logicROMatrix,     //its logical volume
                                 physiROWorld,      //its mother  volume
                                 false,           //no boolean operation
                                 0);              //copy number


  // -------------------------------
  // Pixel layer readout division:
  // -------------------------------
  solidROPixel = new G4Box("ROPixel",               //its name
                         (PixelSizeX)/2,
			 PixelSizeY/2,
                         PixelThickness/2);         //size
          
  logicROPixel = new G4LogicalVolume(solidROPixel,  //its solid
                                   dummyMat,       //its material
                                   "ROPixel");    //its name

  physiROPixel = new G4PVReplica("ROPixel",   //its name
                                logicROPixel,    //its logical volume
                                physiROMatrix,  //its mother
                                kXAxis,            //axis of replication
                                NbOfPixelsInX,      //number of replica
                                PixelSizeX);   //witdth of replica   


  //Flags the cells as sensitive .The pointer here serves
  // as a flag only to check for sensitivity.
  // (Could we make it by a simple cast of a non-NULL value ?)
  ExN03DummySD * dummySensi = new ExN03DummySD;
  logicROPixel->SetSensitiveDetector(dummySensi);

  return physiROWorld;
}
