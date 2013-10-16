UPDATE `creature_template` SET `npcflag`=16777216, `AIName`='' WHERE `entry`=34306;

DELETE FROM `gameobject_loot_template` WHERE `item` = '46356';
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES
(27237, 46356, -100);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '34306';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(34306, 65127, 3);