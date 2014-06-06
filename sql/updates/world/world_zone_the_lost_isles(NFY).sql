UPDATE `creature_template` SET `ScriptName`='npc_geargrinder_gizmo_intro' WHERE `entry`=36600;
UPDATE `creature_template` SET `ScriptName`='npc_doc_zapnozzle_intro' WHERE `entry`=36608;

DELETE FROM `creature_text` WHERE `entry`=36608;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36608,0,0,'Gizmo, what are you doing just sittin there? Don\'t you recognize who that is laying next to you?!',12,0,100,1,0,0,'Comment'),
(36608,1,0,'That\'s $n, $G, the whole reason we\'re still breathing and not crispy fried critters back on Kezan.',12,0,100,1,0,0,'Comment'),
(36608,2,0,'Stay back, I\'m going to resuscitate him! I hope these wet jumper cables don\'t kill us all!',12,0,100,1,0,0,'Comment'),
(36608,3,0,'Come on! Clear!',12,0,100,1,0,0,'Comment'),
(36608,4,0,'Thats all I\'ve got. It\'s up to $g, now. You hear me, $n? Come on, snap out of it! Don\'t go into the Light!',12,0,100,1,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=36600;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36600,0,0,'That\'s $n?! Sorry, Doc. I thought he was dead!',12,0,100,1,0,0,'Comment');

UPDATE `creature_template` SET `InhabitType`=7 WHERE `entry`=36608;

DELETE FROM `creature_questrelation` WHERE `id` = '36608' AND `quest` = '14239';
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES
(36608, 14239);

DELETE FROM `creature_involvedrelation` WHERE `id` = '36608' AND `quest` = '14239';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(36608, 14239);

UPDATE `quest_template` SET `PrevQuestId`='14239' WHERE `Id`=14474;

UPDATE `creature_template` SET `mindmg`=12, `maxdmg`=18 WHERE `entry` IN 
(36153,36740,34699,35812,35838,35904,35891,36735,40064,40068,40067,39376,
36719,39193,39195,39194,38575,38574,38187,38359,38360,36681,36682,39069,39141,
39142,38811,38808,38845,35966,38224,36149,36621,36153,34763,36092,36732,36100,36103,36129);

UPDATE `creature_template` SET `InhabitType`=2 WHERE `entry` IN (34763, 36681, 36682);
UPDATE `creature` SET `spawndist`=14, `MovementType`=1 WHERE `id` IN (34763, 36681, 36682);

-- Daggertooth Shark
SET @ENTRY := 34763;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,6000,6000,15000,2000,11,69203,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Vicious Bite");

-- Teraptor Hatchling
SET @ENTRY := 36740;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,6268,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Rushing Charge");

-- Smart Mining Monkey
SET @ENTRY := 35812;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,38560,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Throw");

-- Pygmy Witchdoctor
SET @ENTRY := 35838;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,18503,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Hex"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,3100,3100,11,9613,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadow Bolt"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,10000,10000,10000,10000,11,11986,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Healing Wave");

-- Jungle Cat
SET @ENTRY := 35904;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,3500,5500,11,31289,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Claw");

-- SI:7 Infiltrator
SET @ENTRY := 35891;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,3000,5000,7500,11,15691,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Eviscerate");

-- Teraptor Matriarch
SET @ENTRY := 36735;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,3000,16500,16500,11,35321,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Gushing Wound"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,13500,13500,25000,35000,11,36629,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Terrifying Roar");

-- Jungle Panther
SET @ENTRY := 40064;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,75002,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Leaping Rush"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2500,2500,3500,3500,11,31289,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Claw"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,4000,4000,4000,4000,11,75930,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Mangle");

-- Venom Spitter
SET @ENTRY := 40068;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,74725,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Venom Spit"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,3500,3500,4000,6000,11,74726,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Shoot Thorns");

-- Iceeya
SET @ENTRY := 40067;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,74724,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Frostbolt"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,4000,4000,4000,4000,11,74724,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Frostbolt");

-- KTC Oil Bot
SET @ENTRY := 39376;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,4000,4000,11,73867,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Cutting Laser");

-- Dying Berserker
SET @ENTRY := 31273;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,31273,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Screech"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,10000,10000,10000,10000,11,31273,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Screech");

-- Brute Overseer
SET @ENTRY := 39193;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,1000,1000,5000,5000,11,76136,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Add Acidic Sweat"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,2000,6000,8000,11,3551,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Skull Crack");

-- Delicia Whipsnaps
SET @ENTRY := 39195;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,2000,5000,7000,11,75960,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Whiplash");

-- Blastshadow the Brutemaster
SET @ENTRY := 39194;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,3100,3100,11,9613,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadow Bolt"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,32063,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Corruption");

-- Oomlot Tribesman
SET @ENTRY := 38575;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,500,500,2500,3500,11,74613,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shoot");

-- Oomlot Shaman
SET @ENTRY := 38574;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,12550,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Lighting Shield"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,2000,6000,9000,11,13281,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Earth Shock");

-- Spiny Raptor
SET @ENTRY := 38187;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,3000,12500,12500,11,42320,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Head Butt");

-- Vashj'elan Warrior
SET @ENTRY := 38359;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2500,2500,5000,5000,11,57846,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Heroic Strike"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,8599,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Enrage");

-- Vashj'elan Siren
SET @ENTRY := 38360;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,500,500,8000,10000,11,11831,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Frost Nova"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,3100,3100,11,9672,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Frostbolt");

-- Ravenous Lurker
SET @ENTRY := 36681;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,2000,4500,6000,11,69203,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Vicious Bite");

-- Alliance Paratrooper
SET @ENTRY := 39069;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,500,500,2500,3500,11,6660,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shoot");

-- Commander Arrington
SET @ENTRY := 39141;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,79853,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Evasion"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,3500,4500,11,60842,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Expose Armor"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,2000,2000,4000,4000,11,79852,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Eviscerate"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,5000,5000,5000,5000,11,60195,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Sinister Strike"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,9500,9500,9500,9500,11,79851,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Fan of Knives");

-- Darkblade Cyn
SET @ENTRY := 39142;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,3583,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Deadly Poison"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,66060,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Sprint"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,1000,1000,3500,3500,11,60195,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Sinister Strike"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,5000,5000,5000,5000,11,60850,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Mutilate");

-- Oostan Headhunter
SET @ENTRY := 38811;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,500,500,2500,3500,11,84837,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shoot");

-- Gaahl
SET @ENTRY := 38808;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,3500,4000,11,12548,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Frost Shock"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,10000,10000,10000,10000,11,72935,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Zombie Transformation");

-- Child of Volcanoth
SET @ENTRY := 38845;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,3000,5000,5000,11,8873,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Flame Breath");

-- Mechachicken
SET @ENTRY := 38224;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5000,5000,5000,5000,11,71657,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Deadly Egg Barrage");

-- Alliance Sailor
SET @ENTRY := 36149;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,3500,3500,11,11976,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Strike");

