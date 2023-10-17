#include "combatDisplay.h"

CombatDisplay::CombatDisplay(CombatInstance* _linkedCombatInstance, SessionManager* _gameSession, string _displaySessionID)
    : linkedCombatInstance(_linkedCombatInstance), gameSession(_gameSession), displaySessionID(_displaySessionID) {
  // Remember to De-Allocate!
  ScreenRenderer* gameRenderService = gameSession->getRenderer();

  // GUI Drivers
  combatScreen = new ScreenGUI(100, 25);
  combatSession = new MenuSession(combatScreen, gameRenderService, displaySessionID);
  gameSession->addSession(combatSession, displaySessionID);

  // DisplayFrames
  combatOutline = combatScreen->createFrame(1, 1, 100 - 1, 25 - 1);

  roundFrame = combatScreen->createFrame((100 - (20 + 2 + 2)) / 2 + 1, 1 + 1, 20 + 2 + 2, 3);
  roundFrame->setContainedText("Round 1");

  // skillsHeaderFrame = combatScreen->createFrame((100 - (20 + 2 + 2)) / 2 + 1, 1 + 1 + 3, 20 + 2 + 2, 3);
  // skillsHeaderFrame->setContainedText("Skills");

  partyATurnFrame = combatScreen->createFrame(1 + 1 + 3, 1 + 1, 20 + 2 + 2, 3);
  partyATurnFrame->setContainedText("Your Turn");
  partyATurnFrame->setTextColor("Blue");
  partyATurnFrame->setBorderColor("Blue");

  partyBTurnFrame = combatScreen->createFrame(100 - (20 + 2 + 2) - 1 - 3, 1 + 1, 20 + 2 + 2, 3);
  partyBTurnFrame->setContainedText("Enemy Turn");
  partyBTurnFrame->setTextColor("Red");
  partyBTurnFrame->setBorderColor("Red");

  // Context 0 (Party A)
  combatContext_0 = new WidgetContext;
  combatSession->registerWidgetContext(combatContext_0);

  Party partyA = linkedCombatInstance->getPartyA();
  const vector<Entity*> partyAMembers = partyA.getPartyMembers();

  unsigned c0_tlx = 1 + 1 + 3;
  unsigned c0_tly = 1 + 1 + 3 + 3;

  for (unsigned i = 0; i < partyAMembers.size(); ++i) {
    Widget* memberWidget = combatScreen->createWidget(c0_tlx, c0_tly + (i * 2) - 3, 20 + 2 + 2, 3);
    Attribute* health = partyAMembers.at(i)->getHealthAttribute();
    unsigned maxHealth = health->getMaxValue();
    unsigned currentHealth = health->getValue();
    memberWidget->setContainedText(partyAMembers.at(i)->getName() + " " + std::to_string(currentHealth) + "/" + std::to_string(maxHealth));  // Implement spacing

    entityToWidget[partyAMembers.at(i)] = memberWidget;

    memberWidget->bindFunction([this, i, memberWidget]() {
      Entity* actingEntity = this->linkedCombatInstance->getTurnOrder().at(this->linkedCombatInstance->getTurnIndex());
      Skill* selectedSkill = actingEntity->getSkill(this->skillIndex);
      unsigned skillRange = selectedSkill->getAttackRange();

      Entity* targetEntity = this->linkedCombatInstance->getPartyA().getPartyMembers().at(i);
      unsigned targetTurnIndex = this->combatContext_0_parallelETI.at(i);

      // TODO: Refactor this please
      auto it = this->targets.begin();
      bool removed = false;

      // TODO: Abstract
      while (it != this->targets.end()) {
        if (*it == targetTurnIndex) {
          // Handle is targetted case
          this->targets.erase(it);
          removed = true;

          memberWidget->setTextColor("Default");
          memberWidget->setHighlightTextColor("Default");

          break;
        }
        ++it;
      }

      if (removed == false) {
        if (this->targets.size() >= skillRange) {
          return;
        }

        this->targets.push_back(targetTurnIndex);
        memberWidget->setTextColor("Magenta");
        memberWidget->setHighlightTextColor("Magenta");
      }
      for (unsigned i = 0; i < this->combatContext_0_contents.size(); ++i) {
        this->gameSession->getRenderer()->renderFrame(this->combatContext_0_contents.at(i));
      }
      this->gameSession->getRenderer()->highlightWidget(this->combatSession->getCurrentWidget());
    });

    combatContext_0->addWidget(memberWidget);
    combatContext_0_contents.push_back(memberWidget);
    combatContext_0_parallelETI.push_back(getEntityTurnIndex(partyAMembers.at(i)));
  }

  // Context 1 (Skills)
  combatContext_1 = new WidgetContext;
  combatSession->registerWidgetContext(combatContext_1);

  unsigned c1_tlx = (100 - (20 + 2 + 2)) / 2 + 1;
  unsigned c1_tly = 1 + 1 + 3;

  for (unsigned i = 0; i < 4; ++i) {
    Widget* skillWidget = combatScreen->createWidget(c1_tlx, c1_tly + (i * 2), 20 + 2 + 2, 3);
    skillWidget->setContainedText("Skill " + std::to_string(i));

    skillWidget->bindFunction([this, i, skillWidget]() {
      this->skillIndex = i;

      if (this->selectedSkillWidget == skillWidget) {
        return;
      }

      if (this->selectedSkillWidget != nullptr) {
        this->selectedSkillWidget->setTextColor("Default");
        this->selectedSkillWidget->setHighlightTextColor("Default");
      }
      this->selectedSkillWidget = skillWidget;
      this->selectedSkillWidget->setTextColor("Magenta");
      this->selectedSkillWidget->setHighlightTextColor("Magenta");

      // Clear targets on skill selections
      this->clearSelection();

      // TODO: Implement re-render context as refactored
      for (unsigned i = 0; i < 4; ++i) {
        this->gameSession->getRenderer()->renderFrame(this->combatContext_1_contents.at(i));
      }
      this->gameSession->getRenderer()->highlightWidget(this->combatSession->getCurrentWidget());
    });

    combatContext_1->addWidget(skillWidget);
    combatContext_1_contents.push_back(skillWidget);
  }
  selectedSkillWidget = combatContext_1_contents.at(skillIndex);
  this->selectedSkillWidget->setTextColor("Magenta");
  this->selectedSkillWidget->setHighlightTextColor("Magenta");

  // Context 2 (Party B)
  combatContext_2 = new WidgetContext;
  combatSession->registerWidgetContext(combatContext_2);

  Party partyB = linkedCombatInstance->getPartyB();
  const vector<Entity*> partyBMembers = partyB.getPartyMembers();

  unsigned c2_tlx = 100 - (20 + 2 + 2) - 1 - 3;
  unsigned c2_tly = 1 + 1 + 3 + 3;

  for (unsigned i = 0; i < partyBMembers.size(); ++i) {
    Widget* memberWidget = combatScreen->createWidget(c2_tlx, c2_tly + (i * 2) - 3, 20 + 2 + 2, 3);
    Attribute* health = partyBMembers.at(i)->getHealthAttribute();
    unsigned maxHealth = health->getMaxValue();
    unsigned currentHealth = health->getValue();
    memberWidget->setContainedText(partyBMembers.at(i)->getName() + " " + std::to_string(currentHealth) + "/" + std::to_string(maxHealth));  // Implement spacing

    entityToWidget[partyBMembers.at(i)] = memberWidget;

    memberWidget->bindFunction([this, i, memberWidget]() {
      Entity* actingEntity = this->linkedCombatInstance->getTurnOrder().at(this->linkedCombatInstance->getTurnIndex());
      Skill* selectedSkill = actingEntity->getSkill(this->skillIndex);
      unsigned skillRange = selectedSkill->getAttackRange();

      Entity* targetEntity = this->linkedCombatInstance->getPartyB().getPartyMembers().at(i);
      unsigned targetTurnIndex = this->combatContext_2_parallelETI.at(i);

      // TODO: Refactor this please
      auto it = this->targets.begin();
      bool removed = false;

      while (it != this->targets.end()) {
        if (*it == targetTurnIndex) {
          // Handle is targetted case
          this->targets.erase(it);
          removed = true;

          memberWidget->setTextColor("Default");
          memberWidget->setHighlightTextColor("Default");

          break;
        }
        ++it;
      }

      if (removed == false) {
        if (this->targets.size() >= skillRange) {
          return;
        }
        this->targets.push_back(targetTurnIndex);
        memberWidget->setTextColor("Magenta");
        memberWidget->setHighlightTextColor("Magenta");
      }
      for (unsigned i = 0; i < this->combatContext_2_contents.size(); ++i) {
        this->gameSession->getRenderer()->renderFrame(this->combatContext_2_contents.at(i));
      }
      this->gameSession->getRenderer()->highlightWidget(this->combatSession->getCurrentWidget());
    });

    combatContext_2->addWidget(memberWidget);
    combatContext_2_contents.push_back(memberWidget);
    combatContext_2_parallelETI.push_back(getEntityTurnIndex(partyBMembers.at(i)));
  }

  // Context 3 (End Turn)
  combatContext_3 = new WidgetContext;
  combatSession->registerWidgetContext(combatContext_3);

  endTurnWidget = combatScreen->createWidget(100 - (8 + 2 + 2) - 1, 25 - (3) - 1, 8 + 2 + 2, 3);
  combatContext_3->addWidget(endTurnWidget);

  endTurnWidget->setContainedText("End Turn");
  endTurnWidget->bindFunction([this]() {
    if (this->linkedCombatInstance->isATurn()) {
      // If it is the player's turn
      Services::_CursorServiceHandle->moveCursor(101, 5);
      std::cout << "SI:" << this->skillIndex << " | Targs: " << this->targets.size();

      this->linkedCombatInstance->handleTurn(this->skillIndex, this->targets);

      // TODO: Render health state
      // TODO: Implement render-on-need caching, i.e. store those whose health changes and only re render them
      this->refreshHealth();
      this->clearSelection();
    } else {
      // If it is not the player's turn
      this->linkedCombatInstance->handleTurn();
    }
  });

  this->colorActingEntity();
}

