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
// $Id: B1PrimaryGeneratorAction.cc 94307 2015-11-11 13:42:46Z gcosmo $
//
/// \file ExG4PrimaryGeneratorAction01.cpp
/// \brief Implementation of the ExG4PrimaryGeneratorAction01 class

#include "ExG4PrimaryGeneratorAction01.hh"
// Подключаем необходимы заголовочные файлы
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// Класс, в котором описывается положение, тип, енергия частиц, направление вылета
// и распределенние начальных частиц
ExG4PrimaryGeneratorAction01::ExG4PrimaryGeneratorAction01()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  // По умолчанию поставим 1 частицу
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  // Получаем встроеную в Geant4 таблицу частиц
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  // Ищем частицу, в нашем случае протон
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="e-");
  // Устанавливаем полученную частицу как испускаемые начальные частицы в источнике
  fParticleGun->SetParticleDefinition(particle);
  // Устанавливаем момент - направление движение частицы по (x,y,z)
  // Здесь установленно направление вдоль оси OZ
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  // Установка начальной энергии испускаемых частиц, 50 МэВ
  fParticleGun->SetParticleEnergy(150*MeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// Деструктор, удаляем созданный в конструкторе экземпляр класса источника G4ParticleGun
ExG4PrimaryGeneratorAction01::~ExG4PrimaryGeneratorAction01()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExG4PrimaryGeneratorAction01::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of ecah event
  //Эта функция вызывается в начале каждого первичного события
  // Задаем координаты источника частиц
  const G4double xmax = 1*cm;
  const G4double ymax = 1*cm;   
  
  //vertex 1 uniform on plane
  //
  G4double x=1.;
  G4double y=1.;
  G4double z = -140*cm;
  while (x*x+y*y > 1.0) {
  x = xmax*(2*G4UniformRand() - 1);  //x uniform in (-xmax, +xmax)
  y = ymax*(2*G4UniformRand() - 1);  //y uniform in (-ymax, +ymax)
}
  // Устанавливаем положение источника частиц
  fParticleGun->SetParticlePosition(G4ThreeVector(x,y,z));
  // Создаем начальное событие, запускаем первичную частицу
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