-- Alliance Wizard
SET @ENTRY := 36621;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,4000,4000,6000,8000,11,11975,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Arcane Explosion"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,500,500,31000,31000,11,9053,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Fireball");

-- Alliance Captain
SET @ENTRY := 36153;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,13730,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Demoralizing Shout"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,5000,8000,11,7896,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Exploding Shot");

DELETE FROM `creature_text` WHERE `entry`=34748;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(34748,0,0,'Thanks, $n. You still owe me that money!',12,0,100,0,0,0,'Comment'),
(34748,0,1,'Blowing open my escape pod. I like your style, $n!',12,0,100,0,0,0,'Comment'),
(34748,0,2,'What were those Alliance ships doing firing at us?! Did I see a Horde ship, too?',12,0,100,0,0,0,'Comment'),
(34748,0,3,'$n? I heard you were dead. ',12,0,100,0,0,0,'Comment'),
(34748,0,4,'$n, it\'s you! Thanks!',12,0,100,0,0,0,'Comment'),
(34748,0,5,'What, are you crazy?! Trying to blow me to smithereens like that!',12,0,100,0,0,0,'Comment'),
(34748,0,6,'$n! Please tell me that monster, the Trade Prince, didn\'t survive?!',12,0,100,0,0,0,'Comment'),
(34748,0,7,'Couldn\'t you have just used a crowbar?',12,0,100,0,0,0,'Comment');

-- Goblin Survivor
SET @ENTRY := 34748;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,1,0,6000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,34748,0,0,46,30,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Move Forward"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,34748,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Run"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,34748,0,0,41,10000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Force Despawn"),
(@ENTRY,@SOURCETYPE,4,0,54,0,100,0,0,0,0,0,33,34748,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Quest Credit");

DELETE FROM `creature_text` WHERE `entry`=34736;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(34736,0,0,'Unfortunately a dead Goblin appears underwater...',42,0,100,0,0,0,'Comment'),
(34736,0,1,'A dead goblin, too late for him, that\'s sad!',42,0,100,0,0,0,'Comment'),
(34736,0,2,'Another poor goblin dead',42,0,100,0,0,0,'Comment'),
(34736,0,3,'Outch, last explosion was huge, you\'ve killed the survivor.',42,0,100,0,0,0,'Comment');

-- Goblin Survivor
SET @ENTRY := 34736;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,1,0,10000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,41,10000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Force Despawn");

UPDATE `gameobject_template` SET `data6`=60, `ScriptName`='go_goblin_escape_pod', `flags`=0 WHERE `entry`=195188;
UPDATE `gameobject_template` SET `data10`=0 WHERE `entry`=195188;
UPDATE `creature_template` SET `InhabitType`=7 WHERE `entry` IN (34748, 34736);
UPDATE `creature_template` SET `unit_flags`=1, `dynamicflags`=32 WHERE `entry`=34736;

DELETE FROM `creature_template_addon` WHERE `entry` = '34736';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(34736, 1, '58806');

DELETE FROM `spell_area` WHERE `spell` = '68258' AND `quest_start` = '14474';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(68258, 4721, 14474, 14474, 1, 10);

DELETE FROM `spell_area` WHERE `spell` = '68258' AND `quest_start` = '14001';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(68258, 4721, 14001, 14001, 1, 10);

DELETE FROM `spell_area` WHERE `spell` = '68256' AND `quest_start` = '14474';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(68256, 4721, 14474, 14474, 1, 10);

DELETE FROM `spell_area` WHERE `spell` = '68256' AND `quest_start` = '14001';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(68256, 4721, 14001, 14001, 1, 10);

DELETE FROM `creature_questrelation` WHERE `id`=36600 AND `quest`=14001;

-- Sassy Hardwrench
SET @ENTRY := 35650;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,14001,0,0,0,45,0,1,0,0,0,0,11,36403,60,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Set Data 1 to Gallywix"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,14014,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,19,0,100,0,14234,0,0,0,1,1,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 1");

DELETE FROM `creature_text` WHERE `entry`=36403;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36403,0,0,'You thought to take my place on Kezan? You reach too far! I made you what you were... were being the operative word. You\'re nothing now. Nothing!',14,0,100,0,0,0,'Comment'),
(36403,0,1,'Oh, I think we all know who\'s really responsible for the mess we\'re in! Don\'t worry, I\'m going to see what deserves!',14,0,100,0,0,0,'Comment'),
(36403,0,2,'I\'ve got my eye on you... Let\'s just say that only one of us will be leaving this island, and that goblin\'s name begins with Trade Prince!',14,0,100,0,0,0,'Comment');

-- Trade Prince Gallywix
SET @ENTRY := 36403;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0");

UPDATE `creature` SET `MovementType`=1 WHERE `id`=36719;
UPDATE `creature_template` SET `speed_walk`=1.4 WHERE `entry`=36719;
UPDATE `creature_template` SET `ScriptName`='npc_bomb_throwing_monkey' WHERE `entry`=34699;

