#include "MyRunManager.h"
#include "MyOutputManager.h"
#include "MyDetectorConstructionGDML.h"

#include "G4SystemOfUnits.hh"
#include "G4Trajectory.hh"
#include "G4TrajectoryPoint.hh"
#include "G4AttDef.hh"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <TVector3.h>

#include <string>
#include <G4String.hh>

//#include <TFile.h>

std::fstream logfile;

void writeToLog(const char* text,int rewrite = 0){
  if (rewrite != 0) {
    logfile.open("junk.log", std::fstream::out);
    logfile << text <<G4endl;
    logfile.close();
  }
  else {
    logfile.open("junk.log", std::fstream::out | std::fstream::app);
    logfile << text <<G4endl;
    logfile.close();
  }
}

std::fstream datfile;



MyRunManager::MyRunManager(std::string fName):G4RunManager(){
  //printf("MyRunManager created\n");
  writeToLog("--- BEGIN OF RUN ---",1);

  MyOutputManager::Get()->setupTree(fName.c_str());

}

MyRunManager::~MyRunManager(){
  //printf("MyRunManager destroyed\n");
  writeToLog("--- END OF RUN ---");

  MyOutputManager::Get()->closeTree();

}


void MyRunManager::AnalyzeEvent (G4Event *anEvent){


//  std::cout << "i am very LOUD" << std::endl;

//  anEvent->Print();
}


// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...


MyRunAction::MyRunAction():G4UserRunAction(){
  //printf("MyRunAction created\n");
  writeToLog("MyRunAction created");
}

MyRunAction::~MyRunAction(){
  //ofile << G4endl << "MyRunAction destroyed" << G4endl;
  writeToLog("MyRunAction destroyed");
}

void MyRunAction::BeginOfRunAction(const G4Run*){
//  printf("%s\n",__PRETTY_FUNCTION__);
//  fflush(stdout);
  writeToLog(__PRETTY_FUNCTION__);
}

void MyRunAction::EndOfRunAction(const G4Run*){
  //printf("%s\n",__PRETTY_FUNCTION__);
  //fflush(stdout);
  writeToLog(__PRETTY_FUNCTION__);
}

// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...


MyEventAction::MyEventAction():G4UserEventAction(){
  //printf("MyEventAction created\n");
  writeToLog("MyEventAction created");
}

MyEventAction::~MyEventAction(){
  //printf("MyEventAction destroyed\n");
  writeToLog("MyEventAction destoyed");
}

void MyEventAction::BeginOfEventAction(const G4Event*){
  //printf("%s\n",__PRETTY_FUNCTION__);
  //fflush(stdout);
  writeToLog(__PRETTY_FUNCTION__);
}

void MyEventAction::EndOfEventAction(const G4Event* event){

// 1. Safely check for the primary vertex
    double xPrimary = 0, yPrimary = 0, zPrimary = 0;
    if (event->GetPrimaryVertex()) {
        xPrimary = event->GetPrimaryVertex()->GetX0()/cm;
        yPrimary = event->GetPrimaryVertex()->GetY0()/cm;
        zPrimary = event->GetPrimaryVertex()->GetZ0()/cm;
    }

    // 2. Safely check for the Hits Collection
    G4VHitsCollection* hc = nullptr;
    G4HCofThisEvent* hce = event->GetHCofThisEvent();
    if (hce) {
        hc = hce->GetHC(0);
    } 

  //printf("PRIMARY: %.02f\t %.02f\t %.02f\n",xPrimary,yPrimary,zPrimary);
/*
  G4TrajectoryContainer* trajectoryContainer = event->GetTrajectoryContainer();
  G4int n_trajectories = 0;
  if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();

  for (G4int i=0;i<n_trajectories;i++){
    G4VTrajectory *trj = (G4Trajectory*)((*trajectoryContainer)[i]);
    //G4VTrajectory* trj = (G4Trajectory*)((*(event->GetTrajectoryContainer()))[i]);
    //G4cout << trj->GetParticleName() << G4endl;
    G4int n_pts = trj->GetPointEntries();
    if (n_pts != 6){
    G4cout << n_pts << G4endl;
    for (G4int i=0;i<n_pts;i++){
      
      G4TrajectoryPoint *pt = (G4TrajectoryPoint*)trj->GetPoint(i);
      G4ThreeVector intpt = pt->GetPosition();
      G4cout << intpt << G4endl;

      G4cout << "Map size: " << pt->GetAttDefs()->begin()->second.GetDesc() << G4endl;
      G4cout << "Vec size: "  << G4endl;
    }
    }
  }

*/


/*  
  G4int eventID = event->GetEventID();
  if ( eventID < 100 || eventID % 1000 == 0) {
    G4cout << ">>> Event: " << eventID  << G4endl;
    if ( trajectoryContainer ) {
      G4cout << "    " << n_trajectories
             << " trajectories stored in this event." << G4endl;
    }
  }
*/

  //printf("%s\n",__PRETTY_FUNCTION__);
  fflush(stdout);
  writeToLog(__PRETTY_FUNCTION__);

}

// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...

MySteppingAction::MySteppingAction():G4UserSteppingAction(){
  //printf("MySteppingAction created\n");
  writeToLog("MySteppingAction created");

  fEventID=-1;
  fParticleName="";
  fStepNum=-1;
  fVolume=-1;
  fProcess=-1;

datfile.open("junk.dat");
  datfile << "EventID/I:"
          << "particle/C:"
          //<< "stepnum/I:"
          << "px/D:"
          << "py/D:"
          << "pz/D" << G4endl;
//          TH1D h("h","h",100,0,100);

}

