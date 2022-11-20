// Подключаем заголовочные файлы
#include "G4RunManager.hh" // RunManager, класс из ядра Geant4,
//должен быть включен обязательно
#include "G4UImanager.hh" // Менеджер взаимодействия с пользователем
#include "ExG4DetectorConstruction01.hh" // Структура детектора,
//должен определяться пользователем
#include "FTFP_BERT.hh" // Подключается физика и частицы
// используемые в проекте, использов предопределенный в Geant4
#include "ExG4ActionInitialization01.hh" // Пользовательские классы
#include "ExG4PrimaryGeneratorAction01.hh"
//для получения данных о процессе моделирования
#ifdef G4UI_USE //Если используется интерфейс пользователя
#include "G4VisExecutive.hh"//Визуализация
#include "G4UIExecutive.hh"//Выбор соответствуещего интерфейса пользователя
#include "HistoManager.hh"
#include "SteppingVerbose.hh"
#include "QBBC.hh"
#include<G4UIterminal.hh>
#include<G4UItcsh.hh>
#include "G4UIExecutive.hh"
#include<G4VisExecutive.hh>
#include<G4Material.hh>
#include<G4UserRunAction.hh>
#include<G4Run.hh>
#include<iostream>
#include<string>
#include<CLHEP/Random/Random.h>
#include<unistd.h>
#include<time.h>
#endif

using namespace std;

int main(int argc,char** argv)
{
//Изменение зерна случайного числа, в качестве зенна берется текущее время
//Суть этой операции в том, что бы при каждом новом запуске генерировалась
//новая последовательность случайных чисел, иначе она будет все время одной
//и тойже, т.е. получаемые события будут одни и теже
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  CLHEP::HepRandom::setTheSeed(time(NULL));
	//CLHEP::HepRandom::setTheSeed(time(0)+getpid());

// construct the default run manager
// Создание класс G4RunManager, он управляет течением программы и
// управляет событиями при запуске проекта
G4RunManager* runManager = new G4RunManager;

// set mandatory initialization classes
// Установка обязательных инициализирующих классов
// Создание и определение детекторов и материалов
runManager->SetUserInitialization(new ExG4DetectorConstruction01);
// Создание физического листа - частиц и физических процессов
// в которых они участвуют, используется предопределенный в Geant4

        G4VModularPhysicsList* physicsList = new QBBC;
        physicsList->SetVerboseLevel(1);
        runManager->SetUserInitialization(physicsList);
// Определение начальных частиц, и прочие классы используемые
// для получения данных о частицах в процессе моделирования
runManager->SetUserInitialization(new ExG4ActionInitialization01);
// initialize G4 kernel
// Инициализация ядра Geant4
runManager->Initialize();
// Initialise Visualization Manager.
// Инициализация менеджера визуализации
G4VisManager* visManager = new G4VisExecutive;
visManager->Initialize();
// get the pointer to the UI manager and set verbosities
// Получение указателя на менеджера взаимодействия с пользователем
// нужен, что бы можно было отправлять команды в проект
G4UImanager* UImanager = G4UImanager::GetUIpointer();
if ( argc == 1 ) {//Если в командной строке есть параметр
// interactive mode : define UI session
#ifdef G4UI_USE
G4UIExecutive* ui = new G4UIExecutive(argc, argv);//Создание интерфейса пользователя
UImanager->ApplyCommand("/control/execute vis.mac");//Отрисовка по умолчанию
ui->SessionStart();//Запуск интерфейса пользователя
delete ui;//Удаление интерфейса пользователя
#endif
}
else {
// batch mode
// Пакетный режим
G4String command = "/control/execute ";//Команда выполнить
G4String fileName = argv[1];//Имя файла из командной строки при запуске проекта
UImanager->ApplyCommand(command+fileName);//Выполнение команды
}
// Окончание работы, вызов деструктора (удаление) G4RunManager
delete runManager;
return 0;
}
