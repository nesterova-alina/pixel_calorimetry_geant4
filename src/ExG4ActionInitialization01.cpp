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
// $Id: B1ActionInitialization.cc 68058 2013-03-13 14:47:43Z gcosmo $
//
/// \file ExG4ActionInitialization01.cpp
/// \brief Implementation of the ExG4ActionInitialization01 class
#include "ExG4ActionInitialization01.hh"
#include "ExG4PrimaryGeneratorAction01.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "HistoManager.hh"
/// Обязательный класс, который должен быть объявлен в проекте Geant4
/// Имя класса может быть другим, и он долже наследоваться от
/// класса G4VUserActionInitialization
/// Конструктор
ExG4ActionInitialization01::ExG4ActionInitialization01()
 : G4VUserActionInitialization()
{}

//Деструктор
ExG4ActionInitialization01::~ExG4ActionInitialization01()
{}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExG4ActionInitialization01::BuildForMaster() const
{
 // Histo manager
 auto  histo = new HistoManager;
  // Actions
 SetUserAction(new RunAction(histo));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//Создание начального источника частиц
void ExG4ActionInitialization01::Build() const
{
  auto histo = new HistoManager;
  SetUserAction(new ExG4PrimaryGeneratorAction01);//Задается начальный источник частиц
// через обязательный класс ExG4PrimaryGeneratorAction01

  SetUserAction(new RunAction(histo));
 auto eventAction = new EventAction(histo);
  SetUserAction(eventAction);
//  SteppingAction* steppingAction = new SteppingAction(eventAction);
  SetUserAction(new SteppingAction(eventAction)); 
}
