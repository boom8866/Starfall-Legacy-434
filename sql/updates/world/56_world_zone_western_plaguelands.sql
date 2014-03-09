UPDATE `creature` SET `phaseMask`=1 WHERE `id` IN (1847, 1784, 1783);

-- Foulmane
SET @ENTRY := 1847;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,3427,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Infected Wound"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,1000,1000,11,13445,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Rend"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,2500,2500,3500,3500,11,3391,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Thrash");

-- Skeletal Sorcerer
SET @ENTRY := 1784;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,85434,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Tombkeeper's Curse"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,4000,4000,11,9672,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Frostbolt");

-- Skeletal Flayer
SET @ENTRY := 1783;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,10000,10000,11,85521,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Vile Aegis");

DELETE FROM `creature_loot_template` WHERE `item` = '60863';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(1784, 60863, -40.6846, 1, 0, 1, 1),
(1783, 60863, -37.0062, 1, 0, 1, 1);

DELETE FROM `creature_loot_template` WHERE `item` = '60864';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(1784, 60864, -40.1181, 1, 0, 1, 1),
(1783, 60864, -37.6716, 1, 0, 1, 1);

UPDATE `creature` SET `phaseMask`=1, `spawndist`=0, `MovementType`=0 WHERE `id`=44329;
UPDATE `creature_template_addon` SET `auras`='49415' WHERE `entry`=44329;

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` IN (27161, 26922);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(49417, 193, 27161, 27161, 1, 8),
(49417, 193, 26922, 26922, 1, 8);

SET @CGUID := 400620;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+14;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 44329, 0, 1, 1, 0, 1, 1482.16, -1410.71, 67.0436, 2.48873, 120, 0, 0, 303, 1067, 0, 0, 34816, 0),
(@CGUID+1, 44329, 0, 1, 1, 0, 1, 1477.55, -1416.74, 67.0422, 2.48873, 120, 0, 0, 303, 1067, 0, 0, 34816, 0),
(@CGUID+2, 44329, 0, 1, 1, 0, 1, 1477.08, -1397.58, 67.0391, 2.54971, 120, 0, 0, 290, 1007, 0, 0, 34816, 0),
(@CGUID+3, 44329, 0, 1, 1, 0, 1, 1486.65, -1398.51, 66.9851, 2.97496, 120, 0, 0, 290, 1007, 0, 0, 34816, 0),
(@CGUID+4, 44329, 0, 1, 1, 0, 1, 1501.12, -1409.64, 66.9563, 1.71608, 120, 0, 0, 303, 1067, 0, 0, 34816, 0),
(@CGUID+5, 44329, 0, 1, 1, 0, 1, 1501.87, -1422.37, 67.0297, 1.32458, 120, 0, 0, 303, 1067, 0, 0, 34816, 0),
(@CGUID+6, 44329, 0, 1, 1, 0, 1, 1485.67, -1436.32, 67.0382, 0.258083, 120, 0, 0, 290, 1007, 0, 0, 34816, 0),
(@CGUID+7, 44329, 0, 1, 1, 0, 1, 1475.68, -1434.4, 67.0385, 5.84939, 120, 0, 0, 290, 1007, 0, 0, 34816, 0),
(@CGUID+8, 44329, 0, 1, 1, 0, 1, 1466.93, -1427.8, 67.0385, 5.45452, 120, 0, 0, 303, 1067, 0, 0, 34816, 0),
(@CGUID+9, 44329, 0, 1, 1, 0, 1, 1464.55, -1418.48, 67.0226, 4.48814, 120, 0, 0, 303, 1067, 0, 0, 34816, 0),
(@CGUID+10, 44329, 0, 1, 1, 0, 1, 1464.16, -1408.21, 67.0385, 5.16314, 120, 0, 0, 303, 1067, 0, 0, 34816, 0),
(@CGUID+11, 44329, 0, 1, 1, 0, 1, 1457.36, -1395.58, 64.4057, 2.38787, 120, 0, 0, 303, 1067, 0, 0, 34816, 0),
(@CGUID+12, 44329, 0, 1, 1, 0, 1, 1461.38, -1391.29, 64.5525, 2.38787, 120, 0, 0, 290, 1007, 0, 0, 34816, 0),
(@CGUID+13, 44329, 0, 1, 1, 0, 1, 1455.81, -1403.12, 65.7798, 2.38787, 120, 0, 0, 303, 1067, 0, 0, 34816, 0),
(@CGUID+14, 44329, 0, 1, 1, 0, 1, 1465.07, -1393.26, 65.6439, 2.38787, 120, 0, 0, 303, 1067, 0, 0, 34816, 0);

-- Scourge Bone Animus
SET @ENTRY := 204966;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,12,44329,4,120000,0,0,0,8,0,0,0,1476.04,-1411.0,67.04,2.4,"On Get Data 1 - Summon Stickbone Berserker"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,12,44329,4,120000,0,0,0,8,0,0,0,1556.99,-1476.89,68.39,4.43,"On Get Data 1 - Summon Stickbone Berserker");

-- Stickbone Berserker
SET @ENTRY := 44329;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,45,0,1,0,0,0,0,14,82595,204966,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Animus"),
(@ENTRY,@SOURCETYPE,1,0,37,0,100,0,0,0,0,0,89,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Random Move"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Passive"),
(@ENTRY,@SOURCETYPE,3,0,6,0,100,0,0,0,0,0,45,0,1,0,0,0,0,14,82618,204966,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Animus");

UPDATE `creature_template` SET `mindmg`=61, `maxdmg`=71, `attackpower`=11, `dmg_multiplier`=1 WHERE `entry` IN (1852, 44318, 44323, 44473, 44447, 44316, 44315, 44562, 44328);

-- Araj the Summoner
SET @ENTRY := 1852;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,11,18661,4,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Cast Phylactery"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,4000,4000,11,9672,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Frostbolt"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,3000,3000,5500,5500,11,75062,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Frost Nova"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,15000,15000,15000,15000,11,83701,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Summon Berserkers"),
(@ENTRY,@SOURCETYPE,4,0,1,0,100,0,3000,3000,3000,3000,49,0,0,0,0,0,0,18,10,0,0,0.0,0.0,0.0,0.0,"OOC - Attack Players");

-- Rattlegore
SET @ENTRY := 44318;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,4000,4000,11,86079,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Ground Slash"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,2000,6000,6000,11,86085,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Mutilate");

-- Darkmaster Gandling
SET @ENTRY := 44323;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,3,2,0,100,1,1,50,0,0,11,86780,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Health 50% - Cast Shadow Prison"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,4000,4000,11,79932,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadow Bolt"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,2500,2500,6500,6500,11,86845,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadow Eruption"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,12,46558,4,15000,0,0,0,8,0,0,0,1284.73,-1529.88,65.88,0.11,"Link - Summon Shadow Prison");

-- Shaggy Black Bear
SET @ENTRY := 44473;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,50256,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Demoralizing Roar"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,4000,4000,11,85415,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Mangle"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,11,85842,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Survival Instincts");

-- Andorhal Deathguard
SET @ENTRY := 44447;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,85524,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Might of the Forsaken"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,15000,15000,15000,15000,11,85524,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Might of the Forsaken");

-- Desiccated Magus
SET @ENTRY := 44315;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,4000,4000,11,11538,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Frostbolt"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5500,5500,5500,5500,11,79847,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Blast Wave");

-- Opengut Behemoth
SET @ENTRY := 44562;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,4000,4000,11,40504,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Cleave"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2500,2500,6500,6500,11,50335,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Scourge Hook");

-- Andorhal Defender
SET @ENTRY := 44328;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,85525,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Lordaeron's Call"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,15000,15000,15000,15000,11,85525,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Lordaeron's Call");

UPDATE `creature_template` SET `faction_A`=1979, `faction_H`=1979, `type_flags`=4096, `flags_extra`=32768, `Health_mod`=3, `Armor_mod`=3 WHERE `entry`=44326;
UPDATE `creature_template` SET `faction_A`=1891, `faction_H`=1891, `type_flags`=4096, `flags_extra`=32768, `Health_mod`=3, `Armor_mod`=3 WHERE `entry`=44328;
UPDATE `creature` SET `spawntimesecs`=60, `spawndist`=15 WHERE `id` IN (44326, 44327);
DELETE FROM `creature` WHERE `guid`=209643;

DELETE FROM `creature_text` WHERE `entry`=45166;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45166,0,0,'Free at last!',12,0,100,0,0,0,'Comment'),
(45166,0,1,'Thank you hero!',0,0,100,0,0,0,'Comment'),
(45166,0,2,'Where is my home?',12,0,100,0,0,0,'Comment'),
(45166,0,3,'I can see the light...',12,0,100,0,0,0,'Comment');

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '27165';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 3197, 27165, 27171, 1, 66, 3);

UPDATE `creature_template` SET `mindmg`=47, `maxdmg`=69, `attackpower`=17 WHERE `entry`=45166;

-- Withdrawn Soul
SET @ENTRY := 45166;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,2,8,0,50,0,84375,1,0,0,33,45166,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit"),
(@ENTRY,@SOURCETYPE,1,0,8,0,50,0,84375,1,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Set Faction Hostile"),
(@ENTRY,@SOURCETYPE,2,5,61,0,100,0,0,0,0,0,46,45,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Move Forward"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,41,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn"),
(@ENTRY,@SOURCETYPE,4,0,1,0,100,0,5000,5000,5000,5000,2,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Reset Faction"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,1,0,2500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,6,0,0,0,100,0,1000,1000,5000,5000,11,85424,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Spirit Burst");

SET @CGUID := 400650;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+11;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 45208, 0, 1, 1, 0, 1, 1521.33, -1921.42, 60.2265, 4.93734, 300, 0, 0, 1050, 1097, 0, 0, 0, 0),
(@CGUID+1, 45208, 0, 1, 1, 0, 1, 1519.9, -1924.02, 59.7796, 5.85759, 300, 0, 0, 1009, 1067, 0, 0, 0, 0),
(@CGUID+2, 45208, 0, 1, 1, 0, 1, 1522.57, -1925.59, 60.1541, 1.94816, 300, 0, 0, 1009, 1067, 0, 0, 0, 0),
(@CGUID+3, 45208, 0, 1, 1, 0, 1, 1523.54, -1922.46, 60.6351, 3.23966, 300, 0, 0, 1050, 1097, 0, 0, 0, 0),
(@CGUID+4, 45208, 0, 1, 1, 0, 1, 1503.92, -1931.03, 60.3638, 6.25247, 300, 0, 0, 1050, 1097, 0, 0, 0, 0),
(@CGUID+5, 45208, 0, 1, 1, 0, 1, 1523.41, -1912.52, 61.157, 6.13855, 300, 0, 0, 1050, 1097, 0, 0, 0, 0),
(@CGUID+6, 45208, 0, 1, 1, 0, 1, 1526.36, -1914.08, 61.6328, 2.99749, 300, 0, 0, 1050, 1097, 0, 0, 0, 0),
(@CGUID+7, 45208, 0, 1, 1, 0, 1, 1526.68, -1911.61, 61.7991, 3.71524, 300, 0, 0, 1050, 1097, 0, 0, 0, 0),
(@CGUID+8, 45208, 0, 1, 1, 0, 1, 1513.16, -1921.59, 59.3114, 3.8299, 300, 0, 0, 1009, 1067, 0, 0, 0, 0),
(@CGUID+9, 45208, 0, 1, 1, 0, 1, 1512.78, -1925.84, 59.3005, 2.30102, 300, 0, 0, 1009, 1067, 0, 0, 0, 0),
(@CGUID+10, 45208, 0, 1, 1, 0, 1, 1509, -1924.52, 59.2929, 0.728273, 300, 0, 0, 1050, 1097, 0, 0, 0, 0),
(@CGUID+11, 45165, 0, 1, 1, 0, 1, 1518.54, -1916.99, 59.9707, 2.13363, 300, 0, 0, 1995, 1534, 0, 0, 0, 0);

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '27172';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49416, 202, 27172, 1, 74, 0);

UPDATE `creature` SET `phaseMask`=1 WHERE `id`=45209;
UPDATE `creature_template` SET `mindmg`=43, `maxdmg`=65, `attackpower`=16, `dmg_multiplier`=1.1, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=45209;

-- Provincial Minuteman
SET @ENTRY := 45231;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive");

-- Provincial Minuteman
SET @ENTRY := 45232;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive");

-- Provincial Minuteman
SET @ENTRY := 45233;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive");

-- Provincial Minuteman
SET @ENTRY := 45234;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive");

-- Provincial Minuteman
SET @ENTRY := 45231;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive");

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '11953';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(11953, 'If you really want to help out, you can help me and my friends with some combat practice.', 1, 1);

UPDATE `creature_template` SET `mindmg`=64, `maxdmg`=98, `attackpower`=21, `dmg_multiplier`=1.2, `faction_A`=35, `faction_H`=35 WHERE `entry`=45212;
UPDATE `creature_template` SET `mindmg`=32, `maxdmg`=45, `attackpower`=21 WHERE `entry` IN (45231, 45232, 45233, 45234);

-- Gory
SET @ENTRY := 45212;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11953,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,10,62,0,100,0,11953,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,45212,0,0,2,974,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Enemy"),
(@ENTRY,@SOURCETYPE,3,9,1,0,100,0,25000,25000,25000,25000,2,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Reset Faction"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,1000,1000,4000,4000,11,40504,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Cleave"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,2500,2500,6000,6000,11,50335,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Scourge Hook"),
(@ENTRY,@SOURCETYPE,6,10,2,0,100,0,1,35,0,0,1,1,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On HP Percent - Talk 1"),
(@ENTRY,@SOURCETYPE,7,0,4,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,1,45212,0,0,33,45212,0,0,0,0,0,18,100,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Quest Credit "),
(@ENTRY,@SOURCETYPE,9,0,61,0,100,0,0,0,0,0,81,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Reset Gossip Flag"),
(@ENTRY,@SOURCETYPE,10,11,61,0,100,0,0,0,0,0,83,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Gossip Flag"),
(@ENTRY,@SOURCETYPE,11,12,61,0,100,0,0,0,0,0,2,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Reset Faction"),
(@ENTRY,@SOURCETYPE,12,14,61,0,100,0,0,0,0,0,24,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Evade"),
(@ENTRY,@SOURCETYPE,13,0,52,0,100,0,0,45212,0,0,49,0,0,0,0,0,0,18,20,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Attack Invoker"),
(@ENTRY,@SOURCETYPE,14,0,61,0,100,0,0,0,0,0,33,45212,0,0,0,0,0,18,100,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete");

DELETE FROM `spell_area` WHERE `spell` = '84482' AND `quest_start` = '27173';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(84482, 202, 27173, 27173, 1, 10);

DELETE FROM `spell_area` WHERE `quest_start` = '27174';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(84452, 202, 27174, 27174, 1, 10),
(84456, 202, 27174, 27174, 1, 10),
(84457, 202, 27174, 27174, 1, 10),
(84458, 202, 27174, 27174, 1, 10);

DELETE FROM `spell_script_names` WHERE `spell_id` IN (84452, 84456, 84457, 84458, 84482);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(84452, 'spell_summon_generic_controller'),
(84456, 'spell_summon_generic_controller'),
(84457, 'spell_summon_generic_controller'),
(84458, 'spell_summon_generic_controller'),
(84482, 'spell_summon_generic_controller');

-- Thurman Grant
SET @ENTRY := 45165;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,27173,0,0,0,85,84940,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewared - Despawn All Summons"),
(@ENTRY,@SOURCETYPE,1,0,20,0,100,0,27174,0,0,0,85,84940,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewared - Despawn All Summons");

DELETE FROM `creature_text` WHERE `entry`=45212;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45212,0,0,'You want to fight? Alright, Gory fight.',12,0,100,0,0,0,'Comment'),
(45212,1,0,'Gory give up! You farmers fight more good!',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `mindmg`=48, `maxdmg`=72, `attackpower`=18, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry` IN (44488, 44487, 44482, 44489, 44479, 44478, 45153, 44551);

