//
//			CIPHER
// ExN03RunAction.cc
//

#include "ExN03RunAction.hh"

#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4UIsession.hh"
#include "G4strstreambuf.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4VVisManager.hh"
#include "G4strstreambuf.hh"
#include "G4ios.hh"

#include "iomanip"
#include <assert.h>

#include "sstream"



ExN03RunAction::ExN03RunAction()
:NbOfPixelsInX(32),NbOfPixelsInY(32)
{
}

ExN03RunAction::~ExN03RunAction()
{}



void ExN03RunAction::BeginOfRunAction(const G4Run* aRun)
{
 
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

  if (G4VVisManager::GetConcreteInstance())
    {
      G4UImanager* UI = G4UImanager::GetUIpointer(); 
      UI->ApplyCommand("/vis/scene/notifyHandlers");
    } 
}



void ExN03RunAction::EndOfRunAction(const G4Run*)
{

  if (G4VVisManager::GetConcreteInstance()) {
     G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/update");
  }
}
