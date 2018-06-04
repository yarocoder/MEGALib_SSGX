//
// ExN03PrimaryGenerationAction.cc 	CIPHER 3
// 


#include "ExN03PrimaryGeneratorAction.hh"
#include "ExN03DetectorConstruction.hh"
#include "ExN03PrimaryGeneratorMessenger.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"
#include "fstream"
#include "stdlib.h"

ExN03PrimaryGeneratorAction::ExN03PrimaryGeneratorAction(
                             ExN03DetectorConstruction* ExN03DC)
:ExN03Detector(ExN03DC),rndmFlag("off")
{

  G4int n_particle = 1;
  particleGun  = new G4ParticleGun(n_particle);

  //create a messenger for this class
  gunMessenger = new ExN03PrimaryGeneratorMessenger(this);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
                    = particleTable->FindParticle(particleName="gamma");
  particleGun->SetParticleDefinition(particle);

}



ExN03PrimaryGeneratorAction::~ExN03PrimaryGeneratorAction()
{
  
  delete particleGun;
  delete gunMessenger;
}



void ExN03PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{  //this function is called at the begining of event

  //
  // Energy distributions
  //

  	// Crab distribution  
//	G4double minenergy = 100.*keV, maxenergy = 600.*keV;
//	G4double primaryenergy = (minenergy*maxenergy)/(((1-G4UniformRand())*maxenergy)+minenergy);   

	//Monochromatic beam
//        G4double primaryenergy=200*keV;

	//Particle gun
  //	particleGun->SetParticleEnergy(primaryenergy);
	//  G4cout << "Energia inicial" << primaryenergy << G4endl;  



  // 
  // Position
  //
  G4double z0 = -0.5*(ExN03Detector->GetWorldSizeZ());
  G4double x0 = 1.0*mm, y0 = 1.0*mm;
   if (rndmFlag == "on")
     {  
	x0 = (((x0)*G4UniformRand())-(x0/2));
	y0 = (((y0)*G4UniformRand())-(y0/2));
     }
  particleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  particleGun->GeneratePrimaryVertex(anEvent);

 G4cout << "X Position: " << x0 << G4endl;
 G4cout << "Y Position: " << y0 << G4endl;

}

