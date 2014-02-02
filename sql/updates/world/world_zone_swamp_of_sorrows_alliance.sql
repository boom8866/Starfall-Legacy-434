DELETE FROM `creature_loot_template` WHERE `item` = '61356';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(922, 61356, -100, 1, 0, 1, 1);

UPDATE `creature_template` SET `mindmg`=83, `maxdmg`=125, `attackpower`=31 WHERE `entry`=45809;

-- Deceased Bogpaddle Privateer
SET @ENTRY := 46014;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,56,61923,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Force Despawn");

UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=46014;
UPDATE `creature_template` SET `flags_extra`=0 WHERE `entry`=45701;
UPDATE `creature_template` SET `mindmg`=85, `maxdmg`=127, `attackpower`=32, `InhabitType`=3 WHERE `entry`=45701;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12099 AND `id`=0;

DELETE FROM `conditions` WHERE `SourceGroup`=12099;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12099, 0, 0, 0, 9, 0, 27600, 0, 0, 0, 0, 0, '', 'In With a Bang - Show gossip only if quest 27600 is active');

UPDATE `spell_target_position` SET `target_position_x`=-10168.24, `target_position_y`=-4179.22, `target_position_z`=23.89, `target_orientation`=5.12 WHERE  `id`=85565 AND `effIndex`=0;
UPDATE `creature_template` SET `VehicleId`=940, `InhabitType`=4 WHERE `entry` IN (45873, 46504);

-- Lil' Crazy Jerry
SET @ENTRY := 46245;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,12099,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12099,0,0,0,85,85565,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Vehicle");

