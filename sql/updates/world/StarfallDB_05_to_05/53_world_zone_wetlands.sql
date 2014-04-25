UPDATE `creature_template` SET `InhabitType`=3, `flags_extra`=0 WHERE `entry` IN (1111, 4040);
DELETE FROM `creature` WHERE `guid`=185828;
DELETE FROM `creature_addon` WHERE `guid`=185828;

UPDATE `creature_template` SET `mindmg`=19, `maxdmg`=28, `attackpower`=7, `dmg_multiplier`=1.4 WHERE `entry` IN (41272, 41273);
UPDATE `creature_template` SET `mindmg`=19, `maxdmg`=28, `attackpower`=7, `dmg_multiplier`=1.1 WHERE `entry` IN
(41343, 41425, 42110, 41426, 42111, 41343, 41342, 41496, 41419, 41390, 41388, 41389, 41409, 41401, 41400, 41416, 41424, 42154);

UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry`=40495;

-- Dark Iron Smouldermage
SET @ENTRY := 41272;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,79849,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Molten Armor"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,6000,6000,11,9053,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Fireball"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,4000,4000,4000,4000,11,82641,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Lava Gout");

-- Horghast Flarecrazed
SET @ENTRY := 41273;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,80576,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Shadowstep");

-- Captured Mosshide
SET @ENTRY := 41410;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Phase 1"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,41,8000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Force Despawn"),
(@ENTRY,@SOURCETYPE,2,0,60,1,100,0,2500,2500,2500,2500,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Set Run"),
(@ENTRY,@SOURCETYPE,3,0,60,1,100,0,2500,2500,2500,2500,46,50,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Move Forward"),
(@ENTRY,@SOURCETYPE,4,0,60,1,100,0,2500,2500,2500,2500,41,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Force Despawn"),
(@ENTRY,@SOURCETYPE,5,0,60,1,100,0,2500,2500,2500,2500,33,41438,0,0,0,0,0,18,6,0,0,0.0,0.0,0.0,0.0,"Update - Quest Credit");

-- Gnoll Cage
SET @ENTRY := 203282;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,19,41410,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Mosshide");

-- Yorla Darksnare
SET @ENTRY := 41416;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,80596,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Explosive Trap"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,4500,4500,11,82708,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Flaming Arrow"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,3500,3500,3500,3500,11,82708,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shoot");

DELETE FROM `spell_script_names` WHERE `spell_id` = '77571';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(77571, 'spell_blessed_floodlily');

UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=26128;
DELETE FROM `creature` WHERE `id` IN (41559, 41560, 41556, 41524, 41558, 41553, 41554, 41523, 41522);

DELETE FROM `areatrigger_scripts` WHERE `entry` = '5990';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(5990, 'at_thandol_span');

DELETE FROM `creature_text` WHERE `entry`=41560;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41560,0,0,'I don\'t care how many times I have to kill you... I\'ll take you all on to save this land!',12,0,100,0,0,0,'Comment'),
(41560,1,0,'FOR KHAZ MODAN!',14,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=41522;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41522,0,0,'Your petty triumphs have been futile. The power of the Twilight\'s Hammer is absolute!',12,0,100,0,0,0,'Comment'),
(41522,1,0,'Rejoice, for you shall be first to die. We will sweep across Khaz Modan and burn all to ash.',12,0,100,0,0,0,'Comment'),
(41522,2,0,'What luck! The offerings throw themselves upon the altar!',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=41523;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41523,0,0,'Aye, and so will we!',12,0,100,0,0,0,'Comment'),
(41523,1,0,'FOR KHAZ MODAN!',14,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `mindmg`=31, `maxdmg`=47, `attackpower`=12, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry` IN
(41524, 41522, 41553, 41556, 41560, 41559, 41558, 41523);

