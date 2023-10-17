#ifndef ENTITY_LIST
#define ENTITY_LIST
#include "Entity.h"
#include "SkillList.h"

Entity *Charactor1Ptr = new Entity("Charactor 1", 30, 5, 1, {skill1, skill3, skill2, skill4});
Entity *Charactor2Ptr = new Entity("Charactor 2", 30, 3, 2, {skill1, skill3, skill2});
Entity *Charactor3Ptr = new Entity("Charactor 3", 30, 1, 3, {skill5, skill3, skill2, skill4});
Entity *Charactor4Ptr = new Entity("Charactor 4", 30, 1, 2, {skill1, skill3, skill2, skill6});
Entity *Charactor5Ptr = new Entity("Charactor 5", 30, 5, 8, {skill6});
Entity *Charactor6Ptr = new Entity("Charactor 6", 30, 5, 8, {skill5, skill2, skill4});
Entity *Charactor7Ptr = new Entity("Charactor 7", 30, 5, 8, {skill1, skill2, skill4});
Entity *Charactor8Ptr = new Entity("Charactor 8", 30, 5, 8, {skill1, skill3, skill4});
Entity *Charactor9Ptr = new Entity("Charactor 9", 30, 5, 8, {skill2, skill4});
Entity *Charactor10Ptr = new Entity("Charactor 10", 9, 5, 8, {skill1, skill3, skill2, skill4});

#endif // !ENTITY_LIST