DELETE FROM `creature_text` WHERE `entry`=35650;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(35650,0,0,'We need all of our bombs and tools to survive on this deserted island, $n.',12,0,100,0,0,0,'Comment'),
(35650,1,0,'We need some new friends if we\'re going to survive all of this. Hopefully, the orcs won\'t just kill you on sight.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=35786;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(35786,0,0,'$n, you gotta get those teraptor hatchlings before they get us!',12,0,100,0,0,0,'Comment'),
(35786,1,0,'Did you hear the matriarch growling up on the cliff? Stay clear of her!',12,0,100,0,0,0,'Comment');

-- Maxx Avalanche
SET @ENTRY := 35786;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,14473,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,35786,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1");

DELETE FROM `creature_text` WHERE `entry`=35758;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(35758,0,0,'These monkeys are going to get a kick out of those bananas!',12,0,100,0,0,0,'Comment'),
(35758,1,0,'That was the most beautiful thing that I\'ve ever seen!',12,0,100,0,0,0,'Comment');

-- Bamm Megabomb
SET @ENTRY := 35758;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,14019,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,35758,0,0,1,1,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1");

UPDATE `gameobject` SET `phaseMask`=32768 WHERE `guid` IN
(779403,780280,780288,780287,780255,780248,780249,780233,
780229,780232,780253,780243,780250,780248,779403,780247,
780263,780294,780235,780225,780268,780231,780071,780024,
780022,780060,780064,780020,780065,780055,780054,780052,
780051,780046,780045,780049,780047);

DELETE FROM `creature_text` WHERE `entry`=35813;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(35813,0,0,'Okay, here we go. You\'re gonna cover me, right?',12,0,100,0,0,0,'Comment'),
(35813,1,0,'Whoa! What\'s with all of the cave paintings? Ack, do I hear monkeys?!',12,0,100,0,0,0,'Comment'),
(35813,2,0,'I can\'t get anything else out of this one.',12,0,100,0,0,0,'Comment'),
(35813,2,1,'Did I ever tell you that I was a mid-level accountant with the company back on Kezan? I worked for you for years. Do you even know my name?',12,0,100,0,0,0,'Comment'),
(35813,2,2,'The monkeys already extracted most of the Kaja\'mite out of this deposit.',12,0,100,0,0,0,'Comment'),
(35813,2,3,'What I wouldn\'t give for some explosives right about now.',12,0,100,0,0,0,'Comment'),
(35813,3,0,'That\'s good enough for now. I\'ll make my way out on my own. Thanks for the escort, $n!',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `minlevel`=6, `maxlevel`=7, `mindmg`=13, `maxdmg`=19, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=35813;

DELETE FROM `spell_target_position` WHERE `id` = '68059';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(68059, 648, 487.22, 2979.44, 7.90, 6.09);

UPDATE `creature` SET `phaseMask`=32768 WHERE `guid` IN
(830532,830484,830531,830363,834005,833977,834003,830545,834118,830410,834034,831125,831106);

DELETE FROM `waypoints` WHERE `entry` = '35813';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(35813, 0, 515.75, 295.23, 7.92, 'Frightened Miner'),
(35813, 1, 526.55, 2962.07, 6.92, 'Frightened Miner'),
(35813, 2, 553.09, 2937.42, 1.49, 'Frightened Miner'),
(35813, 3, 566.60, 2935.68, 0.07, 'Frightened Miner'),
(35813, 4, 579.82, 2958.09, -1.77, 'Frightened Miner'),
(35813, 5, 588.22, 2963.97, -2.46, 'Frightened Miner'),
(35813, 6, 602.46, 2957.56, -5.11, 'Frightened Miner'),
(35813, 7, 577.50, 2918.82, -7.03 , 'Frightened Miner'),
(35813, 8, 576.69, 2907.07, -7.16, 'Frightened Miner'),
(35813, 9, 566.80, 2899.20, -8.94, 'Frightened Miner'),
(35813, 10, 579.17, 2879.93, -8.69, 'Frightened Miner'),
(35813, 11, 603.44, 2866.25, -6.56, 'Frightened Miner'),
(35813, 12, 607.73, 2857.95, -7.01, 'Frightened Miner'),
(35813, 13, 620.07, 2884.85, -4.61, 'Frightened Miner'),
(35813, 14, 627.02, 2920.15, -0.90, 'Frightened Miner'),
(35813, 15, 657.45, 2937.45, 0.24, 'Frightened Miner'),
(35813, 16, 666.40, 2947.31, -0.07, 'Frightened Miner'),
(35813, 17, 657.59, 2964.16, 1.50, 'Frightened Miner');

DELETE FROM `creature_text` WHERE `entry`=35769;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(35769,0,0,'On behalf of the Bilgewater Cratel, I lay claim to this mine!',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry`=35814;

-- Frightened Miner
SET @ENTRY := 35813;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,68064,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Summon Ore Cart"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,35813,0,0,19,4,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Remove Root"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,18,4,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Root"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,0,35813,0,0,53,0,35813,0,0,0,1,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - WP Start"),
(@ENTRY,@SOURCETYPE,5,0,56,0,100,0,0,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Resume - Set Walk"),
(@ENTRY,@SOURCETYPE,6,0,40,0,100,0,2,0,0,0,1,1,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - Talk 1"),
(@ENTRY,@SOURCETYPE,7,0,40,0,100,0,2,0,0,0,54,10000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 2 - WP Pause"),
(@ENTRY,@SOURCETYPE,8,0,40,0,100,0,5,0,0,0,54,8000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 5 - WP Pause"),
(@ENTRY,@SOURCETYPE,9,0,40,0,100,0,5,0,0,0,17,233,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 5 - Emote Mining"),
(@ENTRY,@SOURCETYPE,10,0,56,0,100,0,0,0,0,0,17,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Resume - Remove Mining"),
(@ENTRY,@SOURCETYPE,11,0,4,0,100,0,0,0,0,0,17,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Reset Emote"),
(@ENTRY,@SOURCETYPE,12,0,1,0,100,0,2000,2000,2000,2000,59,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Set Walk"),
(@ENTRY,@SOURCETYPE,13,0,4,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,14,0,40,0,100,0,8,0,0,0,54,8000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 8 - WP Pause"),
(@ENTRY,@SOURCETYPE,15,0,40,0,100,0,8,0,0,0,17,233,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 8 - Emote Mining"),
(@ENTRY,@SOURCETYPE,16,0,40,0,100,0,12,0,0,0,54,8000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 12 - WP Pause"),
(@ENTRY,@SOURCETYPE,17,0,40,0,100,0,12,0,0,0,17,233,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 12 - Emote Mining"),
(@ENTRY,@SOURCETYPE,18,0,40,0,100,0,12,0,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 12 - Talk 2"),
(@ENTRY,@SOURCETYPE,19,0,40,0,100,0,16,0,0,0,54,8000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 16 - WP Pause"),
(@ENTRY,@SOURCETYPE,20,0,40,0,100,0,16,0,0,0,17,233,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 16 - Emote Mining"),
(@ENTRY,@SOURCETYPE,21,0,40,0,100,0,17,0,0,0,54,15000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 17 - WP Pause"),
(@ENTRY,@SOURCETYPE,22,0,40,0,100,0,17,0,0,0,33,35816,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 17 - Quest Complete"),
(@ENTRY,@SOURCETYPE,23,0,40,0,100,0,17,0,0,0,1,3,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 17 - Talk 3"),
(@ENTRY,@SOURCETYPE,24,0,52,0,100,0,3,35813,0,0,41,3000,0,0,0,0,1,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Despawn");

-- Miner Troubles Ore Cart
SET @ENTRY := 35814;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,1000,1000,5000,5000,0,68122,32,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Chain Owner"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,11,68065,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Transform Self");

-- Foreman Dampwick
SET @ENTRY := 35769;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,14021,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,35769,0,0,85,68062,32,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Miner Controller");

UPDATE `creature_template` SET `unit_flags`=0, `unit_flags2`=2048, `dynamicflags`=0 WHERE `entry`=35810;
UPDATE `creature_template` SET `scale`=1.5 WHERE `entry`=37895;

DELETE FROM `spell_area` WHERE `spell` = '70661' AND `quest_start` = '14031';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(70661, 4778, 14031, 14031, 1, 8);

DELETE FROM `spell_area` WHERE `spell` = '70678' AND `quest_start` = '14031';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(70678, 4778, 14031, 14031, 1, 8);

DELETE FROM `spell_area` WHERE `spell` = '70680' AND `quest_start` = '14031';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(70680, 4778, 14031, 14031, 1, 8);

DELETE FROM `spell_area` WHERE `spell` = '70681' AND `quest_start` = '14031';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(70681, 4778, 14031, 14031, 1, 8);

DELETE FROM `spell_script_names` WHERE `spell_id` = '68280';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(68280, 'spell_ktc_snapflash');

DELETE FROM `creature_text` WHERE `entry`=35875;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(35875,0,0,'Kilag Gorefang should be down the path to the west, goblin.',12,0,100,0,0,0,'Comment'),
(35875,1,0,'Head back through the vale and meetup with Kilag at the Wild Overlook.',12,0,100,0,0,0,'Comment');

-- Aggra
SET @ENTRY := 35875;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,14235,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,14237,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 1");

-- Orc Scout
SET @ENTRY := 35894;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,4500,2000,4500,11,15620,0,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shoot"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible");

-- Kilag Gorefang
SET @ENTRY := 35893;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3500,3500,3500,3500,11,15620,0,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shoot"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,14236,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,3,0,20,0,100,0,14236,0,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Talk 1");

DELETE FROM `creature_text` WHERE `entry`=35893;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(35893,0,0,'Use your weed whacker to mow down these plants, little goblin!',12,0,100,0,0,0,'Comment'),
(35893,1,0,'Go back to Aggra and tell her that we\'re moving northwest.',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `unit_flags`=4 WHERE `entry` IN (35893, 35894);

DELETE FROM `spell_area` WHERE `spell` = '68212' AND `quest_start` = '14236';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(68212, 4780, 14236, 14236, 1, 10);

UPDATE `creature` SET `phaseMask`=32768 WHERE `guid` IN (830462, 830461);

-- Freezya
SET @ENTRY := 35897;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3500,6500,3500,6500,11,68209,0,0,0,0,0,10,830458,35893,0,0.0,0.0,0.0,0.0,"IC - Cast Frostbolt");

-- Poison Spitter
SET @ENTRY := 35896;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,65,0,5000,12500,5000,12500,11,68207,32,0,0,0,0,18,10,0,0,0.0,0.0,0.0,0.0,"IC - Cast Poison Spit"),
(@ENTRY,@SOURCETYPE,1,0,0,0,65,0,3500,7500,3500,7500,11,68208,0,0,0,0,0,18,10,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shoot Thorns"),
(@ENTRY,@SOURCETYPE,2,0,0,0,65,0,5000,12500,5000,12500,11,68207,32,0,0,0,0,11,35894,80,0,0.0,0.0,0.0,0.0,"IC - Cast Poison Spit");

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '-68376';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES
(-68376, -69303, 0, 'Infrared Heat Focals');

DELETE FROM `creature_text` WHERE `entry`=35917;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(35917,0,0,'Use your Infrared Heat Focals!',42,0,100,0,0,0,'Comment'),
(35917,1,0,'Don\'t forget to keep your goggles on, $n. That\'s the only way we\'ll spot them before they can jump us.',12,0,100,0,0,0,'Comment');

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '10708';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(10708, 'Kilag, I... uh, somhow... er, lost my scout.', 1, 1);

DELETE FROM `conditions` WHERE `SourceGroup`=10708 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10708, 0, 0, 0, 9, 0, 14238, 0, 0, 0, 0, 0, '', 'Kilag Gorefang - Show gossip only if quest 14238 is active');

-- Orc Scout
SET @ENTRY := 36100;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,1,0,6,0,100,0,0,0,0,0,28,68338,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Death - Remove Auras"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,11,69305,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Battle Shout"),
(@ENTRY,@SOURCETYPE,3,0,4,0,100,0,0,0,0,0,11,100,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Charge"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,1000,1000,5000,8000,11,11977,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Rend"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,2500,2500,3500,3500,11,25710,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Heroic Strike"),
(@ENTRY,@SOURCETYPE,6,0,0,0,100,0,4000,4000,4000,4000,11,8078,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Thunderclap");

UPDATE `creature_template` SET `ScriptName`='npc_kilag_gorefang' WHERE `entry`=35917;
UPDATE `creature_template` SET `minlevel`=8, `maxlevel`=8, `speed_run`=1.90286, `VehicleId`=530, `unit_flags`=768, `scale`=1 WHERE `entry`=36585;

DELETE FROM `waypoints` WHERE `entry` = '36585';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(36585, 0, 865.42, 2840.65, 103.14, 'Bastia WP'),
(36585, 1, 878.88, 2872.45, 100.69, 'Bastia WP'),
(36585, 2, 903.95, 2880.16, 100.02, 'Bastia WP'),
(36585, 3, 920.82, 2904.82, 101.15, 'Bastia WP'),
(36585, 4, 942.72, 2926.20, 106.80, 'Bastia WP'),
(36585, 5, 952.95, 2946.53, 109.60, 'Bastia WP'),
(36585, 6, 1005.17, 2949.67, 108.30, 'Bastia WP'),
(36585, 7, 1037.62, 2954.95, 110.49, 'Bastia WP'),
(36585, 8, 1074.25, 3006.83, 118.83, 'Bastia WP'),
(36585, 9, 1076.20, 3025.06, 121.75, 'Bastia WP'),
(36585, 10, 1089.02, 3040.05, 123.06, 'Bastia WP'),
(36585, 11, 1087.68, 3062.37, 123.75, 'Bastia WP'),
(36585, 12, 1068.84, 3102.58, 125.27, 'Bastia WP'),
(36585, 13, 1024.92, 3130.90, 124.73, 'Bastia WP'),
(36585, 14, 1021.09, 3163.78, 120.61, 'Bastia WP'),
(36585, 15, 1055.73, 3195.78, 113.88, 'Bastia WP'),
(36585, 16, 1059.37, 3223.76, 97.82, 'Bastia WP'),
(36585, 17, 1073.93, 3232.63, 86.41, 'Bastia WP'),
(36585, 18, 1079.07, 3240.43, 81.09, 'Bastia WP'),
(36585, 19, 1055.37, 3257.11, 57.09, 'Bastia WP');

-- Bastia
SET @ENTRY := 36585;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,53,1,36585,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,40,0,100,0,18,0,0,0,28,68974,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 18 - Remove Passenger"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,18,0,0,0,54,3500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 18 - WP Pause"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,19,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 19 - Force Despawn");

DELETE FROM `creature_text` WHERE `entry`=36112;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36112,0,0,'Get to the gyrochoppa! Do it now!',14,0,100,0,5,0,'Comment');

-- Scout Brax
SET @ENTRY := 36112;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,14241,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0");

-- Orc Battlesworn
SET @ENTRY := 36104;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,42,105,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible");

-- Kilag Gorefang
SET @ENTRY := 36117;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,42,260,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible");

-- Aggra
SET @ENTRY := 36115;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,42,193,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible");

UPDATE `creature_template` SET `minlevel`=10, `maxlevel`=10, `speed_run`=2.14286, `unit_flags`=768, `VehicleId`=505, `InhabitType`=4 WHERE `entry`=36143;

DELETE FROM `waypoints` WHERE `entry` = '36143';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(36143, 1, 849.75, 3365.22, 19.40, 'Gyrochoppa WP'),
(36143, 2, 795.43, 3535.90, 78.13, 'Gyrochoppa WP'),
(36143, 3, 817.09, 3686.08, 67.92, 'Gyrochoppa WP'),
(36143, 4, 939.61, 3901.41, 63.53, 'Gyrochoppa WP'),
(36143, 5, 1066.39, 3906.44, 83.99, 'Gyrochoppa WP'),
(36143, 6, 1108.26, 3751.60, 56.94, 'Gyrochoppa WP'),
(36143, 7, 971.79, 3803.18, 15.25, 'Gyrochoppa WP');

-- Gyrochoppa
SET @ENTRY := 36127;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,14242,0,0,0,85,68386,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Accept Quest - Summon Gyrochoppa");

DELETE FROM `creature_text` WHERE `entry`=36143;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36143,0,0,'Find the Precious Cargo!',42,0,100,0,0,0,'Comment');

-- Gyrochoppa
SET @ENTRY := 36143;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,53,1,36143,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,40,0,100,0,7,0,0,0,11,69081,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Quest Credit and Explosion"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,7,0,0,0,11,69081,0,0,0,0,0,18,15,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Quest Credit and Explosion"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,7,0,0,0,1,0,1500,0,0,0,0,23,15,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,0,36143,0,0,28,68387,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Remove Passenger");

UPDATE `creature_template` SET `unit_flags`=0, `unit_flags2`=2048, `dynamicflags`=0 WHERE `entry` IN (36176, 36621);

DELETE FROM `creature_addon` WHERE `guid` IN (831240,831236,831242,831246,831247,831237,831238,831235,831243);
INSERT INTO `creature_addon` (`guid`, `bytes2`, `auras`) VALUES
(831240, 1, '57685'),
(831236, 1, '57685'),
(831242, 1, '57685'),
(831246, 1, '57685'),
(831247, 1, '57685'),
(831237, 1, '57685'),
(831238, 1, '57685'),
(831235, 1, '57685'),
(831243, 1, '57685');

-- Chawg
SET @ENTRY := 36464;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,42,115,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible");

UPDATE `gameobject` SET `phaseMask`=128 WHERE `guid`=780188;
UPDATE `gameobject` SET `phaseMask`=128 WHERE `id` IN
(196822,196823,196820,196821,196825,196826,196824,196828,196827,196818,196819);
UPDATE `creature` SET `phaseMask`=128 WHERE `guid` IN (831240, 831284);
UPDATE `creature` SET `phaseMask`=128 WHERE `id`=36176;
UPDATE `creature_template` SET `ScriptName`='npc_thrall_ship_1' WHERE `entry`=36145;
UPDATE `creature` SET `phaseMask`=2 WHERE `id` IN (36149,36145);
UPDATE `creature` SET `phaseMask`=2 WHERE `guid`=831190;
UPDATE `gameobject` SET `phaseMask`=2 WHERE `guid`=780198;

UPDATE `conditions` SET `ConditionTypeOrReference`=28, `ConditionValue1`=14326 WHERE  `SourceTypeOrReferenceId`=25 AND `SourceGroup`=4720 AND `SourceEntry`=13 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=14242 AND `ConditionValue2`=0 AND `ConditionValue3`=0;
UPDATE `phase_definitions` SET `comment`='Lost Isle: Negate Phase After Quest Accept: 14326' WHERE  `zoneId`=4720 AND `entry`=13;

DELETE FROM `phase_definitions` WHERE `zoneId` = '4720' AND `entry` = '29';
INSERT INTO `phase_definitions` (`zoneId`, `entry`, `phasemask`, `flags`, `comment`) VALUES
(4720, 29, 2, 4, 'Lost Isle: Negate Phase After Quest: 14326');

SET @ZONE := 4720;
SET @ENTRY := 29;
SET @QUEST := 14326;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 25 AND `SourceGroup` = @ZONE AND `SourceEntry` = @ENTRY AND `ConditionValue1` = @QUEST;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(25, @ZONE, @ENTRY, 0, 0, 8, 0, @QUEST, 0, 0, 0, 0, 0, '', '');

-- Alliance Sailor
SET @ENTRY := 36176;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,500,500,3500,6500,17,431,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Set Cower"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,500,500,3500,6500,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Set Passive");

UPDATE `creature` SET `phaseMask`=128 WHERE `id`=36177;
UPDATE `creature_template` SET `AIName`='', `ScriptName`='npc_thrall_lightning_trigger' WHERE `entry`=36177;
UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `speed_run`=1.75286, `unit_flags`=0, `InhabitType`=4, `VehicleId`=508, `ScriptName`='npc_cyclone_of_the_elements' WHERE `entry`=36178;

DELETE FROM `script_waypoint` WHERE `entry` = '36178';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(36178, 1, 1007.73, 3837.32, 27.15, 'Cyclone of the Elements WP'),
(36178, 2, 1059.74, 3877.18, 29, 'Cyclone of the Elements WP'),
(36178, 3, 1106.35, 3852.30, 29, 'Cyclone of the Elements WP'),
(36178, 4, 1106.35, 3759.15, 29, 'Cyclone of the Elements WP'),
(36178, 5, 1068.54, 3713.44, 29, 'Cyclone of the Elements WP'),
(36178, 6, 1013.43, 3757.19, 29, 'Cyclone of the Elements WP'),
(36178, 7, 1025.46, 3836.35, 29, 'Cyclone of the Elements WP'),
(36178, 8, 1007.21, 3874.73, 29, 'Cyclone of the Elements WP'),
(36178, 9, 970.51, 3882.97, 29, 'Cyclone of the Elements WP'),
(36178, 10, 915.65, 3832.55, 29, 'Cyclone of the Elements WP'),
(36178, 11, 943.93, 3741.95, 29, 'Cyclone of the Elements WP'),
(36178, 12, 1004.00, 3756.55, 29, 'Cyclone of the Elements WP'),
(36178, 13, 990.72, 3790.60, 237.72, 'Cyclone of the Elements WP'),
(36178, 14, 991.75, 3330.56, 237.72, 'Cyclone of the Elements WP'),
(36178, 15, 991.07, 3021.47, 149.05, 'Cyclone of the Elements WP'),
(36178, 16, 907.54, 2937.86, 130.90, 'Cyclone of the Elements WP'),
(36178, 17, 869.08, 2831.92, 120.51, 'Cyclone of the Elements WP'),
(36178, 18, 872.40, 2766.31, 121.54, 'Cyclone of the Elements WP');

UPDATE `creature_template` SET `ScriptName`='npc_sassy_rocket' WHERE `entry`=36425;

DELETE FROM `creature_text` WHERE `entry`=36513;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36513,0,0,'You think you\'re such a bigshot, saving everyone and making friends with these orc savages?!',14,0,100,0,5,19584,'Comment'),
(36513,1,0,'I\'m going to crush you! I\'m the Trade Prince! Me! I\'ve got a plan that\'s going to get me off this island and make me the king of Azshara!',14,0,100,0,5,19585,'Comment'),
(36513,2,0,'Mark my words! I\'m going to get you, $n! I\'ll get you all! Out of my way!',14,0,100,0,5,19586,'Comment');

DELETE FROM `creature_template_addon` WHERE `entry` = '36513';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(36513, 1, '60191');

DELETE FROM `creature_template_addon` WHERE `entry` = '36514';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(36514, 1, '60191');

DELETE FROM `creature_template_addon` WHERE `entry` = '36505';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(36505, 1, '60191');

UPDATE `creature_template` SET `InhabitType`=4, `ScriptName`='npc_sling_rocket_tradeprince' WHERE `entry`=36514;
UPDATE `creature_template` SET `InhabitType`=4, `ScriptName`='npc_sling_rocket_player', `VehicleId`=524 WHERE `entry`=36505;

-- Trade Prince Gallywix
SET @ENTRY := 36513;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,1,0,9000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,36513,0,0,1,1,12000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,1,36513,0,0,1,2,7500,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,2,36513,0,0,69,0,0,0,0,0,0,8,0,0,0,870.78,2743.58,122.55,6.0,"After Talk 2 - Move To Rocket"),
(@ENTRY,@SOURCETYPE,4,0,34,0,100,0,8,0,0,0,85,68817,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Summon Rocket"),
(@ENTRY,@SOURCETYPE,5,0,34,0,100,0,8,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Force Despawn");

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=10808 AND `id`=0;

DELETE FROM `conditions` WHERE `SourceGroup`=10808 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 10808, 0, 0, 0, 9, 0, 14244, 0, 0, 0, 0, 0, '', 'Sling Rocket - Allow only if quest 14244 is active');

-- Rocket Sling
SET @ENTRY := 196439;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,10808,0,0,0,85,68804,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Sling Rocket"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,10808,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip");

DELETE FROM `creature_text` WHERE `entry`=36470;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36470,0,0,'Hurry, $n, deploy the Town-In-A-Box. Our people are trapped inside! Oh! I almost forgot your parachute.',12,0,100,0,0,0,'Comment');

-- Foreman Dampwick
SET @ENTRY := 36470;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,14245,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0");

DELETE FROM `conditions` WHERE `SourceEntry` = '25203' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 25203, 25200, 0),
(20, 8, 25203, 25201, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25203' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 25203, 25200, 0),
(19, 8, 25203, 25201, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25202' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 25202, 25200, 0),
(20, 8, 25202, 25201, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25202' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 25202, 25200, 0),
(19, 8, 25202, 25201, 0);

UPDATE `quest_template` SET `PrevQuestId`='25213' WHERE `Id`=25244;

DELETE FROM `creature_text` WHERE `entry`=36471;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36471,0,0,'Hobart\'s right behind you!',12,0,100,0,0,0,'Comment');

-- Foreman Dampwick
SET @ENTRY := 36471;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,27139,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0");

DELETE FROM `spell_script_names` WHERE `spell_id` = '71170';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(71170, 'spell_remote_control_fireworks');

UPDATE `creature_template` SET `ScriptName`='npc_wild_clucker' WHERE `entry`=38111;

DELETE FROM `creature_text` WHERE `entry`=38122;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38122,0,0,'Hey, come over here, would ya? I\'ve got something for you to do.',12,0,100,0,0,0,'Comment');

-- Bamm Megabomb
SET @ENTRY := 38122;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,20,0,100,0,24741,0,0,0,45,0,1,0,0,0,0,10,831656,38120,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Set Data 1 to Hobart");

UPDATE `creature` SET `phaseMask`=32768 WHERE `id` = '38187' AND `MovementType` = '0';
UPDATE `gameobject` SET `phaseMask`=32768 WHERE `id`=201974;
UPDATE `creature_template` SET `unit_flags`=772, `ScriptName`='npc_wild_clucker_egg' WHERE `entry`=38195;
UPDATE `creature_template` SET `ScriptName`='npc_spiny_raptor' WHERE `entry`=38187;

DELETE FROM `creature_template_addon` WHERE `entry` = '38195';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(38195, 1, '71355');

UPDATE `gameobject_template` SET `flags`=4 WHERE `entry`=201972;

DELETE FROM `spell_script_names` WHERE `spell_id` = '56576';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(56576, 'spell_wild_clucker_eggs');

UPDATE `gameobject` SET `spawntimesecs`=60 WHERE `id`=201972;
UPDATE `creature` SET `spawndist`=5, `MovementType`=1 WHERE `id` = '38187';

UPDATE `creature` SET `phaseMask`=32768 WHERE `guid` IN
(831949,831720,832376,832166,831730,831953,832160,832247,
832370,832243,831721,832249,832242,832384,832240,832375,
831775,832378,832385,832387,831707,831706,831764,832159,
832161,831776,832360,832252,832190,831715,832246,832150,
831717,832955,832177,832169,831926,831588,831585,831944,
831695,831948,831523,830493,831946,831691,831699,831700,
831935,830564,832154,832052,832050,832121,831968,832123,
831991,831994,831993,831998,832146,832014,832141,832027,
832015);

UPDATE `gameobject` SET `phaseMask`=32768 WHERE  `guid`=780027;

-- Mechachicken
SET @ENTRY := 38224;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,500,500,3100,3100,11,71657,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Deadly Egg Barrage"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,18,4,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Root"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,500,500,5000,5000,11,95913,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Set Sound"),
(@ENTRY,@SOURCETYPE,3,0,1,0,100,0,500,500,5000,5000,11,95914,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Set Sound 2"),
(@ENTRY,@SOURCETYPE,4,0,1,0,100,0,500,500,5000,5000,11,71423,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Set Overload"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,4000,4000,4000,4000,11,71417,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Egg Bomb"),
(@ENTRY,@SOURCETYPE,6,0,0,0,100,0,5000,7500,5000,7500,11,71417,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Egg Bomb"),
(@ENTRY,@SOURCETYPE,7,0,6,0,100,0,0,0,0,0,2,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Set Friendly"),
(@ENTRY,@SOURCETYPE,8,0,6,0,100,0,0,0,0,0,50,201977,60,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Summon the Biggest Egg");

UPDATE `gameobject` SET `phaseMask`=32768 WHERE `guid`=780025;

DELETE FROM `creature_text` WHERE `entry`=38120;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38120,0,0,'Over here if you please.',12,0,100,0,0,0,'Comment'),
(38120,1,0,'Don\'t\' underestimate the Mechachicken, $n, Afterall, it is a Hobard Grapplehammer invention!',12,0,100,0,0,0,'Comment'),
(38120,2,0,'Greely, load The Biggest Egg Ever in the Pultryizer. Mechanuggets for everyone!',14,0,100,0,0,0,'Comment'),
(38120,3,0,'Shut it down, shut it down! The eggs are bad!!!',14,0,100,0,0,0,'Comment'),
(38120,4,0,'The marketing research Megs has conducted suggests that a naga invasion is imminent!',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=38124;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38124,0,0,'Genius idea, sir. Your brain power never ceases to amaze me!',14,0,100,0,0,0,'Comment'),
(38124,1,0,'This thing is huge! Reverse the polarity on the Pultryizer. We\'ll have to shove it in through the outtake.',14,0,100,0,0,0,'Comment'),
(38124,2,0,'There it goes. It should only be a moment now....',14,0,100,0,0,0,'Comment'),
(38124,3,0,'$n, get to the Mechashark X-Steam Controller. Rid us of the Hammer menace!',12,0,100,0,0,0,'Comment');

-- Hobart Grapplehammer
SET @ENTRY := 38120;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,24671,0,0,0,45,0,1,0,0,0,0,10,831645,38122,0,0.0,0.0,0.0,0.0,"On Quest Reward - Set Data 1 to Megabomb"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,19,0,100,0,24744,0,0,0,1,1,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,20,0,100,0,24744,0,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Reward - Talk 2"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,2,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Talk 3"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,2,38120,0,0,45,0,1,0,0,0,0,10,831641,38124,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 1 to Greely"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,3,38120,0,0,81,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Reset Flags"),
(@ENTRY,@SOURCETYPE,7,0,20,0,100,0,24744,0,0,0,83,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Reward - Remove Flags"),
(@ENTRY,@SOURCETYPE,8,0,38,0,100,0,0,2,0,0,17,431,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Set Emote Cower"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,3,38120,0,0,17,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Reset Emote"),
(@ENTRY,@SOURCETYPE,10,0,19,0,100,0,24856,0,0,0,1,4,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 4");

-- Assistant Greely
SET @ENTRY := 38124;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,1,0,7000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,38124,0,0,1,1,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,38124,0,0,50,202104,16,0,0,0,0,8,0,0,0,905.58,2340.52,5.57,4.17,"After Talk 0 - Summon Egg"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,38124,0,0,1,2,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,2,38124,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Phase 1"),
(@ENTRY,@SOURCETYPE,5,0,1,1,100,0,500,500,500,500,11,71608,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Cast Fountain of Eggs"),
(@ENTRY,@SOURCETYPE,6,0,1,1,100,0,15000,15000,15000,15000,24,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Evade"),
(@ENTRY,@SOURCETYPE,7,0,7,1,100,0,15000,15000,15000,15000,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Set Phase 0"),
(@ENTRY,@SOURCETYPE,8,0,1,1,100,0,10000,10000,10000,10000,45,0,2,0,0,0,0,10,831656,38120,0,0.0,0.0,0.0,0.0,"OOC - Set Data 2 to Hobart"),
(@ENTRY,@SOURCETYPE,9,0,19,0,100,0,24817,0,0,0,1,3,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 3");

UPDATE `creature_template` SET `VehicleId`=628, `InhabitType`=2 WHERE `entry`=38318;

DELETE FROM `creature_template_addon` WHERE `entry` = '38318';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(38318, 1, '71663');

UPDATE `creature_template` SET `minlevel`=8, `maxlevel`=10 WHERE `entry`=38318;
UPDATE `creature_template` SET `mindmg`=60, `maxdmg`=76, `InhabitType`=2 WHERE `entry`=36682;

DELETE FROM `spell_target_position` WHERE `id` = '71648';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(71648, 648, 908.18, 2443.13, -7.84, 1.72);

DELETE FROM `creature_text` WHERE `entry`=38432;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38432,0,0,'You hear that, naga? $n is on his way to settle our "negotiations"!',14,0,100,0,0,0,'Comment'),
(38432,1,0,'Everybody loves a pool pony. It\'s our fastest selling toy behind the Kablooey Bombs: Infant Edition.',12,0,100,0,0,0,'Comment'),
(38432,2,0,'That pygmy helm should fool them, at least for a little while. Get back to town!',12,0,100,0,0,0,'Comment');

-- Megs Dreadshredder
SET @ENTRY := 38432;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,24858,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,24864,0,0,0,1,1,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 1");

DELETE FROM `creature_text` WHERE `entry`=38381;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38381,0,0,'We can discuss the cut after you come back with the hides $n, I\'m thinking ninety-ten.',12,0,100,0,0,0,'Comment');

-- Brett "Coins" McQuid
SET @ENTRY := 38381;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,24859,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0");

UPDATE `gameobject_template` SET `flags`=4, `data5`=1 WHERE `entry`=202133;
UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=44580;

-- Naga Hatchling
SET @ENTRY := 44580;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,85,83115,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Summon Naga"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,33,38413,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Quest Credit"),
(@ENTRY,@SOURCETYPE,3,0,64,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Force Despawn");

DELETE FROM `creature_template_addon` WHERE `entry` = '44590';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(44590, 1, '62011');

-- Naga Hatchling
SET @ENTRY := 44590;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,29,2,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Follow Owner"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,41,120000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Force Despawn");

UPDATE `creature_template` SET `unit_flags`=768, `InhabitType`=7 WHERE `entry`=44590;
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry`=44579 AND `spell_id`=72073;
UPDATE `creature` SET `phaseMask`=32768 WHERE `id` IN (44579, 44578);

-- Naga Hatchling
SET @ENTRY := 38412;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,85,83115,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Summon Naga"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,33,38413,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Quest Credit"),
(@ENTRY,@SOURCETYPE,3,0,64,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Force Despawn");

-- Naga Hatchling
SET @ENTRY := 44578;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,85,83115,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Summon Naga"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,33,38413,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Quest Credit"),
(@ENTRY,@SOURCETYPE,3,0,64,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Force Despawn");

-- Naga Hatchling
SET @ENTRY := 44579;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,85,83115,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Summon Naga"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,33,38413,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Quest Credit"),
(@ENTRY,@SOURCETYPE,3,0,64,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Force Despawn");

UPDATE `creature_template` SET `npcflag`=1 WHERE `entry` IN (44579, 44578, 38412);
UPDATE `creature_template` SET `minlevel`=8, `maxlevel`=8, `unit_flags`=768, `ScriptName`='npc_ace_event_soe' WHERE `entry`=38455;
UPDATE `creature_template` SET `InhabitType`=3, `unit_flags`=768, `mindmg`=10, `maxdmg`=18, `unit_class`=4, `ScriptName`='npc_faceless_soe' WHERE `entry`=38448;
UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry`=38457;

DELETE FROM `creature_text` WHERE `entry`=38455;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38455,0,0,'I got these little hellions on a short leash, $n. The naga won\'t attack us while we have their hatchlings.',12,0,100,0,0,0,'Comment'),
(38455,1,0,'You ready to make their leader surrender, buddy? Okay, here we go.',12,0,100,0,0,0,'Comment'),
(38455,2,0,'We\'re planning on having a special naga appreciation sale after your surrender is all wrapped up! Thirty percent off most goods we have in stock. Red light savings on Kaldorei artifacts today only!',14,0,100,0,0,0,'Comment'),
(38455,3,0,'You naga keep your distance. We\'re not kidding around here!',14,0,100,0,0,0,'Comment'),
(38455,4,0,'We\'ve got your hatchlings. You better not attack us if you know what\'s good for you!',14,0,100,0,0,0,'Comment'),
(38455,5,0,'Prepare to surrender to the Bilgewater Cartel!',14,0,100,0,0,0,'Comment'),
(38455,6,0,'Alright, naga leader, come on out from hiding and surrender in the name of $n and the Bilgewater Cartel!',14,0,100,0,0,0,'Comment'),
(38455,7,0,'Um, dude, this does not look good. I'm out of here!',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_template_addon` WHERE `entry` = '38448';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(38448, 1, '72126 ');

UPDATE `creature` SET `phaseMask`=32768 WHERE `guid`=832143;

DELETE FROM `script_waypoint` WHERE `entry` = '38455';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(38455, 1, 664.62, 2004.72, 38.71, 'Ace SoE WP'),
(38455, 2, 627.82, 1990.73, 19.96, 'Ace SoE WP'),
(38455, 3, 579.57, 1985.76, 10.34, 'Ace SoE WP'),
(38455, 4, 499.25, 2007.99, 1.27, 'Ace SoE WP'),
(38455, 5, 464.15, 1992.07, 0.02, 'Ace SoE WP'),
(38455, 6, 425.29, 1951.25, -0.51, 'Ace SoE WP'),
(38455, 7, 272.65, 1946.95, 0.48, 'Ace SoE WP'),
(38455, 8, 167.91, 1943.29, 5.17, 'Ace SoE WP'),
(38455, 9, 205.27, 1958.89, 1.21, 'Ace SoE WP');

DELETE FROM `creature_text` WHERE `entry`=38448;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38448,0,0,'WHO DARES?!',14,0,100,0,0,0,'Comment'),
(38448,1,0,'Little goblins? I remember when your race was created.',14,0,100,0,0,0,'Comment'),
(38448,2,0,'I care nothing for your threats or these naga. Prepare to be removed from existence.',14,0,100,0,0,0,'Comment'),
(38448,3,0,'Now, young $n, you will die!',14,0,100,0,0,0,'Comment');

-- Megs Dreadshredder
SET @ENTRY := 38432;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,24858,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,24864,0,0,0,1,1,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,19,0,100,0,24868,0,0,0,85,72058,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Start Event"),
(@ENTRY,@SOURCETYPE,3,0,19,0,100,0,24897,0,0,0,1,2,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 2");

UPDATE `quest_template` SET `SourceSpellId`=66987 WHERE `Id`=24897;

UPDATE `creature` SET `phaseMask`=1024 WHERE `guid` IN
(832188,832178,832187,832186,832185,832180,832181, 832179,832172,833075,832171,833067);

UPDATE `creature_template` SET `minlevel`=8, `maxlevel`=10, `faction_A`=14, `faction_H`=14, `mindmg`=8, `maxdmg`=14, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=46747;

-- B.C. Eliminator
SET @ENTRY := 38526;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,5000,20000,5000,20000,45,0,10,0,0,0,0,11,24110,800,0,0.0,0.0,0.0,0.0,"OOC - Set Data 10 to Trigger (For Oomlot Warriors"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,20000,5000,20000,45,0,10,0,0,0,0,11,24110,800,0,0.0,0.0,0.0,0.0,"OOC - Set Data 10 to Trigger (For Oomlot Warriors)");

-- ELM General Purpose Bunny Large
SET @ENTRY := 24110;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,1,1,1,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Kill trigger - On  data set - increment phase 1(1)"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,1,2,2,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Kill trigger - On  data set - increment phase 2(2)"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,1,3,3,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Kill trigger - On  data set - increment phase 3(4)"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,1,4,4,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Kill trigger - On  data set - increment phase 4(8)"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,1,5,5,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Kill trigger - On  data set - increment phase 5(16)"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,1,6,6,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Kill trigger - On  data set - increment phase 6(32)"),
(@ENTRY,@SOURCETYPE,6,7,1,32,100,1,0,0,0,0,45,1,1,0,0,0,0,11,31135,100,0,0.0,0.0,0.0,0.0,"Kill trigger - On  phase 6(32) - Set Data"),
(@ENTRY,@SOURCETYPE,7,0,61,32,100,0,0,0,0,0,78,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Kill trigger - On  phase 6(32) - Set Phase 0"),
(@ENTRY,@SOURCETYPE,8,0,38,0,10,0,0,10,0,0,12,38531,3,20000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Summon Oomlot Warrior");

UPDATE `creature_template` SET `speed_walk`=0.0001, `speed_run`=0.0001 WHERE `entry`=38526;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '38526';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(38526, 46598, 1);

UPDATE `creature_template` SET `unit_flags`=4 WHERE `entry` IN (38518, 38516, 38513, 38514, 38515, 36615, 38738, 38387, 38122, 38432, 36471);
UPDATE `creature_template` SET `unit_flags`=4, `mindmg`=20, `maxdmg`=25 WHERE `entry` IN (38518, 38516, 38513, 38514, 38515, 36615, 38738, 38387, 38122, 38432, 36471);

-- Oomlot Warrior
SET @ENTRY := 38531;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,1,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On AI Init - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,37,0,100,1,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,918.0,2343.25,4.13,2.53,"On AI Init - Move To Pos"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,1,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On AI Init - Set Defensive"),
(@ENTRY,@SOURCETYPE,3,0,7,0,100,0,0,0,0,0,49,0,0,0,0,0,0,11,0,30,0,0.0,0.0,0.0,0.0,"On Evade - Attack New Targets"),
(@ENTRY,@SOURCETYPE,5,0,8,0,100,0,72207,4,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Set Phase 1"),
(@ENTRY,@SOURCETYPE,6,0,1,1,100,1,1300,1300,1300,1300,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Die after Hit"),
(@ENTRY,@SOURCETYPE,7,0,6,0,100,0,0,0,0,0,33,38536,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit"),
(@ENTRY,@SOURCETYPE,8,0,6,0,100,0,0,0,0,0,41,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Force Despawn");

-- Sassy Hardwrench
SET @ENTRY := 38387;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,24924,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0");

DELETE FROM `creature_text` WHERE `entry`=38387;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38387,0,0,'You\'re going to have to take the flight to them, $n. Look for Izzy just outside their village.',12,0,100,0,0,0,'Comment');

UPDATE `creature` SET `phaseMask`=32768 WHERE `guid` IN (832343,832342,832341);

DELETE FROM `creature_text` WHERE `entry`=38647;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38647,0,0,'$n, you gotta get in there and rescue our people!',12,0,100,0,0,0,'Comment');

-- Izzy
SET @ENTRY := 38647;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,20,0,100,0,24924,0,0,0,28,66987,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Remove Invoker Aura"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,24945,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0");