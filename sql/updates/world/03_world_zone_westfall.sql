UPDATE `creature` SET `spawndist`=15, `MovementType`=1 WHERE `id`=42311;

DELETE FROM `spell_area` WHERE `quest_end` IN (26378, 28562, 184, 26215, 26232, 26228);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(79489, 916, 28562, 28562, 0, 0, 2, 1, 74, 74),
(79489, 916, 26378, 26378, 0, 0, 2, 1, 74, 74),
(79489, 916, 184, 184, 0, 0, 2, 1, 74, 74),
(80695, 109, 26215, 26215, 0, 0, 2, 1, 2, 2),
(80695, 109, 26228, 26228, 0, 0, 2, 1, 74, 74),
(80672, 109, 26232, 26232, 0, 0, 2, 1, 66, 66);

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11635;

DELETE FROM `conditions` WHERE `SourceGroup` = '11635';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11635, 0, 0, 0, 9, 0, 26209, 0, 0, 0, 0, 0, '', 'Homeless Stormwind Citizen - Show gossip only if quest 26209 is active'),
(15, 11635, 1, 0, 0, 9, 0, 26209, 0, 0, 0, 0, 0, '', 'Homeless Stormwind Citizen - Show gossip only if quest 26209 is active');

DELETE FROM `creature_text` WHERE `entry`=42384;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(42384,0,0,'Listen, I don\'t want any trouble, ok? I didn\'t see who murdered\'em, but I sure heard it! Lot of yelling. Human voices... you dig? Now get out of here before I change my mind about beating you up and takin\' your shoes.',12,0,100,0,0,0,'Quest Complete (Paid)'),
(42384,1,0,'I didn\'t see who killed\'em, but I go a whiff, Smelled rich, kinda like you. Damn shame too, furlbrows were a fixture around here. Nice people, always willin\' to share a meal of a patch of dirt.',12,0,100,0,0,0,'Paid (2)'),
(42384,2,0,'Who killed the furlbrows? I\'ll tell you who killed the Furlbrows, KING VARIAN WRYNN, THAT\'S WHO! And he\'s killin\' the rest of us too. On burn at a time. The only thing I can tell you is that I saw some gnolls leavin\' the place a few hours before the law arrived.',12,0,100,0,0,0,'Paid (3)'),
(42384,3,0,'Between me, you, and the tree, murlocs killed the Furlbrows. Yep, saw\' em with my own two eyes. Think they\'d been casin\' the joint for days, maybe months. They left in a hurry once they got mind of "Johnny Law" and the idiot brigade over there...',12,0,100,0,0,0,'Paid (4)'),
(42384,4,0,'I ain\'t tellin\' you a damn thing!',12,0,100,0,0,0,'No Pay'),
(42384,5,0,'You rich punks are all the same!',12,0,100,0,0,0,'No Pay'),
(42384,6,0,'Now you\'ve gone and done it! TIME FOR THE FIST!',12,0,100,0,0,0,'No Pay'),
(42384,7,0,'You can\'t buy me! DIE!',12,0,100,0,0,0,'Pay 5 (Failed)'),
(42384,8,0,'I... I didn\'t see nothin\'! He... he died of natural causes.',12,0,100,0,0,0,'Comment');

