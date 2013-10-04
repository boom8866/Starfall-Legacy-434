UPDATE creature SET phaseMask = '1' where id = '3232';
UPDATE creature SET phaseMask = '1' where id = '5807';
UPDATE `creature_template` SET `flags_extra`=0 WHERE  `entry`=15647;
UPDATE `creature_template` SET `flags_extra`=0 WHERE  `entry`=15651;
UPDATE `creature` SET `phaseMask`=1 WHERE  `guid`=763486;
DELETE FROM `spell_area` WHERE `quest_start` = '24970';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES (49417, 154, 24970, 0, 0, 0, 2, 1, 42, 11);
UPDATE `quest_template` SET `PrevQuestId`=3096 WHERE  `Id`=24967;
UPDATE `quest_template` SET `NextQuestId`=0, `NextQuestIdChain`=0 WHERE  `Id`=26801;
UPDATE `quest_template` SET `PrevQuestId`=28651 WHERE  `Id`=24961;
UPDATE `quest_template` SET `PrevQuestId`=0 WHERE  `Id`=3095;
UPDATE `quest_template` SET `PrevQuestId`=3095 WHERE  `Id`=24969;
UPDATE `quest_template` SET `PrevQuestId`=0 WHERE  `Id`=3097;
UPDATE `quest_template` SET `PrevQuestId`=3097 WHERE  `Id`=24966;
UPDATE `creature_template` SET `ScriptName`='npc_wounded_deathguard' WHERE  `entry`=44795;
UPDATE `quest_template` SET `PrevQuestId`=3099 WHERE  `Id`=24968;
UPDATE `quest_template` SET `PrevQuestId`=0 WHERE  `Id`=3099;
UPDATE `quest_template` SET `PrevQuestId`=3098 WHERE  `Id`=24965;
UPDATE `quest_template` SET `PrevQuestId`=0 WHERE  `Id`=3098;
UPDATE `creature_template` SET `gossip_menu_id`=0 WHERE  `entry`=38037;
UPDATE `creature_template` SET `gossip_menu_id`=0 WHERE  `entry`=38245;
UPDATE `creature_template` SET `gossip_menu_id`=0 WHERE  `entry`=38243;

-- Zuni
SET @ENTRY := 37988;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,80,3798800,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Troll - lvl <1> Zuni - On spawn, start timed event");

