//
//	ExN03PixelSD.hh		CIPHER 3
//


#ifndef ExN03PixelSD_h
#define ExN03PixelSD_h 1

#include "G4VSensitiveDetector.hh"
#include "globals.hh"
#include "ExN03RunAction.hh"
#include "ExN03PixelHit.hh"

#include "G4VProcess.hh"  //to get the process name
class G4ProcessVector;

class ExN03DetectorConstruction;
class G4HCofThisEvent;
class G4Step;
class G4TouchableHistory;


class ExN03PixelSD : public G4VSensitiveDetector
{
  public:
  
      ExN03PixelSD(G4String name,ExN03RunAction*);
     ~ExN03PixelSD();

      void Initialize(G4HCofThisEvent*HCE);
      G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
      void EndOfEvent(G4HCofThisEvent*HCE);
      void clear();
      void DrawAll();
      void PrintAll();

  private:
      
      ExN03RunAction*            ExN03Run; 
      G4VProcess* 		 findprocess;
      ExN03PixelHitsCollection*  PixCollection;      
      G4int PixelID[5][5];
      G4int evtorder;
      G4int recordY;
      G4int recordZ; 
      G4double copyIDinY;
      G4double copyIDinZ;
      G4double edep;
      G4String process;
      const int NbOfPixelsInY;
      const int NbOfPixelsInZ;

      G4VProcess* fCurrentProcess;
};

#endif