-- Homeless Stormwind Citizen
SET @ENTRY := 42384;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,16,0,11635,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,5,62,0,16,0,11635,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 0 (Complete 1)"),
(@ENTRY,@SOURCETYPE,2,6,62,0,16,0,11635,1,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 1 (Complete 2)"),
(@ENTRY,@SOURCETYPE,3,7,62,0,16,0,11635,1,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 2 (Complete 3)"),
(@ENTRY,@SOURCETYPE,4,8,62,0,16,0,11635,1,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 3 (Complete 4)"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,33,42414,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit 1"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,0,0,0,0,0,33,42415,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit 2"),
(@ENTRY,@SOURCETYPE,7,0,61,0,100,0,0,0,0,0,33,42416,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit 3"),
(@ENTRY,@SOURCETYPE,8,0,61,0,100,0,0,0,0,0,33,42417,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit 4"),
(@ENTRY,@SOURCETYPE,9,2,62,0,16,0,11635,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,10,3,62,0,16,0,11635,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,11,4,62,0,16,0,11635,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,12,13,62,0,16,0,11635,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,13,14,62,0,16,0,11635,1,0,0,1,7,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 7 (Paid Failed)"),
(@ENTRY,@SOURCETYPE,14,15,61,0,100,0,0,0,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Faction 14"),
(@ENTRY,@SOURCETYPE,15,0,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Attack Invoker"),
(@ENTRY,@SOURCETYPE,16,13,62,0,16,0,11635,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,17,14,62,0,20,0,11635,0,0,0,1,6,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 6"),
(@ENTRY,@SOURCETYPE,18,14,62,0,20,0,11635,0,0,0,1,5,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 5"),
(@ENTRY,@SOURCETYPE,19,0,62,0,20,0,11635,0,0,0,1,4,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 4"),
(@ENTRY,@SOURCETYPE,20,0,7,0,100,0,0,0,0,0,2,7,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Reset Faction"),
(@ENTRY,@SOURCETYPE,21,0,38,0,100,0,0,5,0,0,1,8,5000,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Talk 8");

UPDATE `creature_template` SET `mindmg`=15, `maxdmg`=35, `attackpower`=15 WHERE `entry`=42384;

DELETE FROM `creature_loot_template` WHERE `item` = '57755';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(500, 57755, -31.585, 1, 0, 1, 1),
(117, 57755, -31.6898, 1, 0, 1, 1),
(1236, 57755, -31.585, 1, 0, 1, 1);

DELETE FROM `creature_loot_template` WHERE `item` = '57756';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(515, 57756, -22.7841, 1, 0, 1, 1),
(126, 57756, -20.0536, 1, 0, 1, 1),
(199, 57756, -20.0536, 1, 0, 1, 1),
(458, 57756, -20.0536, 1, 0, 1, 1),
(834, 57756, -20.0536, 1, 0, 1, 1),
(1236, 57756, -20.0536, 1, 0, 1, 1);

UPDATE `creature` SET `phaseMask`=1 WHERE `id` IN (42558, 42559, 42560);

DELETE FROM `spell_script_names` WHERE `spell_id` = '79262';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(79262, 'spell_summon_lou_house');

UPDATE `creature_template` SET `VehicleId`=899, `unit_flags`=2 WHERE `entry`=42500;
UPDATE `creature_template_addon` SET `auras`='79192' WHERE `entry`=42662;

DELETE FROM `creature_text` WHERE `entry` IN (42492, 42662);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(42492,0,0,'What little humie want? Why you call Glubtok?',12,0,100,0,0,0,'Comment'),
(42492,1,0,'Glubtok crush you!',12,0,100,0,0,0,'Comment'),
(42492,2,0,'What option two?',12,0,100,0,0,0,'Comment'),
(42492,3,0,'So Glubtok have two choices: die or be rich and powerful?',12,0,100,0,0,0,'Comment'),
(42492,4,0,'Glubtok take choice two.',12,0,100,0,0,0,'Comment'),
(42662,0,0,'Sad... Is this the life you had hoped for, Glubtok? Running two-bit extortion operations out of a cave?',12,0,100,0,0,0,'Comment'),
(42662,1,0,'Oh will you? Do you dare cross that line and risk your life?',12,0,100,0,0,0,'Comment'),
(42662,2,0,'You may attempt to kill me - and fail - or you may take option two.',12,0,100,0,0,0,'Comment'),
(42662,3,0,'You join me and I shower wealth and power upon you.',12,0,100,0,0,0,'Comment'),
(42662,4,0,'I thought you\'d see it my way.',12,0,100,0,0,0,'Comment'),
(42662,5,0,'I will call for you when the dawning is upon us.',12,0,100,0,0,0,'Comment'),
(42662,6,0,'They provided the distraction I required. We continue as planned.',12,0,100,0,0,0,'Comment'),
(42662,7,0,'We will free the admiral during the dawning.',12,0,100,0,0,0,'Comment'),
(42662,8,0,'Judgment day is soon upon us, Helix.',12,0,100,0,0,0,'Comment'),
(42662,9,0,'Call fo the people. I wish to speak to them one last time before the dawning.',12,0,100,0,0,0,'Comment'),
(42662,10,0,'Aye. Tonight.',12,0,100,0,0,0,'Comment');

-- Two-Shoed Lou's Old House
SET @ENTRY := 42500;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,86,46598,0,23,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Enter the box"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,12,42662,4,180000,0,0,0,8,0,0,0,-9839.85,1400.27,37.24,3.98,"On Passenger Boarded - Summon Shadowy Figure"),
(@ENTRY,@SOURCETYPE,2,0,27,0,100,0,0,0,0,0,12,42492,4,180000,0,0,0,8,0,0,0,-9844.66,1395.01,37.55,0.76,"On Passenger Boarded - Summon Glubtok"),
(@ENTRY,@SOURCETYPE,3,0,28,0,100,0,0,0,0,0,45,0,5,0,0,0,0,11,0,50,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Despawn Jangolode Actors");

-- Glubtok
SET @ENTRY := 42492;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,54,0,100,0,0,0,0,0,11,52096,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Teleport"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,42492,0,0,45,0,1,0,0,0,0,11,42662,50,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Shadowy"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,1,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,42492,0,0,45,0,2,0,0,0,0,11,42662,20,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 2 to Shadowy"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,2,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 2"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,2,42492,0,0,45,0,3,0,0,0,0,11,42662,20,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 3 to Shadowy"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,0,0,3,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 3"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,3,42492,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Talk 4"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,4,42492,0,0,45,0,4,0,0,0,0,11,42662,20,0,0.0,0.0,0.0,0.0,"After Talk 4 - Set Data 4 to Shadowy"),
(@ENTRY,@SOURCETYPE,10,0,38,0,100,0,0,4,0,0,41,1500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Force Despawn (1500)"),
(@ENTRY,@SOURCETYPE,11,0,38,0,100,0,0,5,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Force Despawn (1000)");

-- Shadowy Figure
SET @ENTRY := 42662;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,42662,0,0,45,0,1,0,0,0,0,11,42492,20,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Glubtok"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,2,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,42662,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,2,42662,0,0,45,0,2,0,0,0,0,11,42492,20,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 2 to Glubtok"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,3,0,0,1,3,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 3"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,3,42662,0,0,45,0,3,0,0,0,0,11,42492,20,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 3 to Glubtok"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,0,0,4,0,0,1,4,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 4 - Talk 4"),
(@ENTRY,@SOURCETYPE,8,9,52,0,100,0,4,42662,0,0,1,5,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Talk 5"),
(@ENTRY,@SOURCETYPE,9,10,61,0,100,0,0,0,0,0,15,26228,0,0,0,0,0,18,50,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete"),
(@ENTRY,@SOURCETYPE,10,11,61,0,100,0,0,0,0,0,45,0,4,0,0,0,0,11,42492,20,0,0.0,0.0,0.0,0.0,"Link - Set Data 4 to Glubtok (Despawn)"),
(@ENTRY,@SOURCETYPE,11,0,61,0,100,0,0,0,0,0,41,2000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn (2000)"),
(@ENTRY,@SOURCETYPE,12,0,38,0,100,0,0,5,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Force Despawn (1000)"),
(@ENTRY,@SOURCETYPE,13,14,8,0,100,0,78935,1,0,0,15,26290,0,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Complete"),
(@ENTRY,@SOURCETYPE,14,0,61,0,100,0,0,0,0,0,18,131072,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Pacified");

DELETE FROM `creature_text` WHERE `entry`=42386;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(42386,0,0,'Maybe... maybe life is worth living.',12,0,100,0,0,0,'Comment'),
(42386,0,1,'Bless you, friend.',12,0,100,0,0,0,'Comment'),
(42386,0,2,'I\'d know that smell anywhere! Salma\'s famous stew!',12,0,100,0,0,0,'Comment');

-- Westfall Stew
SET @ENTRY := 42617;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,42386,10,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Data 1 to Homeless Stormwind Citizen");

-- Homeless Stormwind Citizen
SET @ENTRY := 42386;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,38,0,100,0,0,1,0,0,29,2,0,42617,0,0,0,11,42617,10,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Follow Westfall Stew"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,11,79451,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Full and Content"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,0,0,0,0,33,42617,0,0,0,0,0,18,20,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit"),
(@ENTRY,@SOURCETYPE,3,0,61,0,10,0,0,0,0,0,1,0,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0 (Chance 10%)");

DELETE FROM `creature_text` WHERE `entry`=42387;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(42387,0,0,'Did you... Did you meet her?',12,0,100,0,0,0,'Thug 1'),
(42387,1,0,'Yep. She\'s for real',12,0,100,0,0,0,'Thug 2'),
(42387,2,0,'She wanted me to tell you lugs that she appreciates the job that we did for her on the Furlbrows. gave me a pile o\' gold to split with you all. ',12,0,100,0,0,0,'Thug 2'),
(42387,3,0,'See her face? Is it really... ',12,0,100,0,0,0,'Thug 3'),
(42387,4,0,'Whoa, what do we have here? Looks like we have ourselves an eavesdropper, boys. ',12,0,100,0,0,0,'Thug 1'),
(42387,5,0,'Only one thing to do with a lousy, good-for-nothin eavesdropper.',12,0,100,0,0,0,'Thug 1'),
(42387,6,0,'DIE!',12,0,100,0,0,0,'Thug 1'),
(42387,7,0,'Hurry back to the Furlbrow\'s Cottage! ',41,0,100,0,0,0,'Emote');

DELETE FROM `areatrigger_scripts` WHERE `entry` = '5988';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(5988, 'at_thug_scene');

UPDATE `creature_template_addon` SET `auras`='' WHERE `entry`=42387;
UPDATE `creature` SET `spawntimesecs`=60 WHERE `id`=42387;
UPDATE `creature_template_addon` SET `auras`='80671 79372 29266' WHERE `entry`=42560;
UPDATE `creature_template_addon` SET `auras`='80671' WHERE `entry` IN (42559, 42558);
UPDATE `creature_template_addon` SET `auras`='80694' WHERE `entry`=42405;

-- Thug
SET @ENTRY := 42387;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,8,0,100,0,70290,1,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Set Faction 14"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,18,50,0,0,0.0,0.0,0.0,0.0,"Link - Attack Player"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,42387,50,0,0.0,0.0,0.0,0.0,"Link - Set Data 1 to other Thug"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,19,33554432,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Unselectable"),
(@ENTRY,@SOURCETYPE,4,5,38,0,100,0,0,1,0,0,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Faction 14"),
(@ENTRY,@SOURCETYPE,5,8,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,18,50,0,0,0.0,0.0,0.0,0.0,"Link - Attack Player"),
(@ENTRY,@SOURCETYPE,6,0,8,0,100,0,70290,1,0,0,33,42417,0,0,0,0,0,18,50,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Complete"),
(@ENTRY,@SOURCETYPE,7,0,7,0,100,0,0,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Despawn"),
(@ENTRY,@SOURCETYPE,8,0,61,0,100,0,0,0,0,0,19,33554432,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Unselectable");

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '80672';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(80672, -80695, 2, 'Quest Invis 2 -> Remove Quest Invis 1');

DELETE FROM `creature_text` WHERE `entry`IN (42558, 42559);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(42558,0,0,'Doesn\'t look good, rookie.',12,0,100,0,0,0,'Comment'),
(42558,1,0,'This was an execution. Whoever did this was sending a message.',12,0,100,0,0,0,'Comment'),
(42558,2,0,'A message for anyone that would dare snitch on these cirminals.',12,0,100,0,0,0,'Comment'),
(42558,3,0,'It would appear that poor Lou readlly did put his foot...',12,0,100,0,0,0,'Comment'),
(42558,4,0,'In his mouth.',12,0,100,0,0,0,'Comment'),
(42559,0,0,'You were standing right here! What the hell did you see? Speak up!',12,0,100,0,0,0,'Comment'),
(42559,1,0,'Natural causes? Two bullets in the chest and his shoes are on his head. What kind of natural death would that be?',12,0,100,0,0,0,'Comment');

DELETE FROM `areatrigger_scripts` WHERE `entry` = '5989';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(5989, 'at_horatio_laine_2');

-- Stormwind Investigator
SET @ENTRY := 42559;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

DELETE FROM `creature_text` WHERE `entry`IN (42308, 42309);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(42308,0,0,'No kidding, rookie...',12,0,100,0,0,0,'Comment'),
(42308,1,0,'Looks like they really put the cart...',12,0,100,0,0,0,'Comment'),
(42308,2,0,'...before the horse.',12,0,100,0,0,0,'Comment'),
(42309,0,0,'It\'s a bloodbath, lieutenant. They\'ve been murdered.',12,0,100,0,0,0,'Comment'),
(42309,1,0,'Given the body temperature, I\'d say they\'ve been dead no more than 6 hours.',12,0,100,0,0,0,'Comment'),
(42309,2,0,'Damn shame what they did to Old Blanchy...',12,0,100,0,0,0,'Comment');

DELETE FROM `areatrigger_scripts` WHERE `entry` = '5983';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(5983, 'at_horatio_laine_1');

-- Lieutenant Horatio Laine
SET @ENTRY := 42308;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,8,0,100,0,78935,1,0,0,69,0,0,0,0,0,0,8,0,0,0,-9852.53,910.04,29.92,5.11,"On Spellhit - Move to Pos"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,17,16,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Emote");

DELETE FROM `creature_addon` WHERE `guid` IN
(171569, 171568, 171484, 167848, 167849, 167847, 167850, 171570, 171571, 171572);
DELETE FROM `creature` WHERE `guid` IN
(171569, 171568, 171484, 167848, 167849, 167847, 167850, 171570, 171571, 171572);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` IN (42400, 42399);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(42400, 46598, 0),
(42399, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` IN (42400, 42399);
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`) VALUES
(42400, 42399, 1, 'West Plains Drifter -> Hobo Cart'),
(42399, 42403, 1, 'Hobo Cart -> Hobo Goods (Boots)');

-- Lieutenant Horatio Laine
SET @ENTRY := 42308;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,8,0,100,0,78935,1,0,0,69,0,0,0,0,0,0,8,0,0,0,-9852.53,910.04,29.92,5.11,"On Spellhit - Move to Pos"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,17,68,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Emote"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,0,0,0,0,12,42400,4,180000,0,0,0,8,0,0,0,-9804.99,840.79,29.2,2.27,"Link - Summon Creature 1"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,12,42383,4,180000,0,0,0,8,0,0,0,-9808.06,838.24,29.19,2.24,"Link - Summon Creature 2");

-- Transient
SET @ENTRY := 42383;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,11,0,100,1,0,0,0,0,11,79116,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Hobo Stick on Spawn"),
(@ENTRY,@SOURCETYPE,1,0,1,0,50,1,3000,3000,0,0,11,58511,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Rotten Apple Aroma on Spawn"),
(@ENTRY,@SOURCETYPE,2,0,1,0,50,1,3000,3000,0,0,11,58514,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Rotten Banana Aroma on Spawn"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,53,0,42383,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - WP Start"),
(@ENTRY,@SOURCETYPE,4,5,40,0,100,0,1,0,0,0,54,40000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - WP Pause"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,0,42383,0,0,45,0,1,0,0,0,0,11,42400,20,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Drifter"),
(@ENTRY,@SOURCETYPE,7,0,38,0,100,0,0,1,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 1"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,1,42383,0,0,45,0,2,0,0,0,0,11,42400,20,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 2 to Drifter"),
(@ENTRY,@SOURCETYPE,9,0,38,0,100,0,0,2,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 2"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,2,42383,0,0,45,0,3,0,0,0,0,11,42400,20,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 3 to Drifter"),
(@ENTRY,@SOURCETYPE,11,0,40,0,100,0,2,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - Force Despawn");

-- West Plains Drifter
SET @ENTRY := 42400;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,50,1,3000,3000,0,0,11,58511,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Rotten Apple Aroma on Spawn"),
(@ENTRY,@SOURCETYPE,1,0,1,0,50,1,3000,3000,0,0,11,58514,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Rotten Banana Aroma on Spawn"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,53,0,42400,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - WP Start"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,1,0,0,0,54,40000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - WP Pause"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,1,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,0,42400,0,0,45,0,1,0,0,0,0,11,42383,20,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Transient"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,0,0,2,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 1"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,1,42400,0,0,45,0,2,0,0,0,0,11,42383,20,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 2 to Transient"),
(@ENTRY,@SOURCETYPE,8,0,38,0,100,0,0,3,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 2"),
(@ENTRY,@SOURCETYPE,9,0,40,0,100,0,2,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - Force Despawn");

DELETE FROM `creature_text` WHERE `entry` IN (42400, 42383);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(42400,0,0,'Looks like the Furlbrow\'s were murdered...',12,0,100,0,0,0,'Comment'),
(42400,1,0,'Yep. That King Varian is good for nothin\'. ',12,0,100,0,0,0,'Comment'),
(42400,2,0,'Good call.',12,0,100,0,0,0,'Comment'),
(42383,0,0,'What the hell happened here?',12,0,100,0,0,0,'Comment'),
(42383,1,0,'What\'s happened to us? We\'re in worse shape now than when the Defias ran amok!',12,0,100,0,0,0,'Comment'),
(42383,2,0,'Let\'s get out of here before they try and pin this on us.',12,0,100,0,0,0,'Comment');

DELETE FROM `waypoints` WHERE `entry` IN (42383, 42400);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(42383, 1, -9847.15, 896.40, 29.09, 'Transient WP'),
(42383, 2, -9822.72, 852.80, 26.47, 'Transient WP'),
(42400, 1, -9845.42, 892.13, 28.63, 'West Plain Drifter WP'),
(42400, 2, -9819.33, 854.29, 26.55, 'West Plain Drifter WP');

UPDATE `creature_template_addon` SET `bytes1`=65544 WHERE `entry`=42308;

-- Stormwind Investigator
SET @ENTRY := 42309;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

-- Captain Alpert
SET @ENTRY := 42425;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

DELETE FROM `areatrigger_scripts` WHERE `entry` = '5998';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(5998, 'at_moonbrook_event');

DELETE FROM `creature_template_addon` WHERE `entry` = '42680';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(42680, '79192');

SET @CGUID := 798454;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+24;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 42384, 0, 1, 1, 0, 0, -11018.9, 1486.08, 43.2078, 4.9121, 300, 0, 0, 176, 0, 0, 0, 0, 0),
(@CGUID+1, 42384, 0, 1, 1, 0, 0, -11009.3, 1482.48, 43.9946, 3.65772, 300, 0, 0, 176, 0, 0, 0, 0, 0),
(@CGUID+2, 42384, 0, 1, 1, 0, 0, -11009.8, 1486.24, 43.9754, 3.97722, 300, 0, 0, 176, 0, 0, 0, 0, 0),
(@CGUID+3, 42384, 0, 1, 1, 0, 0, -11027.9, 1484.37, 43.1706, 6.09372, 300, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+4, 42384, 0, 1, 1, 0, 0, -11025.1, 1481.72, 43.0106, 5.80685, 300, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+5, 42384, 0, 1, 1, 0, 0, -11022.3, 1484.44, 43.1582, 5.48735, 300, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+6, 42384, 0, 1, 1, 0, 0, -11023.2, 1492.17, 43.169, 5.10035, 300, 0, 0, 176, 0, 0, 0, 0, 0),
(@CGUID+7, 42384, 0, 1, 1, 0, 0, -11025, 1489.53, 43.1671, 5.10035, 300, 0, 0, 176, 0, 0, 0, 0, 0),
(@CGUID+8, 42384, 0, 1, 1, 0, 0, -11011, 1490.92, 43.5443, 4.1666, 300, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+9, 42384, 0, 1, 1, 0, 0, -11016.1, 1491.42, 43.234, 4.7471, 300, 0, 0, 176, 0, 0, 0, 0, 0),
(@CGUID+10, 42384, 0, 1, 1, 0, 0, -11019.4, 1494.37, 43.201, 4.4276, 300, 0, 0, 176, 0, 0, 0, 0, 0),
(@CGUID+11, 42384, 0, 1, 1, 0, 0, -11015.4, 1495.25, 43.2196, 4.78495, 300, 0, 0, 176, 0, 0, 0, 0, 0),
(@CGUID+12, 42386, 0, 1, 1, 0, 0, -11026.7, 1487.2, 43.1825, 5.05198, 300, 0, 0, 176, 0, 0, 0, 0, 0),
(@CGUID+13, 42386, 0, 1, 1, 0, 0, -11031, 1485.57, 43.3272, 5.50198, 300, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+14, 42386, 0, 1, 1, 0, 0, -11027.9, 1489.52, 43.1748, 5.56048, 300, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+15, 42386, 0, 1, 1, 0, 0, -11020.9, 1488.2, 43.1978, 4.72796, 300, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+16, 42386, 0, 1, 1, 0, 0, -11016.4, 1488.27, 43.2592, 4.72796, 300, 0, 0, 176, 0, 0, 0, 0, 0),
(@CGUID+17, 42386, 0, 1, 1, 0, 0, -11013.7, 1488.31, 43.5764, 4.02146, 300, 0, 0, 176, 0, 0, 0, 0, 0),
(@CGUID+18, 42386, 0, 1, 1, 0, 0, -11022.5, 1490.35, 43.1778, 5.30846, 300, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+19, 42386, 0, 1, 1, 0, 0, -11018.7, 1491.51, 43.1957, 4.60196, 300, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+20, 42386, 0, 1, 1, 0, 0, -11021.4, 1494.83, 43.1951, 4.60196, 300, 0, 0, 176, 0, 0, 0, 0, 0),
(@CGUID+21, 42386, 0, 1, 1, 0, 0, -11023.3, 1495.39, 43.1887, 5.31746, 300, 0, 0, 176, 0, 0, 0, 0, 0),
(@CGUID+22, 42386, 0, 1, 1, 0, 0, -11027, 1492.84, 43.1704, 5.31746, 300, 0, 0, 176, 0, 0, 0, 0, 0),
(@CGUID+23, 42386, 0, 1, 1, 0, 0, -11012.5, 1494.29, 43.3482, 4.31608, 300, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+24, 42680, 0, 1, 1, 0, 0, -11016.2, 1479.73, 47.7952, 1.46223, 300, 0, 0, 42, 0, 0, 0, 0, 0);

UPDATE `creature_template_addon` SET `auras`='79116' WHERE `entry` IN (42384, 42386);

DELETE FROM `creature_text` WHERE `entry`=42680;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(42680,0,0,'Gather, brothers and sisters! Come, all, and listen! ',14,0,100,0,1,13904,'Comment'),
(42680,1,0,'Brothers. Sisters. We are ABANDONED - the orphaned children of Stormwind.',14,0,100,0,1,0,'Comment'),
(42680,2,0,'Our "king" sits atop his throne made of gold and shurgs at our plight!',14,0,100,0,1,0,'Comment'),
(42680,3,0,'Meanwhile, our children die of starvation on these very streets!',14,0,100,0,1,0,'Comment'),
(42680,4,0,'HIS war, not ours, cost us our livelihood. WE paid for the Alliance\'s victories with our blood and the blood of our loved ones! ',14,0,100,0,1,13909,'Comment'),
(42680,5,0,'The time has come, brothers and sisters, to stop this injustice! ',14,0,100,0,1,0,'Comment'),
(42680,6,0,'The government of Stormwind, of the ALLIANCE, must be made accountable for what it has done to us!',14,0,100,0,1,13905,'Comment'),
(42680,7,0,'Today, we are reborn! Today we take a stand as men and women, not nameless, faceless numbers!',14,0,100,0,1,13908,'Comment');

-- Shadowy Figure
SET @ENTRY := 42680;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,8,0,100,0,78935,1,0,0,33,42680,0,0,0,0,0,18,100,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Complete"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,19,33554432,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Unit Flag");

UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=11.411 WHERE `entry`=42677 AND `item`=58117;

DELETE FROM `creature_loot_template` WHERE `item` = '57935';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(114, 57935, 8.7495, 1, 0, 1, 1),
(33905, 57935, 0.0014, 1, 0, 1, 1),
(458, 57935, 0.0113, 1, 0, 1, 1);

DELETE FROM `creature_addon` WHERE `guid` = '772511';
DELETE FROM `creature` WHERE `guid` = '772511';
UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN (772510, 772509);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '42654';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`) VALUES
(42654, 42655, 1, 'Helix Lumbering Oaf -> Helix Gearbreaker');

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '42654';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(42654, 46598, 0);

DELETE FROM `creature_addon` WHERE `guid` = '772509';
INSERT INTO `creature_addon` (`guid`, `auras`) VALUES
(772509, '79531');

DELETE FROM `creature_text` WHERE `entry`=42655;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(42655,0,0,'The gnolls have failed, mistress.',12,0,100,0,0,0,'Comment'),
(42655,1,0,'But mistress, the admiral is sti...',12,0,100,0,0,0,'Comment'),
(42655,2,0,'Yes, mistress.',12,0,100,0,0,0,'Comment'),
(42655,3,0,'Moonbrook, mistress?',12,0,100,0,0,0,'Comment');

DELETE FROM `areatrigger_scripts` WHERE `entry` = '5994';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(5994, 'at_mortwake_event');

-- Agent Kearnen
SET @ENTRY := 7024;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,3000,3000,3000,3000,11,79525,2,0,0,0,0,11,42656,60,0,0.0,0.0,0.0,0.0,"Agent Kearnen - Sniper Shot"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,1,0,2500,0,0,0,0,18,70,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0");

-- Mercenary
SET @ENTRY := 42656;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,6,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,7024,65,0,0.0,0.0,0.0,0.0,"On Death - Set Data 1 to Kearnen"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,41,2000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

DELETE FROM `creature_text` WHERE `entry`=7024;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(7024,0,0,'Not a chance',15,0,100,0,0,0,'Comment'),
(7024,0,1,'Easy Peasy.',15,0,100,0,0,0,'Comment'),
(7024,0,2,'Headshot!',15,0,100,0,0,0,'Comment'),
(7024,0,3,'Got him!',15,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `mindmg`=16, `maxdmg`=23, `attackpower`=6, `dmg_multiplier`=5 WHERE `entry`=42656;

DELETE FROM `spell_script_names` WHERE `spell_id` = '79436';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(79436, 'spell_wake_harvest_golem');

UPDATE `creature_template` SET `VehicleId`=907, `spell1`=79425, `spell2`=79430 WHERE `entry`=42601;
UPDATE `creature_template` SET `mindmg`=14, `maxdmg`=22, `attackpower`=5 WHERE `entry`=42342;

-- Overloaded Harvest Golem
SET @ENTRY := 42601;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,86,46598,0,21,6,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cross Cast on Summoner"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Passive"),
(@ENTRY,@SOURCETYPE,2,0,28,0,100,0,0,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Force Despawn");

DELETE FROM `spell_script_names` WHERE `spell_id` = '79586';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(79586, 'spell_vision_of_the_past_deadmines');

UPDATE `creature_template` SET `VehicleId`=916, `modelid1`=11686, `speed_walk`=2, `speed_run`=2.14286, `InhabitType`=7 WHERE `entry`=42693;

DELETE FROM `waypoints` WHERE `entry` = '42693';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(42693, 1, -79.12, -744.42, 30.74, 'Vision of the Past WP'),
(42693, 2, -5.99, -820.62, 50.29, 'Vision of the Past WP'),
(42693, 3, -61.13, -850.43, 54.38, 'Vision of the Past WP'),
(42693, 4, -60.54, -830.53, 53.57, 'Vision of the Past WP');

DELETE FROM `world_quest_phases` WHERE `QuestId` = '26320';
INSERT INTO `world_quest_phases` (`QuestId`, `Phase`, `type`, `MapId`, `ZoneId`, `AreaId`, `Comment`) VALUES
(26320, 2, 4, 36, 1581, 1581, 'Quest ID: 26320 - Vision of the Past (ON AURA UPDATE)');

UPDATE `gameobject` SET `phaseMask`=3 WHERE `guid`=778924;
UPDATE `quest_template` SET `Flags`=4, `SpecialFlags`=2 WHERE `Id`=26320;

-- Vision of the Past
SET @ENTRY := 42693;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,1500,1500,1500,1500,86,79587,0,18,15,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Cross Cast Player"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Phase Event 2");

DELETE FROM `creature_text` WHERE `entry`=42693;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES (42693,0,0,'|cff00ccffFive years ago, in the heart of the Deadmines...|r',41,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `minlevel`=17, `maxlevel`=17, `faction_A`=1770, `faction_H`=1770, `mindmg`=34, `maxdmg`=48, `attackpower`=0, `dmg_multiplier`=5, `baseattacktime`=2000, `rangeattacktime`=2000, `unit_class`=2, `unit_flags`=64, `minrangedmg`=15, `maxrangedmg`=22, `rangedattackpower`=6, `spell1`=1459, `spell2`=15791, `spell3`=11921, `spell4`=12675 WHERE `entry`=42702;
UPDATE `creature_template` SET `minlevel`=32, `maxlevel`=32, `faction_A`=1770, `faction_H`=1770, `mindmg`=34, `maxdmg`=48, `attackpower`=0, `baseattacktime`=2000, `rangeattacktime`=2000, `minrangedmg`=33, `maxrangedmg`=49, `rangedattackpower`=12, `type_flags2`=2147483648, `spell1`=13730, `spell2`=9080, `spell3`=57846, `spell4`=32736 WHERE `entry`=42699;
UPDATE `creature_template` SET `minlevel`=17, `maxlevel`=17, `faction_A`=1770, `faction_H`=1770, `mindmg`=34, `maxdmg`=48, `attackpower`=0, `dmg_multiplier`=5, `baseattacktime`=2000, `rangeattacktime`=2000, `unit_class`=2, `unit_flags`=64, `minrangedmg`=15, `maxrangedmg`=22, `rangedattackpower`=6, `spell1`=12039, `spell2`=13864, `spell3`=22187 WHERE `entry`=42703;
UPDATE `creature_template` SET `minlevel`=17, `maxlevel`=17, `faction_A`=1770, `faction_H`=1770, `mindmg`=34, `maxdmg`=48, `attackpower`=0, `dmg_multiplier`=5, `baseattacktime`=2000, `rangeattacktime`=2000, `unit_class`=2, `unit_flags`=64, `minrangedmg`=15, `maxrangedmg`=22, `rangedattackpower`=6, `spell1`=78754, `spell2`=79610 WHERE `entry`=42701;
UPDATE `creature_template` SET `spell1`=6408, `mindmg`=1, `maxdmg`=2, `attackpower`=0, `dmg_multiplier`=1 WHERE `entry`=42698;
UPDATE `creature_template` SET `spell1`=3391, `spell2`=79618, `mindmg`=1, `maxdmg`=2, `attackpower`=0, `dmg_multiplier`=1 WHERE `entry`=42697;
UPDATE `creature_template` SET `ScriptName`='generic_creature' WHERE `entry` IN (42702, 42703, 42701, 42700);

DELETE FROM `creature_text` WHERE `entry` IN (42699, 42697, 42371);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(42699,0,0,'There\'s nowhere left to hide, VanCleef! The Defias are THROUGH!',14,0,100,0,0,0,'Comment'),
(42699,1,0,'We\'re here to finish this! Face us, coward!',12,0,100,0,0,0,'Comment'),
(42699,2,0,'Victory for the Alliance! Glory to Stormwind!',14,0,100,0,0,0,'Comment'),
(42699,3,0,'Let us return to Sentinel Hill, allies, and inform Gryan of VanCleef\'s demise! ',12,0,100,0,0,0,'Comment'),
(42697,0,0,'None may challenge the Brotherhood!',14,0,100,0,0,0,'Comment'),
(42697,1,0,'Lapdogs, all of you!',14,0,100,0,0,0,'Comment'),
(42697,2,0,'Fools! Our cause is righteous!',14,0,100,0,0,0,'Comment'),
(42697,3,0,'The Brotherhood shall prevail!',14,0,100,0,0,0,'Comment'),
(42371,0,0,'Daddy...',12,0,100,0,0,0,'Comment');

-- Vanessa VanCleef
SET @ENTRY := 42371;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,2,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,1,6000,6000,6000,6000,69,0,0,0,0,0,0,11,42697,100,0,0.0,0.0,0.0,0.0,"Update (5 secs) - Move To Dad"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,42371,0,0,45,0,3,0,0,0,0,11,42693,200,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 3 to Vision of the Past");

-- Alliance Warrior
SET @ENTRY := 42699;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,42699,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,1,42699,0,0,12,42697,4,300000,0,0,0,8,0,0,0,-62.77,-820.25,41.3,3.1,"After Talk 1 - Summon Edwin"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,2,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 2"),
(@ENTRY,@SOURCETYPE,4,5,52,0,100,0,2,42699,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,5,6,61,0,100,0,0,0,0,0,15,26320,0,0,0,0,0,18,200,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete"),
(@ENTRY,@SOURCETYPE,6,7,61,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-65.85,-838.13,41.06,4.72,"Link - Move Out"),
(@ENTRY,@SOURCETYPE,7,8,61,0,100,0,0,0,0,0,41,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn (5 secs)"),
(@ENTRY,@SOURCETYPE,8,0,61,0,100,0,0,0,0,0,12,42371,8,0,0,0,0,8,0,0,0,-62.77,-820.25,41.3,3.1,"Link - Summon Vanessa");

-- Edwin VanCleef
SET @ENTRY := 42697;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,8,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Summoner"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,1,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,2,0,100,1,74,75,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On 75% HP - Talk 1"),
(@ENTRY,@SOURCETYPE,3,3,2,0,100,1,49,50,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On 50% HP - Talk 4"),
(@ENTRY,@SOURCETYPE,4,0,2,0,100,1,24,25,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On 25% HP - Talk 2"),
(@ENTRY,@SOURCETYPE,5,0,2,0,100,1,9,10,0,0,1,3,10000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On 10% HP - Talk 3"),
(@ENTRY,@SOURCETYPE,6,7,52,0,100,0,3,42697,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Die"),
(@ENTRY,@SOURCETYPE,7,0,61,0,100,0,0,0,0,0,45,0,2,0,0,0,0,11,42699,80,0,0.0,0.0,0.0,0.0,"Link - Set Data 2 to Alliance Warrior"),
(@ENTRY,@SOURCETYPE,8,0,61,0,100,0,0,0,0,0,12,42698,4,60000,0,0,0,8,0,0,0,0.0,0.0,0.0,0.0,"Link - Summon Guard");

-- Vision of the Past
SET @ENTRY := 42693;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,1500,1500,1500,1500,86,79587,0,18,15,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Cross Cast Player"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Phase Event 2"),
(@ENTRY,@SOURCETYPE,2,0,27,0,100,0,0,0,0,0,53,0,42693,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - WP Start"),
(@ENTRY,@SOURCETYPE,3,0,27,0,100,0,0,0,0,0,1,0,1000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,40,0,100,0,4,0,0,0,45,0,1,0,0,0,0,11,42699,80,0,0.0,0.0,0.0,0.0,"On WP Reached 4 - Set Data 1 to Alliance Warrior"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,3,0,0,28,79587,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Remove Vehicle"),
(@ENTRY,@SOURCETYPE,6,0,28,0,100,0,0,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Force Despawn");

-- Defias Blackguard
SET @ENTRY := 42698;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,20000,20000,20000,20000,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - 20 secs Die");

SET @CGUID := 798479;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+5;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 42700, 36, 1, 2, 0, 1, -60.7727, -815.467, 41.4911, 3.42506, 300, 0, 0, 1158, 0, 0, 0, 0, 0),
(@CGUID+1, 42703, 36, 1, 2, 0, 1, -58.3812, -817.687, 41.7292, 3.08895, 300, 0, 0, 1050, 3900, 0, 0, 0, 0),
(@CGUID+2, 42701, 36, 1, 2, 0, 1, -59.0087, -813.219, 41.6621, 3.72683, 300, 0, 0, 1050, 3900, 0, 0, 0, 0),
(@CGUID+3, 42702, 36, 1, 2, 0, 1, -60.2679, -823.41, 41.5549, 3.13778, 300, 0, 0, 1050, 3900, 0, 0, 0, 0),
(@CGUID+4, 42699, 36, 1, 2, 0, 1, -62.7755, -820.251, 41.3009, 3.10637, 300, 0, 0, 6342, 0, 0, 0, 0, 0),
(@CGUID+5, 42693, 36, 1, 2, 0, 0, -95.8487, -702.043, 8.82292, 4.72114, 300, 0, 0, 42, 0, 0, 16777216, 0, 0);

DELETE FROM `creature_text` WHERE `entry` IN (234, 42575, 42635, 42744);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(234,0,0,'The People of Westfall salute $N, a brave and valiant defender of freedom.',12,7,100,0,0,0,'Marshal Gryan Stoutmantle'),
(234,1,0,'I don\'t like this, $n. Stay alert!',12,0,100,0,0,0,'Comment'),
(234,2,0,'Hope! Wha..',12,0,100,0,0,0,'Comment'),
(234,3,0,'...get to Stormwind. Tell King Wrynn everything. EVERYTHING! GO NOW!',12,0,100,0,0,0,'Comment'),
(42575,0,0,'You bastards will burn for what you did. ',12,0,100,0,0,0,'Comment'),
(42575,1,0,'Hope? Is that what I was supposed to feel when I saw my father decapitated by your henchmen?',12,0,100,0,0,0,'Comment'),
(42575,2,0,'Hope is a cruel joke, played upon us by a harsh and uncaring world. There is no Hope, there is only Vanessa. Vanessa VanCleef.',12,0,100,0,0,0,'Comment'),
(42575,3,0,'RISE UP BROTHERHOOD! THE DAWNING DAY IS UPON US!',14,0,100,0,0,0,'Comment'),
(42575,4,0,'Tie them up.',12,0,100,0,0,0,'Comment'),
(42575,5,0,'Admiral, your hat.',12,0,100,0,0,0,'Comment'),
(42575,6,0,'And you... I will spare your life. You have done much to help our cause, albeit unwittingly, but the next time we meet it will be as enemies.',12,0,100,0,0,0,'Comment'),
(42575,7,0,'I had no choice, lieutenant. They recognized me. They only people in the world who even knew I existed, recognized my face from when I was an infant.',12,0,100,0,0,0,'Comment'),
(42575,8,0,'I took no pleasure in their deaths.',12,0,100,0,0,0,'Comment'),
(42575,9,0,'Leave nothing but ashes in your wake, brothers! Burn Sentinel Hill to the ground!',14,0,100,0,0,0,'Comment'),
(42635,0,0,'Thank you, my dear.',12,0,100,0,0,0,'Comment'),
(42744,0,0,'Just tell me one thing, Vanessa.',12,0,100,0,0,0,'Comment'),
(42744,1,0,'Why\'d you have the Furlbrows killed?',12,0,100,0,0,0,'Comment');

UPDATE `creature` SET `orientation`=1.925225 WHERE `guid`=172644;

DELETE FROM `waypoints` WHERE `entry` IN (42575, 234, 42635);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(42575, 1, -10507.19, 1041.25, 60.51, 'Hope WP'),
(234, 1, -10508.11, 1043.39, 60.51, 'Gryan WP'),
(42575, 2, -10512.03, 1045.65, 60.51, 'Vanessa WP'),
(42635, 1, -10515.34, 1059.83, 56.11, 'Ripsnarl WP'),
(42575, 3, -10513.30, 1056.45, 57.62, 'Vanessa WP'),
(42575, 4, -10512.37, 1055.41, 58.13, 'Vanessa WP'),
(42575, 5, -10515.34, 1059.83, 56.11, 'Vanessa WP');

UPDATE `creature` SET `phaseMask`=1 WHERE `id` IN (42771, 42793);
UPDATE `creature_template` SET `flags_extra`=128 WHERE `entry` IN (42771, 42793);

SET @CGUID := 798486;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+2;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 42745, 0, 1, 1, 0, 0, -10504.8, 1048.07, 60.5184, 4.52056, 300, 0, 0, 84, 0, 0, 0, 0, 0),
(@CGUID+1, 42745, 0, 1, 1, 0, 0, -10507.1, 1049.29, 60.5186, 4.39581, 300, 0, 0, 84, 0, 0, 0, 0, 0),
(@CGUID+2, 42744, 0, 1, 1, 0, 0, -10506.3, 1047.66, 60.5186, 4.39581, 300, 0, 0, 2865, 0, 0, 0, 0, 0);

-- Marshal Gryan Stoutmantle
SET @ENTRY := 234;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,20,0,100,0,166,0,0,0,1,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Marshal Gryan Stoutmantle - On quest The Defias Brotherhood rewarded - Say line"),
(@ENTRY,@SOURCETYPE,1,9,19,0,100,0,26322,0,0,0,1,1,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Accept Quest 26322 - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,1,234,0,0,45,0,2,0,0,0,0,10,172644,42575,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 2 to Hope"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,1,0,0,53,0,234,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Start WP"),
(@ENTRY,@SOURCETYPE,4,0,40,0,100,0,1,0,0,0,1,2,4000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Talk 2"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,2,234,0,0,45,0,3,0,0,0,0,10,172644,42575,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 3 to Hope"),
(@ENTRY,@SOURCETYPE,6,0,38,0,100,0,0,7,0,0,11,79724,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 7 - Tie up"),
(@ENTRY,@SOURCETYPE,7,0,8,0,100,0,79724,1,0,0,45,0,10,0,0,0,0,10,172644,42575,0,0.0,0.0,0.0,0.0,"On Spellhit - Set Data 10 to Vanessa"),
(@ENTRY,@SOURCETYPE,8,0,38,0,100,0,0,25,0,0,1,3,15000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 25 - Talk 3"),
(@ENTRY,@SOURCETYPE,9,0,61,0,100,0,0,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Npc Flag 0"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,3,234,0,0,45,0,35,0,0,0,0,10,772569,42793,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 35 to Fire Trigger"),
(@ENTRY,@SOURCETYPE,11,0,7,0,100,0,0,0,0,0,81,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Reset NPC Flag");

-- Hope Saldean
SET @ENTRY := 42575;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,2,0,0,53,0,42575,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Start WP"),
(@ENTRY,@SOURCETYPE,1,2,40,0,100,1,1,0,0,0,1,0,2000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,42575,0,0,45,0,1,0,0,0,0,10,172646,234,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Gryan"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,3,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 3 - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,42575,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,2,42575,0,0,11,79709,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Transform in Vanessa"),
(@ENTRY,@SOURCETYPE,6,0,8,0,100,0,79709,1,0,0,1,3,3500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 3"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,3,42575,0,0,45,0,5,0,0,0,0,11,42771,80,0,0.0,0.0,0.0,0.0,"After Talk 3 - Set Data 5 to Triggers"),
(@ENTRY,@SOURCETYPE,8,0,38,0,100,1,0,6,0,0,1,4,3500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 6 - Talk 4"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,4,42575,0,0,45,0,7,0,0,0,0,11,0,100,0,0.0,0.0,0.0,0.0,"After Talk 4 - Set Data 7 to Nearest Creatures (Tie up)"),
(@ENTRY,@SOURCETYPE,10,0,40,0,100,0,1,0,0,0,54,35000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 1 - WP Pause (35 secs)"),
(@ENTRY,@SOURCETYPE,11,0,40,0,100,0,2,0,0,0,1,5,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - Talk 5"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,0,5,42575,0,0,45,0,1,0,0,0,0,10,172484,42635,0,0.0,0.0,0.0,0.0,"After Talk 5 - Set Data 1 to Ripsnarl"),
(@ENTRY,@SOURCETYPE,13,0,38,0,100,0,0,11,0,0,1,6,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 11 - Talk 6"),
(@ENTRY,@SOURCETYPE,14,0,40,0,100,0,2,0,0,0,54,18000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - WP Pause (18 secs)"),
(@ENTRY,@SOURCETYPE,15,0,40,0,100,0,3,0,0,0,54,2000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 3 - WP Pause (2 secs)"),
(@ENTRY,@SOURCETYPE,16,0,38,0,100,0,0,20,0,0,1,7,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 20 - Talk 7"),
(@ENTRY,@SOURCETYPE,17,7,40,0,100,0,4,0,0,0,54,20000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 4 - WP Pause (20 secs)"),
(@ENTRY,@SOURCETYPE,18,0,52,0,100,0,7,42575,0,0,1,8,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 7 - Talk 8"),
(@ENTRY,@SOURCETYPE,19,21,52,0,100,0,8,42575,0,0,1,9,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 8 - Talk 9"),
(@ENTRY,@SOURCETYPE,20,0,40,0,100,0,3,0,0,0,45,0,15,0,0,0,0,11,42744,80,0,0.0,0.0,0.0,0.0,"On WP Reached 3 - Set Data 15 to Laine"),
(@ENTRY,@SOURCETYPE,21,0,61,0,100,0,0,0,0,0,15,26322,0,0,0,0,0,18,100,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete"),
(@ENTRY,@SOURCETYPE,22,0,40,0,100,0,5,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Wp Reached 5 - Force Despawn (1 sec)"),
(@ENTRY,@SOURCETYPE,23,0,40,0,100,0,5,0,0,0,45,0,25,0,0,0,0,10,172646,234,0,0.0,0.0,0.0,0.0,"On Wp Reached 5 - Set Data 25 to Gryan"),
(@ENTRY,@SOURCETYPE,24,0,40,0,100,0,5,0,0,0,45,0,25,0,0,0,0,11,42769,100,0,0.0,0.0,0.0,0.0,"On Wp Reached 5 - Set Data 25 to Blackguards");

-- Sentinel Hill Fire Trigger
SET @ENTRY := 42793;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,30,0,0,11,84788,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 30 - Cast Flames"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,1,0,35,0,0,70,0,0,0,0,0,0,11,0,95,0,0.0,0.0,0.0,0.0,"On Get Data 35 - Respawn Creatures (Reset Events)");

-- Lieutenant Horatio Laine
SET @ENTRY := 42744;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,7,0,0,11,79724,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 7 - Tie up"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,15,0,0,1,0,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 15 - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,42744,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,42744,0,0,45,0,20,0,0,0,0,10,172644,42575,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Data 20 to Vanessa");

-- Stormwind Investigator
SET @ENTRY := 42745;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,7,0,0,11,79724,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 7 - Tie up");

-- Rise of the Brotherhood Event Dummy
SET @ENTRY := 42771;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,5,0,0,11,79712,4,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 5 - Summon Blackguard");

-- Ripsnarl
SET @ENTRY := 42635;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,11,79745,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Return Human"),
(@ENTRY,@SOURCETYPE,1,0,8,0,100,0,79745,1,0,0,1,0,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,42635,0,0,53,0,42635,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Start WP"),
(@ENTRY,@SOURCETYPE,3,4,40,0,100,0,1,0,0,0,41,1500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 1 - Force Despawn (1.5 second)"),
(@ENTRY,@SOURCETYPE,4,0,61,0,100,0,0,0,0,0,45,0,11,0,0,0,0,10,172644,42575,0,0.0,0.0,0.0,0.0,"Link - Set Data 11 to Vanessa"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,1,0,0,28,69196,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Remove In Stocks");

-- Scout Galiaan
SET @ENTRY := 878;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,7,0,0,11,79724,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 7 - Tie up");

-- Captain Danuvin
SET @ENTRY := 821;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,7,0,0,11,79724,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 7 - Tie up");

-- Defias Blackguard
SET @ENTRY := 42769;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,79705,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Smoke"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,1,4000,4000,4000,4000,45,0,6,0,0,0,0,10,172644,42575,0,0.0,0.0,0.0,0.0,"Update (4 sec) - Set Data 6 to Vanessa"),
(@ENTRY,@SOURCETYPE,2,3,38,0,100,0,0,25,0,0,41,3000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 25 - Force Despawn (3 secs)"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,45,0,30,0,0,0,0,11,42793,200,0,0.0,0.0,0.0,0.0,"Link - Set Data 30 to Triggers for Fire");