//
//  Cipher01 ExN03DetectorConstruction.cc
//

#include "ExN03DetectorConstruction.hh"
#include "ExN03DetectorMessenger.hh"
#include "ExN03PixelROGeometry.hh"
#include "ExN03PixelSD.hh"
#include "ExN03PixelParameterisation.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4PVReplica.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4TransportationManager.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"



ExN03DetectorConstruction::ExN03DetectorConstruction()
:solidWorld(NULL),logicWorld(NULL),physiWorld(NULL),
 solidMatrix(NULL),logicMatrix(NULL),physiMatrix(NULL),
 solidPixel(NULL),logicPixel(NULL),physiPixel(NULL),
 PixelMaterial(NULL),defaultMaterial(NULL),pixelSD(NULL)
{

#include "ExN03DetectorParameterDef.icc" 

// create commands for interactive definition of the Matrix
  detectorMessenger = new ExN03DetectorMessenger(this);
}



ExN03DetectorConstruction::~ExN03DetectorConstruction()
{ delete detectorMessenger;}



G4VPhysicalVolume* ExN03DetectorConstruction::Construct()
{
  DefineMaterials();
  return ConstructPixel();
}



void ExN03DetectorConstruction::DefineMaterials()
{ 
 //This function illustrates the possible ways to define materials
 
G4String name, symbol;             //a=mass of a mole;
G4double a, z, density;            //z=mean number of protons;  
G4int iz, n;                       //iz=number of protons  in an isotope; 
                                   // n=number of nucleons in an isotope;

G4int ncomponents, natoms;
G4double abundance, fractionmass;
G4double temperature, pressure;

//
// define Elements
//

a = 1.01*g/mole;
G4Element* H  = new G4Element(name="Hydrogen",symbol="H" , z= 1., a);

a = 12.01*g/mole;
G4Element* C  = new G4Element(name="Carbon"  ,symbol="C" , z= 6., a);

a = 14.01*g/mole;
G4Element* N  = new G4Element(name="Nitrogen",symbol="N" , z= 7., a);

a = 16.00*g/mole;
G4Element* O  = new G4Element(name="Oxygen"  ,symbol="O" , z= 8., a);

//a = 28.09*g/mole;
//G4Element* Si = new G4Element(name="Silicon",symbol="Si" , z= 14., a);

a = 127.60*g/mole;
G4Element* Te = new G4Element(name="Tellurium", symbol="Te", z=52., a);

a = 112.40*g/mole;
G4Element* Cd = new G4Element(name="Cadmium", symbol="Cd", z=48., a);

a = 26.98*g/mole;
G4Element* Al = new G4Element(name="Aluminium", symbol="Al", z=13., a); 


//
// define an Element from isotopes, by relative abundance 
//

G4Isotope* U5 = new G4Isotope(name="U235", iz=92, n=235, a=235.01*g/mole);
G4Isotope* U8 = new G4Isotope(name="U238", iz=92, n=238, a=238.03*g/mole);

G4Element* U  = new G4Element(name="enriched Uranium", symbol="U", ncomponents=2);
U->AddIsotope(U5, abundance= 90.*perCent);
U->AddIsotope(U8, abundance= 10.*perCent);

//
// define simple materials
//

density = 5.323*g/cm3;
a = 72.64*g/mole;
G4Material* Ge = new G4Material(name="Germanium", z=32., a, density);

density = 2.329*g/cm3;
a = 28.0855*g/mole;
G4Material* Si = new G4Material(name="Silicon", z=14., a, density);

//density = 8.960*g/cm3;
//a = 63.55*g/mole;
//G4Material* Cu = new G4Material(name="Copper"   , z=29., a, density);

//density = 11.35*g/cm3;
//a = 207.19*g/mole;
//G4Material* Pb = new G4Material(name="Lead"     , z=82., a, density);

//
// define a material from elements.   case 1: chemical molecule
//
 
density = 1.000*g/cm3;
G4Material* H2O = new G4Material(name="Water", density, ncomponents=2);
H2O->AddElement(H, natoms=2);
H2O->AddElement(O, natoms=1);

density = 1.032*g/cm3;
G4Material* Sci = new G4Material(name="Scintillator", density, ncomponents=2);
Sci->AddElement(C, natoms=9);
Sci->AddElement(H, natoms=10);

//density = 2.200*g/cm3;
//G4Material* SiO2 = new G4Material(name="quartz", density, ncomponents=2);
//SiO2->AddElement(Si, natoms=1);
//SiO2->AddElement(O , natoms=2);

//
// define a material from elements.   case 2: mixture by fractional mass
//

density = 1.290*mg/cm3;
G4Material* Air = new G4Material(name="Air"  , density, ncomponents=2);
Air->AddElement(N, fractionmass=0.7);
Air->AddElement(O, fractionmass=0.3);

//CdTe
density = 6.10*g/cm3;
G4Material* CdTe = new G4Material(name="CdTe", density, ncomponents=2);
CdTe->AddElement(Te, fractionmass=0.52);
CdTe->AddElement(Cd, fractionmass=0.48);


//Al2O3 (ceramic)
density = 3.97*g/cm3;
G4Material* Al2O3 = new G4Material(name="Al2O3", density, ncomponents=2);
Al2O3->AddElement(Al, fractionmass=0.5293);
Al2O3->AddElement(O, fractionmass=0.4707);



//
// define a material from elements and/or others materials (mixture of mixtures)
//

//density = 0.200*g/cm3;
//G4Material* Aerog = new G4Material(name="Aerogel", density, ncomponents=3);
//Aerog->AddMaterial(SiO2, fractionmass=62.5*perCent);
//Aerog->AddMaterial(H2O , fractionmass=37.4*perCent);
//Aerog->AddElement (C   , fractionmass= 0.1*perCent);

//
// examples of gas in non STP conditions
//

density     = 27.*mg/cm3;
pressure    = 50.*atmosphere;
temperature = 325.*kelvin;
G4Material* CO2 = new G4Material(name="CarbonicGas", density, ncomponents=2,
                                     kStateGas,temperature,pressure);
CO2->AddElement(C, natoms=1);
CO2->AddElement(O, natoms=2);
 
density     = 0.3*mg/cm3;
pressure    = 2.*atmosphere;
temperature = 500.*kelvin;
G4Material* steam = new G4Material(name="WaterSteam", density, ncomponents=1,
                                      kStateGas,temperature,pressure);
steam->AddMaterial(H2O, fractionmass=1.);

//
// examples of vacuum
//

density     = universe_mean_density;    //from PhysicalConstants.h
pressure    = 3.e-18*pascal;
temperature = 2.73*kelvin;
G4Material* Galactic = new G4Material(name="Galactic", z=1., a=1.01*g/mole, density,
                   kStateGas,temperature,pressure);

density     = 1.e-5*g/cm3;
pressure    = 2.e-2*bar;
temperature = STP_Temperature;         //from PhysicalConstants.h
G4Material* beam = new G4Material(name="Beam", density, ncomponents=1,
                                      kStateGas,temperature,pressure);
beam->AddMaterial(Air, fractionmass=1.);

G4cout << *(G4Material::GetMaterialTable()) << G4endl;



  //default materials of the matrix 
  PixelMaterial = CdTe;
  defaultMaterial = Galactic;
  //defaultMaterial  = Air;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
  
G4VPhysicalVolume* ExN03DetectorConstruction::ConstructPixel()
{
  // complete the Pixel parameters definition 
//  ComputePixelParameters();
   
  //     
  // World
  //
  solidWorld=NULL; logicWorld=NULL; physiWorld=NULL;

  solidWorld = new G4Box("World",		//its name
                         WorldSizeX/2,WorldSizeY/2,
			 WorldSizeZ/2);	//its size
                         
  logicWorld = new G4LogicalVolume(solidWorld,		//its solid
                                   defaultMaterial,	//its material
                                   "World");		//its name
                                   
  physiWorld = new G4PVPlacement(0,			//no rotation
  				 G4ThreeVector(),	//at (0,0,0)
                                 "World",		//its name
                                 logicWorld,		//its logical volume
                                 NULL,			//its mother  volume
                                 false,			//no boolean operation
                                 0);			//copy number
 
 
  //
  //Matrix
  //
  solidMatrix=NULL; logicMatrix=NULL; physiMatrix=NULL;

  solidMatrix = new G4Box("Matrix",                   //its name
                          MatrixSizeX/2,MatrixSizeY/2,
			  MatrixThickness/2); //size
                       
  logicMatrix = new G4LogicalVolume(solidMatrix,      //its solid
                                    defaultMaterial, //its material
                                    "Matrix");        //its name
        
  physiMatrix = new G4PVPlacement(0,                     //no rotation
                                 G4ThreeVector(),       //at (0,0,0)
                                 "Matrix",        //its name
                                 logicMatrix,     //its logical volume
                                 physiWorld,      //its mother  volume
                                 false,           //no boolean operation
                                 0);              //copy number

  
   //
   //Pixel 
   //
   solidPixel = new G4Box("Pixel",               //its name
                         PixelSizeX/2,PixelSizeY/2,
                         PixelThickness/2);         //size

  logicPixel = new G4LogicalVolume(solidPixel,  //its solid
                                   PixelMaterial,       //its material
                                   "Pixel");    //its name

   G4VPVParameterisation * pixelParam
  				  = new ExN03PixelParameterisation; 

   physiPixel = new G4PVParameterised("Pixel",   //its name
                                logicPixel,    //its logical volume
                                physiMatrix,  //its mother
                                kXAxis,            //axis of replication
                                NbOfPixelsInX,      //number of copies
                                pixelParam);   //parameterisation


 
  // Sensitive Detector: Matrix 
  //
  G4SDManager* SDman = G4SDManager::GetSDMpointer();

  G4String pixelSDname = "/pixel";
  ExN03RunAction* runact = new ExN03RunAction;
  ExN03PixelSD* pixelSD = new ExN03PixelSD(pixelSDname,runact);
  G4String ROgeometryName = "PixelROGeom";
  G4VReadOutGeometry* pixelRO = new ExN03PixelROGeometry(ROgeometryName);
  pixelRO->BuildROGeometry();
  pixelSD->SetROgeometry(pixelRO);
  SDman->AddNewDetector( pixelSD );
  logicPixel->SetSensitiveDetector(pixelSD);
  
  //                                        
  // Visualization attributes
  //
  logicWorld->SetVisAttributes (G4VisAttributes::Invisible);
  G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  simpleBoxVisAtt->SetVisibility(true);
  logicMatrix->SetVisAttributes(simpleBoxVisAtt);

  // Send to a file the parameters 
  PrintPixelParameters();  
  
  // ******** Always return the physical World ********
  
  return physiWorld;

}




 void ExN03DetectorConstruction::PrintPixelParameters()
 {

//   G4std::ofstream logFile;

   G4String coment="mm of ";
   G4String material=PixelMaterial->GetName();

//   logFile.open("teste.dat", ios::out | ios::binary);
//   logFile.write((char*)&PixelThickness, sizeof (G4double));
//   logFile.write(coment, 7);
//   logFile.write(material, 5);
//   logFile.close();

// logFile << PixelThickness << "mm of " << PixelMaterial->GetName() << G4endl;
 }



// **********************************************************

// ENTRIES TO CHANGE ORIGINAL VALUES OF GEOMETRY VARIABLES

// ***********************************************************


void ExN03DetectorConstruction::SetPixelMaterial(G4String materialChoice)
{
  // search the material by its name   
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
  if (pttoMaterial)
     {PixelMaterial = pttoMaterial;
      logicPixel->SetMaterial(pttoMaterial); 
//    PrintCalorParameters();
     }             
}


//void ExN03DetectorConstruction::SetCeramicMaterial(G4String materialChoice)
//{
  // search the material by its name
//  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);
//  if (pttoMaterial)
//     {CeramicMaterial = pttoMaterial;
//      logicLinsupport->SetMaterial(pttoMaterial);
//    PrintCalorParameters();
//     }
//}                              

void ExN03DetectorConstruction::SetPixelThickness(G4double val)
{
  // change the transverse size and recompute the calorimeter parameters
  PixelThickness = val;
}


  
void ExN03DetectorConstruction::UpdateGeometry()
{
  G4RunManager::GetRunManager()->DefineWorldVolume(ConstructPixel());
}

