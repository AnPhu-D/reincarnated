#include <iostream>

#include <string>

#include "Bank.h"
#include "combatDisplay.h"
#include "combatInstance.h"
#include "sessionManager.h"

using namespace std;

Frame *promptFrame(ScreenGUI &targetGUI)
{
  unsigned posX;
  unsigned posY;
  unsigned sizeX;
  unsigned sizeY;

  cout << "-------------------" << endl;

  cout << "Frame Position X: ";
  cin >> posX;
  cout << "Frame Position Y: ";
  cin >> posY;

  cout << "Frame Size X: ";
  cin >> sizeX;
  cout << "Frame Size Y: ";
  cin >> sizeY;

  cout << "Position: (" << posX << ", " << posY << ")" << endl;
  cout << "Size: ( " << sizeX << "," << sizeY << " )" << endl;

  return targetGUI.createFrame(posX, posY, sizeX, sizeY);
}

void applyColorProfile(Frame *targ, std::string bg, std::string txt, std::string brdr)
{
  targ->setBackgroundColor(bg);
  targ->setTextColor(txt);
  targ->setBorderColor(brdr);
}

void applyHighlightProfile(Widget *targ, std::string bg, std::string txt, std::string brdr)
{
  targ->setHighlightColor(bg);
  targ->setHighlightTextColor(txt);
  targ->setHighlightBorderColor(brdr);
}

