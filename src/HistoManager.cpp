
#include "HistoManager.hh"
#include "G4UnitsTable.hh"

#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <TStyle.h>
#include <TColor.h>
#include <CLHEP/Units/SystemOfUnits.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
  : fFileName("alpide_hist"),fRootFile(0), 
 fNtuple1(0), fVar1(0), fVar2(0)
{
  BookHistos(); // for G4AnalysisManager
  fNtuple1 = 0; //tree
  for (G4int k=0; k<MaxHisto; k++) fHisto[k] = 0; //histos  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{
  delete G4AnalysisManager::Instance();
  if ( fRootFile ) delete fRootFile;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::BookTree()
{ 
// Creating a tree container to handle histograms and ntuples. This tree is associated to an output file.
 
 G4String fileName = "alpide_tree.root";
 fRootFile = new TFile(fileName,"RECREATE");
 if(!fRootFile) {
   G4cout << " HistoManager::book :" 
          << " problem creating the ROOT TFile "
          << G4endl;
   return;
 }
   
  // create 1-st tree with 12 branches
 
 fNtuple1 = new TTree("101", "Alpide");
 fNtuple1->Branch("Edep1", &fVar1, "Edep1/D");
 fNtuple1->Branch("D1", &fVar2, "D1/D");
 fNtuple1->Branch("X1", &fVar3, "X1/D");
 fNtuple1->Branch("Y1", &fVar4, "Yl/D");
 fNtuple1->Branch("Edep2", &fVar5, "Edep2/D");
 fNtuple1->Branch("D2", &fVar6, "D2/D");
 fNtuple1->Branch("X2", &fVar7, "X2/D");
 fNtuple1->Branch("Y2", &fVar8, "Y2/D");
 fNtuple1->Branch("Edep3", &fVar9, "Edep3/D");
 fNtuple1->Branch("D3", &fVar10, "D3/D");
 fNtuple1->Branch("X3", &fVar11, "X3/D");
 fNtuple1->Branch("Y3", &fVar12, "Y3/D");
 fNtuple1->Branch("Edep4", &fVar13, "Edep4/D");
 fNtuple1->Branch("D4", &fVar14, "D4/D");
 fNtuple1->Branch("X4", &fVar15, "X4/D");
 fNtuple1->Branch("Y4", &fVar16, "Y4/D");

 // create histos 
 fHisto[1] = new TH1D("1", "Energy deposit in detector#1", 100, 0., 500.);
 if (!fHisto[1]) G4cout << "\n can't create histo 1" << G4endl;
 fHisto[1]->GetXaxis()->SetTitle("E, keV");
 fHisto[1]->GetYaxis()->SetTitle("N");
 fHisto[2] = new TH1D("2", "Absorbed dose in detector#1", 100, 0., 10.);
 if (!fHisto[2]) G4cout << "\n can't create histo 2" << G4endl;
 fHisto[2]->GetXaxis()->SetTitle("Dose, picoGy");
 fHisto[2]->GetYaxis()->SetTitle("N");
 fHisto[3] = new TH1D("3", "X-coordinate of paticle through detector#1", 100, -15.0, 15.0);
 if (!fHisto[3]) G4cout << "\n can't create histo 3" << G4endl;
 fHisto[3]->GetXaxis()->SetTitle("X1, mm");
 fHisto[3]->GetYaxis()->SetTitle("N");
 fHisto[4] = new TH1D("4", "Y-coordinate of paticle through detector#1", 100, -7.5, 7.5);
 if (!fHisto[4]) G4cout << "\n can't create histo 4" << G4endl;
 fHisto[4]->GetXaxis()->SetTitle("Y1, mm");
 fHisto[4]->GetYaxis()->SetTitle("N");
 fHisto[5] = new TH1D("5", "Energy deposit in detector#2", 100, 0., 500.);
 if (!fHisto[5]) G4cout << "\n can't create histo 5" << G4endl;
 fHisto[5]->GetXaxis()->SetTitle("E, keV");
 fHisto[5]->GetYaxis()->SetTitle("N");
 fHisto[6] = new TH1D("6", "Absorbed dose in detector#2", 100, 0., 10.);
 if (!fHisto[6]) G4cout << "\n can't create histo 6" << G4endl;
 fHisto[6]->GetXaxis()->SetTitle("Dose, picoGy");
 fHisto[6]->GetYaxis()->SetTitle("N");
 fHisto[7] = new TH1D("7", "X-coordinate of paticle through detector#2", 100, -15.0, 15.0);
 if (!fHisto[7]) G4cout << "\n can't create histo 7" << G4endl;
 fHisto[7]->GetXaxis()->SetTitle("X2, mm");
 fHisto[7]->GetYaxis()->SetTitle("N");
 fHisto[8] = new TH1D("8", "Y-coordinate of paticle through detector#2", 100, -7.5, 7.5);
 if (!fHisto[8]) G4cout << "\n can't create histo 8" << G4endl;
 fHisto[8]->GetXaxis()->SetTitle("Y2, mm");
 fHisto[8]->GetYaxis()->SetTitle("N");
 fHisto[9] = new TH1D("9", "Energy deposit in detector#3", 100, 0., 500.);
 if (!fHisto[9]) G4cout << "\n can't create histo 9" << G4endl;
 fHisto[9]->GetXaxis()->SetTitle("E, keV");
 fHisto[9]->GetYaxis()->SetTitle("N");
 fHisto[10] = new TH1D("10", "Absorbed dose in detector#3", 100, 0., 10.);
 if (!fHisto[10]) G4cout << "\n can't create histo 10" << G4endl;
 fHisto[10]->GetXaxis()->SetTitle("Dose, picoGy");
 fHisto[10]->GetYaxis()->SetTitle("N");
 fHisto[11] = new TH1D("11", "X-coordinate of paticle through detector#3", 100, -15.0, 15.0);
 if (!fHisto[11]) G4cout << "\n can't create histo 11" << G4endl;
 fHisto[11]->GetXaxis()->SetTitle("X3, mm");
 fHisto[11]->GetYaxis()->SetTitle("N");
 fHisto[12] = new TH1D("12", "Y-coordinate of paticle through detector#3", 100, -7.5, 7.5);
 if (!fHisto[12]) G4cout << "\n can't create histo 12" << G4endl;
 fHisto[12]->GetXaxis()->SetTitle("Y3, mm");
 fHisto[12]->GetYaxis()->SetTitle("N");
 fHisto[13] = new TH1D("13", "Energy deposit in detector#4", 100, 0., 500.);
 if (!fHisto[13]) G4cout << "\n can't create histo 13" << G4endl;
 fHisto[13]->GetXaxis()->SetTitle("E, keV");
 fHisto[13]->GetYaxis()->SetTitle("N");
 fHisto[14] = new TH1D("14", "Absorbed dose in detector#4", 100, 0., 10.);
 if (!fHisto[14]) G4cout << "\n can't create histo 14" << G4endl;
 fHisto[14]->GetXaxis()->SetTitle("Dose, picoGy");
 fHisto[14]->GetYaxis()->SetTitle("N");
 fHisto[15] = new TH1D("15", "X-coordinate of paticle through detector#4", 100, -15.0, 15.0);
 if (!fHisto[15]) G4cout << "\n can't create histo 15" << G4endl;
 fHisto[15]->GetXaxis()->SetTitle("X3, mm");
 fHisto[15]->GetYaxis()->SetTitle("N");
 fHisto[16] = new TH1D("16", "Y-coordinate of paticle through detector#4", 100, -7.5, 7.5);
 if (!fHisto[16]) G4cout << "\n can't create histo 16" << G4endl;
 fHisto[16]->GetXaxis()->SetTitle("Y4, mm");
 fHisto[16]->GetYaxis()->SetTitle("N");


 G4cout << "----> Tree file is opened in " << fileName << G4endl;
}

void HistoManager::FillTree(G4double var1, G4double var2, G4double var3, G4double var4,    
                            G4double var5, G4double var6, G4double var7, G4double var8,    
                            G4double var9, G4double var10, G4double var11, G4double var12,    
                            G4double var13, G4double var14, G4double var15, G4double var16)  
{
 fVar1 = var1;
 fVar2 = var2;
 fVar3 = var3;
 fVar4 = var4;
 fVar5 = var5;
 fVar6 = var6;
 fVar7 = var7;
 fVar8 = var8;
 fVar9 = var9;
 fVar10 = var10;
 fVar11 = var11;
 fVar12 = var12;
 fVar13 = var13;
 fVar14 = var14;
 fVar15 = var15;
 fVar16 = var16;

  if (fNtuple1) fNtuple1->Fill();
}

void HistoManager::FillHisto(G4int ih, G4double xbin, G4double weight)
{
  if (ih >= MaxHisto) {
    G4cout << "---> warning from HistoManager::FillHisto() : histo " << ih
           << " does not exist. (xbin=" << xbin << " weight=" << weight << ")"
           << G4endl;
    return;
  }
 if  (fHisto[ih]) { fHisto[ih]->Fill(xbin, weight); }
}

void HistoManager::SaveTree()
{ 
  G4String fileName = "alpide_tree.root";
  if (fRootFile) {
    fRootFile->Write();       // Writing the histograms to the file
    fRootFile->Close();        // and closing the tree (and the file)
    G4cout << "----> Tree is saved in " << fileName << G4endl; 
  }
}

void HistoManager::BookHistos()
{
  // Create or get analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in HistoManager.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetFileName(fFileName);
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetActivation(true);    // enable inactivation of histograms

  // Define histograms start values
  const G4int kMaxHistoH1 = 25;
  const G4int kMaxHistoH2 = 10;
  const G4String id1[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                           "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
                           "20", "21", "22", "23", "24"};      // H1-histos
  const G4String id2[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};    // H2-histos
  const G4String title1[] =
                { "Energy deposit in all detectors",                        //0
                  "Energy deposit in detector#1",                           //1
                  "Energy deposit in detector#2",                           //2   
                  "Energy deposit in detector#3",                           //3
                  "Energy deposit in detector#4",                           //4
                  "Absorbed dose in detector#1",                            //5
                  "Absorbed dose in detector#2",                            //6
                  "Absorbed dose in detector#3",                            //7
                  "Absorbed dose in detector#4",                            //8
                  "dummy","dummy","dummy","dummy","dummy","dummy",  //9-13                      
                  "dummy","dummy","dummy","dummy","dummy","dummy","dummy",  //14-20
                  "dummy","dummy","dummy","dummy"                           //21-24
               };
 const G4String title2[] =
                { "dummy",                                                //0
                  "XY-distribution of particles through detector#1",      //1
                  "XY-distribution of particles through detector#2",      //2 
                  "XY-distribution of particles through detector#3",      //3
                  "XY-distribution of particles through detector#4",      //4
                  "dummy","dummy","dummy","dummy","dummy"         //5-9
                };

  // Default values (to be reset via /analysis/h1/set command)               
  G4int nbins = 100;
  G4double vmin = 0.;
  G4double vmax = 100.;

  // Default values (to be reset via /analysis/h2/set command)               
  G4int nbins1 = 100;
  G4double vmin1 = 0.;
  G4double vmax1 = 100.;
  G4int nbins2 = 100;
  G4double vmin2 = 0.;
  G4double vmax2 = 100.;
  // Create all histograms as inactivated 
  // as we have not yet set nbins, vmin, vmax
  for (G4int k=0; k<kMaxHistoH1; k++) {
    G4int ih1 = analysisManager->CreateH1(id1[k], title1[k], nbins, vmin, vmax);
    analysisManager->SetH1Activation(ih1, false);
  }
  for (G4int k=0; k<kMaxHistoH2; k++) {
    G4int ih2 = analysisManager->CreateH2(id2[k], title2[k], nbins1, vmin1, vmax1, nbins2, vmin2, vmax2);
    analysisManager->SetH2Activation(ih2, false);
  }
}
