
#ifndef HistoManager_h
#define HistoManager_h 1

#include "globals.hh"

#include "g4root.hh"
//#include "g4xml.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

 class TFile;
 class TTree;
 class TH1D;
 const G4int MaxHisto = 17;  // number of histos

class HistoManager
{
  public:
    HistoManager();
   ~HistoManager();

    void BookTree();
    void FillTree(G4double var1, G4double var2,G4double var3, G4double var4,
                  G4double var5, G4double var6,G4double var7, G4double var8,
                  G4double var9, G4double var10,G4double var11, G4double var12,
                  G4double var13, G4double var14,G4double var15, G4double var16);
    void FillHisto(G4int id, G4double bin, G4double weight = 1.0);
    void SaveTree();

  private:
    void BookHistos();
    G4String fFileName;

    TFile*   fRootFile;
    TTree*   fNtuple1;
    TH1D*    fHisto[MaxHisto];

    G4double fVar1;
    G4double fVar2;
    G4double fVar3;
    G4double fVar4;
    G4double fVar5;
    G4double fVar6;
    G4double fVar7;
    G4double fVar8;
    G4double fVar9;
    G4double fVar10;
    G4double fVar11;
    G4double fVar12;
    G4double fVar13;
    G4double fVar14;
    G4double fVar15;
    G4double fVar16;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

