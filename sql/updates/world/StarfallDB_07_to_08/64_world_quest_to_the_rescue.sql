-- Kadrak
SET @ENTRY := 8582;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,10411,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,75,65051,7,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Cast Spell to Invoker"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,56,45051,1,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Add Kadrak's Reins"),
(@ENTRY,@SOURCETYPE,4,0,62,0,100,0,10411,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,5,6,62,0,100,0,10411,2,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,6,7,61,0,100,0,0,0,0,0,85,96925,2,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Summon Burning Blade Flyer"),
(@ENTRY,@SOURCETYPE,7,0,61,0,100,0,0,0,0,0,1,1,2000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 1");

-- Burning Blade Flyer
SET @ENTRY := 52385;
SET @SOURCETYPE := 0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,10,734271,8582,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move To Kadrak"),
(@ENTRY,@SOURCETYPE,2,0,34,0,100,1,0,0,0,0,86,46598,0,18,10,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Update - Grab Player"),
(@ENTRY,@SOURCETYPE,3,0,27,0,100,0,0,0,0,0,53,1,52385,0,13712,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,4,5,40,0,100,0,4,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached 4 - Remove Passenger"),
(@ENTRY,@SOURCETYPE,5,6,61,0,100,0,0,0,0,0,33,34007,0,0,0,0,0,18,40,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,0,0,0,0,0,41,2500,0,0,0,0,0,1,40,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

UPDATE `creature_template` SET `speed_walk`=2, `speed_run`=2 WHERE `entry`=52385;