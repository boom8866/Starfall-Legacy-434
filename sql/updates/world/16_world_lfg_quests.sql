UPDATE `quest_template` SET `SpecialFlags`= 9 WHERE `id` IN (SELECT `otherQuestId` FROM `lfg_dungeon_rewards`);

UPDATE `quest_template` SET `SpecialFlags`= 8 WHERE `id` IN (SELECT `firstQuestId` FROM `lfg_dungeon_rewards`);

UPDATE `quest_template` SET `SpecialFlags`= 9 WHERE `id` IN (25485, 25483, 25482, 25484, 28905, 29185, 30110);
