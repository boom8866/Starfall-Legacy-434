UPDATE `creature_template` SET `mindmg`=750, `maxdmg`=951, `attackpower`=36, `dmg_multiplier`=14, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=50417;

-- Bound Flames
SET @ENTRY := 50417;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

-- Lava Pool
SET @ENTRY := 50423;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,18,33554432,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Unselectable"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,41,30000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Despawn");

UPDATE `creature_template` SET `unit_flags`=33554432, `faction_A`=16, `faction_H`=16 WHERE `entry`=50423;

DELETE FROM `spell_script_names` WHERE `spell_id` = '94340';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(94340, 'spell_brc_lava_pools_dynobject');

UPDATE `creature_template` SET `ScriptName`='npc_brc_bound_flames' WHERE `entry`=50417;