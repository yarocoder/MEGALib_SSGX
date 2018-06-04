// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: ExN03EventAction.cc,v 1.4.6.1.2.1 1999/12/07 20:47:30 gunter Exp $
// GEANT4 tag $Name: geant4-01-00 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "ExN03EventAction.hh"

#include "ExN03PixelHit.hh"
#include "ExN03EventActionMessenger.hh"

#include "ExN03RunAction.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"


ExN03EventAction::ExN03EventAction()
:pixelCollID(-1),drawFlag("all"),
eventMessenger(NULL),printModulo(10000)
{
  eventMessenger = new ExN03EventActionMessenger(this);
}


ExN03EventAction::~ExN03EventAction()
{
  delete eventMessenger;
}


void ExN03EventAction::BeginOfEventAction(const G4Event* evt)
{
  
 G4int evtNb = evt->GetEventID();
 if (evtNb%printModulo == 0)
   { 
    G4cout << "\n---> Event: " << evtNb << G4endl;
    CLHEP::HepRandom::showEngineStatus();
   }
    
 if (pixelCollID==-1)
   {
    G4SDManager * SDman = G4SDManager::GetSDMpointer();
    pixelCollID = SDman->GetCollectionID("PixCollection");
   } 


}


void ExN03EventAction::EndOfEventAction(const G4Event* evt)
{
  
//  G4int event_id = evt->GetEventID();  //neutralised line the 17th July 2003
 
  G4TrajectoryContainer * trajectoryContainer = evt->GetTrajectoryContainer();
  G4int n_trajectories = 0;
  if(trajectoryContainer)
  { n_trajectories = trajectoryContainer->entries(); }

//  if (event_id < 100 || event_id%100 == 0) {

//   G4cout << G4endl;
// G4cout << " ----->   " << evt->GetEventID() << G4endl;

//    G4cout << "    " << n_trajectories 
//       << " trajectories stored in this event." << endl;
 

    G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
    ExN03PixelHitsCollection* PHC = NULL;
    if (HCE)
        PHC = (ExN03PixelHitsCollection*)(HCE->GetHC(pixelCollID));

    if (PHC)
     {
      int n_hit = PHC->entries();
//      G4cout << "     " << n_hit
//           << " hits are stored in ExN03PixelHitsCollection." << endl;
      G4double totEPix=0, totLPix=0;
      for (int i=0;i<n_hit;i++)
        { 
	  totEPix += (*PHC)[i]->GetEdepPix(); 
          totLPix += (*PHC)[i]->GetTrakPix();
        }
//      G4cout
//         << "   Pixel: total energy: " << setw(7) << G4BestUnit(totEPix,"Energy")
//         << "       total track length: " << setw(7) << G4BestUnit(totLPix,"Length")
//         << endl
//         << endl;           
      }

//  }

//  if(G4VVisManager::GetConcreteInstance())
//  {
//    for(G4int i=0; i<n_trajectories; i++) 
//         { G4Trajectory* trj = (G4Trajectory *)((*(evt->GetTrajectoryContainer()))[i]);
//           if (drawFlag == "all") trj->DrawTrajectory(50);
//           else if ((drawFlag == "charged")&&(trj->GetCharge() != 0.))
//                                  trj->DrawTrajectory(50); 
//         }
//  }
}