-- Pome Wraith
SET @ENTRY := 44488;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,85737,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Rotten to the Core"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,15000,15000,15000,15000,11,85737,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Rotten to the Core");

-- Thrashing Pumpkin
SET @ENTRY := 44487;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,85733,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Foul Juice"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,8000,8000,8000,8000,11,85733,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Foul Juice");

-- Hulking Plaguebear
SET @ENTRY := 44482;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,50256,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Demoralizing Roar"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,2000,6000,6000,11,85419,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Bellowing Roar");

DELETE FROM `creature_loot_template` WHERE `item` = '60763';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(1817, 60763, -56.4062, 1, 0, 1, 1);

DELETE FROM `creature_loot_template` WHERE `item` = '60761';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(1822, 60761, -78.3574, 1, 0, 1, 1);

DELETE FROM `creature_loot_template` WHERE `item` = '60760';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(1824, 60760, -77.6603, 1, 0, 1, 1);

UPDATE `creature_template` SET `flags_extra`=0 WHERE `entry`=44489;

-- Corn Stalker
SET @ENTRY := 44489;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,85729,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Popping Corn");

UPDATE `quest_template` SET `PrevQuestId`='27155' WHERE `Id`=27053;
UPDATE `quest_template` SET `PrevQuestId`='27057' WHERE `Id`=26955;

DELETE FROM `creature_text` WHERE `entry`=44269;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(44269,0,0,'Shapeshift! Over here, mon!',12,0,100,0,0,0,'Comment'),
(44269,1,0,'Zen\'Kiki is in control!',12,0,100,0,0,0,'Comment'),
(44269,1,1,'Meow!',12,0,100,0,0,0,'Comment'),
(44269,1,2,'Rawrr!!',12,0,100,0,0,0,'Comment'),
(44269,2,0,'Shapeshift! Time for cat form!',12,0,100,0,0,0,'Comment'),
(44269,3,0,'Pounce!',12,0,100,0,0,0,'Comment'),
(44269,3,1,'Meow!',12,0,100,0,0,0,'Comment'),
(44269,3,2,'Rawr!',12,0,100,0,0,0,'Comment'),
(44269,3,3,'Leap!',12,0,100,0,0,0,'Comment'),
(44269,4,0,'Get back over there. mon!',12,0,100,0,0,0,'Comment'),
(44269,5,0,'Shapeshift! Oh no! Not again...',12,0,100,0,0,0,'Comment'),
(44269,6,0,'Can Zen\'Kiki get a little nudge?',12,0,100,0,0,0,'Comment'),
(44269,7,0,'A little help here...',12,0,100,0,0,0,'Comment'),
(44269,8,0,'Shapeshift! Here come de moonfire!',12,0,100,0,0,0,'Comment'),
(44269,9,0,'Cut it out!',12,0,100,0,0,0,'Comment'),
(44269,9,1,'It burns like the moon!',12,0,100,0,0,0,'Comment'),
(44269,9,2,'It burns!',12,0,100,0,0,0,'Comment'),
(44269,9,3,'Stop dat!',12,0,100,0,0,0,'Comment'),
(44269,9,4,'Ow, mon!',12,0,100,0,0,0,'Comment'),
(44269,9,5,'OUTCH!',12,0,100,0,0,0,'Comment'),
(44269,10,0,'Hello mon! Let\'s kill some wildlife!',12,0,100,0,0,0,'Comment'),
(44269,12,0,'One is coming! Attack, now!',12,0,100,0,0,0,'Comment'),
(44269,12,1,'Come here...',12,0,100,0,0,0,'Comment');

