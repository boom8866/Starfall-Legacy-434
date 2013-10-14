UPDATE `creature_template` SET `minlevel`=16, `maxlevel`=16, `scale`=0.3, `InhabitType`=4, `faction_A`=2146, `faction_H`=2146, `mindmg`=45, `maxdmg`=90, `lootid`=33041 WHERE `entry`=33042;

-- Weakened Aetherion
SET @ENTRY := 33042;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,18,600,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Start "),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,2000,4500,12000,20000,11,75079,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Update IC Cast Air");

-- Aetherion
SET @ENTRY := 33041;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,4500,12000,20000,11,75079,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Blast of Air"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,1,0,1,0,0,12,33042,8,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Summon Weakened Aetherion"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,1,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Force Despawn 1.5 secs");

-- Aetherion Ritual Orb
SET @ENTRY := 194145;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,10,188223,33041,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Aetherion");

UPDATE `creature_template` SET `minlevel`=16, `maxlevel`=16, `faction_A`=2146, `faction_H`=2146, `mindmg`=45, `maxdmg`=90, `lootid`=33041 WHERE  `entry`=33042;