CombatDisplay::~CombatDisplay() {
}

unsigned CombatDisplay::getEntityTurnIndex(Entity* targetEntity) const {
  const vector<Entity*> turnOrder = linkedCombatInstance->getTurnOrder();
  for (unsigned i = 0; i < turnOrder.size(); ++i) {
    if (targetEntity == turnOrder.at(i)) {
      return i;
    }
  }

  throw std::runtime_error("Could not find turn index for entity!");
}

void CombatDisplay::clearSelection() {
  targets.clear();
  for (unsigned i = 0; i < combatContext_0_contents.size(); ++i) {
    combatContext_0_contents.at(i)->setTextColor("Default");
    combatContext_0_contents.at(i)->setHighlightTextColor("Default");
  }
  for (unsigned i = 0; i < combatContext_2_contents.size(); ++i) {
    combatContext_2_contents.at(i)->setTextColor("Default");
    combatContext_2_contents.at(i)->setHighlightTextColor("Default");
  }

  for (unsigned i = 0; i < combatContext_0_contents.size(); ++i) {
    gameSession->getRenderer()->renderFrame(combatContext_0_contents.at(i));
  }
  for (unsigned i = 0; i < combatContext_2_contents.size(); ++i) {
    gameSession->getRenderer()->renderFrame(combatContext_2_contents.at(i));
  }
  gameSession->getRenderer()->highlightWidget(combatSession->getCurrentWidget());
  colorActingEntity();
}