-- Zen'Kiki Bear Form Offset Vehicle
SET @ENTRY := 44555;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,85,83766,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Bear Form (Visual - Invoker)"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,85,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Invoker"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,1,0,0,11,83453,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Cast Pounce"),
(@ENTRY,@SOURCETYPE,4,0,8,0,100,0,83453,1,0,0,45,0,2,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Pounce - Set Data 2 to Zen'Kiki"),
(@ENTRY,@SOURCETYPE,5,0,28,0,100,0,0,0,0,0,28,83766,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Invoker Remove Bear Form (Visual)");

-- Zen'Kiki Aquatic Form Offset Vehicle
SET @ENTRY := 44552;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,85,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Invoker");

-- Zen'Kiki
SET @ENTRY := 44269;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Invincible"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,1,10,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 10"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,1000,1000,4000,4000,11,83457,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Wrath"),
(@ENTRY,@SOURCETYPE,4,0,0,0,5,0,5000,5000,5000,5000,11,83093,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Bear Form"),
(@ENTRY,@SOURCETYPE,5,0,8,0,100,0,83766,1,0,0,1,0,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 0 (Bear)"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,1,44269,0,0,45,0,1,0,0,0,0,11,44555,5,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 1 to Bear"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,0,0,2,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 1"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,0,44269,0,0,1,1,2500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,9,0,0,0,5,0,5000,5000,5000,5000,11,83452,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Cat Form"),
(@ENTRY,@SOURCETYPE,10,0,8,0,100,0,83452,1,0,0,1,2,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 2 (Cat)"),
(@ENTRY,@SOURCETYPE,11,0,8,0,100,0,83452,1,0,0,18,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Set Pacified"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,0,2,44269,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,13,0,52,0,100,0,3,44269,0,0,19,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Remove Pacified"),
(@ENTRY,@SOURCETYPE,14,0,0,0,5,0,5000,5000,5000,5000,11,82815,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Moonkin Form"),
(@ENTRY,@SOURCETYPE,15,0,8,0,100,0,82815,1,0,0,1,8,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 8 (Moonkin)"),
(@ENTRY,@SOURCETYPE,16,0,52,0,100,0,8,44269,0,0,11,83091,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 8 - Cast Moonfire Spam"),
(@ENTRY,@SOURCETYPE,17,0,8,0,100,0,82816,64,0,0,1,9,1000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 9"),
(@ENTRY,@SOURCETYPE,18,0,8,0,5,0,83085,1,0,0,1,5,3500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 5 (Aquatic)"),
(@ENTRY,@SOURCETYPE,19,0,52,0,100,0,5,44269,0,0,1,6,3500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 5 - Talk 6"),
(@ENTRY,@SOURCETYPE,20,0,52,0,100,0,6,44269,0,0,1,7,3500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 6 - Talk 7"),
(@ENTRY,@SOURCETYPE,21,0,0,0,10,0,5000,5000,5000,5000,11,83085,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Aquatic Form"),
(@ENTRY,@SOURCETYPE,22,0,1,0,100,0,10000,10000,10000,10000,19,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Remove Pacified (Safety Check)"),
(@ENTRY,@SOURCETYPE,23,0,4,0,100,0,0,0,0,0,11,83872,32,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Mark of the Wild"),
(@ENTRY,@SOURCETYPE,24,0,0,0,50,0,8500,8500,8500,8500,11,12160,32,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Rejuvenation"),
(@ENTRY,@SOURCETYPE,25,0,1,0,100,0,6000,6000,6000,6000,49,0,0,0,0,0,0,11,44481,18,0,0.0,0.0,0.0,0.0,"OOC - Attack Diseased Hawk"),
(@ENTRY,@SOURCETYPE,26,0,4,0,100,0,0,0,0,0,1,12,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 12");

-- Diseased Hawk
SET @ENTRY := 44481;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5000,5000,5000,5000,11,81236,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Diseased Spit"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Defensive");

-- Diseased Wolf
SET @ENTRY := 1817;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,4000,9000,35000,40000,11,3427,32,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Diseased Wolf - In Combat - Cast Infected Wound"),
(@ENTRY,@SOURCETYPE,1,0,6,0,100,0,0,0,0,0,33,44777,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit");

-- Plague Lurker
SET @ENTRY := 1824;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,33,44777,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,8000,8000,11,85713,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Intoxicating Venom"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,11,4167,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Web");

-- Hulking Plaguebear
SET @ENTRY := 44482;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,50256,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Demoralizing Roar"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,2000,6000,6000,11,85419,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Bellowing Roar"),
(@ENTRY,@SOURCETYPE,2,0,6,0,100,0,0,0,0,0,33,44777,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit");

-- Venom Mist Lurker
SET @ENTRY := 1822;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,85826,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Blinding Webs"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,8000,8000,11,3583,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Deadly Poisons"),
(@ENTRY,@SOURCETYPE,2,0,6,0,100,0,0,0,0,0,33,44777,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit");

UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry` IN (44552, 44555);

-- Adrine Towhide
SET @ENTRY := 44456;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,44456,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0," Adrine Towhide  - On gossip option select - Close gossip"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,85,83819,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0," Adrine Towhide - Cast"),
(@ENTRY,@SOURCETYPE,2,0,20,0,100,0,26953,0,0,0,85,84940,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Reward - Remove Zen'Kiki"),
(@ENTRY,@SOURCETYPE,3,0,20,0,100,0,26954,0,0,0,85,84940,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Reward - Remove Zen'Kiki"),
(@ENTRY,@SOURCETYPE,4,0,20,0,100,0,26955,0,0,0,85,84940,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Reward - Remove Zen'Kiki");

UPDATE `creature_template` SET `mindmg`=79, `maxdmg`=74, `attackpower`=18, `InhabitType`=4 WHERE `entry`=44481;
UPDATE `creature` SET `spawndist`=20, `MovementType`=1 WHERE `id`=44481;

DELETE FROM `spell_area` WHERE `spell` = '83456' AND `quest_start` = '26953';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(83456, 28, 26953, 26953, 1, 10);

DELETE FROM `spell_area` WHERE `spell` = '83456' AND `quest_start` = '26954';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(83456, 28, 26954, 26954, 1, 10);

DELETE FROM `spell_area` WHERE `spell` = '83819';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(83819, 28, 26955, 26955, 1, 10);

-- Redpine Shaman
SET @ENTRY := 44479;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,86042,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Unleash Earth"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,4000,4000,11,75068,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Lava Burst");

-- Redpine Gnoll
SET @ENTRY := 44478;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5000,5000,5000,5000,11,9080,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Hamstring");

-- Redpine Looter
SET @ENTRY := 45153;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,3000,3000,11,14873,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Sinister Strike"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,2000,6500,6500,11,15691,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Eviscerate");

-- Rabid Fox
SET @ENTRY := 44551;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,85690,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Fox's Cunning"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,4000,4000,11,85691,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Piercing Howl");

UPDATE `creature_template` SET `Health_mod`=1, `minlevel`=37, `maxlevel`=37, `VehicleId`=1052, `spell1`=83605 WHERE `entry`=44832;
UPDATE `creature_template` SET `npcflag`=1, `ScriptName`='npc_hearthglen_mustang' WHERE `entry`=44836;
UPDATE `creature_template` SET `mindmg`=49, `maxdmg`=72, `attackpower`=18, `dmg_multiplier`=1.1 WHERE `entry`=44437;

-- Northridge Spider
SET @ENTRY := 44284;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On AI Init - Set Defensive"),
(@ENTRY,@SOURCETYPE,1,2,8,0,100,0,83605,1,0,0,11,65965,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Fear!"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,33,44850,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,5000,5000,5000,5000,45,0,1,0,0,0,0,11,11616,35,0,0.0,0.0,0.0,0.0,"IC - Set Data 1 to Recruits"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,1,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Force Despawn");

-- Nathaniel Dumah
SET @ENTRY := 11616;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,33,44838,0,0,0,0,0,18,100,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Quest Credit"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,45,0,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Data 1 to Invoker");

UPDATE `quest_template` SET `Flags`=0 WHERE `Id` IN (27151, 27152, 27153, 27154, 27155);
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11943 AND `id`=0;

DELETE FROM `conditions` WHERE `SourceGroup`=11943;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11943, 0, 0, 0, 9, 0, 27156, 0, 0, 0, 0, 0, '', 'Heartglen Trainee - Show gossip only if quest 27156 is active');

-- Hearthglen Trainee
SET @ENTRY := 45162;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11943,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11943,0,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Set Enemy"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,11943,0,0,0,49,14,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Attack Invoker"),
(@ENTRY,@SOURCETYPE,3,0,1,0,100,0,5000,5000,5000,5000,2,2071,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Reset Faction"),
(@ENTRY,@SOURCETYPE,4,0,4,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,5,0,4,0,100,0,0,0,0,0,11,32064,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Battle Shout"),
(@ENTRY,@SOURCETYPE,6,0,0,0,100,0,1000,1000,4000,4000,11,32736,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Mortal Strike"),
(@ENTRY,@SOURCETYPE,7,0,0,0,100,0,1000,1000,6000,6000,11,11977,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Rend"),
(@ENTRY,@SOURCETYPE,8,0,0,0,100,0,3000,3000,7500,7500,11,57846,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Heroic Strike"),
(@ENTRY,@SOURCETYPE,9,0,0,0,100,0,12500,12500,12500,12500,11,79872,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shockwave"),
(@ENTRY,@SOURCETYPE,10,11,2,0,100,1,5,25,0,0,33,45162,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On HP Percent - Quest Credit"),
(@ENTRY,@SOURCETYPE,11,12,61,0,100,0,0,0,0,0,11,7267,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Duel Beg"),
(@ENTRY,@SOURCETYPE,12,13,61,0,100,0,0,0,0,0,2,2071,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Reset Faction"),
(@ENTRY,@SOURCETYPE,13,0,61,0,100,0,0,0,0,0,41,2000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Despawn"),
(@ENTRY,@SOURCETYPE,14,0,1,0,100,0,2000,6000,2000,6000,5,36,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Play Emote");

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '11934';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(11934, 1, 1, 'I would like to buy from you.', 3, 128, 0, 0, 0, 0, ''),
(11934, 0, 0, 'Have you noticed anything strange lately?  Any new customers in the blacksmith shop?', 1, 1, 0, 0, 0, 0, '');

DELETE FROM `creature_text` WHERE `entry`=45148;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45148,0,0,'Well, let\'s see... I saw some drudges running away from that mine over there. Said something about a spider. New customers? Well, there\'s Jeralee, the lovely young gnome who bought an axe twice her size last week. Oh, and Magus Bisp came by asking for armor. Not sure why he\'d need plate armor...',12,0,100,0,0,0,'Comment');

-- Morris Vant
SET @ENTRY := 45148;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11934,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11934,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,11934,0,0,0,33,45148,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit");

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '11936';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(11936, 1, 1, 'I would like to buy from you.', 3, 128, 0, 0, 0, 0, ''),
(11936, 0, 0, 'Have you noticed anything strange lately?  Any new customers, buying anything suspicious?', 1, 1, 0, 0, 0, 0, '');

DELETE FROM `creature_text` WHERE `entry`=45149;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45149,0,0,'What is this, an interrogation? You\'re not one of Fordring\'s internal affairs guys, are you?',12,0,100,0,0,0,'Comment'),
(45149,1,0,'Well, I\'ve got nothing to hide. Let me look over my records. Last week I sold a ball gown to Lieutenant Myner, which struck me as odd. What else... Magus Bisp bought several dozen leather jerkins, which he couldn\'t give a reason for. Oh, and Friar Burlingham came by to stock up on swimwear for his trip to Hardwrench Hideaway. That\'s about it.',12,0,100,0,0,0,'Comment'),
(45149,2,0,'Now if you don\'t mind, I have customers!',12,0,100,0,0,0,'Comment');

-- Outfitter Mendelev
SET @ENTRY := 45149;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11936,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11936,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,45149,0,0,1,1,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,45149,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,2,45149,0,0,33,45149,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Quest Credit");

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11938 AND `id`=0;

DELETE FROM `creature_text` WHERE `entry`=45150;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45150,0,0,'Well, let\'s see. I heard that Magus Bisp has been spending his time cooped up on top of his tower, working on some new spell, or something.',12,0,100,0,0,0,'Comment'),
(45150,1,0,'I heard that Del Gahrron was planning on retiring and heading back to his farm. He may have already left, in fact.',12,0,100,0,0,0,'Comment'),
(45150,2,0,'Oh, and I heard that there\'s some strange people running around town asking people asll sorts of annoying questions!',12,0,100,0,0,0,'Comment'),
(45150,3,0,'Just playing with you, love. Hope that information helped.',12,0,100,0,0,0,'Comment');

-- Bree Ironstock
SET @ENTRY := 45150;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11938,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11938,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,45150,0,0,1,1,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,45150,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,2,45150,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,3,45150,0,0,33,45150,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Quest Credit");

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11940 AND `id`=0;

DELETE FROM `creature_text` WHERE `entry`=45151;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45151,0,0,'Stolen supplies? Well, let me think about it...',12,0,100,0,0,0,'Comment'),
(45151,1,0,'I know a certain priest named Daria who took all the extra wine after last week\'s service, but didn\'t throw it out as I asked. I believe she\'ll be apologizing soon, though.',12,0,100,0,0,0,'Comment'),
(45151,2,0,'<Alphus winks at you.>',16,0,100,0,0,0,'Comment'),
(45151,3,0,'I\'ve also heard an abnormal number of confessions this week from one of the mages... what was his name? Crisp? Lisp? Something along those lines.',12,0,100,0,0,0,'Comment'),
(45151,4,0,'Now, be on your way.',12,0,100,0,0,0,'Comment');

-- High Cleric Alphus
SET @ENTRY := 45151;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11940,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11940,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,45151,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,45151,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,2,45151,0,0,1,3,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,3,45151,0,0,1,4,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Talk 4"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,4,45151,0,0,33,45151,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Quest Credit");

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '11942';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(11942, 'I was just wondering what you knew about the gnolls to the south. Someone has been giving them supplies to practice necromancy.', 1, 1);

DELETE FROM `creature_text` WHERE `entry`=45152;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45152,0,0,'You\'ll pay with your life for interfering with my plans, you miserable scum!',14,0,100,0,0,0,'Comment');

-- Magus Bisp
SET @ENTRY := 45152;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11942,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11942,0,0,0,1,0,1500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0"),
(@ENTRY,@SOURCETYPE,2,3,52,0,100,0,0,45152,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Aggressive"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,18,15,0,0,0.0,0.0,0.0,0.0,"Link - Attack Invoker"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,1000,1000,3000,3000,11,79868,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Arcane Blast"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,4000,4000,12500,12500,11,79868,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Arcane Missiles"),
(@ENTRY,@SOURCETYPE,6,0,4,0,100,0,0,0,0,0,11,79880,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Slow"),
(@ENTRY,@SOURCETYPE,7,0,1,0,100,0,8000,8000,8000,8000,2,2071,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Reset Faction"),
(@ENTRY,@SOURCETYPE,8,0,6,0,100,0,0,0,0,0,33,45152,0,0,0,0,0,18,50,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit");

DELETE FROM `conditions` WHERE `SourceGroup`=11942;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11942, 0, 0, 0, 9, 0, 27154, 0, 0, 0, 0, 0, '', 'Magus Bisp - Show gossip only if quest 27154 is active');

DELETE FROM `conditions` WHERE `SourceGroup`=11940;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11940, 0, 0, 0, 9, 0, 27153, 0, 0, 0, 0, 0, '', 'High Cleric Alphus  - Show gossip only if quest 27153 is active');

DELETE FROM `conditions` WHERE `SourceGroup`=11938;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11938, 0, 0, 0, 9, 0, 27153, 0, 0, 0, 0, 0, '', 'Bree Ironstock - Show gossip only if quest 27153 is active');

DELETE FROM `conditions` WHERE `SourceGroup`=11936;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11936, 0, 0, 0, 9, 0, 27153, 0, 0, 0, 0, 0, '', 'Outfitter Mendelev - Show gossip only if quest 27153 is active');

DELETE FROM `conditions` WHERE `SourceGroup`=11934;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11934, 0, 0, 0, 9, 0, 27153, 0, 0, 0, 0, 0, '', 'Morris Vant - Show gossip only if quest 27153 is active');

UPDATE `creature_template_addon` SET `auras`='' WHERE `entry`=44905;
UPDATE `quest_template` SET `PrevQuestId`='27155' WHERE `Id`=26957;
UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=772861;

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` = '26957';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(49417, 5367, 26957, 0, 1, 74, 0);

DELETE FROM `creature_text` WHERE `entry`=44904;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(44904,0,0,'De tauren say that she\'ll teach me to heal if we do a good job! Let\'s go, mon!',12,0,100,0,0,0,'Comment');

-- Cultist Cage
SET @ENTRY := 207428;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,44902,15,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Captive Plaguebear");

-- Cultist Cage
SET @ENTRY := 207427;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,44902,15,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Captive Plaguebear");

-- Cultist Cage
SET @ENTRY := 205159;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,44902,15,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Captive Plaguebear");

-- Cultist Cage
SET @ENTRY := 205156;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,44902,15,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Captive Plaguebear");

-- Cultist Cage
SET @ENTRY := 205155;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,44902,15,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Captive Plaguebear");

-- Cultist Cage
SET @ENTRY := 205158;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,44902,15,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Captive Plaguebear");

-- Cultist Cage
SET @ENTRY := 207430;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,44902,15,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Captive Plaguebear");

-- Cultist Cage
SET @ENTRY := 205160;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,44902,15,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Captive Plaguebear");

-- Cultist Cage
SET @ENTRY := 205157;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,44902,15,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Captive Plaguebear");

-- Cultist Cage
SET @ENTRY := 207429;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,44902,15,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Captive Plaguebear");


-- Captive Plaguebear
SET @ENTRY := 44902;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,38,0,100,1,0,1,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,1,0,0,0,0,41,6000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn"),
(@ENTRY,@SOURCETYPE,2,0,60,1,100,1,2000,2000,2000,2000,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Set Run"),
(@ENTRY,@SOURCETYPE,3,0,60,1,100,1,2000,2000,2000,2000,46,80,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Move Forward"),
(@ENTRY,@SOURCETYPE,4,5,60,1,100,1,3000,3000,3000,3000,45,0,1,0,0,0,0,11,44904,50,0,0.0,0.0,0.0,0.0,"Update - Set Data 1 to Zen'Kiki"),
(@ENTRY,@SOURCETYPE,5,6,61,1,100,1,0,0,0,0,11,32994,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Rejuvenation"),
(@ENTRY,@SOURCETYPE,6,0,61,1,100,1,0,0,0,0,33,44902,0,0,0,0,0,18,50,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit");

-- Zen'Kiki
SET @ENTRY := 44904;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive "),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,1000,1000,2100,2100,11,83457,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Wrath"),
(@ENTRY,@SOURCETYPE,3,0,4,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,4,0,0,0,85,0,9500,9500,9500,9500,11,12160,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Rejuvenation"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,1,0,0,11,12160,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Cast Rejuvenation on Captive Plaguebear");

-- Cult-Sworn Warlock
SET @ENTRY := 44443;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,86180,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Dark Plague"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,2000,5000,5000,11,79938,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Incinerate"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,3000,3000,6500,6500,11,79938,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Void Whip");

-- Cult-Sworn Pugilist
SET @ENTRY := 44444;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,12500,12500,11,86180,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Dark Plague"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,6000,6000,3500,3500,11,14873,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Sinister Strike");

UPDATE `creature_template` SET `mindmg`=46, `maxdmg`=69, `attackpower`=17, `dmg_multiplier`=1.1 WHERE `entry` IN (44444, 44443, 44442, 45154, 45155, 45156, 44486, 44484, 44485, 44445);

-- Instructor Malicia
SET @ENTRY := 44442;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,13747,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Slow");

-- Redpine Necromancer
SET @ENTRY := 45154;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,86064,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Wandering Shadows");

-- Moldfang
SET @ENTRY := 45155;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,8500,8500,11,86070,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Pierce Armor");

-- Shadril
SET @ENTRY := 45156;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,86071,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Acid Cloud"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,8500,8500,11,0,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Pierce Armor"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,3500,3500,4000,4000,11,0,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Leech Poison");

-- Unholy Corpuscle
SET @ENTRY := 44486;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,10000,10000,11,86002,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Fetid Absorption");

-- Flesh-Cobbled Brute
SET @ENTRY := 44484;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,5000,5000,11,91335,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Slam");

-- Flesh-Cobbled Ripper
SET @ENTRY := 44485;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,8000,8000,11,13443,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Rend");

-- Krastinovian Disciple
SET @ENTRY := 44445;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,6000,6000,11,38556,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Throw");

DELETE FROM `creature` WHERE `guid` IN (209572, 209573);
UPDATE `creature_template` SET `unit_flags`=2 WHERE `entry`=44323;
UPDATE `creature` SET `spawndist`=0, `MovementType`=0 WHERE `guid`=209873;
UPDATE `creature_template` SET `InhabitType`=4, `ScriptName`='npc_shadow_prison' WHERE `entry`=46558;

DELETE FROM `spell_script_names` WHERE `spell_id` = '86780';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(86780, 'spell_shadow_prison');

DELETE FROM `creature` WHERE `guid` IN (209882, 209881, 773054);
DELETE FROM `creature_addon` WHERE `guid` IN (209882, 209881, 773054);

UPDATE `creature_template` SET `unit_flags`=0, `unit_flags2`=2048, `flags_extra`=0 WHERE `entry` iN (44453, 44452);
UPDATE `creature_template` SET `mindmg`=500, `maxdmg`=500 WHERE `entry` IN (44452, 44453);
UPDATE `creature_template` SET `faction_A`=1725, `faction_H`=1725 WHERE `entry`=44453;
UPDATE `creature_template` SET `faction_A`=1725, `faction_H`=1725 WHERE `entry`=44452;

DELETE FROM `creature_text` WHERE `entry`=44452;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(44452,0,0,'For the Horde!',14,0,100,0,0,0,'Comment'),
(44452,1,0,'You heard correctly, Thassarian. I wanted to give you a chance to kill me again.',12,0,100,0,0,0,'Comment'),
(44452,2,0,'Yes, it may... but not today. With the Scourge out of the way, I plan to pull my troops back and regroup.',12,0,100,0,0,0,'Comment'),
(44452,3,0,'Yes, I know. And don\'t think I\'ll go easy on you.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=44453;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(44453,0,0,'Gandling is strong, but do not worry. I will join you shortly after you begin to fight him.',12,0,100,0,0,0,'Comment'),
(44453,1,0,'For the Alliance!',14,0,100,0,0,0,'Comment'),
(44453,2,0,'Koltira! I had heard rumors that you were here in Lordaeron.',12,0,100,0,0,0,'Comment'),
(44453,3,0,'Thassarian laughs',16,0,100,0,0,0,'Comment'),
(44453,4,0,'It looks like it may have to come to that.',12,0,100,0,0,0,'Comment'),
(44453,5,0,'I see. Then I will do the same.',12,0,100,0,0,0,'Comment'),
(44453,6,0,'But you must be aware, Koltira: we are brothers no longer. You are a member of the Horde now, and I of the Alliance.',12,0,100,0,0,0,'Comment'),
(44453,7,0,'Eventually, we will fight this battle for Andorhal, and only one of us can walk off the battlefield victorious.',12,0,100,0,0,0,'Comment'),
(44453,8,0,'Thassarian laughs',16,0,100,0,0,0,'Comment'),
(44453,9,0,'Very well. I look forward to it.',12,0,100,0,0,0,'Comment'),
(44453,10,0,'You are not to speak to ANYONE about the agreement that was made today. Consider this an order from your direct superior.',15,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=44323;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(44323,0,0,'Prepare to die!',12,0,100,0,0,0,'Comment'),
(44323,1,0,'Your life is forfeit.',12,0,100,0,0,0,'Comment'),
(44323,2,0,'Enough of this. The Cult of the Damned doesn\'t need Andorhal. This worthless city is yours to fight over.',12,0,100,0,0,0,'Comment');

-- Thassarian
SET @ENTRY := 44453;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,1,0,37,0,100,0,0,0,0,0,49,1,0,0,0,0,0,11,44323,80,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Darkmaster Gandling"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,10,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Talk 2"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,2,44453,0,0,45,0,1,0,0,0,0,11,44452,50,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 1 to Koltira"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,1,0,0,1,3,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 3"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,3,44453,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Talk 4"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,4,44453,0,0,45,0,2,0,0,0,0,11,44452,50,0,0.0,0.0,0.0,0.0,"After Talk 4 - Set Data 2 to Koltira"),
(@ENTRY,@SOURCETYPE,8,0,38,0,100,0,0,2,0,0,1,5,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 5"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,5,44453,0,0,1,6,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 5 - Talk 6"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,6,44453,0,0,1,7,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 6 - Talk 7"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,0,7,44453,0,0,45,0,3,0,0,0,0,11,44452,50,0,0.0,0.0,0.0,0.0,"After Talk 7 - Set Data 3 to Koltira"),
(@ENTRY,@SOURCETYPE,12,0,38,0,100,0,0,3,0,0,1,8,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 8"),
(@ENTRY,@SOURCETYPE,13,0,52,0,100,0,8,44453,0,0,1,9,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 8 - Talk 9"),
(@ENTRY,@SOURCETYPE,14,0,52,0,100,0,9,44453,0,0,1,10,2000,0,0,0,0,18,50,0,0,0.0,0.0,0.0,0.0,"After Talk 9 - Talk 10"),
(@ENTRY,@SOURCETYPE,15,16,52,0,100,0,10,44453,0,0,33,44323,0,0,0,0,0,18,50,0,0,0.0,0.0,0.0,0.0,"After Talk 10 - Quest Credit"),
(@ENTRY,@SOURCETYPE,16,0,61,0,100,0,0,0,0,0,41,500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn "),
(@ENTRY,@SOURCETYPE,17,0,38,0,100,0,0,1,0,0,66,45,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Orientation");

-- Koltira Deathweaver
SET @ENTRY := 44452;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,1,0,37,0,100,0,0,0,0,0,49,0,0,0,0,0,0,11,44323,80,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Darkmaster Gandling"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,1,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,44452,0,0,45,0,1,0,0,0,0,11,44453,50,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 1 to Thassarian"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,2,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 2"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,2,44452,0,0,45,0,2,0,0,0,0,11,44453,50,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 2 to Thassarian"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,0,0,3,0,0,1,3,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 3"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,3,44452,0,0,45,0,3,0,0,0,0,11,44453,50,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 3 to Thassarian"),
(@ENTRY,@SOURCETYPE,9,0,38,0,100,0,0,1,0,0,66,15,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Orientation"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,3,44452,0,0,41,12000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Force Despawn ");

-- Darkmaster Gandling
SET @ENTRY := 44323;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,3,2,0,100,1,6,50,0,0,12,46558,4,16000,0,0,0,8,0,0,0,1284.73,-1529.88,65.88,3.09,"On Health 50% - Summon Shadow Prison"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,4000,4000,11,79932,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadow Bolt"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,2500,2500,6500,6500,11,86845,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadow Eruption"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,11,86780,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Shadow Prison"),
(@ENTRY,@SOURCETYPE,4,0,4,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,5,0,2,0,100,1,1,25,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 25% - Talk 1"),
(@ENTRY,@SOURCETYPE,6,0,4,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,1,44323,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,8,9,52,0,100,0,2,44323,0,0,45,0,10,0,0,0,0,11,0,50,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 10 to Creatures"),
(@ENTRY,@SOURCETYPE,9,0,61,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,1,44323,0,0,18,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Pacified");

UPDATE `creature` SET `phaseMask`=2, `spawndist`=15, `MovementType`=1 WHERE `id` IN (44449, 45239, 44448, 44450, 44331);
UPDATE `creature` SET `phaseMask`=3 WHERE `guid` IN (209402, 209403, 209401);
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=45239;
UPDATE `quest_template` SET `PrevQuestId`='27197' WHERE `Id`=27199;
UPDATE `quest_template` SET `PrevQuestId`='27197' WHERE `Id`=27198;

DELETE FROM `conditions` WHERE `SourceEntry` = '27205' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 27205, 27199, 0),
(20, 8, 27205, 27198, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '27205' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 27205, 27199, 0),
(19, 8, 27205, 27198, 0);

UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=44331;

-- Andorhal Deathguard
SET @ENTRY := 44331;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,33,44447,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,10000,10000,11,85524,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Might of the Forsaken");

-- Andorhal Defender
SET @ENTRY := 44448;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,10000,10000,11,85525,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Lordaeron's Call");

-- Deathguard War-Captain
SET @ENTRY := 44449;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,85527,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Rallying Cry");

-- Andorhal Force-Commander
SET @ENTRY := 44450;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,85527,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Rallying Cry");

-- Lesser Val'kyr
SET @ENTRY := 45239;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,5000,5000,11,85536,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Spectre Blast"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,5000,5000,5000,5000,49,0,0,0,0,0,0,18,45,0,0,0.0,0.0,0.0,0.0,"OOC - Attack Players");

UPDATE `creature_template` SET `mindmg`=42, `maxdmg`=63, `attackpower`=16, `dmg_multiplier`=1.1, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry` IN (44331, 44449, 45239, 44450, 44448);
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=44450;
UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry` IN (44467, 44471, 45245);
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry` IN (45246, 45252, 45245);
UPDATE `creature_template` SET `VehicleId`=1325, `speed_run`=2.14286 WHERE `entry`=45245;

DELETE FROM `waypoints` WHERE `entry` = '45245';
INSERT INTO `waypoints` (`entry`, `pointId`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(45245, 1, 1412.29, -1489.02, 124.74, 'Depravation Event Camera WP');

DELETE FROM `spell_target_position` WHERE `id` = '84484';
INSERT INTO `spell_target_position` (`id`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(84484, 1370.84, -1465.15, 118.62, 1.56);

DELETE FROM `spell_target_position` WHERE `id` = '84483';
INSERT INTO `spell_target_position` (`id`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(84483, 1369.87, -1477.31, 117.55, 1.49);

DELETE FROM `creature_text` WHERE `entry`=45246;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45246,0,0,'Kneel, Alliance! Kneel before the might of the Forsaken!',14,0,100,0,0,0,'Comment');

-- Aradne
SET @ENTRY := 45246;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,60,1,100,1,4000,4000,4000,4000,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Update - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,1,100,1,0,45246,0,0,12,45252,4,12000,0,0,0,8,0,0,0,1360.98,-1457.25,117.63,1.93,"After Talk 0 - Summon Valkyrs"),
(@ENTRY,@SOURCETYPE,3,0,60,1,100,0,10000,10000,1500,1500,11,84532,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Cast Aradne Lightning"),
(@ENTRY,@SOURCETYPE,4,0,52,1,100,1,0,45246,0,0,12,45252,4,12000,0,0,0,8,0,0,0,1371.58,-1457.78,115.1,1.62,"After Talk 0 - Summon Valkyrs"),
(@ENTRY,@SOURCETYPE,5,0,52,1,100,1,0,45246,0,0,12,45252,4,12000,0,0,0,8,0,0,0,1379.34,-1458.26,117.37,1.58,"After Talk 0 - Summon Valkyrs"),
(@ENTRY,@SOURCETYPE,6,7,60,1,100,1,18000,18000,18000,18000,45,0,1,0,0,0,0,11,45245,100,0,0.0,0.0,0.0,0.0,"Update - Set Data 1 to Camera"),
(@ENTRY,@SOURCETYPE,7,0,61,1,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

UPDATE `creature_template` SET `modelid2`=11686 WHERE `entry`=45245;
UPDATE `quest_template` SET `Flags`=0, `SpecialFlags`=2 WHERE `Id`=27205;
UPDATE `creature` SET `phaseMask`=4 WHERE `id`=45239;

DELETE FROM `spell_area` WHERE `spell` = '65141' AND `quest_start` IN (27197, 27083);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(65141, 193, 27197, 27205, 1, 64, 9),
(65141, 193, 27083, 27205, 1, 66, 9);

DELETE FROM `spell_area` WHERE `spell` IN (55858, 49417) AND `quest_start` = '27205';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(55858, 193, 27205, 27206, 1, 66, 1),
(49417, 193, 27205, 27206, 1, 66, 1);

DELETE FROM `creature_addon` WHERE `guid` IN (400768, 400767, 400670);
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(400768, '49415'),
(400767, '49415'),
(400670, '49415');

UPDATE `creature_template` SET `faction_A`=1801, `faction_H`=1801, `mindmg`=79, `maxdmg`=72, `attackpower`=18, `dmg_multiplier`=1.1, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry` IN (45240, 45241, 45242);

DELETE FROM `creature_equip_template` WHERE `entry` IN (45240, 45241, 45242);
INSERT INTO `creature_equip_template` (`entry`, `id`, `itemEntry1`, `itemEntry2`, `itemEntry3`) VALUES
(45240, 1, 1485, 0, 0),
(45241, 1, 1485, 0, 0),
(45242, 1, 1485, 0, 0);

UPDATE `creature` SET `phaseMask`=4 WHERE `id`=45101;
UPDATE `creature` SET `spawntimesecs`=60, `spawndist`=20, `MovementType`=1 WHERE `id` IN (45231, 45232, 45233, 45234);
UPDATE `creature_template` SET `minlevel`=39, `maxlevel`=40, `faction_A`=2202, `faction_H`=2202, `mindmg`=79, `maxdmg`=72, `attackpower`=18 WHERE `entry`=45231;
UPDATE `creature_template` SET `faction_A`=2161, `faction_H`=2161 WHERE `entry` IN (45240, 45241, 45242);
UPDATE `creature_template` SET `faction_A`=2202, `faction_H`=2202 WHERE `entry` IN (45231, 45232, 45233, 45234);

SET @CGUID := 400670;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+99;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 45165, 0, 1, 4, 0, 1, 1387.5, -1292.29, 58.6175, 3.75203, 300, 0, 0, 1995, 1534, 0, 0, 0, 0),
(@CGUID+1, 45234, 0, 1, 4, 0, 1, 1470.37, -1541.61, 58.9411, 5.26793, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+2, 45233, 0, 1, 4, 0, 1, 1441.23, -1515.4, 55.7365, 0.206034, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+3, 45231, 0, 1, 4, 0, 1, 1392.77, -1536.36, 58.929, 0.618368, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+4, 45231, 0, 1, 4, 0, 1, 1372.78, -1546.02, 57.8899, 1.99674, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+5, 45232, 0, 1, 4, 0, 1, 1346.32, -1586.8, 58.5253, 2.32661, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+6, 45233, 0, 1, 4, 0, 1, 1462.13, -1507.96, 55.5254, 3.83458, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+7, 45232, 0, 1, 4, 0, 1, 1485.43, -1505.09, 55.5758, 0.838282, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+8, 45234, 0, 1, 4, 0, 1, 1454.76, -1506.91, 56.0791, 0.00183249, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+9, 45233, 0, 1, 4, 0, 1, 1427.17, -1541.79, 54.9631, 1.15637, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+10, 45232, 0, 1, 4, 0, 1, 1410.63, -1560.27, 55.3648, 4.01522, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+11, 45231, 0, 1, 4, 0, 1, 1431.55, -1528.88, 55.3643, 4.29796, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+12, 45233, 0, 1, 4, 0, 1, 1353.18, -1614.17, 57.2042, 4.45199, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+13, 45234, 0, 1, 4, 0, 1, 1362.92, -1603.86, 57.5482, 3.19143, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+14, 45232, 0, 1, 4, 0, 1, 1372.51, -1595.19, 58.0204, 4.77793, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+15, 45231, 0, 1, 4, 0, 1, 1372.37, -1584.38, 58.3823, 4.3067, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+16, 45232, 0, 1, 4, 0, 1, 1391.62, -1542.78, 59.547, 0.897809, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+17, 45233, 0, 1, 4, 0, 1, 1388.17, -1547.29, 59.6264, 6.24637, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+18, 45234, 0, 1, 4, 0, 1, 1368.69, -1530.58, 57.8034, 5.41386, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+19, 45233, 0, 1, 4, 0, 1, 1363.76, -1509.19, 57.4226, 4.46746, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+20, 45232, 0, 1, 4, 0, 1, 1369.59, -1494.61, 56.7476, 5.53952, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+21, 45231, 0, 1, 4, 0, 1, 1350.16, -1480.18, 56.2331, 5.6534, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+22, 45232, 0, 1, 4, 0, 1, 1396.18, -1374.54, 53.7507, 5.42564, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+23, 45233, 0, 1, 4, 0, 1, 1387.44, -1358.5, 53.7483, 5.33532, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+24, 45232, 0, 1, 4, 0, 1, 1381.44, -1350.14, 53.7244, 4.546, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+25, 45231, 0, 1, 4, 0, 1, 1385.25, -1340.59, 55.7459, 4.78162, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+26, 45234, 0, 1, 4, 0, 1, 1393.01, -1315.85, 57.935, 4.28682, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+27, 45233, 0, 1, 4, 0, 1, 1395.22, -1305.15, 59.3961, 4.36536, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+28, 45231, 0, 1, 4, 0, 1, 1397.43, -1299.03, 60.4519, 0.14384, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+29, 45232, 0, 1, 4, 0, 1, 1390.03, -1299.49, 58.7593, 5.39423, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+30, 45231, 0, 1, 4, 0, 1, 1378.08, -1278.29, 59.7359, 2.97127, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+31, 45232, 0, 1, 4, 0, 1, 1383.67, -1279.25, 60.2617, 0.697544, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+32, 45233, 0, 1, 4, 0, 1, 1379.38, -1282.85, 59.4606, 2.55501, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+33, 45232, 0, 1, 4, 0, 1, 1398.41, -1286.2, 60.2577, 0.815354, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+34, 45231, 0, 1, 4, 0, 1, 1374.93, -1302.17, 56.6309, 0.75645, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+35, 45232, 0, 1, 4, 0, 1, 1342.16, -1361.61, 47.4866, 0.88604, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+36, 45231, 0, 1, 4, 0, 1, 1319.18, -1425.82, 47.8975, 5.10756, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+37, 45232, 0, 1, 4, 0, 1, 1310.92, -1405.01, 47.006, 4.84838, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+38, 45234, 0, 1, 4, 0, 1, 1346.94, -1413.77, 48.3555, 2.46077, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+39, 45233, 0, 1, 4, 0, 1, 1354.76, -1421.78, 48.8975, 2.30369, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+40, 45232, 0, 1, 4, 0, 1, 1451.04, -1387.11, 61.6613, 5.86939, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+41, 45231, 0, 1, 4, 0, 1, 1437.8, -1383.05, 58.6136, 0.410875, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+42, 45234, 0, 1, 4, 0, 1, 1418.03, -1388.12, 54.8274, 5.89296, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+43, 45233, 0, 1, 4, 0, 1, 1383.44, -1375.97, 54.9033, 4.71486, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+44, 45232, 0, 1, 4, 0, 1, 1381.84, -1349, 53.7213, 5.41779, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+45, 45231, 0, 1, 4, 0, 1, 1367.97, -1332.8, 52.4942, 5.32747, 60, 20, 0, 42, 0, 1, 0, 0, 0),
(@CGUID+46, 45242, 0, 1, 4, 0, 0, 1391.32, -1524.47, 59.3127, 2.87935, 60, 20, 0, 920, 1283, 1, 0, 0, 0),
(@CGUID+47, 45242, 0, 1, 4, 0, 0, 1429.32, -1430.59, 55.6864, 1.57597, 60, 20, 0, 920, 1283, 1, 0, 0, 0),
(@CGUID+48, 45242, 0, 1, 4, 0, 0, 1429.77, -1453.91, 54.1647, 2.05635, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+49, 45241, 0, 1, 4, 0, 0, 1435.3, -1473.75, 55.3008, 1.93485, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+50, 45242, 0, 1, 4, 0, 0, 1442.92, -1492.91, 56.8556, 1.21485, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+51, 45241, 0, 1, 4, 0, 0, 1441.43, -1522.39, 55.6723, 2.32297, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+52, 45241, 0, 1, 4, 0, 0, 1450.99, -1532.61, 56.0747, 0.882971, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+53, 45241, 0, 1, 4, 0, 0, 1436.08, -1552.22, 56.0588, 0.0648379, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+54, 45241, 0, 1, 4, 0, 0, 1420.48, -1551.29, 54.6793, 0.960338, 60, 20, 0, 920, 1283, 1, 0, 0, 0),
(@CGUID+55, 45241, 0, 1, 4, 0, 0, 1411.36, -1559.11, 55.3647, 5.26015, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+56, 45241, 0, 1, 4, 0, 0, 1347.08, -1592.03, 58.5042, 2.54731, 60, 20, 0, 920, 1283, 1, 0, 0, 0),
(@CGUID+57, 45241, 0, 1, 4, 0, 0, 1392.36, -1620.37, 63.4159, 1.31093, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+58, 45241, 0, 1, 4, 0, 0, 1384.78, -1630.66, 61.1715, 6.00449, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+59, 45241, 0, 1, 4, 0, 0, 1368.94, -1613.63, 57.8012, 5.15062, 60, 20, 0, 920, 1283, 1, 0, 0, 0),
(@CGUID+60, 45241, 0, 1, 4, 0, 0, 1371.81, -1591.95, 58.1848, 4.39799, 60, 20, 0, 920, 1283, 1, 0, 0, 0),
(@CGUID+61, 45241, 0, 1, 4, 0, 0, 1384.37, -1578.62, 59.6198, 5.05499, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+62, 45242, 0, 1, 4, 0, 0, 1379.15, -1561.75, 58.6818, 4.78499, 60, 20, 0, 920, 1283, 1, 0, 0, 0),
(@CGUID+63, 45242, 0, 1, 4, 0, 0, 1377.66, -1545.97, 58.3729, 5.38574, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+64, 45242, 0, 1, 4, 0, 0, 1377.19, -1528.86, 59.3284, 4.90537, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+65, 45241, 0, 1, 4, 0, 0, 1376.06, -1512.22, 58.8017, 4.45312, 60, 20, 0, 920, 1283, 1, 0, 0, 0),
(@CGUID+66, 45241, 0, 1, 4, 0, 0, 1386.14, -1499.35, 56.3439, 2.68462, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+67, 45241, 0, 1, 4, 0, 0, 1398.71, -1505.51, 56.2772, 4.22699, 60, 20, 0, 920, 1283, 1, 0, 0, 0),
(@CGUID+68, 45241, 0, 1, 4, 0, 0, 1403.93, -1495.6, 54.9243, 3.50699, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+69, 45242, 0, 1, 4, 0, 0, 1394.34, -1486.35, 56.1266, 0.405307, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+70, 45242, 0, 1, 4, 0, 0, 1365.12, -1497.43, 56.7893, 5.06737, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+71, 45242, 0, 1, 4, 0, 0, 1353.46, -1488.31, 56.692, 0.224183, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+72, 45242, 0, 1, 4, 0, 0, 1341.1, -1464.65, 55.2108, 4.88849, 60, 20, 0, 920, 1283, 1, 0, 0, 0),
(@CGUID+73, 45242, 0, 1, 4, 0, 0, 1337.67, -1445.36, 52.7585, 4.88849, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+74, 45242, 0, 1, 4, 0, 0, 1332.21, -1427.65, 49.3027, 5.87119, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+75, 45242, 0, 1, 4, 0, 0, 1313.51, -1419.27, 47.3737, 3.99469, 60, 20, 0, 920, 1283, 1, 0, 0, 0),
(@CGUID+76, 45242, 0, 1, 4, 0, 0, 1322.7, -1408.72, 46.3351, 5.53707, 60, 20, 0, 920, 1283, 1, 0, 0, 0),
(@CGUID+77, 45242, 0, 1, 4, 0, 0, 1313.21, -1393.77, 46.3528, 3.54132, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+78, 45240, 0, 1, 4, 0, 0, 1324.85, -1381.14, 46.0124, 4.63819, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+79, 45240, 0, 1, 4, 0, 0, 1330.38, -1364.42, 47.3829, 3.62344, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+80, 45240, 0, 1, 4, 0, 0, 1345.98, -1356.05, 48.3386, 4.47844, 60, 20, 0, 920, 1283, 1, 0, 0, 0),
(@CGUID+81, 45240, 0, 1, 4, 0, 0, 1398.19, -1370.02, 53.7504, 2.56032, 60, 20, 0, 920, 1283, 1, 0, 0, 0),
(@CGUID+82, 45240, 0, 1, 4, 0, 0, 1414.35, -1389.02, 54.6677, 2.95294, 60, 20, 0, 920, 1283, 1, 0, 0, 0),
(@CGUID+83, 45240, 0, 1, 4, 0, 0, 1452.02, -1373.74, 60.1238, 5.75644, 60, 20, 0, 920, 1283, 1, 0, 0, 0),
(@CGUID+84, 45240, 0, 1, 4, 0, 0, 1441.48, -1373.02, 58.8725, 1.90326, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+85, 45240, 0, 1, 4, 0, 0, 1440.82, -1386.64, 59.6981, 2.97651, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+86, 45240, 0, 1, 4, 0, 0, 1420.65, -1399.54, 55.2721, 0.985678, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+87, 45240, 0, 1, 4, 0, 0, 1411.97, -1401.85, 55.2597, 5.51386, 60, 20, 0, 920, 1283, 1, 0, 0, 0),
(@CGUID+88, 45240, 0, 1, 4, 0, 0, 1398.49, -1398.35, 55.4996, 6.23274, 60, 20, 0, 920, 1283, 1, 0, 0, 0),
(@CGUID+89, 45240, 0, 1, 4, 0, 0, 1388.69, -1389.69, 55.6397, 5.56111, 60, 20, 0, 920, 1283, 1, 0, 0, 0),
(@CGUID+90, 45240, 0, 1, 4, 0, 0, 1377.93, -1382.64, 54.9514, 5.73999, 60, 20, 0, 920, 1283, 1, 0, 0, 0),
(@CGUID+91, 45240, 0, 1, 4, 0, 0, 1375.96, -1375.15, 52.3405, 4.16386, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+92, 45240, 0, 1, 4, 0, 0, 1382.69, -1354.83, 53.7216, 4.47774, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+93, 45240, 0, 1, 4, 0, 0, 1370.45, -1339.47, 52.9408, 4.97049, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+94, 45240, 0, 1, 4, 0, 0, 1358.4, -1320.46, 52.4583, 5.42274, 60, 20, 0, 920, 1283, 1, 0, 0, 0),
(@CGUID+95, 45240, 0, 1, 4, 0, 0, 1351.76, -1307.94, 54.4701, 4.47774, 60, 20, 0, 885, 1236, 1, 0, 0, 0),
(@CGUID+96, 45240, 0, 1, 4, 0, 0, 1364.45, -1292.25, 57.7293, 6.06546, 60, 20, 0, 920, 1283, 1, 0, 0, 0),
(@CGUID+97, 44471, 0, 1, 4, 0, 1, 1378.45, -1296.6, 57.505, 5.46765, 300, 0, 0, 3048, 0, 0, 0, 0, 0),
(@CGUID+98, 44453, 0, 1, 4, 0, 1, 1381.57, -1298.76, 57.4228, 3.97104, 300, 0, 0, 542430, 0, 0, 0, 0, 0),
(@CGUID+99, 45235, 0, 1, 4, 0, 0, 1299.26, -1322.4, 99.2617, 5.99151, 300, 0, 0, 8582, 1283, 0, 0, 0, 0);

DELETE FROM `creature_addon` WHERE `guid` = '400670';
INSERT INTO `creature_addon` (`guid`, `bytes2`) VALUES
(400670, 1);

DELETE FROM `conditions` WHERE `SourceEntry` = '27204' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 27204, 27201, 0),
(20, 8, 27204, 27202, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '27204' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 27204, 27201, 0),
(19, 8, 27204, 27202, 0);

UPDATE `creature_template` SET `faction_A`=1801, `faction_H`=1801, `mindmg`=42, `maxdmg`=72, `attackpower`=18, `dmg_multiplier`=1.5, `Health_mod`=3, `lootid`=45235 WHERE `entry`=45235;

DELETE FROM `creature_loot_template` WHERE `entry` = '45235';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(45235, 866, 0.1965, 1, 0, 1, 1),
(45235, 870, 0.1637, 1, 0, 1, 1),
(45235, 1207, 0.2292, 1, 0, 1, 1),
(45235, 1529, 0.2, 1, 0, 1, 1),
(45235, 1625, 0.131, 1, 0, 1, 1),
(45235, 1640, 0.0982, 1, 0, 1, 1),
(45235, 1714, 0.0655, 1, 0, 1, 1),
(45235, 1725, 0.2, 1, 0, 1, 1),
(45235, 1980, 0.0327, 1, 0, 1, 1),
(45235, 3778, 0.7531, 1, 0, 1, 1),
(45235, 3779, 0.6549, 1, 0, 1, 1),
(45235, 3780, 0.6221, 1, 0, 1, 1),
(45235, 3781, 0.5894, 1, 0, 1, 1),
(45235, 3782, 0.6549, 1, 0, 1, 1),
(45235, 3783, 0.5239, 1, 0, 1, 1),
(45235, 3784, 0.4912, 1, 0, 1, 1),
(45235, 3785, 0.4584, 1, 0, 1, 1),
(45235, 3786, 0.9496, 1, 0, 1, 1),
(45235, 3787, 0.7204, 1, 0, 1, 1),
(45235, 3792, 0.6876, 1, 0, 1, 1),
(45235, 3793, 0.3274, 1, 0, 1, 1),
(45235, 3794, 0.3602, 1, 0, 1, 1),
(45235, 3795, 0.3602, 1, 0, 1, 1),
(45235, 3796, 0.2947, 1, 0, 1, 1),
(45235, 3797, 0.6221, 1, 0, 1, 1),
(45235, 3798, 0.6549, 1, 0, 1, 1),
(45235, 3799, 0.1, 1, 0, 1, 1),
(45235, 3800, 0.3602, 1, 0, 1, 1),
(45235, 3801, 0.1, 1, 0, 1, 1),
(45235, 3802, 0.2292, 1, 0, 1, 1),
(45235, 3803, 0.3274, 1, 0, 1, 1),
(45235, 3804, 0.5239, 1, 0, 1, 1),
(45235, 3805, 0.3602, 1, 0, 1, 1),
(45235, 3806, 0.2947, 1, 0, 1, 1),
(45235, 3807, 0.2292, 1, 0, 1, 1),
(45235, 3808, 0.1965, 1, 0, 1, 1),
(45235, 3809, 0.1965, 1, 0, 1, 1),
(45235, 3810, 0.2947, 1, 0, 1, 1),
(45235, 3811, 0.262, 1, 0, 1, 1),
(45235, 3812, 0.131, 1, 0, 1, 1),
(45235, 3813, 0.4257, 1, 0, 1, 1),
(45235, 3814, 0.1965, 1, 0, 1, 1),
(45235, 3815, 0.5239, 1, 0, 1, 1),
(45235, 3816, 0.2947, 1, 0, 1, 1),
(45235, 3817, 0.1965, 1, 0, 1, 1),
(45235, 3832, 0.0327, 1, 0, 1, 1),
(45235, 3864, 0.6221, 1, 0, 1, 1),
(45235, 3873, 0.0655, 1, 0, 1, 1),
(45235, 3874, 0.0327, 1, 0, 1, 1),
(45235, 4041, 0.0327, 1, 0, 1, 1),
(45235, 4042, 0.1965, 1, 0, 1, 1),
(45235, 4044, 0.0327, 1, 0, 1, 1),
(45235, 4060, 0.5239, 1, 0, 1, 1),
(45235, 4068, 0.1965, 1, 0, 1, 1),
(45235, 4070, 0.0327, 1, 0, 1, 1),
(45235, 4078, 0.0655, 1, 0, 1, 1),
(45235, 4079, 0.1637, 1, 0, 1, 1),
(45235, 4087, 0.0982, 1, 0, 1, 1),
(45235, 4300, 0.0982, 1, 0, 1, 1),
(45235, 4306, 68.6313, 1, 0, 1, 1),
(45235, 4338, 10.6, 1, 0, 1, 3),
(45235, 4416, 0.0655, 1, 0, 1, 1),
(45235, 4417, 0.0327, 1, 0, 1, 1),
(45235, 4636, 0.6221, 1, 0, 1, 1),
(45235, 4725, 0.0327, 1, 0, 1, 1),
(45235, 4729, 0.0982, 1, 0, 1, 1),
(45235, 4731, 0.0327, 1, 0, 1, 1),
(45235, 4734, 0.0982, 1, 0, 1, 1),
(45235, 4735, 0.0327, 1, 0, 1, 1),
(45235, 4738, 0.0982, 1, 0, 1, 1),
(45235, 5011, 0.1637, 1, 0, 1, 1),
(45235, 5215, 0.1965, 1, 0, 1, 1),
(45235, 6045, 0.0327, 1, 0, 1, 1),
(45235, 6411, 0.1637, 1, 0, 1, 1),
(45235, 6412, 0.0327, 1, 0, 1, 1),
(45235, 6415, 0.1637, 1, 0, 1, 1),
(45235, 6420, 0.0327, 1, 0, 1, 1),
(45235, 6422, 0.0327, 1, 0, 1, 1),
(45235, 6424, 0.0327, 1, 0, 1, 1),
(45235, 6426, 0.131, 1, 0, 1, 1),
(45235, 6432, 0.0655, 1, 0, 1, 1),
(45235, 6433, 0.0327, 1, 0, 1, 1),
(45235, 7084, 0.0327, 1, 0, 1, 1),
(45235, 7086, 0.0327, 1, 0, 1, 1),
(45235, 7090, 0.0327, 1, 0, 1, 1),
(45235, 7429, 0.0327, 1, 0, 1, 1),
(45235, 7430, 0.1637, 1, 0, 1, 1),
(45235, 7431, 0.0655, 1, 0, 1, 1),
(45235, 7440, 0.0327, 1, 0, 1, 1),
(45235, 7453, 0.0327, 1, 0, 1, 1),
(45235, 7454, 0.131, 1, 0, 1, 1),
(45235, 7455, 0.2292, 1, 0, 1, 1),
(45235, 7465, 0.0655, 1, 0, 1, 1),
(45235, 7471, 0.0655, 1, 0, 1, 1),
(45235, 7472, 0.131, 1, 0, 1, 1),
(45235, 7474, 0.2292, 1, 0, 1, 1),
(45235, 7476, 0.0982, 1, 0, 1, 1),
(45235, 7478, 0.0655, 1, 0, 1, 1),
(45235, 7479, 0.0327, 1, 0, 1, 1),
(45235, 7483, 0.3929, 1, 0, 1, 1),
(45235, 7484, 0.0982, 1, 0, 1, 1),
(45235, 7487, 0.0655, 1, 0, 1, 1),
(45235, 7488, 0.0655, 1, 0, 1, 1),
(45235, 7492, 0.0655, 1, 0, 1, 1),
(45235, 7493, 0.131, 1, 0, 1, 1),
(45235, 7556, 0.0982, 1, 0, 1, 1),
(45235, 7909, 0.1, 1, 0, 1, 1),
(45235, 8137, 0.0327, 1, 0, 1, 1),
(45235, 8156, 0.1637, 1, 0, 1, 1),
(45235, 8157, 0.0327, 1, 0, 1, 1),
(45235, 8159, 0.0655, 1, 0, 1, 1),
(45235, 8160, 0.1637, 1, 0, 1, 1),
(45235, 8161, 0.0327, 1, 0, 1, 1),
(45235, 8162, 0.1637, 1, 0, 1, 1),
(45235, 8163, 0.0327, 1, 0, 1, 1),
(45235, 8196, 0.0655, 1, 0, 1, 1),
(45235, 8387, 0.0327, 1, 0, 1, 1),
(45235, 8746, 0.4257, 1, 0, 1, 1),
(45235, 8747, 0.2947, 1, 0, 1, 1),
(45235, 8748, 0.8513, 1, 0, 1, 1),
(45235, 9285, 0.0982, 1, 0, 1, 1),
(45235, 9287, 0.0982, 1, 0, 1, 1),
(45235, 9288, 0.0327, 1, 0, 1, 1),
(45235, 9289, 0.0655, 1, 0, 1, 1),
(45235, 9290, 0.0327, 1, 0, 1, 1),
(45235, 9291, 0.0327, 1, 0, 1, 1),
(45235, 9292, 0.1965, 1, 0, 1, 1),
(45235, 9873, 0.0327, 1, 0, 1, 1),
(45235, 9874, 0.0327, 1, 0, 1, 1),
(45235, 9875, 0.0327, 1, 0, 1, 1),
(45235, 9876, 0.0982, 1, 0, 1, 1),
(45235, 9878, 0.0982, 1, 0, 1, 1),
(45235, 9879, 0.0327, 1, 0, 1, 1),
(45235, 9881, 0.2292, 1, 0, 1, 1),
(45235, 9884, 0.1965, 1, 0, 1, 1),
(45235, 9885, 0.1637, 1, 0, 1, 1),
(45235, 9886, 0.0327, 1, 0, 1, 1),
(45235, 9887, 0.0327, 1, 0, 1, 1),
(45235, 9889, 0.0982, 1, 0, 1, 1),
(45235, 9892, 0.1965, 1, 0, 1, 1),
(45235, 9893, 0.0327, 1, 0, 1, 1),
(45235, 9894, 0.0327, 1, 0, 1, 1),
(45235, 9895, 0.0982, 1, 0, 1, 1),
(45235, 9896, 0.0655, 1, 0, 1, 1),
(45235, 9897, 0.1637, 1, 0, 1, 1),
(45235, 9899, 0.0982, 1, 0, 1, 1),
(45235, 9900, 0.262, 1, 0, 1, 1),
(45235, 9901, 0.0655, 1, 0, 1, 1),
(45235, 9903, 0.0655, 1, 0, 1, 1),
(45235, 9908, 0.0327, 1, 0, 1, 1),
(45235, 9926, 0.0327, 1, 0, 1, 1),
(45235, 9929, 0.0327, 1, 0, 1, 1),
(45235, 9931, 0.0327, 1, 0, 1, 1),
(45235, 9967, 0.0327, 1, 0, 1, 1),
(45235, 9968, 0.0327, 1, 0, 1, 1),
(45235, 9969, 0.0655, 1, 0, 1, 1),
(45235, 9971, 0.0655, 1, 0, 1, 1),
(45235, 9973, 0.0327, 1, 0, 1, 1),
(45235, 10301, 0.0655, 1, 0, 1, 1),
(45235, 10312, 0.0327, 1, 0, 1, 1),
(45235, 11167, 0.0327, 1, 0, 1, 1),
(45235, 11972, 0.0655, 1, 0, 1, 1),
(45235, 11986, 0.0655, 1, 0, 1, 1),
(45235, 11987, 0.1637, 1, 0, 1, 1),
(45235, 11998, 0.0327, 1, 0, 1, 1),
(45235, 12011, 0.0655, 1, 0, 1, 1),
(45235, 12042, 0.0655, 1, 0, 1, 1),
(45235, 12808, 1.1788, 1, 0, 1, 1),
(45235, 13029, 0.0655, 1, 0, 1, 1),
(45235, 13121, 0.0655, 1, 0, 1, 1),
(45235, 15214, 0.3274, 1, 0, 1, 1),
(45235, 15233, 0.131, 1, 0, 1, 1),
(45235, 15234, 0.1965, 1, 0, 1, 1),
(45235, 15244, 0.0655, 1, 0, 1, 1),
(45235, 15251, 0.0327, 1, 0, 1, 1),
(45235, 15261, 0.4912, 1, 0, 1, 1),
(45235, 15322, 0.1637, 1, 0, 1, 1),
(45235, 15918, 0.0327, 1, 0, 1, 1),
(45235, 21940, 0.0327, 1, 0, 1, 1);

UPDATE `creature` SET `phaseMask`=5 WHERE `guid`=209399;
UPDATE `quest_template` SET `PrevQuestId`='27083' WHERE `Id` IN (27086, 27085);
UPDATE `quest_template` SET `PrevQuestId`='27087' WHERE `Id`=27089;
UPDATE `quest_template` SET `PrevQuestId`='27090' WHERE `Id`=27144;
UPDATE `quest_template` SET `PrevQuestId`='27083' WHERE `Id`=27084;

DELETE FROM `conditions` WHERE `SourceEntry` = '27087' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 27087, 27085, 0),
(20, 8, 27087, 27086, 0),
(20, 8, 27087, 27084, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '27087' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 27087, 27085, 0),
(19, 8, 27087, 27086, 0),
(19, 8, 27087, 27084, 0);

SET @CGUID := 400770;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+14;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 44329, 0, 1, 1, 0, 1, 1561.77, -1472.04, 68.3983, 4.53121, 120, 0, 0, 290, 1007, 0, 0, 34816, 0),
(@CGUID+1, 44329, 0, 1, 1, 0, 1, 1554.43, -1470.14, 68.3969, 4.27989, 120, 0, 0, 290, 1007, 0, 0, 34816, 0),
(@CGUID+2, 44329, 0, 1, 1, 0, 1, 1554.4, -1492.29, 67.2734, 4.45268, 120, 0, 0, 290, 1007, 0, 0, 34816, 0),
(@CGUID+3, 44329, 0, 1, 1, 0, 1, 1545.4, -1483.42, 68.3919, 5.50903, 120, 0, 0, 303, 1067, 0, 0, 34816, 0),
(@CGUID+4, 44329, 0, 1, 1, 0, 1, 1540.16, -1474.57, 68.3265, 5.1988, 120, 0, 0, 303, 1067, 0, 0, 34816, 0),
(@CGUID+5, 44329, 0, 1, 1, 0, 1, 1540.14, -1463.67, 68.3929, 3.79687, 120, 0, 0, 303, 1067, 0, 0, 34816, 0),
(@CGUID+6, 44329, 0, 1, 1, 0, 1, 1546.33, -1453.69, 68.3127, 3.73403, 120, 0, 0, 303, 1067, 0, 0, 34816, 0),
(@CGUID+7, 44329, 0, 1, 1, 0, 1, 1558.9, -1450.16, 68.316, 3.43558, 120, 0, 0, 290, 1007, 0, 0, 34816, 0),
(@CGUID+8, 44329, 0, 1, 1, 0, 1, 1572.54, -1453.28, 68.3918, 1.99437, 120, 0, 0, 303, 1067, 0, 0, 34816, 0),
(@CGUID+9, 44329, 0, 1, 1, 0, 1, 1577.65, -1460.82, 68.2777, 2.10825, 120, 0, 0, 290, 1007, 0, 0, 34816, 0),
(@CGUID+10, 44329, 0, 1, 1, 0, 1, 1576.31, -1476.16, 68.3929, 1.33464, 120, 0, 0, 303, 1067, 0, 0, 34816, 0),
(@CGUID+11, 44329, 0, 1, 1, 0, 1, 1571.82, -1482.84, 68.3165, 0.678829, 120, 0, 0, 290, 1007, 0, 0, 34816, 0),
(@CGUID+12, 44466, 0, 1, 1, 0, 1, 1875.35, -1332.72, 59.9942, 3.15966, 120, 0, 0, 3048, 0, 0, 0, 0, 0),
(@CGUID+13, 44466, 0, 1, 2, 0, 1, 1540.15, -1692.23, 57.4216, 1.65265, 300, 0, 0, 3048, 0, 0, 0, 0, 0),
(@CGUID+14, 44452, 0, 1, 2, 0, 1, 1544.23, -1610.82, 64.6275, 3.37872, 300, 0, 0, 1549800, 89080, 0, 0, 0, 0);

UPDATE `creature_template` SET `mindmg`=45, `maxdmg`=68, `attackpower`=15, `dmg_multiplier`=1.5 WHERE `entry`=44317;

-- The Ravenian
SET @ENTRY := 44317;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,4000,4000,11,15550,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Trample"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,2000,6000,6000,11,40504,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Cleave");

UPDATE `creature_template` SET `faction_A`=2161, `faction_H`=2161 WHERE `entry`=44326;
UPDATE `quest_template` SET `Flags`=0, `SpecialFlags`=2 WHERE `Id`=26930;
UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry` IN (1835, 1831, 10605, 45165, 45129);

DELETE FROM `areatrigger_scripts` WHERE `entry` = '6213';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6213, 'at_charred_outpost');

UPDATE `quest_template` SET `Method`=2, `PrevQuestId`='26978' WHERE `Id`=26936;

-- Andorhal Deathguard
SET @ENTRY := 44326;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,10000,10000,11,85524,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Might of the Forsaken");

DELETE FROM `creature_loot_template` WHERE `item` = '60679';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(1815, 60679, -100, 1, 0, 1, 1);

DELETE FROM `gameobject_loot_template` WHERE `item` = '60679';
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(31797, 60679, -100, 1, 0, 1, 1);

-- Diseased Black Bear
SET @ENTRY := 1815;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,60,0,6000,9000,12000,18000,11,3427,32,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"Diseased Black Bear - In Combat - Cast Infected Wound"),
(@ENTRY,@SOURCETYPE,1,0,6,0,100,0,0,0,0,0,11,83105,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Cast Latent Disease");

UPDATE `creature_template` SET `mindmg`=45, `maxdmg`=68, `attackpower`=17 WHERE `entry` IN (44432, 44474, 44476, 44433);

-- Alliance Fox Hunter
SET @ENTRY := 44432;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,79721,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Explosive Shot"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,4000,4000,11,85710,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shoot"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,3000,3000,6000,6000,11,85710,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Explosive Shot"),
(@ENTRY,@SOURCETYPE,3,0,1,0,100,0,5000,5000,5000,5000,45,0,1,0,0,0,0,11,44476,50,0,0.0,0.0,0.0,0.0,"OOC - Set Data 1 to Mastiff");

-- Whitetail Fox
SET @ENTRY := 44474;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,85690,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Fox's Cunning"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,2000,10000,10000,11,85691,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Piercing Howl");

-- Bullmastiff
SET @ENTRY := 44476;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,61684,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Dash"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,4000,4000,11,17253,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Bite"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,2000,2000,9000,9000,11,17253,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Lock Jaw"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,1,0,0,29,3,0,0,0,0,0,11,44432,50,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Follow Hunter");

UPDATE `quest_template` SET `PrevQuestId`='26936' WHERE `Id`=26979;
UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=26937;

-- Alliance Laborer
SET @ENTRY := 44433;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,4000,4000,11,85691,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Boot Toss");

DELETE FROM `spell_script_names` WHERE `spell_id` = '83176';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(83176, 'spell_place_dithers_drum');

UPDATE `creature` SET `phaseMask`=2 WHERE `guid` IN (209418, 209309, 209391, 209384, 209417, 209386, 209382);

DELETE FROM `spell_area` WHERE `spell` = '84016' AND `quest_start` = '26937';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(84016, 28, 26937, 26937, 1, 10);

DELETE FROM `spell_area` WHERE `spell` IN (84149, 90161) AND `quest_start` = '26938';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(84149, 28, 26938, 26938, 1, 10),
(90161, 28, 26938, 26938, 1, 10);

DELETE FROM `spell_area` WHERE `spell` = '65141' AND `quest_start` = '26938';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(65141, 28, 26938, 26938, 1, 10);

UPDATE `creature_template` SET `ScriptName`='npc_enthralled_valkyr', `HoverHeight`=2.2 WHERE `entry`=44491;
UPDATE `creature_template` SET `ScriptName`='npc_enthralled_valkyr_final', `HoverHeight`=2.0 WHERE `entry`=44492;

DELETE FROM `creature_template_addon` WHERE `entry` IN (44491, 45080, 44492);
INSERT INTO `creature_template_addon` (`entry`, `bytes1`) VALUES
(44491, 50397184),
(45080, 50397184),
(44492, 50397184);

UPDATE `creature_template` SET `VehicleId`=1069, `spell1`=84143, `spell2`=84155, `spell3`=84155, `unit_class`=8, `HoverHeight`=2.3 WHERE `entry`=44491;
UPDATE `creature_template` SET `spell1`=15968, `spell2`=83381, `VehicleId`=1069, `unit_class`=8, `HoverHeight`=1 WHERE `entry`=45080;
UPDATE `creature` SET `phaseMask`=1, `spawntimesecs`=60, `spawndist`=15, `MovementType`=1 WHERE `id`=45085;
UPDATE `creature` SET `phaseMask`=2, `spawntimesecs`=60 WHERE `guid`=772984;

UPDATE `creature` SET `phaseMask`=2 WHERE `id` IN (45050, 45049, 45085);

-- Opengut Behemoth
SET @ENTRY := 45098;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,10000,10000,11,50335,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Scourge Hook"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,4000,4000,11,40504,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Cleave");

UPDATE `creature_template` SET `mindmg`=45, `maxdmg`=68, `attackpower`=37, `dmg_multiplier`=3.5, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=45098;

-- Opengut Behemoth
SET @ENTRY := 45098;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,10000,10000,11,50335,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Scourge Hook"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,4000,4000,11,40504,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Cleave"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,5000,5000,5000,5000,49,0,0,0,0,0,0,11,45080,20,0,0.0,0.0,0.0,0.0,"IC - Attack Val'Kyr");

UPDATE `creature` SET `phaseMask`=3 WHERE `guid`=400782;
UPDATE `creature` SET `phaseMask`=3 WHERE `id` IN (1835, 1831, 10605);
UPDATE `quest_template` SET `PrevQuestId`='27055' WHERE `Id` IN (27197, 27083);
UPDATE `creature` SET `phaseMask`=7 WHERE `guid` IN (209892, 209680);
UPDATE `creature` SET `phaseMask`=2 WHERE `guid`=209967;
UPDATE `creature_template` SET `faction_A`=2161, `faction_H`=2161, `flags_extra`=32768, `unit_flags2`=33556480 WHERE `entry` IN (44331, 44449);
UPDATE `creature` SET `phaseMask`=4 WHERE `guid`=210100;
UPDATE `creature` SET `phaseMask`=4 WHERE `id`=44955;
UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=209891;
UPDATE `creature` SET `phaseMask`=2 WHERE `id` IN (44944, 44946);
UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=209968;
UPDATE `creature_template` SET `unit_flags`=512 WHERE `entry` IN (44462, 46004);
UPDATE `creature_template` SET `mindmg`=79, `maxdmg`=72, `attackpower`=18, `dmg_multiplier`=1.1, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=44944;
UPDATE `creature_template` SET `mindmg`=79, `maxdmg`=72, `attackpower`=18, `dmg_multiplier`=1.5, `baseattacktime`=2000, `rangeattacktime`=2000, `Health_mod`=4 WHERE `entry`=44946;

-- Provincial Minuteman
SET @ENTRY := 44944;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,10000,10000,11,85681,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Boot Toss");

-- Opengut Behemoth
SET @ENTRY := 44946;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,9500,9500,11,50335,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Scourge Hook"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,2000,4000,4000,11,50335,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Cleave"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,2000,2000,5000,5000,49,0,0,0,0,0,0,11,44944,50,0,0.0,0.0,0.0,0.0,"OOC - Attack Farmers");

DELETE FROM `creature` WHERE `id`=44955;
UPDATE `creature_template` SET `InhabitType`=4, `VehicleId`=562, `ScriptName`='npc_summoned_ebon_gargoyle', `faction_A`=2161, `faction_H`=2161, `unit_flags`=0 WHERE `entry`=44955;

DELETE FROM `spell_area` WHERE `spell` = '65141' AND `quest_start` = '27083';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(65141, 193, 27083, 27087, 0, 0, 2, 1, 66, 11);

UPDATE `creature` SET `phaseMask`=4 WHERE `guid`=209398;

DELETE FROM `spell_area` WHERE `spell` = '84198' AND `quest_start` = '27089';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(84198, 193, 27089, 27089, 1, 10);

DELETE FROM `spell_area` WHERE `spell` IN (55858, 49416) AND `quest_start` = '27087';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(55858, 193, 27087, 27144, 0, 0, 2, 1, 64, 11),
(49416, 193, 27087, 27144, 0, 0, 2, 1, 64, 11);

UPDATE `creature_template` SET `unit_class`=8 WHERE `entry`=44492;

-- Lurid
SET @ENTRY := 45129;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,3000,3000,3000,3000,33,44453,0,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"Update - Quest Credit"),
(@ENTRY,@SOURCETYPE,1,0,20,0,100,0,27089,0,0,0,85,84940,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Reward - Despawn All Summons");

UPDATE `creature_template` SET `VehicleId`=1055, `InhabitType`=4 WHERE `entry`=45113;
UPDATE `creature_addon` SET `auras`='' WHERE `auras`=54913;
UPDATE `creature_template_addon` SET `auras`='' WHERE `auras`=54913;
UPDATE `creature_template_addon` SET `auras`='' WHERE `auras`=0;

DELETE FROM `spell_target_position` WHERE `id` = '84211';
INSERT INTO `spell_target_position` (`id`, `effIndex`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(84211, 0, 0, 1540.53, -1690.08, 59.4, 3.22);

DELETE FROM `creature_text` WHERE `entry`=45111;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45111,0,0,'Koltira! Your queen summons you!',14,0,100,0,0,0,'Comment'),
(45111,1,0,'Enough of this insolence. Do you think that I\'m blind to everything that goes on outside of the Undercity?',12,0,100,0,0,0,'Comment'),
(45111,2,0,'No thanks to you. Andorhal should have been ours days ago, when we defeated the Scourge.',12,0,100,0,0,0,'Comment'),
(45111,3,0,'I know your secret, Koltira. I\'m aware of your friendship with the Alliance death knight, Thassarian.',0,0,100,0,0,0,'Comment'),
(45111,4,0,'Arthas clearly failed when he created his death knights. You are still weak.',12,0,100,0,0,0,'Comment'),
(45111,5,0,'Fortunately, I have agents that can help you... erase this weakness. Beneath the Undercity you go.',12,0,100,0,0,0,'Comment'),
(45111,6,0,'Shh... quiet, death knight. When I\'m finished with you, your fear will be gone.',12,0,100,0,0,0,'Comment'),
(45111,7,0,'You can thank me later.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=45112;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(45112,0,0,'Your highness, I deliver to you... Andorhal.',12,0,100,0,0,0,'Comment'),
(45112,1,0,'I... your majesty, we were victorious!',12,0,100,0,0,0,'Comment'),
(45112,2,0,'Y... your majesty...',12,0,100,0,0,0,'Comment'),
(45112,3,0,'NO!',14,0,100,0,0,0,'Comment');

DELETE FROM `waypoints` WHERE `entry` = '45113';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(45113, 1, 1539.32, -1684.92, 59.33, 'Reckoning Camera WP'),
(45113, 2, 1541.48, -1685.35, 58.47, 'Reckoning Camera WP');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '84252';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(84252, -49416, 0, 'Temporary Remove Quest Invisibility Detection 1');

DELETE FROM `creature_template_addon` WHERE `entry` IN (45114, 45112, 45111, 45113);
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(45114, '60191'),
(45113, '60191'),
(45112, '60191'),
(45111, '60191');

DELETE FROM `spell_area` WHERE `spell` = '60191';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(60191, 193, 27144, 27144, 1, 8);

-- Reckoning Event Camera
SET @ENTRY := 45113;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,60,1,100,1,1500,1500,1500,1500,11,84219,0,0,0,0,0,11,45112,80,0,0.0,0.0,0.0,0.0,"Update - Cast Channel Koltira"),
(@ENTRY,@SOURCETYPE,2,0,60,1,100,1,1500,1500,1500,1500,11,84219,0,0,0,0,0,11,45112,80,0,0.0,0.0,0.0,0.0,"Update (1.5 secs) - Cast Channel Koltira"),
(@ENTRY,@SOURCETYPE,3,0,60,1,100,1,1500,1500,1500,1500,59,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (1 secs) - Set Walk"),
(@ENTRY,@SOURCETYPE,4,0,60,1,100,1,9000,9000,9000,9000,53,1,45113,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (5 secs) - Start WP"),
(@ENTRY,@SOURCETYPE,5,0,60,1,100,1,67500,67500,67500,67500,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (67.5 Secs) - Remove Passenger");

-- Koltira Deathweaver
SET @ENTRY := 45112;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,69,0,0,0,0,0,0,8,0,0,0,1540.05,-1688.83,57.39,4.76,"On Get Data 1 - Move To Pos"),
(@ENTRY,@SOURCETYPE,1,0,34,0,100,0,8,0,0,0,17,428,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Set Kneel"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,1,0,0,1,0,7000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,45112,0,0,45,0,1,0,0,0,0,11,45111,50,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Sylvanas"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,2,0,0,1,1,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 1"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,1,45112,0,0,45,0,2,0,0,0,0,11,45111,50,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 2 to Sylvanas"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,0,0,3,0,0,1,2,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 2"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,2,45112,0,0,45,0,3,0,0,0,0,11,45111,50,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 3 to Sylvanas"),
(@ENTRY,@SOURCETYPE,8,0,38,0,100,0,0,4,0,0,1,3,2500,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 3"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,3,45112,0,0,45,0,1,0,0,0,0,11,45114,30,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 1 to Portal"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,3,45112,0,0,17,473,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Strangulate"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,0,3,45112,0,0,45,0,4,0,0,0,0,11,45111,35,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 4 to Sylvanas");

-- Lady Sylvanas Windrunner
SET @ENTRY := 45111;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,1,0,3500,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,45111,0,0,45,0,1,0,0,0,0,11,45112,80,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Koltira"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,1,0,0,1,1,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,45111,0,0,45,0,2,0,0,0,0,11,45112,80,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 2 to Koltira"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,2,0,0,1,2,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 2"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,2,45111,0,0,1,3,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,3,45111,0,0,45,0,3,0,0,0,0,11,45112,80,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 3 to Koltira"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,0,0,3,0,0,1,4,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 4"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,4,45111,0,0,1,5,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Talk 5"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,5,45111,0,0,45,0,4,0,0,0,0,11,45112,80,0,0.0,0.0,0.0,0.0,"After Talk 5 - Set Data 4 to Koltira"),
(@ENTRY,@SOURCETYPE,10,0,38,0,100,0,0,4,0,0,1,6,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 6"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,0,6,45111,0,0,1,7,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 6 - Talk 7"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,0,4,45111,0,0,11,84218,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Summon Portal");

-- Portal to Undercity
SET @ENTRY := 45114;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,11,76489,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Cast Chains");

UPDATE `creature` SET `phaseMask`=32768 WHERE `guid` IN (209448, 209362, 209449, 209560);
UPDATE `creature_template` SET `Health_mod`=15, `Armor_mod`=10 WHERE `entry` IN (44326, 44332, 44328);
UPDATE `creature_template` SET `unit_flags`=512 WHERE `entry`=1852;
UPDATE `creature` SET `phaseMask`=32768 WHERE `id`=44447;
UPDATE `creature` SET `spawntimesecs`=60 WHERE `id` IN (44315, 44316);
DELETE FROM `creature` WHERE `guid` IN (209638, 209647);
UPDATE `creature_template` SET `unit_flags`=512 WHERE `entry`=44466;

-- Lady Sylvanas Windrunner
SET @ENTRY := 44451;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,27144,0,0,0,85,84252,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - The Reckoning (Force Phase 8)"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,27144,0,0,0,85,84211,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - The Reckoning (Summon Camera)"),
(@ENTRY,@SOURCETYPE,2,0,19,0,100,0,27144,0,0,0,85,84208,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - The Reckoning (Summon Sylvanas)"),
(@ENTRY,@SOURCETYPE,3,0,19,0,100,0,27144,0,0,0,85,84209,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - The Reckoning (Summon Koltira)");