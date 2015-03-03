-- Twilight Recruit
SET @ENTRY := 39619;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,64,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,0,0,0,0,1,1,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,0,0,0,0,0,1,2,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk"),
(@ENTRY,@SOURCETYPE,3,4,61,0,100,0,0,0,0,0,83,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Remove Flag"),
(@ENTRY,@SOURCETYPE,4,8,61,0,100,0,0,0,0,0,29,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Follow"),
(@ENTRY,@SOURCETYPE,5,0,6,0,100,0,0,0,0,0,82,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Set NPC Flag"),
(@ENTRY,@SOURCETYPE,6,0,11,0,100,0,0,0,0,0,82,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Respawn - Set NPC Flag"),
(@ENTRY,@SOURCETYPE,7,0,7,0,100,0,0,0,0,0,82,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Set NPC Flag"),
(@ENTRY,@SOURCETYPE,8,0,61,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");