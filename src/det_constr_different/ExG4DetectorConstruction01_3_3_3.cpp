// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file ExG4DetectorConstruction01.cpp
/// \brief Implementation of the ExG4DetectorConstruction01 class

#include "ExG4DetectorConstruction01.hh"
#include "ExG4DetectorSD.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4SubtractionSolid.hh"

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//Создание детектора, всего моделируемого объема
ExG4DetectorConstruction01::ExG4DetectorConstruction01()
: G4VUserDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExG4DetectorConstruction01::~ExG4DetectorConstruction01()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//Создаем детекторы

G4VPhysicalVolume* ExG4DetectorConstruction01::Construct()
{  
  // Get nist material manager
  // Для обучения используем предопределенные в Geant4 материалы
  // Так объявляется менеджер, из которого из можно извлечь
  //
  G4NistManager* nist = G4NistManager::Instance();
  
  // Detector parameters
  // Параметры детектора,
  //
   G4double det_sizeX = 3*cm, det_sizeZ = 0.005*cm, det_sizeY = 1.5*cm;
  // Target parameters
  // Параметры мишени,
  //
  G4double tgt1_sizeX = 5*cm, tgt1_sizeZ = 0.0003*cm, tgt1_sizeY = 7*cm;
  G4double tgt_sizeX = 4*cm, tgt_sizeZ = 2.0*cm, tgt_sizeY = 5*cm;

   // Материал детектора
  //
  G4Material* det_mat = nist->FindOrBuildMaterial("G4_Si");

  // Материал мишени
  //
  G4Material* tgt_mat = nist->FindOrBuildMaterial("G4_Pb");
  G4Material* tgt_mat1 = nist->FindOrBuildMaterial("G4_Al");
 
  G4double tube_dPhi = twopi;
  // Option to switch on/off checking of volumes overlaps
  // Опция для включения выключения проверки перекрытия объемов
  //
  //G4bool checkOverlaps = true;


  //     
  // World
  // Мир, самый большой объем, включающий остальные, аналог экспериментального
  // зала
  //
  G4double world_sizeX = 30*cm;//Размер по x и y будут одинаковы - ширина и высота
  G4double world_sizeY = 30*cm;  
  G4double world_sizeZ  = 400*cm;//Размер по z - толщина
  // Выбор материала для мира из предопределенных в Geant4, берем воздух
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  // Создание объема для мира, определяется просто сама форма объема, берем параллелепипед
  G4Box* solidWorld =    
    new G4Box("World",                       //its name, название объема
       0.5*world_sizeX, 0.5*world_sizeY, 0.5*world_sizeZ);     //its size, его размеры

  // Логический объем, здесь подключается материал, из которого сделан объем
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid, объем
                        world_mat,           //its material, материал объема
                        "World");            //its name, название логического объема
                                             //совпадает с названием объема, но
                                             //для Geant4 это разные объекты
                                             //объем и логический объем

  //Физический объем, а теперь наш логический объем помещае в "ральный" мир
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation, нет вращения
                      G4ThreeVector(),       //at (0,0,0), расположение в центре (0,0,0)
                      logicWorld,            //its logical volume, логический объем этого физического
                      "World",               //its name, название физического объема
                      0,                     //its mother  volume, материнский объем, этот самый первый
                      false,                 //no boolean operation, без логических (булевых) операций
                      0                     //copy number, номер копии
                        );        //overlaps checking, флаг проверки перекрытия объемов
  

  //                  
  //Алюминиевая фольга на выходе пучка
  // 
  G4Box *solidTgt = new G4Box("solidTgt", 5*cm, 5*cm, 0.05*mm);
  G4LogicalVolume *logTgt = new G4LogicalVolume(solidTgt, tgt_mat1, "logTgt");
  G4PVPlacement *physTgt = new G4PVPlacement(0, G4ThreeVector(0,0,-130*cm), logTgt,
					       "physTgt",logicWorld, false, 0);
  
