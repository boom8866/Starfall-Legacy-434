-- DELETE KODOS ALREADY SPAWNED (Only two kodos Need to be spawned)
DELETE FROM `creature` WHERE `guid` = '736387';
DELETE FROM `creature` WHERE `guid` = '736388';
DELETE FROM `creature` WHERE `guid` = '736394';
DELETE FROM `creature` WHERE `guid` = '736395';

UPDATE `creature` SET `spawntimesecs`= '60' WHERE `guid` = '736392';
UPDATE `creature` SET `spawntimesecs`= '60' WHERE `guid` = '736393';

UPDATE `creature_template` SET `VehicleId`= '690' WHERE `entry` = '39364';
UPDATE `creature_template` SET `spell1`= '73851' WHERE `entry`= '39364';
UPDATE creature SET phaseMask = '1' WHERE id = '39365';

DELETE FROM `gossip_menu` WHERE `entry` = '39380';
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES
(39380, 11209);

UPDATE `gossip_menu_option` SET `option_id` = '1', `npc_option_npcflag` = '1' WHERE  `menu_id` = '11209' AND `id` = '0';

DELETE FROM `waypoints` WHERE `entry` = '39364';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES (39364, 1, 1279.77, -4818.80, 17.96, 'The Wolf Waypoint');

-- Shin Stonepillar
SET @ENTRY := 39380;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,11209,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,11209,0,0,0,85,73840,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon The Wolf");

-- The Wolf
SET @ENTRY := 39364;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,86,46598,0,23,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Summoned - Ride Vehicle"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,8,0,100,0,73851,1,0,0,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On SpellHit - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,60,0,100,0,4000,4000,4000,4000,45,0,1,0,0,0,0,10,736393,39365,0,0.0,0.0,0.0,0.0,"Update - Set Data 1 to Kodos"),
(@ENTRY,@SOURCETYPE,4,0,27,0,100,0,0,0,0,0,75,73919,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Add Invisibility Detection for Quest"),
(@ENTRY,@SOURCETYPE,5,0,40,0,100,0,1,0,0,0,18,4,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Set Rooted "),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,0,39365,0,0,53,0,39364,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Talk 0 (The Kodo) - Start WP"),
(@ENTRY,@SOURCETYPE,7,0,8,0,100,0,73868,1,0,0,33,39365,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Spell Hit - Quest Credit"),
(@ENTRY,@SOURCETYPE,8,0,8,0,100,0,73868,1,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spell Hit - Remove Vehicle");

-- The Kodo
SET @ENTRY := 39365;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,17,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"AI Init - Set emote 35"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,23,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Get Data 1 - Set Phase 1"),
(@ENTRY,@SOURCETYPE,2,0,60,1,100,1,2000,2000,2000,2000,1,0,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Phase 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,0,39365,0,0,1,1,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Phase 1 - On Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,1,39365,0,0,51,0,0,0,0,0,0,10,736392,39365,0,0.0,0.0,0.0,0.0,"Phase 1 - On Talk 1 - Kill Kodo"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,1,39365,0,0,1,2,6000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Phase 1 - On Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,1,39365,0,0,17,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Phase 1 - On Talk 1 - Set Emote to 0"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,2,39365,0,0,11,73868,4,0,0,0,0,11,39364,10,0,0.0,0.0,0.0,0.0,"Phase 1 - On Talk 2 - Cast Rumbling Hooves to The Wolf"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,2,39365,0,0,1,3,1000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Phase 1 - On Talk 2 - Talk 3");

DELETE FROM `creature_text` WHERE `entry`=39365;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(39365,0,0,'He happened upon a pair of battling kodos.',41,0,100,0,0,0,'Comment'),
(39365,1,0,'Clever as he was, The Wolf decided to wait for one to defeat the other.',41,0,100,0,0,0,'Comment'),
(39365,2,0,'When the weaker Kodo died, The Wolf approached and tried to eat it.',41,0,100,0,0,0,'Comment'),
(39365,3,0,'The remaining Kodo, angry at The Wolf\'s impetuousness, swiftly killed The Wolf before he had a chance to eat.',41,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=39364;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(39364,0,0,'One day, The Wolf was very hungry, so he ran east to look for some food.',41,0,100,0,0,0,'Comment'),
(39364,1,0,'The Wolf had grown tired of eating boar meat.',41,0,100,0,0,0,'Comment'),
(39364,1,1,'The Wolf did not care for raptor meat.',41,0,100,0,0,0,'Comment'),
(39364,1,2,'He was hungry for kodo meat.',41,0,100,0,0,0,'Comment'),
(39364,1,3,'The Wolf was lazy, and didn\'t want to work for his meal.',41,0,100,0,0,0,'Comment'),
(39364,1,4,'The Wolf rand and ran, looking for an easy meal.',41,0,100,0,0,0,'Comment');