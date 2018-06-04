// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: ExN03CalorHit.hh,v 1.1.10.1 1999/12/07 20:47:28 gunter Exp $
// GEANT4 tag $Name: geant4-01-00 $
//
// 


#ifndef ExN03PixelHit_h
#define ExN03PixelHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

class ExN03PixelHit : public G4VHit
{
  public:

      ExN03PixelHit();
      ExN03PixelHit(G4LogicalVolume *logVol,G4double y,G4double z);
     ~ExN03PixelHit();
      ExN03PixelHit(const ExN03PixelHit &right);
      const ExN03PixelHit& operator=(const ExN03PixelHit &right);
      int operator==(const ExN03PixelHit &right) const;

      inline void *operator new(size_t);
      inline void operator delete(void *aHit);

      void Draw();
      void Print();
      
                 
  private:
      
      const G4LogicalVolume* pLogV;
      G4double YPixelID;
      G4double ZPixelID;
//      G4double edep;
      G4ThreeVector Pos;
 
      G4double EdepPix, TrackLengthPix;
     
  public:
      
      inline void SetPixelID(G4double y,G4double z)
      {
        YPixelID = y;
        ZPixelID = z;
      }
      inline G4double GetY() { return YPixelID; }
      inline G4double GetZ() { return ZPixelID; }
      inline void SetEdepPix(G4double de)
      { EdepPix = de; }
      inline void AddEdepPix(G4double de)
      { EdepPix += de; }
      inline G4double GetEdepPix()
      { return EdepPix; }   
      inline void SetTrakPix(G4double dl)
      { TrackLengthPix = dl; } 
      inline void AddTrakPix(G4double dl)
      { TrackLengthPix += dl; }
      inline G4double GetTrakPix()
      { return TrackLengthPix; }   

      inline void SetPos(G4ThreeVector xyz)
      { Pos = xyz; }
      inline G4ThreeVector GetPos()
      { return Pos; }
      inline const G4LogicalVolume * GetLogV()
      { return pLogV; }
 
};

typedef G4THitsCollection<ExN03PixelHit> ExN03PixelHitsCollection;

extern G4Allocator<ExN03PixelHit> ExN03PixelHitAllocator;

inline void* ExN03PixelHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*) ExN03PixelHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

inline void ExN03PixelHit::operator delete(void* aHit)
{
  ExN03PixelHitAllocator.FreeSingle((ExN03PixelHit*) aHit);
}

#endif


