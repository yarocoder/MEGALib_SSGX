// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: ExN03CalorHit.cc,v 1.1.10.1 1999/12/07 20:47:29 gunter Exp $
// GEANT4 tag $Name: geant4-01-00 $
//
// 


#include "ExN03PixelHit.hh"
#include "G4ios.hh"
#include "G4VVisManager.hh"
#include "G4VHit.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"

G4Allocator<ExN03PixelHit> ExN03PixelHitAllocator;


ExN03PixelHit::ExN03PixelHit()
{pLogV=NULL;}

ExN03PixelHit::ExN03PixelHit(G4LogicalVolume* logVol,G4double y,G4double z)
:pLogV(logVol),YPixelID(y),ZPixelID(z)
{;}

ExN03PixelHit::~ExN03PixelHit()
{;}


ExN03PixelHit::ExN03PixelHit(const ExN03PixelHit& right)
  : G4VHit()
{
  YPixelID = right.YPixelID;
  ZPixelID = right.ZPixelID;
  EdepPix = right.EdepPix;
  TrackLengthPix = right.TrackLengthPix;

  Pos = right.Pos;
  pLogV = right.pLogV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

const ExN03PixelHit& ExN03PixelHit::operator=(const ExN03PixelHit& right)
{
  YPixelID = right.YPixelID;
  ZPixelID = right.ZPixelID;
  EdepPix = right.EdepPix;
  TrackLengthPix = right.TrackLengthPix;

  Pos = right.Pos;
  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

int ExN03PixelHit::operator==(const ExN03PixelHit& right) const
{
  return ((YPixelID==right.YPixelID)&&(ZPixelID==right.ZPixelID));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void ExN03PixelHit::Draw()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void ExN03PixelHit::Print()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