/// Коллиматор
  G4Box *boxColl = new G4Box("boxColl", 5*cm, 5*cm, 7.5*cm);
  G4VSolid *TubeColl =
    new G4Tubs("TubeColl",                    //its name, имя
         0.*mm, 0.5*4*mm, 0.5*16*cm, 0.,tube_dPhi*rad);
  G4VSolid *solidColl = new G4SubtractionSolid("solidColl", boxColl, TubeColl);
  G4LogicalVolume *logColl = new G4LogicalVolume(solidColl, tgt_mat, "logColl");
  G4PVPlacement *physColl = new G4PVPlacement(0, G4ThreeVector(0,0,-13*cm), logColl,
					       "physColl",logicWorld, false, 0);


  //                  
  //Алюминиевая фольга на входе в модуль
  //   
 G4Box* solidTgt0 =
    new G4Box("Al_Target",                    //its name, имя
        0.5*tgt1_sizeX, 0.5*tgt1_sizeY, 0.5*tgt1_sizeZ); //its size, размеры

  //Логический объем
  G4LogicalVolume* logicTar0 =
    new G4LogicalVolume(solidTgt0,            //its solid, объем
                        tgt_mat1,             //its material, указываем материал детектора
                        "Al_Target");         //its name, его имя

  //Физический объем
  new G4PVPlacement(0,                       //no rotation, так же без вращения
                    G4ThreeVector(0,0,0*cm),         //at (0,0,0)
                    logicTar0,                //its logical volume, подключаем логический объем
                    "Al_Target",              //its name, имя физического объема
                    logicWorld,              //its mother  volume, родительский логический объем!
                    false,                   //no boolean operation, без булевых операций
                    0);                       //copy number, номер копии
                //  checkOverlaps);          //overlaps checking, флаг проверки перекрытия объемов                



  // Detector
  // Детектор, также используем параллелепипед
  //  1
  G4Box* solidDet1 =
    new G4Box("solidDet1",                    //its name, имя
      0.5*det_sizeX, 0.5*det_sizeY, 0.5*det_sizeZ); //its size, размеры

  //Логический объем
  G4LogicalVolume*  logDet1 = 
    new G4LogicalVolume(solidDet1,            //its solid, объем
                        det_mat,             //its material, указываем материал детектора
                        "logDet1");         //its name, его имя

  //Физический объем детектора
  new G4PVPlacement(0,                       //no rotation, так же без вращения
                    G4ThreeVector(0,0,6*cm),         //at (0,0,0)
                    logDet1,                //its logical volume, подключаем логический объем
                    "physDet1",              //its name, имя физического объема
                    logicWorld,              //its mother  volume, родительский логический объем!
                    false,                   //no boolean operation, без булевых операций
                    0);                       //copy number, номер копии
                  // checkOverlaps);          //overlaps checking, флаг проверки перекрытия объемов







  // 2 
  G4Box* solidDet2 =
    new G4Box("solidDet2",                    //its name, имя
        0.5*det_sizeX, 0.5*det_sizeY, 0.5*det_sizeZ); //its size, размеры

  //Логический объем
  G4LogicalVolume* logDet2 =
    new G4LogicalVolume(solidDet2,            //its solid, объем
                        det_mat,             //its material, указываем материал детектора
                        "logDet2");         //its name, его имя

  //Физический объем детектора
  new G4PVPlacement(0,                       //no rotation, так же без вращения
                    G4ThreeVector(0,0,11.5*cm),         //at (0,0,0)
                    logDet2,                //its logical volume, подключаем логический объем
                    "physDet2",              //its name, имя физического объема
                    logicWorld,              //its mother  volume, родительский логический объем!
                    false,                   //no boolean operation, без булевых операций
                    0);                       //copy number, номер копии
                    //checkOverlaps);          //overlaps checking, флаг проверки перекрытия объемов
  







//  3
  G4Box* solidDet3 =
    new G4Box("solidDet3",                    //its name, имя
        0.5*det_sizeX, 0.5*det_sizeY, 0.5*det_sizeZ); //its size, размеры

  //Логический объем
  G4LogicalVolume* logDet3 =
    new G4LogicalVolume(solidDet3,            //its solid, объем
                        det_mat,             //its material, указываем материал детектора
                        "logDet3");         //its name, его имя

  //Физический объем детектора
  new G4PVPlacement(0,                       //no rotation, так же без вращения
                    G4ThreeVector(0,0,17*cm),         //at (0,0,0)
                    logDet3,                //its logical volume, подключаем логический объем
                    "physDet3",              //its name, имя физического объема
                    logicWorld,              //its mother  volume, родительский логический объем!
                    false,                   //no boolean operation, без булевых операций
                    0);                       //copy number, номер копии
                   // checkOverlaps);          //overlaps checking, флаг проверки перекрытия объемов
 





//  4
  G4Box* solidDet4 =
    new G4Box("solidDet4",                    //its name, имя
        0.5*det_sizeX, 0.5*det_sizeY, 0.5*det_sizeZ); //its size, размеры

  //Логический объем
  G4LogicalVolume* logDet4 =
    new G4LogicalVolume(solidDet4,            //its solid, объем
                        det_mat,             //its material, указываем материал детектора
                        "logDet4");         //its name, его имя

  //Физический объем детектора
  new G4PVPlacement(0,                       //no rotation, так же без вращения
                    G4ThreeVector(0,0,22.5*cm),         //at (0,0,0)
                    logDet4,                //its logical volume, подключаем логический объем
                    "physDet4",              //its name, имя физического объема
                    logicWorld,              //its mother  volume, родительский логический объем!
                    false,                   //no boolean operation, без булевых операций
                    0);                       //copy number, номер копии
                 //   checkOverlaps);          //overlaps checking, флаг проверки перекрытия объемов

 



  //
  // Свинцовая мишень, также используем параллелепипед
  //  
  
