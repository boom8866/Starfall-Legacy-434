-- TODO: Check correct vehicleid

UPDATE `creature_template` SET `InhabitType`=3 WHERE `entry`=33127;
UPDATE `creature_template` SET `VehicleId`=690, `npcflag`=1 `spell2`=63996, `spell1`=62246 WHERE `entry`=43742;
DELETE FROM `spell_script_names` WHERE `spell_id` = '63996';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(63996, 'spell_moonsurge');

-- Vengeful Protector
SET @ENTRY := 43742;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,12,43742,8,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Summon Self"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,86,46598,0,18,15,15,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Grab Player"),
(@ENTRY,@SOURCETYPE,2,0,28,0,100,0,0,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Despawn"),
(@ENTRY,@SOURCETYPE,3,0,27,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Set Passive");