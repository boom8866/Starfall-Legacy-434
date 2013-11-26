-- Lashtail Hatchling
SET @ENTRY := 42736;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,11,79662,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Eat"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Passive"),
(@ENTRY,@SOURCETYPE,3,0,8,0,100,0,79661,1,0,0,33,42742,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit (H - Basilisk)"),
(@ENTRY,@SOURCETYPE,4,5,38,0,100,0,0,2,0,0,11,79706,2,0,0,0,0,11,42736,15,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Cast Dig Visual"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,11,82328,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Fetish in Mouth (A)"),
(@ENTRY,@SOURCETYPE,6,0,8,0,100,0,79702,1,0,0,11,79714,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit (H)"),
(@ENTRY,@SOURCETYPE,7,0,8,0,100,0,82328,1,0,0,45,0,2,0,0,0,0,11,43977,30,0,0.0,0.0,0.0,0.0,"On Spellhit - Set Data 2 to Tkashi Fetish"),
(@ENTRY,@SOURCETYPE,8,11,38,0,100,0,0,3,0,0,11,79706,2,0,0,0,0,11,42772,15,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Cast Dig Visual"),
(@ENTRY,@SOURCETYPE,9,0,8,0,100,0,82328,1,0,0,11,82324,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit (A)"),
(@ENTRY,@SOURCETYPE,10,0,8,0,100,0,79714,1,0,0,45,0,3,0,0,0,0,11,42772,30,0,0.0,0.0,0.0,0.0,"On Spellhit - Set Data 3 to Zuuldaian Fetish"),
(@ENTRY,@SOURCETYPE,11,0,61,0,100,0,0,0,0,0,11,79702,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Fetish in Mouth (H)"),
(@ENTRY,@SOURCETYPE,12,0,38,0,100,0,0,4,0,0,11,79662,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Eat"),
(@ENTRY,@SOURCETYPE,13,0,8,0,100,0,79661,1,0,0,33,42742,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit (A - Murloc)"),
(@ENTRY,@SOURCETYPE,14,0,38,0,100,0,0,5,0,0,11,79678,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Troll Skull in Mouth"),
(@ENTRY,@SOURCETYPE,15,0,8,0,100,0,79678,1,0,0,56,58201,1,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Give Skull to Owner"),
(@ENTRY,@SOURCETYPE,16,0,60,0,100,0,10000,10000,10000,10000,28,79678,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Remove Skull");

-- Crystal Spine Basilisk
SET @ENTRY := 689;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,75,0,5000,5000,16000,16000,11,3635,0,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"Crystal Spine Basilisk - In Combat - Cast Crystal Gaze"),
(@ENTRY,@SOURCETYPE,1,0,6,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,42736,50,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Hatchling");

-- Murkgill Oracle
SET @ENTRY := 4459;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,45,0,4,0,0,0,0,11,42736,50,0,0.0,0.0,0.0,0.0,"On Death - Set Data 4 to Lashtail Hatchling");

-- Murkgill Forager
SET @ENTRY := 4457;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,2000,19900,30000,11,13443,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Murkgill Forager - In Combat - Cast Rend"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2600,2600,3700,9100,11,744,32,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Murkgill Forager - In Combat - Cast Poison"),
(@ENTRY,@SOURCETYPE,2,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Murkgill Forager - At 15% HP - Flee For Assist"),
(@ENTRY,@SOURCETYPE,3,0,6,0,100,0,0,0,0,0,45,0,4,0,0,0,0,11,42736,50,0,0.0,0.0,0.0,0.0,"On Death - Set Data 4 to Lashtail Hatchling");

-- Skullsplitter Axe Thrower
SET @ENTRY := 696;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,45,0,5,0,0,0,0,11,42736,65,0,0.0,0.0,0.0,0.0,"On Death - Set Data 5 to Lashtail Hatchling");

-- Skullsplitter Mystic
SET @ENTRY := 780;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,45,0,5,0,0,0,0,11,42736,65,0,0.0,0.0,0.0,0.0,"On Death - Set Data 5 to Lashtail Hatchling");

-- Skullsplitter Warrior
SET @ENTRY := 667;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,45,0,5,0,0,0,0,11,42736,65,0,0.0,0.0,0.0,0.0,"On Death - Set Data 5 to Lashtail Hatchling");

DELETE FROM `creature_loot_template` WHERE `item` = '58201';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(780, 58201, -3.42, 1, 0, 1, 1),
(696, 58201, -3.173, 1, 0, 1, 1),
(667, 58201, -3.295, 1, 0, 1, 1);

-- Murkgill Hunter
SET @ENTRY := 4458;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,45,0,4,0,0,0,0,11,42736,50,0,0.0,0.0,0.0,0.0,"On Death - Set Data 4 to Lashtail Hatchling");

-- Murkgill Coldbringer
SET @ENTRY := 4460;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,45,0,4,0,0,0,0,11,42736,50,0,0.0,0.0,0.0,0.0,"On Death - Set Data 4 to Lashtail Hatchling");

-- Murkgill Warrior
SET @ENTRY := 4461;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,2,0,100,1,0,15,0,0,25,1,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Murkgill Warrior - At 15% HP - Flee For Assist"),
(@ENTRY,@SOURCETYPE,1,0,6,0,100,0,0,0,0,0,45,0,4,0,0,0,0,11,42736,50,0,0.0,0.0,0.0,0.0,"On Death - Set Data 4 to Lashtail Hatchling");

UPDATE `creature` SET `phaseMask`=1 AND `spawntimesecs`=60 WHERE `guid` IN (775045, 775046, 775047);

DELETE FROM `creature_text` WHERE `entry` IN (43886, 43884, 43885);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(43886,0,0,'Freedom! Sweet, sweet freedom!',12,0,100,0,0,0,'Comment'),
(43884,0,0,'Woo hoo',12,0,100,0,0,0,'Comment'),
(43885,0,0,'Thank you! I don\'t know how much longer we would have survived.',12,0,100,0,0,0,'Comment'),
(43885,1,0,'That cage was stifling my magic',12,0,100,0,0,0,'Comment'),
(43885,2,0,'If you don\'t mind, I\'m going to teleport us back to the Rebel Camp. We\'ll thank you in person later.',12,0,100,0,0,0,'Comment');

DELETE FROM `spell_area` WHERE `quest_end` = '26736';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(82210, 101, 26736, 26736, 1, 10, 10),
(82225, 99, 26736, 26736, 1, 66, 66);

-- Kurzen Cage
SET @ENTRY := 204828;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,0,25,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Prisoneers");

-- Osborn Obnoticus
SET @ENTRY := 43884;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,22,2,0,0,0,0,0,1,0,0,0,-11570.7,-575.14,33.68,4.77,"On Get Data 1 - Set Phase 2"),
(@ENTRY,@SOURCETYPE,1,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Run"),
(@ENTRY,@SOURCETYPE,2,5,60,2,100,1,1500,1500,1500,1500,69,0,0,0,0,0,0,8,0,0,0,-11570.9,-573.45,33.68,4.73,"Update (1.5 secs) - Move Out of the Cage"),
(@ENTRY,@SOURCETYPE,3,0,60,2,100,1,7000,7000,7000,7000,1,0,5000,0,0,0,0,1,0,0,0,-11572.2,-757.15,33.68,5.6,"Update (7 secs) - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,38,2,100,0,0,2,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Force Despawn 1 sec"),
(@ENTRY,@SOURCETYPE,5,0,61,2,100,0,0,0,0,0,33,43919,0,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"Link - Killer Monster");

-- Emerine Junis
SET @ENTRY := 43885;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,22,2,0,0,0,0,0,1,0,0,0,-11570.7,-575.14,33.68,4.77,"On Get Data 1 - Set Phase 2"),
(@ENTRY,@SOURCETYPE,1,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Run"),
(@ENTRY,@SOURCETYPE,2,9,60,2,100,1,1500,1500,1500,1500,69,0,0,0,0,0,0,8,0,0,0,-11569.8,-574.89,33.68,4.26,"Update (1.5 secs) - Move Out of the Cage"),
(@ENTRY,@SOURCETYPE,3,0,60,2,100,1,5000,5000,5000,5000,1,0,5000,0,0,0,0,1,0,0,0,-11572.2,-757.15,33.68,5.6,"Update (5 secs) - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,52,2,100,0,0,43885,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,5,0,52,2,100,0,1,43885,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,6,7,52,2,100,0,2,43885,0,0,11,52096,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Cast Teleport"),
(@ENTRY,@SOURCETYPE,7,8,61,2,100,0,0,0,0,0,45,0,2,0,0,0,0,11,0,20,0,0.0,0.0,0.0,0.0,"Link - Set Data 2 to Company"),
(@ENTRY,@SOURCETYPE,8,0,61,2,100,0,0,0,0,0,41,2000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn 2 secs"),
(@ENTRY,@SOURCETYPE,9,0,61,2,100,0,0,0,0,0,33,43920,0,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"Link - Killed Monster"),
(@ENTRY,@SOURCETYPE,10,0,54,0,100,0,0,0,0,0,28,49414,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Remove Quest Invisibility");

-- Berrin Burnquill
SET @ENTRY := 43886;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,22,2,0,0,0,0,0,1,0,0,0,-11570.7,-575.14,33.68,4.77,"On Get Data 1 - Set Phase 2"),
(@ENTRY,@SOURCETYPE,1,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set Run"),
(@ENTRY,@SOURCETYPE,2,5,60,2,100,1,1500,1500,1500,1500,69,0,0,0,0,0,0,8,0,0,0,-11572.2,-575.15,33.68,5.6,"Update (1.5 secs) - Move Out of the Cage"),
(@ENTRY,@SOURCETYPE,3,0,60,2,100,1,3000,3000,3000,3000,1,0,5000,0,0,0,0,1,0,0,0,-11572.2,-757.15,33.68,5.6,"Update (3 secs) - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,38,2,100,0,0,2,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Force Despawn 1 sec"),
(@ENTRY,@SOURCETYPE,5,0,61,2,100,0,0,0,0,0,33,43921,0,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"Link - Killed Monster");

SET @CGUID := 798490;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+2;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 43884, 0, 1, 1, 0, 1, -11323.1, -210.134, 76.0911, 2.5747, 300, 0, 0, 773, 811, 0, 0, 0, 0),
(@CGUID+1, 43886, 0, 1, 1, 0, 1, -11306.3, -190.011, 75.4834, 3.65844, 300, 0, 0, 773, 811, 0, 0, 0, 0),
(@CGUID+2, 43885, 0, 1, 1, 0, 1, -11301.7, -209.594, 76.2104, 1.98193, 300, 0, 0, 773, 811, 0, 0, 0, 0);

DELETE FROM `creature_template_addon` WHERE `entry`=938;
UPDATE `creature_template` SET `flags_extra`=0, `InhabitType`=3 WHERE `entry` = '687';
DELETE FROM `creature_equip_template` WHERE `entry` IN (687,689);

DELETE FROM `creature_loot_template` WHERE `item` IN (60213, 60274, 60271, 60270, 60272, 57990);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(689, 60213, -55.9409, 1, 0, 1, 1),
(4461, 60274, -30.9862, 1, 0, 1, 1),
(4457, 60274, -31.474, 1, 0, 1, 1),
(4458, 60274, -31.159, 1, 0, 1, 1),
(4459, 60274, -30.0618, 1, 0, 1, 1),
(4460, 60274, -29.0415, 1, 0, 1, 1),
(702, 60270, -11.7151, 1, 0, 1, 1),
(702, 60271, -11.7337, 1, 0, 1, 1),
(702, 60272, -11.7408, 1, 0, 1, 1),
(43050, 57990, -1.7568, 1, 0, 1, 1),
(43910, 57990, -0.0297, 1, 0, 1, 1),
(43911, 57990, -0.0131, 1, 0, 1, 1),
(44112, 57990, -0.4484, 1, 0, 1, 1),
(905, 57990, -9.6507, 1, 0, 1, 1),
(1150, 57990, -8.7156, 1, 0, 1, 1),
(681, 57990, -3.5238, 1, 0, 1, 1),
(688, 57990, -1.996, 1, 0, 1, 1),
(875, 57990, -0.4149, 1, 0, 1, 1),
(683, 57990, -0.6078, 1, 0, 1, 1),
(676, 57990, -0.1931, 1, 0, 1, 1),
(702, 57990, -0.3387, 1, 0, 1, 1),
(1493, 57990, -0.1022, 1, 0, 1, 1),
(871, 57990, -0.0535, 1, 0, 1, 1),
(1094, 57990, -0.1577, 1, 0, 1, 1),
(937, 57990, -0.0826, 1, 0, 1, 1),
(682, 57990, -0.0741, 1, 0, 1, 1),
(940, 57990, -0.0925, 1, 0, 1, 1),
(685, 57990, -0.1009, 1, 0, 1, 1),
(1062, 57990, -0.1276, 1, 0, 1, 1),
(1142, 57990, -0.0862, 1, 0, 1, 1),
(709, 57990, -0.0668, 1, 0, 1, 1),
(696, 57990, -0.0638, 1, 0, 1, 1),
(667, 57990, -0.0443, 1, 0, 1, 1),
(697, 57990, -0.0636, 1, 0, 1, 1),
(736, 57990, -0.0708, 1, 0, 1, 1),
(595, 57990, -0.0782, 1, 0, 1, 1),
(1563, 57990, -0.0238, 1, 0, 1, 1),
(4460, 57990, -0.0392, 1, 0, 1, 1),
(686, 57990, -0.0591, 1, 0, 1, 1),
(1085, 57990, -0.0411, 1, 0, 1, 1),
(1492, 57990, -0.0304, 1, 0, 1, 1),
(674, 57990, -0.0369, 1, 0, 1, 1),
(1061, 57990, -0.0423, 1, 0, 1, 1),
(699, 57990, -0.0591, 1, 0, 1, 1),
(943, 57990, -0.0537, 1, 0, 1, 1),
(731, 57990, -0.0305, 1, 0, 1, 1),
(587, 57990, -0.0528, 1, 0, 1, 1),
(694, 57990, -0.0387, 1, 0, 1, 1),
(938, 57990, -0.0708, 1, 0, 1, 1),
(1096, 57990, -0.0483, 1, 0, 1, 1),
(588, 57990, -0.0268, 1, 0, 1, 1),
(689, 57990, -0.0369, 1, 0, 1, 1),
(1152, 57990, -0.0219, 1, 0, 1, 1),
(2635, 57990, -0.0169, 1, 0, 1, 1),
(941, 57990, -0.0406, 1, 0, 1, 1),
(1561, 57990, -0.0147, 1, 0, 1, 1),
(783, 57990, -0.0102, 1, 0, 1, 1),
(691, 57990, -0.0182, 1, 0, 1, 1),
(701, 57990, -0.0257, 1, 0, 1, 1),
(687, 57990, -0.0136, 1, 0, 1, 1),
(782, 57990, -0.0071, 1, 0, 1, 1),
(660, 57990, -0.0135, 1, 0, 1, 1),
(710, 57990, -0.0069, 1, 0, 1, 1),
(42858, 57990, -0.007, 1, 0, 1, 1),
(1144, 57990, -0.0952, 1, 0, 1, 1),
(684, 57990, -0.0102, 1, 0, 1, 1),
(729, 57990, -0.0173, 1, 0, 1, 1),
(730, 57990, -0.0057, 1, 0, 1, 1),
(671, 57990, -0.0056, 1, 0, 1, 1),
(670, 57990, -0.0166, 1, 0, 1, 1),
(1562, 57990, -0.0039, 1, 0, 1, 1),
(669, 57990, -0.0071, 1, 0, 1, 1),
(597, 57990, -0.0034, 1, 0, 1, 1),
(1907, 57990, -0.0071, 1, 0, 1, 1),
(780, 57990, -0.042, 1, 0, 1, 1),
(4457, 57990, -0.0049, 1, 0, 1, 1),
(4461, 57990, -0.0135, 1, 0, 1, 1),
(4458, 57990, -0.0039, 1, 0, 1, 1),
(2522, 57990, -0.0018, 1, 0, 1, 1),
(772, 57990, -0.0016, 1, 0, 1, 1),
(1488, 57990, -0.0015, 1, 0, 1, 1),
(43223, 57990, -0.0059, 1, 0, 1, 1),
(43849, 57990, -0.4762, 1, 0, 1, 1),
(44113, 57990, -0.0064, 1, 0, 1, 1),
(51661, 57990, -0.5172, 1, 0, 1, 1),
(51662, 57990, -0.0461, 1, 0, 1, 1),
(51663, 57990, -0.1861, 1, 0, 1, 1),
(52224, 57990, -0.0006, 1, 0, 1, 1),
(675, 57990, -0.0705, 1, 0, 1, 1),
(679, 57990, -0.0068, 1, 0, 1, 1),
(728, 57990, -0.0177, 1, 0, 1, 1),
(818, 57990, -0.0076, 1, 0, 1, 1),
(879, 57990, -0.054, 1, 0, 1, 1),
(921, 57990, -0.0436, 1, 0, 1, 1),
(939, 57990, -0.0229, 1, 0, 1, 1),
(976, 57990, -0.0222, 1, 0, 1, 1),
(977, 57990, -0.0686, 1, 0, 1, 1),
(1097, 57990, -0.0483, 1, 0, 1, 1),
(1489, 57990, -0.0048, 1, 0, 1, 1),
(1490, 57990, -0.0036, 1, 0, 1, 1),
(1550, 57990, -0.0067, 1, 0, 1, 1),
(1551, 57990, -0.001, 1, 0, 1, 1),
(1557, 57990, -0.003, 1, 0, 1, 1),
(1564, 57990, -0.004, 1, 0, 1, 1),
(1565, 57990, -0.0027, 1, 0, 1, 1),
(1713, 57990, -0.0045, 1, 0, 1, 1),
(4260, 57990, -0.1193, 1, 0, 1, 1),
(4459, 57990, -0.01, 1, 0, 1, 1),
(4723, 57990, -0.022, 1, 0, 1, 1),
(11383, 57990, -0.0932, 1, 0, 1, 1),
(14487, 57990, -0.0471, 1, 0, 1, 1),
(14488, 57990, -0.177, 1, 0, 1, 1),
(14491, 57990, -0.056, 1, 0, 1, 1),
(14492, 57990, -0.0615, 1, 0, 1, 1);

UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry` IN (43977, 42772);
UPDATE `creature` SET `spawntimesecs`=60 WHERE `id`=43977;

-- Tkashi Fetish
SET @ENTRY := 43977;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,3500,3500,3500,3500,45,0,2,0,0,0,0,11,42736,15,0,0.0,0.0,0.0,0.0,"Update - Set Data 2 to Lashtail Hatchling"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,2,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Despawn");

-- Zuuldaian Fetish
SET @ENTRY := 42772;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,3500,3500,3500,3500,45,0,3,0,0,0,0,11,42736,15,0,0.0,0.0,0.0,0.0,"Update - Set Data 3 to Lashtail Hatchling"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,3,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Despawn");

UPDATE `quest_template` SET `Flags`=10 WHERE `Id` IN (194, 195, 196, 197, 190, 191, 192, 193, 185, 186, 187, 188);

DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (11785, 11661);
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(11785, 0, 'I am ready for the Mind Vision ritual, Thaalia.', 1, 1),
(11785, 1, 'I am ready for the Mind Vision ritual, Thaalia.', 1, 1),
(11661, 0, 'I am ready for the Mind Vision ritual, Hu\'rala.', 1, 1),
(11661, 1, 'I am ready for the Mind Vision ritual, Hu\'rala.', 1, 1);

DELETE FROM `conditions` WHERE `SourceGroup` IN (11785, 11664, 11665, 11666, 11661);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11785, 0, 0, 0, 9, 0, 26773, 0, 0, 0, 0, 0, '', 'Priestess Thaalia - Show gossip only if quest 26773 is active'),
(15, 11785, 1, 0, 0, 9, 0, 26775, 0, 0, 0, 0, 0, '', 'Priestess Thaalia - Show gossip only if quest 26775 is active'),
(15, 11661, 0, 0, 0, 9, 0, 26359, 0, 0, 0, 0, 0, '', 'Priestess Hu\'rala - Show gossip only if quest 26359 is active'),
(15, 11661, 1, 0, 0, 9, 0, 26362, 0, 0, 0, 0, 0, '', 'Priestess Hu\'rala - Show gossip only if quest 26362 is active'),
(15, 11664, 0, 0, 0, 1, 0, 79821, 0, 0, 0, 0, 0, '', 'Tan\'Shang - Show gossip only if aura 79821 is active'),
(15, 11665, 0, 0, 0, 1, 0, 79821, 0, 0, 0, 0, 0, '', 'Tenjiyu - Show gossip only if aura 79821 is active'),
(15, 11665, 1, 0, 0, 1, 0, 80210, 0, 0, 0, 0, 0, '', 'Tenjiyu - Show gossip only if Stolen Food aura is active'),
(15, 11666, 0, 0, 0, 1, 0, 79821, 0, 0, 0, 0, 0, '', 'Chiyu - Show gossip only if aura 79821 is active');

-- Priestess Thaalia
SET @ENTRY := 44017;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11785,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11785,0,0,0,75,93481,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Fade"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,11785,0,0,0,11,79834,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Raptor"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,11785,0,0,0,86,79845,2,7,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Cast Teleport Zul'Gurub"),
(@ENTRY,@SOURCETYPE,4,0,62,0,100,0,11785,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,5,0,62,0,100,0,11785,1,0,0,75,93481,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Fade"),
(@ENTRY,@SOURCETYPE,6,8,62,0,100,0,11785,1,0,0,11,79952,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Raptor 1"),
(@ENTRY,@SOURCETYPE,7,0,62,0,100,0,11785,1,0,0,86,80119,2,7,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Cast Teleport Zul'Gurub"),
(@ENTRY,@SOURCETYPE,8,0,61,0,100,0,0,0,0,0,75,79821,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Add Mind Vision");

UPDATE `creature_template` SET `VehicleId`=926 WHERE `entry`=42840;

DELETE FROM `creature_text` WHERE `entry`=42842;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(42842,0,0,'Welcome to Zul\'Gurub, little one. It might not look like much now, but give it time...',12,0,100,0,0,0,'Comment'),
(42842,1,0,'Ahh... it\'s good to be home.',12,0,100,0,34,0,'Emote'),
(42842,2,0,'There\'s plenty others of your kind here, but I wouldn\'t worry about competition. You\'re from the bloodline of Ohgan, my oldest friend. You see... our souls are intertwined, yours and mine.',12,0,100,0,0,0,'Comment'),
(42842,3,0,'Here we are. Get ready for your training, little one. I reccomend you forget about that worthless human rogue and start thinking about your duties here in Zul\'Gurub.',12,0,100,0,0,0,'Comment');

DELETE FROM `waypoints` WHERE `entry` IN (42842, 42840);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(42842, 1, -12247.07, -1820.45, 130.25, 'Mandokir (Event) WP'),
(42842, 2, -12296.43, -1823.36, 130.26, 'Mandokir (Event) WP'),
(42842, 3, -12318.94, -1835.75, 130.26, 'Mandokir (Event) WP'),
(42842, 4, -12320.50, -1853.67, 130.26, 'Mandokir (Event) WP'),
(42842, 5, -12281.48, -1910.52, 130.26, 'Mandokir (Event) WP'),
(42842, 6, -12221.02, -1938.14, 130.27, 'Mandokir (Event) WP'),
(42840, 1, -12231.71, -1818.71, 127.87, 'Mandokir (Event) WP'),
(42840, 2, -12293.55, -1822.06, 130.26, 'Mandokir (Event) WP'),
(42840, 3, -12315.50, -1835.84, 130.26, 'Mandokir (Event) WP'),
(42840, 4, -12320.24, -1849.43, 130.26, 'Mandokir (Event) WP'),
(42840, 5, -12289.35, -1900.93, 130.26, 'Mandokir (Event) WP'),
(42840, 6, -12234.69, -1932.05, 130.27, 'Mandokir (Event) WP');

-- Captured Lashtail Hatchling
SET @ENTRY := 42840;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,3000,3000,3000,3000,86,46598,0,18,30,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (3 sec) - Ride Player"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Phase 2"),
(@ENTRY,@SOURCETYPE,2,0,27,2,100,0,0,0,0,0,11,79838,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Summon Mandokir"),
(@ENTRY,@SOURCETYPE,3,0,61,2,100,0,0,0,0,0,53,0,42840,0,0,0,0,1,42842,8,0,0.0,0.0,0.0,0.0,"Link - Start WP"),
(@ENTRY,@SOURCETYPE,4,5,28,2,100,0,0,0,0,0,41,500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Force Despawn"),
(@ENTRY,@SOURCETYPE,5,0,61,2,100,0,0,0,0,0,45,0,2,0,0,0,0,11,42842,20,0,0.0,0.0,0.0,0.0,"Link - Set Data 2 to Mandokir"),
(@ENTRY,@SOURCETYPE,6,3,27,2,100,0,0,0,0,0,45,0,1,0,0,0,0,11,42842,15,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Data 1 to Mandokir"),
(@ENTRY,@SOURCETYPE,7,0,38,2,100,0,0,1,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Remove Passenger"),
(@ENTRY,@SOURCETYPE,8,0,40,2,100,0,1,0,0,0,54,13000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 1 - WP Pause");

-- Bloodlord Mandokir
SET @ENTRY := 42842;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,1,0,500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,42842,0,0,53,0,42842,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Start WP"),
(@ENTRY,@SOURCETYPE,2,3,40,0,100,0,1,0,0,0,54,8000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 1 - WP Pause"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,40,0,100,0,3,0,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 3 - Talk 2"),
(@ENTRY,@SOURCETYPE,5,0,40,0,100,0,6,0,0,0,1,3,10000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 6 - Talk 3"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,3,0,0,0,45,0,1,0,0,0,0,11,42840,25,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 1 to Raptor"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,0,0,2,0,0,41,2000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Force Despawn"),
(@ENTRY,@SOURCETYPE,8,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run");

UPDATE `creature` SET `phaseMask`=2 WHERE `id` IN (42881, 42882, 42883, 42871, 42834, 42888);
UPDATE `creature` SET `phaseMask`=3 WHERE `id` IN (42825, 42837, 42838);
UPDATE `creature_template` SET `InhabitType`=4, `MovementType`=1 WHERE `entry`=42837;
UPDATE `creature` SET `spawndist`=30 WHERE `id`=42837;
DELETE FROM `creature_template_addon` WHERE `entry`=42838;
UPDATE `creature_template` SET `spell1`=44531 WHERE `entry`=42870;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11664 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11665 AND `id`=0;
UPDATE `creature_template` SET `unit_flags`=16777216, `dynamicflags`=16777216, `InhabitType`=1, `VehicleId`=928, `minlevel`=35, `maxlevel`=35 WHERE `entry` IN (42870, 42930, 42931, 42932);
UPDATE `creature_template` SET `spell1`=44531, `spell2`=80022 WHERE `entry`=42930;
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=42871;
UPDATE `creature_template` SET `spell1`=44531, `spell2`=80022, `spell3`=80046 WHERE `entry`=42931;
UPDATE `gameobject` SET `phaseMask`=1 WHERE `id` IN (204112, 204111, 204113);
UPDATE `creature` SET `phaseMask`=1 WHERE `id` IN (42922, 42883, 42927);
UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry` IN (42922, 42927);
UPDATE `creature_template` SET `MovementType`=1 WHERE `entry`=42871;
UPDATE `creature` SET `spawndist`=60 WHERE `id`=42871;
UPDATE `gameobject_template` SET `flags`=1 WHERE `entry`=204111;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11666 AND `id`=0;
UPDATE `creature_template` SET `spell1`=44531, `spell2`=80022, `spell3`=80046, `spell4`=80049 WHERE `entry`=42932;
UPDATE `gameobject` SET `phaseMask`=3 WHERE `id` IN (208349, 208350);

DELETE FROM `creature_text` WHERE `entry` IN (42930, 42882, 42883);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(42930,0,0,'Use the Eat Through Net ability to chew through gurubashi nets!',41,0,100,0,0,0,'Comment'),
(42882,0,0,'Steal food from sleeping Gurubashi Soldiers!',41,0,100,0,0,0,'Comment'),
(42882,1,0,'Pick up Burning Twigs from braziers, then use Light Fire to burn down Zul\'Gurub Tikis!',41,0,100,0,0,0,'Comment'),
(42883,0,0,'Pick up Gurubashi Skulls from skullpiles, then drop them in troll paths!',41,0,100,0,0,0,'Comment');

DELETE FROM `creature_addon` WHERE `guid` IN (775061, 775060, 775059, 775062, 775058, 775117, 775122, 775057, 775055, 775054, 775064, 775119, 775121, 775120, 775116);
DELETE FROM `creature` WHERE `guid` IN (775061, 775060, 775059, 775062, 775058, 775117, 775122, 775057, 775055, 775054, 775064, 775119, 775121, 775120, 775116);
UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=42871;

DELETE FROM `creature_template_addon` WHERE `entry` = '42871';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(42871, '82851');

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '11665' AND `id` = '1';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(11665, 1, 'I\'ve brought some food for you.', 1, 1);

-- Captured Lashtail Hatchling
SET @ENTRY := 42870;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,3000,3000,3000,3000,86,46598,0,18,30,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update (3 sec) - Ride Player"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Phase 2"),
(@ENTRY,@SOURCETYPE,2,0,28,0,100,0,0,0,0,0,41,500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Force Despawn"),
(@ENTRY,@SOURCETYPE,3,4,38,0,100,0,0,1,0,0,36,42930,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Update Template"),
(@ENTRY,@SOURCETYPE,4,6,61,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,5,0,54,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Passive"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Passive"),
(@ENTRY,@SOURCETYPE,7,8,38,0,100,0,0,3,0,0,36,42931,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Update Template"),
(@ENTRY,@SOURCETYPE,8,9,61,0,100,0,0,0,0,0,28,80210,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Stolen Food"),
(@ENTRY,@SOURCETYPE,9,0,61,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Passive"),
(@ENTRY,@SOURCETYPE,10,8,38,0,100,0,0,10,0,0,36,42932,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Update Template"),
(@ENTRY,@SOURCETYPE,11,0,54,0,100,0,0,0,0,0,44,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Phase 2");

-- Captured Lashtail Hatchling
SET @ENTRY := 42930;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,1,0,1,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0");

-- Tan'shang
SET @ENTRY := 42881;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11664,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11664,0,0,0,45,0,1,0,0,0,0,11,42870,15,0,0.0,0.0,0.0,0.0,"On Gossip Select - Set Data 1 to Hatchling"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,11664,0,0,0,33,42881,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit");

-- Tenjiyu
SET @ENTRY := 42882;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,3,62,0,100,0,11665,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11665,0,0,0,45,0,2,0,0,0,0,11,42930,15,0,0.0,0.0,0.0,0.0,"On Gossip Select - Set Data 1 to Hatchling"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,11665,1,0,0,33,42882,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,4,5,62,0,100,0,11665,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,5,6,61,0,100,0,0,0,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 1"),
(@ENTRY,@SOURCETYPE,6,7,61,0,100,0,0,0,0,0,45,0,3,0,0,0,0,11,42930,25,0,0.0,0.0,0.0,0.0,"Link - Set Data 3 to Hatchling"),
(@ENTRY,@SOURCETYPE,7,8,61,0,100,0,0,0,0,0,28,80210,0,0,0,0,0,11,42930,25,0,0.0,0.0,0.0,0.0,"Link - Remove Stolen Food (Vehicle)"),
(@ENTRY,@SOURCETYPE,8,0,61,0,100,0,0,0,0,0,28,80210,0,0,0,0,0,18,25,0,0,0.0,0.0,0.0,0.0,"Link - Remove Stolen Food (Player)");

-- Chiyu
SET @ENTRY := 42883;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11666,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,3,62,0,100,0,11666,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,11666,0,0,0,33,42883,5000,0,0,0,0,18,30,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,45,0,10,0,0,0,0,11,42931,30,0,0.0,0.0,0.0,0.0,"Link - Set Data 10 to Lashtail");

-- Gurubashi Soldier
SET @ENTRY := 42871;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,50,0,1000,1000,30000,60000,11,78677,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Sleep"),
(@ENTRY,@SOURCETYPE,1,3,60,0,50,0,45000,45000,45000,45000,28,78677,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Asleep"),
(@ENTRY,@SOURCETYPE,2,0,8,0,100,0,78677,1,0,0,2,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Set Friendly"),
(@ENTRY,@SOURCETYPE,3,9,61,0,100,0,0,0,0,0,2,28,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Reset Faction"),
(@ENTRY,@SOURCETYPE,4,0,64,0,100,0,0,0,0,0,75,80210,0,0,0,0,0,19,42930,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Add Stolen Food"),
(@ENTRY,@SOURCETYPE,5,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,6,0,4,0,100,0,80021,0,0,0,75,0,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Net on victim"),
(@ENTRY,@SOURCETYPE,7,0,64,0,100,0,0,0,0,0,75,80210,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Add Stolen Food"),
(@ENTRY,@SOURCETYPE,8,10,38,0,100,0,0,5,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Set Passive"),
(@ENTRY,@SOURCETYPE,9,0,61,0,100,0,0,0,0,0,8,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Reset State"),
(@ENTRY,@SOURCETYPE,10,0,61,0,100,0,0,0,0,0,69,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Move To Invoker");

UPDATE `creature_template` SET `unit_flags`=0, `type_flags`=0, `VehicleId`=0 WHERE `entry`=1061;
DELETE FROM `creature_template_addon` WHERE `entry`=1061;

DELETE FROM `creature_loot_template` WHERE `item` = '58179';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(1061, 58179, -100, 1, 0, 1, 1);

DELETE FROM `spell_area` WHERE `quest_end` = '26323';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(79772, 117, 26323, 26323, 1, 74, 74);

UPDATE `creature_template` SET `npcflag`=16777216, `IconName`='Cast' WHERE `entry`=2530;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '2530';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(2530, 3660, 1);

DELETE FROM `creature_loot_template` WHERE `item` = '1532';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(671, 1532, -75, 1, 0, 1, 3),
(660, 1532, -75, 1, 0, 1, 3),
(597, 1532, -72, 1, 0, 1, 3);

-- Priestess Hu'rala
SET @ENTRY := 42812;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11661,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11661,0,0,0,75,93481,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Fade"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,11661,0,0,0,11,79834,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Raptor"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,11661,0,0,0,86,79845,2,7,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Cast Teleport Zul'Gurub"),
(@ENTRY,@SOURCETYPE,4,0,62,0,100,0,11661,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,5,0,62,0,100,0,11661,1,0,0,75,93481,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Fade"),
(@ENTRY,@SOURCETYPE,6,8,62,0,100,0,11661,1,0,0,11,79952,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Raptor 1"),
(@ENTRY,@SOURCETYPE,7,0,62,0,100,0,11661,1,0,0,86,80119,2,7,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Cast Teleport Zul'Gurub"),
(@ENTRY,@SOURCETYPE,8,0,61,0,100,0,0,0,0,0,75,79821,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Add Mind Vision");

DELETE FROM `spell_target_position` WHERE `id` = '82401';
INSERT INTO `spell_target_position` (`id`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(82401, -12083.16, -856.14, 51.24, 4.36);

-- Venture Co. Shredder
SET @ENTRY := 4260;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,0,0,100,0,5000,12500,5000,12500,11,83825,2,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Use buzzsaw"),
(@ENTRY,@SOURCETYPE,1,0,61,0,65,0,0,0,0,0,86,80277,0,2,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete");

DELETE FROM `gameobject_loot_template` WHERE `entry` = '39336';
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(39336, 720, 0.3775, 1, 0, 1, 1),
(39336, 774, 0.2, 1, 0, 1, 1),
(39336, 791, 0.3791, 1, 0, 1, 1),
(39336, 818, 0.6394, 1, 0, 1, 1),
(39336, 858, 0.1864, 1, 0, 1, 1),
(39336, 890, 0.3615, 1, 0, 1, 1),
(39336, 929, 0.5125, 1, 0, 1, 1),
(39336, 934, 0.4305, 1, 0, 1, 1),
(39336, 936, 0.3904, 1, 0, 1, 1),
(39336, 937, 0.4016, 1, 0, 1, 1),
(39336, 1121, 0.3791, 1, 0, 1, 1),
(39336, 1203, 0.1815, 1, 0, 1, 1),
(39336, 1206, 0.784, 1, 0, 1, 1),
(39336, 1210, 0.792, 1, 0, 1, 1),
(39336, 1265, 0.4, 1, 0, 1, 1),
(39336, 1529, 1.0153, 1, 0, 1, 1),
(39336, 1607, 0.2, 1, 0, 1, 1),
(39336, 1705, 1.0008, 1, 0, 1, 1),
(39336, 1710, 0.347, 1, 0, 1, 1),
(39336, 1716, 0.3341, 1, 0, 1, 1),
(39336, 1717, 0.4016, 1, 0, 1, 1),
(39336, 1726, 0.3663, 1, 0, 1, 1),
(39336, 1973, 0.2088, 1, 0, 1, 1),
(39336, 2011, 0.3599, 1, 0, 1, 1),
(39336, 2059, 0.4289, 1, 0, 1, 1),
(39336, 2075, 0.1478, 1, 0, 1, 1),
(39336, 2098, 0.3518, 1, 0, 1, 1),
(39336, 2194, 0.3229, 1, 0, 1, 1),
(39336, 2236, 0.3566, 1, 0, 1, 1),
(39336, 2256, 0.3165, 1, 0, 1, 1),
(39336, 2276, 0.4337, 1, 0, 1, 1),
(39336, 2277, 0.3743, 1, 0, 1, 1),
(39336, 2278, 0.4032, 1, 0, 1, 1),
(39336, 2299, 0.4482, 1, 0, 1, 1),
(39336, 2455, 0.2024, 1, 0, 1, 1),
(39336, 2456, 0.188, 1, 0, 1, 1),
(39336, 2459, 0.2217, 1, 0, 1, 1),
(39336, 2565, 0.3775, 1, 0, 1, 1),
(39336, 2721, 0.4016, 1, 0, 1, 1),
(39336, 2800, 0.2956, 1, 0, 1, 1),
(39336, 2802, 0.2, 1, 0, 1, 1),
(39336, 2877, 0.3727, 1, 0, 1, 1),
(39336, 2878, 0.3261, 1, 0, 1, 1),
(39336, 2879, 0.392, 1, 0, 1, 1),
(39336, 2911, 0.3293, 1, 0, 1, 1),
(39336, 2912, 0.3518, 1, 0, 1, 1),
(39336, 2951, 0.4337, 1, 0, 1, 1),
(39336, 3020, 0.4209, 1, 0, 1, 1),
(39336, 3021, 0.3839, 1, 0, 1, 1),
(39336, 3040, 0.1, 1, 0, 1, 1),
(39336, 3192, 0.1382, 1, 0, 1, 1),
(39336, 3196, 0.2, 1, 0, 1, 1),
(39336, 3203, 0.3807, 1, 0, 1, 1),
(39336, 3283, 0.1735, 1, 0, 1, 1),
(39336, 3384, 0.4097, 1, 0, 1, 1),
(39336, 3385, 0.4209, 1, 0, 1, 1),
(39336, 3827, 0.3374, 1, 0, 1, 1),
(39336, 3864, 0.7502, 1, 0, 1, 1),
(39336, 4561, 0.2, 1, 0, 1, 1),
(39336, 4570, 0.151, 1, 0, 1, 1),
(39336, 4571, 0.2, 1, 0, 1, 1),
(39336, 4596, 0.1992, 1, 0, 1, 1),
(39336, 4696, 0.1767, 1, 0, 1, 1),
(39336, 5266, 0.2024, 1, 0, 1, 1),
(39336, 5631, 0.2233, 1, 0, 1, 1),
(39336, 5633, 0.3615, 1, 0, 1, 1),
(39336, 6048, 0.4562, 1, 0, 1, 1),
(39336, 6049, 0.3149, 1, 0, 1, 1),
(39336, 6050, 0.3502, 1, 0, 1, 1),
(39336, 6051, 0.2104, 1, 0, 1, 1),
(39336, 6052, 0.2972, 1, 0, 1, 1),
(39336, 6372, 0.204, 1, 0, 1, 1),
(39336, 6660, 0.1976, 1, 0, 1, 1),
(39336, 7734, 0.2281, 1, 0, 1, 1),
(39336, 7909, 0.8402, 1, 0, 1, 1),
(39336, 7910, 0.6506, 1, 0, 1, 1),
(39336, 8006, 0.4321, 1, 0, 1, 1),
(39336, 8190, 0.2056, 1, 0, 1, 1),
(39336, 9385, 0.3727, 1, 0, 1, 1),
(39336, 9395, 0.3486, 1, 0, 1, 1),
(39336, 9402, 0.2, 1, 0, 1, 1),
(39336, 9405, 0.4145, 1, 0, 1, 1),
(39336, 9435, 0.3261, 1, 0, 1, 1),
(39336, 11302, 0.2, 1, 0, 1, 1),
(39336, 12974, 0.3438, 1, 0, 1, 1),
(39336, 12979, 0.339, 1, 0, 1, 1),
(39336, 12982, 0.3518, 1, 0, 1, 1),
(39336, 12983, 0.4064, 1, 0, 1, 1),
(39336, 12984, 0.4546, 1, 0, 1, 1),
(39336, 12985, 0.3245, 1, 0, 1, 1),
(39336, 12987, 0.4755, 1, 0, 1, 1),
(39336, 12988, 0.3952, 1, 0, 1, 1),
(39336, 12989, 0.3502, 1, 0, 1, 1),
(39336, 12990, 0.4787, 1, 0, 1, 1),
(39336, 12992, 0.3454, 1, 0, 1, 1),
(39336, 12994, 0.3068, 1, 0, 1, 1),
(39336, 12996, 0.4113, 1, 0, 1, 1),
(39336, 12997, 0.3856, 1, 0, 1, 1),
(39336, 12998, 0.3615, 1, 0, 1, 1),
(39336, 12999, 0.4209, 1, 0, 1, 1),
(39336, 13002, 0.2554, 1, 0, 1, 1),
(39336, 13003, 0.2072, 1, 0, 1, 1),
(39336, 13004, 0.2265, 1, 0, 1, 1),
(39336, 13005, 0.3534, 1, 0, 1, 1),
(39336, 13007, 0.2056, 1, 0, 1, 1),
(39336, 13008, 0.1944, 1, 0, 1, 1),
(39336, 13010, 0.3582, 1, 0, 1, 1),
(39336, 13011, 0.3229, 1, 0, 1, 1),
(39336, 13012, 0.3807, 1, 0, 1, 1),
(39336, 13013, 0.2121, 1, 0, 1, 1),
(39336, 13016, 0.3036, 1, 0, 1, 1),
(39336, 13017, 0.4627, 1, 0, 1, 1),
(39336, 13019, 0.4, 1, 0, 1, 1),
(39336, 13020, 0.4835, 1, 0, 1, 1),
(39336, 13022, 0.2201, 1, 0, 1, 1),
(39336, 13024, 0.4097, 1, 0, 1, 1),
(39336, 13025, 0.3695, 1, 0, 1, 1),
(39336, 13027, 0.2121, 1, 0, 1, 1),
(39336, 13030, 0.1815, 1, 0, 1, 1),
(39336, 13031, 0.3454, 1, 0, 1, 1),
(39336, 13032, 0.3711, 1, 0, 1, 1),
(39336, 13033, 0.4643, 1, 0, 1, 1),
(39336, 13037, 0.5832, 1, 0, 1, 1),
(39336, 13038, 0.4482, 1, 0, 1, 1),
(39336, 13040, 0.1912, 1, 0, 1, 1),
(39336, 13041, 0.3936, 1, 0, 1, 1),
(39336, 13045, 0.3791, 1, 0, 1, 1),
(39336, 13047, 0.2104, 1, 0, 1, 1),
(39336, 13048, 0.3775, 1, 0, 1, 1),
(39336, 13049, 0.3711, 1, 0, 1, 1),
(39336, 13052, 0.2394, 1, 0, 1, 1),
(39336, 13054, 0.437, 1, 0, 1, 1),
(39336, 13056, 0.2217, 1, 0, 1, 1),
(39336, 13057, 0.4305, 1, 0, 1, 1),
(39336, 13059, 0.2217, 1, 0, 1, 1),
(39336, 13062, 0.3872, 1, 0, 1, 1),
(39336, 13063, 0.3679, 1, 0, 1, 1),
(39336, 13066, 0.1815, 1, 0, 1, 1),
(39336, 13067, 0.2, 1, 0, 1, 1),
(39336, 13070, 0.2265, 1, 0, 1, 1),
(39336, 13073, 0.188, 1, 0, 1, 1),
(39336, 13077, 0.1719, 1, 0, 1, 1),
(39336, 13079, 0.3904, 1, 0, 1, 1),
(39336, 13081, 0.5301, 1, 0, 1, 1),
(39336, 13084, 0.408, 1, 0, 1, 1),
(39336, 13087, 0.4177, 1, 0, 1, 1),
(39336, 13091, 0.2, 1, 0, 1, 1),
(39336, 13093, 0.3888, 1, 0, 1, 1),
(39336, 13094, 0.3727, 1, 0, 1, 1),
(39336, 13097, 0.3374, 1, 0, 1, 1),
(39336, 13099, 0.4659, 1, 0, 1, 1),
(39336, 13103, 0.4498, 1, 0, 1, 1),
(39336, 13105, 0.3968, 1, 0, 1, 1),
(39336, 13106, 0.3711, 1, 0, 1, 1),
(39336, 13108, 0.4402, 1, 0, 1, 1),
(39336, 13110, 0.4113, 1, 0, 1, 1),
(39336, 13111, 0.2394, 1, 0, 1, 1),
(39336, 13114, 0.4546, 1, 0, 1, 1),
(39336, 13119, 0.3823, 1, 0, 1, 1),
(39336, 13120, 0.1944, 1, 0, 1, 1),
(39336, 13121, 0.3823, 1, 0, 1, 1),
(39336, 13124, 0.339, 1, 0, 1, 1),
(39336, 13126, 0.1847, 1, 0, 1, 1),
(39336, 13127, 0.3004, 1, 0, 1, 1),
(39336, 13129, 0.392, 1, 0, 1, 1),
(39336, 13131, 0.4064, 1, 0, 1, 1),
(39336, 13135, 0.1815, 1, 0, 1, 1),
(39336, 13136, 0.3791, 1, 0, 1, 1),
(39336, 13137, 0.3358, 1, 0, 1, 1),
(39336, 13144, 0.196, 1, 0, 1, 1),
(39336, 13145, 0.3293, 1, 0, 1, 1),
(39336, 13146, 0.2, 1, 0, 1, 1),
(39336, 15222, 0.1526, 1, 0, 1, 1),
(39336, 15248, 0.2, 1, 0, 1, 1),
(39336, 15268, 0.2153, 1, 0, 1, 1),
(39336, 15497, 0.2, 1, 0, 1, 1),
(39336, 21929, 0.3486, 1, 0, 1, 1),
(39336, 23077, 0.3213, 1, 0, 1, 1),
(39336, 23079, 0.355, 1, 0, 1, 1),
(39336, 23107, 0.3888, 1, 0, 1, 1),
(39336, 23112, 0.3534, 1, 0, 1, 1),
(39336, 23117, 0.408, 1, 0, 1, 1),
(39336, 24222, 0.2, 1, 0, 1, 1),
(39336, 37757, 0.2, 1, 0, 1, 1),
(39336, 37758, 0.3084, 1, 0, 1, 1),
(39336, 37759, 0.392, 1, 0, 1, 1),
(39336, 37760, 0.4739, 1, 0, 1, 1),
(39336, 37761, 0.4273, 1, 0, 1, 1),
(39336, 37767, 0.3422, 1, 0, 1, 1),
(39336, 37768, 0.3582, 1, 0, 1, 1),
(39336, 37769, 0.3839, 1, 0, 1, 1),
(39336, 37770, 0.4884, 1, 0, 1, 1),
(39336, 37771, 0.3759, 1, 0, 1, 1),
(39336, 37778, 0.3422, 1, 0, 1, 1),
(39336, 37779, 0.4803, 1, 0, 1, 1),
(39336, 37780, 0.4225, 1, 0, 1, 1),
(39336, 37781, 0.5719, 1, 0, 1, 1),
(39336, 37786, 0.2, 1, 0, 1, 1),
(39336, 37789, 0.339, 1, 0, 1, 1),
(39336, 37790, 0.3936, 1, 0, 1, 1),
(39336, 37792, 0.3615, 1, 0, 1, 1),
(39336, 37793, 0.4691, 1, 0, 1, 1),
(39336, 37794, 0.3775, 1, 0, 1, 1),
(39336, 37797, 0.4578, 1, 0, 1, 1),
(39336, 37802, 0.2, 1, 0, 1, 1),
(39336, 37804, 0.347, 1, 0, 1, 1),
(39336, 37806, 0.3615, 1, 0, 1, 1),
(39336, 37808, 0.3293, 1, 0, 1, 1),
(39336, 37809, 0.3952, 1, 0, 1, 1),
(39336, 37810, 0.2651, 1, 0, 1, 1),
(39336, 37812, 0.3406, 1, 0, 1, 1),
(39336, 37822, 0.4611, 1, 0, 1, 1),
(39336, 37823, 0.4835, 1, 0, 1, 1),
(39336, 37824, 0.408, 1, 0, 1, 1),
(39336, 40211, 0.1735, 1, 0, 1, 1),
(39336, 40213, 0.1815, 1, 0, 1, 1),
(39336, 40215, 0.2, 1, 0, 1, 1),
(39336, 41777, 0.2715, 1, 0, 1, 1),
(39336, 41778, 0.1896, 1, 0, 1, 1),
(39336, 41780, 0.2104, 1, 0, 1, 1),
(39336, 41783, 0.2104, 1, 0, 1, 1),
(39336, 41784, 0.2763, 1, 0, 1, 1),
(39336, 41786, 0.2458, 1, 0, 1, 1),
(39336, 41787, 0.3422, 1, 0, 1, 1),
(39336, 41788, 0.2281, 1, 0, 1, 1),
(39336, 41789, 0.2265, 1, 0, 1, 1),
(39336, 45912, 2.0418, 1, 0, 1, 1),
(39336, 66916, 0.1, 1, 0, 1, 1),
(39336, 66976, 0.1655, 1, 0, 1, 1),
(39336, 67098, 0.1815, 1, 0, 1, 1),
(39336, 67110, 0.2362, 1, 0, 1, 1);