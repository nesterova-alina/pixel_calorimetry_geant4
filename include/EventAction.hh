
#ifndef B1EventAction_h
#define B1EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
/// Event action class

class HistoManager;

class EventAction : public G4UserEventAction
{
  public:
    EventAction(HistoManager*);
    virtual ~EventAction();
    
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void GetEdepTot(G4double edep) { fEdepTot += edep; }
    void GetEdep1(G4double edep) { fEdep1 = edep; }
    void AddDose1(G4double dose) { fDose1 += dose; }
    void GetPosition1(G4ThreeVector pos) { fPosition1 = pos;} 
    void GetEdep2(G4double edep) { fEdep2 = edep; }
    void AddDose2(G4double dose) { fDose2 += dose; }
    void GetPosition2(G4ThreeVector pos) { fPosition2 = pos;} 
    void GetEdep3(G4double edep) { fEdep3 = edep; }
    void AddDose3(G4double dose) { fDose3 += dose; }
    void GetPosition3(G4ThreeVector pos) { fPosition3 = pos;} 
    void GetEdep4(G4double edep) { fEdep4 = edep; }
    void AddDose4(G4double dose) { fDose4 += dose; }
    void GetPosition4(G4ThreeVector pos) { fPosition4 = pos;}

  private:
    HistoManager* fHistoManager;
    G4double  fEdepTot;  //total energy deposit in all detectors
    G4double  fEdep1;     //energy deposit in detector#1 
    G4double  fDose1;     //absorbed dose in detector#1 
    G4ThreeVector fPosition1; // Position of track entering detector#1
    G4double  fEdep2;     //energy deposit in detector#2 
    G4double  fDose2;     //absorbed dose in detector#2 
    G4ThreeVector fPosition2; // Position of track entering detector#2
    G4double  fEdep3;     //energy deposit in detector#3 
    G4double  fDose3;     //absorbed dose in detector#3 
    G4ThreeVector fPosition3; // Position of track entering detector#3
    G4double  fEdep4;     //energy deposit in detector#4 
    G4double  fDose4;     //absorbed dose in detector#4
    G4ThreeVector fPosition4; // Position of track entering detector#4
};

#endif

    
