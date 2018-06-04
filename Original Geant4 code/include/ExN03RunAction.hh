//
//	ExN03RunAction.hh	CIPHER 3
// 


#ifndef ExN03RunAction_h
#define ExN03RunAction_h 1
#include "G4VPhysicalVolume.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4ios.hh"

#include "iomanip"
#include <assert.h>
#include "iostream"
#include "fstream"
#include "functional"
#include "set"
#include "sstream"
#include <vector>
#include <streambuf>



class G4Run;

class ExN03RunAction : public G4UserRunAction
{
  public:
    ExN03RunAction();
   ~ExN03RunAction();

  public:
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);

    inline void fillPerHit(G4double,G4double,G4double);
    

  private:
    
    const G4int NbOfPixelsInX;
    const G4int NbOfPixelsInY;

    std::ofstream DoublesFile;

    G4int 	IDinX;
    G4int 	IDinY;	
    G4int       Multiplicity;
    G4double    PixelEnergy;
    G4double 	TotalPixelEnergy;
    G4double    InitEnergy;
    G4int       EventNumber;
    G4int       Detected;
    G4int       FullyDetected;
    G4int 	NbOfDoubles;

};

inline 

void ExN03RunAction::fillPerHit(G4double IDinX,G4double IDinY,G4double PixelEnergy)
{

 static G4int EventNumber = 0;
 static G4int Multiplicity = 0;
// static G4int Detected = 0;
// static G4int FullyDetected = 0;
// static G4double PixelEnergy = 0;
 static G4double InitEnergy = 0;
 static G4double TotalPixelEnergy = 0;


/***  Writing in a file ***/

// Begining of event: Event number, Multiplicity
if(PixelEnergy==-2){
  IDinX=0;
  IDinY=0;
  EventNumber++;
}

// Writing on file at the End of Event
else if(PixelEnergy==-1)
{

    if(TotalPixelEnergy==InitEnergy){
    FullyDetected++;
    }
    if(TotalPixelEnergy>20*keV){
    Detected++;
    }

    DoublesFile.open("CdTe200mm200mm10mm.dat");
    if((EventNumber)%100==0){ 	// writes in file each 100
	  DoublesFile << "Source Photons:: " << EventNumber << G4endl;
       	  DoublesFile << "Detected: " << Detected << "  Fully Detected: " << FullyDetected;
	  DoublesFile << G4endl;
    }
    DoublesFile.close();

    /*** Variables reset ***/
    TotalPixelEnergy=0;
    Multiplicity=0;
//    storyX = -1; storyY = -1;
}


// Writing on file during the event
else
{
	Multiplicity++;
	if(Multiplicity==1){
	InitEnergy=IDinX;
	} 
	if(PixelEnergy>20*keV){
	TotalPixelEnergy=TotalPixelEnergy+PixelEnergy;
	}	
     	G4cout << "Initial Energy: " << InitEnergy << " Energy: " << PixelEnergy << " Total: " << TotalPixelEnergy << G4endl;

}

}

#endif