-- The Baron's Cannon
SET @ENTRY := 45873;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,85,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Invoker"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Phase 1"),
(@ENTRY,@SOURCETYPE,2,0,60,1,100,1,3000,3000,3000,3000,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (3 secs) - Remove Passenger"),
(@ENTRY,@SOURCETYPE,3,0,28,1,100,1,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Force Despawn");

UPDATE `creature` SET `phaseMask`=1, `spawndist`=10, `MovementType`=1 WHERE `id` IN (45914, 45934);
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12292 AND `id`=0;

DELETE FROM `conditions` WHERE `SourceGroup`=12292;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(28, 12292, 0, 0, 0, 9, 0, 27600, 0, 0, 0, 0, 0, '', 'In With a Bang - Show gossip only if quest 27600 is active');

UPDATE `spell_target_position` SET `target_position_x`=-9966.91, `target_position_y`=-4541.90, `target_position_z`=14.06, `target_orientation`=2.08 WHERE `id`=86685 AND `effIndex`=0;
UPDATE `gameobject` SET `phaseMask`=1, `spawntimesecs`=120 WHERE `guid` IN (728560, 728558, 728559, 728557);

-- The Baron's Cannon
SET @ENTRY := 46504;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,85,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Invoker"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Phase 1"),
(@ENTRY,@SOURCETYPE,2,0,60,1,100,1,3000,3000,3000,3000,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (3 secs) - Remove Passenger"),
(@ENTRY,@SOURCETYPE,3,0,28,1,100,1,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Force Despawn");

-- Landward Cannon
SET @ENTRY := 206679;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,12292,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,12292,0,0,0,85,86685,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Vehicle");

DELETE FROM `gameobject_loot_template` WHERE `item` IN (61921, 61922, 61373);
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(205826, 61921, -100, 1, 0, 1, 1),
(205827, 61922, -100, 1, 0, 1, 1),
(205828, 61373, -100, 1, 0, 1, 1);

UPDATE `gameobject_template` SET `data1`=205826 WHERE `entry`=205826;
UPDATE `gameobject_template` SET `data1`=205827 WHERE `entry`=205827;
UPDATE `gameobject_template` SET `data1`=205828 WHERE `entry`=205828;

UPDATE `creature_template` SET `mindmg`=85, `maxdmg`=127, `attackpower`=32 WHERE `entry` IN (45967, 46368, 46365, 46366, 46367, 46369, 46371, 46146);
UPDATE `creature_template` SET `unit_flags`=0, `unit_flags2`=2048, `dynamicflags`=0 WHERE `entry`=45887;
UPDATE `creature_template_addon` SET `bytes2`=0 WHERE `entry`=45887;
UPDATE `quest_template` SET `PrevQuestId`='27704' WHERE `Id`=27705;
UPDATE `quest_template` SET `PrevQuestId`='27705' WHERE `Id`=27768;
UPDATE `quest_template` SET `PrevQuestId`='27768' WHERE `Id`=27773;
UPDATE `quest_template` SET `PrevQuestId`='27773' WHERE `Id`=27914;

DELETE FROM `creature_involvedrelation` WHERE `quest` = '27768';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(46071, 27768);

UPDATE `quest_template` SET `PrevQuestId`='27821 27822' WHERE `Id` IN (27795, 27843, 27845);
UPDATE `quest_template` SET `PrevQuestId`='27795 27843 27845' WHERE `Id` IN (27849, 27851);
UPDATE `creature` SET `phaseMask`=2 WHERE `id` IN (46881, 46775, 46770);

DELETE FROM `spell_area` WHERE `spell` = '65141' AND `quest_start` IN (27795, 27843, 27845);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(65141, 5460, 27795, 27795, 1, 10),
(65141, 5460, 27843, 27843, 1, 10),
(65141, 5460, 27845, 27845, 1, 10);

DELETE FROM `spell_area` WHERE `spell` = '87292' AND `quest_start` IN (27795, 27843, 27845);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(87292, 5460, 27795, 27795, 1, 10),
(87292, 5460, 27843, 27843, 1, 10),
(87292, 5460, 27845, 27845, 1, 10);

SET @CGUID := 400400;
DELETE FROM `creature_addon` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+6;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 4, 0, 1, 2, 0, 0, -10335.9, -3410.86, 22.1486, 6.03639, 300, 0, 0, 30951, 0, 0, 0, 0, 0),
(@CGUID+1, 4, 0, 1, 2, 0, 0, -10335.9, -3441.11, 19.0684, 0.000602732, 300, 0, 0, 30951, 0, 0, 0, 0, 0),
(@CGUID+2, 4, 0, 1, 2, 0, 0, -10354.4, -3627.02, 22.3648, 5.98231, 300, 0, 0, 30951, 0, 0, 0, 0, 0),
(@CGUID+3, 4, 0, 1, 2, 0, 0, -10347, -3588.71, 21.3886, 5.7624, 300, 0, 0, 30951, 0, 0, 0, 0, 0),
(@CGUID+4, 4, 0, 1, 2, 0, 0, -10349.1, -3540.58, 20.4024, 5.89985, 300, 0, 0, 30951, 0, 0, 0, 0, 0),
(@CGUID+5, 4, 0, 1, 2, 0, 0, -10334, -3508.36, 22.5179, 5.20085, 300, 0, 0, 30951, 0, 0, 0, 0, 0),
(@CGUID+6, 4, 0, 1, 2, 0, 0, -10372.6, -3481.8, 19.0697, 6.04195, 300, 0, 0, 30951, 0, 0, 0, 0, 0);

-- Stonard Ogre
SET @ENTRY := 46765;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,46,185,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On AI Init - Move Forward"),
(@ENTRY,@SOURCETYPE,1,0,34,0,100,0,8,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Despawn"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On AI Init - Set Passive"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Passive"),
(@ENTRY,@SOURCETYPE,4,0,54,0,100,0,0,0,0,0,46,150,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move Forward"),
(@ENTRY,@SOURCETYPE,5,0,4,0,100,0,0,0,0,0,49,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Attack Invoker"),
(@ENTRY,@SOURCETYPE,6,0,0,0,100,0,15000,15000,15000,15000,11,4955,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Fist of Stone"),
(@ENTRY,@SOURCETYPE,7,0,4,0,100,0,0,0,0,0,11,4955,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Fist of Stone"),
(@ENTRY,@SOURCETYPE,8,0,54,0,100,0,0,0,0,0,41,120000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Force Despawn");

UPDATE `creature_template` SET `mindmg`=86, `maxdmg`=130, `attackpower`=32, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=46765;
DELETE FROM `creature` WHERE `id`=46765;
UPDATE `creature` SET `spawntimesecs`=60, `currentwaypoint`=1, `MovementType`=15 WHERE `id`=46770;

-- Stonard Warlock
SET @ENTRY := 46770;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,11939,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Summon Imp"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,3500,3500,3500,3500,11,9613,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadowbolt"),
(@ENTRY,@SOURCETYPE,2,0,0,0,50,0,5000,12500,5000,12500,11,9613,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Curse of Weakness"),
(@ENTRY,@SOURCETYPE,3,0,4,0,100,0,0,0,0,0,49,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Attack Victim"),
(@ENTRY,@SOURCETYPE,4,0,37,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Passive"),
(@ENTRY,@SOURCETYPE,5,0,11,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Respawn - Set Passive");

-- Marshtide Mage
SET @ENTRY := 46775;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,79865,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Frost Armor"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,3500,3500,3500,3500,11,79858,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Frostbolt"),
(@ENTRY,@SOURCETYPE,2,0,0,0,80,0,5500,5500,5500,5500,11,79858,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Blizzard");

DELETE FROM `spell_script_names` WHERE `spell_id` = '87293';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(87293, 'spell_marked_for_retrieval');

UPDATE `creature` SET `phaseMask`=2, `spawntimesecs`=60 WHERE `id` IN (46869, 46870);

DELETE FROM `spell_area` WHERE `spell` = '65141' AND `quest_start` IN (27849, 27851);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(65141, 75, 27849, 27849, 1, 10),
(65141, 75, 27851, 27851, 1, 10);

-- Marshtide Invader
SET @ENTRY := 46869;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,5000,5000,5000,5000,49,0,0,0,0,0,0,11,46870,5,0,0.0,0.0,0.0,0.0,"OOC - Attack Start Nearest Creature");

UPDATE `gameobject` SET `phaseMask`=2, `spawntimesecs`=60 WHERE `id`=206391;
UPDATE `gameobject_template` SET `data1`=206391 WHERE `entry`=206391;

DELETE FROM `gameobject_loot_template` WHERE `item` = '62516';
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(206391, 62516, -100, 1, 0, 1, 1);

-- The Harborage (DA CERCARE IL QUEST END!!)
DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '27918';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 657, 27918, 1, 74, 0);

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` = '27918';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49417, 657, 27918, 24913, 1, 74, 11);

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` = '24913';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49417, 657, 24913, 24913, 1, 8, 11);

UPDATE `creature_template` SET `mindmg`=88, `maxdmg`=132, `attackpower`=33 WHERE `entry` IN (46997, 48248, 46950, 46953, 45825, 45807);

-- Misty Grell
SET @ENTRY := 46950;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3500,3500,3500,3500,11,36227,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Firebolt");

-- Purespring Elemental
SET @ENTRY := 46953;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3500,3500,3500,3500,11,32011,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Water Bolt"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5500,5500,5500,5500,11,39207,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Water Spout");

-- Shifting Mireglob
SET @ENTRY := 46997;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3500,3500,3500,3500,11,21067,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Poison Bolt"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5500,5500,5500,5500,11,22595,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Poison Shock");

-- Sorrow Venomspitter
SET @ENTRY := 48248;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3500,3500,3500,3500,11,6917,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Venom Spit");

-- Swampstrider
SET @ENTRY := 45825;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,15000,15000,11,81678,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Eye Peck"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,66060,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Sprint");

-- Sawtooth Crocolisk
SET @ENTRY := 45807;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,87228,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Thick Hide"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,5000,8500,8500,11,48287,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Powerful Bite");

UPDATE `creature_template` SET `lootid`=46953 WHERE `entry`=46953;

DELETE FROM `creature_loot_template` WHERE `entry` = '46953';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(46953, 810, 0.0011, 1, 0, 1, 1),
(46953, 811, 0.0011, 1, 0, 1, 1),
(46953, 812, 0.0011, 1, 0, 1, 1),
(46953, 1203, 0.0034, 1, 0, 1, 1),
(46953, 1607, 0.0023, 1, 0, 1, 1),
(46953, 1721, 0.0045, 1, 0, 1, 1),
(46953, 2163, 0.0011, 1, 0, 1, 1),
(46953, 3075, 0.0056, 1, 0, 1, 1),
(46953, 3914, 0.2, 1, 0, 1, 1),
(46953, 3944, 0.1, 1, 0, 1, 1),
(46953, 3945, 0.1, 1, 0, 1, 1),
(46953, 3946, 0.1, 1, 0, 1, 1),
(46953, 3947, 0.1, 1, 0, 1, 1),
(46953, 3948, 0.05, 1, 0, 1, 1),
(46953, 3949, 0.05, 1, 0, 1, 1),
(46953, 3950, 0.05, 1, 0, 1, 1),
(46953, 3951, 0.1, 1, 0, 1, 1),
(46953, 3969, 0.05, 1, 0, 1, 1),
(46953, 3970, 0.05, 1, 0, 1, 1),
(46953, 3971, 0.1, 1, 0, 1, 1),
(46953, 3972, 0.1, 1, 0, 1, 1),
(46953, 3973, 0.05, 1, 0, 1, 1),
(46953, 3974, 0.1, 1, 0, 1, 1),
(46953, 3975, 0.05, 1, 0, 1, 1),
(46953, 3976, 0.1, 1, 0, 1, 1),
(46953, 3987, 0.1, 1, 0, 1, 1),
(46953, 3990, 0.1, 1, 0, 1, 1),
(46953, 3992, 0.05, 1, 0, 1, 1),
(46953, 3993, 0.1, 1, 0, 1, 1),
(46953, 3994, 0.115, 1, 0, 1, 1),
(46953, 3995, 0.05, 1, 0, 1, 1),
(46953, 3996, 0.05, 1, 0, 1, 1),
(46953, 3997, 0.05, 1, 0, 1, 1),
(46953, 3998, 0.05, 1, 0, 1, 1),
(46953, 3999, 0.05, 1, 0, 1, 1),
(46953, 4500, 0.2, 1, 0, 1, 1),
(46953, 5758, 0.1, 1, 0, 1, 1),
(46953, 6660, 0.0023, 1, 0, 1, 1),
(46953, 7070, 8.8087, 1, 0, 1, 1),
(46953, 7079, 6.4847, 1, 0, 1, 1),
(46953, 7080, 4.6175, 1, 0, 1, 1),
(46953, 7909, 0.1, 1, 0, 1, 1),
(46953, 7910, 0.05, 1, 0, 1, 1),
(46953, 8080, 0.0632, 1, 0, 1, 1),
(46953, 8081, 0.0455, 1, 0, 1, 1),
(46953, 8082, 0.0607, 1, 0, 1, 1),
(46953, 8083, 0.05, 1, 0, 1, 1),
(46953, 8084, 0.05, 1, 0, 1, 1),
(46953, 8085, 0.05, 1, 0, 1, 1),
(46953, 8086, 0.05, 1, 0, 1, 1),
(46953, 8245, 0.0023, 1, 0, 1, 1),
(46953, 8251, 0.009, 1, 0, 1, 1),
(46953, 8252, 0.0034, 1, 0, 1, 1),
(46953, 8254, 0.0023, 1, 0, 1, 1),
(46953, 8258, 0.0023, 1, 0, 1, 1),
(46953, 8261, 0.0147, 1, 0, 1, 1),
(46953, 8262, 0.0124, 1, 0, 1, 1),
(46953, 8263, 0.0079, 1, 0, 1, 1),
(46953, 8265, 0.0101, 1, 0, 1, 1),
(46953, 8267, 0.009, 1, 0, 1, 1),
(46953, 8268, 0.0135, 1, 0, 1, 1),
(46953, 8269, 0.0248, 1, 0, 1, 1),
(46953, 8270, 0.009, 1, 0, 1, 1),
(46953, 8271, 0.0068, 1, 0, 1, 1),
(46953, 8272, 0.0068, 1, 0, 1, 1),
(46953, 8275, 0.0079, 1, 0, 1, 1),
(46953, 8284, 0.0056, 1, 0, 1, 1),
(46953, 8285, 0.0045, 1, 0, 1, 1),
(46953, 8286, 0.0192, 1, 0, 1, 1),
(46953, 8287, 0.0056, 1, 0, 1, 1),
(46953, 8291, 0.0056, 1, 0, 1, 1),
(46953, 8293, 0.0034, 1, 0, 1, 1),
(46953, 8294, 0.0023, 1, 0, 1, 1),
(46953, 8295, 0.0034, 1, 0, 1, 1),
(46953, 8297, 0.009, 1, 0, 1, 1),
(46953, 8304, 0.0045, 1, 0, 1, 1),
(46953, 8311, 0.0203, 1, 0, 1, 1),
(46953, 8312, 0.0023, 1, 0, 1, 1),
(46953, 8316, 0.0045, 1, 0, 1, 1),
(46953, 8317, 0.0169, 1, 0, 1, 1),
(46953, 8318, 0.0158, 1, 0, 1, 1),
(46953, 8319, 0.0056, 1, 0, 1, 1),
(46953, 8320, 0.0034, 1, 0, 1, 1),
(46953, 8389, 0.05, 1, 0, 1, 1),
(46953, 8752, 0.1012, 1, 0, 1, 1),
(46953, 8753, 0.05, 1, 0, 1, 1),
(46953, 8754, 0.1, 1, 0, 1, 1),
(46953, 8755, 0.05, 1, 0, 1, 1),
(46953, 9262, 0.0011, 1, 0, 1, 1),
(46953, 9295, 0.0025, 1, 0, 1, 1),
(46953, 9944, 0.0034, 1, 0, 1, 1),
(46953, 9946, 0.0011, 1, 0, 1, 1),
(46953, 9950, 0.0045, 1, 0, 1, 1),
(46953, 9974, 0.0023, 1, 0, 1, 1),
(46953, 10057, 0.0011, 1, 0, 1, 1),
(46953, 10064, 0.0023, 1, 0, 1, 1),
(46953, 10065, 0.0023, 1, 0, 1, 1),
(46953, 10070, 0.0079, 1, 0, 1, 1),
(46953, 10074, 0.0045, 1, 0, 1, 1),
(46953, 10077, 0.0023, 1, 0, 1, 1),
(46953, 10078, 0.009, 1, 0, 1, 1),
(46953, 10093, 0.0011, 1, 0, 1, 1),
(46953, 10095, 0.0011, 1, 0, 1, 1),
(46953, 10096, 0.0135, 1, 0, 1, 1),
(46953, 10097, 0.0011, 1, 0, 1, 1),
(46953, 10098, 0.0056, 1, 0, 1, 1),
(46953, 10099, 0.0056, 1, 0, 1, 1),
(46953, 10100, 0.0045, 1, 0, 1, 1),
(46953, 10103, 0.0135, 1, 0, 1, 1),
(46953, 10106, 0.0056, 1, 0, 1, 1),
(46953, 10107, 0.0147, 1, 0, 1, 1),
(46953, 10108, 0.0068, 1, 0, 1, 1),
(46953, 10109, 0.0135, 1, 0, 1, 1),
(46953, 10110, 0.0068, 1, 0, 1, 1),
(46953, 10111, 0.0034, 1, 0, 1, 1),
(46953, 10112, 0.0023, 1, 0, 1, 1),
(46953, 10113, 0.0045, 1, 0, 1, 1),
(46953, 10119, 0.0023, 1, 0, 1, 1),
(46953, 10120, 0.0113, 1, 0, 1, 1),
(46953, 10121, 0.0011, 1, 0, 1, 1),
(46953, 10122, 0.0079, 1, 0, 1, 1),
(46953, 10123, 0.0023, 1, 0, 1, 1),
(46953, 10124, 0.0045, 1, 0, 1, 1),
(46953, 10126, 0.009, 1, 0, 1, 1),
(46953, 10128, 0.0079, 1, 0, 1, 1),
(46953, 10165, 0.009, 1, 0, 1, 1),
(46953, 10166, 0.0135, 1, 0, 1, 1),
(46953, 10167, 0.0045, 1, 0, 1, 1),
(46953, 10170, 0.0034, 1, 0, 1, 1),
(46953, 10171, 0.0113, 1, 0, 1, 1),
(46953, 10172, 0.0271, 1, 0, 1, 1),
(46953, 10173, 0.0045, 1, 0, 1, 1),
(46953, 10175, 0.0203, 1, 0, 1, 1),
(46953, 10176, 0.0135, 1, 0, 1, 1),
(46953, 10177, 0.0135, 1, 0, 1, 1),
(46953, 10179, 0.0101, 1, 0, 1, 1),
(46953, 10181, 0.0011, 1, 0, 1, 1),
(46953, 10182, 0.0011, 1, 0, 1, 1),
(46953, 10183, 0.0079, 1, 0, 1, 1),
(46953, 10186, 0.0045, 1, 0, 1, 1),
(46953, 10187, 0.0079, 1, 0, 1, 1),
(46953, 10188, 0.0056, 1, 0, 1, 1),
(46953, 10189, 0.0101, 1, 0, 1, 1),
(46953, 10192, 0.0101, 1, 0, 1, 1),
(46953, 10193, 0.0045, 1, 0, 1, 1),
(46953, 10195, 0.0011, 1, 0, 1, 1),
(46953, 10198, 0.0011, 1, 0, 1, 1),
(46953, 10199, 0.0068, 1, 0, 1, 1),
(46953, 10200, 0.0011, 1, 0, 1, 1),
(46953, 10204, 0.0079, 1, 0, 1, 1),
(46953, 10212, 0.0045, 1, 0, 1, 1),
(46953, 10216, 0.0023, 1, 0, 1, 1),
(46953, 10224, 0.0034, 1, 0, 1, 1),
(46953, 10229, 0.0068, 1, 0, 1, 1),
(46953, 10231, 0.0034, 1, 0, 1, 1),
(46953, 10232, 0.0011, 1, 0, 1, 1),
(46953, 10233, 0.0011, 1, 0, 1, 1),
(46953, 10234, 0.0011, 1, 0, 1, 1),
(46953, 10240, 0.0113, 1, 0, 1, 1),
(46953, 10244, 0.0034, 1, 0, 1, 1),
(46953, 10245, 0.0056, 1, 0, 1, 1),
(46953, 10276, 0.0068, 1, 0, 1, 1),
(46953, 10278, 0.0079, 1, 0, 1, 1),
(46953, 10281, 0.0011, 1, 0, 1, 1),
(46953, 10282, 0.0023, 1, 0, 1, 1),
(46953, 10370, 0.0023, 1, 0, 1, 1),
(46953, 11302, 0.0011, 1, 0, 1, 1),
(46953, 11977, 0.0045, 1, 0, 1, 1),
(46953, 11978, 0.0011, 1, 0, 1, 1),
(46953, 11990, 0.0068, 1, 0, 1, 1),
(46953, 12002, 0.0056, 1, 0, 1, 1),
(46953, 12004, 0.0011, 1, 0, 1, 1),
(46953, 12014, 0.0056, 1, 0, 1, 1),
(46953, 12025, 0.009, 1, 0, 1, 1),
(46953, 12035, 0.0023, 1, 0, 1, 1),
(46953, 12045, 0.0045, 1, 0, 1, 1),
(46953, 12056, 0.0011, 1, 0, 1, 1),
(46953, 12682, 0.009, 1, 0, 1, 1),
(46953, 12683, 0.05, 1, 0, 1, 1),
(46953, 12684, 0.05, 1, 0, 1, 1),
(46953, 12689, 0.0051, 1, 0, 1, 1),
(46953, 12691, 0.0126, 1, 0, 1, 1),
(46953, 12692, 0.0011, 1, 0, 1, 1),
(46953, 13013, 0.0011, 1, 0, 1, 1),
(46953, 13022, 0.0011, 1, 0, 1, 1),
(46953, 13040, 0.0011, 1, 0, 1, 1),
(46953, 13059, 0.0011, 1, 0, 1, 1),
(46953, 13067, 0.0023, 1, 0, 1, 1),
(46953, 13073, 0.0011, 1, 0, 1, 1),
(46953, 13091, 0.0011, 1, 0, 1, 1),
(46953, 13111, 0.0011, 1, 0, 1, 1),
(46953, 13120, 0.0011, 1, 0, 1, 1),
(46953, 13122, 0.0034, 1, 0, 1, 1),
(46953, 13126, 0.0023, 1, 0, 1, 1),
(46953, 13144, 0.0011, 1, 0, 1, 1),
(46953, 13146, 0.0011, 1, 0, 1, 1),
(46953, 13816, 0.1, 1, 0, 1, 1),
(46953, 13818, 0.1, 1, 0, 1, 1),
(46953, 13819, 0.1, 1, 0, 1, 1),
(46953, 13820, 0.1, 1, 0, 1, 1),
(46953, 13821, 0.1, 1, 0, 1, 1),
(46953, 13822, 0.1, 1, 0, 1, 1),
(46953, 13823, 0.1, 1, 0, 1, 1),
(46953, 13824, 0.2, 1, 0, 1, 1),
(46953, 13825, 0.1, 1, 0, 1, 1),
(46953, 14467, 0.0051, 1, 0, 1, 1),
(46953, 14494, 0.0025, 1, 0, 1, 1),
(46953, 15217, 0.0395, 1, 0, 1, 1),
(46953, 15218, 0.0068, 1, 0, 1, 1),
(46953, 15228, 0.0506, 1, 0, 1, 1),
(46953, 15229, 0.0192, 1, 0, 1, 1),
(46953, 15237, 0.0135, 1, 0, 1, 1),
(46953, 15238, 0.0023, 1, 0, 1, 1),
(46953, 15254, 0.0226, 1, 0, 1, 1),
(46953, 15255, 0.0101, 1, 0, 1, 1),
(46953, 15264, 0.0147, 1, 0, 1, 1),
(46953, 15271, 0.0101, 1, 0, 1, 1),
(46953, 15275, 0.0192, 1, 0, 1, 1),
(46953, 15280, 0.05, 1, 0, 1, 1),
(46953, 15281, 0.0056, 1, 0, 1, 1),
(46953, 15294, 0.05, 1, 0, 1, 1),
(46953, 15295, 0.0158, 1, 0, 1, 1),
(46953, 15324, 0.0068, 1, 0, 1, 1),
(46953, 15755, 0.0253, 1, 0, 1, 1),
(46953, 15930, 0.0079, 1, 0, 1, 1),
(46953, 15936, 0.009, 1, 0, 1, 1),
(46953, 16044, 0.0023, 1, 0, 1, 1),
(46953, 21947, 0.05, 1, 0, 1, 1),
(46953, 24222, 0.0011, 1, 0, 1, 1),
(46953, 55984, 55.7761, 1, 0, 1, 1),
(46953, 55985, 24.2228, 1, 0, 1, 1),
(46953, 62609, -81.9733, 1, 0, 1, 1);

UPDATE `creature_template_addon` SET `auras`='49415 99480', `bytes1`=0 WHERE `entry`=1776;

DELETE FROM `creature_text` WHERE `entry`=17127;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(17127,0,0,'Even now, nothing. Why? Why would the Light forsake the innocent?',12,0,100,0,0,0,'Comment');
(17127,1,0,'Prophet Velen!',12,0,100,0,0,0,'Comment');
(17127,2,0,'...thank you, Prophet. You have given both of us great comfort. I will continue my work, in faith and memory of Magtoor.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=46986;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(46986,0,0,'Some have spent decades meditating upon this mystery, Avuun. I do not wish the same fate upon you.',12,0,100,0,0,0,'Comment'),
(46986,1,0,'The Light wishes suffering on none, my child. But it does not reign unopposed in our realm.',12,0,100,0,0,0,'Comment'),
(46986,2,0,'Even now, the true battle between the forces of Light and Darkness approaches. We will all be called to join, and in the face of this conflict, all mortal suffering will be meaningless.',12,0,100,0,0,0,'Comment'),
(46986,3,0,'Magtoor, you have embraced your plight bravely. Are you ready to return to the embrace of the Light?',12,0,100,0,0,0,'Comment'),
(46986,4,0,'Then may the Light save you and raise you up.',12,0,100,0,0,0,'Comment'),
(46986,5,0,'Remember, Avuun. Not all who wander are lost.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=1776;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(1776,0,0,'Yes...',12,0,100,0,0,0,'Comment');

-- Anchorite Avuun
SET @ENTRY := 17127;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,24913,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,24913,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Set NPC Flag to 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,17127,0,0,50,207995,65,0,0,0,0,8,0,0,0,-10105.8,-2754.35,25.33,6.05,"After Talk 0 - Summon Portal to Exodar"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,1,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,17127,0,0,45,0,1,0,0,0,0,11,46986,50,0,0.0,0.0,0.0,0.0,"Aftert Talk 1 - Set Data 1 to Velen"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,2,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 2"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,2,17127,0,0,81,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Aftert Talk 2 - Set NPC Flag 3 "),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,0,17127,0,0,11,87536,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Summon Velen"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,1,17127,0,0,66,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Aftert Talk 1 - Set Orientation"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,1,17127,0,0,5,68,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Aftert Talk 1 - Emote Beg");

-- Prophet Velen
SET @ENTRY := 46986;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,60,1,100,1,2000,2000,2000,2000,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (2 secs) - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,60,1,100,1,2000,2000,2000,2000,46,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (2 secs) - Move Forward"),
(@ENTRY,@SOURCETYPE,3,0,52,1,100,1,0,46986,0,0,45,0,1,0,0,0,0,10,150955,17127,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Avuun"),
(@ENTRY,@SOURCETYPE,4,0,38,1,100,1,0,1,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1"),
(@ENTRY,@SOURCETYPE,5,0,52,1,100,1,1,46986,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,6,0,52,1,100,1,2,46986,0,0,1,3,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,7,0,52,1,100,1,3,46986,0,0,45,0,1,0,0,0,0,10,150956,1776,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 1 to Magtoor"),
(@ENTRY,@SOURCETYPE,8,0,38,1,100,1,0,2,0,0,1,4,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 4"),
(@ENTRY,@SOURCETYPE,9,0,52,1,100,1,4,46986,0,0,1,5,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Talk 5"),
(@ENTRY,@SOURCETYPE,10,0,52,1,100,1,5,46986,0,0,45,0,2,0,0,0,0,10,150955,17127,0,0.0,0.0,0.0,0.0,"After Talk 5 - Set Data 2 to Avuun"),
(@ENTRY,@SOURCETYPE,11,0,38,1,100,1,0,3,0,0,1,6,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 6"),
(@ENTRY,@SOURCETYPE,12,0,52,1,100,1,5,46986,0,0,69,0,0,0,0,0,0,8,0,0,0,-10104.3,-2754.67,25.33,2.86,"After Talk 5 - Move To Portal"),
(@ENTRY,@SOURCETYPE,13,0,52,1,100,1,5,46986,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 5 - Set Phase 2"),
(@ENTRY,@SOURCETYPE,14,0,60,2,100,1,2000,2000,2000,2000,11,52096,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (2 Secs) - Cast Teleport Effect"),
(@ENTRY,@SOURCETYPE,15,0,60,2,100,1,2000,2000,2000,2000,41,1500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (2 Secs) - Force Despawn"),
(@ENTRY,@SOURCETYPE,16,0,38,1,100,1,0,2,0,0,11,87524,0,0,0,0,0,11,1776,80,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Cast Extreme Unction"),
(@ENTRY,@SOURCETYPE,17,0,52,1,100,1,4,46986,0,0,33,47541,0,0,0,0,0,18,100,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Quest Complete");

-- Magtoor
SET @ENTRY := 1776;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,1776,0,0,45,0,2,0,0,0,0,11,46986,50,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 2 to Velen");

UPDATE `gameobject_template` SET `flags`=4 WHERE `entry`=207995;

DELETE FROM `creature_loot_template` WHERE `entry` = '45807';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(45807, 810, 0.002, 1, 0, 1, 1),
(45807, 942, 0.001, 1, 0, 1, 1),
(45807, 1315, 0.001, 1, 0, 1, 1),
(45807, 1607, 0.002, 1, 0, 1, 1),
(45807, 2564, 0.001, 1, 0, 1, 1),
(45807, 2915, 0.003, 1, 0, 1, 1),
(45807, 3667, 47.5223, 1, 0, 1, 1),
(45807, 3914, 0.2, 1, 0, 1, 1),
(45807, 3944, 0.1, 1, 0, 1, 1),
(45807, 3945, 0.1, 1, 0, 1, 1),
(45807, 3946, 0.1, 1, 0, 1, 1),
(45807, 3947, 0.1, 1, 0, 1, 1),
(45807, 3948, 0.05, 1, 0, 1, 1),
(45807, 3949, 0.05, 1, 0, 1, 1),
(45807, 3950, 0.05, 1, 0, 1, 1),
(45807, 3951, 0.1, 1, 0, 1, 1),
(45807, 3969, 0.05, 1, 0, 1, 1),
(45807, 3970, 0.1, 1, 0, 1, 1),
(45807, 3971, 0.1, 1, 0, 1, 1),
(45807, 3972, 0.05, 1, 0, 1, 1),
(45807, 3973, 0.05, 1, 0, 1, 1),
(45807, 3974, 0.1, 1, 0, 1, 1),
(45807, 3975, 0.05, 1, 0, 1, 1),
(45807, 3976, 0.1, 1, 0, 1, 1),
(45807, 3987, 0.05, 1, 0, 1, 1),
(45807, 3990, 0.05, 1, 0, 1, 1),
(45807, 3992, 0.05, 1, 0, 1, 1),
(45807, 3993, 0.05, 1, 0, 1, 1),
(45807, 3994, 0.1, 1, 0, 1, 1),
(45807, 3995, 0.05, 1, 0, 1, 1),
(45807, 3996, 0.05, 1, 0, 1, 1),
(45807, 3997, 0.05, 1, 0, 1, 1),
(45807, 3998, 0.05, 1, 0, 1, 1),
(45807, 3999, 0.05, 1, 0, 1, 1),
(45807, 4500, 0.2, 1, 0, 1, 1),
(45807, 5758, 0.1, 1, 0, 1, 1),
(45807, 7537, 0.002, 1, 0, 1, 1),
(45807, 7557, 0.001, 1, 0, 1, 1),
(45807, 7909, 0.05, 1, 0, 1, 1),
(45807, 7910, 0.05, 1, 0, 1, 1),
(45807, 7990, 0.05, 1, 0, 1, 1),
(45807, 7993, 0.05, 1, 0, 1, 1),
(45807, 8080, 0.0587, 1, 0, 1, 1),
(45807, 8081, 0.05, 1, 0, 1, 1),
(45807, 8082, 0.05, 1, 0, 1, 1),
(45807, 8083, 0.05, 1, 0, 1, 1),
(45807, 8084, 0.05, 1, 0, 1, 1),
(45807, 8085, 0.05, 1, 0, 1, 1),
(45807, 8106, 0.004, 1, 0, 1, 1),
(45807, 8113, 0.004, 1, 0, 1, 1),
(45807, 8119, 0.0279, 1, 0, 1, 1),
(45807, 8126, 0.012, 1, 0, 1, 1),
(45807, 8132, 0.007, 1, 0, 1, 1),
(45807, 8134, 0.003, 1, 0, 1, 1),
(45807, 8169, 3.1919, 1, 0, 1, 1),
(45807, 8246, 0.012, 1, 0, 1, 1),
(45807, 8247, 0.006, 1, 0, 1, 1),
(45807, 8249, 0.0528, 1, 0, 1, 1),
(45807, 8250, 0.0339, 1, 0, 1, 1),
(45807, 8251, 0.005, 1, 0, 1, 1),
(45807, 8253, 0.005, 1, 0, 1, 1),
(45807, 8254, 0.002, 1, 0, 1, 1),
(45807, 8256, 0.0159, 1, 0, 1, 1),
(45807, 8260, 0.0259, 1, 0, 1, 1),
(45807, 8261, 0.004, 1, 0, 1, 1),
(45807, 8262, 0.004, 1, 0, 1, 1),
(45807, 8263, 0.009, 1, 0, 1, 1),
(45807, 8264, 0.011, 1, 0, 1, 1),
(45807, 8266, 0.005, 1, 0, 1, 1),
(45807, 8267, 0.009, 1, 0, 1, 1),
(45807, 8268, 0.001, 1, 0, 1, 1),
(45807, 8269, 0.007, 1, 0, 1, 1),
(45807, 8270, 0.001, 1, 0, 1, 1),
(45807, 8272, 0.003, 1, 0, 1, 1),
(45807, 8274, 0.005, 1, 0, 1, 1),
(45807, 8275, 0.001, 1, 0, 1, 1),
(45807, 8286, 0.003, 1, 0, 1, 1),
(45807, 8297, 0.002, 1, 0, 1, 1),
(45807, 8311, 0.001, 1, 0, 1, 1),
(45807, 8314, 0.008, 1, 0, 1, 1),
(45807, 8315, 0.0139, 1, 0, 1, 1),
(45807, 8316, 0.003, 1, 0, 1, 1),
(45807, 8319, 0.005, 1, 0, 1, 1),
(45807, 8320, 0.001, 1, 0, 1, 1),
(45807, 8752, 0.05, 1, 0, 1, 1),
(45807, 8753, 0.05, 1, 0, 1, 1),
(45807, 8754, 0.05, 1, 0, 1, 1),
(45807, 8755, 0.05, 1, 0, 1, 1),
(45807, 9298, 0.0049, 1, 0, 1, 1),
(45807, 9946, 0.003, 1, 0, 1, 1),
(45807, 9950, 0.006, 1, 0, 1, 1),
(45807, 9954, 0.011, 1, 0, 1, 1),
(45807, 9958, 0.002, 1, 0, 1, 1),
(45807, 9974, 0.01, 1, 0, 1, 1),
(45807, 10061, 0.009, 1, 0, 1, 1),
(45807, 10062, 0.002, 1, 0, 1, 1),
(45807, 10063, 0.004, 1, 0, 1, 1),
(45807, 10064, 0.012, 1, 0, 1, 1),
(45807, 10065, 0.001, 1, 0, 1, 1),
(45807, 10068, 0.005, 1, 0, 1, 1),
(45807, 10070, 0.001, 1, 0, 1, 1),
(45807, 10072, 0.006, 1, 0, 1, 1),
(45807, 10073, 0.011, 1, 0, 1, 1),
(45807, 10074, 0.004, 1, 0, 1, 1),
(45807, 10075, 0.009, 1, 0, 1, 1),
(45807, 10077, 0.006, 1, 0, 1, 1),
(45807, 10078, 0.004, 1, 0, 1, 1),
(45807, 10082, 0.0139, 1, 0, 1, 1),
(45807, 10083, 0.007, 1, 0, 1, 1),
(45807, 10084, 0.0169, 1, 0, 1, 1),
(45807, 10085, 0.0179, 1, 0, 1, 1),
(45807, 10093, 0.003, 1, 0, 1, 1),
(45807, 10096, 0.003, 1, 0, 1, 1),
(45807, 10098, 0.01, 1, 0, 1, 1),
(45807, 10099, 0.009, 1, 0, 1, 1),
(45807, 10103, 0.005, 1, 0, 1, 1),
(45807, 10107, 0.01, 1, 0, 1, 1),
(45807, 10108, 0.007, 1, 0, 1, 1),
(45807, 10109, 0.0159, 1, 0, 1, 1),
(45807, 10110, 0.001, 1, 0, 1, 1),
(45807, 10120, 0.006, 1, 0, 1, 1),
(45807, 10126, 0.004, 1, 0, 1, 1),
(45807, 10128, 0.003, 1, 0, 1, 1),
(45807, 10132, 0.002, 1, 0, 1, 1),
(45807, 10133, 0.0129, 1, 0, 1, 1),
(45807, 10134, 0.006, 1, 0, 1, 1),
(45807, 10165, 0.001, 1, 0, 1, 1),
(45807, 10166, 0.002, 1, 0, 1, 1),
(45807, 10171, 0.003, 1, 0, 1, 1),
(45807, 10173, 0.011, 1, 0, 1, 1),
(45807, 10174, 0.0159, 1, 0, 1, 1),
(45807, 10175, 0.002, 1, 0, 1, 1),
(45807, 10176, 0.007, 1, 0, 1, 1),
(45807, 10179, 0.004, 1, 0, 1, 1),
(45807, 10180, 0.0179, 1, 0, 1, 1),
(45807, 10183, 0.002, 1, 0, 1, 1),
(45807, 10184, 0.009, 1, 0, 1, 1),
(45807, 10185, 0.006, 1, 0, 1, 1),
(45807, 10186, 0.007, 1, 0, 1, 1),
(45807, 10187, 0.002, 1, 0, 1, 1),
(45807, 10189, 0.005, 1, 0, 1, 1),
(45807, 10190, 0.0159, 1, 0, 1, 1),
(45807, 10191, 0.006, 1, 0, 1, 1),
(45807, 10192, 0.006, 1, 0, 1, 1),
(45807, 10193, 0.003, 1, 0, 1, 1),
(45807, 10196, 0.0159, 1, 0, 1, 1),
(45807, 10197, 0.011, 1, 0, 1, 1),
(45807, 10198, 0.009, 1, 0, 1, 1),
(45807, 10199, 0.005, 1, 0, 1, 1),
(45807, 10200, 0.004, 1, 0, 1, 1),
(45807, 10203, 0.0129, 1, 0, 1, 1),
(45807, 10231, 0.003, 1, 0, 1, 1),
(45807, 10238, 0.0159, 1, 0, 1, 1),
(45807, 10239, 0.002, 1, 0, 1, 1),
(45807, 10240, 0.003, 1, 0, 1, 1),
(45807, 10241, 0.007, 1, 0, 1, 1),
(45807, 10242, 0.0169, 1, 0, 1, 1),
(45807, 10243, 0.008, 1, 0, 1, 1),
(45807, 10244, 0.011, 1, 0, 1, 1),
(45807, 10245, 0.005, 1, 0, 1, 1),
(45807, 10278, 0.001, 1, 0, 1, 1),
(45807, 10320, 0.05, 1, 0, 1, 1),
(45807, 11208, 0.0733, 1, 0, 1, 1),
(45807, 11302, 0.002, 1, 0, 1, 1),
(45807, 11976, 0.004, 1, 0, 1, 1),
(45807, 11977, 0.001, 1, 0, 1, 1),
(45807, 11989, 0.008, 1, 0, 1, 1),
(45807, 11990, 0.003, 1, 0, 1, 1),
(45807, 12002, 0.004, 1, 0, 1, 1),
(45807, 12014, 0.007, 1, 0, 1, 1),
(45807, 12025, 0.002, 1, 0, 1, 1),
(45807, 12034, 0.003, 1, 0, 1, 1),
(45807, 12037, 33.4263, 1, 0, 1, 1),
(45807, 12044, 0.011, 1, 0, 1, 1),
(45807, 12055, 0.0149, 1, 0, 1, 1),
(45807, 12682, 0.0098, 1, 0, 1, 1),
(45807, 12684, 0.011, 1, 0, 1, 1),
(45807, 12685, 0.005, 1, 0, 1, 1),
(45807, 12689, 0.05, 1, 0, 1, 1),
(45807, 12691, 0.05, 1, 0, 1, 1),
(45807, 12693, 0.0244, 1, 0, 1, 1),
(45807, 12704, 0.007, 1, 0, 1, 1),
(45807, 13008, 0.004, 1, 0, 1, 1),
(45807, 13009, 0.001, 1, 0, 1, 1),
(45807, 13014, 0.003, 1, 0, 1, 1),
(45807, 13022, 0.001, 1, 0, 1, 1),
(45807, 13027, 0.003, 1, 0, 1, 1),
(45807, 13030, 0.002, 1, 0, 1, 1),
(45807, 13046, 0.002, 1, 0, 1, 1),
(45807, 13052, 0.003, 1, 0, 1, 1),
(45807, 13059, 0.009, 1, 0, 1, 1),
(45807, 13073, 0.003, 1, 0, 1, 1),
(45807, 13085, 0.002, 1, 0, 1, 1),
(45807, 13122, 0.001, 1, 0, 1, 1),
(45807, 13125, 0.003, 1, 0, 1, 1),
(45807, 13816, 0.1, 1, 0, 1, 1),
(45807, 13818, 0.1, 1, 0, 1, 1),
(45807, 13819, 0.1, 1, 0, 1, 1),
(45807, 13820, 0.1, 1, 0, 1, 1),
(45807, 13821, 0.1, 1, 0, 1, 1),
(45807, 13822, 0.1, 1, 0, 1, 1),
(45807, 13823, 0.1, 1, 0, 1, 1),
(45807, 13824, 0.1, 1, 0, 1, 1),
(45807, 13825, 0.1, 1, 0, 1, 1),
(45807, 14467, 0.01, 1, 0, 1, 1),
(45807, 14499, 0.008, 1, 0, 1, 1),
(45807, 15216, 0.011, 1, 0, 1, 1),
(45807, 15217, 0.0049, 1, 0, 1, 1),
(45807, 15228, 0.007, 1, 0, 1, 1),
(45807, 15229, 0.0073, 1, 0, 1, 1),
(45807, 15236, 0.0309, 1, 0, 1, 1),
(45807, 15237, 0.1711, 1, 0, 1, 1),
(45807, 15253, 0.0209, 1, 0, 1, 1),
(45807, 15274, 0.0229, 1, 0, 1, 1),
(45807, 15279, 0.0189, 1, 0, 1, 1),
(45807, 15280, 0.0169, 1, 0, 1, 1),
(45807, 15291, 0.0159, 1, 0, 1, 1),
(45807, 15294, 0.0049, 1, 0, 1, 1),
(45807, 15936, 0.002, 1, 0, 1, 1),
(45807, 15937, 0.001, 1, 0, 1, 1),
(45807, 16215, 0.0049, 1, 0, 1, 1),
(45807, 16218, 0.008, 1, 0, 1, 1),
(45807, 16220, 0.0098, 1, 0, 1, 1),
(45807, 17007, 0.003, 1, 0, 1, 1),
(45807, 21949, 0.0489, 1, 0, 1, 1),
(45807, 30466, 22.8184, 1, 0, 1, 1),
(45807, 62526, 77.1288, 1, 0, 1, 1);

UPDATE `creature_template` SET `lootid`=45807 WHERE `entry`=45807;
UPDATE `quest_template` SET `PrevQuestId`='27852 27853' WHERE `Id` IN (27854, 27855, 27856);