DELETE FROM `creature_text` WHERE `entry` IN (41559, 41558);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(41559,0,0,'FOR KHAZ MODAN!',14,0,100,0,0,0,'Comment'),
(41558,0,0,'FOR KHAZ MODAN!',14,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `minlevel`=25, `maxlevel`=25, `faction_A`=2245, `faction_H`=2245, `unit_class`=8 WHERE `entry`=41522;

-- Calamoth Ashbeard
SET @ENTRY := 41522;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,70509,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Blue Explosion"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,1,0,10000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,41522,0,0,1,1,10000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0  - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,41522,0,0,45,0,1,0,0,0,0,11,41560,100,0,0.0,0.0,0.0,0.0,"After Talk 1  - Set Data 1 to Anvilmar"),
(@ENTRY,@SOURCETYPE,4,0,54,0,100,0,0,0,0,0,75,74617,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Add Blue Flames"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,1,0,0,1,2,7000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,6,0,0,0,100,0,1000,1000,15500,15000,11,82723,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Twilight Blast"),
(@ENTRY,@SOURCETYPE,7,0,0,0,100,0,6500,6500,6500,6500,11,78129,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Twilight Bolt"),
(@ENTRY,@SOURCETYPE,8,0,6,0,100,0,0,0,0,0,33,41522,0,0,0,0,0,18,250,0,0,0.0,0.0,0.0,0.0,"On Death - Range Quest Credit"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,2,41522,0,0,45,0,10,0,0,0,0,11,0,500,0,0.0,0.0,0.0,0.0,"After Talk 2  - Set Data 10 to All Creatures"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,2,41522,0,0,19,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2  - Set Attackable"),
(@ENTRY,@SOURCETYPE,11,0,54,0,100,0,0,0,0,0,18,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Unattackable");

-- Yorla Darksnare
SET @ENTRY := 41524;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,70509,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Blue Explosion"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,5000,8500,11,82708,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Flaming Arrow"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,3000,3000,6000,15500,11,80596,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Explosive Trap"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,10,0,0,69,0,0,0,0,0,0,8,0,0,0,-2398.66,-2502.04,86.69,3.14,"On Get Data 10 - Move To Pos"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,10,0,0,19,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Remove Flag Unattackable");

-- Drungeld Glowerglare
SET @ENTRY := 41553;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,70509,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Blue Explosion"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,11,82635,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Flaming Leap"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,2000,2000,12500,12500,11,77670,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Fire Whirl"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,4000,4000,6500,8550,11,77670,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Blast Wave"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,10,0,0,69,0,0,0,0,0,0,8,0,0,0,-2398.66,-2502.04,86.69,3.14,"On Get Data 10 - Move To Pos"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,10,0,0,19,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Remove Flag Unattackable");

-- Balgaras the Foul
SET @ENTRY := 41556;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,70509,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Blue Explosion"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,4500,4500,11,16568,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Mind Flay"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,5000,5000,7500,7500,11,77721,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Shadow Weave"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,10,0,0,69,0,0,0,0,0,0,8,0,0,0,-2398.66,-2502.04,86.69,3.14,"On Get Data 10 - Move To Pos"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,10,0,0,19,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 10 - Remove Flag Unattackable");

-- Captain Stoutfist
SET @ENTRY := 41559;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,46,25,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move Forward"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,10,0,0,69,0,0,0,0,0,0,8,0,0,0,-2398.66,-2502.04,86.69,3.14,"On Get Data 10 - Move To Pos");

-- Shilah Slabchisel
SET @ENTRY := 41523;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,46,30,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move Forward"),
(@ENTRY,@SOURCETYPE,2,0,34,0,100,1,8,0,0,0,1,0,7000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,41523,0,0,45,0,1,0,0,0,0,11,41522,100,0,0.0,0.0,0.0,0.0,"After Talk 0 - Set Data 1 to Calamoth"),
(@ENTRY,@SOURCETYPE,4,0,4,0,100,0,0,0,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 1"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,10,0,0,69,0,0,0,0,0,0,8,0,0,0,-2398.66,-2502.04,86.69,3.14,"On Get Data 10 - Move To Pos");

-- Forba Slabchisel
SET @ENTRY := 41558;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,46,30,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move Forward"),
(@ENTRY,@SOURCETYPE,2,0,4,0,100,0,0,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,2000,2000,12500,15500,11,80117,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Earth Spike"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,2000,2000,12500,15500,11,82738,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Rock Shower"),
(@ENTRY,@SOURCETYPE,5,0,38,0,100,0,0,10,0,0,69,0,0,0,0,0,0,8,0,0,0,-2398.66,-2502.04,86.69,3.14,"On Get Data 10 - Move To Pos");

-- Thargas Anvilmar
SET @ENTRY := 41560;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-2427.43,-2504.34,81.19,0.03,"On Just Summoned - Move To Bridge"),
(@ENTRY,@SOURCETYPE,2,0,34,0,100,1,8,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Set Phase 1"),
(@ENTRY,@SOURCETYPE,3,0,38,1,100,0,0,1,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,4,1,100,0,0,0,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,5,0,52,1,100,0,0,41560,0,0,12,41559,4,60000,0,0,0,8,0,0,0,-2452.06,-2508.01,78.5,0.01,"After Talk 0 - Summon Stoutfist"),
(@ENTRY,@SOURCETYPE,6,0,52,1,100,0,0,41560,0,0,12,41558,4,60000,0,0,0,8,0,0,0,-2452.09,-2500.67,78.5,6.17,"After Talk 0 - Summon Forba"),
(@ENTRY,@SOURCETYPE,7,0,52,1,100,0,0,41560,0,0,12,41523,4,60000,0,0,0,8,0,0,0,-2451.99,-2496.94,78.5,6.25,"After Talk 0 - Summon Schilah"),
(@ENTRY,@SOURCETYPE,8,0,38,1,100,0,0,10,0,0,69,0,0,0,0,0,0,8,0,0,0,-2398.66,-2502.04,86.69,3.14,"On Get Data 10 - Move To Pos");

UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry` IN (41524, 41553, 41556, 41522);