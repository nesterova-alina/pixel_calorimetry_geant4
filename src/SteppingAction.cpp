
#include "SteppingAction.hh"
#include "EventAction.hh"
#include "ExG4DetectorConstruction01.hh"
#include "HistoManager.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include <G4SystemOfUnits.hh>
#include "G4UnitsTable.hh"

#include <iostream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
 // get volume of the current step
  G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
 
 // Get volumes of the current step in PreStepPoint and PostStepPoint
  G4String volPre = step->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetName(); 
  if(step ->GetPostStepPoint()->GetPhysicalVolume() != 0){ 
  G4String  volPost = step->GetPostStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetName(); 
   if ( volPre == "World" && volPost == "logDet1"  ) {
     int pdg = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding();
     double mom = step->GetTrack()->GetDynamicParticle()->GetTotalMomentum();
     G4cout.precision(6); 
     G4cout << "PDGcode: " << pdg << " PreStepVolume: " << volPre << " PostStepVolume: " << volPost << " Step length: " << step->GetStepLength()<< " Moment = " << mom << G4endl;  
    G4ThreeVector Pos1 = step->GetTrack()->GetPosition();
    double x_det1 = Pos1.x();
    double y_det1 = Pos1.y();
    double z_det1 = Pos1.z();
    G4cout<< " Det1: x= " << x_det1 << " y= " << y_det1 << " z= " << z_det1 << G4endl;
   if( x_det1<15.0 && x_det1>-15.0 && y_det1<7.5 && y_det1>-7.5)
   fEventAction->GetPosition1(Pos1); 

   G4AnalysisManager* analysisManager = G4AnalysisManager::Instance(); 
   analysisManager->FillH2(1,Pos1.x(),Pos1.y()); 


   }
   if ( volPre == "World" && volPost == "logDet2"  ) {
     int pdg = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding();
     double mom = step->GetTrack()->GetDynamicParticle()->GetTotalMomentum();
     G4cout.precision(6); 
     G4cout << "PDGcode: " << pdg << " PreStepVolume: " << volPre << " PostStepVolume: " << volPost << " Step length: " << step->GetStepLength()<< " Moment = " << mom << G4endl;  
    G4ThreeVector Pos2 = step->GetTrack()->GetPosition();
    double x_det2 = Pos2.x();
    double y_det2 = Pos2.y();
    double z_det2 = Pos2.z();
    G4cout<< " Det2: x= " << x_det2 << " y= " << y_det2 << " z= " << z_det2 << G4endl;
   if( x_det2<15.0 && x_det2>-15.0 && y_det2<7.5 && y_det2>-7.5)
   fEventAction->GetPosition2(Pos2); 

   G4AnalysisManager* analysisManager = G4AnalysisManager::Instance(); 
   analysisManager->FillH2(2,Pos2.x(),Pos2.y()); 
   }
   if ( volPre == "World" && volPost == "logDet3"  ) {
     int pdg = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding();
     double mom = step->GetTrack()->GetDynamicParticle()->GetTotalMomentum();
     G4cout.precision(6); 
     G4cout << "PDGcode: " << pdg << " PreStepVolume: " << volPre << " PostStepVolume: " << volPost << " Step length: " << step->GetStepLength()<< " Moment = " << mom << G4endl;  
    G4ThreeVector Pos3 = step->GetTrack()->GetPosition();
    double x_det3 = Pos3.x();
    double y_det3 = Pos3.y();
    double z_det3 = Pos3.z();
    G4cout<< " Det3: x= " << x_det3 << " y= " << y_det3 << " z= " << z_det3 << G4endl;
   if( x_det3<15.0 && x_det3>-15.0 && y_det3<7.5 && y_det3>-7.5)
   fEventAction->GetPosition3(Pos3); 

   G4AnalysisManager* analysisManager = G4AnalysisManager::Instance(); 
   analysisManager->FillH2(3,Pos3.x(),Pos3.y()); 

}
   if ( volPre == "World" && volPost == "logDet4"  ) {
     int pdg = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding();
     double mom = step->GetTrack()->GetDynamicParticle()->GetTotalMomentum();
     G4cout.precision(6); 
     G4cout << "PDGcode: " << pdg << " PreStepVolume: " << volPre << " PostStepVolume: " << volPost << " Step length: " << step->GetStepLength()<< " Moment = " << mom << G4endl;  
    G4ThreeVector Pos4 = step->GetTrack()->GetPosition();
    double x_det4 = Pos4.x();
    double y_det4 = Pos4.y();
    double z_det4 = Pos4.z();
    G4cout<< " Det4: x= " << x_det4 << " y= " << y_det4 << " z= " << z_det4 << G4endl;
   if( x_det4<15.0 && x_det4>-15.0 && y_det4<7.5 && y_det4>-7.5)
   fEventAction->GetPosition4(Pos4); 

   G4AnalysisManager* analysisManager = G4AnalysisManager::Instance(); 
   analysisManager->FillH2(4,Pos4.x(),Pos4.y()); 


   }
  }

  // Collect energy and dose deposited in this step

  G4double edepStep = step->GetTotalEnergyDeposit();
  G4String volSens = volume->GetName(); 
   if ( volSens == "logDet1" ) { 
  G4cout << " Energy deposited in detector#1: "  << G4BestUnit(edepStep,"Energy") << G4endl; 
  G4double mass = volume->GetMass(); 
  G4cout << " Mass of detector#1: "  << G4BestUnit(mass,"Mass") << G4endl; 
  G4double dose = edepStep/mass;
  G4cout << " Absorbed dose in detector#1: "  << G4BestUnit(dose,"Dose") << G4endl; 
//  fEventAction->AddEdep(edepStep); 
  fEventAction->AddDose1(dose); 
   }

   if ( volSens == "logDet2" ) { 
  G4cout << " Energy deposited in detector#2: "  << G4BestUnit(edepStep,"Energy") << G4endl; 
  G4double mass = volume->GetMass(); 
  G4cout << " Mass of detector#2: "  << G4BestUnit(mass,"Mass") << G4endl; 
  G4double dose = edepStep/mass;
  G4cout << " Absorbed dose in detector#2: "  << G4BestUnit(dose,"Dose") << G4endl; 
//  fEventAction->AddEdep(edepStep); 
  fEventAction->AddDose2(dose); 
   }

   if ( volSens == "logDet3" ) { 
  G4cout << " Energy deposited in detector#1: "  << G4BestUnit(edepStep,"Energy") << G4endl; 
  G4double mass = volume->GetMass(); 
  G4cout << " Mass of detector#3: "  << G4BestUnit(mass,"Mass") << G4endl; 
  G4double dose = edepStep/mass;
  G4cout << " Absorbed dose in detector#3: "  << G4BestUnit(dose,"Dose") << G4endl; 
//  fEventAction->AddEdep(edepStep); 
  fEventAction->AddDose3(dose); 
   }
   if ( volSens == "logDet4" ) { 
  G4cout << " Energy deposited in detector#4: "  << G4BestUnit(edepStep,"Energy") << G4endl; 
  G4double mass = volume->GetMass(); 
  G4cout << " Mass of detector#4: "  << G4BestUnit(mass,"Mass") << G4endl; 
  G4double dose = edepStep/mass;
  G4cout << " Absorbed dose in detector#4: "  << G4BestUnit(dose,"Dose") << G4endl; 
//  fEventAction->AddEdep(edepStep); 
  fEventAction->AddDose4(dose); 
}
 
  // Collect energy deposited in this step in all volumes
//  G4double edepStep = step->GetTotalEnergyDeposit();
//  fEventAction->GetEdepTot(edepStep); 

}