MySteppingAction::~MySteppingAction(){
  //printf("MySteppingAction destroyed\n");
  writeToLog("MySteppingAction destroyed");
  datfile.close();

}

void MySteppingAction::UserSteppingAction(const G4Step* step){
 
  G4Track *track = step->GetTrack();
  G4String partname = track->GetParticleDefinition()->GetParticleName();

  fParticleName = partname;

/*
  if(fEventID!=MyRunManager::GetRunManager()->GetCurrentEvent()->GetEventID()){
    // do something useful
    fParticleName = partname;
    fStepNum = 0;
    fSubStepNum = 0;
    fEventID=MyRunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  } else {
    fStepNum++;
    if(fParticleName.compare(partname)!= 0){ // current particle not prev particle
      fSubStepNum = 0;
      fParticleName = partname;
    } else {
      fSubStepNum++;
    }
  }
*/

  // EVENT ID THINGS
  fEventID=MyRunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

  // TRACK ID THINGS
  int fTrackID = track->GetTrackID();

  // STEP ID THINGS
  int fStepNum = track->GetCurrentStepNumber();

  // SECONDARIES
  const std::vector<const G4Track*> *substep = step->GetSecondaryInCurrentStep();
  for (unsigned int i = 0; i < substep->size(); ++i){
    int sectrackid = (*step->GetSecondaryInCurrentStep())[i]->GetTrackID();
    std::vector<int> secondaries;
    secondaries.push_back(sectrackid);

//    for (int x : secondaries)
//      G4cout << x << G4endl;
  }
  


  // VOLUME THINGS
  G4VPhysicalVolume *stepvol = step->GetPreStepPoint()->GetPhysicalVolume();

  const G4String volname = stepvol->GetName();
  //printf(volname);
  //printf("\n\n");
  if (volname == "myWorld_PV"){
    fVolume = 0;
  } else if (volname == "myBlock_1"){
    fVolume = 1;
  } else if (volname == "myLayer1_1"){
    fVolume = 2;
  } else if(G4StrUtil::contains(volname, "myDetector")) {
      size_t last_index = volname.find_last_not_of("0123456789");
      std::string result = volname.substr(last_index + 1); 
      fVolume = atoi(result.c_str())-1 + 13;  
  }

  // ENERGY THINGS
  double ke = step->GetPostStepPoint()->GetKineticEnergy();
  double edep = step->GetTotalEnergyDeposit();

  // PROCESS THINGS
  std::string processname 
    = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();

  //G4cout << processname << G4endl;
  if (processname=="Transportation"){fProcess = 0;}
  else if (processname=="UserMaxStep"){fProcess = 1;}
  else if (processname=="hIoni"){fProcess = 2;}
  else if (processname=="CoulombScat"){fProcess = 3;}
  else if (processname=="ionIoni"){fProcess = 4;}
  else if (processname=="hadElastic"){fProcess = 5;}
  else if (processname=="alphaInelastic"){fProcess = 6;}
  else if (processname=="msc"){fProcess = 7;}
                               //G4cout << processname << G4endl;}
  else {fProcess=57005;
    G4cout << processname << G4endl;
  };


/*  datfile << MyRunManager::GetRunManager()->GetCurrentEvent()->GetEventID() 
          << "\t" << partname
          << "\t" << x
          << "\t" << y
          << "\t" << z << G4endl;
*/

  // STEP LENGTH THINGS
  fStepLen = step->GetStepLength();


  // POSITIONY THINGS
  //step->GetPreStepPoint()->GetPosition();

  G4ThreeVector presteppos = step->GetPreStepPoint()->GetPosition()*cm;
  G4ThreeVector poststeppos = step->GetPostStepPoint()->GetPosition()*cm;

  TVector3 posvec = TVector3(poststeppos.x(),poststeppos.y(),poststeppos.z());

  float x = poststeppos.x()/cm;
  float y = poststeppos.y()/cm;
  float z = poststeppos.z()/cm;

  float zdep = z; 

  G4ThreeVector shift = presteppos + G4UniformRand()*(poststeppos - presteppos);
  if (step->GetTrack()->GetDefinition()->GetPDGCharge()==0.) shift = presteppos;
  zdep = shift.z()/cm;

  //printf("%s\n",__PRETTY_FUNCTION__);

  //printf("steplength = %.02f nm\n",steplength);
  //printf(partname);
  //printf("\n %.02f\t %.02f\t %.02f\n",x,y,z);


  MyOutputManager::Get()->fill(fEventID,
                               fTrackID,
                               fStepNum,
                               fVolume,
                               fParticleName,
                               fProcess,
                               ke/keV,
                               edep/keV,
                               fStepLen/um,
                               x/um,zdep/um,y/um,z/um,posvec);

  //fflush(stdout);
  writeToLog(__PRETTY_FUNCTION__);
}

// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...

/*
MyTrackingAction::MyTrackingAction():G4UserTrackingAction(){
  //printf("MyTrackingAction created\n");
  writeToLog("MyTrackingAction created");
}

MyTrackingAction::~MyTrackingAction(){
  //printf("MyTrackingAction destroyed\n");
  writeToLog("MyTrackingAction destroyed");
}

void MyTrackingAction::PreUserTrackingAction(const G4Track* track){
  fpTrackingManager->SetStoreTrajectory(true);
  writeToLog(__PRETTY_FUNCTION__);
}

void MyTrackingAction::PostUserTrackingAction(const G4Track* track){
  writeToLog(__PRETTY_FUNCTION__);
}
*/
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
// ...oooOOO0OOOooo......oooOOO0OOOooo......oooOOO0OOOooo...
