UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=10974 AND `id`=0;

-- Deletes creature Captive Spitescale Scout (id: 38142, guid: 142383) in zone: 14, area: 4865
DELETE FROM `creature` WHERE `guid` = 142383; DELETE FROM creature_addon WHERE guid = 142383;

-- Captive Spitescale Scout
SET @ENTRY := 38142;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,46,6,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Data Set 1 - Move Forward"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,19,33024,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Data Set 1 - Remove Unit Flags"),
(@ENTRY,@SOURCETYPE,2,0,6,0,100,0,0,0,0,0,9,0,0,0,0,0,0,14,48543,201968,0,0.0,0.0,0.0,0.0,"On Death - Close Cage"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,1,0,0,81,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Data Set 1 - Remove NPC Flag"),
(@ENTRY,@SOURCETYPE,4,0,6,0,100,0,0,0,0,0,70,0,0,0,0,0,0,10,142394,39062,0,0.0,0.0,0.0,0.0,"On Death - Spawn Jailor"),
(@ENTRY,@SOURCETYPE,5,0,6,0,100,0,0,0,0,0,41,2000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Despawn");