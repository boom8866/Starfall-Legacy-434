UPDATE `conditions` SET `SourceEntry`=1 WHERE  `SourceTypeOrReferenceId`=15 AND `SourceGroup`=5967 AND `SourceEntry`=0 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=9 AND `ConditionTarget`=0 AND `ConditionValue1`=28052 AND `ConditionValue2`=0 AND `ConditionValue3`=0;
UPDATE `conditions` SET `SourceEntry`=1 WHERE  `SourceTypeOrReferenceId`=15 AND `SourceGroup`=5968 AND `SourceEntry`=0 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=9 AND `ConditionTarget`=0 AND `ConditionValue1`=28052 AND `ConditionValue2`=0 AND `ConditionValue3`=0;

-- Lanie Reed
SET @ENTRY := 2941;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,4,0,100,0,0,0,0,0,12,9526,4,30000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Lanie Reed - On Aggro - Summon Enraged Gryphon"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,12,9526,4,30000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Lanie Reed - On Aggro - Summon Enraged Gryphon"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Lanie Reed - On Aggro - Say Line 0"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,5967,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,4,0,62,0,100,0,5967,1,0,0,75,65141,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Cast Phase"),
(@ENTRY,@SOURCETYPE,5,0,62,0,100,0,5967,1,0,0,85,88498,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Flight Machine");

DELETE FROM `creature` WHERE `guid` = 198685;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `curhealth`, `curmana`) VALUES
(198685, 44244, 530, 4294967295, 1, 9502.063477, -6766.545898, 16.495075, 4.638288, 300, 37735, 20288);

DELETE FROM `creature` WHERE `guid` = 198686;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `curhealth`, `curmana`) VALUES
(198686, 27946, 530, 1, 1, 9506.100586, -6766.364746, 16.494289, 4.399532, 300, 37735, 20288);

DELETE FROM `creature` WHERE `guid` = 198687;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `curhealth`, `curmana`) VALUES
(198687, 27946, 530, 1, 1, 9498.155273, -6766.183594, 16.496826, 4.386966, 300, 37735, 20288);

DELETE FROM `creature` WHERE `guid` = 198688;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `curhealth`, `curmana`) VALUES
(198688, 27946, 530, 1, 1, 8743.609375, -6646.658691, 70.736633, 5.690900, 300, 37735, 20288);

DELETE FROM `creature` WHERE `guid` = 198689;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `curhealth`, `curmana`) VALUES
(198689, 27946, 530, 1, 1, 8738.664063, -6651.111328, 70.435471, 5.522039, 300, 37735, 20288);