//1
   G4Box* solidTgt1 =
    new G4Box("Target1",                    //its name, имя
        0.5*tgt_sizeX, 0.5*tgt_sizeY, 0.5*3*cm); //its size, размеры

  //Логический объем
  G4LogicalVolume* logicTar1 =
    new G4LogicalVolume(solidTgt1,            //its solid, объем
                        tgt_mat,             //its material, указываем материал детектора
                        "Target1");         //its name, его имя

  //Физический объем
  new G4PVPlacement(0,                       //no rotation, так же без вращения
                    G4ThreeVector(0,0,9*cm),         //at (0,0,0)
                    logicTar1,                //its logical volume, подключаем логический объем
                    "Target1",              //its name, имя физического объема
                    logicWorld,              //its mother  volume, родительский логический объем!
                    false,                   //no boolean operation, без булевых операций
                    0);                       //copy number, номер копии
                  //checkOverlaps);          //overlaps checking, флаг проверки перекрытия объемов                

//2
   G4Box* solidTgt2 =
    new G4Box("Target2",                    //its name, имя
        0.5*tgt_sizeX, 0.5*tgt_sizeY, 0.5*3*cm); //its size, размеры

  //Логический объем
  G4LogicalVolume* logicTar2 =
    new G4LogicalVolume(solidTgt2,            //its solid, объем
                        tgt_mat,             //its material, указываем материал детектора
                        "Target2");         //its name, его имя

  //Физический объем
  new G4PVPlacement(0,                       //no rotation, так же без вращения
                    G4ThreeVector(0,0,14.5*cm),         //at (0,0,0)
                    logicTar2,                //its logical volume, подключаем логический объем
                    "Target2",              //its name, имя физического объема
                    logicWorld,              //its mother  volume, родительский логический объем!
                    false,                   //no boolean operation, без булевых операций
                    0);                       //copy number, номер копии
                 // checkOverlaps);          //overlaps checking, флаг проверки перекрытия объемов                


//3
   G4Box* solidTgt3 =
    new G4Box("Target3",                    //its name, имя
        0.5*tgt_sizeX, 0.5*tgt_sizeY, 0.5*3*cm); //its size, размеры

  //Логический объем
  G4LogicalVolume* logicTar3 =
    new G4LogicalVolume(solidTgt3,            //its solid, объем
                        tgt_mat,             //its material, указываем материал детектора
                        "Target3");         //its name, его имя

  //Физический объем
  new G4PVPlacement(0,                       //no rotation, так же без вращения
                    G4ThreeVector(0,0,20*cm),         //at (0,0,0)
                    logicTar3,                //its logical volume, подключаем логический объем
                    "Target3",              //its name, имя физического объема
                    logicWorld,              //its mother  volume, родительский логический объем!
                    false,                   //no boolean operation, без булевых операций
                    0);                       //copy number, номер копии
                  //checkOverlaps);          //overlaps checking, флаг проверки перекрытия объемов                





  //                  
  //Алюминиевая фольга на выходе в модуль
  //   
 G4Box* solidTgt0_out =
    new G4Box("Al_Target_out",                    //its name, имя
        0.5*world_sizeX, 0.5*world_sizeY, 0.5*tgt1_sizeZ); //its size, размеры

  //Логический объем
  G4LogicalVolume* logicTar0_out =
    new G4LogicalVolume(solidTgt0_out,            //its solid, объем
                        tgt_mat1,             //its material, указываем материал детектора
                        "Al_Target_out");         //its name, его имя

  //Физический объем
  new G4PVPlacement(0,                       //no rotation, так же без вращения
                    G4ThreeVector(0,0,20.5*cm),         //at (0,0,0)
                    logicTar0_out,                //its logical volume, подключаем логический объем
                    "Al_Target_out",              //its name, имя физического объема
                    logicWorld,              //its mother  volume, родительский логический объем!
                    false,                   //no boolean operation, без булевых операций
                    0);                       //copy number, номер копии
                //  checkOverlaps);          //overlaps checking, флаг проверки перекрытия объемов                







 
  //
  //always return the physical World
  //Всегда возвращает физический объем
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void ExG4DetectorConstruction01::ConstructSDandField()
{
  // Sensitive detectors
  // Объявление чуствительной области детектора, где можно получить подробную
  // информацию о состоянии и движении частицы
  // Назовем чуствительную область DetectorSD
  G4String trackerChamberSDname = "DetectorSD";
  // Создаем экземпляр чуствительной области
  ExG4DetectorSD* aTrackerSD = new ExG4DetectorSD(trackerChamberSDname);
  // Передаем указатель менеджеру
  G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD);
  // Setting aTrackerSD to all logical volumes with the same name
  // of "Chamber_LV".
  // Добавляем чуствительный объем ко всем логическим областям с
  // именем Detector
  SetSensitiveDetector("logDet1", aTrackerSD, true);
  SetSensitiveDetector("logDet2", aTrackerSD, true);
  SetSensitiveDetector("logDet3", aTrackerSD, true);
  SetSensitiveDetector("logDet4", aTrackerSD, true);
  SetSensitiveDetector("Al_Target_out", aTrackerSD, true);
}
