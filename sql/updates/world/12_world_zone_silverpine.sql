-- High Priest Benedictus Voss
SET @ENTRY := 39097;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,38,0,100,0,0,1,0,0,80,3909700,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"on data set 1 do action"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,18,776,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"set unit flag");

-- Scarlet Bodyguard
SET @ENTRY := 1660;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,30,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,7000,8000,28000,11,12169,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Shield Block"),
(@ENTRY,@SOURCETYPE,2,0,2,0,100,1,0,15,0,0,25,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Flee at 15% HP"),
(@ENTRY,@SOURCETYPE,3,0,2,0,100,1,0,15,0,0,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Say Text at 15% HP"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,3909700,1,0,0,18,776,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Init Data Set");

-- High Priest Benedictus Voss
SET @ENTRY := 3909700;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,1000,1000,1000,1000,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 0"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,9000,9000,9000,9000,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 1"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,10000,10000,10000,10000,1,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"talk 2");

-- Lilian Voss
SET @ENTRY := 39038;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,4000,4000,2000,9000,87,3903800,3903801,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"on aggro do random action"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,1,2000,2000,2000,2000,11,73392,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"update ooc cast stealth"),
(@ENTRY,@SOURCETYPE,2,5,38,0,100,0,0,1,0,0,80,3903802,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"data set 1 do actiontime"),
(@ENTRY,@SOURCETYPE,3,0,25,0,100,0,0,0,0,0,29,0,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"follow owner"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,18,776,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"set unit flag"),
(@ENTRY,@SOURCETYPE,6,0,37,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Run");

-- Lilian Voss
SET @ENTRY := 3903802;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,3073.76,-555.71,126.72,0.08,"Move Point"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk Start"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,1000,1000,1000,1000,2,35,0,0,0,0,0,9,1660,1,50,0.0,0.0,0.0,0.0,"Set faction 35 - To ID: 1660"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,1000,1000,1000,1000,2,35,0,0,0,0,0,9,1665,1,50,0.0,0.0,0.0,0.0,"Set faction 35 - To ID: 1665"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,1000,1000,1000,1000,2,35,0,0,0,0,0,9,39097,1,50,0.0,0.0,0.0,0.0,"Set faction 35 - To ID: 1665"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,39097,50,0,0.0,0.0,0.0,0.0,"Init Data 1 to Father"),
(@ENTRY,@SOURCETYPE,6,0,0,0,100,0,5000,5000,5000,5000,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 1"),
(@ENTRY,@SOURCETYPE,7,0,0,0,100,0,1000,1000,1000,1000,11,46598,0,0,0,0,0,11,1665,20,0,0.0,0.0,0.0,0.0,"Jump on Captain"),
(@ENTRY,@SOURCETYPE,8,0,0,0,100,0,1500,1500,0,0,51,0,0,0,0,0,0,11,1665,20,0,0.0,0.0,0.0,0.0,"Kill Captain"),
(@ENTRY,@SOURCETYPE,9,0,0,0,100,0,1000,1000,0,0,11,46598,0,0,0,0,0,11,1660,20,0,0.0,0.0,0.0,0.0,"Jump on Bodyguard"),
(@ENTRY,@SOURCETYPE,10,0,0,0,100,0,1500,1500,0,0,51,0,0,0,0,0,0,11,1660,20,0,0.0,0.0,0.0,0.0,"Kill Bodyguard"),
(@ENTRY,@SOURCETYPE,11,0,0,0,100,0,0,0,0,0,1,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 2"),
(@ENTRY,@SOURCETYPE,12,0,0,0,100,0,5000,5000,0,0,1,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 3"),
(@ENTRY,@SOURCETYPE,13,0,0,0,100,0,5000,5000,0,0,1,4,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 4"),
(@ENTRY,@SOURCETYPE,14,0,0,0,100,0,0,0,0,0,11,46598,0,0,0,0,0,11,39097,20,0,0.0,0.0,0.0,0.0,"Jump on Target - 39097"),
(@ENTRY,@SOURCETYPE,15,0,0,0,100,0,0,0,0,0,33,39098,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"Quest Complete"),
(@ENTRY,@SOURCETYPE,16,0,0,0,100,0,3000,3000,3000,3000,51,0,0,0,0,0,0,11,39097,20,0,0.0,0.0,0.0,0.0,"Kill Father"),
(@ENTRY,@SOURCETYPE,17,0,0,0,100,0,10000,10000,0,0,41,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Despawn");

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

SET @CGUID := 801942;
DELETE FROM `creature` WHERE `id` IN (144951, 144952);
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+153;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+0, 144951, 0, 1, 1, 33981, 0, 1373.35, 1031.58, 54.6189, 0.959931, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+1, 144951, 0, 1, 1, 33978, 0, 1377.3, 1035.93, 55.0961, 3.14159, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+2, 144951, 0, 1, 1, 33981, 0, 1373.35, 1031.58, 54.6189, 0.959931, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+3, 144951, 646, 1, 8192, 0, 0, 967.871, 574.931, -44.4778, 5.47147, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+4, 144951, 646, 1, 8192, 0, 0, 991.187, 459.124, -44.3375, 1.22391, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+5, 144951, 646, 1, 8192, 0, 0, 1079.32, 538.924, -44.4618, 3.43992, 300, 0, 0, 42, 0, 0, 0, 33554432, 0),
(@CGUID+6, 144951, 0, 1, 1, 33981, 0, 1373.35, 1031.58, 54.6189, 0.959931, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+7, 144951, 0, 1, 1, 33978, 0, 1377.3, 1035.93, 55.0961, 3.14159, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+8, 144951, 0, 1, 1, 33981, 0, 1370.66, 1030.82, 55.134, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+9, 144951, 0, 1, 1, 33980, 0, 1374.14, 1036.35, 54.9217, 5.53269, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+10, 144951, 0, 1, 1, 33981, 0, 1369.57, 1036.9, 54.998, 0.20944, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+11, 144951, 0, 1, 1, 33978, 0, 1377.3, 1035.93, 55.0961, 3.14159, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+12, 144951, 0, 1, 1, 33981, 0, 1373.35, 1031.58, 54.6189, 0.959931, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+13, 144951, 0, 1, 1, 33985, 0, 1372.08, 1034.98, 54.8489, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+14, 144951, 0, 1, 1, 33983, 0, 1375.2, 1038.58, 55.2451, 4.55531, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+15, 144951, 0, 1, 1, 33985, 0, 1369.71, 1040.19, 55.0212, 5.58505, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+16, 144951, 0, 1, 1, 33984, 0, 1376, 1029.61, 54.9374, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+17, 144951, 0, 1, 1, 33979, 0, 1372.98, 1041.06, 55.381, 0.226893, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+18, 144951, 0, 1, 1, 33978, 0, 1378.16, 1031.71, 55.3717, 0.767945, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+19, 144951, 0, 1, 1, 33978, 0, 1372.58, 1038.07, 54.9666, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+20, 144951, 0, 1, 1, 33978, 0, 1375.42, 1033.81, 54.6522, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+21, 144951, 0, 1, 1, 33979, 0, 1369.65, 1033.67, 54.9668, 0.698132, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+22, 144951, 0, 1, 1, 33978, 0, 1367.33, 1035.38, 55.304, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+23, 144951, 0, 1, 1, 33981, 0, 1370.66, 1030.82, 55.134, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+24, 144951, 0, 1, 1, 33980, 0, 1374.14, 1036.35, 54.9217, 5.53269, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+25, 144951, 0, 1, 1, 33981, 0, 1369.57, 1036.9, 54.998, 0.20944, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+26, 144951, 0, 1, 1, 33984, 0, 1376, 1029.61, 54.9374, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+27, 144951, 0, 1, 1, 33979, 0, 1372.98, 1041.06, 55.381, 0.226893, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+28, 144951, 0, 1, 1, 33978, 0, 1378.16, 1031.71, 55.3717, 0.767945, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+29, 144951, 0, 1, 1, 33978, 0, 1372.58, 1038.07, 54.9666, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+30, 144951, 0, 1, 1, 33978, 0, 1375.42, 1033.81, 54.6522, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+31, 144951, 0, 1, 1, 33979, 0, 1369.65, 1033.67, 54.9668, 0.698132, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+32, 144951, 0, 1, 1, 33978, 0, 1367.33, 1035.38, 55.304, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+33, 144951, 0, 1, 1, 33981, 0, 1370.66, 1030.82, 55.134, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+34, 144951, 0, 1, 1, 33980, 0, 1374.14, 1036.35, 54.9217, 5.53269, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+35, 144951, 0, 1, 1, 33981, 0, 1369.57, 1036.9, 54.998, 0.20944, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+36, 144951, 0, 1, 1, 33978, 0, 1367.33, 1035.38, 55.304, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+37, 144951, 0, 1, 1, 33979, 0, 1369.65, 1033.67, 54.9668, 0.698132, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+38, 144951, 0, 1, 1, 33978, 0, 1375.42, 1033.81, 54.6522, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+39, 144951, 0, 1, 1, 33978, 0, 1372.58, 1038.07, 54.9666, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+40, 144951, 0, 1, 1, 33978, 0, 1378.16, 1031.71, 55.3717, 0.767945, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+41, 144951, 0, 1, 1, 33979, 0, 1372.98, 1041.06, 55.381, 0.226893, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+42, 144951, 0, 1, 1, 33984, 0, 1376, 1029.61, 54.9374, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+43, 144951, 0, 1, 1, 33985, 0, 1369.71, 1040.19, 55.0212, 5.58505, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+44, 144951, 0, 1, 1, 33983, 0, 1375.2, 1038.58, 55.2451, 4.55531, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+45, 144951, 0, 1, 1, 33985, 0, 1372.08, 1034.98, 54.8489, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+46, 144951, 0, 1, 1, 33981, 0, 1373.35, 1031.58, 54.6189, 0.959931, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+47, 144951, 0, 1, 1, 33978, 0, 1377.3, 1035.93, 55.0961, 3.14159, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+48, 144951, 0, 1, 1, 33981, 0, 1369.57, 1036.9, 54.998, 0.20944, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+49, 144951, 0, 1, 1, 33980, 0, 1374.14, 1036.35, 54.9217, 5.53269, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+50, 144951, 0, 1, 1, 33981, 0, 1370.66, 1030.82, 55.134, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+51, 144951, 0, 1, 1, 33978, 0, 1367.33, 1035.38, 55.304, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+52, 144951, 0, 1, 1, 33979, 0, 1369.65, 1033.67, 54.9668, 0.698132, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+53, 144951, 0, 1, 1, 33978, 0, 1375.42, 1033.81, 54.6522, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+54, 144951, 0, 1, 1, 33978, 0, 1372.58, 1038.07, 54.9666, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+55, 144951, 0, 1, 1, 33978, 0, 1378.16, 1031.71, 55.3717, 0.767945, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+56, 144951, 0, 1, 1, 33979, 0, 1372.98, 1041.06, 55.381, 0.226893, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+57, 144951, 0, 1, 1, 33984, 0, 1376, 1029.61, 54.9374, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+58, 144951, 0, 1, 1, 33985, 0, 1369.71, 1040.19, 55.0212, 5.58505, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+59, 144951, 0, 1, 1, 33983, 0, 1375.2, 1038.58, 55.2451, 4.55531, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+60, 144951, 0, 1, 1, 33985, 0, 1372.08, 1034.98, 54.8489, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+61, 144951, 0, 1, 1, 33978, 0, 1377.3, 1035.93, 55.0961, 3.14159, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+62, 144951, 0, 1, 1, 33981, 0, 1369.57, 1036.9, 54.998, 0.20944, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+63, 144951, 0, 1, 1, 33980, 0, 1374.14, 1036.35, 54.9217, 5.53269, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+64, 144951, 0, 1, 1, 33981, 0, 1370.66, 1030.82, 55.134, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+65, 144951, 0, 1, 1, 33978, 0, 1367.33, 1035.38, 55.304, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+66, 144951, 0, 1, 1, 33979, 0, 1369.65, 1033.67, 54.9668, 0.698132, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+67, 144951, 0, 1, 1, 33978, 0, 1375.42, 1033.81, 54.6522, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+68, 144951, 0, 1, 1, 33978, 0, 1372.58, 1038.07, 54.9666, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+69, 144951, 0, 1, 1, 33978, 0, 1378.16, 1031.71, 55.3717, 0.767945, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+70, 144951, 0, 1, 1, 33979, 0, 1372.98, 1041.06, 55.381, 0.226893, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+71, 144951, 0, 1, 1, 33984, 0, 1376, 1029.61, 54.9374, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+72, 144951, 0, 1, 1, 33985, 0, 1369.71, 1040.19, 55.0212, 5.58505, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+73, 144951, 0, 1, 1, 33983, 0, 1375.2, 1038.58, 55.2451, 4.55531, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+74, 144951, 0, 1, 1, 33985, 0, 1372.08, 1034.98, 54.8489, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+75, 144951, 0, 1, 1, 33981, 0, 1373.35, 1031.58, 54.6189, 0.959931, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+76, 144951, 0, 1, 1, 33978, 0, 1377.3, 1035.93, 55.0961, 3.14159, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+77, 144951, 0, 1, 1, 33981, 0, 1369.57, 1036.9, 54.998, 0.20944, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+78, 144951, 0, 1, 1, 33980, 0, 1374.14, 1036.35, 54.9217, 5.53269, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+79, 144951, 0, 1, 1, 33981, 0, 1370.66, 1030.82, 55.134, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+80, 144951, 0, 1, 1, 33978, 0, 1367.33, 1035.38, 55.304, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+81, 144951, 0, 1, 1, 33979, 0, 1369.65, 1033.67, 54.9668, 0.698132, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+82, 144951, 0, 1, 1, 33978, 0, 1375.42, 1033.81, 54.6522, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+83, 144951, 0, 1, 1, 33978, 0, 1372.58, 1038.07, 54.9666, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+84, 144951, 0, 1, 1, 33978, 0, 1378.16, 1031.71, 55.3717, 0.767945, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+85, 144951, 0, 1, 1, 33979, 0, 1372.98, 1041.06, 55.381, 0.226893, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+86, 144951, 0, 1, 1, 33984, 0, 1376, 1029.61, 54.9374, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+87, 144951, 0, 1, 1, 33985, 0, 1369.71, 1040.19, 55.0212, 5.58505, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+88, 144951, 0, 1, 1, 33983, 0, 1375.2, 1038.58, 55.2451, 4.55531, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+89, 144951, 0, 1, 1, 33985, 0, 1372.08, 1034.98, 54.8489, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+90, 144951, 0, 1, 1, 33981, 0, 1373.35, 1031.58, 54.6189, 0.959931, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+91, 144951, 0, 1, 1, 33978, 0, 1377.3, 1035.93, 55.0961, 3.14159, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+92, 144951, 0, 1, 1, 33981, 0, 1369.57, 1036.9, 54.998, 0.20944, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+93, 144951, 0, 1, 1, 33980, 0, 1374.14, 1036.35, 54.9217, 5.53269, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+94, 144951, 0, 1, 1, 33981, 0, 1370.66, 1030.82, 55.134, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+95, 144951, 0, 1, 1, 33978, 0, 1367.33, 1035.38, 55.304, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+96, 144951, 0, 1, 1, 33979, 0, 1369.65, 1033.67, 54.9668, 0.698132, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+97, 144951, 0, 1, 1, 33978, 0, 1375.42, 1033.81, 54.6522, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+98, 144951, 0, 1, 1, 33978, 0, 1372.58, 1038.07, 54.9666, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+99, 144951, 0, 1, 1, 33978, 0, 1378.16, 1031.71, 55.3717, 0.767945, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+100, 144951, 0, 1, 1, 33979, 0, 1372.98, 1041.06, 55.381, 0.226893, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+101, 144951, 0, 1, 1, 33984, 0, 1376, 1029.61, 54.9374, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+102, 144951, 0, 1, 1, 33985, 0, 1369.71, 1040.19, 55.0212, 5.58505, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+103, 144951, 0, 1, 1, 33983, 0, 1375.2, 1038.58, 55.2451, 4.55531, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+104, 144951, 0, 1, 1, 33985, 0, 1372.08, 1034.98, 54.8489, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+105, 144951, 0, 1, 1, 33981, 0, 1373.35, 1031.58, 54.6189, 0.959931, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+106, 144951, 0, 1, 1, 33978, 0, 1377.3, 1035.93, 55.0961, 3.14159, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+107, 144951, 0, 1, 1, 33981, 0, 1369.57, 1036.9, 54.998, 0.20944, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+108, 144951, 0, 1, 1, 33980, 0, 1374.14, 1036.35, 54.9217, 5.53269, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+109, 144951, 0, 1, 1, 33981, 0, 1370.66, 1030.82, 55.134, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+110, 144951, 0, 1, 1, 33978, 0, 1367.33, 1035.38, 55.304, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+111, 144951, 0, 1, 1, 33979, 0, 1369.65, 1033.67, 54.9668, 0.698132, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+112, 144951, 0, 1, 1, 33978, 0, 1375.42, 1033.81, 54.6522, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+113, 144951, 0, 1, 1, 33978, 0, 1372.58, 1038.07, 54.9666, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+114, 144951, 0, 1, 1, 33978, 0, 1378.16, 1031.71, 55.3717, 0.767945, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+115, 144951, 0, 1, 1, 33979, 0, 1372.98, 1041.06, 55.381, 0.226893, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+116, 144951, 0, 1, 1, 33984, 0, 1376, 1029.61, 54.9374, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+117, 144951, 0, 1, 1, 33985, 0, 1369.71, 1040.19, 55.0212, 5.58505, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+118, 144951, 0, 1, 1, 33983, 0, 1375.2, 1038.58, 55.2451, 4.55531, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+119, 144951, 0, 1, 1, 33985, 0, 1372.08, 1034.98, 54.8489, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+120, 144951, 0, 1, 1, 33985, 0, 1369.71, 1040.19, 55.0212, 5.58505, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+121, 144951, 0, 1, 1, 33983, 0, 1375.2, 1038.58, 55.2451, 4.55531, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+122, 144951, 0, 1, 1, 33985, 0, 1372.08, 1034.98, 54.8489, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+123, 144951, 0, 1, 1, 33981, 0, 1373.35, 1031.58, 54.6189, 0.959931, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+124, 144951, 0, 1, 1, 33978, 0, 1377.3, 1035.93, 55.0961, 3.14159, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+125, 144951, 0, 1, 1, 33981, 0, 1369.57, 1036.9, 54.998, 0.20944, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+126, 144951, 0, 1, 1, 33980, 0, 1374.14, 1036.35, 54.9217, 5.53269, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+127, 144951, 0, 1, 1, 33981, 0, 1370.66, 1030.82, 55.134, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+128, 144951, 0, 1, 1, 33978, 0, 1367.33, 1035.38, 55.304, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+129, 144951, 0, 1, 1, 33979, 0, 1369.65, 1033.67, 54.9668, 0.698132, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+130, 144951, 0, 1, 1, 33978, 0, 1375.42, 1033.81, 54.6522, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+131, 144951, 0, 1, 1, 33978, 0, 1372.58, 1038.07, 54.9666, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+132, 144951, 0, 1, 1, 33978, 0, 1378.16, 1031.71, 55.3717, 0.767945, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+133, 144951, 0, 1, 1, 33979, 0, 1372.98, 1041.06, 55.381, 0.226893, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+134, 144951, 0, 1, 1, 33984, 0, 1376, 1029.61, 54.9374, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+135, 144951, 0, 1, 1, 33985, 0, 1369.71, 1040.19, 55.0212, 5.58505, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+136, 144951, 0, 1, 1, 33983, 0, 1375.2, 1038.58, 55.2451, 4.55531, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+137, 144951, 0, 1, 1, 33985, 0, 1372.08, 1034.98, 54.8489, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+138, 144951, 0, 1, 1, 33981, 0, 1373.35, 1031.58, 54.6189, 0.959931, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+139, 144951, 0, 1, 1, 33978, 0, 1377.3, 1035.93, 55.0961, 3.14159, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+140, 144951, 0, 1, 1, 33981, 0, 1369.57, 1036.9, 54.998, 0.20944, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+141, 144951, 0, 1, 1, 33980, 0, 1374.14, 1036.35, 54.9217, 5.53269, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+142, 144951, 0, 1, 1, 33981, 0, 1370.66, 1030.82, 55.134, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+143, 144951, 0, 1, 1, 33978, 0, 1367.33, 1035.38, 55.304, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+144, 144951, 0, 1, 1, 33979, 0, 1369.65, 1033.67, 54.9668, 0.698132, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+145, 144951, 0, 1, 1, 33978, 0, 1375.42, 1033.81, 54.6522, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+146, 144951, 0, 1, 1, 33978, 0, 1372.58, 1038.07, 54.9666, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+147, 144951, 0, 1, 1, 33978, 0, 1378.16, 1031.71, 55.3717, 0.767945, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+148, 144951, 0, 1, 1, 33979, 0, 1372.98, 1041.06, 55.381, 0.226893, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+149, 144951, 0, 1, 1, 33984, 0, 1376, 1029.61, 54.9374, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+150, 144951, 0, 1, 1, 33985, 0, 1369.71, 1040.19, 55.0212, 5.58505, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+151, 144951, 0, 1, 1, 33983, 0, 1375.2, 1038.58, 55.2451, 4.55531, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+152, 144951, 0, 1, 1, 33985, 0, 1372.08, 1034.98, 54.8489, 0.890118, 500, 0, 0, 273, 0, 0, 0, 0, 0),
(@CGUID+153, 144952, 0, 1, 65535, 0, 0, 3040.39, -559.053, 122.038, 0.201109, 300, 0, 0, 42, 0, 0, 0, 33554432, 0);

UPDATE `creature_template` SET `minlevel`=10, `maxlevel`=11, `mindmg`=3, `maxdmg`=5, `attackpower`=2, `baseattacktime`=2000, `rangeattacktime`=2000 WHERE `entry`=39038;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=33 WHERE `item`=52079;

DELETE FROM `creature_loot_template` WHERE `entry` = '1535' AND `item` = '52079';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES
(1535, 52079, 50);

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1, `action_menu_id`=11136 WHERE `menu_id`=11134 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1, `action_menu_id`=11134 WHERE `menu_id`=11135 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11136 AND `id`=0;

DELETE FROM `creature_text` WHERE `entry`=38999;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38999,3,0,'Gebler, father, why would you...',12,0,100,0,0,0,'Comment'),
(38999,1,0,'Gebler, you came! What did he say?',12,0,100,0,0,0,'Comment'),
(38999,4,0,'The world of the living may have turned its back on me, but I\'m no damned Scourge. Just go.',12,0,100,0,0,0,'Comment'),
(38999,2,0,'What? NO! This can\'t be! Gebler, you know me... we were friends once!',12,0,100,0,0,0,'Comment'),
(38999,0,0,'Yes, my... wait, be quiet! I hear the lieutenant approaching.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=39002;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(39002,1,0,'High Priest Voss denounces you as a daughter. He\'s ordered that you be executed immediately.',12,0,100,0,0,0,'Comment'),
(39002,1,1,'The High Priest sends his regrets. He had hoped that one day you would be a powerful weapon against our enemies.',12,0,100,0,0,0,'Comment'),
(39002,0,0,'The time has come, my little captive... word has come back from your father.',12,0,100,0,0,0,'Comment'),
(39002,2,0,'Unfortunately, you were too dangerous in life, and you\'re far too dangerous in undeath. I will enjoy killing you, you Scourged witch...',12,0,100,0,0,0,'Comment');

UPDATE `creature_template` SET `gossip_menu_id`=11134 WHERE `entry`=38999;

DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (11134, 11135, 11136);
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(11136, 0, 0, 'Your father?', 1, 1, 0, 0, 0, 0, ''),
(11134, 0, 0, 'I\'m here to rescue you.', 1, 1, 11135, 0, 0, 0, ''),
(11135, 0, 0, 'Lilian, you\'re one of the Forsaken, like me.  Which brings the question: why did the Scarlet Crusade put you in a cage?  They usually kill the undead on sight.', 1, 1, 11136, 0, 0, 0, '');

UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry`=39002;

-- Scarlet Lieutenant Gebler
SET @ENTRY := 39002;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,1,500,500,120000,120000,53,0,39002,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - WP Start"),
(@ENTRY,@SOURCETYPE,1,0,40,0,100,1,4,0,0,0,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 4 - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,39002,0,0,1,1,6000,0,0,0,0,10,204036,38999,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1 (Lilian Voss)"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,1,38999,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 (Lilian Voss) - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,39002,0,0,1,2,6000,0,0,0,0,10,204036,38999,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2 (Lilian Voss)"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,2,38999,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 (Lilian Voss) - Talk 2"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,2,39002,0,0,45,0,1,0,0,0,0,10,204036,38999,0,0.0,0.0,0.0,0.0,"After Talk 2 - Set Data 1 to Lilian Voss"),
(@ENTRY,@SOURCETYPE,7,0,6,0,100,0,0,0,0,0,75,73304,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Set Shadowy"),
(@ENTRY,@SOURCETYPE,8,0,6,0,100,0,0,0,0,0,41,10000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Force Despawn");

-- Lilian Voss
SET @ENTRY := 38999;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11136,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11136,0,0,0,1,0,8000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,11136,0,0,0,83,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Remove NPC Flag Gossip"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,11136,0,0,0,12,39002,8,300000,0,0,0,8,0,0,0,2445.79,1599.76,66.57,5.42,"On Gossip Select - Summon Gebler"),
(@ENTRY,@SOURCETYPE,4,0,38,0,100,0,0,1,0,0,11,73304,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Enrage"),
(@ENTRY,@SOURCETYPE,5,6,38,0,100,0,0,1,0,0,66,15,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Fix Orientation"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Phase 1"),
(@ENTRY,@SOURCETYPE,7,0,1,1,100,0,1500,1500,50000,50000,11,46598,0,0,0,0,0,11,39002,30,0,0.0,0.0,0.0,0.0,"OOC - Ride Gebler"),
(@ENTRY,@SOURCETYPE,8,0,1,1,100,0,4000,4000,50000,50000,51,0,0,0,0,0,0,11,39002,30,0,0.0,0.0,0.0,0.0,"OOC - Kill Gebler"),
(@ENTRY,@SOURCETYPE,9,0,1,1,100,0,6500,6500,50000,50000,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Talk 3"),
(@ENTRY,@SOURCETYPE,10,0,52,1,100,0,3,38999,0,0,1,4,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Talk 4"),
(@ENTRY,@SOURCETYPE,11,0,52,1,100,0,3,38999,0,0,33,38999,0,0,0,0,0,18,40,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Quest Credit AoE"),
(@ENTRY,@SOURCETYPE,12,13,52,1,100,0,4,38999,0,0,81,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 4 - Reset NPC Flag"),
(@ENTRY,@SOURCETYPE,13,14,61,0,100,0,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Set Phase 0"),
(@ENTRY,@SOURCETYPE,14,0,61,0,100,0,0,0,0,0,41,10000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

DELETE FROM `waypoints` WHERE `entry` = '39002';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(39002, 0, 2452.56, 1590.69, 72.15, 'Gebler WP'),
(39002, 1, 2448.00, 1587.62, 72.15, 'Gebler WP'),
(39002, 2, 2442.37, 1591.15, 72.15, 'Gebler WP'),
(39002, 3, 2440.45, 1596.34, 72.15, 'Gebler WP'),
(39002, 4, 2441.38, 1597.85, 72.15, 'Gebler WP');

-- Position update for Lilian Voss (id: 38999) in zone: 85, area: 4917
UPDATE `creature` SET `position_x` = 2442.920, `position_y` = 1600.710, `position_z` = 72.150, `orientation`= 4.452 WHERE `guid` = 204036;

UPDATE `creature` SET `spawntimesecs`=60 WHERE `guid`=204036;

-- Shadow Priestess Malia
SET @ENTRY := 39117;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11157,0,0,0,72,0,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11157,0,0,0,1,0,3000,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Talk"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,0,39117,0,0,53,0,39117,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Start WP"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,4,0,0,0,1,1,5000,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"WP End"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,39117,0,0,1,2,5000,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Mid Event"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,2,39117,0,0,1,3,5000,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Mid Event"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,3,39117,0,0,1,4,4000,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Mid Event"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,4,39117,0,0,12,38980,3,40000,0,0,0,8,0,0,0,2246.8,228.36,42.65,1.96,"Summon Devlin"),
(@ENTRY,@SOURCETYPE,8,0,62,0,100,0,11157,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Block Gossip"),
(@ENTRY,@SOURCETYPE,10,0,52,0,100,0,5,39117,0,0,24,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Evade"),
(@ENTRY,@SOURCETYPE,11,0,52,0,100,0,5,39117,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Despawn");