-- Zuni
SET @ENTRY := 3798800;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,1,2000,2500,0,0,1,1,1000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Troll - lvl <1> Zuni - Trigger, wait 3 - 4 secs, then say first phrase"),
(@ENTRY,@SOURCETYPE,1,0,60,0,100,1,700,800,0,0,53,1,3798800,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Troll - lvl <1> Zuni - After short period, start running to camp"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,1,13000,13000,0,0,1,2,500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Troll - lvl <1> Zuni - after 13 seconds, say second phrase"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,1,2,37988,0,0,44,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Troll - lvl <1> Zuni - On last waypoint, say second phrase");

DELETE FROM `waypoints` WHERE `entry` = '3798800';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(3798800, 1, -1171.6, -5275.5, 0.875105, 'lvl <1> Zuni Running to Training Grounds'),
(3798800, 2, -1170.57, -5283.05, 1.24778, 'lvl <1> Zuni Running to Training Grounds'),
(3798800, 3, -1169.18, -5295.41, 3.89082, 'lvl <1> Zuni Running to Training Grounds'),
(3798800, 4, -1170.49, -5308.3, 8.49512, 'lvl <1> Zuni Running to Training Grounds'),
(3798800, 5, -1171.77, -5321.09, 12.2087, 'lvl <1> Zuni Running to Training Grounds'),
(3798800, 6, -1172.98, -5333.17, 14.4536, 'lvl <1> Zuni Running to Training Grounds'),
(3798800, 7, -1168.9, -5343.4, 15.1187, 'lvl <1> Zuni Running to Training Grounds'),
(3798800, 8, -1165.36, -5355.14, 14.6408, 'lvl <1> Zuni Running to Training Grounds'),
(3798800, 9, -1164.11, -5364.4, 14.5861, 'lvl <1> Zuni Running to Training Grounds'),
(3798800, 10, -1163.89, -5374.46, 12.6836, 'lvl <1> Zuni Running to Training Grounds'),
(3798800, 11, -1166.16, -5386.9, 12.0185, 'lvl <1> Zuni Running to Training Grounds');

DELETE FROM `waypoints` WHERE `entry` = 39062;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(39062, 1, -1150.38, -5531.23, 8.1, 'Darkspear Jailor WP'),
(39062, 2, -1159.76, -5530.88, 11.95, 'Darkspear Jailor WP');

UPDATE `creature` SET `spawntimesecs`=60 WHERE  `guid`=142383;
UPDATE `creature` SET `spawntimesecs`=60 WHERE  `guid`=142312;

-- Darkspear Jailor
SET @ENTRY := 39062;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,62,0,100,0,10974,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1"),
(@ENTRY,@SOURCETYPE,2,0,1,1,100,1,500,500,0,0,53,0,39062,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start WP"),
(@ENTRY,@SOURCETYPE,3,0,40,1,100,1,1,0,0,0,9,0,0,0,0,0,0,14,48543,201968,0,0.0,0.0,0.0,0.0,"On WP Reached - Open Cage"),
(@ENTRY,@SOURCETYPE,5,0,40,1,100,1,1,0,0,0,45,0,1,0,0,0,0,11,38142,25,0,0.0,0.0,0.0,0.0,"Set Data 1 to Trapped Creature"),
(@ENTRY,@SOURCETYPE,6,0,40,1,100,0,2,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Force Despawn - Jailor"),
(@ENTRY,@SOURCETYPE,7,0,62,0,100,0,10974,0,0,0,33,39062,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Close Gossip - Credit 1"),
(@ENTRY,@SOURCETYPE,8,0,62,0,100,0,10974,0,0,0,12,38142,5,0,0,0,0,8,0,0,0,-1150.49,-5519.39,11.95,4.71,"Spawn Creature"),
(@ENTRY,@SOURCETYPE,9,0,62,0,100,0,10974,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Remove Gossip Flag");

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
(@ENTRY,@SOURCETYPE,4,0,6,0,100,0,0,0,0,0,70,0,0,0,0,0,0,10,142394,39062,0,0.0,0.0,0.0,0.0,"On Death - Spawn Jailor");

-- Vol'jin
SET @ENTRY := 3896600;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,1,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,0,1,100,0,0,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Set Event Phase 2"),
(@ENTRY,@SOURCETYPE,2,0,0,2,100,0,500,500,0,0,66,0,0,0,0,0,0,20,202434,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Change Orientation (to gameobject)."),
(@ENTRY,@SOURCETYPE,3,0,0,2,100,0,500,500,0,0,5,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Emote."),
(@ENTRY,@SOURCETYPE,4,0,0,2,100,0,500,500,0,0,1,0,1000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Say 1."),
(@ENTRY,@SOURCETYPE,5,0,0,2,100,0,1000,1000,0,0,11,73169,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Cast Rites of Vision (Visual)."),
(@ENTRY,@SOURCETYPE,6,0,0,2,100,0,5000,5000,0,0,12,38938,3,120000,0,0,0,8,0,0,0,-1321.56,-5610.44,25.0887,2.51048,"Vol'jin; Summon npc Vision of Garrosh Hellscream."),
(@ENTRY,@SOURCETYPE,7,0,0,2,100,0,1500,1500,0,0,1,0,1000,0,0,0,0,19,38938,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Say 2. (Vision of Garrosh Hellscream)"),
(@ENTRY,@SOURCETYPE,8,0,0,2,100,0,1000,1000,0,0,12,38953,3,115000,0,0,0,8,0,0,0,-1324.21,-5608.34,25.0905,5.59238,"Vol'jin; Summon npc Vision of Vol'jin."),
(@ENTRY,@SOURCETYPE,9,0,0,2,100,0,1000,1000,0,0,9,0,0,0,0,0,0,20,202434,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Active gobject Rites of Vision."),
(@ENTRY,@SOURCETYPE,10,0,0,2,100,0,10500,10500,0,0,1,0,1000,0,0,0,0,19,38953,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Say 3. (Vision of Vol'jin)"),
(@ENTRY,@SOURCETYPE,11,0,0,2,100,0,10500,10500,0,0,1,1,1000,0,0,0,0,19,38953,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Say 4. (Vision of Vol'jin)"),
(@ENTRY,@SOURCETYPE,12,0,0,2,100,0,7000,7000,0,0,1,1,1000,0,0,0,0,19,38938,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Say 5. (Vision of Garrosh Hellscream)"),
(@ENTRY,@SOURCETYPE,13,0,0,2,100,0,10000,10000,0,0,1,2,1000,0,0,0,0,19,38953,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Say 6. (Vision of Vol'jin)"),
(@ENTRY,@SOURCETYPE,14,0,0,2,100,0,9500,9500,0,0,1,2,1000,0,0,0,0,19,38938,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Say 7. (Vision of Garrosh Hellscream)"),
(@ENTRY,@SOURCETYPE,15,0,0,2,100,0,15000,15000,0,0,1,3,1000,0,0,0,0,19,38953,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Say 8. (Vision of Vol'jin)"),
(@ENTRY,@SOURCETYPE,16,0,0,2,100,0,16000,16000,0,0,1,4,1000,0,0,0,0,19,38953,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Say 9. (Vision of Vol'jin)"),
(@ENTRY,@SOURCETYPE,17,0,0,2,100,0,14000,14000,0,0,1,5,1000,0,0,0,0,19,38953,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Say 10. (Vision of Vol'jin)"),
(@ENTRY,@SOURCETYPE,18,0,0,2,100,0,17000,17000,0,0,1,3,1000,0,0,0,0,19,38938,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Say 11. (Vision of Garrosh Hellscream)"),
(@ENTRY,@SOURCETYPE,19,0,0,2,100,0,3000,3000,0,0,1,6,1000,0,0,0,0,19,38953,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Say 12. (Vision of Vol'jin)"),
(@ENTRY,@SOURCETYPE,20,0,0,2,100,0,0,0,0,0,9,0,0,0,0,0,0,20,202434,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Deactive gobject Rites of Vision."),
(@ENTRY,@SOURCETYPE,21,0,0,2,100,0,500,500,0,0,66,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Change Orientation (to home)."),
(@ENTRY,@SOURCETYPE,22,0,0,2,100,0,1000,1000,0,0,28,73169,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Remove aura Rites of Vision (Visual)."),
(@ENTRY,@SOURCETYPE,23,0,0,2,100,0,2000,2000,0,0,1,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Say 13."),
(@ENTRY,@SOURCETYPE,24,0,0,2,100,0,9000,9000,0,0,1,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Say 14."),
(@ENTRY,@SOURCETYPE,25,0,0,2,100,0,16000,16000,0,0,1,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Say 15."),
(@ENTRY,@SOURCETYPE,26,0,0,2,100,0,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Vol'jin; Set Event Phase 1");

DELETE FROM `creature_text` WHERE `entry`IN(38938,38953,45228,45196,37988);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(38938,0,1,'Don\'t talk back to me, troll. You know who was left in charge here. Haven\'t you stopped to ask yourself why Thrall chose me instead of you?',12,0,100,25,0,20508,'Vol\'jin - Vision - Quote'),
(38938,1,1,'You are lucky that I don\'t gut you right here, whelp. You are foolish to think that you can speak to your Warchief in such ways.',12,0,100,5,0,20512,'Vol\'jin - Vision - Quote'),
(38938,2,1,'And what exactly do you think that you are going to do about it?  Your threats are hollow.  Go slink away with the rest of your kind to the slums, I will endure your filth in my throne room no longer.',12,0,100,1,0,20509,'Vol\'jin - Vision - Quote'),
(38938,3,1,'You have sealed your fate, troll.',12,0,100,1,0,20510,'Vol\'jin - Vision - Quote'),
(38953,0,1,'Dere be no question why, Garrosh. He gave ya tha title because ya be Grom\'s son and because tha people be wantin\' a war hero.',12,0,100,5,0,20098,'Vol\'jin - Vision - Quote'),
(38953,1,1,'I tink ya be even more like ya father den ya thought, even witout da demon blood.',12,0,100,1,0,20099,'Vol\'jin - Vision - Quote'),
(38953,2,1,'Ya be no Warchief of mine. Ya\'ve not earned my respect and I\'ll not be seein\' tha Horde destroyed by ya foolish thirst for war.',12,0,100,1,0,20100,'Vol\'jin - Vision - Quote'),
(38953,3,1,'I know exactly what I\'ll be doin\' about it, son of Hellscream. I\'ll watch and wait as ya people slowly become aware of ya ineptitude. I\'ll laugh as dey grow ta despise ya as I do.',12,0,100,1,0,20101,'Vol\'jin - Vision - Quote'),
(38953,4,1,'And when tha time comes dat ya failure is complete and ya "power" is meaningless, I will be dere to end ya rule swiftly and silently.',12,0,100,1,0,20102,'Vol\'jin - Vision - Quote'),
(38953,5,1,'Ya will spend ya reign glancin\' over ya shoulda and fearin\' tha shadows, for when tha time comes and ya blood be slowly drainin\' out, ya will know exactly who fired tha arrow dat pierced ya black heart.',12,0,100,1,0,20103,'Vol\'jin - Vision - Quote'),
(38953,6,1,'And you yours, "Warchief."',12,0,100,1,0,20104,'Vol\'jin - Vision - Quote'),
(45228,0,0,'Ready then? Let\'s get a move on! Try and keep up, $n',12,0,100,0,0,0,'Comment'),
(45228,1,0,'Onward, brothers and sisters!',12,0,100,0,0,0,'Comment'),
(45228,2,0,'What\'s this then?',12,0,100,0,0,0,'Comment'),
(45228,3,0,'BOMB! IT\'S A TRAP! RUN!',14,0,100,0,0,0,'Comment'),
(45228,4,0,'Remember this day as the day the Forteski saved your hide. Now run! Get back to Sylvanas!',12,0,100,0,0,0,'Comment'),
(45196,0,0,'ORC NEEDS PEANUTS!',12,0,100,0,2,0,'Comment'),
(45196,0,1,'Crush and clobber! Bobber slobber!',12,0,100,0,2,0,'Comment'),
(45196,0,2,'HELL OF A KICK TO THAT ALE!',12,0,100,0,2,0,'Comment'),
(45196,0,3,'AAAAAAAAAALLLLLLLLLLEEEEEEEEE!!! ARRRRRRRRGGHHH!',12,0,100,0,2,0,'Comment'),
(45196,0,4,'I may or may not have pissed myself.',12,0,100,0,2,0,'Comment'),
(45196,0,5,'My power has returned!',12,0,100,0,2,0,'Comment'),
(37988,1,0,'Ya, mon. Let\'s crack some tiki target skulls!',12,0,100,0,0,21366,'lvl <1> Zuni Quote'),
(37988,2,1,'Ya trainer should be somewhere in the grounds \'ere. I\'ll catch you lata, mon.',12,0,100,397,0,21367,'lvl <1> Zuni Quote');

DELETE FROM creature WHERE id = '38938';
DELETE FROM creature WHERE id = '38953';

UPDATE `quest_template` SET `RequiredNpcOrGo1`=45228, `RequiredNpcOrGoCount1`=1 WHERE  `Id`=27195;

DELETE FROM `waypoints` WHERE `entry` = '45228';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(45228, 1, 375.55, 1082.09, 106.41, 'Master Forteski'),
(45228, 2, 386.92, 1046.07, 106.28, 'Master Forteski'),
(45228, 3, 413.16, 1033.53, 106.83, 'Master Forteski'),
(45228, 4, 409.88, 1009.89, 107.50, 'Master Forteski');

UPDATE `gameobject` SET `spawntimesecs`=60 WHERE  `guid`=19601;
UPDATE `gameobject` SET `spawntimesecs`=60 WHERE  `guid`=19624;

UPDATE `gameobject` SET `phaseMask`=32768 WHERE  `guid`=19624;
UPDATE `gameobject` SET `phaseMask`=32768 WHERE  `guid`=19601;

UPDATE `creature` SET `spawntimesecs`= 60 WHERE `id`= 45225;
UPDATE `creature` SET `spawntimesecs`= 60 WHERE `id`= 45228;
UPDATE `creature` SET `spawntimesecs`= 60 WHERE `id`= 45236;

-- Veteran Forsaken Trooper
SET @ENTRY := 45225;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,53,1,45228,0,27195,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Set Data - Start Follow Master Forteski"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,41,24000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Force Despawn - 24 secs");

-- Master Forteski
SET @ENTRY := 45228;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,27195,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accepted - Start Event"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,45228,0,0,1,1,1500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk - 1"),
(@ENTRY,@SOURCETYPE,2,0,52,0,100,0,1,45228,0,0,53,1,45228,0,27195,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Text 0 - Start WP"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,1,0,0,0,45,0,1,0,0,0,0,11,45225,20,0,0.0,0.0,0.0,0.0,"On Text 1 - Set Data 1 to Guards"),
(@ENTRY,@SOURCETYPE,4,0,40,0,100,0,4,0,0,0,1,2,4500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Last WP - Talk 2"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,2,45228,0,0,45,0,1,0,0,0,0,11,45236,50,0,0.0,0.0,0.0,0.0,"On Last WP - Set Data 1 to Bloodfang"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,2,45228,0,0,1,3,2500,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Talk 3"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,3,45228,0,0,1,4,2500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Talk 4"),
(@ENTRY,@SOURCETYPE,8,0,52,0,100,0,4,45228,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Die - Self"),
(@ENTRY,@SOURCETYPE,9,0,52,0,100,0,4,45228,0,0,37,0,0,0,0,0,0,11,45225,40,0,0.0,0.0,0.0,0.0,"Die - Creatures");

-- Packleader Ivar Bloodfang
SET @ENTRY := 45236;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,37,0,100,0,0,0,0,0,47,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On AI Init - Set Visible Off"),
(@ENTRY,@SOURCETYPE,1,0,38,0,100,0,0,1,0,0,47,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Set Visibile ON"),
(@ENTRY,@SOURCETYPE,2,0,38,0,100,0,0,1,0,0,1,0,2500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Talk 0"),
(@ENTRY,@SOURCETYPE,3,0,52,0,100,0,0,0,0,0,9,0,0,0,0,0,0,14,19601,205271,0,0.0,0.0,0.0,0.0,"On Text - 0 - Activate bombs"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,0,0,0,0,9,0,0,0,0,0,0,14,19624,205271,0,0.0,0.0,0.0,0.0,"On Text - 0 - Activate bombs"),
(@ENTRY,@SOURCETYPE,5,0,52,0,100,0,0,0,0,0,33,45228,0,0,0,0,0,18,80,0,0,0.0,0.0,0.0,0.0,"On Text 0 - Quest Complete"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,0,45236,0,0,11,66016,4,0,0,0,0,11,0,30,0,0.0,0.0,0.0,0.0,"Cast Explosion"),
(@ENTRY,@SOURCETYPE,7,0,52,0,100,0,0,45236,0,0,41,2500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Explosion - Force Despawn");

DELETE FROM `spell_script_names` WHERE `spell_id` = 70874;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
(70874, 'spell_bloodtalon_whistle');

UPDATE `creature` SET `spawntimesecs`= 60 WHERE `id`= 37960;
UPDATE `creature_template` SET `ScriptName`='npc_wounded_outrunner' WHERE `entry`= 44857;
UPDATE `creature_template` SET `gossip_menu_id`= 0 WHERE  `entry`= 43010;
UPDATE `creature_template` SET `ScriptName`='npc_wounded_infantry' WHERE `entry`= 42501;
UPDATE `creature_template` SET `gossip_menu_id`= 0 WHERE  `entry`= 35870;
UPDATE `creature_template` SET `ScriptName`='npc_wounded_sentinel' WHERE `entry`= 44617;

UPDATE `creature_template` SET `spell1`=84575 WHERE  `entry`=45263;
UPDATE `creature_template` SET `ScriptName`='npc_horde_cannon_lordamere' WHERE  `entry`=45263;
UPDATE `creature_template` SET `flags_extra`=2 WHERE  `entry`=45263;
UPDATE `creature_template` SET `InhabitType`=7, `HoverHeight`=1 WHERE  `entry`=45270;

DELETE FROM `gameobject` WHERE `id` = 205350;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(778999, 205350, 0, 1, 2, 709.175, 964.656, 34.7558, 4.67748, 0, 0, 0, 1, 120, 255, 1);

-- Todo: find correct trigger and remove this hack!
DELETE FROM `creature_template` WHERE `entry` = 144954;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
(144954, 0, 0, 0, 0, 0, 999, 0, 0, 0, '[QT - The Waters Run Red]', '', '', 0, 1, 1, 0, 0, 35, 35, 0, 1, 1, 1, 0, 1007, 1354, 0, 1571, 1, 2000, 2200, 1, 0, 2048, 8, 0, 0, 0, 0, 758, 1062, 220, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 128, 'npc_hillsbrad_worgens_trigger', 15595);

UPDATE `creature_template` SET `faction_A`=16, `faction_H`=16 WHERE `entry`=144954;
update creature set phasemask = '2' where id = '45263';
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '45263';
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`) VALUES (45263, 46598, 1);
UPDATE `creature_template` SET `InhabitType`=1 WHERE `entry`=45263;
-- Hack
UPDATE `creature_template` SET `speed_walk` =0.001, `speed_run`= 0.001 WHERE `entry`= 45263;

-- Hillsbrad Worgen
SET @ENTRY := 45270;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,1,0,6,0,100,0,0,0,0,0,75,84563,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death add self blood aura"),
(@ENTRY,@SOURCETYPE,2,0,37,0,100,0,0,0,0,0,46,200,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On AI Init - Move Forward"),
(@ENTRY,@SOURCETYPE,3,0,37,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On AI Init - Set Passive"),
(@ENTRY,@SOURCETYPE,4,0,37,0,100,0,0,0,0,0,61,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On AI Init - Set Swim"),
(@ENTRY,@SOURCETYPE,5,0,37,0,100,0,0,0,0,0,44,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phasemask 2"),
(@ENTRY,@SOURCETYPE,6,0,60,0,100,0,1000,1000,0,0,41,24000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Force Despawn");
