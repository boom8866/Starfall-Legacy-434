DELETE FROM `creature_text` WHERE `entry`=951;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(951,0,0,'BY THE LIGHT BE RENEWED!',12,0,100,0,0,0,'Brother Paxton - Renew Cast Phrase'),
(951,1,0,'AND I LAY MY HANDS UPON YOU!',12,0,100,0,0,0,'Brother Paxton - Renew Cast Phrase'),
(951,1,1,'Let the Holy Light embrace you!',12,0,100,0,0,0,'Brother Paxton - Healing Cast Phrase'),
(951,2,0,'Be healed, brother!',12,0,100,0,0,0,'Brother Paxton - Healing Cast Phrase'),
(951,2,1,'FIGHT ON, BROTHER!',12,0,100,0,0,0,'Brother Paxton - Healing Cast Phrase'),
(951,3,0,'[Right-Click] |cFFFFFFFFon Injured Stormwind Infantry that you find in the north field.|r',42,0,100,0,0,0,'Comment');

-- Brother Paxton
SET @ENTRY := 951;
SET @SOURCETYPE := 0;

-- Brother Paxton
SET @ENTRY := 951;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,0,0,1800000,1800000,11,13864,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Every 30 Minutes, re-apply fortitude"),
(@ENTRY,@SOURCETYPE,1,0,25,0,100,0,0,0,0,0,53,0,95100,1,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Reset - Start Waypoint Path"),
(@ENTRY,@SOURCETYPE,2,3,40,0,25,0,0,0,0,0,54,7000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Pause waypoint"),
(@ENTRY,@SOURCETYPE,3,0,61,0,20,0,0,0,0,0,88,95100,95103,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Chance to do Random Timed Action"),
(@ENTRY,@SOURCETYPE,4,0,19,0,100,0,28806,0,0,0,1,3,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 3"),
(@ENTRY,@SOURCETYPE,5,0,19,0,100,0,28808,0,0,0,1,3,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 3"),
(@ENTRY,@SOURCETYPE,6,0,19,0,100,0,28809,0,0,0,1,3,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 3"),
(@ENTRY,@SOURCETYPE,7,0,19,0,100,0,28810,0,0,0,1,3,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 3"),
(@ENTRY,@SOURCETYPE,8,0,19,0,100,0,28811,0,0,0,1,3,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 3"),
(@ENTRY,@SOURCETYPE,9,0,19,0,100,0,28812,0,0,0,1,3,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 3"),
(@ENTRY,@SOURCETYPE,10,0,19,0,100,0,28813,0,0,0,1,3,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 3"),
(@ENTRY,@SOURCETYPE,11,0,19,0,100,0,29082,0,0,0,1,3,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 3"),
(@ENTRY,@SOURCETYPE,12,0,25,0,100,0,0,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Reset - Set Walk"),
(@ENTRY,@SOURCETYPE,13,3,40,0,25,0,0,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Pause waypoint - Set Walk");
