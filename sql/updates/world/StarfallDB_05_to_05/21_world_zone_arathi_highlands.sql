UPDATE `creature` SET `spawndist`=15, `MovementType`=1 WHERE `guid`=162476;
UPDATE `gameobject` SET `phaseMask`=1, `position_z`=48.421 WHERE `guid`=722613;
UPDATE `quest_template` SET `SpecialFlags`=2 WHERE `Id` IN (26050, 26628);
UPDATE `quest_template` SET `PrevQuestId`=26052 WHERE `Id`=26628;
UPDATE `quest_template` SET `SourceSpellId`=95675 WHERE `Id`=26051;

DELETE FROM `creature_text` WHERE `entry` IN (2775, 2610);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(2775,0,0,'You\'ve plundered our treasures too long. Prepare to meet your watery grave!',14,0,100,0,0,0,'Comment'),
(2610,0,0,'If we can just hold them now, I am sure we will be in the clear.',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry` IN (12938, 12937, 12936, 12923, 12924, 12925);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(12938,0,0,'Dying... See the light... gloriouss...',12,0,100,0,0,0,'Comment'),
(12938,0,1,'I\'m saved! Thank you, doctor!',12,0,100,0,0,0,'Comment'),
(12938,0,2,'Whoa! Look at that bullseye!',12,0,100,0,0,0,'Comment'),
(12938,0,3,'HOORAY! I AM SAVED!',12,0,100,0,0,0,'Comment'),
(12938,0,4,'Brain encaved... mortar... bas... hed... leaking... dyin.. g...',12,0,100,0,0,0,'Comment'),
(12936,0,0,'Dying... See the light... gloriouss...',12,0,100,0,0,0,'Comment'),
(12936,0,1,'I\'m saved! Thank you, doctor!',12,0,100,0,0,0,'Comment'),
(12936,0,2,'Whoa! Look at that bullseye!',12,0,100,0,0,0,'Comment'),
(12936,0,3,'HOORAY! I AM SAVED!',12,0,100,0,0,0,'Comment'),
(12936,0,4,'Brain encaved... mortar... bas... hed... leaking... dyin.. g...',12,0,100,0,0,0,'Comment'),
(12937,0,0,'Dying... See the light... gloriouss...',12,0,100,0,0,0,'Comment'),
(12937,0,1,'I\'m saved! Thank you, doctor!',12,0,100,0,0,0,'Comment'),
(12937,0,2,'Whoa! Look at that bullseye!',12,0,100,0,0,0,'Comment'),
(12937,0,3,'HOORAY! I AM SAVED!',12,0,100,0,0,0,'Comment'),
(12937,0,4,'Brain encaved... mortar... bas... hed... leaking... dyin.. g...',12,0,100,0,0,0,'Comment'),
(12923,0,0,'Dying... See the light... gloriouss...',12,0,100,0,0,0,'Comment'),
(12923,0,1,'I\'m saved! Thank you, doctor!',12,0,100,0,0,0,'Comment'),
(12923,0,2,'Whoa! Look at that bullseye!',12,0,100,0,0,0,'Comment'),
(12923,0,3,'HOORAY! I AM SAVED!',12,0,100,0,0,0,'Comment'),
(12923,0,4,'Brain encaved... mortar... bas... hed... leaking... dyin.. g...',12,0,100,0,0,0,'Comment'),
(12924,0,0,'Dying... See the light... gloriouss...',12,0,100,0,0,0,'Comment'),
(12924,0,1,'I\'m saved! Thank you, doctor!',12,0,100,0,0,0,'Comment'),
(12924,0,2,'Whoa! Look at that bullseye!',12,0,100,0,0,0,'Comment'),
(12924,0,3,'HOORAY! I AM SAVED!',12,0,100,0,0,0,'Comment'),
(12924,0,4,'Brain encaved... mortar... bas... hed... leaking... dyin.. g...',12,0,100,0,0,0,'Comment'),
(12925,0,0,'Dying... See the light... gloriouss...',12,0,100,0,0,0,'Comment'),
(12925,0,1,'I\'m saved! Thank you, doctor!',12,0,100,0,0,0,'Comment'),
(12925,0,2,'Whoa! Look at that bullseye!',12,0,100,0,0,0,'Comment'),
(12925,0,3,'HOORAY! I AM SAVED!',12,0,100,0,0,0,'Comment'),
(12925,0,4,'Brain encaved... mortar... bas... hed... leaking... dyin.. g...',12,0,100,0,0,0,'Comment');

-- Lolo the Lookout
SET @ENTRY := 2766;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,5000,5000,5000,5000,49,0,0,0,0,0,0,11,2775,80,0,0.0,0.0,0.0,0.0,"OOC - Attack Marauder"),
(@ENTRY,@SOURCETYPE,1,0,2,0,100,0,20,50,0,0,42,25,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Invincible");

-- Daggerspine Marauder
SET @ENTRY := 2775;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,5,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,54,0,100,0,0,0,0,0,46,120,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move Forward"),
(@ENTRY,@SOURCETYPE,2,0,6,0,10,0,0,0,0,0,15,26628,0,0,0,0,0,18,250,0,0,0.0,0.0,0.0,0.0,"On Death - Quest Complete"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Run"),
(@ENTRY,@SOURCETYPE,4,0,1,0,100,0,5000,5000,5000,5000,49,0,0,0,0,0,0,11,2766,80,0,0.0,0.0,0.0,0.0,"OOC - Attack Lolo");

UPDATE `creature_template` SET `unit_flags`=0, `flags_extra`=0 WHERE `entry`=2766;
UPDATE `creature_template` SET `minlevel`=27, `maxlevel`=30, `attackpower`=72 WHERE `entry`=2775;
UPDATE `gossip_menu_option` SET `option_text`='Teach me how to create and apply special bandages, Doctor.' WHERE `menu_id`=5381 AND `id`=0;
DELETE FROM `gossip_menu_option` WHERE `menu_id`=5381 AND `id`=1;
DELETE FROM `gossip_menu_option` WHERE `menu_id`=5381 AND `id`=2;
UPDATE `creature_template` SET `gossip_menu_id`=5381 WHERE `entry`=12939;