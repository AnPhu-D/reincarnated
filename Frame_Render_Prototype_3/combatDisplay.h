#ifndef __COMBATDISPLAY_H__
#define __COMBATDISPLAY_H__

#include <map>

#include "combatInstance.h"
#include "entity.h"
#include "party.h"

#include "gameManager.h"
#include "sessionManager.h"

using std::map;
using std::string;
using std::vector;

// Metastructure
class CombatDisplay {
 public:
  CombatDisplay(CombatInstance* _linkedCombatInstance, SessionManager* _gameSession, string _displaySessionID);
  ~CombatDisplay();

 private:
  // State
  SessionManager* gameSession;
  CombatInstance* linkedCombatInstance;
  string displaySessionID;

  // Selection State
  map<Entity*, Widget*> entityToWidget;
  Widget* selectedSkillWidget = nullptr;

  // Request State
  unsigned skillIndex = 0;
  vector<unsigned> targets;
  unsigned getEntityTurnIndex(Entity* targetEntity) const;

  // GUI Drivers
  ScreenGUI* combatScreen;
  MenuSession* combatSession;

  // DisplayFrames
  Frame* combatOutline;

  Frame* roundFrame;
  Frame* partyATurnFrame;
  Frame* partyBTurnFrame;

  // Context 0 (Party A)
  WidgetContext* combatContext_0;
  vector<Widget*> combatContext_0_contents;
  vector<unsigned> combatContext_0_parallelETI;

  // Context 1 (Skills)
  // Frame* skillsHeaderFrame;
  WidgetContext* combatContext_1;
  vector<Widget*> combatContext_1_contents;

  // Context 2 (Party B)
  WidgetContext* combatContext_2;
  vector<Widget*> combatContext_2_contents;
  vector<unsigned> combatContext_2_parallelETI;

  // Context 3 (End Turn)
  WidgetContext* combatContext_3;
  Widget* endTurnWidget;
  
  void clearSelection();
  void deselectTarget(unsigned targetTurnIndex, Widget* memberWidget);

  void refreshHealth();
  void colorActingEntity();
};

#endif