int main()
{
  // Instantiates its own ScreenRenderer
  SessionManager *gameSession = new SessionManager;
  ScreenRenderer *gameRenderService = gameSession->getRenderer();

  //------------------------------------------------------
  // Session Instantiation
  // Main Menu
  ScreenGUI *mainMenuScreen = new ScreenGUI(100, 25);

  std::string mainMenuSessionID = "MainMenu";
  MenuSession *mainMenuSession = new MenuSession(mainMenuScreen, gameRenderService, mainMenuSessionID);
  gameSession->addSession(mainMenuSession, mainMenuSessionID);

  Frame *mainMenuOutline = mainMenuScreen->createFrame(1, 1, 100 - 1, 25 - 1);

  WidgetContext *mainMenu_GameInfoContext = new WidgetContext;
  mainMenuSession->registerWidgetContext(mainMenu_GameInfoContext);

  WidgetContext *mainMenuButtons = new WidgetContext;
  mainMenuSession->registerWidgetContext(mainMenuButtons);
  mainMenuSession->setDefaultWidgetContext(1);

  Widget *mainMenu_PlayGame = mainMenuScreen->createWidget((100 - 20) / 2 + 1, 2 + (3 * 1), 20, 3);
  mainMenu_PlayGame->setContainedText("     Play game");
  mainMenuButtons->addWidget(mainMenu_PlayGame);
  applyHighlightProfile(mainMenu_PlayGame, "White", "Black", "Black");

  Widget *mainMenu_Settings = mainMenuScreen->createWidget((100 - 20) / 2 + 1, 2 + (3 * 2), 20, 3);
  mainMenu_Settings->setContainedText("     Settings");
  mainMenuButtons->addWidget(mainMenu_Settings);
  applyHighlightProfile(mainMenu_Settings, "White", "Black", "Black");

  Widget *mainMenu_ExitGame = mainMenuScreen->createWidget((100 - 20) / 2 + 1, 2 + (3 * 3), 20, 3);
  mainMenu_ExitGame->setContainedText("     Exit game");
  mainMenuButtons->addWidget(mainMenu_ExitGame);
  applyHighlightProfile(mainMenu_ExitGame, "White", "Black", "Black");

  Frame *mainMenu_GameTextLabel = mainMenuScreen->createFrame(1 + 1, 1 + 1, 100 - 2 - 1, 3);
  mainMenu_GameTextLabel->setContainedText("  R'eincarnated");

  ScrollingWidget *mainMenu_GameDesc = mainMenuScreen->createScrollingWidget(1 + 1, 1 + 1 + 3, 35, 25 - 2 - (1 + 1 + 3));
  mainMenu_GameDesc->setTextXPadding(2);
  mainMenu_GameDesc->setRawText("R'eincarnated is a terminal based JRPG that takes you on an adventure to survive in a fantastical world. Help the heroes face their opponents and forge a lasting story!");
  mainMenu_GameDesc->setHighlightColor("none");
  mainMenu_GameDesc->setHighlightTextColor("Bright White");
  mainMenu_GameDesc->setHighlightBorderColor("Bright White");
  mainMenu_GameInfoContext->addWidget(mainMenu_GameDesc);

  //------------------------------------------------------
  ScreenGUI *newLoadGameScreen = new ScreenGUI(100, 25);

  std::string newLoadGameSessionID = "NewLoadGame";
  MenuSession *newLoadGameSession = new MenuSession(newLoadGameScreen, gameRenderService, newLoadGameSessionID);
  gameSession->addSession(newLoadGameSession, newLoadGameSessionID);

  Frame *newLoadGameOutline = newLoadGameScreen->createFrame(1, 1, 100 - 1, 25 - 1);

  WidgetContext *newLoadGameButtons = new WidgetContext;
  newLoadGameSession->registerWidgetContext(newLoadGameButtons);

  Widget *newLoadGame_NewGame = newLoadGameScreen->createWidget((100 - 20) / 2 + 1, 2 + (3 * 1), 20, 3);
  newLoadGame_NewGame->setContainedText("     New Game");
  newLoadGameButtons->addWidget(newLoadGame_NewGame);
  applyHighlightProfile(newLoadGame_NewGame, "White", "Black", "Black");

  Widget *newLoadGame_LoadGame = newLoadGameScreen->createWidget((100 - 20) / 2 + 1, 2 + (3 * 2), 20, 3);
  newLoadGame_LoadGame->setContainedText("     Load Game");
  newLoadGameButtons->addWidget(newLoadGame_LoadGame);
  applyHighlightProfile(newLoadGame_LoadGame, "White", "Black", "Black");

  Widget *newLoadGame_BackToMenu = newLoadGameScreen->createWidget((100 - 20) / 2 + 1, 2 + (3 * 3), 20, 3);
  newLoadGame_BackToMenu->setContainedText("   Back to Menu");
  newLoadGameButtons->addWidget(newLoadGame_BackToMenu);
  applyHighlightProfile(newLoadGame_BackToMenu, "White", "Black", "Black");

  Frame *newLoadGame_GameTextLabel = newLoadGameScreen->createFrame(1 + 1, 1 + 1, 100 - 2 - 1, 3);
  newLoadGame_GameTextLabel->setContainedText("  R'eincarnated");

  //------------------------------------------------------
  // Starter Town a
  ScreenGUI *starterTownScreen = new ScreenGUI(100, 25);

  std::string starterTownSessionID = "StarterTown";
  MenuSession *starterTownSession = new MenuSession(starterTownScreen, gameRenderService, starterTownSessionID);
  gameSession->addSession(starterTownSession, starterTownSessionID);

  Frame *starterTownOutline = starterTownScreen->createFrame(1, 1, 100 - 1, 25 - 1);

  Frame *starterTown_LevelDisplay = starterTownScreen->createFrame(1 + 1, 1 + 1, 30 + 2 + 2, 3);
  starterTown_LevelDisplay->setContainedText(" Lvl  0: [--------------------]"); // TODO: Hook to gamemanager.player state

  Frame *starterTown_GoldDisplay = starterTownScreen->createFrame(1 + 1 + starterTown_LevelDisplay->getSX() - 1, 1 + 1, 10 + 2 + 2, 3);
  starterTown_GoldDisplay->setContainedText(" 10000 Gold");

  Frame *starterTown_GemDisplay = starterTownScreen->createFrame(1 + 1 + starterTown_LevelDisplay->getSX() - 1 + starterTown_GoldDisplay->getSX() - 1, 1 + 1, 10 + 2 + 2, 3);
  starterTown_GemDisplay->setContainedText(" 10000 Gems");

  Frame *tempFrame = starterTownScreen->createFrame(1 + 1 + starterTown_LevelDisplay->getSX() - 1 + starterTown_GoldDisplay->getSX() - 1 + starterTown_GemDisplay->getSX() - 1, 1 + 1, 31, 3);

  WidgetContext *starterTownButtons = new WidgetContext;
  starterTownSession->registerWidgetContext(starterTownButtons);

  Widget *starterTown_Market = starterTownScreen->createWidget((100 - 20) / 2 + 1, 2 + (3 * 1), 20, 3);
  starterTown_Market->setContainedText("      Market");
  starterTownButtons->addWidget(starterTown_Market);

  Widget *starterTown_Guild = starterTownScreen->createWidget((100 - 20) / 2 + 1, 2 + (3 * 2), 20, 3);
  starterTown_Guild->setContainedText("      Guild");
  starterTownButtons->addWidget(starterTown_Guild);

  Widget *starterTown_Adventure = starterTownScreen->createWidget((100 - 20) / 2 + 1, 2 + (3 * 3), 20, 3);
  starterTown_Adventure->setContainedText("     Adventure");
  starterTownButtons->addWidget(starterTown_Adventure);

  WidgetContext *starterTown_MenuButtons = new WidgetContext;
  starterTownSession->registerWidgetContext(starterTown_MenuButtons);

  Widget *starterTown_MenuButton = starterTownScreen->createWidget(100 - (4 + 2 + 2) - 1, 1 + 1, 4 + 2 + 2, 3);
  starterTown_MenuButton->setContainedText(" Menu ");
  starterTown_MenuButtons->addWidget(starterTown_MenuButton);

  //------------------------------------------------------

  //------------------------------------------------------
  mainMenu_PlayGame->bindFunction([gameSession, newLoadGameSessionID]()
                                  { gameSession->transitionToSession(newLoadGameSessionID); });
  mainMenu_Settings->bindFunction([]() {});
  mainMenu_ExitGame->bindFunction([]() {});
  mainMenu_GameDesc->bindFunction([]() {});

  newLoadGame_NewGame->bindFunction([gameSession, starterTownSessionID]()
                                    { gameSession->transitionToSession(starterTownSessionID); });
  newLoadGame_LoadGame->bindFunction([]() {});
  newLoadGame_BackToMenu->bindFunction([gameSession, mainMenuSessionID]()
                                       { gameSession->transitionToSession(mainMenuSessionID); });

  starterTown_Market->bindFunction([gameSession]() {

  });
  starterTown_Guild->bindFunction([gameSession]() {

  });
  starterTown_Adventure->bindFunction([gameSession]() {

  });
  starterTown_MenuButton->bindFunction([gameSession]()
                                       { gameSession->transitionToSession("MainMenu"); });

  //------------------------------------------------------

  // Instantiate Combat Test Session
  // Menthy

  Party partyA = Party(4);
  partyA.addMember(Bank::_EntityBank->getEntity(0));
  partyA.addMember(Bank::_EntityBank->getEntity(1));
  partyA.addMember(Bank::_EntityBank->getEntity(3));
  partyA.addMember(Bank::_EntityBank->getEntity(2));
  Party partyB = Party(3);
  partyB.addMember(Bank::_EntityBank->getEntity(4));
  partyB.addMember(Bank::_EntityBank->getEntity(5));
  partyB.addMember(Bank::_EntityBank->getEntity(6));

  CombatInstance combatInstance = CombatInstance(&partyA, &partyB);
  string combatTestSessionID = "combatTestSession";
  CombatDisplay testCD(&combatInstance, gameSession, combatTestSessionID);

  // CombatInstance testCombat;

  gameSession->cleanupCurrentSession();
  gameSession->setCurrentSession(combatTestSessionID);

  gameSession->getCurrentSession()->setWidgetContext(gameSession->getCurrentSession()->getDefaultWidgetContext());
  gameSession->getCurrentSession()->setWidget(0);

  gameSession->getCurrentSession()->displayGUI();
  gameSession->getRenderer()->highlightWidget(gameSession->getCurrentSession()->getCurrentWidget());
  Services::_CursorServiceHandle->moveCursor(100 + 1, 25);

  //------------------------------------------------------
  // Please Re-Enable

  // mainMenuSession->setWidgetContext(mainMenuSession->getDefaultWidgetContext());
  // mainMenuSession->setWidget(0);

  // gameSession->cleanupCurrentSession();
  // gameSession->setCurrentSession(mainMenuSessionID);

  // gameSession->getCurrentSession()->displayGUI();
  // gameSession->getRenderer()->highlightWidget(mainMenu_PlayGame);
  // Services::_CursorServiceHandle->moveCursor(100 + 1, 25);

  //------------------------------------------------------
  // Game Launch

  std::string KPEID = "OnKeyPress";
  KeyPressedEvent *KPEHandle = Services::_UserInputServiceHandle->getKeyPressedEvent();
  std::function<void(Event *)> KPEFunction = [gameSession, KPEID](Event *eventHandle)
  {
    gameSession->parseKeyPress(eventHandle);
  };
  EventConnection *KPEConnection = new EventConnection(KPEID, KPEFunction);
  KPEHandle->bindFunction(KPEConnection);

  Services::_UserInputServiceHandle->launch();

  //------------------------------------------------------
  // Cleanup

  Services::_CursorServiceHandle->moveCursor(101, 25);

  delete KPEConnection;
  delete gameSession;

  Services::_CursorServiceHandle->deleteService();
  Services::_HighlightServiceHandle->deleteService();
  Services::_LineDrawServiceHandle->deleteService();
  Services::_TextColorServiceHandle->deleteService();
  Services::_UserInputServiceHandle->deleteService();

  Bank::_EntityBank->deleteBank();
  Bank::_WeaponBank->deleteBank();
  Bank::_SkillBank->deleteBank();
  Bank::_ArmorBank->deleteBank();

  return 0;
}