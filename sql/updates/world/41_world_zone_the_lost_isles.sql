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
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,32063,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Corruption"),
(@ENTRY,@SOURCETYPE,2,0,6,0,100,0,0,0,0,0,2,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Set Friendly"),
(@ENTRY,@SOURCETYPE,3,0,6,0,100,0,0,0,0,0,11,73703,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Summon Object"),
(@ENTRY,@SOURCETYPE,4,0,8,0,100,0,73702,1,0,0,33,39276,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit"),
(@ENTRY,@SOURCETYPE,5,0,8,0,100,0,73702,1,0,0,1,3,5000,0,0,0,0,11,39199,20,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 3"),
(@ENTRY,@SOURCETYPE,6,0,8,0,100,0,73702,1,0,0,11,73723,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Cast Soulstone");

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
(35813,3,0,'That\'s good enough for now. I\'ll make my way out on my own. Thanks for the escort, $n',12,0,100,0,0,0,'Comment');

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
(@ENTRY,@SOURCETYPE,22,0,40,0,100,0,17,0,0,0,33,35816,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 17 - Quest Complete"),
(@ENTRY,@SOURCETYPE,23,0,40,0,100,0,17,0,0,0,1,3,8000,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 17 - Talk 3"),
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
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,8,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Aggressive"),
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

DELETE FROM `conditions` WHERE `SourceEntry` = '25203' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 25203, 25200, 0),
(20, 8, 25203, 25201, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25203' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 25203, 25200, 0),
(19, 8, 25203, 25201, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25202' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 25202, 25200, 0),
(20, 8, 25202, 25201, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25202' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 25202, 25200, 0),
(19, 8, 25202, 25201, 0);

UPDATE `quest_template` SET `PrevQuestId`='25213' WHERE `Id`=25244;

DELETE FROM `creature_text` WHERE `entry`=36471;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36471,0,0,'Hobart\'s right behind you!',12,0,100,0,0,0,'Comment'),
(36471,1,0,'Remember, look for the pygmy leaders: Gaahl, Malmo and Teloch.',12,0,100,0,0,0,'Comment');

-- Foreman Dampwick
SET @ENTRY := 36471;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,27139,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,24945,0,0,0,1,1,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,50,0,0,10,4,17,21,11,10,10,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Random Emote");

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
(@ENTRY,@SOURCETYPE,1,0,20,0,100,0,24741,0,0,0,45,0,1,0,0,0,0,10,831656,38120,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Set Data 1 to Hobart"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,50,0,0,10,4,17,21,11,10,10,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Random Emote");

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
(38120,4,0,'The marketing research Megs has conducted suggests that a naga invasion is imminent!',12,0,100,0,0,0,'Comment'),
(38120,5,0,'Take your time, my dear. Now what can I modify this shredder boot to be? Hmm.',12,0,100,0,0,0,'Comment'),
(38120,6,0,'I\'ve set the Bootzooka to fire several rockets per shot. I\'m fairly certain that I perfectly calibrated the targeting.',12,0,100,0,0,0,'Comment'),
(38120,7,0,'Booster rockets for cages. What will I think of next? I am a genius!',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=38124;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38124,0,0,'Genius idea, sir. Your brain power never ceases to amaze me!',14,0,100,0,0,0,'Comment'),
(38124,1,0,'This thing is huge! Reverse the polarity on the Pultryizer. We\'ll have to shove it in through the outtake.',14,0,100,0,0,0,'Comment'),
(38124,2,0,'There it goes. It should only be a moment now....',14,0,100,0,0,0,'Comment'),
(38124,3,0,'$n, get to the Mechashark X-Steam Controller. Rid us of the Hammer menace!',12,0,100,0,0,0,'Comment'),
(38124,4,0,'Look for the mounds of glowing stuff on the ground.',12,0,100,0,0,0,'Comment'),
(38124,5,0,'Get rid of those Steamwheedle Sharks before they trounce us!',12,0,100,0,0,0,'Comment'),
(38124,6,0,'It\'s time for a little sabotage!',12,0,100,0,0,0,'Comment'),
(38124,7,0,'Deliver the footbomb uniform to the Slave Pits. Hurry, $n!',12,0,100,0,0,0,'Comment');

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
(@ENTRY,@SOURCETYPE,10,0,19,0,100,0,24856,0,0,0,1,4,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 4"),
(@ENTRY,@SOURCETYPE,11,0,19,0,100,0,24954,0,0,0,1,5,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 5"),
(@ENTRY,@SOURCETYPE,12,0,19,0,100,0,24958,0,0,0,1,6,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 6"),
(@ENTRY,@SOURCETYPE,13,0,1,0,100,0,1000,1000,1000,1000,28,72971,0,0,0,0,0,18,15,0,0,0.0,0.0,0.0,0.0,"OOC - Remove Auras from players"),
(@ENTRY,@SOURCETYPE,14,0,19,0,100,0,25214,0,0,0,1,7,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 7"),
(@ENTRY,@SOURCETYPE,15,0,38,0,100,0,0,50,0,0,10,4,17,21,11,10,10,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Random Emote");

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
(@ENTRY,@SOURCETYPE,9,0,19,0,100,0,24817,0,0,0,1,3,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 3"),
(@ENTRY,@SOURCETYPE,10,0,19,0,100,0,24946,0,0,0,1,4,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 4"),
(@ENTRY,@SOURCETYPE,11,0,19,0,100,0,25200,0,0,0,1,5,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 5"),
(@ENTRY,@SOURCETYPE,12,0,19,0,100,0,25204,0,0,0,1,6,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 6"),
(@ENTRY,@SOURCETYPE,13,0,19,0,100,0,25213,0,0,0,1,7,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 7"),
(@ENTRY,@SOURCETYPE,14,0,38,0,100,0,0,50,0,0,10,4,17,21,11,10,10,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Random Emote");

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
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,24859,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,50,0,0,10,4,17,21,11,10,10,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Random Emote");

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
(38455,7,0,'Um, dude, this does not look good. I\'m out of here!',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_template_addon` WHERE `entry` = '38448';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(38448, 1, '72126');

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
(832188,832178,832187,832186,832185,832180,832181, 832179,832172,833075,832171,833067,
832966,832962,832914,832961,832965,832960,832964,832948,832963,832946);

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
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,24924,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,24940,0,0,0,1,1,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,19,0,100,0,25058,0,0,0,1,2,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 2"),
(@ENTRY,@SOURCETYPE,3,0,19,0,100,0,25066,0,0,0,1,3,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 3"),
(@ENTRY,@SOURCETYPE,4,0,62,0,100,0,12582,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,5,0,62,0,100,0,12582,0,0,0,85,73431,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Airplane"),
(@ENTRY,@SOURCETYPE,6,0,19,0,100,0,25098,0,0,0,1,4,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 4"),
(@ENTRY,@SOURCETYPE,7,0,19,0,100,0,25243,0,0,0,1,5,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 5"),
(@ENTRY,@SOURCETYPE,8,0,19,0,100,0,25244,0,0,0,1,6,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 6"),
(@ENTRY,@SOURCETYPE,9,0,19,0,100,0,25251,0,0,0,1,7,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 7"),
(@ENTRY,@SOURCETYPE,10,0,38,0,100,0,0,50,0,0,10,4,17,21,11,10,10,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Random Emote"),
(@ENTRY,@SOURCETYPE,11,0,62,0,100,0,12582,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,12,0,62,0,100,0,12582,1,0,0,85,74029,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Teleport & Bind");

DELETE FROM `creature_text` WHERE `entry`=38387;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38387,0,0,'You\'re going to have to take the flight to them, $n. Look for Izzy just outside their village.',12,0,100,0,0,0,'Comment'),
(38387,1,0,'Those zombies are slow. You don\'t have to run right through them. Don\'t let them eat your brains, $n!',12,0,100,0,0,0,'Comment'),
(38387,2,0,'Goblin grenades versus gnomish land mines. Show them who\'s better, $n.',12,0,100,0,0,0,'Comment'),
(38387,3,0,'I forget... did you take flying lessons back on Kezan?',12,0,100,0,0,0,'Comment'),
(38387,4,0,'Better hurry up, $n. I think that Thrall has news on where the people are being held.',12,0,100,0,0,0,'Comment'),
(38387,5,0,'First sh left you for Chip, and now the Trade Prince! She was never good enough for you, $n',12,0,100,0,0,0,'Comment'),
(38387,6,0,'She stole your man, $n! You know what you gotta do!',12,0,100,0,0,0,'Comment'),
(38387,7,0,'$n, get into the Ultimate Footbomb Uniform behind you and get down to the docks. Help Thrall kick the Trade Prince\'s butt!',12,0,100,0,0,0,'Comment');

UPDATE `creature` SET `phaseMask`=32768 WHERE `guid` IN
(832343,832342,832341,833051,833067,832335,832345,832348,
832265,832340,832673,833291,833290,833186,833293,833292,
833305,831882,831883,831868,833342,833341,833361,833372,
833348,833383,833439,833382,833422,833404,833455,833405,
833356,833408,833438,833723,833898,833237,833234,833892,
833734,833230,833236,833242,833683,833893,833219,833686,
833687,833880,833767,833768,833717,833250,833673,833682);

-- Yngwie
SET @ENTRY := 38696;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,6000,6000,20000,30000,11,75942,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Voodoo Illusion"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0");

DELETE FROM `creature_text` WHERE `entry`=40722;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(40722,0,0,'A Voodoo Allucination spawns near Yngwie!',16,0,100,0,0,0,'Comment');

-- Voodoo Illusion
SET @ENTRY := 40722;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,37075,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Damage Ampl"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,49,0,5000,0,0,0,0,18,20,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Player");

DELETE FROM `creature_text` WHERE `entry`=38696;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38696,0,0,'Meesa na wafun ta ionga!',14,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=38643;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38643,0,0,'They were trying to change me into a zombie!!!',12,0,100,0,0,0,'Comment'),
(38643,0,1,'They took the others up into the volcano. Some to turn into zombies, some to sacrifice to their turtle god, Volcanoth!',12,0,100,0,0,0,'Comment'),
(38643,0,2,'I felt my life slipping out of me.',12,0,100,0,0,0,'Comment'),
(38643,0,3,'The other captives are up in the volcano... they\'re being sacrificed, or worse, zombified! ',12,0,100,0,0,0,'Comment'),
(38643,0,4,'I really can\'t thank you enough! ',12,0,100,0,0,0,'Comment'),
(38643,0,5,'I gotta get out of here before they catch me again! ',12,0,100,0,0,0,'Comment'),
(38643,0,6,'I\'m free! I owe you my life!',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `speed_run`=1 WHERE `entry`=38455;

-- Goblin Captive
SET @ENTRY := 38643;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,1,500,500,60000,60000,11,72243,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,1,1,100,1,1000,1000,0,0,11,72243,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Summon Shaman"),
(@ENTRY,@SOURCETYPE,2,0,8,1,100,1,72935,8,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Set Phase 2"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,1,0,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,0,38643,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Run"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,0,38643,0,0,69,1,0,0,0,0,0,8,0,0,0,712.39,1779.86,109.36,1.98,"After Talk 0 - Move Away"),
(@ENTRY,@SOURCETYPE,6,0,34,0,100,0,8,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Force Despawn"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,0,38643,0,0,41,10000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Force Despawn");

-- Oomlot Shaman
SET @ENTRY := 38644;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,72935,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Zombify"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Defensive"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,45,0,1,0,0,0,0,19,38643,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Data 1 to Owner"),
(@ENTRY,@SOURCETYPE,3,0,4,0,100,0,0,0,0,0,11,12550,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Lightning Shield");

UPDATE `creature_template` SET `minlevel`=5, `maxlevel`=8, `faction_A`=14, `faction_H`=14 WHERE `entry`=38644;
UPDATE `creature_template` SET `mindmg`=7, `maxdmg`=11, `attackpower`=3 WHERE `entry`=38753;

DELETE FROM `creature_text` WHERE `entry`=38738;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38738,0,0,'Get in there and show those zombies what the Bilgewater Buccaneers are made of, kid!',12,0,100,0,0,0,'Comment'),
(38738,1,0,'You\'re going to love this!',12,0,100,0,0,0,'Comment'),
(38738,2,0,'We\'re gonna make you the ultimate footbomb uniform, kid. But first, we need parts. Lots of them.',12,0,100,0,0,0,'Comment');

-- Coach Crosscheck
SET @ENTRY := 38738;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,24942,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,24952,0,0,0,1,1,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,19,0,100,0,25201,0,0,0,1,2,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 2"),
(@ENTRY,@SOURCETYPE,3,0,4,0,100,0,0,0,0,0,42,96,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible");

UPDATE `creature_template` SET `minlevel`=6, `maxlevel`=10, `speed_run`=1.64286, `VehicleId`=653, `InhabitType`=4 WHERE `entry`=38802;

DELETE FROM conditions WHERE SourceEntry = '72886' AND ConditionValue2 = '38753';
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 7, 72886, 0, 0, 31, 0, 3, 38753, 0, 0, 0, '', 'Rocket Boots - Only on Zombies');

-- Goblin Zombie
SET @ENTRY := 38753;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,6,0,100,0,0,0,0,0,33,38807,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit");

DELETE FROM `spell_script_names` WHERE `spell_id` = '72891';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(72891, 'spell_super_booster_rocket_boots');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '-72887';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(-72887, -72885, 'Super Rockets -> Remove Trigger Fire');

-- Malmo
SET @ENTRY := 38809;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,500,500,3500,8500,11,57780,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Lightning Bolt"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,4000,12500,4000,12500,11,75945,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Fury of the Storm");

-- Teloch
SET @ENTRY := 38810;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,39591,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Searing Totem"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,500,500,12000,12000,11,75946,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Fire and the Flames");

UPDATE `creature_template` SET `mindmg`=8, `maxdmg`=12, `attackpower`=3, `dmg_multiplier`=1.1 WHERE `entry` IN (38809, 38810,38808);

DELETE FROM `spell_script_names` WHERE `spell_id` = '72971';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(72971, 'spell_rockin_powder_infused_boots');

DELETE FROM `creature_text` WHERE `entry`=38855;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38855,0,0,'Stay out of the way of Volcanoth\'s breath!',41,0,100,0,0,0,'Comment');

-- Volcanoth
SET @ENTRY := 38855;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,8000,8000,8000,8000,11,73097,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Volcanoth's Breath"),
(@ENTRY,@SOURCETYPE,1,0,6,0,100,0,0,0,0,0,11,73060,0,0,0,0,0,18,65,0,0,0.0,0.0,0.0,0.0,"On Death - Kill Credit"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,4000,4000,8000,8000,1,0,5000,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Talk 0");

UPDATE `creature_template` SET `unit_flags`=0, `unit_flags2`=0 WHERE `entry`=38441;
UPDATE `creature_template` SET `speed_run`=2.14286, `unit_flags`=768, `VehicleId`=657, `InhabitType`=4 WHERE `entry` IN (38918, 38929);
UPDATE `creature_template` SET `ScriptName`='npc_flight_bomber_volcano_escape' WHERE  `entry`=38918;

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '38929';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(38929, 46598, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '38918';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(38918, 46598, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '38929';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(38929, 38928, 1, 'Sassy on Bomber', 8, 0);

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '38918';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(38918, 38928, 1, 'Sassy on Bomber', 8, 0);

DELETE FROM `creature_template_addon` WHERE `entry` IN (38929, 38918);
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(38929, 1, '73149'),
(38918, 1, '73149');

DELETE FROM `script_waypoint` WHERE `entry` = '38918';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(38918, 1, 1150.28, 1122.74, 167.49, 'Flight Bomber (Volcano Escape)'),
(38918, 2, 1060.64, 1187.82, 158.16, 'Flight Bomber (Volcano Escape)'),
(38918, 3, 1005.76, 1220.02, 151.86, 'Flight Bomber (Volcano Escape)'),
(38918, 4, 990.87, 1264.70, 132.98, 'Flight Bomber (Volcano Escape)'),
(38918, 5, 1007.30, 1322.27, 115.33, 'Flight Bomber (Volcano Escape)'),
(38918, 6, 1009.08, 1383.37, 114.40, 'Flight Bomber (Volcano Escape)'),
(38918, 7, 1020.45, 1448.55, 120.04, 'Flight Bomber (Volcano Escape)'),
(38918, 8, 1040.14, 1486.75, 120.99, 'Flight Bomber (Volcano Escape)'),
(38918, 9, 970.21, 1552.84, 151.03, 'Flight Bomber (Volcano Escape)'),
(38918, 10, 916.42, 1583.00, 172.74, 'Flight Bomber (Volcano Escape)'),
(38918, 11, 808.38, 1595.70, 168.44, 'Flight Bomber (Volcano Escape)'),
(38918, 12, 755.99, 1604.28, 157.24, 'Flight Bomber (Volcano Escape)'),
(38918, 13, 741.78, 1618.60, 143.39, 'Flight Bomber (Volcano Escape)'),
(38918, 14, 724.39, 1749.35, 125.89, 'Flight Bomber (Volcano Escape)'),
(38918, 15, 716.25, 1829.95, 122.14, 'Flight Bomber (Volcano Escape)'),
(38918, 16, 777.73, 1909.03, 122.68, 'Flight Bomber (Volcano Escape)'),
(38918, 17, 793.38, 2084.37, 106.72, 'Flight Bomber (Volcano Escape)'),
(38918, 18, 901.13, 2167.15, 97.72, 'Flight Bomber (Volcano Escape)'),
(38918, 19, 944.27, 2383.26, 44.23, 'Flight Bomber (Volcano Escape)'),
(38918, 20, 939.05, 2543.66, 37.75, 'Flight Bomber (Volcano Escape)'),
(38918, 21, 843.64, 2606.68, 35.93, 'Flight Bomber (Volcano Escape)'),
(38918, 22, 767.85, 2506.33, 34.67, 'Flight Bomber (Volcano Escape)'),
(38918, 23, 781.22, 2378.01, 43.93, 'Flight Bomber (Volcano Escape)'),
(38918, 24, 805.91, 2355.10, 47.47, 'Flight Bomber (Volcano Escape)'),
(38918, 25, 1057.48, 2274.28, 55.26, 'Flight Bomber (Volcano Escape)'),
(38918, 26, 1258.49, 2230.75, 99.55, 'Flight Bomber (Volcano Escape)'),
(38918, 27, 1310.85, 2299.57, 82.33, 'Flight Bomber (Volcano Escape)'),
(38918, 28, 1331.35, 2429.52, 69.47, 'Flight Bomber (Volcano Escape)'),
(38918, 29, 1355.57, 2587.11, 85.92, 'Flight Bomber (Volcano Escape)'),
(38918, 30, 1391.76, 2648.55, 95.79, 'Flight Bomber (Volcano Escape)'),
(38918, 31, 1497.00, 2624.90, 113.16, 'Flight Bomber (Volcano Escape)'),
(38918, 32, 1557.30, 2624.44, 114.49, 'Flight Bomber (Volcano Escape)'),
(38918, 33, 1564.85, 2691.76, 97.29, 'Flight Bomber (Volcano Escape)');

DELETE FROM `creature_text` WHERE `entry`=38928;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38928,0,0,'Hang on, $n! We have to get you out of here, NOW!',14,0,100,0,0,0,'Comment'),
(38928,1,0,'OH MY GOSH! BEHIND YOU!!!',14,0,100,0,0,0,'Comment'),
(38928,2,0,'WE\'RE ON FIRE!',14,0,100,0,0,0,'Comment'),
(38928,3,0,'YEEEEEEEEEE HAAAAAAAAAA!!!',14,0,100,0,0,0,'Comment'),
(38928,4,0,'We\'re coming up on the Town-In-A-Box now...',14,0,100,0,0,0,'Comment'),
(38928,5,0,'Oh no! Where is everyone? I dropped them off here!',14,0,100,0,0,0,'Comment'),
(38928,6,0,'Get in the back seat. We\'re getting out of here. I know where our old friends, the orcs, are!',14,0,100,0,0,0,'Comment'),
(38928,7,0,'First Kezan and now here. We are toast if we don\'t find a way off of this island soon!',14,0,100,0,0,0,'Comment');

UPDATE `quest_template` SET `SourceSpellId`=73105 WHERE `Id`=25023;

-- Giant Fireball Bunny
SET @ENTRY := 38979;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,73111,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Add Triggering"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,41,8000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Despawn");

DELETE FROM `spell_target_position` WHERE `id` = '73105';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(73105, 648, 1163.41, 1093.56, 123.79, 2.11);

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=-90418 AND `spell_effect`=91202 AND `type`=0;
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=90418 AND `spell_effect`=91202 AND `type`=0;

DELETE FROM `spell_area` WHERE `spell` = '90418' AND `quest_start` = '25023';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(90418, 4720, 25023, 1, 74, 0);

-- Aggra
SET @ENTRY := 39065;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,25093,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accepted - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,20,0,100,0,25093,0,0,0,1,1,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accepted - Talk 1");

DELETE FROM `creature_text` WHERE `entry`=39065;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39065,0,0,'Deliver justice for our dead. $n.',12,0,100,0,0,0,'Comment'),
(39065,1,0,'You honor us with your actions on behalf of our dead, $n.',12,0,100,0,0,0,'Comment');

UPDATE `gameobject_template` SET `flags`=0 WHERE `entry`=202472;
UPDATE `gameobject_template` SET `data12`=0 WHERE `entry`=202472;
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=39039;
UPDATE `creature` SET `spawndist`=45, `MovementType`=1 WHERE `id`=39039;
UPDATE `creature_template` SET `speed_walk`=2 WHERE `entry`=39039;

DELETE FROM `creature_loot_template` WHERE `entry` IN (39141, 39143, 39069, 39142);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(39069, 765, 40, 1, 0, 1, 1),
(39069, 2449, 40, 1, 0, 1, 1),
(39141, 118, 0.9, 1, 0, 1, 1),
(39141, 159, 1, 1, 0, 1, 1),
(39141, 414, 26.7857, 1, 0, 1, 1),
(39141, 727, 0.4181, 1, 0, 1, 1),
(39141, 768, 0.1, 1, 0, 1, 1),
(39141, 805, 1.098, 1, 0, 1, 1),
(39141, 818, 3.5714, 1, 0, 1, 1),
(39141, 858, 8.9286, 1, 0, 1, 1),
(39141, 1210, 10.7143, 1, 0, 1, 1),
(39141, 1411, 0.1, 1, 0, 1, 1),
(39141, 1412, 0.2, 1, 0, 1, 1),
(39141, 1413, 0.2, 1, 0, 1, 1),
(39141, 1414, 0.2, 1, 0, 1, 1),
(39141, 1415, 0.2, 1, 0, 1, 1),
(39141, 1416, 0.2, 1, 0, 1, 1),
(39141, 1417, 0.1, 1, 0, 1, 1),
(39141, 1418, 0.2, 1, 0, 1, 1),
(39141, 1419, 0.2, 1, 0, 1, 1),
(39141, 1420, 0.3472, 1, 0, 1, 1),
(39141, 1422, 0.2906, 1, 0, 1, 1),
(39141, 1423, 0.1, 1, 0, 1, 1),
(39141, 1425, 0.1, 1, 0, 1, 1),
(39141, 1427, 0.1, 1, 0, 1, 1),
(39141, 1429, 0.1, 1, 0, 1, 1),
(39141, 1430, 0.1, 1, 0, 1, 1),
(39141, 1431, 0.2, 1, 0, 1, 1),
(39141, 1433, 0.1, 1, 0, 1, 1),
(39141, 2070, 1.9417, 1, 0, 1, 1),
(39141, 2138, 0.3, 1, 0, 1, 1),
(39141, 2212, 0.2, 1, 0, 1, 1),
(39141, 2213, 0.2, 1, 0, 1, 1),
(39141, 2553, 0.0213, 1, 0, 1, 1),
(39141, 2589, 25.7, 1, 0, 1, 2),
(39141, 2598, 0.1063, 1, 0, 1, 1),
(39141, 2635, 0.1, 1, 0, 1, 1),
(39141, 2642, 0.1984, 1, 0, 1, 1),
(39141, 2643, 0.05, 1, 0, 1, 1),
(39141, 2645, 0.05, 1, 0, 1, 1),
(39141, 2646, 0.2197, 1, 0, 1, 1),
(39141, 2648, 0.05, 1, 0, 1, 1),
(39141, 2773, 0.2, 1, 0, 1, 1),
(39141, 2774, 0.2, 1, 0, 1, 1),
(39141, 3192, 0.05, 1, 0, 1, 1),
(39141, 3279, 0.0283, 1, 0, 1, 1),
(39141, 3280, 0.0921, 1, 0, 1, 1),
(39141, 3281, 0.0213, 1, 0, 1, 1),
(39141, 3282, 0.0638, 1, 0, 1, 1),
(39141, 3283, 0.0142, 1, 0, 1, 1),
(39141, 3284, 0.0354, 1, 0, 1, 1),
(39141, 3285, 0.1205, 1, 0, 1, 1),
(39141, 3286, 0.0638, 1, 0, 1, 1),
(39141, 3287, 0.0567, 1, 0, 1, 1),
(39141, 3288, 0.0425, 1, 0, 1, 1),
(39141, 3289, 0.0496, 1, 0, 1, 1),
(39141, 3290, 0.0496, 1, 0, 1, 1),
(39141, 3291, 0.0496, 1, 0, 1, 1),
(39141, 3292, 0.0425, 1, 0, 1, 1),
(39141, 3303, 0.0071, 1, 0, 1, 1),
(39141, 3312, 0.0142, 1, 0, 1, 1),
(39141, 3370, 0.05, 1, 0, 1, 1),
(39141, 3373, 0.247, 1, 0, 1, 1),
(39141, 3609, 0.05, 1, 0, 1, 1),
(39141, 3642, 0.0992, 1, 0, 1, 1),
(39141, 3644, 0.085, 1, 0, 1, 1),
(39141, 3649, 0.085, 1, 0, 1, 1),
(39141, 3650, 0.0283, 1, 0, 1, 1),
(39141, 3653, 0.0071, 1, 0, 1, 1),
(39141, 3654, 0.0071, 1, 0, 1, 1),
(39141, 4408, 0.05, 1, 0, 1, 1),
(39141, 4496, 0.05, 1, 0, 1, 1),
(39141, 4537, 10.7143, 1, 0, 1, 1),
(39141, 4541, 12.5, 1, 0, 1, 1),
(39141, 4561, 0.1, 1, 0, 1, 1),
(39141, 4562, 0.1772, 1, 0, 1, 1),
(39141, 4563, 0.1, 1, 0, 1, 1),
(39141, 4564, 0.05, 1, 0, 1, 1),
(39141, 4566, 0.1, 1, 0, 1, 1),
(39141, 4577, 0.05, 1, 0, 1, 1),
(39141, 4668, 0.1205, 1, 0, 1, 1),
(39141, 4669, 0.0921, 1, 0, 1, 1),
(39141, 4671, 0.4394, 1, 0, 1, 1),
(39141, 4672, 0.1913, 1, 0, 1, 1),
(39141, 4674, 0.1701, 1, 0, 1, 1),
(39141, 4675, 0.1063, 1, 0, 1, 1),
(39141, 4680, 0.0071, 1, 0, 1, 1),
(39141, 4686, 0.0283, 1, 0, 1, 1),
(39141, 4692, 0.0709, 1, 0, 1, 1),
(39141, 5069, 0.05, 1, 0, 1, 1),
(39141, 5368, 42.8571, 1, 0, 1, 1),
(39141, 5571, 0.05, 1, 0, 1, 1),
(39141, 5572, 0.05, 1, 0, 1, 1),
(39141, 6527, 0.0354, 1, 0, 1, 1),
(39141, 8178, 0.1701, 1, 0, 1, 1),
(39141, 8180, 0.1, 1, 0, 1, 1),
(39141, 8181, 0.1701, 1, 0, 1, 1),
(39141, 14086, 0.1488, 1, 0, 1, 1),
(39141, 14089, 0.1417, 1, 0, 1, 1),
(39141, 14090, 0.078, 1, 0, 1, 1),
(39141, 14091, 0.0283, 1, 0, 1, 1),
(39141, 14093, 0.1772, 1, 0, 1, 1),
(39141, 14094, 0.0354, 1, 0, 1, 1),
(39141, 14095, 0.078, 1, 0, 1, 1),
(39141, 14098, 0.1843, 1, 0, 1, 1),
(39141, 14099, 0.0213, 1, 0, 1, 1),
(39141, 14102, 0.0354, 1, 0, 1, 1),
(39141, 14110, 0.0425, 1, 0, 1, 1),
(39141, 15004, 0.1772, 1, 0, 1, 1),
(39141, 15005, 0.0992, 1, 0, 1, 1),
(39141, 15006, 0.0142, 1, 0, 1, 1),
(39141, 15008, 0.1276, 1, 0, 1, 1),
(39141, 15009, 0.0425, 1, 0, 1, 1),
(39141, 15010, 0.0638, 1, 0, 1, 1),
(39141, 15015, 0.085, 1, 0, 1, 1),
(39141, 15297, 0.0638, 1, 0, 1, 1),
(39141, 15299, 0.3543, 1, 0, 1, 1),
(39141, 15301, 0.0142, 1, 0, 1, 1),
(39141, 15302, 0.0638, 1, 0, 1, 1),
(39141, 15472, 0.078, 1, 0, 1, 1),
(39141, 15473, 0.1559, 1, 0, 1, 1),
(39141, 15476, 0.1063, 1, 0, 1, 1),
(39141, 15477, 0.0213, 1, 0, 1, 1),
(39141, 15478, 0.0496, 1, 0, 1, 1),
(39141, 15479, 0.0425, 1, 0, 1, 1),
(39141, 15480, 0.0496, 1, 0, 1, 1),
(39141, 15482, 0.0638, 1, 0, 1, 1),
(39141, 15483, 0.1205, 1, 0, 1, 1),
(39141, 15484, 0.0709, 1, 0, 1, 1),
(39141, 15486, 0.1063, 1, 0, 1, 1),
(39141, 15944, 0.0567, 1, 0, 1, 1),
(39141, 15969, 0.0709, 1, 0, 1, 1),
(39141, 15970, 0.0283, 1, 0, 1, 1),
(39141, 52346, -100, 1, 0, 1, 1),
(39142, 118, 1, 1, 0, 1, 1),
(39142, 159, 1.5, 1, 0, 1, 1),
(39142, 414, 9.0909, 1, 0, 1, 1),
(39142, 727, 0.2345, 1, 0, 1, 1),
(39142, 768, 0.2274, 1, 0, 1, 1),
(39142, 805, 0.1989, 1, 0, 1, 1),
(39142, 828, 0.05, 1, 0, 1, 1),
(39142, 858, 6.8182, 1, 0, 1, 1),
(39142, 1210, 4.5455, 1, 0, 1, 1),
(39142, 1411, 0.2, 1, 0, 1, 1),
(39142, 1412, 0.2, 1, 0, 1, 1),
(39142, 1413, 0.2, 1, 0, 1, 1),
(39142, 1414, 0.1, 1, 0, 1, 1),
(39142, 1415, 0.2, 1, 0, 1, 1),
(39142, 1416, 0.3553, 1, 0, 1, 1),
(39142, 1417, 0.1, 1, 0, 1, 1),
(39142, 1418, 0.2, 1, 0, 1, 1),
(39142, 1419, 0.1, 1, 0, 1, 1),
(39142, 1420, 0.2, 1, 0, 1, 1),
(39142, 1422, 0.05, 1, 0, 1, 1),
(39142, 1423, 0.3055, 1, 0, 1, 1),
(39142, 1425, 0.1, 1, 0, 1, 1),
(39142, 1427, 0.2, 1, 0, 1, 1),
(39142, 1429, 0.1, 1, 0, 1, 1),
(39142, 1430, 0.2, 1, 0, 1, 1),
(39142, 1431, 0.2, 1, 0, 1, 1),
(39142, 1433, 0.1, 1, 0, 1, 1),
(39142, 2075, 0.05, 1, 0, 1, 1),
(39142, 2138, 0.2, 1, 0, 1, 1),
(39142, 2140, 0.1066, 1, 0, 1, 1),
(39142, 2212, 0.1, 1, 0, 1, 1),
(39142, 2213, 0.1, 1, 0, 1, 1),
(39142, 2589, 27.2, 1, 0, 1, 2),
(39142, 2598, 0.0995, 1, 0, 1, 1),
(39142, 2635, 0.1, 1, 0, 1, 1),
(39142, 2642, 0.1989, 1, 0, 1, 1),
(39142, 2643, 0.1, 1, 0, 1, 1),
(39142, 2645, 0.1, 1, 0, 1, 1),
(39142, 2646, 0.1, 1, 0, 1, 1),
(39142, 2648, 0.1, 1, 0, 1, 1),
(39142, 2773, 0.1, 1, 0, 1, 1),
(39142, 2774, 0.1, 1, 0, 1, 1),
(39142, 3192, 0.05, 1, 0, 1, 1),
(39142, 3279, 0.0355, 1, 0, 1, 1),
(39142, 3280, 0.1208, 1, 0, 1, 1),
(39142, 3281, 0.0355, 1, 0, 1, 1),
(39142, 3282, 0.0355, 1, 0, 1, 1),
(39142, 3283, 0.0355, 1, 0, 1, 1),
(39142, 3284, 0.0355, 1, 0, 1, 1),
(39142, 3285, 0.1634, 1, 0, 1, 1),
(39142, 3286, 0.0284, 1, 0, 1, 1),
(39142, 3287, 0.0213, 1, 0, 1, 1),
(39142, 3288, 0.0497, 1, 0, 1, 1),
(39142, 3289, 0.0711, 1, 0, 1, 1),
(39142, 3290, 0.0213, 1, 0, 1, 1),
(39142, 3291, 0.0568, 1, 0, 1, 1),
(39142, 3292, 0.0071, 1, 0, 1, 1),
(39142, 3303, 0.0568, 1, 0, 1, 1),
(39142, 3312, 0.0924, 1, 0, 1, 1),
(39142, 3370, 0.05, 1, 0, 1, 1),
(39142, 3373, 0.2, 1, 0, 1, 1),
(39142, 3609, 0.05, 1, 0, 1, 1),
(39142, 3610, 0.05, 1, 0, 1, 1),
(39142, 3642, 0.1989, 1, 0, 1, 1),
(39142, 3644, 0.0853, 1, 0, 1, 1),
(39142, 3649, 0.0568, 1, 0, 1, 1),
(39142, 3650, 0.0142, 1, 0, 1, 1),
(39142, 3653, 0.0071, 1, 0, 1, 1),
(39142, 4496, 0.05, 1, 0, 1, 1),
(39142, 4537, 15.9091, 1, 0, 1, 1),
(39142, 4540, 2.1316, 1, 0, 1, 1),
(39142, 4541, 11.3636, 1, 0, 1, 1),
(39142, 4561, 0.1563, 1, 0, 1, 1),
(39142, 4562, 0.4689, 1, 0, 1, 1),
(39142, 4563, 0.135, 1, 0, 1, 1),
(39142, 4564, 0.05, 1, 0, 1, 1),
(39142, 4566, 0.05, 1, 0, 1, 1),
(39142, 4577, 0.05, 1, 0, 1, 1),
(39142, 4668, 0.1279, 1, 0, 1, 1),
(39142, 4669, 0.1421, 1, 0, 1, 1),
(39142, 4671, 0.1776, 1, 0, 1, 1),
(39142, 4672, 0.1492, 1, 0, 1, 1),
(39142, 4674, 0.0995, 1, 0, 1, 1),
(39142, 4675, 0.1066, 1, 0, 1, 1),
(39142, 4680, 0.0213, 1, 0, 1, 1),
(39142, 4686, 0.0639, 1, 0, 1, 1),
(39142, 4692, 0.0426, 1, 0, 1, 1),
(39142, 5069, 0.1634, 1, 0, 1, 1),
(39142, 5368, 52.2727, 1, 0, 1, 1),
(39142, 5571, 0.05, 1, 0, 1, 1),
(39142, 5572, 0.05, 1, 0, 1, 1),
(39142, 6527, 0.0142, 1, 0, 1, 1),
(39142, 8178, 0.1208, 1, 0, 1, 1),
(39142, 8180, 0.05, 1, 0, 1, 1),
(39142, 8181, 0.1776, 1, 0, 1, 1),
(39142, 14086, 0.1137, 1, 0, 1, 1),
(39142, 14089, 0.1776, 1, 0, 1, 1),
(39142, 14090, 0.0426, 1, 0, 1, 1),
(39142, 14091, 0.0426, 1, 0, 1, 1),
(39142, 14093, 0.0995, 1, 0, 1, 1),
(39142, 14094, 0.0284, 1, 0, 1, 1),
(39142, 14095, 0.1066, 1, 0, 1, 1),
(39142, 14098, 0.2416, 1, 0, 1, 1),
(39142, 14099, 0.0355, 1, 0, 1, 1),
(39142, 14102, 0.0355, 1, 0, 1, 1),
(39142, 14110, 0.0355, 1, 0, 1, 1),
(39142, 15004, 0.0568, 1, 0, 1, 1),
(39142, 15005, 0.0853, 1, 0, 1, 1),
(39142, 15006, 0.0284, 1, 0, 1, 1),
(39142, 15008, 0.1208, 1, 0, 1, 1),
(39142, 15009, 0.0639, 1, 0, 1, 1),
(39142, 15010, 0.0568, 1, 0, 1, 1),
(39142, 15015, 0.0213, 1, 0, 1, 1),
(39142, 15297, 0.0995, 1, 0, 1, 1),
(39142, 15298, 0.0071, 1, 0, 1, 1),
(39142, 15299, 0.1492, 1, 0, 1, 1),
(39142, 15301, 0.0213, 1, 0, 1, 1),
(39142, 15302, 0.0782, 1, 0, 1, 1),
(39142, 15472, 0.0782, 1, 0, 1, 1),
(39142, 15473, 0.0924, 1, 0, 1, 1),
(39142, 15476, 0.1137, 1, 0, 1, 1),
(39142, 15477, 0.0639, 1, 0, 1, 1),
(39142, 15478, 0.0071, 1, 0, 1, 1),
(39142, 15479, 0.0497, 1, 0, 1, 1),
(39142, 15480, 0.0142, 1, 0, 1, 1),
(39142, 15481, 0.0142, 1, 0, 1, 1),
(39142, 15482, 0.0284, 1, 0, 1, 1),
(39142, 15483, 0.2416, 1, 0, 1, 1),
(39142, 15484, 0.0426, 1, 0, 1, 1),
(39142, 15486, 0.0853, 1, 0, 1, 1),
(39142, 15944, 0.0782, 1, 0, 1, 1),
(39142, 15969, 0.0995, 1, 0, 1, 1),
(39142, 15970, 0.0071, 1, 0, 1, 1),
(39142, 50437, -0.0071, 1, 0, 1, 1),
(39142, 52347, -100, 1, 0, 1, 1),
(39143, 118, 0.5, 1, 0, 1, 1),
(39143, 159, 0.5, 1, 0, 1, 1),
(39143, 414, 7.6923, 1, 0, 1, 1),
(39143, 727, 0.2119, 1, 0, 1, 1),
(39143, 768, 0.1483, 1, 0, 1, 1),
(39143, 774, 1.017, 1, 0, 1, 1),
(39143, 805, 0.1, 1, 0, 1, 1),
(39143, 818, 1.9231, 1, 0, 1, 1),
(39143, 828, 0.05, 1, 0, 1, 1),
(39143, 858, 19.2308, 1, 0, 1, 1),
(39143, 1411, 0.4, 1, 0, 1, 1),
(39143, 1412, 0.3, 1, 0, 1, 1),
(39143, 1413, 0.2, 1, 0, 1, 1),
(39143, 1414, 0.2, 1, 0, 1, 1),
(39143, 1415, 0.2, 1, 0, 1, 1),
(39143, 1416, 0.2, 1, 0, 1, 1),
(39143, 1417, 0.3, 1, 0, 1, 1),
(39143, 1418, 0.1, 1, 0, 1, 1),
(39143, 1419, 0.2754, 1, 0, 1, 1),
(39143, 1420, 0.2, 1, 0, 1, 1),
(39143, 1422, 0.6498, 1, 0, 1, 1),
(39143, 1423, 0.1, 1, 0, 1, 1),
(39143, 1425, 0.3, 1, 0, 1, 1),
(39143, 1427, 0.3, 1, 0, 1, 1),
(39143, 1429, 0.2, 1, 0, 1, 1),
(39143, 1430, 0.2, 1, 0, 1, 1),
(39143, 1431, 0.3, 1, 0, 1, 1),
(39143, 1433, 0.1, 1, 0, 1, 1),
(39143, 2138, 0.1, 1, 0, 1, 1),
(39143, 2212, 0.2, 1, 0, 1, 1),
(39143, 2213, 0.2, 1, 0, 1, 1),
(39143, 2407, 0.05, 1, 0, 1, 1),
(39143, 2589, 27, 1, 0, 1, 2),
(39143, 2598, 0.05, 1, 0, 1, 1),
(39143, 2635, 0.1, 1, 0, 1, 1),
(39143, 2642, 0.1916, 1, 0, 1, 1),
(39143, 2643, 0.1, 1, 0, 1, 1),
(39143, 2645, 0.1, 1, 0, 1, 1),
(39143, 2646, 0.1, 1, 0, 1, 1),
(39143, 2648, 0.1, 1, 0, 1, 1),
(39143, 2773, 0.2, 1, 0, 1, 1),
(39143, 2774, 0.3, 1, 0, 1, 1),
(39143, 3192, 0.05, 1, 0, 1, 1),
(39143, 3279, 0.0353, 1, 0, 1, 1),
(39143, 3280, 0.0636, 1, 0, 1, 1),
(39143, 3281, 0.0283, 1, 0, 1, 1),
(39143, 3282, 0.0212, 1, 0, 1, 1),
(39143, 3283, 0.0212, 1, 0, 1, 1),
(39143, 3285, 0.1271, 1, 0, 1, 1),
(39143, 3286, 0.0494, 1, 0, 1, 1),
(39143, 3287, 0.0494, 1, 0, 1, 1),
(39143, 3288, 0.1201, 1, 0, 1, 1),
(39143, 3289, 0.0848, 1, 0, 1, 1),
(39143, 3290, 0.0565, 1, 0, 1, 1),
(39143, 3291, 0.0212, 1, 0, 1, 1),
(39143, 3292, 0.0071, 1, 0, 1, 1),
(39143, 3303, 0.0071, 1, 0, 1, 1),
(39143, 3370, 0.2825, 1, 0, 1, 1),
(39143, 3373, 0.2, 1, 0, 1, 1),
(39143, 3609, 0.1, 1, 0, 1, 1),
(39143, 3642, 0.1766, 1, 0, 1, 1),
(39143, 3644, 0.0565, 1, 0, 1, 1),
(39143, 3649, 0.0424, 1, 0, 1, 1),
(39143, 3650, 0.0283, 1, 0, 1, 1),
(39143, 3653, 0.0141, 1, 0, 1, 1),
(39143, 4496, 0.05, 1, 0, 1, 1),
(39143, 4536, 2.1329, 1, 0, 1, 1),
(39143, 4537, 17.3077, 1, 0, 1, 1),
(39143, 4541, 17.3077, 1, 0, 1, 1),
(39143, 4561, 0.05, 1, 0, 1, 1),
(39143, 4562, 0.2048, 1, 0, 1, 1),
(39143, 4563, 1.3684, 1, 0, 1, 1),
(39143, 4564, 0.05, 1, 0, 1, 1),
(39143, 4566, 0.1, 1, 0, 1, 1),
(39143, 4668, 0.0424, 1, 0, 1, 1),
(39143, 4669, 0.1059, 1, 0, 1, 1),
(39143, 4671, 0.0848, 1, 0, 1, 1),
(39143, 4672, 0.1342, 1, 0, 1, 1),
(39143, 4674, 0.0989, 1, 0, 1, 1),
(39143, 4675, 0.113, 1, 0, 1, 1),
(39143, 4686, 0.0283, 1, 0, 1, 1),
(39143, 4692, 0.0424, 1, 0, 1, 1),
(39143, 5069, 0.05, 1, 0, 1, 1),
(39143, 5368, 40.3846, 1, 0, 1, 1),
(39143, 5572, 0.05, 1, 0, 1, 1),
(39143, 6527, 0.0283, 1, 0, 1, 1),
(39143, 8178, 0.3108, 1, 0, 1, 1),
(39143, 8180, 0.1201, 1, 0, 1, 1),
(39143, 8181, 0.1, 1, 0, 1, 1),
(39143, 14086, 0.1766, 1, 0, 1, 1),
(39143, 14089, 0.2684, 1, 0, 1, 1),
(39143, 14090, 0.0848, 1, 0, 1, 1),
(39143, 14091, 0.0565, 1, 0, 1, 1),
(39143, 14093, 0.2119, 1, 0, 1, 1),
(39143, 14094, 0.0353, 1, 0, 1, 1),
(39143, 14095, 0.0494, 1, 0, 1, 1),
(39143, 14098, 0.2401, 1, 0, 1, 1),
(39143, 14099, 0.0283, 1, 0, 1, 1),
(39143, 14102, 0.0424, 1, 0, 1, 1),
(39143, 14110, 0.0565, 1, 0, 1, 1),
(39143, 15004, 0.1271, 1, 0, 1, 1),
(39143, 15005, 0.1907, 1, 0, 1, 1),
(39143, 15006, 0.0141, 1, 0, 1, 1),
(39143, 15008, 0.0848, 1, 0, 1, 1),
(39143, 15009, 0.0353, 1, 0, 1, 1),
(39143, 15010, 0.1342, 1, 0, 1, 1),
(39143, 15015, 0.0283, 1, 0, 1, 1),
(39143, 15297, 0.0353, 1, 0, 1, 1),
(39143, 15299, 0.113, 1, 0, 1, 1),
(39143, 15301, 0.0353, 1, 0, 1, 1),
(39143, 15302, 0.0283, 1, 0, 1, 1),
(39143, 15472, 0.0424, 1, 0, 1, 1),
(39143, 15473, 0.0777, 1, 0, 1, 1),
(39143, 15476, 0.1413, 1, 0, 1, 1),
(39143, 15477, 0.0494, 1, 0, 1, 1),
(39143, 15478, 0.0141, 1, 0, 1, 1),
(39143, 15479, 0.0706, 1, 0, 1, 1),
(39143, 15480, 0.0071, 1, 0, 1, 1),
(39143, 15481, 0.0212, 1, 0, 1, 1),
(39143, 15482, 0.0636, 1, 0, 1, 1),
(39143, 15483, 0.1201, 1, 0, 1, 1),
(39143, 15484, 0.0141, 1, 0, 1, 1),
(39143, 15486, 0.0636, 1, 0, 1, 1),
(39143, 15944, 0.0424, 1, 0, 1, 1),
(39143, 15969, 0.1271, 1, 0, 1, 1),
(39143, 15970, 0.0071, 1, 0, 1, 1),
(39143, 50438, 0.0141, 1, 0, 1, 1),
(39143, 52349, -100, 1, 0, 1, 1);

UPDATE `creature_template` SET `lootid`=39069 WHERE `entry`=39069;
UPDATE `creature_template` SET `lootid`=39143 WHERE `entry`=39143;
UPDATE `creature_template` SET `lootid`=39141 WHERE `entry`=39141;
UPDATE `creature_template` SET `lootid`=39142 WHERE `entry`=39142;

UPDATE `creature_template` SET `mindmg`=8, `maxdmg`=13, `attackpower`=3, `dmg_multiplier`=1.2 WHERE `entry`=39143;

-- Alexi Silenthowl
SET @ENTRY := 39143;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,79864,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Shadowstep"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,3500,3500,3500,3500,11,79862,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Backstab"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,4500,4500,4500,4500,11,79863,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Hemorrhage");

UPDATE `creature` SET `phaseMask`=32768 WHERE `id`=39041;

DELETE FROM `vehicle_template_accessory` WHERE `entry` = '39039';
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(39039, 39041, 1, 'Airplanes (Lost Isles) -> Pilots', 8, 0);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '39039';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES
(39039, 46598, 0);

UPDATE `gossip_menu_option` SET `option_id`=3, `npc_option_npcflag`=128 WHERE `menu_id`=11223 AND `id`=0;

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '12582';
INSERT INTO `gossip_menu_option` (`menu_id`, `option_text`, `option_id`, `npc_option_npcflag`) VALUES
(12582, 'Get me up into the skies, Sassy', 1, 1);

DELETE FROM `conditions` WHERE `SourceGroup`=12582 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12582, 0, 0, 0, 9, 0, 25066, 0, 0, 0, 0, 0, '', 'Sassy Headwrench - Show gossip only if quest 25066 is active');

UPDATE `creature_template` SET `minlevel`=10, `maxlevel`=10, `VehicleId`=669, `InhabitType`=4, `speed_walk`=2, `speed_run`=2.14286 WHERE `entry`=39074;

DELETE FROM conditions WHERE SourceEntry = '73477' AND ConditionValue2 = '39039';
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 7, 73477, 0, 0, 31, 0, 3, 39039, 0, 0, 0, '', 'Rockets - Only on Stealth Fighters');

-- Pride of Kezan
SET @ENTRY := 39074;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,73446,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Flight Speed");

-- Kilag Gorefang
SET @ENTRY := 39066;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,25100,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accepted - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,25100,0,0,0,85,73532,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accepted - Start Event");

DELETE FROM `creature_text` WHERE `entry`=39066;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39066,0,0,'Run, Bastia! Get $n to Sky Falls and the labor mine.',12,0,100,0,0,0,'Comment');

-- Slinky Sharpshiv
SET @ENTRY := 38517;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,25109,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,50,0,0,10,4,17,21,11,10,10,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Random Emote");

DELETE FROM `creature_text` WHERE `entry`=38517;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38517,0,0,'Okay. We\'re going to move away from the exploding volcano and try to hook up with the orcs for the final assault on the Trade Prince. See you on the other side... I hope.',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `speed_run`=2.42857, `VehicleId`=530, `unit_flags`=768 WHERE `entry`=39152;

DELETE FROM `waypoints` WHERE `entry` = '39152';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(39152, 1, 1714.96, 2819.47, 30.42, 'Bastia (Final WP)'),
(39152, 2, 1707.88, 2792.43, 37.86, 'Bastia (Final WP)'),
(39152, 3, 1703.09, 2784.44, 41.27, 'Bastia (Final WP)'),
(39152, 4, 1670.68, 2756.88, 63.68, 'Bastia (Final WP)'),
(39152, 5, 1657.71, 2747.00, 70.90, 'Bastia (Final WP)'),
(39152, 6, 1633.91, 2734.59, 78.28, 'Bastia (Final WP)'),
(39152, 7, 1616.70, 2721.59, 81.76, 'Bastia (Final WP)'),
(39152, 8, 1572.28, 2715.02, 84.12, 'Bastia (Final WP)'),
(39152, 9, 1564.04, 2695.70, 88.68, 'Bastia (Final WP)'),
(39152, 10, 1567.62, 2663.23, 94.87, 'Bastia (Final WP)'),
(39152, 11, 1623.82, 2634.79, 97.20, 'Bastia (Final WP)'),
(39152, 12, 1713.68, 2598.67, 95.42, 'Bastia (Final WP)'),
(39152, 13, 1749.10, 2550.22, 102.83, 'Bastia (Final WP)'),
(39152, 14, 1746.67, 2511.83, 118.19, 'Bastia (Final WP)'),
(39152, 15, 1752.73, 2507.32, 120.90, 'Bastia (Final WP)'),
(39152, 16, 1776.12, 2503.59, 131.01, 'Bastia (Final WP)'),
(39152, 17, 1782.13, 2480.45, 143.69, 'Bastia (Final WP)'),
(39152, 18, 1787.56, 2465.03, 147.09, 'Bastia (Final WP)'),
(39152, 19, 1777.48, 2440.84, 151.67, 'Bastia (Final WP)'),
(39152, 20, 1738.61, 2365.81, 163.30, 'Bastia (Final WP)'),
(39152, 21, 1740.81, 2346.12, 171.74, 'Bastia (Final WP)'),
(39152, 22, 1744.08, 2334.55, 179.99, 'Bastia (Final WP)'),
(39152, 23, 1746.76, 2330.68, 182.27, 'Bastia (Final WP)'),
(39152, 24, 1748.23, 2316.96, 187.60, 'Bastia (Final WP)'),
(39152, 25, 1750.98, 2311.43, 186.29, 'Bastia (Final WP)'),
(39152, 26, 1773.27, 2289.74, 188.23, 'Bastia (Final WP)'),
(39152, 27, 1788.99, 2272.29, 190.49, 'Bastia (Final WP)'),
(39152, 28, 1799.57, 2270.48, 186.69, 'Bastia (Final WP)'),
(39152, 29, 1805.55, 2269.24, 179.01, 'Bastia (Final WP)'),
(39152, 30, 1809.72, 2265.50, 180.61, 'Bastia (Final WP)'),
(39152, 31, 1821.29, 2253.63, 180.80, 'Bastia (Final WP)'),
(39152, 32, 1824.52, 2228.77, 182.51, 'Bastia (Final WP)'),
(39152, 33, 1869.81, 2137.97, 183.70, 'Bastia (Final WP)'),
(39152, 34, 1902.58, 2089.69, 184.91, 'Bastia (Final WP)'),
(39152, 35, 1877.69, 2000.34, 209.17, 'Bastia (Final WP)'),
(39152, 36, 1858.32, 1980.25, 220.63, 'Bastia (Final WP)'),
(39152, 37, 1831.00, 1959.67, 221.01, 'Bastia (Final WP)');

-- Bastia
SET @ENTRY := 39152;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,53,1,39152,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - WP Start"),
(@ENTRY,@SOURCETYPE,1,0,40,0,100,0,37,0,0,0,28,73531,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Despawn");

UPDATE `creature_template` SET `lootid`=39193, `mingold`=19, `maxgold`=19 WHERE `entry`=39193;

DELETE FROM `creature_loot_template` WHERE `entry` = '39193';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(39193, 117, 4.8756, 1, 0, 1, 1),
(39193, 118, 1.2683, 1, 0, 1, 1),
(39193, 159, 2.3, 1, 0, 1, 1),
(39193, 414, 12.4161, 1, 0, 1, 1),
(39193, 727, 0.2971, 1, 0, 1, 1),
(39193, 767, 0.1212, 1, 0, 1, 1),
(39193, 768, 0.3412, 1, 0, 1, 1),
(39193, 774, 1.4247, 1, 0, 1, 1),
(39193, 805, 0.1, 1, 0, 1, 1),
(39193, 818, 4.698, 1, 0, 1, 1),
(39193, 828, 0.1, 1, 0, 1, 1),
(39193, 858, 15.4362, 1, 0, 1, 1),
(39193, 1210, 1.0067, 1, 0, 1, 1),
(39193, 1411, 0.4744, 1, 0, 1, 1),
(39193, 1412, 0.4916, 1, 0, 1, 1),
(39193, 1413, 0.5066, 1, 0, 1, 1),
(39193, 1414, 0.4624, 1, 0, 1, 1),
(39193, 1415, 0.4258, 1, 0, 1, 1),
(39193, 1416, 0.4894, 1, 0, 1, 1),
(39193, 1417, 0.5021, 1, 0, 1, 1),
(39193, 1418, 0.3479, 1, 0, 1, 1),
(39193, 1419, 0.3943, 1, 0, 1, 1),
(39193, 1420, 0.4826, 1, 0, 1, 1),
(39193, 1422, 0.5036, 1, 0, 1, 1),
(39193, 1423, 0.431, 1, 0, 1, 1),
(39193, 1425, 0.4055, 1, 0, 1, 1),
(39193, 1427, 0.339, 1, 0, 1, 1),
(39193, 1429, 0.431, 1, 0, 1, 1),
(39193, 1430, 0.3734, 1, 0, 1, 1),
(39193, 1431, 0.4557, 1, 0, 1, 1),
(39193, 1433, 0.3801, 1, 0, 1, 1),
(39193, 1697, 0.003, 1, 0, 1, 1),
(39193, 2070, 0.0007, 1, 0, 1, 1),
(39193, 2075, 0.1339, 1, 0, 1, 1),
(39193, 2138, 0.5298, 1, 0, 1, 1),
(39193, 2140, 0.1362, 1, 0, 1, 1),
(39193, 2212, 0.327, 1, 0, 1, 1),
(39193, 2213, 0.3419, 1, 0, 1, 1),
(39193, 2406, 0.05, 1, 0, 1, 1),
(39193, 2407, 0.05, 1, 0, 1, 1),
(39193, 2408, 0.05, 1, 0, 1, 1),
(39193, 2553, 0.05, 1, 0, 1, 1),
(39193, 2555, 0.05, 1, 0, 1, 1),
(39193, 2589, 56.7, 1, 0, 1, 2),
(39193, 2598, 0.1579, 1, 0, 1, 1),
(39193, 2635, 0.2761, 1, 0, 1, 1),
(39193, 2642, 0.306, 1, 0, 1, 1),
(39193, 2643, 0.3629, 1, 0, 1, 1),
(39193, 2645, 0.3479, 1, 0, 1, 1),
(39193, 2646, 0.3442, 1, 0, 1, 1),
(39193, 2648, 0.2941, 1, 0, 1, 1),
(39193, 2773, 0.4908, 1, 0, 1, 1),
(39193, 2774, 0.5103, 1, 0, 1, 1),
(39193, 3189, 0.1235, 1, 0, 1, 1),
(39193, 3190, 0.1332, 1, 0, 1, 1),
(39193, 3192, 0.1167, 1, 0, 1, 1),
(39193, 3279, 0.0576, 1, 0, 1, 1),
(39193, 3280, 0.2305, 1, 0, 1, 1),
(39193, 3281, 0.1025, 1, 0, 1, 1),
(39193, 3282, 0.0621, 1, 0, 1, 1),
(39193, 3283, 0.0292, 1, 0, 1, 1),
(39193, 3284, 0.0696, 1, 0, 1, 1),
(39193, 3285, 0.2147, 1, 0, 1, 1),
(39193, 3286, 0.0838, 1, 0, 1, 1),
(39193, 3287, 0.0875, 1, 0, 1, 1),
(39193, 3288, 0.0352, 1, 0, 1, 1),
(39193, 3289, 0.1212, 1, 0, 1, 1),
(39193, 3290, 0.1354, 1, 0, 1, 1),
(39193, 3291, 0.0426, 1, 0, 1, 1),
(39193, 3292, 0.0202, 1, 0, 1, 1),
(39193, 3303, 0.0868, 1, 0, 1, 1),
(39193, 3312, 0.0135, 1, 0, 1, 1),
(39193, 3370, 0.4033, 1, 0, 1, 1),
(39193, 3373, 0.4213, 1, 0, 1, 1),
(39193, 3609, 0.1661, 1, 0, 1, 1),
(39193, 3610, 0.05, 1, 0, 1, 1),
(39193, 3642, 0.3689, 1, 0, 1, 1),
(39193, 3644, 0.0875, 1, 0, 1, 1),
(39193, 3649, 0.1063, 1, 0, 1, 1),
(39193, 3650, 0.1422, 1, 0, 1, 1),
(39193, 3653, 0.006, 1, 0, 1, 1),
(39193, 3654, 0.0082, 1, 0, 1, 1),
(39193, 4408, 0.05, 1, 0, 1, 1),
(39193, 4496, 0.1, 1, 0, 1, 1),
(39193, 4537, 11.745, 1, 0, 1, 1),
(39193, 4541, 12.4161, 1, 0, 1, 1),
(39193, 4561, 0.1975, 1, 0, 1, 1),
(39193, 4562, 0.3225, 1, 0, 1, 1),
(39193, 4563, 0.3861, 1, 0, 1, 1),
(39193, 4564, 0.1, 1, 0, 1, 1),
(39193, 4566, 0.1, 1, 0, 1, 1),
(39193, 4577, 0.05, 1, 0, 1, 1),
(39193, 4668, 0.2349, 1, 0, 1, 1),
(39193, 4669, 0.1811, 1, 0, 1, 1),
(39193, 4671, 0.4385, 1, 0, 1, 1),
(39193, 4672, 0.315, 1, 0, 1, 1),
(39193, 4674, 0.3479, 1, 0, 1, 1),
(39193, 4675, 0.2357, 1, 0, 1, 1),
(39193, 4680, 0.0247, 1, 0, 1, 1),
(39193, 4686, 0.1077, 1, 0, 1, 1),
(39193, 4692, 0.0643, 1, 0, 1, 1),
(39193, 5069, 1.1844, 1, 0, 1, 1),
(39193, 5368, 50, 1, 0, 1, 1),
(39193, 5571, 0.1, 1, 0, 1, 1),
(39193, 5572, 0.1, 1, 0, 1, 1),
(39193, 6271, 0.05, 1, 0, 1, 1),
(39193, 6303, 0.0045, 1, 0, 1, 1),
(39193, 6342, 0.05, 1, 0, 1, 1),
(39193, 6527, 0.0224, 1, 0, 1, 1),
(39193, 7288, 0.05, 1, 0, 1, 1),
(39193, 8178, 0.3015, 1, 0, 1, 1),
(39193, 8180, 0.1758, 1, 0, 1, 1),
(39193, 8181, 0.3038, 1, 0, 1, 1),
(39193, 14086, 0.2739, 1, 0, 1, 1),
(39193, 14087, 0.2103, 1, 0, 1, 1),
(39193, 14088, 0.2095, 1, 0, 1, 1),
(39193, 14089, 0.2716, 1, 0, 1, 1),
(39193, 14090, 0.1048, 1, 0, 1, 1),
(39193, 14091, 0.0569, 1, 0, 1, 1),
(39193, 14093, 0.3719, 1, 0, 1, 1),
(39193, 14094, 0.0569, 1, 0, 1, 1),
(39193, 14095, 0.1452, 1, 0, 1, 1),
(39193, 14098, 0.2402, 1, 0, 1, 1),
(39193, 14099, 0.0741, 1, 0, 1, 1),
(39193, 14102, 0.0397, 1, 0, 1, 1),
(39193, 14110, 0.0374, 1, 0, 1, 1),
(39193, 15003, 0.1796, 1, 0, 1, 1),
(39193, 15004, 0.4085, 1, 0, 1, 1),
(39193, 15005, 0.3367, 1, 0, 1, 1),
(39193, 15006, 0.1003, 1, 0, 1, 1),
(39193, 15007, 0.2888, 1, 0, 1, 1),
(39193, 15008, 0.2641, 1, 0, 1, 1),
(39193, 15009, 0.0973, 1, 0, 1, 1),
(39193, 15010, 0.0935, 1, 0, 1, 1),
(39193, 15015, 0.0554, 1, 0, 1, 1),
(39193, 15297, 0.0756, 1, 0, 1, 1),
(39193, 15298, 0.0052, 1, 0, 1, 1),
(39193, 15299, 0.2095, 1, 0, 1, 1),
(39193, 15301, 0.0224, 1, 0, 1, 1),
(39193, 15302, 0.1549, 1, 0, 1, 1),
(39193, 15472, 0.2843, 1, 0, 1, 1),
(39193, 15473, 0.1893, 1, 0, 1, 1),
(39193, 15474, 0.1706, 1, 0, 1, 1),
(39193, 15475, 0.1519, 1, 0, 1, 1),
(39193, 15476, 0.1833, 1, 0, 1, 1),
(39193, 15477, 0.0816, 1, 0, 1, 1),
(39193, 15478, 0.1384, 1, 0, 1, 1),
(39193, 15479, 0.0771, 1, 0, 1, 1),
(39193, 15480, 0.0314, 1, 0, 1, 1),
(39193, 15481, 0.0232, 1, 0, 1, 1),
(39193, 15482, 0.0823, 1, 0, 1, 1),
(39193, 15483, 0.2013, 1, 0, 1, 1),
(39193, 15484, 0.0516, 1, 0, 1, 1),
(39193, 15486, 0.1279, 1, 0, 1, 1),
(39193, 15944, 0.1294, 1, 0, 1, 1),
(39193, 15969, 0.0928, 1, 0, 1, 1),
(39193, 15970, 0.0142, 1, 0, 1, 1),
(39193, 47530, -0.0052, 1, 0, 1, 1),
(39193, 49424, -0.0022, 1, 0, 1, 1),
(39193, 50381, -0.0112, 1, 0, 1, 1),
(39193, 50437, -0.0172, 1, 0, 1, 1),
(39193, 50438, 0.0187, 1, 0, 1, 1),
(39193, 52035, -0.003, 1, 0, 1, 1),
(39193, 52346, -0.0007, 1, 0, 1, 1),
(39193, 52347, -0.0045, 1, 0, 1, 1),
(39193, 52349, -0.0015, 1, 0, 1, 1),
(39193, 52483, -33.6506, 1, 0, 1, 1),
(39193, 55983, 0.003, 1, 0, 1, 1),
(39193, 67257, 0.0015, 1, 0, 1, 1);

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '25110';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(49416, 4924, 25110, 25110, 1, 11);

UPDATE `quest_template` SET `RewardSpellCast`=0 WHERE `Id`=25110;

DELETE FROM `creature_addon` WHERE `guid` = '833366';
INSERT INTO `creature_addon` (`guid`, `bytes2`, `auras`) VALUES
(833366, 1, '49414');

DELETE FROM `spell_target_position` WHERE `id` = '73603';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(73603, 648, 1781.03, 1983.22, 173.11, 2.46);

DELETE FROM `spell_script_names` WHERE `spell_id` = '73603';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(73603, 'spell_summon_generic_controller');

UPDATE `creature_template` SET `minlevel`=10, `maxlevel`=10, `unit_flags`=768, `ScriptName`='npc_assistant_greely' WHERE `entry`=39199;

DELETE FROM `spell_area` WHERE `spell` = '73603' AND `quest_start` = '25110';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`) VALUES
(73603, 4924, 25110, 25184, 1),
(73603, 4923, 25110, 25184, 1),
(73603, 4951, 25110, 25184, 1);

DELETE FROM `creature_text` WHERE `entry`=39199;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39199,0,0,'I\'VE GOT AN IDEA!',14,0,100,0,0,0,'Comment'),
(39199,1,0,'We\'ve got to get our people out of here, $n. The key is to get them to drink plenty of Kaja\'Cola Zero-One!',12,0,100,0,0,0,'Comment'),
(39199,2,0,'$n, we need to escape through the northern tunnel!',12,0,100,0,0,0,'Comment'),
(39199,3,0,'We\'re not a part of your system!',14,0,100,0,0,0,'Comment');

-- Ace
SET @ENTRY := 38441;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,42,110,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,1,0,19,0,100,0,25203,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,50,0,0,10,4,17,21,11,10,10,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Random Emote");

DELETE FROM `creature_text` WHERE `entry`=38441;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38441,0,0,'I never liked that guy. He stole your girlfriend. I say, good riddance!',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=38409;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38409,0,0,'Mom detectors.',14,0,100,0,0,0,'Comment'),
(38409,0,1,'Bagel-holes!',14,0,100,0,0,0,'Comment'),
(38409,0,2,'So I have this idea for a movie. Three gnomes find a bracelet of power...',14,0,100,0,0,0,'Comment'),
(38409,0,3,'We put a whole town... in a tiny little box!',14,0,100,0,0,0,'Comment'),
(38409,0,4,'How about smiling monkey wallets?',14,0,100,0,0,0,'Comment'),
(38409,0,5,'Explosive fire extinguishers! We\'ll fight fire... WITH fire!',14,0,100,0,0,0,'Comment'),
(38409,0,6,'Spoon sharpeners!',14,0,100,0,0,0,'Comment'),
(38409,0,7,'A truck that delivers ice cream. With a catapult.',14,0,100,0,0,0,'Comment'),
(38409,0,8,'I\'ve got it: Squeezeable rocks!',14,0,100,0,0,0,'Comment'),
(38409,0,9,'Clowns. Instead of making you laugh, they\'re there for beating.',14,0,100,0,0,0,'Comment'),
(38409,0,10,'Thirteen-sided dice!',14,0,100,0,0,0,'Comment'),
(38409,0,11,'Tauren paladins!',14,0,100,0,0,0,'Comment'),
(38409,0,12,'Invisible condiments. For an unobstructed view of your food.',14,0,100,0,0,0,'Comment'),
(38409,0,13,'Feed pigs rubber, \'till they bounce. There\'s got to be an application for that.',14,0,100,0,0,0,'Comment'),
(38409,0,14,'A globe that shows the inside of the planet... on the outside. So you know where to dig!',14,0,100,0,0,0,'Comment'),
(38409,0,15,'Handheld one-way mirrors!',14,0,100,0,0,0,'Comment'),
(38409,0,16,'Nose-stenders. For smelling things in different rooms.',14,0,100,0,0,0,'Comment'),
(38409,0,17,'Attach two vehicles to a bigger vehicle, and then have the passengers jump from one vehicle to the other!',14,0,100,0,0,0,'Comment'),
(38409,0,18,'Electrical wires used to send messages over great distances... no, impractical. Giant rockets, with speakers attached...',14,0,100,0,0,0,'Comment'),
(38409,0,19,'Houses made of dirt! When you clean them... THEY\'RE GONE.',14,0,100,0,0,0,'Comment'),
(38409,0,20,'Stairways... for horizontal surfaces!',14,0,100,0,0,0,'Comment'),
(38409,0,21,'Half man... half sharkalligator!',14,0,100,0,0,0,'Comment'),
(38409,0,22,'Leashes... with pre-attached pets.',14,0,100,0,0,0,'Comment'),
(38409,0,23,'A big convention, see? To show off all of our inventions. We\'ll call it GoblinCon. And we\'ll give away special pets! Except most people will probably sell them for profit on the auction house.',14,0,100,0,0,0,'Comment'),
(38409,0,24,'Distilling the juice out of Kaja\'mite to make a delicious, carbonated beverage that will give people IDEAS! Hey, wait a minute...',14,0,100,0,0,0,'Comment'),
(38409,0,25,'Giant gnomes! No, wait... tiny giants!',14,0,100,0,0,0,'Comment'),
(38409,0,26,'Goblins with gills!',14,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=38745;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38745,0,0,'Mom detectors.',14,0,100,0,0,0,'Comment'),
(38745,0,1,'Bagel-holes!',14,0,100,0,0,0,'Comment'),
(38745,0,2,'So I have this idea for a movie. Three gnomes find a bracelet of power...',14,0,100,0,0,0,'Comment'),
(38745,0,3,'We put a whole town... in a tiny little box!',14,0,100,0,0,0,'Comment'),
(38745,0,4,'How about smiling monkey wallets?',14,0,100,0,0,0,'Comment'),
(38745,0,5,'Explosive fire extinguishers! We\'ll fight fire... WITH fire!',14,0,100,0,0,0,'Comment'),
(38745,0,6,'Spoon sharpeners!',14,0,100,0,0,0,'Comment'),
(38745,0,7,'A truck that delivers ice cream. With a catapult.',14,0,100,0,0,0,'Comment'),
(38745,0,8,'I\'ve got it: Squeezeable rocks!',14,0,100,0,0,0,'Comment'),
(38745,0,9,'Clowns. Instead of making you laugh, they\'re there for beating.',14,0,100,0,0,0,'Comment'),
(38745,0,10,'Thirteen-sided dice!',14,0,100,0,0,0,'Comment'),
(38745,0,11,'Tauren paladins!',14,0,100,0,0,0,'Comment'),
(38745,0,12,'Invisible condiments. For an unobstructed view of your food.',14,0,100,0,0,0,'Comment'),
(38745,0,13,'Feed pigs rubber, \'till they bounce. There\'s got to be an application for that.',14,0,100,0,0,0,'Comment'),
(38745,0,14,'A globe that shows the inside of the planet... on the outside. So you know where to dig!',14,0,100,0,0,0,'Comment'),
(38745,0,15,'Handheld one-way mirrors!',14,0,100,0,0,0,'Comment'),
(38745,0,16,'Nose-stenders. For smelling things in different rooms.',14,0,100,0,0,0,'Comment'),
(38745,0,17,'Attach two vehicles to a bigger vehicle, and then have the passengers jump from one vehicle to the other!',14,0,100,0,0,0,'Comment'),
(38745,0,18,'Electrical wires used to send messages over great distances... no, impractical. Giant rockets, with speakers attached...',14,0,100,0,0,0,'Comment'),
(38745,0,19,'Houses made of dirt! When you clean them... THEY\'RE GONE.',14,0,100,0,0,0,'Comment'),
(38745,0,20,'Stairways... for horizontal surfaces!',14,0,100,0,0,0,'Comment'),
(38745,0,21,'Half man... half sharkalligator!',14,0,100,0,0,0,'Comment'),
(38745,0,22,'Leashes... with pre-attached pets.',14,0,100,0,0,0,'Comment'),
(38745,0,23,'A big convention, see? To show off all of our inventions. We\'ll call it GoblinCon. And we\'ll give away special pets! Except most people will probably sell them for profit on the auction house.',14,0,100,0,0,0,'Comment'),
(38745,0,24,'Distilling the juice out of Kaja\'mite to make a delicious, carbonated beverage that will give people IDEAS! Hey, wait a minute...',14,0,100,0,0,0,'Comment'),
(38745,0,25,'Giant gnomes! No, wait... tiny giants!',14,0,100,0,0,0,'Comment'),
(38745,0,26,'Goblins with gills!',14,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=38745;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38745,0,0,'Mom detectors.',14,0,100,0,0,0,'Comment'),
(38745,0,1,'Bagel-holes!',14,0,100,0,0,0,'Comment'),
(38745,0,2,'So I have this idea for a movie. Three gnomes find a bracelet of power...',14,0,100,0,0,0,'Comment'),
(38745,0,3,'We put a whole town... in a tiny little box!',14,0,100,0,0,0,'Comment'),
(38745,0,4,'How about smiling monkey wallets?',14,0,100,0,0,0,'Comment'),
(38745,0,5,'Explosive fire extinguishers! We\'ll fight fire... WITH fire!',14,0,100,0,0,0,'Comment'),
(38745,0,6,'Spoon sharpeners!',14,0,100,0,0,0,'Comment'),
(38745,0,7,'A truck that delivers ice cream. With a catapult.',14,0,100,0,0,0,'Comment'),
(38745,0,8,'I\'ve got it: Squeezeable rocks!',14,0,100,0,0,0,'Comment'),
(38745,0,9,'Clowns. Instead of making you laugh, they\'re there for beating.',14,0,100,0,0,0,'Comment'),
(38745,0,10,'Thirteen-sided dice!',14,0,100,0,0,0,'Comment'),
(38745,0,11,'Tauren paladins!',14,0,100,0,0,0,'Comment'),
(38745,0,12,'Invisible condiments. For an unobstructed view of your food.',14,0,100,0,0,0,'Comment'),
(38745,0,13,'Feed pigs rubber, \'till they bounce. There\'s got to be an application for that.',14,0,100,0,0,0,'Comment'),
(38745,0,14,'A globe that shows the inside of the planet... on the outside. So you know where to dig!',14,0,100,0,0,0,'Comment'),
(38745,0,15,'Handheld one-way mirrors!',14,0,100,0,0,0,'Comment'),
(38745,0,16,'Nose-stenders. For smelling things in different rooms.',14,0,100,0,0,0,'Comment'),
(38745,0,17,'Attach two vehicles to a bigger vehicle, and then have the passengers jump from one vehicle to the other!',14,0,100,0,0,0,'Comment'),
(38745,0,18,'Electrical wires used to send messages over great distances... no, impractical. Giant rockets, with speakers attached...',14,0,100,0,0,0,'Comment'),
(38745,0,19,'Houses made of dirt! When you clean them... THEY\'RE GONE.',14,0,100,0,0,0,'Comment'),
(38745,0,20,'Stairways... for horizontal surfaces!',14,0,100,0,0,0,'Comment'),
(38745,0,21,'Half man... half sharkalligator!',14,0,100,0,0,0,'Comment'),
(38745,0,22,'Leashes... with pre-attached pets.',14,0,100,0,0,0,'Comment'),
(38745,0,23,'A big convention, see? To show off all of our inventions. We\'ll call it GoblinCon. And we\'ll give away special pets! Except most people will probably sell them for profit on the auction house.',14,0,100,0,0,0,'Comment'),
(38745,0,24,'Distilling the juice out of Kaja\'mite to make a delicious, carbonated beverage that will give people IDEAS! Hey, wait a minute...',14,0,100,0,0,0,'Comment'),
(38745,0,25,'Giant gnomes! No, wait... tiny giants!',14,0,100,0,0,0,'Comment'),
(38745,0,26,'Goblins with gills!',14,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=38746;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38746,0,0,'Mom detectors.',14,0,100,0,0,0,'Comment'),
(38746,0,1,'Bagel-holes!',14,0,100,0,0,0,'Comment'),
(38746,0,2,'So I have this idea for a movie. Three gnomes find a bracelet of power...',14,0,100,0,0,0,'Comment'),
(38746,0,3,'We put a whole town... in a tiny little box!',14,0,100,0,0,0,'Comment'),
(38746,0,4,'How about smiling monkey wallets?',14,0,100,0,0,0,'Comment'),
(38746,0,5,'Explosive fire extinguishers! We\'ll fight fire... WITH fire!',14,0,100,0,0,0,'Comment'),
(38746,0,6,'Spoon sharpeners!',14,0,100,0,0,0,'Comment'),
(38746,0,7,'A truck that delivers ice cream. With a catapult.',14,0,100,0,0,0,'Comment'),
(38746,0,8,'I\'ve got it: Squeezeable rocks!',14,0,100,0,0,0,'Comment'),
(38746,0,9,'Clowns. Instead of making you laugh, they\'re there for beating.',14,0,100,0,0,0,'Comment'),
(38746,0,10,'Thirteen-sided dice!',14,0,100,0,0,0,'Comment'),
(38746,0,11,'Tauren paladins!',14,0,100,0,0,0,'Comment'),
(38746,0,12,'Invisible condiments. For an unobstructed view of your food.',14,0,100,0,0,0,'Comment'),
(38746,0,13,'Feed pigs rubber, \'till they bounce. There\'s got to be an application for that.',14,0,100,0,0,0,'Comment'),
(38746,0,14,'A globe that shows the inside of the planet... on the outside. So you know where to dig!',14,0,100,0,0,0,'Comment'),
(38746,0,15,'Handheld one-way mirrors!',14,0,100,0,0,0,'Comment'),
(38746,0,16,'Nose-stenders. For smelling things in different rooms.',14,0,100,0,0,0,'Comment'),
(38746,0,17,'Attach two vehicles to a bigger vehicle, and then have the passengers jump from one vehicle to the other!',14,0,100,0,0,0,'Comment'),
(38746,0,18,'Electrical wires used to send messages over great distances... no, impractical. Giant rockets, with speakers attached...',14,0,100,0,0,0,'Comment'),
(38746,0,19,'Houses made of dirt! When you clean them... THEY\'RE GONE.',14,0,100,0,0,0,'Comment'),
(38746,0,20,'Stairways... for horizontal surfaces!',14,0,100,0,0,0,'Comment'),
(38746,0,21,'Half man... half sharkalligator!',14,0,100,0,0,0,'Comment'),
(38746,0,22,'Leashes... with pre-attached pets.',14,0,100,0,0,0,'Comment'),
(38746,0,23,'A big convention, see? To show off all of our inventions. We\'ll call it GoblinCon. And we\'ll give away special pets! Except most people will probably sell them for profit on the auction house.',14,0,100,0,0,0,'Comment'),
(38746,0,24,'Distilling the juice out of Kaja\'mite to make a delicious, carbonated beverage that will give people IDEAS! Hey, wait a minute...',14,0,100,0,0,0,'Comment'),
(38746,0,25,'Giant gnomes! No, wait... tiny giants!',14,0,100,0,0,0,'Comment'),
(38746,0,26,'Goblins with gills!',14,0,100,0,0,0,'Comment');

-- Goblin Survivor
SET @ENTRY := 38409;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,73583,1,0,0,11,73599,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Drink Cola"),
(@ENTRY,@SOURCETYPE,1,0,8,0,100,0,73599,1,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Set Run"),
(@ENTRY,@SOURCETYPE,2,0,8,0,100,0,73599,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,38409,0,0,69,0,0,0,0,0,0,8,0,0,0,2023.25,1828.69,142.42,0.55,"After Talk 0 - Move To Pos"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,0,38409,0,0,41,10000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Force Despawn"),
(@ENTRY,@SOURCETYPE,5,0,8,0,100,0,73583,1,0,0,33,38409,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Drink Cola");

-- Kezan Citizen
SET @ENTRY := 38745;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,42,100,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,1,0,8,0,100,0,73583,1,0,0,11,73599,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Drink Cola"),
(@ENTRY,@SOURCETYPE,2,0,8,0,100,0,73599,1,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Set Run"),
(@ENTRY,@SOURCETYPE,3,0,8,0,100,0,73599,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,0,38745,0,0,69,0,0,0,0,0,0,8,0,0,0,2023.25,1828.69,142.42,0.55,"After Talk 0 - Move To Pos"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,0,38745,0,0,41,10000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Force Despawn"),
(@ENTRY,@SOURCETYPE,6,0,8,0,100,0,73583,1,0,0,33,38409,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit");

UPDATE `creature_template` SET `mindmg`=8, `maxdmg`=13, `attackpower`=3, `dmg_multiplier`=1.2 WHERE `entry`=39195;
UPDATE `gameobject` SET `phaseMask`=32768 WHERE `id`=202574;
UPDATE `gameobject` SET `phaseMask`=32768 WHERE `guid` IN (779569,779568,779565);

DELETE FROM conditions WHERE SourceEntry = '73702' AND ConditionValue2 = '39194';
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 7, 73702, 0, 0, 31, 0, 3, 39194, 0, 0, 0, '', 'Blastshadow Soulstonr - Only on Blastshadow');

UPDATE `gossip_menu_option` SET `option_id`=9, `npc_option_npcflag`=131072 WHERE `menu_id`=10722 AND `id`=0;

DELETE FROM `gossip_menu` WHERE `entry` = '10722';
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES
(10722, 14881);

DELETE FROM `creature_addon` WHERE `guid` = '833416';
INSERT INTO `creature_addon` (`guid`, `bytes2`, `auras`) VALUES
(833416, 1, '49415');

UPDATE `creature_template` SET `ScriptName`='npc_gobber_kaja_cola' WHERE `entry`=39201;

DELETE FROM `spell_area` WHERE `spell` = '73611' AND `quest_start` = '25122';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(73611, 4924, 25122, 25184, 0, 0, 2, 1, 66, 11),
(73611, 4923, 25122, 25184, 0, 0, 2, 1, 66, 11),
(73611, 4951, 25122, 25184, 0, 0, 2, 1, 66, 11);

DELETE FROM `spell_area` WHERE `spell` = '73601' AND `quest_start` = '25122';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(73601, 4924, 25122, 25184, 0, 0, 2, 1, 66, 11),
(73601, 4923, 25122, 25184, 0, 0, 2, 1, 66, 11),
(73601, 4951, 25122, 25184, 0, 0, 2, 1, 66, 11);

DELETE FROM `spell_area` WHERE `spell` = '73609' AND `quest_start` = '25122';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(73609, 4924, 25122, 25184, 0, 0, 2, 1, 66, 11),
(73609, 4923, 25122, 25184, 0, 0, 2, 1, 66, 11),
(73609, 4951, 25122, 25184, 0, 0, 2, 1, 66, 11);

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` = '25122';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(49417, 4924, 25122, 25122, 1, 11);

-- Gobber
SET @ENTRY := 38746;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,73583,1,0,0,33,38746,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit"),
(@ENTRY,@SOURCETYPE,1,0,8,0,100,0,73583,1,0,0,11,73605,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Idea"),
(@ENTRY,@SOURCETYPE,2,0,8,0,100,0,73605,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,4,0,100,0,0,0,0,0,42,98,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,50,0,0,10,4,17,21,11,10,10,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Random Emote");

-- Izzy
SET @ENTRY := 38647;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,73583,1,0,0,33,38647,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit"),
(@ENTRY,@SOURCETYPE,1,0,8,0,100,0,73583,1,0,0,11,73605,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Idea"),
(@ENTRY,@SOURCETYPE,2,0,8,0,100,0,73605,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,19,0,100,0,25202,0,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,50,0,0,10,4,17,21,11,10,10,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Random Emote"),
(@ENTRY,@SOURCETYPE,5,0,20,0,100,0,24924,0,0,0,28,66987,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Remove Invoker Aura"),
(@ENTRY,@SOURCETYPE,6,0,19,0,100,0,24945,0,0,0,1,2,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 2"),
(@ENTRY,@SOURCETYPE,7,0,19,0,100,0,24937,0,0,0,1,3,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 3"),
(@ENTRY,@SOURCETYPE,8,0,19,0,100,0,25202,0,0,0,1,4,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 4");

-- Ace
SET @ENTRY := 38441;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,73583,1,0,0,33,38441,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit"),
(@ENTRY,@SOURCETYPE,1,0,8,0,100,0,73583,1,0,0,11,73605,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Idea"),
(@ENTRY,@SOURCETYPE,2,0,8,0,100,0,73605,1,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,4,0,100,0,0,0,0,0,42,95,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,4,0,19,0,100,0,25203,0,0,0,1,1,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accepted - Talk 1"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,50,0,0,10,4,17,21,11,10,10,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Random Emote");

UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry` IN (39198, 39200, 39201);
UPDATE `creature_template` SET `ScriptName`='npc_ace_kaja_cola' WHERE `entry`=39198;
UPDATE `creature_template` SET `ScriptName`='npc_izzy_kaja_cola' WHERE `entry`=39200;

DELETE FROM `creature_text` WHERE `entry`=38647;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38647,0,0,'Mom detectors.',14,0,100,0,0,0,'Comment'),
(38647,0,1,'Bagel-holes!',14,0,100,0,0,0,'Comment'),
(38647,0,2,'So I have this idea for a movie. Three gnomes find a bracelet of power...',14,0,100,0,0,0,'Comment'),
(38647,0,3,'We put a whole town... in a tiny little box!',14,0,100,0,0,0,'Comment'),
(38647,0,4,'How about smiling monkey wallets?',14,0,100,0,0,0,'Comment'),
(38647,0,5,'Explosive fire extinguishers! We\'ll fight fire... WITH fire!',14,0,100,0,0,0,'Comment'),
(38647,0,6,'Spoon sharpeners!',14,0,100,0,0,0,'Comment'),
(38647,0,7,'A truck that delivers ice cream. With a catapult.',14,0,100,0,0,0,'Comment'),
(38647,0,8,'I\'ve got it: Squeezeable rocks!',14,0,100,0,0,0,'Comment'),
(38647,0,9,'Clowns. Instead of making you laugh, they\'re there for beating.',14,0,100,0,0,0,'Comment'),
(38647,0,10,'Thirteen-sided dice!',14,0,100,0,0,0,'Comment'),
(38647,0,11,'Tauren paladins!',14,0,100,0,0,0,'Comment'),
(38647,0,12,'Invisible condiments. For an unobstructed view of your food.',14,0,100,0,0,0,'Comment'),
(38647,0,13,'Feed pigs rubber, \'till they bounce. There\'s got to be an application for that.',14,0,100,0,0,0,'Comment'),
(38647,0,14,'A globe that shows the inside of the planet... on the outside. So you know where to dig!',14,0,100,0,0,0,'Comment'),
(38647,0,15,'Handheld one-way mirrors!',14,0,100,0,0,0,'Comment'),
(38647,0,16,'Nose-stenders. For smelling things in different rooms.',14,0,100,0,0,0,'Comment'),
(38647,0,17,'Attach two vehicles to a bigger vehicle, and then have the passengers jump from one vehicle to the other!',14,0,100,0,0,0,'Comment'),
(38647,0,18,'Electrical wires used to send messages over great distances... no, impractical. Giant rockets, with speakers attached...',14,0,100,0,0,0,'Comment'),
(38647,0,19,'Houses made of dirt! When you clean them... THEY\'RE GONE.',14,0,100,0,0,0,'Comment'),
(38647,0,20,'Stairways... for horizontal surfaces!',14,0,100,0,0,0,'Comment'),
(38647,0,21,'Half man... half sharkalligator!',14,0,100,0,0,0,'Comment'),
(38647,0,22,'Leashes... with pre-attached pets.',14,0,100,0,0,0,'Comment'),
(38647,0,23,'A big convention, see? To show off all of our inventions. We\'ll call it GoblinCon. And we\'ll give away special pets! Except most people will probably sell them for profit on the auction house.',14,0,100,0,0,0,'Comment'),
(38647,0,24,'Distilling the juice out of Kaja\'mite to make a delicious, carbonated beverage that will give people IDEAS! Hey, wait a minute...',14,0,100,0,0,0,'Comment'),
(38647,0,25,'Giant gnomes! No, wait... tiny giants!',14,0,100,0,0,0,'Comment'),
(38647,0,26,'Goblins with gills!',14,0,100,0,0,0,'Comment'),
(38647,1,0,'You cannot let him walk all over you like that! Go get his heart, girl!',12,0,100,0,0,0,'Comment'),
(38647,2,0,'$n, you gotta get in there and rescue our people!',12,0,100,0,0,0,'Comment'),
(38647,3,0,'Goblin zombies? The Town-In-A-Box has to be warned!',12,0,100,0,0,0,'Comment'),
(38647,4,0,'You cannot let him walk all over you like that! Go get his heart, girl!',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=38441;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38441,0,0,'Mom detectors.',14,0,100,0,0,0,'Comment'),
(38441,0,1,'Bagel-holes!',14,0,100,0,0,0,'Comment'),
(38441,0,2,'So I have this idea for a movie. Three gnomes find a bracelet of power...',14,0,100,0,0,0,'Comment'),
(38441,0,3,'We put a whole town... in a tiny little box!',14,0,100,0,0,0,'Comment'),
(38441,0,4,'How about smiling monkey wallets?',14,0,100,0,0,0,'Comment'),
(38441,0,5,'Explosive fire extinguishers! We\'ll fight fire... WITH fire!',14,0,100,0,0,0,'Comment'),
(38441,0,6,'Spoon sharpeners!',14,0,100,0,0,0,'Comment'),
(38441,0,7,'A truck that delivers ice cream. With a catapult.',14,0,100,0,0,0,'Comment'),
(38441,0,8,'I\'ve got it: Squeezeable rocks!',14,0,100,0,0,0,'Comment'),
(38441,0,9,'Clowns. Instead of making you laugh, they\'re there for beating.',14,0,100,0,0,0,'Comment'),
(38441,0,10,'Thirteen-sided dice!',14,0,100,0,0,0,'Comment'),
(38441,0,11,'Tauren paladins!',14,0,100,0,0,0,'Comment'),
(38441,0,12,'Invisible condiments. For an unobstructed view of your food.',14,0,100,0,0,0,'Comment'),
(38441,0,13,'Feed pigs rubber, \'till they bounce. There\'s got to be an application for that.',14,0,100,0,0,0,'Comment'),
(38441,0,14,'A globe that shows the inside of the planet... on the outside. So you know where to dig!',14,0,100,0,0,0,'Comment'),
(38441,0,15,'Handheld one-way mirrors!',14,0,100,0,0,0,'Comment'),
(38441,0,16,'Nose-stenders. For smelling things in different rooms.',14,0,100,0,0,0,'Comment'),
(38441,0,17,'Attach two vehicles to a bigger vehicle, and then have the passengers jump from one vehicle to the other!',14,0,100,0,0,0,'Comment'),
(38441,0,18,'Electrical wires used to send messages over great distances... no, impractical. Giant rockets, with speakers attached...',14,0,100,0,0,0,'Comment'),
(38441,0,19,'Houses made of dirt! When you clean them... THEY\'RE GONE.',14,0,100,0,0,0,'Comment'),
(38441,0,20,'Stairways... for horizontal surfaces!',14,0,100,0,0,0,'Comment'),
(38441,0,21,'Half man... half sharkalligator!',14,0,100,0,0,0,'Comment'),
(38441,0,22,'Leashes... with pre-attached pets.',14,0,100,0,0,0,'Comment'),
(38441,0,23,'A big convention, see? To show off all of our inventions. We\'ll call it GoblinCon. And we\'ll give away special pets! Except most people will probably sell them for profit on the auction house.',14,0,100,0,0,0,'Comment'),
(38441,0,24,'Distilling the juice out of Kaja\'mite to make a delicious, carbonated beverage that will give people IDEAS! Hey, wait a minute...',14,0,100,0,0,0,'Comment'),
(38441,0,25,'Giant gnomes! No, wait... tiny giants!',14,0,100,0,0,0,'Comment'),
(38441,0,26,'Goblins with gills!',14,0,100,0,0,0,'Comment'),
(38441,1,0,'I never liked that guy. He stole your girlfriend. I say, good riddance!',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=39198;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39198,0,0,'Mom detectors.',14,0,100,0,0,0,'Comment'),
(39198,0,1,'Bagel-holes!',14,0,100,0,0,0,'Comment'),
(39198,0,2,'So I have this idea for a movie. Three gnomes find a bracelet of power...',14,0,100,0,0,0,'Comment'),
(39198,0,3,'We put a whole town... in a tiny little box!',14,0,100,0,0,0,'Comment'),
(39198,0,4,'How about smiling monkey wallets?',14,0,100,0,0,0,'Comment'),
(39198,0,5,'Explosive fire extinguishers! We\'ll fight fire... WITH fire!',14,0,100,0,0,0,'Comment'),
(39198,0,6,'Spoon sharpeners!',14,0,100,0,0,0,'Comment'),
(39198,0,7,'A truck that delivers ice cream. With a catapult.',14,0,100,0,0,0,'Comment'),
(39198,0,8,'I\'ve got it: Squeezeable rocks!',14,0,100,0,0,0,'Comment'),
(39198,0,9,'Clowns. Instead of making you laugh, they\'re there for beating.',14,0,100,0,0,0,'Comment'),
(39198,0,10,'Thirteen-sided dice!',14,0,100,0,0,0,'Comment'),
(39198,0,11,'Tauren paladins!',14,0,100,0,0,0,'Comment'),
(39198,0,12,'Invisible condiments. For an unobstructed view of your food.',14,0,100,0,0,0,'Comment'),
(39198,0,13,'Feed pigs rubber, \'till they bounce. There\'s got to be an application for that.',14,0,100,0,0,0,'Comment'),
(39198,0,14,'A globe that shows the inside of the planet... on the outside. So you know where to dig!',14,0,100,0,0,0,'Comment'),
(39198,0,15,'Handheld one-way mirrors!',14,0,100,0,0,0,'Comment'),
(39198,0,16,'Nose-stenders. For smelling things in different rooms.',14,0,100,0,0,0,'Comment'),
(39198,0,17,'Attach two vehicles to a bigger vehicle, and then have the passengers jump from one vehicle to the other!',14,0,100,0,0,0,'Comment'),
(39198,0,18,'Electrical wires used to send messages over great distances... no, impractical. Giant rockets, with speakers attached...',14,0,100,0,0,0,'Comment'),
(39198,0,19,'Houses made of dirt! When you clean them... THEY\'RE GONE.',14,0,100,0,0,0,'Comment'),
(39198,0,20,'Stairways... for horizontal surfaces!',14,0,100,0,0,0,'Comment'),
(39198,0,21,'Half man... half sharkalligator!',14,0,100,0,0,0,'Comment'),
(39198,0,22,'Leashes... with pre-attached pets.',14,0,100,0,0,0,'Comment'),
(39198,0,23,'A big convention, see? To show off all of our inventions. We\'ll call it GoblinCon. And we\'ll give away special pets! Except most people will probably sell them for profit on the auction house.',14,0,100,0,0,0,'Comment'),
(39198,0,24,'Distilling the juice out of Kaja\'mite to make a delicious, carbonated beverage that will give people IDEAS! Hey, wait a minute...',14,0,100,0,0,0,'Comment'),
(39198,0,25,'Giant gnomes! No, wait... tiny giants!',14,0,100,0,0,0,'Comment'),
(39198,0,26,'Goblins with gills!',14,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=39200;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39200,0,0,'Mom detectors.',14,0,100,0,0,0,'Comment'),
(39200,0,1,'Bagel-holes!',14,0,100,0,0,0,'Comment'),
(39200,0,2,'So I have this idea for a movie. Three gnomes find a bracelet of power...',14,0,100,0,0,0,'Comment'),
(39200,0,3,'We put a whole town... in a tiny little box!',14,0,100,0,0,0,'Comment'),
(39200,0,4,'How about smiling monkey wallets?',14,0,100,0,0,0,'Comment'),
(39200,0,5,'Explosive fire extinguishers! We\'ll fight fire... WITH fire!',14,0,100,0,0,0,'Comment'),
(39200,0,6,'Spoon sharpeners!',14,0,100,0,0,0,'Comment'),
(39200,0,7,'A truck that delivers ice cream. With a catapult.',14,0,100,0,0,0,'Comment'),
(39200,0,8,'I\'ve got it: Squeezeable rocks!',14,0,100,0,0,0,'Comment'),
(39200,0,9,'Clowns. Instead of making you laugh, they\'re there for beating.',14,0,100,0,0,0,'Comment'),
(39200,0,10,'Thirteen-sided dice!',14,0,100,0,0,0,'Comment'),
(39200,0,11,'Tauren paladins!',14,0,100,0,0,0,'Comment'),
(39200,0,12,'Invisible condiments. For an unobstructed view of your food.',14,0,100,0,0,0,'Comment'),
(39200,0,13,'Feed pigs rubber, \'till they bounce. There\'s got to be an application for that.',14,0,100,0,0,0,'Comment'),
(39200,0,14,'A globe that shows the inside of the planet... on the outside. So you know where to dig!',14,0,100,0,0,0,'Comment'),
(39200,0,15,'Handheld one-way mirrors!',14,0,100,0,0,0,'Comment'),
(39200,0,16,'Nose-stenders. For smelling things in different rooms.',14,0,100,0,0,0,'Comment'),
(39200,0,17,'Attach two vehicles to a bigger vehicle, and then have the passengers jump from one vehicle to the other!',14,0,100,0,0,0,'Comment'),
(39200,0,18,'Electrical wires used to send messages over great distances... no, impractical. Giant rockets, with speakers attached...',14,0,100,0,0,0,'Comment'),
(39200,0,19,'Houses made of dirt! When you clean them... THEY\'RE GONE.',14,0,100,0,0,0,'Comment'),
(39200,0,20,'Stairways... for horizontal surfaces!',14,0,100,0,0,0,'Comment'),
(39200,0,21,'Half man... half sharkalligator!',14,0,100,0,0,0,'Comment'),
(39200,0,22,'Leashes... with pre-attached pets.',14,0,100,0,0,0,'Comment'),
(39200,0,23,'A big convention, see? To show off all of our inventions. We\'ll call it GoblinCon. And we\'ll give away special pets! Except most people will probably sell them for profit on the auction house.',14,0,100,0,0,0,'Comment'),
(39200,0,24,'Distilling the juice out of Kaja\'mite to make a delicious, carbonated beverage that will give people IDEAS! Hey, wait a minute...',14,0,100,0,0,0,'Comment'),
(39200,0,25,'Giant gnomes! No, wait... tiny giants!',14,0,100,0,0,0,'Comment'),
(39200,0,26,'Goblins with gills!',14,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=39201;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39201,0,0,'Mom detectors.',14,0,100,0,0,0,'Comment'),
(39201,0,1,'Bagel-holes!',14,0,100,0,0,0,'Comment'),
(39201,0,2,'So I have this idea for a movie. Three gnomes find a bracelet of power...',14,0,100,0,0,0,'Comment'),
(39201,0,3,'We put a whole town... in a tiny little box!',14,0,100,0,0,0,'Comment'),
(39201,0,4,'How about smiling monkey wallets?',14,0,100,0,0,0,'Comment'),
(39201,0,5,'Explosive fire extinguishers! We\'ll fight fire... WITH fire!',14,0,100,0,0,0,'Comment'),
(39201,0,6,'Spoon sharpeners!',14,0,100,0,0,0,'Comment'),
(39201,0,7,'A truck that delivers ice cream. With a catapult.',14,0,100,0,0,0,'Comment'),
(39201,0,8,'I\'ve got it: Squeezeable rocks!',14,0,100,0,0,0,'Comment'),
(39201,0,9,'Clowns. Instead of making you laugh, they\'re there for beating.',14,0,100,0,0,0,'Comment'),
(39201,0,10,'Thirteen-sided dice!',14,0,100,0,0,0,'Comment'),
(39201,0,11,'Tauren paladins!',14,0,100,0,0,0,'Comment'),
(39201,0,12,'Invisible condiments. For an unobstructed view of your food.',14,0,100,0,0,0,'Comment'),
(39201,0,13,'Feed pigs rubber, \'till they bounce. There\'s got to be an application for that.',14,0,100,0,0,0,'Comment'),
(39201,0,14,'A globe that shows the inside of the planet... on the outside. So you know where to dig!',14,0,100,0,0,0,'Comment'),
(39201,0,15,'Handheld one-way mirrors!',14,0,100,0,0,0,'Comment'),
(39201,0,16,'Nose-stenders. For smelling things in different rooms.',14,0,100,0,0,0,'Comment'),
(39201,0,17,'Attach two vehicles to a bigger vehicle, and then have the passengers jump from one vehicle to the other!',14,0,100,0,0,0,'Comment'),
(39201,0,18,'Electrical wires used to send messages over great distances... no, impractical. Giant rockets, with speakers attached...',14,0,100,0,0,0,'Comment'),
(39201,0,19,'Houses made of dirt! When you clean them... THEY\'RE GONE.',14,0,100,0,0,0,'Comment'),
(39201,0,20,'Stairways... for horizontal surfaces!',14,0,100,0,0,0,'Comment'),
(39201,0,21,'Half man... half sharkalligator!',14,0,100,0,0,0,'Comment'),
(39201,0,22,'Leashes... with pre-attached pets.',14,0,100,0,0,0,'Comment'),
(39201,0,23,'A big convention, see? To show off all of our inventions. We\'ll call it GoblinCon. And we\'ll give away special pets! Except most people will probably sell them for profit on the auction house.',14,0,100,0,0,0,'Comment'),
(39201,0,24,'Distilling the juice out of Kaja\'mite to make a delicious, carbonated beverage that will give people IDEAS! Hey, wait a minute...',14,0,100,0,0,0,'Comment'),
(39201,0,25,'Giant gnomes! No, wait... tiny giants!',14,0,100,0,0,0,'Comment'),
(39201,0,26,'Goblins with gills!',14,0,100,0,0,0,'Comment');

DELETE FROM `spell_script_names` WHERE `spell_id` = '73611';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(73611, 'spell_summon_generic_controller');

DELETE FROM `spell_script_names` WHERE `spell_id` = '73601';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(73601, 'spell_summon_generic_controller');

DELETE FROM `spell_script_names` WHERE `spell_id` = '73609';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(73609, 'spell_summon_generic_controller');

UPDATE `creature_template` SET `VehicleId`=688 WHERE `entry`=39329;

DELETE FROM `spell_target_position` WHERE `id` = '73746';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(73746, 648, 2066.34, 1844.25, 138.60, 0.35);

DELETE FROM `waypoints` WHERE `entry` = '39329';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(39329, 1, 2107.63, 1836.64, 131.32, 'Minecart Kaja WP'),
(39329, 2, 2207.33, 1887.54, 75.49, 'Minecart Kaja WP'),
(39329, 3, 2252.62, 1900.79, 52.57, 'Minecart Kaja WP'),
(39329, 4, 2285.47, 1909.20, 36.28, 'Minecart Kaja WP'),
(39329, 5, 2325.76, 1922.89, 29.25, 'Minecart Kaja WP'),
(39329, 6, 2332.09, 1925.61, 28.22, 'Minecart Kaja WP'),
(39329, 7, 2342.89, 1928.85, 26.44, 'Minecart Kaja WP'),
(39329, 8, 2353.39, 1929.71, 25.20, 'Minecart Kaja WP'),
(39329, 9, 2369.96, 1934.30, 21.59, 'Minecart Kaja WP');

UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry` IN (39329, 38124);

-- Mine Cart
SET @ENTRY := 39341;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,0,0,0,0,85,73746,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Summon Minecart");

UPDATE `creature_template` SET `speed_walk`=1.5, `speed_run`=2.13 WHERE `entry` IN (39341, 39329);

-- Mine Cart
SET @ENTRY := 39329;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,88223,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Visual"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,53,1,39329,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Start WP"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Set Run"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,9,0,0,0,11,73755,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Explode"),
(@ENTRY,@SOURCETYPE,4,0,40,0,100,0,9,0,0,0,28,73747,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Explode - Remove All Auras"),
(@ENTRY,@SOURCETYPE,5,0,40,0,100,0,9,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Explode - Despawn"),
(@ENTRY,@SOURCETYPE,6,0,54,0,100,0,0,0,0,0,11,73767,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Sound Prepare");

UPDATE `creature_template` SET `lootid`=39354 WHERE `entry`=39354;
UPDATE `creature_template` SET `mindmg`=10, `maxdmg`=15, `attackpower`=4 WHERE `entry`=39354;

DELETE FROM `creature_loot_template` WHERE `entry` = '39354';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(39354, 727, 0.7949, 1, 0, 1, 1),
(39354, 767, 0.2162, 1, 0, 1, 1),
(39354, 768, 0.8203, 1, 0, 1, 1),
(39354, 774, 3.5898, 1, 0, 1, 1),
(39354, 805, 0.1781, 1, 0, 1, 1),
(39354, 818, 0.8903, 1, 0, 1, 1),
(39354, 828, 0.2385, 1, 0, 1, 1),
(39354, 1411, 1.1479, 1, 0, 1, 1),
(39354, 1412, 1.0652, 1, 0, 1, 1),
(39354, 1413, 0.903, 1, 0, 1, 1),
(39354, 1414, 1.1542, 1, 0, 1, 1),
(39354, 1415, 1.027, 1, 0, 1, 1),
(39354, 1416, 1.3863, 1, 0, 1, 1),
(39354, 1417, 1.1224, 1, 0, 1, 1),
(39354, 1418, 0.9253, 1, 0, 1, 1),
(39354, 1419, 1.0366, 1, 0, 1, 1),
(39354, 1420, 0.849, 1, 0, 1, 1),
(39354, 1422, 0.7695, 1, 0, 1, 1),
(39354, 1423, 1.1701, 1, 0, 1, 1),
(39354, 1425, 0.8903, 1, 0, 1, 1),
(39354, 1427, 1.027, 1, 0, 1, 1),
(39354, 1429, 0.9157, 1, 0, 1, 1),
(39354, 1430, 1.0079, 1, 0, 1, 1),
(39354, 1431, 0.9475, 1, 0, 1, 1),
(39354, 1433, 1.0048, 1, 0, 1, 1),
(39354, 1697, 0.0095, 1, 0, 1, 1),
(39354, 2070, 0.0032, 1, 0, 1, 1),
(39354, 2075, 0.3211, 1, 0, 1, 1),
(39354, 2138, 1.1606, 1, 0, 1, 1),
(39354, 2140, 0.337, 1, 0, 1, 1),
(39354, 2212, 0.814, 1, 0, 1, 1),
(39354, 2213, 0.725, 1, 0, 1, 1),
(39354, 2406, 0.0184, 1, 0, 1, 1),
(39354, 2407, 0.0191, 1, 0, 1, 1),
(39354, 2408, 0.05, 1, 0, 1, 1),
(39354, 2555, 0.0413, 1, 0, 1, 1),
(39354, 2598, 0.5056, 1, 0, 1, 1),
(39354, 2635, 0.7059, 1, 0, 1, 1),
(39354, 2642, 0.7886, 1, 0, 1, 1),
(39354, 2643, 0.7663, 1, 0, 1, 1),
(39354, 2645, 0.7122, 1, 0, 1, 1),
(39354, 2646, 0.8203, 1, 0, 1, 1),
(39354, 2648, 0.6614, 1, 0, 1, 1),
(39354, 2773, 1.0302, 1, 0, 1, 1),
(39354, 2774, 1.0747, 1, 0, 1, 1),
(39354, 3189, 0.2798, 1, 0, 1, 1),
(39354, 3190, 0.2448, 1, 0, 1, 1),
(39354, 3192, 0.2925, 1, 0, 1, 1),
(39354, 3279, 0.1685, 1, 0, 1, 1),
(39354, 3280, 0.5755, 1, 0, 1, 1),
(39354, 3281, 0.2099, 1, 0, 1, 1),
(39354, 3282, 0.1717, 1, 0, 1, 1),
(39354, 3283, 0.0572, 1, 0, 1, 1),
(39354, 3284, 0.2194, 1, 0, 1, 1),
(39354, 3285, 0.4674, 1, 0, 1, 1),
(39354, 3286, 0.1399, 1, 0, 1, 1),
(39354, 3287, 0.2957, 1, 0, 1, 1),
(39354, 3288, 0.0668, 1, 0, 1, 1),
(39354, 3289, 0.3211, 1, 0, 1, 1),
(39354, 3290, 0.1876, 1, 0, 1, 1),
(39354, 3291, 0.0954, 1, 0, 1, 1),
(39354, 3292, 0.0445, 1, 0, 1, 1),
(39354, 3303, 0.1367, 1, 0, 1, 1),
(39354, 3312, 0.0795, 1, 0, 1, 1),
(39354, 3370, 0.9062, 1, 0, 1, 1),
(39354, 3373, 0.6773, 1, 0, 1, 1),
(39354, 3609, 0.2734, 1, 0, 1, 1),
(39354, 3610, 0.05, 1, 0, 1, 1),
(39354, 3642, 0.9157, 1, 0, 1, 1),
(39354, 3644, 0.1844, 1, 0, 1, 1),
(39354, 3649, 0.2385, 1, 0, 1, 1),
(39354, 3650, 0.2607, 1, 0, 1, 1),
(39354, 3653, 0.0223, 1, 0, 1, 1),
(39354, 3654, 0.0095, 1, 0, 1, 1),
(39354, 4408, 0.05, 1, 0, 1, 1),
(39354, 4496, 0.2003, 1, 0, 1, 1),
(39354, 4561, 0.2671, 1, 0, 1, 1),
(39354, 4562, 0.8108, 1, 0, 1, 1),
(39354, 4563, 0.7663, 1, 0, 1, 1),
(39354, 4564, 0.1165, 1, 0, 1, 1),
(39354, 4566, 0.1, 1, 0, 1, 1),
(39354, 4577, 0.05, 1, 0, 1, 1),
(39354, 4668, 0.7822, 1, 0, 1, 1),
(39354, 4669, 0.3657, 1, 0, 1, 1),
(39354, 4671, 0.8808, 1, 0, 1, 1),
(39354, 4672, 0.6836, 1, 0, 1, 1),
(39354, 4674, 0.7504, 1, 0, 1, 1),
(39354, 4675, 0.5024, 1, 0, 1, 1),
(39354, 4680, 0.0541, 1, 0, 1, 1),
(39354, 4686, 0.1622, 1, 0, 1, 1),
(39354, 4692, 0.1653, 1, 0, 1, 1),
(39354, 5069, 0.2576, 1, 0, 1, 1),
(39354, 5571, 0.1685, 1, 0, 1, 1),
(39354, 5572, 0.283, 1, 0, 1, 1),
(39354, 6271, 0.05, 1, 0, 1, 1),
(39354, 6342, 0.05, 1, 0, 1, 1),
(39354, 6527, 0.0731, 1, 0, 1, 1),
(39354, 7288, 0.05, 1, 0, 1, 1),
(39354, 8178, 0.6868, 1, 0, 1, 1),
(39354, 8180, 0.3975, 1, 0, 1, 1),
(39354, 8181, 0.8744, 1, 0, 1, 1),
(39354, 14086, 0.531, 1, 0, 1, 1),
(39354, 14087, 0.4134, 1, 0, 1, 1),
(39354, 14088, 0.4102, 1, 0, 1, 1),
(39354, 14089, 0.4483, 1, 0, 1, 1),
(39354, 14090, 0.2989, 1, 0, 1, 1),
(39354, 14091, 0.1526, 1, 0, 1, 1),
(39354, 14093, 0.8172, 1, 0, 1, 1),
(39354, 14094, 0.1081, 1, 0, 1, 1),
(39354, 14095, 0.248, 1, 0, 1, 1),
(39354, 14098, 0.4897, 1, 0, 1, 1),
(39354, 14099, 0.2353, 1, 0, 1, 1),
(39354, 14102, 0.0604, 1, 0, 1, 1),
(39354, 14110, 0.0986, 1, 0, 1, 1),
(39354, 15003, 0.3911, 1, 0, 1, 1),
(39354, 15004, 0.7377, 1, 0, 1, 1),
(39354, 15005, 0.814, 1, 0, 1, 1),
(39354, 15006, 0.2544, 1, 0, 1, 1),
(39354, 15007, 0.4102, 1, 0, 1, 1),
(39354, 15008, 0.5024, 1, 0, 1, 1),
(39354, 15009, 0.1717, 1, 0, 1, 1),
(39354, 15010, 0.2671, 1, 0, 1, 1),
(39354, 15015, 0.0827, 1, 0, 1, 1),
(39354, 15297, 0.2607, 1, 0, 1, 1),
(39354, 15298, 0.0477, 1, 0, 1, 1),
(39354, 15299, 0.4229, 1, 0, 1, 1),
(39354, 15301, 0.0668, 1, 0, 1, 1),
(39354, 15302, 0.2353, 1, 0, 1, 1),
(39354, 15472, 0.5851, 1, 0, 1, 1),
(39354, 15473, 0.4483, 1, 0, 1, 1),
(39354, 15474, 0.2957, 1, 0, 1, 1),
(39354, 15475, 0.4038, 1, 0, 1, 1),
(39354, 15476, 0.337, 1, 0, 1, 1),
(39354, 15477, 0.2607, 1, 0, 1, 1),
(39354, 15478, 0.2226, 1, 0, 1, 1),
(39354, 15479, 0.2385, 1, 0, 1, 1),
(39354, 15480, 0.0509, 1, 0, 1, 1),
(39354, 15481, 0.0254, 1, 0, 1, 1),
(39354, 15482, 0.3148, 1, 0, 1, 1),
(39354, 15483, 0.3466, 1, 0, 1, 1),
(39354, 15484, 0.194, 1, 0, 1, 1),
(39354, 15486, 0.318, 1, 0, 1, 1),
(39354, 15944, 0.2289, 1, 0, 1, 1),
(39354, 15969, 0.2385, 1, 0, 1, 1),
(39354, 15970, 0.0223, 1, 0, 1, 1),
(39354, 49424, -0.0064, 1, 0, 1, 1),
(39354, 50381, -0.0095, 1, 0, 1, 1),
(39354, 50437, -0.0191, 1, 0, 1, 1),
(39354, 50438, 0.0382, 1, 0, 1, 1),
(39354, 52035, -0.0064, 1, 0, 1, 1),
(39354, 52347, -0.0032, 1, 0, 1, 1),
(39354, 52530, -42.8871, 1, 0, 1, 1),
(39354, 54619, 0.0032, 1, 0, 1, 1),
(39354, 67252, 0.0032, 1, 0, 1, 1),
(39354, 67256, 0.0064, 1, 0, 1, 1);

-- Steamwheedle Shark
SET @ENTRY := 39354;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,32735,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Saw Blade"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,8000,8000,11,75962,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shred Armor"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,3500,3500,3500,3500,11,75962,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Saw Blade");

DELETE FROM `conditions` WHERE `SourceEntry` = '25203' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 20, 25203, 0, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25203' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 20, 25203, 0, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25202' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 20, 25202, 1, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25202' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 20, 25202, 1, 0);

UPDATE `creature_template` SET `lootid`=39376, `mingold`=19, `maxgold`=25 WHERE `entry`=39376;

DELETE FROM `creature_loot_template` WHERE `entry` = '39376';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(39376, 727, 0.1791, 1, 0, 1, 1),
(39376, 767, 0.8631, 1, 0, 1, 1),
(39376, 768, 0.1665, 1, 0, 1, 1),
(39376, 774, 0.8697, 1, 0, 1, 1),
(39376, 805, 1.1287, 1, 0, 1, 1),
(39376, 828, 0.05, 1, 0, 1, 1),
(39376, 1411, 0.2, 1, 0, 1, 1),
(39376, 1412, 0.3, 1, 0, 1, 1),
(39376, 1413, 0.3, 1, 0, 1, 1),
(39376, 1414, 0.3, 1, 0, 1, 1),
(39376, 1415, 0.2, 1, 0, 1, 1),
(39376, 1416, 0.3, 1, 0, 1, 1),
(39376, 1417, 0.3, 1, 0, 1, 1),
(39376, 1418, 0.2, 1, 0, 1, 1),
(39376, 1419, 0.2722, 1, 0, 1, 1),
(39376, 1420, 0.2, 1, 0, 1, 1),
(39376, 1422, 0.3, 1, 0, 1, 1),
(39376, 1423, 0.3028, 1, 0, 1, 1),
(39376, 1425, 0.2473, 1, 0, 1, 1),
(39376, 1427, 2.5561, 1, 0, 1, 1),
(39376, 1429, 0.2, 1, 0, 1, 1),
(39376, 1430, 0.2, 1, 0, 1, 1),
(39376, 1431, 0.2, 1, 0, 1, 1),
(39376, 1433, 0.3, 1, 0, 1, 1),
(39376, 2075, 0.1, 1, 0, 1, 1),
(39376, 2138, 0.3, 1, 0, 1, 1),
(39376, 2140, 0.05, 1, 0, 1, 1),
(39376, 2212, 0.1, 1, 0, 1, 1),
(39376, 2213, 0.1, 1, 0, 1, 1),
(39376, 2407, 0.05, 1, 0, 1, 1),
(39376, 2555, 0.0232, 1, 0, 1, 1),
(39376, 2598, 0.1, 1, 0, 1, 1),
(39376, 2635, 0.1, 1, 0, 1, 1),
(39376, 2642, 0.2, 1, 0, 1, 1),
(39376, 2643, 0.1, 1, 0, 1, 1),
(39376, 2645, 0.1, 1, 0, 1, 1),
(39376, 2646, 0.1, 1, 0, 1, 1),
(39376, 2648, 0.1925, 1, 0, 1, 1),
(39376, 2773, 0.2, 1, 0, 1, 1),
(39376, 2774, 3.4192, 1, 0, 1, 1),
(39376, 3189, 0.1, 1, 0, 1, 1),
(39376, 3190, 0.05, 1, 0, 1, 1),
(39376, 3192, 0.05, 1, 0, 1, 1),
(39376, 3279, 0.0222, 1, 0, 1, 1),
(39376, 3280, 0.1284, 1, 0, 1, 1),
(39376, 3281, 0.0301, 1, 0, 1, 1),
(39376, 3282, 0.0222, 1, 0, 1, 1),
(39376, 3283, 0.0111, 1, 0, 1, 1),
(39376, 3284, 0.0349, 1, 0, 1, 1),
(39376, 3285, 0.0951, 1, 0, 1, 1),
(39376, 3286, 0.0333, 1, 0, 1, 1),
(39376, 3287, 0.0396, 1, 0, 1, 1),
(39376, 3288, 0.0111, 1, 0, 1, 1),
(39376, 3289, 0.0698, 1, 0, 1, 1),
(39376, 3290, 0.0523, 1, 0, 1, 1),
(39376, 3291, 0.0127, 1, 0, 1, 1),
(39376, 3292, 0.0016, 1, 0, 1, 1),
(39376, 3303, 0.0317, 1, 0, 1, 1),
(39376, 3312, 0.0048, 1, 0, 1, 1),
(39376, 3370, 0.1, 1, 0, 1, 1),
(39376, 3373, 0.2, 1, 0, 1, 1),
(39376, 3609, 0.1015, 1, 0, 1, 1),
(39376, 3610, 0.05, 1, 0, 1, 1),
(39376, 3642, 0.2077, 1, 0, 1, 1),
(39376, 3644, 0.038, 1, 0, 1, 1),
(39376, 3649, 0.065, 1, 0, 1, 1),
(39376, 3650, 0.0618, 1, 0, 1, 1),
(39376, 3653, 0.0033, 1, 0, 1, 1),
(39376, 4496, 0.1, 1, 0, 1, 1),
(39376, 4561, 0.1, 1, 0, 1, 1),
(39376, 4562, 0.1506, 1, 0, 1, 1),
(39376, 4563, 0.195, 1, 0, 1, 1),
(39376, 4564, 0.05, 1, 0, 1, 1),
(39376, 4566, 0.05, 1, 0, 1, 1),
(39376, 4577, 0.05, 1, 0, 1, 1),
(39376, 4668, 0.1348, 1, 0, 1, 1),
(39376, 4669, 0.0967, 1, 0, 1, 1),
(39376, 4671, 0.1855, 1, 0, 1, 1),
(39376, 4672, 0.1459, 1, 0, 1, 1),
(39376, 4674, 0.2695, 1, 0, 1, 1),
(39376, 4675, 0.1031, 1, 0, 1, 1),
(39376, 4680, 0.0095, 1, 0, 1, 1),
(39376, 4686, 0.046, 1, 0, 1, 1),
(39376, 4692, 0.0206, 1, 0, 1, 1),
(39376, 5069, 0.05, 1, 0, 1, 1),
(39376, 5571, 0.1, 1, 0, 1, 1),
(39376, 5572, 0.05, 1, 0, 1, 1),
(39376, 6271, 0.05, 1, 0, 1, 1),
(39376, 6527, 0.0079, 1, 0, 1, 1),
(39376, 8178, 0.149, 1, 0, 1, 1),
(39376, 8180, 0.1, 1, 0, 1, 1),
(39376, 8181, 0.2045, 1, 0, 1, 1),
(39376, 14086, 0.1252, 1, 0, 1, 1),
(39376, 14087, 0.1046, 1, 0, 1, 1),
(39376, 14088, 0.0935, 1, 0, 1, 1),
(39376, 14089, 0.1078, 1, 0, 1, 1),
(39376, 14090, 0.0491, 1, 0, 1, 1),
(39376, 14091, 0.0444, 1, 0, 1, 1),
(39376, 14093, 0.1934, 1, 0, 1, 1),
(39376, 14094, 0.0365, 1, 0, 1, 1),
(39376, 14095, 0.0809, 1, 0, 1, 1),
(39376, 14098, 0.1554, 1, 0, 1, 1),
(39376, 14099, 0.0539, 1, 0, 1, 1),
(39376, 14102, 0.027, 1, 0, 1, 1),
(39376, 14110, 0.0048, 1, 0, 1, 1),
(39376, 15003, 0.1031, 1, 0, 1, 1),
(39376, 15004, 0.1649, 1, 0, 1, 1),
(39376, 15005, 0.1538, 1, 0, 1, 1),
(39376, 15006, 0.092, 1, 0, 1, 1),
(39376, 15007, 0.0634, 1, 0, 1, 1),
(39376, 15008, 0.1141, 1, 0, 1, 1),
(39376, 15009, 0.065, 1, 0, 1, 1),
(39376, 15010, 0.0745, 1, 0, 1, 1),
(39376, 15015, 0.0127, 1, 0, 1, 1),
(39376, 15297, 0.0523, 1, 0, 1, 1),
(39376, 15298, 0.0095, 1, 0, 1, 1),
(39376, 15299, 0.1379, 1, 0, 1, 1),
(39376, 15301, 0.0238, 1, 0, 1, 1),
(39376, 15302, 0.0523, 1, 0, 1, 1),
(39376, 15472, 0.1395, 1, 0, 1, 1),
(39376, 15473, 0.092, 1, 0, 1, 1),
(39376, 15474, 0.0951, 1, 0, 1, 1),
(39376, 15475, 0.0539, 1, 0, 1, 1),
(39376, 15476, 0.1459, 1, 0, 1, 1),
(39376, 15477, 0.0444, 1, 0, 1, 1),
(39376, 15478, 0.0777, 1, 0, 1, 1),
(39376, 15479, 0.0365, 1, 0, 1, 1),
(39376, 15480, 0.0143, 1, 0, 1, 1),
(39376, 15481, 0.0032, 1, 0, 1, 1),
(39376, 15482, 0.0396, 1, 0, 1, 1),
(39376, 15483, 0.0904, 1, 0, 1, 1),
(39376, 15484, 0.0254, 1, 0, 1, 1),
(39376, 15486, 0.0602, 1, 0, 1, 1),
(39376, 15944, 0.0412, 1, 0, 1, 1),
(39376, 15969, 0.0476, 1, 0, 1, 1),
(39376, 15970, 0.0063, 1, 0, 1, 1),
(39376, 49424, -0.0032, 1, 0, 1, 1),
(39376, 50437, -0.0016, 1, 0, 1, 1),
(39376, 50438, 0.0048, 1, 0, 1, 1),
(39376, 54623, 18.8487, 1, 0, 1, 1),
(39376, 54624, 81.0863, 1, 0, 1, 1);

UPDATE `creature` SET `phaseMask`=32768 WHERE `guid`=833540;
UPDATE `creature_template` SET `mindmg`=10, `maxdmg`=14, `attackpower`=4, `dmg_multiplier`=1.2, `lootid`=39363 WHERE `entry`=39363;

DELETE FROM `creature_loot_template` WHERE `entry` = '39363';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(39363, 414, 21.5686, 1, 0, 1, 1),
(39363, 727, 0.1, 1, 0, 1, 1),
(39363, 818, 0.5697, 1, 0, 1, 1),
(39363, 858, 21.5686, 1, 0, 1, 1),
(39363, 1179, 2.8, 1, 0, 1, 1),
(39363, 1495, 0.2645, 1, 0, 1, 1),
(39363, 1497, 0.2, 1, 0, 1, 1),
(39363, 1498, 0.4, 1, 0, 1, 1),
(39363, 1499, 0.2747, 1, 0, 1, 1),
(39363, 1501, 0.2, 1, 0, 1, 1),
(39363, 1502, 0.1, 1, 0, 1, 1),
(39363, 1503, 0.2, 1, 0, 1, 1),
(39363, 1504, 0.2, 1, 0, 1, 1),
(39363, 1506, 0.3459, 1, 0, 1, 1),
(39363, 1507, 0.3256, 1, 0, 1, 1),
(39363, 1509, 0.2543, 1, 0, 1, 1),
(39363, 1510, 0.4, 1, 0, 1, 1),
(39363, 1511, 0.3561, 1, 0, 1, 1),
(39363, 1512, 0.1, 1, 0, 1, 1),
(39363, 1513, 0.3256, 1, 0, 1, 1),
(39363, 1514, 0.4578, 1, 0, 1, 1),
(39363, 1515, 0.3866, 1, 0, 1, 1),
(39363, 1516, 0.6308, 1, 0, 1, 1),
(39363, 1730, 0.2543, 1, 0, 1, 1),
(39363, 1731, 0.2035, 1, 0, 1, 1),
(39363, 1732, 0.1, 1, 0, 1, 1),
(39363, 1734, 0.3968, 1, 0, 1, 1),
(39363, 1735, 0.2, 1, 0, 1, 1),
(39363, 1737, 0.234, 1, 0, 1, 1),
(39363, 2075, 0.2238, 1, 0, 1, 1),
(39363, 2140, 0.6206, 1, 0, 1, 1),
(39363, 2214, 0.2, 1, 0, 1, 1),
(39363, 2215, 0.1, 1, 0, 1, 1),
(39363, 2287, 7.7017, 1, 0, 1, 1),
(39363, 2407, 0.0203, 1, 0, 1, 1),
(39363, 2409, 1.9608, 1, 0, 1, 1),
(39363, 2455, 0.9, 1, 0, 1, 1),
(39363, 2589, 53.7, 1, 0, 1, 3),
(39363, 2632, 0.7997, 1, 0, 1, 1),
(39363, 2763, 0.3663, 1, 0, 1, 1),
(39363, 2777, 0.3663, 1, 0, 1, 1),
(39363, 2778, 0.2999, 1, 0, 1, 1),
(39363, 3192, 0.1119, 1, 0, 1, 1),
(39363, 3279, 0.061, 1, 0, 1, 1),
(39363, 3281, 0.0814, 1, 0, 1, 1),
(39363, 3282, 0.0203, 1, 0, 1, 1),
(39363, 3283, 0.0509, 1, 0, 1, 1),
(39363, 3284, 0.0102, 1, 0, 1, 1),
(39363, 3285, 0.1526, 1, 0, 1, 1),
(39363, 3286, 0.0407, 1, 0, 1, 1),
(39363, 3287, 0.0407, 1, 0, 1, 1),
(39363, 3288, 0.1017, 1, 0, 1, 1),
(39363, 3289, 0.1526, 1, 0, 1, 1),
(39363, 3290, 0.1017, 1, 0, 1, 1),
(39363, 3291, 0.1017, 1, 0, 1, 1),
(39363, 3292, 0.0305, 1, 0, 1, 1),
(39363, 3303, 0.1119, 1, 0, 1, 1),
(39363, 3304, 0.0102, 1, 0, 1, 1),
(39363, 3312, 0.0814, 1, 0, 1, 1),
(39363, 3374, 0.2849, 1, 0, 1, 1),
(39363, 3375, 0.234, 1, 0, 1, 1),
(39363, 3610, 0.0203, 1, 0, 1, 1),
(39363, 3644, 0.1526, 1, 0, 1, 1),
(39363, 3649, 0.0305, 1, 0, 1, 1),
(39363, 3654, 0.0102, 1, 0, 1, 1),
(39363, 4292, 0.0203, 1, 0, 1, 1),
(39363, 4345, 0.02, 1, 0, 1, 1),
(39363, 4346, 0.1999, 1, 0, 1, 1),
(39363, 4408, 0.1999, 1, 0, 1, 1),
(39363, 4537, 13.7255, 1, 0, 1, 1),
(39363, 4541, 9.8039, 1, 0, 1, 1),
(39363, 4561, 0.2849, 1, 0, 1, 1),
(39363, 4564, 0.05, 1, 0, 1, 1),
(39363, 4566, 0.1, 1, 0, 1, 1),
(39363, 4569, 0.05, 1, 0, 1, 1),
(39363, 4669, 0.0712, 1, 0, 1, 1),
(39363, 4672, 0.1323, 1, 0, 1, 1),
(39363, 4675, 0.0509, 1, 0, 1, 1),
(39363, 4680, 0.0712, 1, 0, 1, 1),
(39363, 4681, 0.0305, 1, 0, 1, 1),
(39363, 4686, 0.0203, 1, 0, 1, 1),
(39363, 4687, 0.0203, 1, 0, 1, 1),
(39363, 4692, 0.061, 1, 0, 1, 1),
(39363, 4693, 0.0102, 1, 0, 1, 1),
(39363, 5071, 0.1, 1, 0, 1, 1),
(39363, 5368, 43.1373, 1, 0, 1, 1),
(39363, 5573, 0.05, 1, 0, 1, 1),
(39363, 6342, 0.0203, 1, 0, 1, 1),
(39363, 6527, 0.1017, 1, 0, 1, 1),
(39363, 7288, 0.0407, 1, 0, 1, 1),
(39363, 8178, 0.1, 1, 0, 1, 1),
(39363, 8180, 0.2238, 1, 0, 1, 1),
(39363, 14086, 0.5799, 1, 0, 1, 1),
(39363, 14089, 0.0203, 1, 0, 1, 1),
(39363, 14090, 0.234, 1, 0, 1, 1),
(39363, 14091, 0.0916, 1, 0, 1, 1),
(39363, 14094, 0.0814, 1, 0, 1, 1),
(39363, 14095, 0.2543, 1, 0, 1, 1),
(39363, 14097, 0.0407, 1, 0, 1, 1),
(39363, 14098, 0.1323, 1, 0, 1, 1),
(39363, 14099, 0.0407, 1, 0, 1, 1),
(39363, 14102, 0.2137, 1, 0, 1, 1),
(39363, 14110, 0.0203, 1, 0, 1, 1),
(39363, 14115, 0.0509, 1, 0, 1, 1),
(39363, 14116, 0.0102, 1, 0, 1, 1),
(39363, 15008, 0.0814, 1, 0, 1, 1),
(39363, 15009, 0.1119, 1, 0, 1, 1),
(39363, 15010, 0.1017, 1, 0, 1, 1),
(39363, 15013, 0.0305, 1, 0, 1, 1),
(39363, 15015, 0.061, 1, 0, 1, 1),
(39363, 15297, 0.1424, 1, 0, 1, 1),
(39363, 15298, 0.0102, 1, 0, 1, 1),
(39363, 15299, 0.0509, 1, 0, 1, 1),
(39363, 15300, 0.0305, 1, 0, 1, 1),
(39363, 15301, 0.234, 1, 0, 1, 1),
(39363, 15302, 0.1933, 1, 0, 1, 1),
(39363, 15303, 0.0509, 1, 0, 1, 1),
(39363, 15473, 0.0814, 1, 0, 1, 1),
(39363, 15476, 0.0305, 1, 0, 1, 1),
(39363, 15477, 0.1526, 1, 0, 1, 1),
(39363, 15479, 0.0916, 1, 0, 1, 1),
(39363, 15480, 0.0305, 1, 0, 1, 1),
(39363, 15481, 0.061, 1, 0, 1, 1),
(39363, 15482, 0.0814, 1, 0, 1, 1),
(39363, 15483, 0.0712, 1, 0, 1, 1),
(39363, 15484, 0.0814, 1, 0, 1, 1),
(39363, 15485, 0.0102, 1, 0, 1, 1),
(39363, 15486, 0.0916, 1, 0, 1, 1),
(39363, 15490, 0.0203, 1, 0, 1, 1),
(39363, 15944, 0.061, 1, 0, 1, 1),
(39363, 15969, 0.0509, 1, 0, 1, 1),
(39363, 15970, 0.0203, 1, 0, 1, 1),
(39363, 52531, -100, 1, 0, 1, 1);

-- Chip Endale
SET @ENTRY := 39363;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,75964,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Beatdown"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,4500,4500,4500,4500,11,75964,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Beatdown"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,1000,1000,5500,5500,11,75968,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Full Monte");

-- Valve #4
SET @ENTRY := 202612;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,19,33765,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Dummy");

-- Valve #3
SET @ENTRY := 202611;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,19,33765,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Dummy");

-- Valve #2
SET @ENTRY := 202610;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,19,33765,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Dummy");

-- Valve #1
SET @ENTRY := 202609;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,19,33765,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Dummy");

-- ELM General Purpose Bunny (scale x2)
SET @ENTRY := 33765;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,11,73839,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Cast Dummy Effect");

-- ELM General Purpose Bunny Gigantic (scale x2)
SET @ENTRY := 39375;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,2000,4500,2000,3500,11,73891,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Cast Explosion"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,2000,4500,2000,3500,11,73891,0,0,0,0,0,18,30,0,0,0.0,0.0,0.0,0.0,"OOC - Camera Shake");

UPDATE `creature` SET `phaseMask`=16384 WHERE `id`=39375;
UPDATE `gameobject_template` SET `data0`=73900 WHERE `entry`=205061;
UPDATE `quest_template` SET `SpecialFlags`=0 WHERE `Id` IN (25202, 25203);
UPDATE `quest_template` SET `SourceSpellId`=89164 WHERE `Id`=25213;
UPDATE `creature_template` SET `VehicleId`=1293 WHERE `entry`=47956;

DELETE FROM `waypoints` WHERE `entry` = '47956';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(47956, 1, 2364.41, 1938.40, 21.53, 'The Slave Pits WP'),
(47956, 2, 2346.97, 1939.84, 23.66, 'The Slave Pits WP'),
(47956, 3, 2290.96, 1971.64, 24.68, 'The Slave Pits WP'),
(47956, 4, 2238.84, 2051.65, 29.28, 'The Slave Pits WP'),
(47956, 5, 2185.09, 2047.17, 40.56, 'The Slave Pits WP'),
(47956, 6, 2157.99, 2059.93, 44.64, 'The Slave Pits WP'),
(47956, 7, 2138.83, 2112.86, 56.24, 'The Slave Pits WP'),
(47956, 8, 2126.09, 2120.05, 60.35, 'The Slave Pits WP'),
(47956, 9, 2120.65, 2137.85, 62.89, 'The Slave Pits WP'),
(47956, 10, 2117.31, 2159.36, 63.10, 'The Slave Pits WP'),
(47956, 11, 2141.70, 2229.25, 59.79, 'The Slave Pits WP'),
(47956, 12, 2139.19, 2243.77, 59.23, 'The Slave Pits WP'),
(47956, 13, 2120.18, 2271.01, 58.08, 'The Slave Pits WP'),
(47956, 14, 2108.80, 2313.83, 56.89, 'The Slave Pits WP'),
(47956, 15, 2092.53, 2334.78, 58.18, 'The Slave Pits WP'),
(47956, 16, 2122.81, 2368.18, 47.95, 'The Slave Pits WP'),
(47956, 17, 2117.82, 2393.70, 46.27, 'The Slave Pits WP');

UPDATE `creature_template` SET `unit_flags`=768, `speed_run`=2.14286 WHERE `entry`=47956;

-- Footbomb Uniform
SET @ENTRY := 47956;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,53,1,47956,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,40,0,100,0,17,0,0,0,28,89174,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Dismiss");

DELETE FROM `conditions` WHERE `SourceEntry` = '25243' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 20, 25243, 0, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25243' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 20, 25243, 0, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25244' AND `SourceTypeOrReferenceId` = '20';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 20, 25244, 1, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '25244' AND `SourceTypeOrReferenceId` = '19';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 20, 25244, 1, 0);

UPDATE `creature_template` SET `unit_flags`=0, `unit_flags2`=2048, `dynamicflags`=0 WHERE `entry`=39449;

DELETE FROM `creature_addon` WHERE `guid` IN
(833672,833674,833677,833679,833681,833686,833687,833709,
833711,833721,833753,833766,833767,833768,833778,833793,
833796,833803,833807,833845,833880);

INSERT INTO `creature_addon` (`guid`, `bytes2`, `auras`) VALUES
(833672, 1, '58951'),(833674, 1, '58951'),(833677, 1, '58951'),
(833679, 1, '58951'),(833681, 1, '58951'),(833686, 1, '58951'),
(833687, 1, '58951'),(833709, 1, '58951'),(833711, 1, '58951'),
(833721, 1, '58951'),(833753, 1, '58951'),(833766, 1, '58951'),
(833767, 1, '58951'),(833768, 1, '58951'),(833778, 1, '58951'),
(833793, 1, '58951'),(833796, 1, '58951'),(833803, 1, '58951'),
(833807, 1, '58951'),(833845, 1, '58951'),(833880, 1, '58951');

UPDATE `creature` SET `unit_flags`=768 WHERE `guid` IN
(833672,833674,833677,833679,833681,833686,833687,833709,
833711,833721,833753,833766,833767,833768,833778,833793,
833796,833803,833807,833845,833880);

UPDATE `creature` SET `position_x`=2131.40, `position_y`=2624.94, `position_z`=7.37, `orientation`=4.29 WHERE `guid`=833879;
UPDATE `creature_template` SET `lootid`=39449, `pickpocketloot`=39449 WHERE `entry`=39449;
UPDATE `creature_template` SET `mindmg`=10, `maxdmg`=15, `attackpower`=4 WHERE `entry`=39449;

DELETE FROM `creature_loot_template` WHERE `entry` = '39449';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(39449, 117, 4.0262, 1, 0, 1, 1),
(39449, 118, 1.0366, 1, 0, 1, 1),
(39449, 159, 1.6, 1, 0, 1, 1),
(39449, 727, 0.2466, 1, 0, 1, 1),
(39449, 767, 0.1233, 1, 0, 1, 1),
(39449, 768, 0.3617, 1, 0, 1, 1),
(39449, 774, 1.1972, 1, 0, 1, 1),
(39449, 805, 0.05, 1, 0, 1, 1),
(39449, 818, 12.8571, 1, 0, 1, 1),
(39449, 828, 0.05, 1, 0, 1, 1),
(39449, 858, 22.8571, 1, 0, 1, 1),
(39449, 1210, 2.8571, 1, 0, 1, 1),
(39449, 1411, 0.3585, 1, 0, 1, 1),
(39449, 1412, 0.4153, 1, 0, 1, 1),
(39449, 1413, 0.3958, 1, 0, 1, 1),
(39449, 1414, 0.4623, 1, 0, 1, 1),
(39449, 1415, 0.2, 1, 0, 1, 1),
(39449, 1416, 0.5434, 1, 0, 1, 1),
(39449, 1417, 0.3877, 1, 0, 1, 1),
(39449, 1418, 0.3715, 1, 0, 1, 1),
(39449, 1419, 0.3244, 1, 0, 1, 1),
(39449, 1420, 0.2855, 1, 0, 1, 1),
(39449, 1422, 0.3017, 1, 0, 1, 1),
(39449, 1423, 0.2936, 1, 0, 1, 1),
(39449, 1425, 0.2839, 1, 0, 1, 1),
(39449, 1427, 0.2952, 1, 0, 1, 1),
(39449, 1429, 0.412, 1, 0, 1, 1),
(39449, 1430, 0.3634, 1, 0, 1, 1),
(39449, 1431, 0.3471, 1, 0, 1, 1),
(39449, 1433, 0.3974, 1, 0, 1, 1),
(39449, 1697, 0.0032, 1, 0, 1, 1),
(39449, 2075, 0.1, 1, 0, 1, 1),
(39449, 2138, 0.5191, 1, 0, 1, 1),
(39449, 2140, 0.1314, 1, 0, 1, 1),
(39449, 2212, 0.3261, 1, 0, 1, 1),
(39449, 2213, 0.2758, 1, 0, 1, 1),
(39449, 2287, 31.4286, 1, 0, 1, 1),
(39449, 2406, 0.05, 1, 0, 1, 1),
(39449, 2407, 0.05, 1, 0, 1, 1),
(39449, 2553, 0.05, 1, 0, 1, 1),
(39449, 2555, 0.05, 1, 0, 1, 1),
(39449, 2589, 47.2, 1, 0, 1, 2),
(39449, 2598, 0.1265, 1, 0, 1, 1),
(39449, 2635, 0.2287, 1, 0, 1, 1),
(39449, 2642, 0.2044, 1, 0, 1, 1),
(39449, 2643, 0.3017, 1, 0, 1, 1),
(39449, 2645, 0.2255, 1, 0, 1, 1),
(39449, 2646, 0.2563, 1, 0, 1, 1),
(39449, 2648, 0.279, 1, 0, 1, 1),
(39449, 2773, 0.3666, 1, 0, 1, 1),
(39449, 2774, 0.3909, 1, 0, 1, 1),
(39449, 3189, 0.1054, 1, 0, 1, 1),
(39449, 3190, 0.1136, 1, 0, 1, 1),
(39449, 3192, 0.1106, 1, 0, 1, 1),
(39449, 3279, 0.0357, 1, 0, 1, 1),
(39449, 3280, 0.2287, 1, 0, 1, 1),
(39449, 3281, 0.086, 1, 0, 1, 1),
(39449, 3282, 0.0454, 1, 0, 1, 1),
(39449, 3283, 0.013, 1, 0, 1, 1),
(39449, 3284, 0.0633, 1, 0, 1, 1),
(39449, 3285, 0.1865, 1, 0, 1, 1),
(39449, 3286, 0.047, 1, 0, 1, 1),
(39449, 3287, 0.1168, 1, 0, 1, 1),
(39449, 3288, 0.0341, 1, 0, 1, 1),
(39449, 3289, 0.1006, 1, 0, 1, 1),
(39449, 3290, 0.0698, 1, 0, 1, 1),
(39449, 3291, 0.0389, 1, 0, 1, 1),
(39449, 3292, 0.0081, 1, 0, 1, 1),
(39449, 3303, 0.0584, 1, 0, 1, 1),
(39449, 3312, 0.0292, 1, 0, 1, 1),
(39449, 3370, 0.2693, 1, 0, 1, 1),
(39449, 3373, 0.3131, 1, 0, 1, 1),
(39449, 3609, 0.1, 1, 0, 1, 1),
(39449, 3610, 0.05, 1, 0, 1, 1),
(39449, 3642, 0.292, 1, 0, 1, 1),
(39449, 3644, 0.1395, 1, 0, 1, 1),
(39449, 3649, 0.0876, 1, 0, 1, 1),
(39449, 3650, 0.0941, 1, 0, 1, 1),
(39449, 3653, 0.0065, 1, 0, 1, 1),
(39449, 3654, 0.0065, 1, 0, 1, 1),
(39449, 4496, 0.05, 1, 0, 1, 1),
(39449, 4541, 35.7143, 1, 0, 1, 1),
(39449, 4561, 0.1, 1, 0, 1, 1),
(39449, 4562, 0.378, 1, 0, 1, 1),
(39449, 4563, 0.2547, 1, 0, 1, 1),
(39449, 4564, 0.05, 1, 0, 1, 1),
(39449, 4566, 0.05, 1, 0, 1, 1),
(39449, 4577, 0.05, 1, 0, 1, 1),
(39449, 4668, 0.2206, 1, 0, 1, 1),
(39449, 4669, 0.146, 1, 0, 1, 1),
(39449, 4671, 0.2758, 1, 0, 1, 1),
(39449, 4672, 0.1801, 1, 0, 1, 1),
(39449, 4674, 0.2774, 1, 0, 1, 1),
(39449, 4675, 0.2206, 1, 0, 1, 1),
(39449, 4680, 0.013, 1, 0, 1, 1),
(39449, 4686, 0.0844, 1, 0, 1, 1),
(39449, 4692, 0.0844, 1, 0, 1, 1),
(39449, 5069, 0.1087, 1, 0, 1, 1),
(39449, 5571, 0.1, 1, 0, 1, 1),
(39449, 5572, 0.1, 1, 0, 1, 1),
(39449, 6271, 0.05, 1, 0, 1, 1),
(39449, 6342, 0.05, 1, 0, 1, 1),
(39449, 6527, 0.0081, 1, 0, 1, 1),
(39449, 7288, 0.05, 1, 0, 1, 1),
(39449, 8178, 0.2563, 1, 0, 1, 1),
(39449, 8180, 0.1054, 1, 0, 1, 1),
(39449, 8181, 0.2741, 1, 0, 1, 1),
(39449, 9260, 2.6798, 1, 0, 1, 1),
(39449, 14086, 0.219, 1, 0, 1, 1),
(39449, 14087, 0.1492, 1, 0, 1, 1),
(39449, 14088, 0.1492, 1, 0, 1, 1),
(39449, 14089, 0.2222, 1, 0, 1, 1),
(39449, 14090, 0.1395, 1, 0, 1, 1),
(39449, 14091, 0.0487, 1, 0, 1, 1),
(39449, 14093, 0.3098, 1, 0, 1, 1),
(39449, 14094, 0.0406, 1, 0, 1, 1),
(39449, 14095, 0.1087, 1, 0, 1, 1),
(39449, 14098, 0.2093, 1, 0, 1, 1),
(39449, 14099, 0.0876, 1, 0, 1, 1),
(39449, 14102, 0.0276, 1, 0, 1, 1),
(39449, 14110, 0.047, 1, 0, 1, 1),
(39449, 15003, 0.1557, 1, 0, 1, 1),
(39449, 15004, 0.2823, 1, 0, 1, 1),
(39449, 15005, 0.2823, 1, 0, 1, 1),
(39449, 15006, 0.0779, 1, 0, 1, 1),
(39449, 15007, 0.1541, 1, 0, 1, 1),
(39449, 15008, 0.1979, 1, 0, 1, 1),
(39449, 15009, 0.0957, 1, 0, 1, 1),
(39449, 15010, 0.1136, 1, 0, 1, 1),
(39449, 15015, 0.0211, 1, 0, 1, 1),
(39449, 15297, 0.0973, 1, 0, 1, 1),
(39449, 15298, 0.0065, 1, 0, 1, 1),
(39449, 15299, 0.1606, 1, 0, 1, 1),
(39449, 15301, 0.0227, 1, 0, 1, 1),
(39449, 15302, 0.0925, 1, 0, 1, 1),
(39449, 15472, 0.2093, 1, 0, 1, 1),
(39449, 15473, 0.1574, 1, 0, 1, 1),
(39449, 15474, 0.1379, 1, 0, 1, 1),
(39449, 15475, 0.1444, 1, 0, 1, 1),
(39449, 15476, 0.1963, 1, 0, 1, 1),
(39449, 15477, 0.0714, 1, 0, 1, 1),
(39449, 15478, 0.0957, 1, 0, 1, 1),
(39449, 15479, 0.0535, 1, 0, 1, 1),
(39449, 15480, 0.0114, 1, 0, 1, 1),
(39449, 15481, 0.0195, 1, 0, 1, 1),
(39449, 15482, 0.0762, 1, 0, 1, 1),
(39449, 15483, 0.1428, 1, 0, 1, 1),
(39449, 15484, 0.047, 1, 0, 1, 1),
(39449, 15486, 0.146, 1, 0, 1, 1),
(39449, 15944, 0.0844, 1, 0, 1, 1),
(39449, 15969, 0.1038, 1, 0, 1, 1),
(39449, 15970, 0.0081, 1, 0, 1, 1),
(39449, 50381, -0.0032, 1, 0, 1, 1),
(39449, 50437, -0.0032, 1, 0, 1, 1),
(39449, 50438, 0.0032, 1, 0, 1, 1),
(39449, 52347, -0.0016, 1, 0, 1, 1),
(39449, 52575, 54.1479, 1, 0, 1, 1);

DELETE FROM `pickpocketing_loot_template` WHERE `entry` = '39449';
INSERT INTO `pickpocketing_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(39449, 818, 10.2804, 1, 0, 1, 1),
(39449, 858, 15.4206, 1, 0, 1, 1),
(39449, 1210, 2.3364, 1, 0, 1, 1),
(39449, 2287, 39.7196, 1, 0, 1, 1),
(39449, 2408, 0.9346, 1, 0, 1, 1),
(39449, 4541, 35.9813, 1, 0, 1, 1),
(39449, 7288, 0.4673, 1, 0, 1, 1);

-- Southsea Mercenary
SET @ENTRY := 39449;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,3000,3000,3000,11,75361,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Swashbuckling Slice");

UPDATE `creature_template` SET `mindmg`=10, `maxdmg`=14, `attackpower`=4, `dmg_multiplier`=1.2, `mingold`=25, `maxgold`=25 WHERE `entry`=39426;
UPDATE `creature_template` SET `lootid`=39426, `pickpocketloot`=39426 WHERE `entry`=39426;

-- Candy Cane
SET @ENTRY := 39426;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,75924,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Heartbreaker"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,14000,14000,14000,14000,11,75924,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Heartbreaker");

DELETE FROM `creature_loot_template` WHERE `entry` = '39426';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(39426, 414, 6.6667, 1, 0, 1, 1),
(39426, 727, 0.2, 1, 0, 1, 1),
(39426, 818, 2.2222, 1, 0, 1, 1),
(39426, 858, 11.1111, 1, 0, 1, 1),
(39426, 1179, 2.2, 1, 0, 1, 1),
(39426, 1495, 0.2, 1, 0, 1, 1),
(39426, 1497, 0.2764, 1, 0, 1, 1),
(39426, 1498, 0.1, 1, 0, 1, 1),
(39426, 1499, 0.8386, 1, 0, 1, 1),
(39426, 1501, 0.2495, 1, 0, 1, 1),
(39426, 1502, 0.2304, 1, 0, 1, 1),
(39426, 1503, 0.2673, 1, 0, 1, 1),
(39426, 1504, 0.2949, 1, 0, 1, 1),
(39426, 1506, 0.3133, 1, 0, 1, 1),
(39426, 1507, 0.3, 1, 0, 1, 1),
(39426, 1509, 0.05, 1, 0, 1, 1),
(39426, 1510, 0.3502, 1, 0, 1, 1),
(39426, 1511, 0.3502, 1, 0, 1, 1),
(39426, 1512, 0.3, 1, 0, 1, 1),
(39426, 1513, 0.3778, 1, 0, 1, 1),
(39426, 1514, 0.3778, 1, 0, 1, 1),
(39426, 1515, 0.4, 1, 0, 1, 1),
(39426, 1516, 0.4239, 1, 0, 1, 1),
(39426, 1730, 0.2764, 1, 0, 1, 1),
(39426, 1731, 0.1, 1, 0, 1, 1),
(39426, 1732, 0.2673, 1, 0, 1, 1),
(39426, 1734, 0.1, 1, 0, 1, 1),
(39426, 1735, 0.2212, 1, 0, 1, 1),
(39426, 1737, 0.2, 1, 0, 1, 1),
(39426, 2075, 0.2212, 1, 0, 1, 1),
(39426, 2140, 0.2212, 1, 0, 1, 1),
(39426, 2214, 0.2, 1, 0, 1, 1),
(39426, 2215, 0.05, 1, 0, 1, 1),
(39426, 2287, 6.1555, 1, 0, 1, 1),
(39426, 2406, 0.0276, 1, 0, 1, 1),
(39426, 2407, 0.0276, 1, 0, 1, 1),
(39426, 2408, 0.0178, 1, 0, 1, 1),
(39426, 2409, 0.0276, 1, 0, 1, 1),
(39426, 2455, 1.1, 1, 0, 1, 1),
(39426, 2555, 0.0553, 1, 0, 1, 1),
(39426, 2589, 44.6, 1, 0, 1, 3),
(39426, 2598, 0.1, 1, 0, 1, 1),
(39426, 2632, 0.0921, 1, 0, 1, 1),
(39426, 2763, 0.4147, 1, 0, 1, 1),
(39426, 2777, 0.2, 1, 0, 1, 1),
(39426, 2778, 0.2, 1, 0, 1, 1),
(39426, 3192, 0.05, 1, 0, 1, 1),
(39426, 3279, 0.0369, 1, 0, 1, 1),
(39426, 3281, 0.0553, 1, 0, 1, 1),
(39426, 3282, 0.0092, 1, 0, 1, 1),
(39426, 3283, 0.0645, 1, 0, 1, 1),
(39426, 3284, 0.0276, 1, 0, 1, 1),
(39426, 3285, 0.0921, 1, 0, 1, 1),
(39426, 3286, 0.0553, 1, 0, 1, 1),
(39426, 3287, 0.1567, 1, 0, 1, 1),
(39426, 3288, 0.0645, 1, 0, 1, 1),
(39426, 3289, 0.1382, 1, 0, 1, 1),
(39426, 3290, 0.0369, 1, 0, 1, 1),
(39426, 3291, 0.0737, 1, 0, 1, 1),
(39426, 3292, 0.0092, 1, 0, 1, 1),
(39426, 3303, 0.0276, 1, 0, 1, 1),
(39426, 3304, 0.0276, 1, 0, 1, 1),
(39426, 3312, 0.0184, 1, 0, 1, 1),
(39426, 3374, 0.2495, 1, 0, 1, 1),
(39426, 3375, 0.2396, 1, 0, 1, 1),
(39426, 3644, 0.0461, 1, 0, 1, 1),
(39426, 3649, 0.0276, 1, 0, 1, 1),
(39426, 3653, 0.0553, 1, 0, 1, 1),
(39426, 3654, 0.0369, 1, 0, 1, 1),
(39426, 4293, 0.0276, 1, 0, 1, 1),
(39426, 4408, 0.1782, 1, 0, 1, 1),
(39426, 4537, 6.6667, 1, 0, 1, 1),
(39426, 4541, 15.5556, 1, 0, 1, 1),
(39426, 4561, 0.1843, 1, 0, 1, 1),
(39426, 4562, 0.1, 1, 0, 1, 1),
(39426, 4564, 0.1, 1, 0, 1, 1),
(39426, 4566, 0.1106, 1, 0, 1, 1),
(39426, 4569, 0.05, 1, 0, 1, 1),
(39426, 4577, 0.1, 1, 0, 1, 1),
(39426, 4669, 0.0276, 1, 0, 1, 1),
(39426, 4672, 0.1382, 1, 0, 1, 1),
(39426, 4675, 0.0921, 1, 0, 1, 1),
(39426, 4681, 0.0553, 1, 0, 1, 1),
(39426, 4686, 0.1567, 1, 0, 1, 1),
(39426, 4687, 0.0461, 1, 0, 1, 1),
(39426, 4693, 0.0276, 1, 0, 1, 1),
(39426, 5069, 0.1, 1, 0, 1, 1),
(39426, 5368, 62.2222, 1, 0, 1, 1),
(39426, 6527, 0.0184, 1, 0, 1, 1),
(39426, 8178, 0.1843, 1, 0, 1, 1),
(39426, 8180, 0.2304, 1, 0, 1, 1),
(39426, 14086, 0.0829, 1, 0, 1, 1),
(39426, 14089, 0.0184, 1, 0, 1, 1),
(39426, 14090, 0.1198, 1, 0, 1, 1),
(39426, 14091, 0.0369, 1, 0, 1, 1),
(39426, 14094, 0.1198, 1, 0, 1, 1),
(39426, 14095, 0.0921, 1, 0, 1, 1),
(39426, 14098, 0.1567, 1, 0, 1, 1),
(39426, 14099, 0.0737, 1, 0, 1, 1),
(39426, 14102, 0.0461, 1, 0, 1, 1),
(39426, 14110, 0.0276, 1, 0, 1, 1),
(39426, 14115, 0.0276, 1, 0, 1, 1),
(39426, 14116, 0.0645, 1, 0, 1, 1),
(39426, 15008, 0.0461, 1, 0, 1, 1),
(39426, 15009, 0.258, 1, 0, 1, 1),
(39426, 15010, 0.1751, 1, 0, 1, 1),
(39426, 15013, 0.0184, 1, 0, 1, 1),
(39426, 15015, 0.0184, 1, 0, 1, 1),
(39426, 15297, 0.1659, 1, 0, 1, 1),
(39426, 15298, 0.0184, 1, 0, 1, 1),
(39426, 15299, 0.1014, 1, 0, 1, 1),
(39426, 15300, 0.0092, 1, 0, 1, 1),
(39426, 15301, 0.0553, 1, 0, 1, 1),
(39426, 15302, 0.1751, 1, 0, 1, 1),
(39426, 15303, 0.0369, 1, 0, 1, 1),
(39426, 15473, 0.4515, 1, 0, 1, 1),
(39426, 15476, 0.0553, 1, 0, 1, 1),
(39426, 15477, 0.0461, 1, 0, 1, 1),
(39426, 15479, 0.1014, 1, 0, 1, 1),
(39426, 15480, 0.0276, 1, 0, 1, 1),
(39426, 15481, 0.0184, 1, 0, 1, 1),
(39426, 15482, 0.1198, 1, 0, 1, 1),
(39426, 15483, 0.0184, 1, 0, 1, 1),
(39426, 15484, 0.0276, 1, 0, 1, 1),
(39426, 15485, 0.0369, 1, 0, 1, 1),
(39426, 15486, 0.0737, 1, 0, 1, 1),
(39426, 15490, 0.0092, 1, 0, 1, 1),
(39426, 15944, 0.0553, 1, 0, 1, 1),
(39426, 15969, 0.0553, 1, 0, 1, 1),
(39426, 15970, 0.0092, 1, 0, 1, 1),
(39426, 52559, -74.7236, 1, 0, 1, 1);

DELETE FROM `pickpocketing_loot_template` WHERE `entry` = '39426';
INSERT INTO `pickpocketing_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(39426, 414, 5.7377, 1, 0, 1, 1),
(39426, 818, 1.6393, 1, 0, 1, 1),
(39426, 858, 11.1111, 1, 0, 1, 1),
(39426, 4293, 0.8197, 1, 0, 1, 1),
(39426, 4537, 13.9344, 1, 0, 1, 1),
(39426, 4541, 17.2131, 1, 0, 1, 1),
(39426, 5368, 54.0984, 1, 0, 1, 1);

DELETE FROM `creature_addon` WHERE  `guid` IN
(833721,833796,833807,833845,833778,833766,833753,833803);
UPDATE `creature` SET `unit_flags`=0 WHERE `guid` IN
(833721,833796,833807,833845,833778,833766,833753,833803);

UPDATE `quest_template` SET `SpecialFlags`=0 WHERE `Id` IN (25244, 25243);

DELETE FROM `playercreateinfo_spell` WHERE  `racemask`=2099197 AND `classmask`=16 AND `Spell`=77486;
UPDATE `gossip_menu_option` SET `option_id`=3, `npc_option_npcflag`=128 WHERE `menu_id`=11009 AND `id`=0;

DELETE FROM `creature_text` WHERE `entry`=39456;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39456,0,0,'What are these rockets for?!',12,0,100,0,0,0,'Comment'),
(39456,0,1,'3... 2... 1...',12,0,100,0,0,0,'Comment'),
(39456,0,2,'The pirates have keys!',12,0,100,0,0,0,'Comment'),
(39456,0,3,'Mommy!',12,0,100,0,0,0,'Comment'),
(39456,0,4,'$n, you and Hobart are going to be the death of me!',12,0,100,0,0,0,'Comment'),
(39456,0,5,'Um... you do realize that there\'s a bottom to this cage?!',12,0,100,0,0,0,'Comment'),
(39456,0,6,'Just open the door... oh no!',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_template_addon` WHERE `entry` = '39456';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(39456, 1, '73926');

UPDATE `creature_template` SET `IconName`='Interact', `npcflag`=1 WHERE `entry`=39456;

-- Captured Goblin
SET @ENTRY := 39456;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,64,0,100,0,0,0,0,0,1,0,3500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,75,73948,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Rockets"),
(@ENTRY,@SOURCETYPE,3,0,64,0,100,0,0,0,0,0,33,39456,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Quest Credit"),
(@ENTRY,@SOURCETYPE,4,0,64,0,100,0,0,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Disable Npc flag");

DELETE FROM `spell_script_names` WHERE `spell_id` = '73948';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(73948, 'spell_escape_velocity_rockets');

-- Brute Bodyguard
SET @ENTRY := 39589;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,6000,15000,6000,15000,11,10966,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Uppercut");

UPDATE `creature_template` SET `mindmg`=13, `maxdmg`=19, `attackpower`=5, `lootid`=39589, `mingold`=21, `maxgold`=21 WHERE `entry`=39589;

DELETE FROM `creature_loot_template` WHERE `entry` = '39589';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(39589, 858, 3.8462, 1, 0, 1, 1),
(39589, 1179, 1.9, 1, 0, 1, 1),
(39589, 1210, 11.1111, 1, 0, 1, 1),
(39589, 1495, 0.4525, 1, 0, 1, 1),
(39589, 1497, 0.6787, 1, 0, 1, 1),
(39589, 1502, 0.6787, 1, 0, 1, 1),
(39589, 1503, 0.6787, 1, 0, 1, 1),
(39589, 1504, 1.1312, 1, 0, 1, 1),
(39589, 1506, 0.6787, 1, 0, 1, 1),
(39589, 1509, 5.5556, 1, 0, 1, 1),
(39589, 1510, 0.6787, 1, 0, 1, 1),
(39589, 1511, 5.5556, 1, 0, 1, 1),
(39589, 1512, 0.4525, 1, 0, 1, 1),
(39589, 1514, 0.4525, 1, 0, 1, 1),
(39589, 1516, 1.81, 1, 0, 1, 1),
(39589, 1731, 0.2262, 1, 0, 1, 1),
(39589, 1735, 2.2624, 1, 0, 1, 1),
(39589, 2075, 0.2262, 1, 0, 1, 1),
(39589, 2214, 0.2262, 1, 0, 1, 1),
(39589, 2215, 0.4525, 1, 0, 1, 1),
(39589, 2287, 9.9548, 1, 0, 1, 1),
(39589, 2406, 0.2262, 1, 0, 1, 1),
(39589, 2455, 1.3575, 1, 0, 1, 1),
(39589, 2589, 74.2081, 1, 0, 1, 1),
(39589, 2763, 0.905, 1, 0, 1, 1),
(39589, 2777, 0.4525, 1, 0, 1, 1),
(39589, 2778, 0.6787, 1, 0, 1, 1),
(39589, 3036, 0.2262, 1, 0, 1, 1),
(39589, 3192, 0.905, 1, 0, 1, 1),
(39589, 3279, 0.2262, 1, 0, 1, 1),
(39589, 3286, 0.2262, 1, 0, 1, 1),
(39589, 3287, 0.2262, 1, 0, 1, 1),
(39589, 3290, 0.2262, 1, 0, 1, 1),
(39589, 3303, 0.2262, 1, 0, 1, 1),
(39589, 3304, 0.4525, 1, 0, 1, 1),
(39589, 3307, 0.6787, 1, 0, 1, 1),
(39589, 3374, 0.6787, 1, 0, 1, 1),
(39589, 3375, 0.4525, 1, 0, 1, 1),
(39589, 3649, 0.2262, 1, 0, 1, 1),
(39589, 4561, 0.4525, 1, 0, 1, 1),
(39589, 4675, 0.2262, 1, 0, 1, 1),
(39589, 4692, 0.2262, 1, 0, 1, 1),
(39589, 5069, 0.4525, 1, 0, 1, 1),
(39589, 8180, 0.4525, 1, 0, 1, 1),
(39589, 14089, 0.2262, 1, 0, 1, 1),
(39589, 14090, 0.4525, 1, 0, 1, 1),
(39589, 14365, 0.4525, 1, 0, 1, 1),
(39589, 15473, 0.4525, 1, 0, 1, 1),
(39589, 15477, 0.2262, 1, 0, 1, 1),
(39589, 15482, 0.2262, 1, 0, 1, 1),
(39589, 15485, 0.2262, 1, 0, 1, 1),
(39589, 15944, 0.2262, 1, 0, 1, 1),
(39589, 15969, 0.4525, 1, 0, 1, 1);

UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `exp`=3, `VehicleId`=696 WHERE `entry`=39598;

DELETE FROM `creature_text` WHERE `entry`=39582;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39582,0,0,'Gotta trim some fat around here. I\'m downsizing the company!',14,0,100,0,0,19573,'Comment'),
(39582,0,1,'I\'m downsizing the cartel, starting with you!',14,0,100,0,0,19571,'Comment'),
(39582,0,2,'The Bilgewater Cartel has grown too large. Time to downsize! ',14,0,100,0,0,19572,'Comment'),
(39582,1,0,'Here\'s some of that moolah back that I took from you.',14,0,100,0,0,19577,'Comment'),
(39582,1,1,'I like you. Here\'s a raise!',14,0,100,0,0,19578,'Comment'),
(39582,1,2,'I\'m so money!',14,0,100,0,0,19579,'Comment'),
(39582,2,0,'Here, I need to unload some toxic assets!',14,0,100,0,0,19568,'Comment'),
(39582,2,1,'Excuse me while I dispose of these toxic assets all over you!',14,0,100,0,0,16569,'Comment'),
(39582,2,2,'I need to move these toxic assets onto a sucker... like you!',14,0,100,0,0,19570,'Comment'),
(39582,3,0,'You burned down my headquarters, now I\'m going to burn down you! ',14,0,100,0,0,19576,'Comment'),
(39582,3,1,'You\'re fired!',14,0,100,0,0,19574,'Comment'),
(39582,3,2,'I\'m all fired up over finally getting rid of you!',14,0,100,0,0,19575,'Comment'),
(39582,4,0,'I SEE THE TRAITOR IS HERE TO RESCUE YOU, WARCHIEF. HOW CONVENIENT. YOU WILL BOTH BOW TO ME OR FALL TOGETHER!',14,0,100,0,0,19567,'Comment'),
(39582,5,0,'Uncle! Uncle! I give! You guys are too much for me!',14,0,100,0,0,19580,'Comment'),
(39582,6,0,'I\'m beaten. You\'ve shown me the error of my ways. From here on out, I promise to reform the way that the cartel is run!',14,0,100,0,0,19581,'Comment'),
(39582,7,0,'I\'m your goblin, Thrall. What would you have of me?',14,0,100,0,0,19582,'Comment'),
(39582,8,0,'It will be as you say! Long live the Bilgewater Cartel! For the Horde!',14,0,100,0,0,19583,'Comment');

DELETE FROM `creature_text` WHERE `entry`=39594;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39594,0,0,'For now, you will remain the Trade Prince of the Bilgewater Cartel.',14,0,100,0,0,22513,'Comment'),
(39594,1,0,'I will send a representative from amongst your people to the new warchief, Garrosh Hellscream in Orgrimmar.',14,0,100,0,0,20148,'Comment'),
(39594,2,0,'You will have a new home in Azshara and the Bilgewater Cartel will be part of the Horde!',14,0,100,0,0,20149,'Comment');

DELETE FROM `creature_addon` WHERE `guid` = '833835';
INSERT INTO `creature_addon` (`guid`, `mount`, `bytes2`) VALUES
(833835, 29681, 1);

DELETE FROM `creature_addon` WHERE `guid` = '833955';
INSERT INTO `creature_addon` (`guid`, `mount`, `bytes2`) VALUES
(833955, 29681, 1);

UPDATE `creature_template` SET `ScriptName`='npc_gallywix_final_event' WHERE `entry`=39582;
UPDATE `creature_template` SET `ScriptName`='npc_thrall_final_event' WHERE `entry`=39594;
UPDATE `creature_template` SET `npcflag`=1, `ScriptName`='npc_ultimate_footbomb_uniform' WHERE `entry`=39592;
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=39594;
UPDATE `creature_template` SET `Health_mod`=5, `Mana_mod`=5 WHERE `entry`=39582;
UPDATE `quest_template` SET `SourceSpellId`=74028 WHERE `Id`=25265;

DELETE FROM `spell_script_names` WHERE `spell_id` = '74028';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(74028, 'spell_rockin_powder_infused_boots_docks');

UPDATE `creature` SET `phaseMask`=8192 WHERE `id`=39449 AND `phaseMask`=1;
UPDATE `creature` SET `phaseMask`=8192 WHERE `id`=39456 AND `phaseMask`=1;
UPDATE `creature` SET `phaseMask`=8192 WHERE `id`=39589 AND `phaseMask`=1;

-- Thrall
SET @ENTRY := 38935;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,1000,1000,1000,1000,28,74028,0,0,0,0,0,18,20,0,0,0.0,0.0,0.0,0.0,"OOC - Remove Boots");

-- Trade Prince Gallywix
SET @ENTRY := 39615;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,2500,3500,2500,3500,45,0,50,0,0,0,0,11,0,80,0,0.0,0.0,0.0,0.0,"OOC - Set Data 50 to Creatures in Range");

UPDATE `gameobject_template` SET `ScriptName`='go_gallywix_docks_fireworks' WHERE `name` LIKE '%quest phase 10 (scale x2)';
UPDATE `gameobject` SET `phaseMask`=32768 WHERE `id` IN (203275,203277,203267,203266,203271,203273,203270,203272,203276,203274,203269,203268);
UPDATE `creature_template` SET `gossip_menu_id`=12002 WHERE `entry`=45286;
UPDATE `gossip_menu_option` SET `option_id`=3, `npc_option_npcflag`=128 WHERE `menu_id`=12002 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_icon`=3 WHERE `menu_id`=12002 AND `id`=1;
UPDATE `gossip_menu_option` SET `option_icon`=3 WHERE `menu_id`=12002 AND `id`=2;
UPDATE `gossip_menu_option` SET `option_id`=1 WHERE `menu_id`=12002 AND `id`=1;
UPDATE `gossip_menu_option` SET `option_id`=1 WHERE `menu_id`=12002 AND `id`=2;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12046 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12046 AND `id`=1;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12046 AND `id`=2;
UPDATE `gossip_menu_option` SET `option_icon`=3 WHERE `menu_id`=12046 AND `id`=2;
UPDATE `gossip_menu_option` SET `option_icon`=3 WHERE `menu_id`=12046 AND `id`=0;
UPDATE `gossip_menu_option` SET `action_menu_id`=12045 WHERE `menu_id`=12002 AND `id`=1;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=12045;
UPDATE `gossip_menu_option` SET `option_icon`=3 WHERE `menu_id`=12046 AND `id`=1;
UPDATE `gossip_menu_option` SET `option_icon`=0 WHERE `menu_id`=12002 AND `id`=1;
UPDATE `gossip_menu_option` SET `option_icon`=0 WHERE `menu_id`=12002 AND `id`=2;
UPDATE `creature_template` SET `trainer_type`=2 WHERE `entry`=45286;

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11244 AND `id`=0;
UPDATE `gossip_menu_option` SET `menu_id`=12582, `id`=1 WHERE `menu_id`=11244 AND `id`=0;

DELETE FROM `conditions` WHERE `SourceGroup`=12582 AND `SourceEntry` = '1';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 12582, 1, 0, 0, 9, 0, 25266, 0, 0, 0, 0, 0, '', 'Sassy Headwrench - Show gossip only if quest 25266 is active');

UPDATE `quest_template` SET `SourceSpellId`=74032 WHERE `Id`=25267;
UPDATE `creature_template` SET `minlevel`=12, `maxlevel`=12, `speed_run`=2.14286, `VehicleId`=802, `unit_flags`=768 WHERE  `entry`=39611;

DELETE FROM `waypoints` WHERE `entry` = '39611';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(39611, 1, 1440.34, -5015.43, 12.13, 'Battleworg WP'),
(39611, 2, 1429.43, -4912.09, 12.21, 'Battleworg WP'),
(39611, 3, 1421.00, -4863.09, 12.23, 'Battleworg WP'),
(39611, 4, 1407.01, -4811.09, 21.76, 'Battleworg WP'),
(39611, 5, 1372.77, -4741.49, 28.07, 'Battleworg WP'),
(39611, 6, 1371.63, -4676.04, 27.76, 'Battleworg WP'),
(39611, 7, 1311.42, -4583.58, 23.59, 'Battleworg WP'),
(39611, 8, 1307.53, -4505.59, 22.76, 'Battleworg WP'),
(39611, 9, 1317.92, -4452.92, 24.93, 'Battleworg WP'),
(39611, 10, 1313.77, -4388.52, 26.09, 'Battleworg WP'),
(39611, 11, 1346.18, -4376.88, 26.16, 'Battleworg WP');

-- Battleworg
SET @ENTRY := 39611;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,53,1,39611,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,40,0,100,0,11,0,0,0,28,74030,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Remove Passenger");

-- SI:7 Operative
SET @ENTRY := 36103;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,500,500,5000,5000,49,0,0,0,0,0,0,11,0,35,0,0.0,0.0,0.0,0.0,"OOC - Attack");

-- Thrall
SET @ENTRY := 36161;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,14243,0,0,0,85,68408,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Summon Event");

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=832335;
UPDATE `creature_template` SET `mindmg`=7, `maxdmg`=11, `attackpower`=3 WHERE `entry`=38696;
UPDATE `creature_template` SET `InhabitType`=3 WHERE `entry`=38802;
UPDATE `creature` SET `phaseMask`=32768 WHERE `guid`=832814;

-- Volcanoth Champion
SET @ENTRY := 38850;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,500,500,5000,5000,49,0,0,0,0,0,0,11,0,10,0,0.0,0.0,0.0,0.0,"OOC - Attack Creatures");