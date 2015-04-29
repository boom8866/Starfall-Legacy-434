UPDATE `creature` SET `id`=51988 WHERE `guid`=31254;
UPDATE `creature` SET `id`=51989 WHERE `guid`=161970;
UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN (732529, 738912);
UPDATE `quest_template` SET `RequiredRaces`=946 WHERE `Id` IN (10942, 172);
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=2 WHERE `item`=43507 AND `ChanceOrQuestChance` < 1;
UPDATE `creature_loot_template` SET `groupid`=2 WHERE `item`=43507;
UPDATE `item_loot_template` SET `groupid`=1 WHERE `entry`=44113 AND `item`=33925;
UPDATE `quest_template` SET `RewardItemId1`=46545, `RewardItemCount1`=1 WHERE `Id`=13959;
UPDATE `quest_template` SET `RewardItemId1`=46544, `RewardItemCount1`=1 WHERE `Id`=13960;
UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=738913;
UPDATE `gameobject` SET `phaseMask`=1 WHERE `guid`=729174;

DELETE FROM `game_event_creature` WHERE `guid` = '738913';
INSERT INTO `game_event_creature` (`eventEntry`, `guid`) VALUES
(10, 738913);

DELETE FROM `game_event_gameobject` WHERE `guid` = '729874';
INSERT INTO `game_event_gameobject` (`eventEntry`, `guid`) VALUES
(10, 729874);

UPDATE `gossip_menu_option` SET `option_id`=3, `npc_option_npcflag`=128 WHERE `menu_id`=12761 AND `id`=0;

DELETE FROM `npc_vendor` WHERE `entry` = '52358';
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `type`) VALUES
(52358, 0, 34498, 0, 0, 0, 1),
(52358, 0, 44481, 0, 0, 0, 1),
(52358, 0, 44482, 0, 0, 0, 1),
(52358, 0, 44599, 0, 0, 0, 1),
(52358, 0, 44601, 0, 0, 0, 1),
(52358, 0, 44606, 0, 0, 0, 1),
(52358, 0, 45057, 0, 0, 0, 1),
(52358, 0, 46725, 0, 0, 0, 1),
(52358, 0, 48601, 0, 0, 0, 1),
(52358, 0, 54343, 0, 0, 0, 1),
(52358, 0, 54436, 0, 0, 0, 1),
(52358, 0, 54437, 0, 0, 0, 1),
(52358, 0, 54438, 0, 0, 0, 1),
(52358, 0, 68890, 0, 0, 0, 1),
(52358, 0, 69057, 0, 0, 0, 1);

DELETE FROM `npc_vendor` WHERE `item` = '69057';
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`, `type`) VALUES
(52358, 0, 69057, 0, 0, 0, 1),
(52809, 0, 69057, 0, 0, 0, 1);

DELETE FROM `spell_script_names` WHERE `spell_id` IN (23012, 23013);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(23012, 'spell_cw_summon_orphan'),
(23013, 'spell_cw_summon_orphan');