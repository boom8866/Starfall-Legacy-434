-- Northwatch Supply Crate
SET @ENTRY := 39251;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,25,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Reset - Set Passive");

UPDATE `creature` SET `spawndist`=12, `MovementType`=1 WHERE `id`=39245;

-- Position update for Northwatch Supply Crate (id: 39251) in zone: 14, area: 14
UPDATE `creature` SET `position_x` = -1002.589, `position_y` = -4722.263, `position_z` = 15.704, `orientation`= 1.000 WHERE `guid` = 142043;

-- Position update for Northwatch Supply Crate (id: 39251) in zone: 14, area: 14
UPDATE `creature` SET `position_x` = -1017.732, `position_y` = -4733.135, `position_z` = 14.162, `orientation`= 3.077 WHERE `guid` = 143193;

-- Position update for Northwatch Supply Crate (id: 39251) in zone: 14, area: 14
UPDATE `creature` SET `position_x` = -1043.359, `position_y` = -4727.294, `position_z` = 15.680, `orientation`= 1.428 WHERE `guid` = 141991;

-- Position update for Northwatch Lug (id: 39249) in zone: 14, area: 14
UPDATE `creature` SET `position_x` = -1051.525, `position_y` = -4714.391, `position_z` = 17.223, `orientation`= 0.132 WHERE `guid` = 141990;

-- Position update for Northwatch Lug (id: 39249) in zone: 14, area: 14
UPDATE `creature` SET `position_x` = -1037.094, `position_y` = -4732.872, `position_z` = 14.737, `orientation`= 5.061 WHERE `guid` = 141992;

-- Position update for Northwatch Supply Crate (id: 39251) in zone: 14, area: 14
UPDATE `creature` SET `position_x` = -1020.667, `position_y` = -4749.634, `position_z` = 13.370, `orientation`= 0.987 WHERE `guid` = 143193;

-- Position update for Northwatch Lug (id: 39249) in zone: 14, area: 14
UPDATE `creature` SET `position_x` = -1004.354, `position_y` = -4745.337, `position_z` = 13.961, `orientation`= 1.623 WHERE `guid` = 143192;

-- Position update for Northwatch Lug (id: 39249) in zone: 14, area: 14
UPDATE `creature` SET `position_x` = -993.588, `position_y` = -4735.214, `position_z` = 15.263, `orientation`= 2.989 WHERE `guid` = 143194;

-- Position update for Northwatch Lug (id: 39249) in zone: 14, area: 14
UPDATE `creature` SET `position_x` = -990.366, `position_y` = -4708.268, `position_z` = 18.021, `orientation`= 1.772 WHERE `guid` = 142044;

-- Position update for Northwatch Supply Crate (id: 39251) in zone: 14, area: 14
UPDATE `creature` SET `position_x` = -1002.145, `position_y` = -4673.838, `position_z` = 28.224, `orientation`= 1.886 WHERE `guid` = 141999;

-- Position update for Northwatch Infantryman (id: 39260) in zone: 14, area: 366
UPDATE `creature` SET `position_x` = -985.414, `position_y` = -4662.704, `position_z` = 28.597, `orientation`= 1.336 WHERE `guid` = 143195;

-- Position update for Northwatch Supply Crate (id: 39251) in zone: 14, area: 366
UPDATE `creature` SET `position_x` = -980.776, `position_y` = -4516.019, `position_z` = 26.155, `orientation`= 1.077 WHERE `guid` = 142057;