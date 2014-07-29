-- Trogg Dweller
SET @ENTRY := 39450;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1500,1500,3500,4500,11,76507,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Claw Puncture"),
(@ENTRY,@SOURCETYPE,1,0,6,0,100,0,0,0,0,0,33,51182,0,0,0,0,0,18,150,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit");

-- Twilight Firecatcher
SET @ENTRY := 39870;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,2,1000,3000,6000,8000,11,76765,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Twilight Firecatcher"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,2,5000,10000,15000,20000,11,76766,1,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"Twilight Firecatcher"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,6,11000,16000,40000,45000,11,74551,1,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Twilight Firecatcher"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,4,1000,3000,6000,8000,11,90849,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Twilight Firecatcher"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,4,5000,10000,15000,20000,11,90851,1,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"Twilight Firecatcher"),
(@ENTRY,@SOURCETYPE,5,0,6,0,100,0,0,0,0,0,33,51184,0,0,0,0,0,18,150,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit");

-- Twilight Thundercaller
SET @ENTRY := 40270;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,2,2000,4000,9000,11000,11,76579,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Twilight Thundercaller"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,2,5000,7000,12000,14000,11,76578,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Twilight Thundercaller"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,6,15000,20000,45000,50000,11,75096,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Twilight Thundercaller"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,4,2000,4000,9000,11000,11,90858,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Twilight Thundercaller"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,4,5000,7000,12000,14000,11,90856,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Twilight Thundercaller"),
(@ENTRY,@SOURCETYPE,5,0,6,0,100,0,0,0,0,0,33,51184,0,0,0,0,0,18,150,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit");

-- Twilight Earthshaper
SET @ENTRY := 39890;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,2,5000,5000,6000,7000,11,76603,1,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"Twilight Earthshaper"),
(@ENTRY,@SOURCETYPE,1,0,2,0,100,2,5,30,8000,8100,11,76596,1,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Twilight Earthshaper"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,6,10000,15000,40000,45000,11,74552,1,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Twilight Earthshaper"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,4,5000,5000,6000,7000,11,90487,1,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"Twilight Earthshaper"),
(@ENTRY,@SOURCETYPE,4,0,2,0,100,4,5,30,8000,8100,11,90486,1,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Twilight Earthshaper"),
(@ENTRY,@SOURCETYPE,5,0,6,0,100,0,0,0,0,0,33,51184,0,0,0,0,0,18,150,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit");

-- Twilight Stormbreaker
SET @ENTRY := 39962;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,2,5000,7000,16000,18000,11,76720,1,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"Twilight Stormbreaker"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,6,10000,15000,40000,45000,11,76561,1,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Twilight Stormbreaker"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,4,5000,7000,16000,18000,11,90522,1,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"Twilight Stormbreaker"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,4,2000,4000,8000,10000,11,90491,1,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"Twilight Stormbreaker"),
(@ENTRY,@SOURCETYPE,4,0,6,0,100,0,0,0,0,0,33,51184,0,0,0,0,0,18,150,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit");

UPDATE `creature_template` SET `mindmg`=550, `maxdmg`=950, `attackpower`=36, `dmg_multiplier`=7, `rangeattacktime`=1500, `minrangedmg`=300, `maxrangedmg`=450, `rangedattackpower`=113, `mingold`=6367, `maxgold`=6367 WHERE `entry` IN
(39450, 48509, 39854, 48661, 39855, 48745, 39381, 48654, 41073, 48611, 39890, 48595, 39962, 48597, 39956, 48666, 39890, 48595,
39415, 48677, 40268, 48744, 39626, 48682, 39870, 48748, 39909, 48680, 39873, 48754, 40273, 48753, 40272, 48751, 40270, 48750,
41095, 48755, 40167, 48695, 40166, 48693, 39414, 48676, 39954, 48669, 39390);

UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `exp`=3, `faction_A`=1771, `faction_H`=1771, `mindmg`=1007, `maxdmg`=1354.7, `attackpower`=138, `dmg_multiplier`=45.7, `baseattacktime`=2000, `rangeattacktime`=2000, `minrangedmg`=832, `maxrangedmg`=1023, `rangedattackpower`=79 WHERE `entry` IN 
(39450, 48509, 39854, 48661, 39855, 48745, 39381, 48654, 41073, 48611, 39890, 48595, 39962, 48597, 39956, 48666, 39890, 48595,
39415, 48677, 40268, 48744, 39626, 48682, 39870, 48748, 39909, 48680, 39873, 48754, 40273, 48753, 40272, 48751, 40270, 48750,
41095, 48755, 40167, 48695, 40166, 48693, 39414, 48676, 39954, 48669, 39390, 39405, 48652, 39855, 40291, 40448, 48667, 40306,
48610);

UPDATE `creature_template` SET `speed_walk`=2, `speed_run`=2.42857 WHERE `entry`=39390;
UPDATE `creature_template` SET `VehicleId`=156, `spell1`=74039, `speed_walk`=1, `speed_run`=2.42857 WHERE `entry`=39294;
UPDATE `creature` SET `spawndist`=20, `MovementType`=1 WHERE `id` IN (41095, 39390, 42608);

DELETE FROM `creature_text` WHERE `entry`=39294;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39294,0,0,'Welcome, friend. Let\'s ride through Grim Batol and strike a blow against Deathwing that he won\'t soon forget!',15,0,100,0,0,0,'Comment'),
(39294,1,1,'Once we are all free, we shall fly with you through Grim Batol!',12,0,100,0,0,0,'Comment'),
(39294,1,2,'Please champions, rescue my brethren from the Twilight\'s Hammer!',12,0,100,0,0,0,'Comment'),
(39294,1,3,'Please heroes, help my brothers and we shall assist you!',12,0,100,0,0,0,'Comment'),
(39294,1,4,'Please! Free the others from their Nets!',12,0,100,0,0,0,'Comment'),
(39294,2,0,'Thank you for rescuing me, now please aid the rest of my brood!',12,0,100,0,0,0,'Comment'),
(39294,2,1,'The Twilight Dragonkin must be stopped! Rescue the other Red Dragonflight and we shall assist you!',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `unit_flags`=0, `unit_flags2`=2048, `HoverHeight`=1 WHERE `entry`=39294;

DELETE FROM `spell_script_names` WHERE `spell_id` = '74040';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(74040, 'spell_engulfing_flames');

UPDATE `creature` SET `phaseMask`=1 WHERE `id`=39294;
DELETE FROM `creature_template_addon` WHERE `entry`=39294;
UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry`=39294;

DELETE FROM `creature_loot_template` WHERE `item` = '66927';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(40319, 66927, -100, 1, 0, 1, 1),
(48784, 66927, -100, 1, 0, 1, 1);