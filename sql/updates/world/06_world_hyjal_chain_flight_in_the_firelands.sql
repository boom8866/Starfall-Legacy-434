UPDATE `gameobject_template` SET `ScriptName`='go_twilight_weapon_rack' WHERE `entry`=202967;

DELETE FROM `spell_script_names` WHERE `spell_id` = '74180';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(74180, 'spell_twilight_firelance_equipped');

UPDATE `creature_template` SET `npcflag` = '1' AND `ScriptName`='npc_aviana_guardian' WHERE `entry`=40720;
UPDATE `creature_template` SET `spell1`=0, `spell4`=74183 WHERE `entry`=40719;
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry` IN (40650, 39833);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` IN (39833, 40650);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(39833, 46598, 0),
(40650, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '40650';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(40650, 40660, 1, 'Twilight Firebird - Twilight Lancer', 8, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '39833';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(39833, 39835, 1, 'Twilight Buzzard - Knight Rider', 8, 0);

UPDATE `creature` SET `spawndist`=20, `MovementType`=1, `phaseMask`=16384 WHERE `id`=40650;
UPDATE `creature` SET `spawndist`=20, `MovementType`=1, `phaseMask`=2 WHERE `id`=39833;
UPDATE `creature` SET `phaseMask`=16384 WHERE `id` IN (40708, 40762);
UPDATE `creature_template` SET `speed_walk`=2.14 WHERE `entry` IN (40650, 39833);
UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry`=40719;

-- Twilight Firebird
SET @ENTRY := 40650;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,33,40660,0,0,0,0,0,18,6,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit");

-- Twilight Buzzard
SET @ENTRY := 39833;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,33,39835,0,0,0,0,0,18,6,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit");

-- Firelands Egg
SET @ENTRY := 40762;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,33,40762,0,0,0,0,0,18,5,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit"),
(@ENTRY,@SOURCETYPE,1,0,6,0,100,0,0,0,0,0,11,19593,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Explode");

-- Aviana's Guardian
SET @ENTRY := 40719;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,85,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Invoker"),
(@ENTRY,@SOURCETYPE,1,0,28,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Force Despawn"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,3,0,1,0,100,0,1000,1000,1000,1000,51,0,0,0,0,0,0,11,40650,5,0,0.0,0.0,0.0,0.0,"OOC - Kill Unit"),
(@ENTRY,@SOURCETYPE,4,0,1,0,100,0,1000,1000,1000,1000,51,0,0,0,0,0,0,11,39833,5,0,0.0,0.0,0.0,0.0,"OOC - Kill Unit"),
(@ENTRY,@SOURCETYPE,5,0,1,0,100,0,1000,1000,1000,1000,85,35041,0,0,0,0,0,11,40650,5,0,0.0,0.0,0.0,0.0,"OOC - Swing"),
(@ENTRY,@SOURCETYPE,6,0,1,0,100,0,1000,1000,1000,1000,85,35041,0,0,0,0,0,11,39833,5,0,0.0,0.0,0.0,0.0,"OOC - Swing"),
(@ENTRY,@SOURCETYPE,7,0,1,0,100,0,1000,1000,1000,1000,51,0,0,0,0,0,0,11,40762,6,0,0.0,0.0,0.0,0.0,"OOC - Kill Unit"),
(@ENTRY,@SOURCETYPE,8,0,1,0,100,0,1000,1000,1000,1000,85,35041,0,0,0,0,0,11,40762,6,0,0.0,0.0,0.0,0.0,"OOC - Swing"),
(@ENTRY,@SOURCETYPE,10,0,8,0,4,0,74183,1,0,0,1,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 0");

DELETE FROM `spell_area` WHERE `spell` = '65141' AND `quest_start` = '25525';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(65141, 5050, 25525, 25525, 1, 10);

UPDATE `creature` SET `spawntimesecs`=60 WHERE `id`=40708;
UPDATE `creature_template` SET `modelid2`=32545 WHERE `entry`=40762;
UPDATE `creature` SET `spawntimesecs`=60 WHERE `id`=40762;

DELETE FROM `creature_text` WHERE `entry`=40578;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(40578,0,0,'Grab a Lance from the Racks',42,0,100,0,0,0,'Comment'),
(40578,1,0,'Wave One:',42,0,100,0,0,0,'Comment'),
(40578,2,0,'Prepare to Joust. Buzzard Bait!',42,0,100,0,0,0,'Comment'),
(40578,3,0,'Wave Two:',42,0,100,0,0,0,'Comment'),
(40578,4,0,'The sky is falling!',42,0,100,0,0,0,'Comment'),
(40578,5,0,'Egg Wave:',42,0,100,0,0,0,'Comment'),
(40578,6,0,'Destroy the Firelands Eggs!',42,0,100,0,0,0,'Comment');

-- Farden Talonshrike
SET @ENTRY := 40578;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,25523,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,25525,0,0,0,1,1,3000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,1,40578,0,0,1,2,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,3,0,19,0,100,0,25544,0,0,0,1,3,3000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 3"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,3,40578,0,0,1,4,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Talk 4"),
(@ENTRY,@SOURCETYPE,5,0,19,0,100,0,25560,0,0,0,1,5,3000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 5"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,5,40578,0,0,1,6,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 5 - Talk 6"),
(@ENTRY,@SOURCETYPE,7,0,20,0,100,0,25523,0,0,0,28,46598,0,0,0,0,0,22,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Remove From Vehicle"),
(@ENTRY,@SOURCETYPE,8,0,20,0,100,0,25525,0,0,0,28,46598,0,0,0,0,0,22,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Remove From Vehicle"),
(@ENTRY,@SOURCETYPE,9,0,20,0,100,0,25544,0,0,0,28,46598,0,0,0,0,0,22,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Remove From Vehicle"),
(@ENTRY,@SOURCETYPE,10,0,20,0,100,0,25560,0,0,0,28,46598,0,0,0,0,0,22,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Remove From Vehicle"),
(@ENTRY,@SOURCETYPE,11,0,20,0,100,0,29177,0,0,0,28,46598,0,0,0,0,0,22,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Remove From Vehicle");

DELETE FROM `creature_text` WHERE `entry`=40719;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(40719,0,0,'Flap Your Wings Rapidly to Re-Gain Altitude!',42,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_falling_boulder' WHERE `entry`=40708;