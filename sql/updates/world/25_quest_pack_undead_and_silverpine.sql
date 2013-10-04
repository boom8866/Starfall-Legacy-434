DELETE FROM creature WHERE id = '13158';
DELETE FROM `creature_template_addon` WHERE `entry` = '39038';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES (39038, '73304');
UPDATE `creature_template` SET `flags_extra`=2 WHERE  `entry`=39086;

-- Lieutenant Sanders' Noose
SET @ENTRY := 38936;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,1000,1000,1000,1000,11,73444,0,0,0,0,0,19,39093,100,0,0.0,0.0,0.0,0.0,"cast 73444 on 39093");

DELETE FROM `vehicle_template_accessory` WHERE entry=38936 AND accessory_entry=13158;
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `description`) VALUES ('38936', '13158', 'Lieutenant sanders');
DELETE FROM `npc_spellclick_spells` WHERE npc_entry=38936 AND spell_id=46598;
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES ('38936', '46598', '0');
UPDATE `creature_template` SET `InhabitType` = 4 WHERE `entry` = 38936;
UPDATE creature SET MovementType=0,spawndist=0 WHERE id=39086;
UPDATE creature SET MovementType=0,spawndist=0 WHERE id=39087;
UPDATE `quest_template` SET `SourceSpellId` = 73306 WHERE `Id` = 25046;

