
#include "EventAction.hh"
#include "Run.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

#include <G4SystemOfUnits.hh>
#include "G4UnitsTable.hh"

#include "HistoManager.hh"

#include <iostream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(HistoManager* histo)
: G4UserEventAction(),fHistoManager(histo),
  fEdep1(0.),fEdep2(0.),fEdep3(0.), fEdep4(0.)
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{    
  fEdepTot = 0.;
  fEdep1 = 0.;
  fDose1 = 0.;
  fEdep2 = 0.;
  fDose2 = 0.;
  fEdep3 = 0.;
  fDose3 = 0.;
  fEdep4 = 0.;
  fDose4 = 0.;
 }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event*)
{   
  // Get statistics in given event
  Run* run = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  run->AddEdep(fEdep1);
   G4cout.precision(6); 
 
   G4cout << " Position of e- entering detector#1: " << G4BestUnit(fPosition1, "Length") << G4endl;
   G4cout << " Energy deposited in detector#1: "  << G4BestUnit(fEdep1,"Energy") << G4endl;
   G4cout << " Absorbed dose in detector#1: "  << G4BestUnit(fDose1,"Dose") << G4endl;
   G4cout << " Position of e- entering detector#2: " << G4BestUnit(fPosition2, "Length") << G4endl;
   G4cout << " Energy deposited in detector#2: "  << G4BestUnit(fEdep2,"Energy") << G4endl;
   G4cout << " Absorbed dose in detector#2: "  << G4BestUnit(fDose2,"Dose") << G4endl;
   G4cout << " Position of e- entering detector#3: " << G4BestUnit(fPosition3, "Length") << G4endl;
   G4cout << " Energy deposited in detector#3: "  << G4BestUnit(fEdep3,"Energy") << G4endl;
   G4cout << " Absorbed dose in detector#3: "  << G4BestUnit(fDose3,"Dose") << G4endl;
   G4cout << " Position of e- entering detector#4: " << G4BestUnit(fPosition4, "Length") << G4endl;
   G4cout << " Energy deposited in detector#4: "  << G4BestUnit(fEdep4,"Energy") << G4endl;
   G4cout << " Absorbed dose in detector#4: "  << G4BestUnit(fDose4,"Dose") << G4endl;
   G4cout << " Energy deposited in all detecrors: "  << G4BestUnit(fEdepTot,"Energy") << G4endl;


// Fill G4 histograms
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH2(1,fPosition1.x(),fPosition1.y());  
  analysisManager->FillH2(2,fPosition2.x(),fPosition2.y()); 
  analysisManager->FillH2(3,fPosition3.x(),fPosition3.y()); 
  analysisManager->FillH2(4,fPosition4.x(),fPosition4.y()); 
  analysisManager->FillH1(5,fDose1);  
  analysisManager->FillH1(6,fDose2); 
  analysisManager->FillH1(7,fDose3); 
  analysisManager->FillH1(8,fDose4); 

// Fill ROOT tree and histograms
 fHistoManager->FillTree(1.e+3*fEdep1, 1.e+24*fDose1,fPosition1.x(), fPosition1.y(),
                         1.e+3*fEdep2, 1.e+24*fDose2,fPosition2.x(), fPosition2.y(),
                         1.e+3*fEdep3, 1.e+24*fDose3,fPosition3.x(), fPosition3.y(),
                         1.e+3*fEdep4, 1.e+24*fDose4,fPosition4.x(), fPosition4.y());


 fHistoManager->FillHisto(1, 1.e+3*fEdep1);
 fHistoManager->FillHisto(2, 1.e+24*fDose1);  //picoGy
 fHistoManager->FillHisto(3, fPosition1.x());
 fHistoManager->FillHisto(4, fPosition1.y());
 fHistoManager->FillHisto(5, 1.e+3*fEdep2);
 fHistoManager->FillHisto(6, 1.e+24*fDose2);  //picoGy
 fHistoManager->FillHisto(7, fPosition2.x());
 fHistoManager->FillHisto(8, fPosition2.y()); 
 fHistoManager->FillHisto(9, 1.e+3*fEdep3);
 fHistoManager->FillHisto(10, 1.e+24*fDose3);  //picoGy
 fHistoManager->FillHisto(11, fPosition3.x());
 fHistoManager->FillHisto(12, fPosition3.y());
 fHistoManager->FillHisto(13, 1.e+3*fEdep4);
 fHistoManager->FillHisto(14, 1.e+24*fDose4);  //picoGy
 fHistoManager->FillHisto(15, fPosition4.x());
 fHistoManager->FillHisto(16, fPosition4.y());


// Clear parameters
  fEdepTot=0.;
  fEdep1=0.;
  fDose1=0.;
  fEdep2=0.;
  fDose2=0.;
  fEdep3=0.;
  fDose3=0.;
  fEdep4=0.;
  fDose4=0.;
 }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
