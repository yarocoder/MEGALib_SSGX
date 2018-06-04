//
// Dummy sensitive used only to flag sensitivity
// in cells of RO geometry.
//

#ifndef ExN03DummySD_h
#define ExN03DummySD_h 1

#include "G4VSensitiveDetector.hh"
class G4Step;

class ExN03DummySD : public G4VSensitiveDetector
{
public:
  ExN03DummySD();
  ~ExN03DummySD() {};
  
  void Initialize(G4HCofThisEvent*) {};
  G4bool ProcessHits(G4Step*,G4TouchableHistory*) {return false;}
  void EndOfEvent(G4HCofThisEvent*) {};
  void clear() {};
  void DrawAll() {};
  void PrintAll() {};
};
ExN03DummySD::ExN03DummySD()
  : G4VSensitiveDetector("dummySD")
{}
#endif
