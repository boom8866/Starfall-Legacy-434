DELETE FROM `creature` WHERE `guid` = '793978';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(793978, 38910, 0, 1, 1, 0, 0, 1857.74, 1556.2, 94.7914, 3.18656, 5, 0, 0, 98, 115, 0, 0, 0, 0);

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11133 AND `id`=0;

-- Lilian Voss
SET @ENTRY := 38910;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,11133,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,33,38910,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Complete Quest"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,11133,0,0,0,1,0,5000,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Talk"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,11133,0,0,0,53,1,38910,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Follow WP"),
(@ENTRY,@SOURCETYPE,4,0,40,0,100,0,7,0,0,0,41,0,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Stop WP");

UPDATE `gossip_menu_option` SET `menu_id`=11157, `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11156 AND `id`=0;

DELETE FROM `conditions` WHERE `SourceGroup`=11157 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11157, 0, 0, 0, 9, 0, 25006, 0, 0, 0, 0, 0, '', 'Shadow Priestess Malia - Show gossip only if quest 25006 is active');