void CombatDisplay::refreshHealth() {
  const vector<Entity*> partyAMembers = linkedCombatInstance->getPartyA().getPartyMembers();
  const vector<Entity*> partyBMembers = linkedCombatInstance->getPartyB().getPartyMembers();
  for (unsigned i = 0; i < partyAMembers.size(); ++i) {
    Widget* memberWidget = combatContext_0_contents.at(i);
    Attribute* health = partyAMembers.at(i)->getHealthAttribute();
    unsigned maxHealth = health->getMaxValue();
    unsigned currentHealth = health->getValue();
    memberWidget->setContainedText(partyAMembers.at(i)->getName() + " " + std::to_string(currentHealth) + "/" + std::to_string(maxHealth));  // Implement spacing
    gameSession->getRenderer()->renderFrame(memberWidget);
  }
  for (unsigned i = 0; i < partyBMembers.size(); ++i) {
    Widget* memberWidget = combatContext_2_contents.at(i);
    Attribute* health = partyBMembers.at(i)->getHealthAttribute();
    unsigned maxHealth = health->getMaxValue();
    unsigned currentHealth = health->getValue();
    memberWidget->setContainedText(partyBMembers.at(i)->getName() + " " + std::to_string(currentHealth) + "/" + std::to_string(maxHealth));  // Implement spacing
    gameSession->getRenderer()->renderFrame(memberWidget);
  }
}

void CombatDisplay::colorActingEntity() {
  Entity* actingEntity = linkedCombatInstance->getTurnOrder().at(linkedCombatInstance->getTurnIndex());
  Widget* actingEntityWidget = entityToWidget[actingEntity];

  actingEntityWidget->setTextColor("Cyan");
  actingEntityWidget->setHighlightTextColor("Cyan");

  gameSession->getRenderer()->renderFrame(actingEntityWidget);
}