#include<G4Step.hh>
#include<fstream>
#include<iostream>
#include<vector>
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "ExG4DetectorSD.hh"
#include "G4EventManager.hh"
#include "G4UnitsTable.hh"
#include "HistoManager.hh"
#include "EventAction.hh"

   using namespace std;
// Конструктор чуствительной областью, по умолчанию инициализируем нижнюю и верхнюю
// границы гистограммы в 0 и 50 МэВ
ExG4DetectorSD::ExG4DetectorSD(G4String name): G4VSensitiveDetector(name)
{
}

G4bool ExG4DetectorSD::ProcessHits(G4Step* step, G4TouchableHistory* history)
   {
  std::ofstream file1("kin_el1.dat",std::ios::app);
  std::ofstream file2("kin_el2.dat",std::ios::app);
  std::ofstream file3("kin_el3.dat",std::ios::app);
  std::ofstream file4("kin_el4.dat",std::ios::app);
  std::ofstream file5("kin_ga1.dat",std::ios::app);
  std::ofstream file6("kin_ga2.dat",std::ios::app);
  std::ofstream file7("kin_ga3.dat",std::ios::app);
  std::ofstream file8("kin_ga4.dat",std::ios::app);
  double energy_dep = step->GetTotalEnergyDeposit();
  G4String volume_sens = step->GetTrack()->GetVolume()->GetName();
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4int particle_code = step->GetTrack()->GetDynamicParticle()->GetPDGcode();
    double energy_kin = step->GetTrack()->GetDynamicParticle()->GetKineticEnergy();

  if(particle_code == 11) {
  G4cout<< "Kinetic energy of electron in  " << volume_sens << " :" << G4BestUnit(energy_kin,"Energy") << G4endl;
   if (volume_sens == "physDet1") {file1 << energy_kin <<std::endl;}
   if (volume_sens == "physDet2") {file2 << energy_kin <<std::endl;}
   if (volume_sens == "physDet3") {file3 << energy_kin <<std::endl;}
   if (volume_sens == "physDet4") {file4 << energy_kin <<std::endl;}
  }

  if(particle_code == 22) {
  G4cout<< "Kinetic energy of gamma in  " << volume_sens << " :" << G4BestUnit(energy_kin,"Energy") << G4endl;
   if (volume_sens == "physDet1") {file5 << energy_kin <<std::endl;}
   if (volume_sens == "physDet2") {file6 << energy_kin <<std::endl;}
   if (volume_sens == "physDet3") {file7 << energy_kin <<std::endl;}
   if (volume_sens == "physDet4") {file8 << energy_kin <<std::endl;}
  }
 file1.close();
 file2.close();
 file3.close();
 file4.close();
 file5.close();
 file6.close();
 file7.close();
 file8.close();
// Accumulate energy deposit in given modules

  if(volume_sens=="physDet1") edep_det[1] += energy_dep;  
  if(volume_sens=="physDet2") edep_det[2] += energy_dep;
  if(volume_sens=="physDet3") edep_det[3] += energy_dep;
  if(volume_sens=="physDet4") edep_det[4] += energy_dep;

//  edep_sum += energy_dep;  
    //if(volume_sens=="Al_Target_out") step->GetTrack()->SetTrackStatus(fStopAndKill);
  return true;
}

void ExG4DetectorSD::EndOfEvent(G4HCofThisEvent*)
{
//  edep_sum /= 1000. ; // Express energy in GeV
  G4cout << " Total energy deposited in detector#1: " << G4BestUnit(edep_det[1],"Energy") << G4endl; 
  G4cout << " Total energy deposited in detector#2: " << G4BestUnit(edep_det[2],"Energy") << G4endl; 
  G4cout << " Total energy deposited in detector#3: " << G4BestUnit(edep_det[3],"Energy") << G4endl; 
  G4cout << " Total energy deposited in detector#4: " << G4BestUnit(edep_det[4],"Energy") << G4endl;


  auto analysisManager = G4AnalysisManager::Instance();
  for(int i = 1; i<5; i++) {
  analysisManager->FillH1(i,edep_det[i]*1000)  ; //keV 
  edep_sum += edep_det[i];
  }

  analysisManager->FillH1(0,edep_sum*1000) ; // keV  
// Pass the the energy deposit in sensitive volumes for this event to the method of the event 
// aciton to fill histograms 
  EventAction* myAction = (EventAction*)(G4EventManager::GetEventManager()->GetUserEventAction()); 
  if(myAction) {
  myAction->GetEdep1(edep_det[1]); 
  myAction->GetEdep2(edep_det[2]);
  myAction->GetEdep3(edep_det[3]);
  myAction->GetEdep4(edep_det[4]);
  myAction->GetEdepTot(edep_sum); 
  }


}

 ExG4DetectorSD::~ExG4DetectorSD()
{
  std::ofstream file("spectrum.dat");
  for(int i = 1; i<5; i++) 
  {
   file << " Module: " << std::setw(5) << i << std::setw(15) <<  "E deposit: " << std::setw(5) << edep_det[i] << " MeV" <<std::endl;
  }
  //std::ofstream file2("kinen.dat");
  //for(int k = 0; k<=n; k++) 
  //{
   //file2 << array[k] << " MeV" <<std::endl;
  //}


// Clear the values   
   edep_sum = 0.;
   for(int i = 1; i<5; i++) edep_det[i]=0;

}
