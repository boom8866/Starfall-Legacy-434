-- Mutant Bush Chicken
SET @ENTRY := 44935;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,2,54,0,100,1,0,0,0,0,29,0,0,0,0,0,0,11,44367,100,0,0.0,0.0,0.0,0.0,"On Just Summoned - Follow Ettin"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,1,0,1,0,0,11,46598,0,0,0,0,0,11,44367,50,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Ride Ettin"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Run"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,1,0,1,0,0,45,0,1,0,0,0,0,11,44367,10,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Data 1 to Ettin"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,1,0,1,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Force Despawn");

-- Mutant Bush Chicken
SET @ENTRY := 4493500;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;

-- Forest Ettin
SET @ENTRY := 44367;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5000,7000,17000,22000,11,80146,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Bonk"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,12000,15000,28000,35000,11,88421,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Log Smash"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,2000,2000,2000,2000,45,0,1,0,0,0,0,11,44935,25,0,0.0,0.0,0.0,0.0,"IC - Set Data 1 to Chicken"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,1,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Phase 1"),
(@ENTRY,@SOURCETYPE,4,0,0,1,100,0,2000,2000,20000,20000,11,72942,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Explosion"),
(@ENTRY,@SOURCETYPE,5,0,0,1,100,0,4000,4000,5000,5000,11,83903,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Explosion"),
(@ENTRY,@SOURCETYPE,6,0,0,1,100,0,3000,3000,20000,20000,33,44367,0,0,0,0,0,18,100,0,0,0.0,0.0,0.0,0.0,"IC - Quest Credit"),
(@ENTRY,@SOURCETYPE,7,0,0,1,100,0,1500,1500,1500,1500,41,15000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Force Despawn");

-- Fallen Human
SET @ENTRY := 4459300;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,0,0,0,0,69,0,0,0,0,0,0,19,144951,15,0,0.0,0.0,0.0,0.0,"move to nearest trigger"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,5000,0,0,69,0,0,0,0,0,0,19,144953,15,0,0.0,0.0,0.0,0.0,"move to nearest trigger"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,0,0,0,0,12,44597,3,30000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"summon 44596 on self"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,500,500,0,0,41,2000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"force despawn self");

UPDATE `creature_template` SET `mindmg`=14, `maxdmg`=22, `attackpower`=5, `dmg_multiplier`=2 WHERE `entry` IN
(44987, 45195, 45219, 45255);

-- Magistrate Henry Maleb
SET @ENTRY := 44996;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,31,0,100,0,84097,1,0,0,45,0,2,0,0,0,0,11,44951,50,0,0.0,0.0,0.0,0.0,"Set DATA 2 to Agatha");

DELETE FROM `creature_text` WHERE `entry`=44996;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(44996,0,0,'We would rather die than be turned into worgen, but seeing as how even death provides no relief from the atrocities of this war...',12,0,100,1,0,0,'Comment'),
(44996,1,0,'We choose vengeance!',12,0,100,1,0,0,'Comment');

-- Agatha
SET @ENTRY := 44951;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,1,0,37,0,100,0,0,0,0,0,75,85451,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Add Death Walk to self"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,8000,8000,8000,8000,11,83173,0,0,0,0,0,11,44593,10,0,0.0,0.0,0.0,0.0,"Raise Forsaken from Fallen Humans"),
(@ENTRY,@SOURCETYPE,3,0,31,0,100,0,83173,1,0,0,33,44953,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Quest Credit"),
(@ENTRY,@SOURCETYPE,4,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Run"),
(@ENTRY,@SOURCETYPE,5,0,37,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Passive"),
(@ENTRY,@SOURCETYPE,6,0,0,0,50,0,1500,1500,1500,1500,11,84012,0,0,0,0,0,11,44987,3,0,0.0,0.0,0.0,0.0,"Cast Doomhowl"),
(@ENTRY,@SOURCETYPE,7,0,0,0,25,0,5000,5000,5000,5000,11,84013,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Cast Unholy Darkness"),
(@ENTRY,@SOURCETYPE,8,0,0,0,50,0,1500,1500,1500,1500,11,84014,0,0,0,0,0,11,44987,3,0,0.0,0.0,0.0,0.0,"Cast Unholy Smite"),
(@ENTRY,@SOURCETYPE,9,0,1,0,100,0,10000,10000,40000,40000,1,0,5000,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Talk 0"),
(@ENTRY,@SOURCETYPE,10,0,31,0,100,0,83173,1,1500,1500,1,1,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Talk 1"),
(@ENTRY,@SOURCETYPE,11,0,38,0,100,0,0,1,0,0,80,4495100,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Data Set 1 Call Actionlist"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,1,2,44951,0,0,12,44989,8,120000,0,0,0,8,0,0,0,992.64,692.38,74.89,6.09,"Summon Crowley on Text 2"),
(@ENTRY,@SOURCETYPE,13,0,38,0,100,0,0,2,0,0,80,4495101,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Data Set 2 Call Actionlist"),
(@ENTRY,@SOURCETYPE,14,0,40,0,100,0,18,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 18 - Remove Passenger"),
(@ENTRY,@SOURCETYPE,15,0,1,0,100,0,5000,5000,5000,5000,49,0,0,0,0,0,0,11,44987,5,0,0.0,0.0,0.0,0.0,"OOC - Attack Worgens"),
(@ENTRY,@SOURCETYPE,16,0,4,0,100,0,0,0,0,0,8,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Aggro - Set Defensive"),
(@ENTRY,@SOURCETYPE,17,0,1,0,100,0,5000,5000,5000,5000,8,0,0,0,0,0,0,1,44987,5,0,0.0,0.0,0.0,0.0,"OOC - Set Passive"),
(@ENTRY,@SOURCETYPE,18,0,38,0,100,0,0,1,0,0,18,512,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Data Set 1 - Set Immune to All");

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '84128';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(84128, 84164, 'Lordaeron Event');

-- Forsaken Warhorse
SET @ENTRY := 45041;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,1,0,0,0,0,86,46598,0,23,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Forsaken Warhorse (Player)"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,53,1,45041,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger boarded - Start WP"),
(@ENTRY,@SOURCETYPE,2,0,39,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Start - Set Run"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,20,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 20 - Dismount"),
(@ENTRY,@SOURCETYPE,4,0,40,0,100,0,15,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP 15 Set Walk");

-- Forsaken Warhorse
SET @ENTRY := 45057;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,2000,2000,0,0,53,1,45057,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,18,1048576,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Taxi"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,1,0,0,0,1,0,8000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 0"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,45051,0,0,1,1,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,45051,0,0,1,2,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 2"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,2,45051,0,0,1,3,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 3"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,3,45051,0,0,1,4,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 4"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,4,45051,0,0,1,5,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 5"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,5,45051,0,0,1,6,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 6"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,6,45051,0,0,1,7,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 7"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,7,45051,0,0,1,8,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 8"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,0,8,45051,0,0,1,9,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 9"),
(@ENTRY,@SOURCETYPE,12,0,52,0,100,0,9,45051,0,0,1,10,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 10"),
(@ENTRY,@SOURCETYPE,13,0,52,0,100,0,10,45051,0,0,1,11,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 11"),
(@ENTRY,@SOURCETYPE,14,0,52,0,100,0,11,45051,0,0,1,12,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 12"),
(@ENTRY,@SOURCETYPE,15,0,52,0,100,0,12,45051,0,0,1,13,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 13"),
(@ENTRY,@SOURCETYPE,16,0,52,0,100,0,13,45051,0,0,1,14,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 14"),
(@ENTRY,@SOURCETYPE,17,0,52,0,100,0,14,45051,0,0,1,15,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 15"),
(@ENTRY,@SOURCETYPE,18,0,52,0,100,0,15,45051,0,0,1,16,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 16"),
(@ENTRY,@SOURCETYPE,19,0,52,0,100,0,16,45051,0,0,1,17,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 17"),
(@ENTRY,@SOURCETYPE,20,0,52,0,100,0,17,45051,0,0,1,18,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 18"),
(@ENTRY,@SOURCETYPE,21,0,52,0,100,0,18,45051,0,0,1,19,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 19"),
(@ENTRY,@SOURCETYPE,22,0,52,0,100,0,19,45051,0,0,1,20,10000,0,0,0,0,11,45051,5,0,0.0,0.0,0.0,0.0,"Talk - 20"),
(@ENTRY,@SOURCETYPE,23,0,40,0,100,0,20,0,0,0,41,3000,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Dismount on WP End"),
(@ENTRY,@SOURCETYPE,24,0,58,0,100,0,0,0,0,0,33,45051,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Quest Completed"),
(@ENTRY,@SOURCETYPE,25,0,52,0,100,0,20,45051,0,0,1,21,5000,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Talk - 21"),
(@ENTRY,@SOURCETYPE,26,0,40,0,100,0,15,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP 15 - Set Walk");

-- Lady Sylvanas Windrunner
SET @ENTRY := 45051;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,46598,0,0,0,0,0,11,45057,5,0,0.0,0.0,0.0,0.0,"Ride Sylvanas Warhorse"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,0,1500,1500,1500,1500,11,84182,4,0,0,0,0,11,44793,40,0,0.0,0.0,0.0,0.0,"Cast Heartstrike"),
(@ENTRY,@SOURCETYPE,2,0,60,0,100,0,1500,1500,1500,1500,11,84182,4,0,0,0,0,11,1778,40,0,0.0,0.0,0.0,0.0,"Cast Heartstrike on Bear"),
(@ENTRY,@SOURCETYPE,3,0,60,0,100,0,1500,1500,1500,1500,11,84182,4,0,0,0,0,11,1766,40,0,0.0,0.0,0.0,0.0,"Cast Heartstrike on Wolf"),
(@ENTRY,@SOURCETYPE,4,0,60,0,100,0,2000,2000,2000,2000,5,66,0,0,0,0,0,11,44911,12,0,0.0,0.0,0.0,0.0,"Salute Sylvanas"),
(@ENTRY,@SOURCETYPE,5,0,60,0,100,0,1500,1500,1500,1500,11,0,0,0,0,0,0,11,1797,40,0,0.0,0.0,0.0,0.0,"Cast Heartstrike on Bear 2"),
(@ENTRY,@SOURCETYPE,6,0,54,0,100,0,0,0,0,0,41,230000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Force Despawn");

DELETE FROM `waypoints` WHERE `entry` IN (45041, 45057);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(45041, 1, 1341.96, 1011.48, 54.59, 'Sylvanas (Lordaeron Event)'),
(45041, 2, 1315.56, 1020.83, 54.59, 'Sylvanas (Lordaeron Event)'),
(45041, 3, 1268.48, 1086.55, 52.33, 'Sylvanas (Lordaeron Event)'),
(45041, 4, 1226.24, 1124.89, 50.47, 'Sylvanas (Lordaeron Event)'),
(45041, 5, 1142.65, 1183.89, 47.89, 'Sylvanas (Lordaeron Event)'),
(45041, 6, 1105.21, 1205, 46.4, 'Sylvanas (Lordaeron Event)'),
(45041, 7, 1040.83, 1269.22, 46.03, 'Sylvanas (Lordaeron Event)'),
(45041, 8, 954.33, 1320.4, 46.54, 'Sylvanas (Lordaeron Event)'),
(45041, 9, 904.19, 1348.97, 48.92, 'Sylvanas (Lordaeron Event)'),
(45041, 10, 865.52, 1358.9, 54.7, 'Sylvanas (Lordaeron Event)'),
(45041, 11, 773.64, 1359.87, 65.12, 'Sylvanas (Lordaeron Event)'),
(45041, 12, 733.14, 1353.96, 71.88, 'Sylvanas (Lordaeron Event)'),
(45041, 13, 670.48, 1306.19, 81.39, 'Sylvanas (Lordaeron Event)'),
(45041, 14, 641.97, 1294.35, 85.6, 'Sylvanas (Lordaeron Event)'),
(45041, 15, 607.69, 1355.34, 87.32, 'Sylvanas (Lordaeron Event)'),
(45041, 16, 579.67, 1416.12, 96.24, 'Sylvanas (Lordaeron Event)'),
(45041, 17, 550.03, 1454.93, 106.07, 'Sylvanas (Lordaeron Event)'),
(45041, 18, 506.98, 1495.19, 124.92, 'Sylvanas (Lordaeron Event)'),
(45041, 19, 497.14, 1531.72, 129.62, 'Sylvanas (Lordaeron Event)'),
(45041, 20, 497.45, 1562.66, 127.63, 'Sylvanas (Lordaeron Event)'),
(45057, 1, 1344.96, 1011.48, 54.59, 'Sylvanas (Lordaeron Event)'),
(45057, 2, 1318.56, 1020.83, 54.59, 'Sylvanas (Lordaeron Event)'),
(45057, 3, 1271.48, 1086.55, 52.33, 'Sylvanas (Lordaeron Event)'),
(45057, 4, 1229.24, 1124.89, 50.47, 'Sylvanas (Lordaeron Event)'),
(45057, 5, 1145.65, 1183.89, 47.89, 'Sylvanas (Lordaeron Event)'),
(45057, 6, 1108.21, 1205, 46.4, 'Sylvanas (Lordaeron Event)'),
(45057, 7, 1043.83, 1269.22, 46.03, 'Sylvanas (Lordaeron Event)'),
(45057, 8, 957.33, 1320.4, 46.54, 'Sylvanas (Lordaeron Event)'),
(45057, 9, 907.19, 1348.97, 48.92, 'Sylvanas (Lordaeron Event)'),
(45057, 10, 868.52, 1358.9, 54.7, 'Sylvanas (Lordaeron Event)'),
(45057, 11, 776.64, 1359.87, 65.12, 'Sylvanas (Lordaeron Event)'),
(45057, 12, 736.14, 1353.96, 71.88, 'Sylvanas (Lordaeron Event)'),
(45057, 13, 673.48, 1306.19, 81.39, 'Sylvanas (Lordaeron Event)'),
(45057, 14, 644.97, 1294.35, 85.6, 'Sylvanas (Lordaeron Event)'),
(45057, 15, 610.69, 1355.34, 87.32, 'Sylvanas (Lordaeron Event)'),
(45057, 16, 582.67, 1416.12, 96.24, 'Sylvanas (Lordaeron Event)'),
(45057, 17, 553.03, 1454.93, 106.07, 'Sylvanas (Lordaeron Event)'),
(45057, 18, 509.98, 1495.19, 124.92, 'Sylvanas (Lordaeron Event)'),
(45057, 19, 500.14, 1531.72, 129.62, 'Sylvanas (Lordaeron Event)'),
(45057, 20, 500.45, 1562.66, 127.63, 'Sylvanas (Lordaeron Event)');

UPDATE `quest_template` SET `PrevQuestId`='27098' WHERE `Id`=27181;
UPDATE `quest_template` SET `PrevQuestId`='27098' WHERE `Id`=27231;
UPDATE `quest_template` SET `ExclusiveGroup`=0, `PrevQuestId`='0' WHERE `Id`=27226;

DELETE FROM `conditions` WHERE `SourceEntry` = '27226' AND `SourceTypeOrReferenceId` = '20' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(20, 8, 27226, 27098, 0);

DELETE FROM `conditions` WHERE `SourceEntry` = '27226' AND `SourceTypeOrReferenceId` = '19' AND `ConditionTypeOrReference`='8';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `ConditionTypeOrReference`, `SourceEntry`, `ConditionValue1`, `ElseGroup`) VALUES
(19, 8, 27226, 27098, 0);

-- Orc Sea Dog
SET @ENTRY := 45196;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,84517,1,0,0,1,0,2500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk on Spellhit"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,45196,0,0,33,45196,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Quest Credit"),
(@ENTRY,@SOURCETYPE,2,0,8,0,100,0,84517,1,0,0,28,84511,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Remove buff"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,45196,0,0,41,3000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Despawn");

UPDATE `creature_template` SET `mindmg`=14, `maxdmg`=22, `attackpower`=5, `dmg_multiplier`=2 WHERE `entry` IN
(44987, 45195, 45219, 45255);

UPDATE `gameobject` SET `phaseMask`=3 WHERE `guid`=778999;

DELETE FROM `world_quest_phases` WHERE `QuestId` = '27232' AND `type` = '1';
INSERT INTO `world_quest_phases` (`QuestId`, `Phase`, `type`, `ZoneId`, `AreaId`, `Comment`) VALUES
(27232, 2, 1, 130, 1338, 'Quest ID: 27232 - The Waters Run Red... (ON QUEST ACCEPT)');

UPDATE `gameobject` SET `phaseMask`=32769 WHERE `id`=205367;
UPDATE `creature_template_addon` SET `emote`=0 WHERE `entry` IN (45280, 45532, 45762, 45777, 45882, 46086);

-- Forsaken Vanguard
SET @ENTRY := 45777;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,2,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,2,0,0,46,150,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Move Forward"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,2,0,0,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 2 - Set Aggressive");

DELETE FROM `world_quest_phases` WHERE `QuestId` = '27333' AND `type` = '4';
INSERT INTO `world_quest_phases` (`QuestId`, `Phase`, `type`, `MapId`, `ZoneId`, `AreaId`, `Comment`) VALUES
(27333, 32768, 4, 0, 4706, 5440, 'Quest ID: 27333 - Losing Ground (ON AURA UPDATE)');

UPDATE `creature_template` SET `mindmg`=16, `maxdmg`=23, `attackpower`=12 WHERE `entry` IN (45292, 45403, 45405, 45753, 45750);
UPDATE `creature` SET `spawntimesecs`=60 WHERE `id` IN (45292, 45405);
UPDATE `creature_template` SET `mindmg`=16, `maxdmg`=23, `attackpower`=6, `dmg_multiplier`=1 WHERE `entry`=45280;

-- Forward Commander Onslaught
SET @ENTRY := 45315;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,27405,0,0,0,85,91202,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accepted - Fadeout");

UPDATE `quest_template` SET `SpecialFlags`=2 WHERE `Id`=27349;
UPDATE `quest_template` SET `Flags`=0 WHERE `Id` IN (27364, 27401);

DELETE FROM `world_quest_phases` WHERE `QuestId` = '27349';
INSERT INTO `world_quest_phases` (`QuestId`, `Phase`, `type`, `ZoneId`, `AreaId`, `Comment`) VALUES
(27349, 32768, 4, 4706, 5443, 'Quest ID: 27349 - Break in Communications: Dreadwatch Outpost (ON AURA UPDATE)'),
(27349, 32768, 2, 4706, 5443, 'Quest ID: 27349 - Break in Communications: Dreadwatch Outpost (ON QUEST REWARDED)');

DELETE FROM `world_quest_phases` WHERE `QuestId` IN (27364, 27360);
INSERT INTO `world_quest_phases` (`QuestId`, `Phase`, `type`, `ZoneId`, `AreaId`, `Comment`) VALUES
(27364, 32768, 4, 4706, 5435, 'Quest ID: 27364 - On Whose Orders? (ON AURA UPDATE)'),
(27360, 32768, 4, 4706, 5435, 'Quest ID: 27360 - Vengeance for Our Soldiers (ON AURA UPDATE)');

-- Arthura
SET @ENTRY := 45611;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,86,46598,0,23,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Grab Owner"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,53,1,45611,0,27290,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Start WP"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP 1 Reached - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,6,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Last WP Reached - Leave Vehicle");

-- Arthura
SET @ENTRY := 45473;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2500,4500,3000,6000,11,84014,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Unholy Smite"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,7000,7000,7000,7000,11,84013,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Unholy Darkness"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,12000,12000,20000,20000,11,84992,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Doomhowl");

-- Deathstalker Commander Belmont
SET @ENTRY := 45474;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,79864,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Aggro - Cast Shadowstep"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,3000,3000,3000,3000,11,79862,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Backstab"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,4000,4000,4000,4000,11,79851,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Fan of Knives");

DELETE FROM `waypoints` WHERE `entry` = '45314';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(45314, 1, -2040.33, 825.91, 132.71, 'Arthura Final WP'),
(45314, 2, -1323.74, 746.55, 147.21, 'Arthura Final WP'),
(45314, 3, -740.26, 997.55, 209.63, 'Arthura Final WP'),
(45314, 4, -552.54, 1172.38, 209.17, 'Arthura Final WP'),
(45314, 5, -179.06, 1286.47, 48.93, 'Arthura Final WP');

DELETE FROM `creature_text` WHERE `entry` = '45576';
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(45576, 0, 0, 'I live again...', 12, 0, 100, 1, 0, 0, 'Comment'),
(45576, 1, 0, 'The irony of what I have become is not lost upon me, Lady Sylvanas.', 12, 0, 100, 1, 0, 0, 'Comment'),
(45576, 2, 0, 'Though as I have always said, better dead than worgen.', 12, 0, 100, 1, 0, 0, 'Comment'),
(45576, 3, 0, 'Or in this case, better undead than worgen.', 12, 0, 100, 1, 0, 0, 'Comment');

UPDATE `creature_template` SET `minlevel`=15, `maxlevel`=15, `speed_walk`=3, `speed_run`=3, `unit_flags`=768, `VehicleId`=1075, `InhabitType`=4, `HoverHeight`=2.4 WHERE `entry`=45611;

DELETE FROM `waypoints` WHERE `entry` = '45611';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(45611, 1, 480.35, 1541.18, 158.89, 'Arthura to Gilneas'),
(45611, 2, 255.29, 1453.4, 164.76, 'Arthura to Gilneas'),
(45611, 3, -372.69, 1430.74, 180.49, 'Arthura to Gilneas'),
(45611, 4, -732.05, 1547.03, 72.42, 'Arthura to Gilneas'),
(45611, 5, -887.05, 1580.53, 76.02, 'Arthura to Gilneas'),
(45611, 6, -932.12, 1632.24, 73, 'Arthura to Gilneas');

UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=-100 WHERE `entry`=45711 AND `item`=61307;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=-100 WHERE `entry`=47009 AND `item`=61307;

DELETE FROM `spell_area` WHERE `spell` = '85320' AND `quest_start` IN (27483, 27478, 27483, 27478);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(85320, 228, 27483, 27483, 0, 0, 2, 1, 10, 10),
(85320, 228, 27478, 27483, 0, 0, 2, 1, 10, 10),
(85320, 279, 27483, 27483, 0, 0, 2, 1, 10, 10),
(85320, 279, 27478, 27483, 0, 0, 2, 1, 10, 10);

DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` IN (45731, 45732);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(45731, 85317, 1, 0),
(45732, 85318, 1, 0);

-- Archmage Ataeric
SET @ENTRY := 2120;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,18,4,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Rooted"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,2120,0,0,1,1,3000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,2120,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Set Phase 1"),
(@ENTRY,@SOURCETYPE,4,0,0,1,100,0,3000,20000,12500,25000,11,87253,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Phase 1 - Summon Arcane Fiend"),
(@ENTRY,@SOURCETYPE,5,7,6,0,100,0,0,0,0,0,1,7,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Talk 7"),
(@ENTRY,@SOURCETYPE,6,0,6,0,100,0,0,0,0,0,33,45769,0,0,0,0,0,18,100,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit");

UPDATE `creature` SET `spawntimesecs`=60 WHERE `guid`=773227;

-- Arcane Fiend
SET @ENTRY := 45766;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,18,25,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Closest Player"),
(@ENTRY,@SOURCETYPE,1,0,6,0,100,0,0,0,0,0,11,87249,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Cast Arcane Expulsion");

DELETE FROM `conditions` WHERE `SourceEntry` = '85600' AND `SourceTypeOrReferenceId` = '13';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(13, 1, 85600, 0, 2, 31, 0, 3, 45938, 0, 0, 0, 0, '', 'Toss Torch'),
(13, 1, 85600, 0, 1, 31, 0, 3, 45937, 0, 0, 0, 0, '', 'Toss Torch'),
(13, 1, 85600, 0, 3, 31, 0, 3, 45939, 0, 0, 0, 0, '', 'Toss Torch');

UPDATE `creature_template` SET `dmg_multiplier`=3.5 WHERE `entry` IN (45878, 45879, 45880);
UPDATE `creature` SET `phaseMask`=32769 WHERE `id`=45896;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=100 WHERE `entry`=45896 AND `item`=61505;
UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=27574;