DELETE FROM `spell_script_names` WHERE `spell_id` = '79513';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(79513, 'spell_tiki_torch');

-- Jintha'Alor Tiki Mask Fire Bunny
SET @ENTRY := 42704;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,15000,15000,15000,15000,28,42726,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Remove Fire");

UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=42857;

-- Sacrificed Vilebranch
SET @ENTRY := 42857;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,56,58228,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Item"),
(@ENTRY,@SOURCETYPE,2,0,64,0,100,0,0,0,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Die");

UPDATE `creature_template` SET `mindmg`=32, `maxdmg`=64, `attackpower`=13 WHERE `entry`=42815;

-- Ongo'longo
SET @ENTRY := 42815;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,79875,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Ongolongo Smash!"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,5000,5000,5000,5000,11,90325,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Slam"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Invincible"),
(@ENTRY,@SOURCETYPE,3,0,2,0,100,0,1,10,0,0,11,63227,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Hp Low - Cast Enrage"),
(@ENTRY,@SOURCETYPE,4,0,8,0,100,0,63227,1,0,0,33,42815,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit"),
(@ENTRY,@SOURCETYPE,5,0,8,0,100,0,63227,1,0,0,2,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Set Faction Friendly"),
(@ENTRY,@SOURCETYPE,6,0,8,0,100,0,63227,1,0,0,18,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Set Immune To All"),
(@ENTRY,@SOURCETYPE,7,0,1,0,100,0,15000,15000,15000,15000,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Reset Faction"),
(@ENTRY,@SOURCETYPE,8,0,1,0,100,0,15000,15000,15000,15000,19,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Reset Flags");

-- Ongolongo's Right Shackle
SET @ENTRY := 42816;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,5000,5000,5000,5000,11,79807,0,0,0,0,0,10,169170,42815,0,0.0,0.0,0.0,0.0,"Update - Cast Chains");

-- Ongolongo's Left Shackle
SET @ENTRY := 42817;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,5000,5000,5000,5000,11,79807,0,0,0,0,0,10,169170,42815,0,0.0,0.0,0.0,0.0,"Update - Cast Chains");

UPDATE `creature_template` SET `mindmg`=39, `maxdmg`=60, `attackpower`=15, `dmg_multiplier`=1.1 WHERE `entry`=42877;

-- Morta'gya the Keeper
SET @ENTRY := 42877;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,18266,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Curse of Agony"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,4000,4000,11,9613,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadow Bolt"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,11000,11000,11000,11000,11,18266,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Curse of Agony");

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=763471;
UPDATE `creature_template` SET `npcflag`=1 WHERE `entry`=42689;

-- Skittering Spiderling
SET @ENTRY := 42689;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,64,0,100,0,0,0,0,0,85,79588,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Invoker Collect Skitter"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,85,79591,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit"),
(@ENTRY,@SOURCETYPE,3,0,64,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Force Despawn");

UPDATE `creature_template` SET `mindmg`=41, `maxdmg`=61, `attackpower`=15, `type_flags`=0 WHERE `entry`=42592;
DELETE FROM `creature` WHERE `id` = '2640';

SET @CGUID := 400600;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+11;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 2640, 0, 1, 1, 28256, 0, -313.384, -4229.1, 136.937, 0.976212, 300, 3, 0, 888, 935, 1, 0, 0, 0),
(@CGUID+1, 2640, 0, 1, 1, 28256, 0, -317.626, -3406.5, 165.412, 4.47026, 300, 3, 0, 888, 935, 1, 0, 0, 0),
(@CGUID+2, 2640, 0, 1, 1, 28256, 0, -287.69, -4079.92, 152.689, 5.59015, 300, 3, 0, 888, 935, 1, 0, 0, 0),
(@CGUID+3, 2640, 0, 1, 1, 28256, 0, -336.407, -4213.17, 152.19, 0.173277, 300, 3, 0, 888, 935, 1, 0, 0, 0),
(@CGUID+4, 2640, 0, 1, 1, 6543, 0, -339.897, -4104.31, 152.645, 1.82956, 300, 3, 0, 888, 935, 1, 0, 0, 0),
(@CGUID+5, 2640, 0, 1, 1, 28256, 0, -296.856, -4167.88, 136.447, 0.383164, 300, 3, 0, 888, 935, 1, 0, 0, 0),
(@CGUID+6, 2640, 0, 1, 1, 28256, 0, -293.992, -4112.27, 137.35, 4.80429, 300, 3, 0, 888, 935, 1, 0, 0, 0),
(@CGUID+7, 2640, 0, 1, 1, 6543, 0, -293.451, -4109.87, 137.85, 1.11553, 300, 3, 0, 888, 935, 1, 0, 0, 0),
(@CGUID+8, 2640, 0, 1, 1, 28256, 0, -297.925, -4169.24, 136.447, 4.46002, 300, 3, 0, 888, 935, 1, 0, 0, 0),
(@CGUID+9, 2640, 0, 1, 1, 6543, 0, -313.818, -4227.72, 137.062, 1.6032, 300, 3, 0, 888, 935, 1, 0, 0, 0),
(@CGUID+10, 2640, 0, 1, 1, 6543, 0, -335.181, -4100.95, 153.02, 3.71361, 300, 3, 0, 888, 935, 1, 0, 0, 0),
(@CGUID+11, 2640, 0, 1, 1, 28256, 0, -288.209, -4079.85, 152.689, 3.79384, 300, 3, 0, 888, 935, 1, 0, 0, 0);

UPDATE `creature_template` SET `InhabitType`=3 WHERE `entry`=2505;

DELETE FROM `creature_loot_template` WHERE `item` = '58867';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(2505, 58867, -26.3324, 1, 0, 1, 1);

UPDATE `creature_template` SET `minlevel`=34, `maxlevel`=34, `faction_A`=1801, `faction_H`=1801, `mindmg`=44, `maxdmg`=65, `attackpower`=16, `InhabitType`=3 WHERE `entry`=43541;
UPDATE `creature_template` SET `mindmg`=34, `maxdmg`=45, `attackpower`=21, `Health_mod`=3 WHERE `entry`=46478;
UPDATE `creature` SET `spawntimesecs`=60 WHERE `id`=46478;

-- Highvale Sentry
SET @ENTRY := 46478;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,10000,18500,10000,18500,12,43541,4,20000,0,1,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Summon Invader");

DELETE FROM `gameobject` WHERE `guid` IN (400071, 400070, 400072);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(400071, 144072, 0, 1, 1, 219.774, -2717.08, 122.885, 1.78256, 0, 0, 0.777878, 0.628416, 60, 0, 1),
(400070, 144071, 0, 1, 1, 264.475, -2807, 124.298, 5.31799, 0, 0, 0.464083, -0.885792, 60, 0, 1),
(400072, 144073, 0, 1, 1, 284.813, -2674.61, 119.949, 3.40791, 0, 0, 0.991148, -0.132763, 60, 0, 1);

UPDATE `gameobject_template` SET `flags`=0, `castBarCaption`='Collecting', `questItem1`=61972, `faction`=35, `type`=3, `data0`=43, `data1`=144071, `data3`=1, `data4`=0, `data5`=0, `data11`=0 WHERE `entry`=144071;
UPDATE `gameobject_template` SET `flags`=0, `castBarCaption`='Collecting', `questItem1`=61973, `faction`=35, `type`=3, `data0`=43, `data1`=144072, `data3`=1, `data4`=0, `data5`=0, `data11`=0 WHERE `entry`=144072;
UPDATE `gameobject_template` SET `flags`=0, `castBarCaption`='Collecting', `questItem1`=61974, `faction`=35, `type`=3, `data0`=43, `data1`=144073, `data3`=1, `data4`=0, `data5`=0, `data11`=0 WHERE `entry`=144073;

DELETE FROM `gameobject_loot_template` WHERE `entry` IN (144071, 144072, 144073);
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES
(144071, 61972, -100),
(144072, 61973, -100),
(144073, 61974, -100);

DELETE FROM `spell_script_names` WHERE `spell_id` = '80469';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(80469, 'spell_ritual_of_shadra');

-- Shadra
SET @ENTRY := 43007;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,28991,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Web"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,15500,15500,15500,15500,11,28991,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Web"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,4500,4500,4500,4500,11,7992,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Slowing Poison"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,1500,1500,5000,5000,11,7992,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Poison"),
(@ENTRY,@SOURCETYPE,4,0,6,0,100,0,0,0,0,0,33,43007,0,0,0,0,0,18,300,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Credit"),
(@ENTRY,@SOURCETYPE,5,0,6,0,100,0,0,0,0,0,11,80474,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Cast Chop"),
(@ENTRY,@SOURCETYPE,6,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-318.1,-2894.91,78.29,6.05,"On Just Summoned - Move To Pos");

-- Wildhammer Spirithunter
SET @ENTRY := 43213;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,5000,5000,5000,5000,49,1,0,0,0,0,0,11,43007,500,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Shadra");

-- Gyphon Master Talonaxe
SET @ENTRY := 43215;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,5000,5000,5000,5000,49,1,0,0,0,0,0,11,43007,500,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Shadra");

-- Deathstalker Bodychopper
SET @ENTRY := 43016;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,5000,5000,5000,5000,49,1,0,0,0,0,0,11,43007,500,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Shadra");

UPDATE `creature_template` SET `mindmg`=38, `maxdmg`=56, `attackpower`=14, `dmg_multiplier`=3, `baseattacktime`=2000, `rangeattacktime`=2000, `minlevel`=35, `maxlevel`=35 WHERE `entry` IN (43016, 43213, 43215);
UPDATE `creature_template` SET `ScriptName`='npc_wildhammer_lookout' WHERE `entry`=43298;
UPDATE `creature_template` SET `ScriptName`='npc_deathstalker_lookout' WHERE `entry`=43299;
UPDATE `creature_template` SET `mindmg`=45, `maxdmg`=68, `attackpower`=37, `dmg_multiplier`=8, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=43007;
UPDATE `creature_template` SET `mindmg`=44, `maxdmg`=65, `attackpower`=16 WHERE `entry` IN (42913, 42555, 42609, 42724, 42901, 42919, 43891, 42879, 42518, 42610, 42536);

-- Shadraspawn Venomspitter
SET @ENTRY := 42913;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,10000,10000,11,6917,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Venom");

-- Revantusk Hexxer
SET @ENTRY := 42555;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,18267,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Curse of Weakness"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,7000,7000,11,16568,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Mind Flay"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,3000,3000,8500,8500,11,9613,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadow Bolt");

-- Gan'dranda
SET @ENTRY := 42609;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,13730,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Demoralizing Shout"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,4000,4000,11,57846,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Heroic Strike"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,2500,2500,5500,5500,11,32736,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Mortal Strike");

-- Umboda Three-Heads
SET @ENTRY := 42724;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,8599,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Enrage"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,4000,4000,11,85280,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Two-fisted Skull Bash"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,2000,2000,6000,6000,11,85279,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Two-fisted Skull Bash");

-- Vilebranch Broodguard
SET @ENTRY := 42901;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,32064,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Battleshout"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,22120,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Charge");

-- Qiaga the Keeper
SET @ENTRY := 42919;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,32063,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Corruption"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,4000,4000,11,9613,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadow Bolt");

-- Vilebranch Zealot
SET @ENTRY := 43891;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,2000,12000,12000,11,84535,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Zealotry");

-- Spawn of Shadra
SET @ENTRY := 42879;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,16000,16000,11,85278,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadra's Venom");

-- Wildhammer Warrior
SET @ENTRY := 42518;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,38232,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Battle Shout"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1500,1500,4000,4000,11,57846,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Heroic Strike");

-- Thornar Thunderclash
SET @ENTRY := 42610;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5000,5000,15000,20000,11,79878,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Bloodthirst"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,81140,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Thunderclap"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,2000,2000,4500,4500,11,79878,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Cleave");

UPDATE `creature_template` SET `lootid`=42609 WHERE `entry`=42609;
UPDATE `creature_template` SET `lootid`=42919 WHERE `entry`=42919;
UPDATE `creature_template` SET `lootid`=43891 WHERE `entry`=43891;

DELETE FROM `creature_loot_template` WHERE `entry` = '42609';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(42609, 1708, 4.5, 1, 0, 1, 1),
(42609, 1710, 4.1374, 1, 0, 1, 1),
(42609, 1725, 0.2, 1, 0, 1, 1),
(42609, 2592, 7.4, 1, 0, 1, 3),
(42609, 3041, 0.0701, 1, 0, 1, 1),
(42609, 3185, 0.0351, 1, 0, 1, 1),
(42609, 3385, 1.6129, 1, 0, 1, 1),
(42609, 3771, 10.3086, 1, 0, 1, 1),
(42609, 3778, 0.3, 1, 0, 1, 1),
(42609, 3779, 0.4909, 1, 0, 1, 1),
(42609, 3780, 0.5961, 1, 0, 1, 1),
(42609, 3781, 0.3042, 1, 0, 1, 1),
(42609, 3782, 0.7714, 1, 0, 1, 1),
(42609, 3783, 0.4208, 1, 0, 1, 1),
(42609, 3784, 0.1, 1, 0, 1, 1),
(42609, 3785, 0.4558, 1, 0, 1, 1),
(42609, 3786, 0.7714, 1, 0, 1, 1),
(42609, 3787, 0.4208, 1, 0, 1, 1),
(42609, 3792, 0.3156, 1, 0, 1, 1),
(42609, 3793, 0.2281, 1, 0, 1, 1),
(42609, 3794, 0.2104, 1, 0, 1, 1),
(42609, 3795, 1.122, 1, 0, 1, 1),
(42609, 3797, 0.2454, 1, 0, 1, 1),
(42609, 3798, 2.2814, 1, 0, 1, 1),
(42609, 3800, 0.1521, 1, 0, 1, 1),
(42609, 3802, 0.1, 1, 0, 1, 1),
(42609, 3803, 0.5961, 1, 0, 1, 1),
(42609, 3804, 0.1753, 1, 0, 1, 1),
(42609, 3805, 0.1753, 1, 0, 1, 1),
(42609, 3806, 0.1753, 1, 0, 1, 1),
(42609, 3807, 0.1753, 1, 0, 1, 1),
(42609, 3809, 0.1521, 1, 0, 1, 1),
(42609, 3810, 0.3857, 1, 0, 1, 1),
(42609, 3811, 0.1753, 1, 0, 1, 1),
(42609, 3813, 1.5209, 1, 0, 1, 1),
(42609, 3814, 0.1, 1, 0, 1, 1),
(42609, 3815, 0.1403, 1, 0, 1, 1),
(42609, 3816, 0.2805, 1, 0, 1, 1),
(42609, 3817, 0.3156, 1, 0, 1, 1),
(42609, 4035, 0.0351, 1, 0, 1, 1),
(42609, 4039, 0.0351, 1, 0, 1, 1),
(42609, 4048, 0.1052, 1, 0, 1, 1),
(42609, 4050, 0.0351, 1, 0, 1, 1),
(42609, 4052, 0.0701, 1, 0, 1, 1),
(42609, 4071, 0.1052, 1, 0, 1, 1),
(42609, 4306, 66.7251, 1, 0, 1, 1),
(42609, 4338, 1.3, 1, 0, 1, 1),
(42609, 4716, 0.0351, 1, 0, 1, 1),
(42609, 4719, 0.1753, 1, 0, 1, 1),
(42609, 4722, 0.0701, 1, 0, 1, 1),
(42609, 5774, 0.0701, 1, 0, 1, 1),
(42609, 6211, 0.0351, 1, 0, 1, 1),
(42609, 6396, 0.1753, 1, 0, 1, 1),
(42609, 6404, 0.0351, 1, 0, 1, 1),
(42609, 6409, 0.0351, 1, 0, 1, 1),
(42609, 6410, 0.0351, 1, 0, 1, 1),
(42609, 6609, 0.0351, 1, 0, 1, 1),
(42609, 6616, 0.0701, 1, 0, 1, 1),
(42609, 7110, 0.0351, 1, 0, 1, 1),
(42609, 7355, 0.2454, 1, 0, 1, 1),
(42609, 7357, 0.0351, 1, 0, 1, 1),
(42609, 7363, 0.0351, 1, 0, 1, 1),
(42609, 7366, 0.1521, 1, 0, 1, 1),
(42609, 7368, 0.0351, 1, 0, 1, 1),
(42609, 7370, 0.0351, 1, 0, 1, 1),
(42609, 7406, 0.4558, 1, 0, 1, 1),
(42609, 7408, 0.0351, 1, 0, 1, 1),
(42609, 7411, 0.0351, 1, 0, 1, 1),
(42609, 7416, 0.0351, 1, 0, 1, 1),
(42609, 7422, 0.0351, 1, 0, 1, 1),
(42609, 7449, 0.0351, 1, 0, 1, 1),
(42609, 7460, 0.0351, 1, 0, 1, 1),
(42609, 8704, 1.1921, 1, 0, 1, 1),
(42609, 8747, 0.3857, 1, 0, 1, 1),
(42609, 8748, 0.1753, 1, 0, 1, 1),
(42609, 9825, 0.0701, 1, 0, 1, 1),
(42609, 9828, 0.0351, 1, 0, 1, 1),
(42609, 9832, 0.0701, 1, 0, 1, 1),
(42609, 9834, 0.0701, 1, 0, 1, 1),
(42609, 9839, 0.0351, 1, 0, 1, 1),
(42609, 9840, 0.0351, 1, 0, 1, 1),
(42609, 9842, 0.0351, 1, 0, 1, 1),
(42609, 9857, 0.0351, 1, 0, 1, 1),
(42609, 9860, 0.0351, 1, 0, 1, 1),
(42609, 9867, 0.0701, 1, 0, 1, 1),
(42609, 10406, 0.1403, 1, 0, 1, 1),
(42609, 10408, 0.0701, 1, 0, 1, 1),
(42609, 11164, 0.1052, 1, 0, 1, 1),
(42609, 11996, 0.1403, 1, 0, 1, 1),
(42609, 12028, 0.1052, 1, 0, 1, 1),
(42609, 13037, 0.0701, 1, 0, 1, 1),
(42609, 13048, 0.0351, 1, 0, 1, 1),
(42609, 13079, 0.4909, 1, 0, 1, 1),
(42609, 15225, 0.0351, 1, 0, 1, 1),
(42609, 15231, 0.0701, 1, 0, 1, 1),
(42609, 15250, 0.1403, 1, 0, 1, 1),
(42609, 15285, 0.0351, 1, 0, 1, 1),
(42609, 15286, 0.0351, 1, 0, 1, 1),
(42609, 15934, 0.6311, 1, 0, 1, 1),
(42609, 15935, 0.0351, 1, 0, 1, 1),
(42609, 20974, 0.0351, 1, 0, 1, 1);

DELETE FROM `creature_loot_template` WHERE `entry` = '42919';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(42919, 934, 0.0111, 1, 0, 1, 1),
(42919, 1529, 0.1, 1, 0, 1, 1),
(42919, 1708, 2.3, 1, 0, 1, 1),
(42919, 2080, 0.0444, 1, 0, 1, 1),
(42919, 2592, 4.6, 1, 0, 1, 3),
(42919, 3037, 0.0222, 1, 0, 1, 1),
(42919, 3042, 0.0222, 1, 0, 1, 1),
(42919, 3185, 0.0333, 1, 0, 1, 1),
(42919, 3385, 0.5, 1, 0, 1, 1),
(42919, 3771, 5.8771, 1, 0, 1, 1),
(42919, 3778, 0.05, 1, 0, 1, 1),
(42919, 3779, 0.3281, 1, 0, 1, 1),
(42919, 3780, 0.3, 1, 0, 1, 1),
(42919, 3781, 0.1, 1, 0, 1, 1),
(42919, 3782, 0.1, 1, 0, 1, 1),
(42919, 3783, 0.3, 1, 0, 1, 1),
(42919, 3784, 0.2, 1, 0, 1, 1),
(42919, 3785, 3.2808, 1, 0, 1, 1),
(42919, 3786, 0.1, 1, 0, 1, 1),
(42919, 3787, 0.2, 1, 0, 1, 1),
(42919, 3792, 0.175, 1, 0, 1, 1),
(42919, 3793, 0.1, 1, 0, 1, 1),
(42919, 3794, 0.2, 1, 0, 1, 1),
(42919, 3795, 0.1, 1, 0, 1, 1),
(42919, 3796, 0.1, 1, 0, 1, 1),
(42919, 3798, 0.05, 1, 0, 1, 1),
(42919, 3799, 0.1, 1, 0, 1, 1),
(42919, 3800, 0.1444, 1, 0, 1, 1),
(42919, 3802, 0.1, 1, 0, 1, 1),
(42919, 3803, 0.05, 1, 0, 1, 1),
(42919, 3804, 0.1, 1, 0, 1, 1),
(42919, 3805, 0.1, 1, 0, 1, 1),
(42919, 3806, 0.1, 1, 0, 1, 1),
(42919, 3807, 0.05, 1, 0, 1, 1),
(42919, 3808, 0.1, 1, 0, 1, 1),
(42919, 3810, 0.1, 1, 0, 1, 1),
(42919, 3811, 0.1312, 1, 0, 1, 1),
(42919, 3812, 0.1778, 1, 0, 1, 1),
(42919, 3813, 0.05, 1, 0, 1, 1),
(42919, 3814, 0.1, 1, 0, 1, 1),
(42919, 3815, 0.1222, 1, 0, 1, 1),
(42919, 3816, 0.2406, 1, 0, 1, 1),
(42919, 3817, 0.2, 1, 0, 1, 1),
(42919, 3870, 0.0111, 1, 0, 1, 1),
(42919, 4040, 0.0444, 1, 0, 1, 1),
(42919, 4054, 0.0333, 1, 0, 1, 1),
(42919, 4055, 0.0222, 1, 0, 1, 1),
(42919, 4057, 0.0111, 1, 0, 1, 1),
(42919, 4059, 0.0111, 1, 0, 1, 1),
(42919, 4074, 0.0111, 1, 0, 1, 1),
(42919, 4075, 0.0222, 1, 0, 1, 1),
(42919, 4299, 0.0111, 1, 0, 1, 1),
(42919, 4306, 28.8, 1, 0, 1, 2),
(42919, 4352, 0.0222, 1, 0, 1, 1),
(42919, 4634, 0.175, 1, 0, 1, 1),
(42919, 4720, 0.0111, 1, 0, 1, 1),
(42919, 4726, 0.0111, 1, 0, 1, 1),
(42919, 6405, 0.0222, 1, 0, 1, 1),
(42919, 6406, 0.0222, 1, 0, 1, 1),
(42919, 6407, 0.0222, 1, 0, 1, 1),
(42919, 6408, 0.2444, 1, 0, 1, 1),
(42919, 6409, 0.0555, 1, 0, 1, 1),
(42919, 6410, 0.0111, 1, 0, 1, 1),
(42919, 6417, 0.0333, 1, 0, 1, 1),
(42919, 7357, 0.0333, 1, 0, 1, 1),
(42919, 7360, 0.0222, 1, 0, 1, 1),
(42919, 7367, 0.0111, 1, 0, 1, 1),
(42919, 7407, 0.0111, 1, 0, 1, 1),
(42919, 7408, 0.0222, 1, 0, 1, 1),
(42919, 7409, 0.0111, 1, 0, 1, 1),
(42919, 7413, 0.0111, 1, 0, 1, 1),
(42919, 7414, 0.0333, 1, 0, 1, 1),
(42919, 7417, 0.0111, 1, 0, 1, 1),
(42919, 7418, 0.0222, 1, 0, 1, 1),
(42919, 7421, 0.0222, 1, 0, 1, 1),
(42919, 7424, 0.0111, 1, 0, 1, 1),
(42919, 7448, 0.0111, 1, 0, 1, 1),
(42919, 7450, 0.0111, 1, 0, 1, 1),
(42919, 7458, 0.0222, 1, 0, 1, 1),
(42919, 7460, 0.0222, 1, 0, 1, 1),
(42919, 8704, 0.2777, 1, 0, 1, 1),
(42919, 8746, 0.1969, 1, 0, 1, 1),
(42919, 8747, 0.1, 1, 0, 1, 1),
(42919, 8748, 0.05, 1, 0, 1, 1),
(42919, 9819, 0.0222, 1, 0, 1, 1),
(42919, 9825, 0.0333, 1, 0, 1, 1),
(42919, 9830, 0.0111, 1, 0, 1, 1),
(42919, 9833, 0.0444, 1, 0, 1, 1),
(42919, 9835, 0.0111, 1, 0, 1, 1),
(42919, 9836, 0.0111, 1, 0, 1, 1),
(42919, 9847, 0.0111, 1, 0, 1, 1),
(42919, 9848, 0.0222, 1, 0, 1, 1),
(42919, 9849, 0.0333, 1, 0, 1, 1),
(42919, 9853, 0.0222, 1, 0, 1, 1),
(42919, 9857, 0.0111, 1, 0, 1, 1),
(42919, 9860, 0.0111, 1, 0, 1, 1),
(42919, 9861, 0.0111, 1, 0, 1, 1),
(42919, 9865, 0.0333, 1, 0, 1, 1),
(42919, 9872, 0.0111, 1, 0, 1, 1),
(42919, 10601, 0.0111, 1, 0, 1, 1),
(42919, 11970, 0.0222, 1, 0, 1, 1),
(42919, 12020, 0.0111, 1, 0, 1, 1),
(42919, 13019, 0.0111, 1, 0, 1, 1),
(42919, 13108, 0.0333, 1, 0, 1, 1),
(42919, 15225, 0.0444, 1, 0, 1, 1),
(42919, 15232, 0.0889, 1, 0, 1, 1),
(42919, 15286, 0.0444, 1, 0, 1, 1),
(42919, 15935, 0.0333, 1, 0, 1, 1),
(42919, 58779, -100, 1, 0, 1, 1);

DELETE FROM `creature_loot_template` WHERE `entry` = '43891';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(43891, 863, 0.0259, 1, 0, 1, 1),
(43891, 1529, 0.1, 1, 0, 1, 1),
(43891, 1708, 5.8275, 1, 0, 1, 1),
(43891, 1710, 15.3846, 1, 0, 1, 1),
(43891, 1725, 0.2, 1, 0, 1, 1),
(43891, 2080, 0.1036, 1, 0, 1, 1),
(43891, 2299, 0.0086, 1, 0, 1, 1),
(43891, 2592, 9.2, 1, 0, 1, 3),
(43891, 2721, 0.0086, 1, 0, 1, 1),
(43891, 2877, 0.0086, 1, 0, 1, 1),
(43891, 3037, 0.1295, 1, 0, 1, 1),
(43891, 3042, 0.0345, 1, 0, 1, 1),
(43891, 3185, 0.1554, 1, 0, 1, 1),
(43891, 3385, 1.4763, 1, 0, 1, 1),
(43891, 3396, 0.0086, 1, 0, 1, 1),
(43891, 3611, 0.0086, 1, 0, 1, 1),
(43891, 3771, 10.8262, 1, 0, 1, 1),
(43891, 3778, 0.1, 1, 0, 1, 1),
(43891, 3779, 0.4748, 1, 0, 1, 1),
(43891, 3780, 0.4144, 1, 0, 1, 1),
(43891, 3781, 0.4144, 1, 0, 1, 1),
(43891, 3782, 0.2, 1, 0, 1, 1),
(43891, 3783, 0.2849, 1, 0, 1, 1),
(43891, 3784, 0.3885, 1, 0, 1, 1),
(43891, 3785, 0.3281, 1, 0, 1, 1),
(43891, 3786, 0.3453, 1, 0, 1, 1),
(43891, 3787, 0.3194, 1, 0, 1, 1),
(43891, 3792, 0.2849, 1, 0, 1, 1),
(43891, 3793, 0.2, 1, 0, 1, 1),
(43891, 3794, 0.19, 1, 0, 1, 1),
(43891, 3795, 0.2, 1, 0, 1, 1),
(43891, 3796, 0.2504, 1, 0, 1, 1),
(43891, 3798, 0.1899, 1, 0, 1, 1),
(43891, 3799, 0.1986, 1, 0, 1, 1),
(43891, 3800, 0.4748, 1, 0, 1, 1),
(43891, 3801, 0.2417, 1, 0, 1, 1),
(43891, 3802, 0.1689, 1, 0, 1, 1),
(43891, 3803, 0.05, 1, 0, 1, 1),
(43891, 3804, 0.1813, 1, 0, 1, 1),
(43891, 3805, 0.2, 1, 0, 1, 1),
(43891, 3806, 0.1, 1, 0, 1, 1),
(43891, 3807, 0.1, 1, 0, 1, 1),
(43891, 3808, 0.1267, 1, 0, 1, 1),
(43891, 3809, 0.1813, 1, 0, 1, 1),
(43891, 3810, 0.1813, 1, 0, 1, 1),
(43891, 3811, 0.1899, 1, 0, 1, 1),
(43891, 3812, 0.1, 1, 0, 1, 1),
(43891, 3813, 0.1554, 1, 0, 1, 1),
(43891, 3814, 0.1468, 1, 0, 1, 1),
(43891, 3815, 0.1295, 1, 0, 1, 1),
(43891, 3816, 0.19, 1, 0, 1, 1),
(43891, 3817, 0.1, 1, 0, 1, 1),
(43891, 3831, 0.0086, 1, 0, 1, 1),
(43891, 3872, 0.0086, 1, 0, 1, 1),
(43891, 4039, 0.0173, 1, 0, 1, 1),
(43891, 4040, 0.0518, 1, 0, 1, 1),
(43891, 4052, 0.0086, 1, 0, 1, 1),
(43891, 4054, 0.0518, 1, 0, 1, 1),
(43891, 4055, 0.0863, 1, 0, 1, 1),
(43891, 4057, 0.0345, 1, 0, 1, 1),
(43891, 4059, 0.0173, 1, 0, 1, 1),
(43891, 4065, 0.0086, 1, 0, 1, 1),
(43891, 4075, 0.0345, 1, 0, 1, 1),
(43891, 4076, 0.0345, 1, 0, 1, 1),
(43891, 4077, 0.0086, 1, 0, 1, 1),
(43891, 4300, 0.0259, 1, 0, 1, 1),
(43891, 4306, 66.4681, 1, 0, 1, 1),
(43891, 4338, 2.1, 1, 0, 1, 1),
(43891, 4634, 0.2158, 1, 0, 1, 1),
(43891, 4717, 0.0086, 1, 0, 1, 1),
(43891, 4718, 0.0259, 1, 0, 1, 1),
(43891, 4720, 0.095, 1, 0, 1, 1),
(43891, 4721, 0.0259, 1, 0, 1, 1),
(43891, 4726, 0.0173, 1, 0, 1, 1),
(43891, 4732, 0.0173, 1, 0, 1, 1),
(43891, 5009, 0.0086, 1, 0, 1, 1),
(43891, 5427, 30.7692, 1, 0, 1, 1),
(43891, 6045, 0.0086, 1, 0, 1, 1),
(43891, 6402, 0.0086, 1, 0, 1, 1),
(43891, 6403, 0.0432, 1, 0, 1, 1),
(43891, 6405, 0.0259, 1, 0, 1, 1),
(43891, 6406, 0.0086, 1, 0, 1, 1),
(43891, 6407, 0.0518, 1, 0, 1, 1),
(43891, 6408, 0.0604, 1, 0, 1, 1),
(43891, 6409, 0.0259, 1, 0, 1, 1),
(43891, 6410, 0.0173, 1, 0, 1, 1),
(43891, 6413, 0.0173, 1, 0, 1, 1),
(43891, 7086, 0.0086, 1, 0, 1, 1),
(43891, 7330, 0.0173, 1, 0, 1, 1),
(43891, 7354, 0.0173, 1, 0, 1, 1),
(43891, 7357, 0.1209, 1, 0, 1, 1),
(43891, 7367, 0.0518, 1, 0, 1, 1),
(43891, 7368, 0.0345, 1, 0, 1, 1),
(43891, 7369, 0.0432, 1, 0, 1, 1),
(43891, 7407, 0.0173, 1, 0, 1, 1),
(43891, 7409, 0.1381, 1, 0, 1, 1),
(43891, 7414, 0.0173, 1, 0, 1, 1),
(43891, 7417, 0.0345, 1, 0, 1, 1),
(43891, 7418, 0.0345, 1, 0, 1, 1),
(43891, 7420, 0.0518, 1, 0, 1, 1),
(43891, 7421, 0.0345, 1, 0, 1, 1),
(43891, 7423, 0.0259, 1, 0, 1, 1),
(43891, 7424, 0.0173, 1, 0, 1, 1),
(43891, 7436, 0.0259, 1, 0, 1, 1),
(43891, 7438, 0.0173, 1, 0, 1, 1),
(43891, 7443, 0.0086, 1, 0, 1, 1),
(43891, 7444, 0.0173, 1, 0, 1, 1),
(43891, 7446, 0.0086, 1, 0, 1, 1),
(43891, 7447, 0.0345, 1, 0, 1, 1),
(43891, 7448, 0.0432, 1, 0, 1, 1),
(43891, 7449, 0.0432, 1, 0, 1, 1),
(43891, 7450, 0.0345, 1, 0, 1, 1),
(43891, 7458, 0.0259, 1, 0, 1, 1),
(43891, 7460, 0.0259, 1, 0, 1, 1),
(43891, 7461, 0.0173, 1, 0, 1, 1),
(43891, 7465, 0.0086, 1, 0, 1, 1),
(43891, 7609, 0.0259, 1, 0, 1, 1),
(43891, 8704, 0.6302, 1, 0, 1, 1),
(43891, 8746, 0.1, 1, 0, 1, 1),
(43891, 8747, 0.1689, 1, 0, 1, 1),
(43891, 8748, 0.1727, 1, 0, 1, 1),
(43891, 9395, 0.0086, 1, 0, 1, 1),
(43891, 9405, 0.0173, 1, 0, 1, 1),
(43891, 9819, 0.0691, 1, 0, 1, 1),
(43891, 9825, 0.0173, 1, 0, 1, 1),
(43891, 9830, 0.0086, 1, 0, 1, 1),
(43891, 9833, 0.0086, 1, 0, 1, 1),
(43891, 9835, 0.0086, 1, 0, 1, 1),
(43891, 9836, 0.0086, 1, 0, 1, 1),
(43891, 9843, 0.0086, 1, 0, 1, 1),
(43891, 9845, 0.0173, 1, 0, 1, 1),
(43891, 9846, 0.0259, 1, 0, 1, 1),
(43891, 9847, 0.0345, 1, 0, 1, 1),
(43891, 9849, 0.095, 1, 0, 1, 1),
(43891, 9850, 0.0086, 1, 0, 1, 1),
(43891, 9851, 0.0173, 1, 0, 1, 1),
(43891, 9853, 0.1122, 1, 0, 1, 1),
(43891, 9855, 0.0086, 1, 0, 1, 1),
(43891, 9856, 0.0086, 1, 0, 1, 1),
(43891, 9857, 0.095, 1, 0, 1, 1),
(43891, 9859, 0.0086, 1, 0, 1, 1),
(43891, 9860, 0.0604, 1, 0, 1, 1),
(43891, 9861, 0.0086, 1, 0, 1, 1),
(43891, 9862, 0.0173, 1, 0, 1, 1),
(43891, 9863, 0.0173, 1, 0, 1, 1),
(43891, 9865, 0.0518, 1, 0, 1, 1),
(43891, 9867, 0.0432, 1, 0, 1, 1),
(43891, 9868, 0.0259, 1, 0, 1, 1),
(43891, 9869, 0.0259, 1, 0, 1, 1),
(43891, 9870, 0.0086, 1, 0, 1, 1),
(43891, 9872, 0.0173, 1, 0, 1, 1),
(43891, 10601, 0.0086, 1, 0, 1, 1),
(43891, 11970, 0.0259, 1, 0, 1, 1),
(43891, 11971, 0.0086, 1, 0, 1, 1),
(43891, 11996, 0.0086, 1, 0, 1, 1),
(43891, 12009, 0.0691, 1, 0, 1, 1),
(43891, 12020, 0.0086, 1, 0, 1, 1),
(43891, 12029, 0.0086, 1, 0, 1, 1),
(43891, 12039, 0.0173, 1, 0, 1, 1),
(43891, 13033, 0.0086, 1, 0, 1, 1),
(43891, 13045, 0.0086, 1, 0, 1, 1),
(43891, 13084, 0.0345, 1, 0, 1, 1),
(43891, 13087, 0.0086, 1, 0, 1, 1),
(43891, 13108, 0.0173, 1, 0, 1, 1),
(43891, 13124, 0.0086, 1, 0, 1, 1),
(43891, 15213, 0.0345, 1, 0, 1, 1),
(43891, 15225, 0.0777, 1, 0, 1, 1),
(43891, 15226, 0.0259, 1, 0, 1, 1),
(43891, 15232, 0.0345, 1, 0, 1, 1),
(43891, 15243, 0.095, 1, 0, 1, 1),
(43891, 15928, 0.0086, 1, 0, 1, 1),
(43891, 15934, 0.0345, 1, 0, 1, 1),
(43891, 16883, 53.8462, 1, 0, 1, 1),
(43891, 20974, 0.0173, 1, 0, 1, 1),
(43891, 63128, -0.0211, 1, 0, 1, 1);

UPDATE `creature_template` SET `flags_extra`=0, `Armor_mod`=4 WHERE `entry` IN (2926, 42536);
UPDATE `creature_template` SET `mindmg`=14, `maxdmg`=21 WHERE `entry` IN (42518, 42536);
UPDATE `creature` SET `spawntimesecs`=60 WHERE `id` IN (2926, 42536);

-- Revantusk Stalker
SET @ENTRY := 42536;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,79402,1,0,0,11,56646,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Enrage"),
(@ENTRY,@SOURCETYPE,1,2,8,0,100,0,79402,1,0,0,11,95966,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Recently Enraged"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,33,42597,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit");

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '11764';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(11764, 0, 5, 'Make this inn your home.', 8, 65536, 0, 0, 0, 0, ''),
(11764, 1, 1, 'Let me browse your goods.', 3, 128, 0, 0, 0, 0, '');