-- Scarlet Friar
SET @ENTRY := 1538;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,30,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,7000,8000,28000,11,12169,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Shield Block"),
(@ENTRY,@SOURCETYPE,2,0,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Flee at 15% HP"),
(@ENTRY,@SOURCETYPE,3,0,2,0,100,1,0,15,0,0,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text at 15% HP"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,6000,9000,17000,20000,11,75967,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Whirlwind"),
(@ENTRY,@SOURCETYPE,5,0,8,0,100,0,73309,0,0,0,11,64431,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"on spellhit 73309 cast 64431");

-- Scarlet Neophyte
SET @ENTRY := 1539;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,4,1,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving on Aggro"),
(@ENTRY,@SOURCETYPE,2,0,4,1,100,1,0,0,0,0,11,13322,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast bolt on Aggro"),
(@ENTRY,@SOURCETYPE,3,0,9,1,100,0,0,40,3400,4700,11,13322,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast bolt"),
(@ENTRY,@SOURCETYPE,4,0,9,1,100,0,40,100,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving when not in bolt Range"),
(@ENTRY,@SOURCETYPE,5,0,9,1,100,0,10,15,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving at 15 Yards"),
(@ENTRY,@SOURCETYPE,6,0,9,1,100,0,0,40,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving when in bolt Range"),
(@ENTRY,@SOURCETYPE,7,0,3,1,100,0,0,15,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 2 at 15% Mana"),
(@ENTRY,@SOURCETYPE,8,0,3,2,100,0,0,15,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving at 15% Mana"),
(@ENTRY,@SOURCETYPE,9,0,3,2,100,0,30,100,100,100,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 When Mana is above 30%"),
(@ENTRY,@SOURCETYPE,10,0,2,2,100,1,0,15,0,0,22,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 3 at 15% HP"),
(@ENTRY,@SOURCETYPE,11,0,2,3,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Flee at 15% HP"),
(@ENTRY,@SOURCETYPE,12,0,7,3,100,1,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Reset on Evade"),
(@ENTRY,@SOURCETYPE,13,0,2,3,100,1,0,15,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text at 15% HP"),
(@ENTRY,@SOURCETYPE,14,0,4,0,30,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text on Aggro"),
(@ENTRY,@SOURCETYPE,15,0,1,0,100,0,500,1000,1800000,1800000,11,12544,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Frost Armor on Spawn"),
(@ENTRY,@SOURCETYPE,16,0,8,0,100,0,73309,0,0,0,11,64431,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Type a script description here.");

-- Scarlet Vanguard
SET @ENTRY := 1540;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,30,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,1,0,0,0,0,11,7164,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Defensive Stance on Aggro"),
(@ENTRY,@SOURCETYPE,2,0,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Flee at 15% HP"),
(@ENTRY,@SOURCETYPE,3,0,2,0,100,1,0,15,0,0,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text at 15% HP"),
(@ENTRY,@SOURCETYPE,4,0,13,0,100,0,2000,4500,20000,30000,11,11972,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shield Bash on Player Spell Cast"),
(@ENTRY,@SOURCETYPE,5,0,8,0,100,0,73309,0,0,0,11,64431,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Type a script description here.");


UPDATE `creature_template` SET `VehicleId` = 665 WHERE `entry`= 1660;
DELETE FROM `creature` WHERE `guid`= 4731;

UPDATE `creature_template` SET `VehicleId` = 665 WHERE `entry`= 39097;
UPDATE `creature_template` SET `VehicleId` = 665, `AIName`= 'SmartAI' WHERE `entry`= 1665;

-- Lilian Voss
SET @ENTRY := 39038;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,4000,4000,2000,9000,87,3903800,3903801,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"on aggro do random action"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,1,2000,2000,2000,2000,11,73392,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"update ooc cast stealth"),
(@ENTRY,@SOURCETYPE,2,5,38,0,100,0,0,1,0,0,80,3903802,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"data set 1 do actiontime"),
(@ENTRY,@SOURCETYPE,3,0,25,0,100,0,0,0,0,0,29,0,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"follow owner"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,18,776,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"set unit flag");

-- Lilian Voss
SET @ENTRY := 3903800;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,3000,0,0,11,73309,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"cast 73309 on victime"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,3000,3000,0,0,51,0,0,0,0,0,0,9,0,0,15,0.0,0.0,0.0,0.0,"kill unit after 1 sec");

-- Lilian Voss
SET @ENTRY := 3903801;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,2000,0,0,11,46598,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"enter vehicle"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,0,0,0,0,51,0,0,0,0,0,0,9,0,0,5,0.0,0.0,0.0,0.0,"kill unit");

-- Hack!
DELETE FROM `creature_template` WHERE (`entry`=144952);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES (144952, 0, 0, 0, 0, 0, 16480, 16480, 16480, 16480, 'Invisible Trigger One', '', '', 0, 1, 1, 0, 35, 35, 0, 0.91, 1.14286, 1, 0, 1007, 1354.7, 0, 1571, 1, 2000, 2200, 1, 0, 2048, 8, 0, 0, 0, 0, 0, 758.1, 1062.1, 220, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 128, '', 12340);
-- Invisible Trigger One
SET @ENTRY := 144952;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,0,3000,3000,3000,3000,45,0,1,0,0,0,0,19,39038,5,0,0.0,0.0,0.0,0.0,"send data 1 to 39038");


-- Lilian Voss
SET @ENTRY := 3903802; -- the entry should equal the npc entry / npc guid
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,3073.76,-555.71,126.72,0.08,"Move Point"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk Start"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,1000,1000,1000,1000,2,35,0,0,0,0,0,9,1660,1,50,0.0,0.0,0.0,0.0,"Set faction 35 - To ID: 1660"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,1000,1000,1000,1000,2,35,0,0,0,0,0,9,1665,1,50,0.0,0.0,0.0,0.0,"Set faction 35 - To ID: 1665"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,1000,1000,1000,1000,2,35,0,0,0,0,0,9,39097,1,50,0.0,0.0,0.0,0.0,"Set faction 35 - To ID: 1665"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,0,0,0,0,45,0,1,0,0,0,0,9,39097,1,50,0.0,0.0,0.0,0.0,"Init Data 1 to Father"),
(@ENTRY,@SOURCETYPE,6,0,0,0,100,0,5000,5000,5000,5000,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 1"),
(@ENTRY,@SOURCETYPE,7,0,0,0,100,0,1000,1000,1000,1000,11,46598,0,0,0,0,0,9,1665,1,20,0.0,0.0,0.0,0.0,"Jump on Captain"),
(@ENTRY,@SOURCETYPE,8,0,0,0,100,0,500,500,0,0,51,0,0,0,0,0,0,9,1665,1,20,0.0,0.0,0.0,0.0,"Kill Captain"),
(@ENTRY,@SOURCETYPE,9,0,0,0,100,0,1000,1000,0,0,11,46598,0,0,0,0,0,9,1660,1,20,0.0,0.0,0.0,0.0,"Jump on Bodyguard"),
(@ENTRY,@SOURCETYPE,10,0,0,0,100,0,500,500,0,0,51,0,0,0,0,0,0,9,1660,1,20,0.0,0.0,0.0,0.0,"Kill Bodyguard"),
(@ENTRY,@SOURCETYPE,11,0,0,0,100,0,0,0,0,0,1,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 2"),
(@ENTRY,@SOURCETYPE,12,0,0,0,100,0,5000,5000,0,0,1,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 3"),
(@ENTRY,@SOURCETYPE,13,0,0,0,100,0,5000,5000,0,0,1,4,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 4"),
(@ENTRY,@SOURCETYPE,14,0,0,0,100,0,0,0,0,0,11,46598,0,0,0,0,0,9,39097,1,20,0.0,0.0,0.0,0.0,"Jump on Target - 39097"),
(@ENTRY,@SOURCETYPE,15,0,0,0,100,0,0,0,0,0,33,39098,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Quest Complete"),
(@ENTRY,@SOURCETYPE,16,0,0,0,100,0,1000,1000,1000,1000,51,0,0,0,0,0,0,9,39097,1,20,0.0,0.0,0.0,0.0,"Kill Father"),
(@ENTRY,@SOURCETYPE,17,0,0,0,100,0,10000,10000,0,0,41,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Despawn");

-- High Priest Benedictus Voss
SET @ENTRY := 3909700;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,1000,1000,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 0"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,9000,9000,9000,9000,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 1"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,10000,10000,10000,10000,1,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 2");

-- High Priest Benedictus Voss
SET @ENTRY := 39097;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,80,3909700,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"on data set 1 do action");

DELETE FROM creature_text WHERE entry=39038;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(39038, 0, 0, 'Father!', 12, 0, 100, 0, 0, 0, '?????? ????'),
(39038, 1, 0, 'Shut up.', 12, 0, 100, 0, 0, 0, '?????? ????'),
(39038, 2, 0, 'You raised me to be a killer. How am I doing, daddy?', 12, 0, 100, 0, 0, 0, '?????? ????'),
(39038, 3, 0, 'But wait... I remember now. You taught me to only kill the undead. So you do want me to kill myself, daddy?', 12, 0, 100, 0, 0, 0, '?????? ????'),
(39038, 4, 0, 'Then again, why kill myself... when I can kill YOU instead!', 12, 0, 100, 0, 0, 0, '?????? ????');

DELETE FROM creature_text WHERE entry=39097;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(39097, 0, 0, 'Lilian... you''re... it''s so nice to see you well.', 12, 0, 100, 0, 0, 0, '????????? ???? ???????? ???? to ?????? ????'),
(39097, 1, 0, 'I, ah...', 12, 0, 100, 0, 0, 0, '????????? ???? ???????? ???? to ?????? ????'),
(39097, 2, 0, 'Lilian, I...', 12, 0, 100, 0, 0, 0, '????????? ???? ???????? ???? to ?????? ????');

DELETE FROM `creature` WHERE `id`=144952;
INSERT INTO `creature` (`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES
(144952, 0, 1, 65535, 0, 0, 3038.11, -559.181, 121.427, 3.21225, 300, 0, 0, 42, 0, 0, 0, 33554432, 0);

SET @CGUID := 786687;
DELETE FROM `creature` WHERE `id` IN (1540, 1538);
INSERT INTO `creature` (`guid; `id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES
(@CGUID+0, 1540, 0, 1, 1, 2481, 0, 2791.81, -473.694, 101.753, 1.25664, 500, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+1, 1540, 0, 1, 1, 2481, 0, 2750.31, -521.581, 106.324, 2.35619, 500, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+2, 1540, 0, 1, 1, 2470, 0, 2769.89, -485.563, 107.248, 3.78736, 500, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+3, 1540, 0, 1, 1, 2470, 0, 2848.74, -511.46, 106.835, 5.12463, 500, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+4, 1540, 0, 1, 1, 2470, 0, 2943.75, -554.264, 109.317, 3.22052, 500, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+5, 1540, 0, 1, 1, 2481, 0, 2870.57, -497.285, 101.174, 5.39186, 500, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+6, 1540, 0, 1, 1, 2470, 0, 3101.32, -548.31, 126.898, 0.925025, 500, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+7, 1540, 0, 1, 1, 2470, 0, 2849.83, -475.367, 99.6665, 1.67552, 500, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+8, 1540, 0, 1, 1, 2481, 0, 2792.01, -487.446, 101.4, 5.79449, 500, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+9, 1540, 0, 1, 1, 2481, 0, 3006.29, -538.512, 116.235, 5.79449, 500, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+10, 1540, 0, 1, 1, 2481, 0, 2923.53, -562.806, 109.015, 1.67552, 500, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+11, 1540, 0, 1, 1, 2481, 0, 2848.48, -507.172, 107.063, 2.04204, 500, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+12, 1540, 0, 1, 1, 2481, 0, 2850, -531.182, 108.825, 5.79449, 500, 0, 0, 222, 0, 0, 0, 0, 0),
(@CGUID+13, 1540, 0, 1, 1, 2470, 0, 2957.23, -553.232, 110.077, 3.32014, 500, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+14, 1540, 0, 1, 1, 2481, 0, 2880.77, -525.427, 105.685, 4.2237, 500, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+15, 1540, 0, 1, 1, 2470, 0, 2990.25, -527.663, 111.274, 5.79449, 500, 0, 0, 222, 0, 0, 0, 0, 0),
(@CGUID+16, 1540, 0, 1, 1, 2470, 0, 2827.28, -496.497, 101.523, 1.67552, 500, 0, 0, 222, 0, 0, 0, 0, 0),
(@CGUID+17, 1540, 0, 1, 1, 2470, 0, 3019.89, -560.585, 118.777, 5.79449, 500, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+18, 1540, 0, 1, 1, 2470, 0, 2892.33, -533.336, 106.112, 3.90954, 500, 0, 0, 222, 0, 0, 0, 0, 0),
(@CGUID+19, 1540, 0, 1, 1, 2481, 0, 2761.21, -484.215, 104.69, 5.79449, 500, 0, 0, 222, 0, 0, 0, 0, 0),
(@CGUID+20, 1540, 0, 1, 1, 2470, 0, 2994.17, -558.007, 116.411, 1.67552, 500, 0, 0, 198, 0, 0, 0, 0, 0),
(@CGUID+21, 1540, 0, 1, 1, 2470, 0, 3119.52, -573.777, 128.942, 0.680678, 500, 0, 0, 222, 0, 0, 0, 0, 0);

INSERT INTO `creature` (`guid`, `id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES
(@CGUID+22, 1538, 0, 1, 1, 2466, 0, 2750.02, -531.186, 104.635, 2.79253, 120, 0, 0, 166, 178, 0, 0, 0, 0),
(@CGUID+23, 1538, 0, 1, 1, 2477, 0, 2149.27, -513.366, 81.8476, 2.1293, 120, 0, 0, 166, 178, 0, 0, 0, 0),
(@CGUID+24, 1538, 0, 1, 1, 2466, 0, 2143.29, -554.631, 81.5568, 5.79449, 120, 0, 0, 166, 178, 0, 0, 0, 0),
(@CGUID+25, 1538, 0, 1, 1, 2477, 0, 2165.17, -556.663, 79.3422, 5.44543, 120, 0, 0, 166, 178, 0, 0, 0, 0),
(@CGUID+26, 1538, 0, 1, 1, 2466, 0, 2896.56, -537.532, 106.566, 3.24631, 120, 0, 0, 166, 178, 0, 0, 0, 0),
(@CGUID+27, 1538, 0, 1, 1, 2466, 0, 2169.06, -520.564, 81.5963, 4.86947, 120, 0, 0, 166, 178, 0, 0, 0, 0),
(@CGUID+28, 1538, 0, 1, 1, 2477, 0, 2143.57, -529.984, 81.7805, 5.60251, 120, 0, 0, 166, 178, 0, 0, 0, 0),
(@CGUID+29, 1538, 0, 1, 1, 2477, 0, 2113.39, -405.729, 71.3364, 3.102, 120, 0, 0, 166, 178, 0, 0, 0, 0),
(@CGUID+30, 1538, 0, 1, 1, 2466, 0, 2142.8, -505.647, 81.7233, 1.98477, 120, 0, 0, 166, 178, 0, 0, 0, 0),
(@CGUID+31, 1538, 0, 1, 1, 2466, 0, 2184.19, -450.619, 75.4925, 2.49582, 120, 0, 0, 166, 178, 0, 0, 0, 0),
(@CGUID+32, 1538, 0, 1, 1, 2466, 0, 2123.34, -632.033, 93.5874, 5.07891, 120, 0, 0, 166, 178, 0, 0, 0, 0),
(@CGUID+33, 1538, 0, 1, 1, 2466, 0, 2177.13, -610.977, 80.7263, 5.22851, 120, 0, 0, 166, 178, 0, 0, 0, 0),
(@CGUID+34, 1538, 0, 1, 1, 2466, 0, 2112.78, -625.056, 93.5988, 3.4383, 120, 0, 0, 166, 178, 0, 0, 0, 0),
(@CGUID+35, 1538, 0, 1, 1, 2477, 0, 3097.16, -552.221, 126.705, 2.99377, 120, 0, 0, 166, 178, 0, 0, 0, 0),
(@CGUID+36, 1538, 0, 1, 1, 2466, 0, 2550.38, -905.022, 56.928, 0.959931, 120, 0, 0, 166, 178, 0, 0, 0, 0),
(@CGUID+37, 1538, 0, 1, 1, 2466, 0, 2484.22, -879.037, 60.3536, 0.033223, 120, 0, 0, 166, 178, 0, 0, 0, 0),
(@CGUID+38, 1538, 0, 1, 1, 2477, 0, 2237.77, -653.93, 78.261, 2.04207, 120, 0, 0, 166, 178, 0, 0, 0, 0),
(@CGUID+39, 1538, 0, 1, 1, 2477, 0, 2528.36, -904.647, 57.0912, 0.977384, 120, 0, 0, 166, 178, 0, 0, 0, 0),
(@CGUID+40, 1538, 0, 1, 1, 2466, 0, 2517.75, -898.981, 56.1185, 1.98968, 120, 0, 0, 166, 178, 0, 0, 0, 0),
(@CGUID+41, 1538, 0, 1, 1, 2477, 0, 2540.38, -886.911, 55.5066, 4.88814, 120, 0, 0, 166, 178, 0, 0, 0, 0),
(@CGUID+42, 1538, 0, 1, 1, 2477, 0, 2563.66, -895.477, 55.6279, 2.46091, 120, 0, 0, 166, 178, 0, 0, 0, 0),
(@CGUID+43, 1538, 0, 1, 1, 2477, 0, 2147.25, -641.061, 94.1245, 4.4855, 120, 0, 0, 186, 191, 0, 0, 0, 0),
(@CGUID+44, 1538, 0, 1, 1, 2477, 0, 2814.89, -511.951, 104.53, 0.872665, 120, 0, 0, 166, 178, 0, 0, 0, 0),
(@CGUID+45, 1538, 0, 1, 1, 2466, 0, 2956.95, -562.66, 110.595, 1.36136, 120, 0, 0, 166, 178, 0, 0, 0, 0),
(@CGUID+46, 1538, 0, 1, 1, 2477, 0, 2985.34, -533.891, 111.998, 5.3058, 120, 0, 0, 166, 178, 0, 0, 0, 0),
(@CGUID+47, 1538, 0, 1, 1, 2477, 0, 2924.75, -542.059, 108.463, 5.3058, 120, 0, 0, 186, 191, 0, 0, 0, 0),
(@CGUID+48, 1538, 0, 1, 1, 2477, 0, 3026.9, -563.031, 119.64, 2.89725, 120, 0, 0, 186, 191, 0, 0, 0, 0);
