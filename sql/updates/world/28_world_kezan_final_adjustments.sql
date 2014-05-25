UPDATE `npc_text` SET `text0_1`='Hey there, boss. I trust that you\'re enjoying your new promotion?$B$BWe all think that you\'re the one who\'s going to finally be able to replace that stinky ol\' Gallywix and take the title of Trade $g Prince : Princess;. But you didn\'t hear that from me!$B$BWe have a lot to do and very little time. Hope you\'re ready!' WHERE `ID`=14590;
UPDATE `npc_text` SET `text0_1`='$G Mr. : Ms.; $N, so very good to see you.$B$BI hope that you are enjoying the Kaja\'Cola marketing campaign. We\'re planning a massive set of explosions for the next phase of the campaign. That always goes over well with our target demographic.' WHERE `ID`=14657;
UPDATE `npc_text` SET `text0_0`='YOU!$B$BYou think you can just waltz in here and take my spot? Think again, $g boy : girl;!$B$BI\'ve heard the whispering in the boardroom. The people you\'ve surrounded yourself with at headquarters are all boot-licking sycophants who will do anything to get ahead. I should know... I hired all of them.$B$BYour meteoric rise to power is a fluke, and I\'m fully prepared to knock you down a gear or two! Watch your step, $N. Who knows when you\'re going to need me on your side?' WHERE `ID`=15807;
UPDATE `quest_template` SET `OfferRewardText`='You lost your Keys to the Hot Rod somewhere?$B$BNo problem, boss. I always like to keep a spare set handy just in case.' WHERE `Id`=28607;
UPDATE `quest_template` SET `PrevQuestId`='14071' WHERE `Id`=28607;

DELETE FROM `creature_text` WHERE `entry`=34830;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(34830,0,0,'Oops, break\'s over.',12,0,100,0,0,0,'Comment'),
(34830,0,1,'Don\'t tase me, mon!',12,0,100,0,0,0,'Comment'),
(34830,0,2,'I report you to HR!',12,0,100,0,0,0,'Comment'),
(34830,0,3,'Work was bettah in da Undermine!',12,0,100,0,0,0,'Comment'),
(34830,0,4,'I\'m going. I\'m going!',12,0,100,0,0,0,'Comment'),
(34830,0,5,'Sorry, mon. It won\'t happen again.',12,0,100,0,0,0,'Comment'),
(34830,0,6,'What I doin\' wrong? Don\'t I get a lunch and two breaks a day, mon?',12,0,100,0,0,0,'Comment'),
(34830,0,7,'Ouch! Dat hurt!',12,0,100,0,0,0,'Comment');

DELETE FROM `spell_script_names` WHERE `spell_id` = '66299';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(66299, 'spell_radio_kezan');

UPDATE `creature_template` SET `ScriptName`='npc_hot_rod' WHERE `entry`=34840;

DELETE FROM `spell_script_names` WHERE `spell_id` = '66298';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(66298, 'spell_honk_horn');

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '14071';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(49416, 4737, 14071, 14071, 1, 10);

DELETE FROM `spell_area` WHERE `spell` = '49417' AND `quest_start` = '14071';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(49417, 4737, 14071, 14071, 1, 10);

DELETE FROM `spell_area` WHERE `spell` = '60922' AND `quest_start` = '14071';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(60922, 4737, 14071, 14071, 1, 10);

DELETE FROM `spell_target_position` WHERE `id` IN (66600, 66597, 66599);
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(66600, 648, -8507.65, 1342.84, 101.77, 6.26),
(66597, 648, -8068.12, 1482.03, 9.01, 3.59),
(66599, 648, -8179.47, 1321.38, 27.60, 5.25);

UPDATE `creature_template` SET `ScriptName`='npc_ace_rwmh' WHERE `entry`=34957;
UPDATE `creature_template` SET `ScriptName`='npc_gobber_rwmh' WHERE `entry`=34958;
UPDATE `creature_template` SET `ScriptName`='npc_izzy_rwmh' WHERE `entry`=34959;

DELETE FROM `creature_text` WHERE `entry`=34874;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(34874,0,0,'Ooh, I think you\'re gonna like this, boss!',12,0,100,0,0,0,'Comment'),
(34874,1,0,'Use the Keys to the Hot Rod |TInterface\\Icons\\inv_misc_key_12.blp:32|t to get into your car. Pick up your friends, Izzy, Ace, and Gobber.',42,0,100,0,0,0,'Comment'),
(34874,2,0,'There they are! Okay, you three make sure that you help $g out today. $G got a lot of stuff to take care of before the party!',12,0,100,0,0,0,'Comment');

-- Megs Dreadshredder
SET @ENTRY := 34874;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,14071,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,34874,0,0,1,1,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,2,0,20,0,100,0,14071,0,0,0,1,2,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Talk 2"),
(@ENTRY,@SOURCETYPE,3,0,20,0,100,0,14071,0,0,0,85,84940,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Rewarded - Despawn old friends");

DELETE FROM `creature_text` WHERE `entry`=35075;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(35075, 0, 1, 'You will hear from my lawyer!', 12, 0, 100, 5, 0, 18500, 'Kezan Citizen'),
(35075, 0, 2, 'Fits on but where your outward journey!', 12, 0, 100, 92, 0, 18500, 'Kezan Citizen'),
(35075, 0, 3, 'You will hear from my lawyer!', 12, 0, 100, 25, 0, 18500, 'Kezan Citizen'),
(35075, 0, 4, 'You are a public nuisance, $N!', 12, 0, 100, 5, 0, 1411, 'Kezan Citizen'),
(35075, 0, 5, 'Ouch!', 12, 0, 100, 92, 0, 0, 'Kezan Citizen'),
(35075, 0, 6, 'Fits on but where your outward journey!', 12, 0, 100, 92, 0, 0, 'Kezan Citizen'),
(35075, 0, 7, 'Learn kindly, how to drive, you madman!', 12, 0, 100, 92, 0, 18500, 'Kezan Citizen'),
(35075, 0, 8, 'You are a public nuisance, $N!', 12, 0, 100, 1, 0, 18500, 'Kezan Citizen'),
(35075, 0, 9, 'The Trade Prince is informed of his, $N!', 12, 0, 100, 5, 0, 18500, 'Kezan Citizen'),
(35075, 0, 10, 'Ouch!', 12, 0, 100, 5, 0, 18500, 'Kezan Citizen'),
(35075, 0, 11, 'You are a public nuisance, $N!', 12, 0, 100, 5, 0, 18500, 'Kezan Citizen'),
(35075, 0, 12, 'Fits on but where your outward journey!', 12, 0, 100, 5, 0, 18500, 'Kezan Citizen'),
(35075, 0, 13, 'Learn kindly, how to drive, you madman!', 12, 0, 100, 5, 0, 18500, 'Kezan Citizen'),
(35075, 0, 14, 'I\'ll get you, $N!', 12, 0, 100, 5, 0, 12924, 'Kezan Citizen');

-- Kezan Citizen
SET @ENTRY := 35075;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,66301,1,0,0,1,0,7500,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,52,0,100,0,0,35075,0,0,24,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Evade");

DELETE FROM conditions WHERE SourceEntry = '93599' AND ConditionValue2 = '46963';
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, SourceId, ElseGroup, ConditionTypeOrReference, ConditionTarget, ConditionValue1, ConditionValue2, ConditionValue3, NegativeCondition, ErrorType, ScriptName, Comment) VALUES
(13, 7, 93599, 0, 0, 31, 0, 3, 46963, 0, 0, 0, '', 'Hot Rod Knockback - Only on Citizens');

UPDATE `creature` SET `spawndist`=10, `MovementType`=1 WHERE `guid`=834768;
UPDATE `creature_template` SET `speed_walk`=0.8, `speed_run`=2 WHERE `entry`=34840;

DELETE FROM `spell_area` WHERE `spell` = '66644' AND `quest_start` = '14071';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(66644, 4737, 14071, 14070, 1, 64, 11);

DELETE FROM `spell_area` WHERE `spell` = '66645' AND `quest_start` = '14071';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(66645, 4737, 14071, 14070, 1, 64, 11);

DELETE FROM `spell_area` WHERE `spell` = '66646' AND `quest_start` = '14071';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(66646, 4737, 14071, 14070, 1, 64, 11);

DELETE FROM `spell_script_names` WHERE `spell_id` IN (66644, 66645, 66646);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(66644, 'spell_summon_generic_controller'),
(66645, 'spell_summon_generic_controller'),
(66646, 'spell_summon_generic_controller');

UPDATE `creature` SET `spawntimesecs`=60 WHERE `id` IN (34835, 34878, 34877, 34876, 35200, 35234, 35294);
UPDATE `creature_template` SET `mindmg`=4, `maxdmg`=6 WHERE `entry` IN (34835, 34878, 34877, 34876, 35200, 35234, 35294);
UPDATE `creature` SET `spawndist`=10, `MovementType`=1 WHERE `guid`=834659;
UPDATE `gossip_menu_option` SET `option_id`=5, `npc_option_npcflag`=16 WHERE `menu_id`=10683 AND `id`=0;
UPDATE `quest_template` SET `RequiredItemId1`=46856, `RequiredItemCount1`=1 WHERE `Id`=14009;

-- Injured Employee
SET @ENTRY := 48305;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,2061,2,0,0,33,44175,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit");

UPDATE `creature_template` SET `mindmg`=2, `maxdmg`=4, `maxlevel`=2, `minlevel`=2, `type_flags`=4096, `unit_flags`=32776, `unit_flags2`=33556480 WHERE `entry` IN (34957, 34958, 34959);
UPDATE `creature_template_addon` SET `auras`='81355 75773' WHERE `entry`=34835;
UPDATE `creature_template_addon` SET `auras`='81355' WHERE `entry`=34876;
UPDATE `creature_template_addon` SET `auras`='81355 76136' WHERE `entry`=34877;
UPDATE `creature_template_addon` SET `auras`='81355' WHERE `entry`=34878;

DELETE FROM `creature_text` WHERE `entry`=34668;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(34668,0,0,'Ace, Izzy, Gobber, you three make sure you tag along with $n and help $g take care of those deadbeats!',12,0,100,0,0,0,'Comment'),
(34668,1,0,'You better get upstairs pronto, boss. Trade Prince Gallywix is waiting for you.',12,0,100,0,0,0,'Comment');

-- Sassy Hardwrench
SET @ENTRY := 34668;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,14070,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,20,0,100,0,14070,0,0,0,85,84940,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Reward - Despawn Summons"),
(@ENTRY,@SOURCETYPE,2,0,19,0,100,0,14116,0,0,0,1,0,5000,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 1");

DELETE FROM `creature_text` WHERE `entry`=34835;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(34835,0,0,'I was just comin\' to see you. Honest!',12,0,100,0,0,0,'Comment'),
(34835,1,0,'Darn, you got me!',12,0,100,0,0,0,'Comment');

-- Bruno Flameretardant
SET @ENTRY := 34835;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,2,0,2,0,100,1,0,2,0,0,1,1,2500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 2% - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,2,0,100,1,0,2,0,0,18,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 2% - Set Flags"),
(@ENTRY,@SOURCETYPE,4,0,2,0,100,1,0,2,0,0,5,20,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 2% - Beg"),
(@ENTRY,@SOURCETYPE,5,0,2,0,100,1,0,2,0,0,33,34835,0,0,0,0,0,18,20,0,0,0.0,0.0,0.0,0.0,"On Health 2% - Quest Credit"),
(@ENTRY,@SOURCETYPE,6,0,2,0,100,0,0,2,0,0,24,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 2% - Evade"),
(@ENTRY,@SOURCETYPE,7,0,7,0,100,0,0,0,0,0,19,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Remove Flags");

-- Frankie Gearslipper
SET @ENTRY := 34876;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,2,0,2,0,100,1,0,2,0,0,1,1,2500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 2% - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,2,0,100,1,0,2,0,0,18,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 2% - Set Flags"),
(@ENTRY,@SOURCETYPE,4,0,2,0,100,1,0,2,0,0,5,20,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 2% - Beg"),
(@ENTRY,@SOURCETYPE,5,0,2,0,100,1,0,2,0,0,33,34876,0,0,0,0,0,18,20,0,0,0.0,0.0,0.0,0.0,"On Health 2% - Quest Credit"),
(@ENTRY,@SOURCETYPE,6,0,2,0,100,0,0,2,0,0,24,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 2% - Evade"),
(@ENTRY,@SOURCETYPE,7,0,7,0,100,0,0,0,0,0,19,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Remove Flags"),
(@ENTRY,@SOURCETYPE,8,0,4,0,100,1,0,0,0,0,11,75775,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Throw Gears on Aggro");

DELETE FROM `creature_text` WHERE `entry`=34876;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(34876,0,0,'Oh no you didn\'t!',12,0,100,0,0,0,'Comment'),
(34876,1,0,'What? Fine, fine... I\'ll pay my protection moolah to your goons!',12,0,100,0,0,0,'Comment');

-- Jack the Hammer
SET @ENTRY := 34877;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,2,0,2,0,100,1,0,2,0,0,1,1,2500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 2% - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,2,0,100,1,0,2,0,0,18,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 2% - Set Flags"),
(@ENTRY,@SOURCETYPE,4,0,2,0,100,1,0,2,0,0,5,20,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 2% - Beg"),
(@ENTRY,@SOURCETYPE,5,0,2,0,100,1,0,2,0,0,33,34877,0,0,0,0,0,18,20,0,0,0.0,0.0,0.0,0.0,"On Health 2% - Quest Credit"),
(@ENTRY,@SOURCETYPE,6,0,2,0,100,0,0,2,0,0,24,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 2% - Evade"),
(@ENTRY,@SOURCETYPE,7,0,7,0,100,0,0,0,0,0,19,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Remove Flags"),
(@ENTRY,@SOURCETYPE,8,0,4,0,100,1,0,0,0,0,11,75775,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Throw Gears on Aggro"),
(@ENTRY,@SOURCETYPE,9,0,0,0,100,0,5000,7700,12300,16700,11,75986,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Knockback"),
(@ENTRY,@SOURCETYPE,10,0,1,0,100,1,500,1000,0,0,11,76136,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Acidic Sweat on Spawn");

DELETE FROM `creature_text` WHERE `entry`=34877;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(34877,0,0,'<Jack grunts something about the hammer being his weapon... you think.>',12,0,100,0,0,0,'Comment'),
(34877,1,0,'Jack the Hammer grunts and gives up, clearly beaten.',16,0,100,0,0,0,'Comment');

-- Sudsy Magee
SET @ENTRY := 34878;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible"),
(@ENTRY,@SOURCETYPE,2,0,2,0,100,1,0,2,0,0,1,1,2500,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 2% - Talk 1"),
(@ENTRY,@SOURCETYPE,3,0,2,0,100,1,0,2,0,0,18,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 2% - Set Flags"),
(@ENTRY,@SOURCETYPE,4,0,2,0,100,1,0,2,0,0,5,20,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 2% - Beg"),
(@ENTRY,@SOURCETYPE,5,0,2,0,100,1,0,2,0,0,33,34878,0,0,0,0,0,18,20,0,0,0.0,0.0,0.0,0.0,"On Health 2% - Quest Credit"),
(@ENTRY,@SOURCETYPE,6,0,2,0,100,0,0,2,0,0,24,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 2% - Evade"),
(@ENTRY,@SOURCETYPE,7,0,7,0,100,0,0,0,0,0,19,768,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Evade - Remove Flags"),
(@ENTRY,@SOURCETYPE,8,0,4,0,100,1,0,0,0,0,11,75775,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Throw Gears on Aggro"),
(@ENTRY,@SOURCETYPE,9,0,0,0,100,0,5000,7700,12300,16700,11,75986,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Knockback"),
(@ENTRY,@SOURCETYPE,10,0,1,0,100,1,500,1000,0,0,11,76136,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Acidic Sweat on Spawn"),
(@ENTRY,@SOURCETYPE,11,0,4,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 on Aggro"),
(@ENTRY,@SOURCETYPE,12,0,4,1,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving on Aggro"),
(@ENTRY,@SOURCETYPE,13,0,4,1,100,1,0,0,0,0,11,9672,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast bolt on Aggro"),
(@ENTRY,@SOURCETYPE,14,0,9,1,100,0,5,40,3400,4700,11,9672,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast bolt on Range"),
(@ENTRY,@SOURCETYPE,15,0,0,1,100,0,3400,4700,3400,4700,11,9672,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast bolt"),
(@ENTRY,@SOURCETYPE,16,0,9,1,100,1,40,100,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving when not in bolt Range"),
(@ENTRY,@SOURCETYPE,17,0,9,1,100,1,10,15,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving at 15 Yards"),
(@ENTRY,@SOURCETYPE,18,0,9,1,100,1,0,5,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving when not in bolt Range"),
(@ENTRY,@SOURCETYPE,19,0,9,1,100,1,5,40,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving when in bolt Range"),
(@ENTRY,@SOURCETYPE,20,0,3,1,100,1,0,15,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 2 at 15% Mana"),
(@ENTRY,@SOURCETYPE,21,0,3,2,100,1,0,15,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving at 15% Mana"),
(@ENTRY,@SOURCETYPE,22,0,3,2,100,1,30,100,100,100,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 When Mana is above 30%"),
(@ENTRY,@SOURCETYPE,23,0,0,0,100,0,9800,11000,17600,25400,11,75761,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Bubble Blast");

DELETE FROM `creature_text` WHERE `entry`=34878;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(34878,0,0,'I\'m tryin\' to run a business here!',12,0,100,0,0,0,'Comment'),
(34878,1,0,'Not the face, not the face!',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=37106;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(37106,0,0,'Get into that shredder and win the game. The Bilgewater Cartel\'s counting on you!',12,0,100,0,0,0,'Comment');

-- Coach Crosscheck
SET @ENTRY := 37106;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,0,100,0,24502,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Quest Accept - Talk 0");

UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=24502;

DELETE FROM `spell_area` WHERE `spell` = '90161' AND `quest_start` = '24502';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(90161, 4822, 24502, 1, 8, 11);

DELETE FROM `creature_text` WHERE `entry`=37179;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(37179,0,0,'Throw your Footbombs at those Steamwheedle Sharks!',42,0,100,0,0,0,'Comment');

-- Deletes creature Kezan Citizen (id: 35063, guid: 834684) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834684; DELETE FROM creature_addon WHERE guid = 834684;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834683) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834683; DELETE FROM creature_addon WHERE guid = 834683;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834681) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834681; DELETE FROM creature_addon WHERE guid = 834681;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834682) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834682; DELETE FROM creature_addon WHERE guid = 834682;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834677) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834677; DELETE FROM creature_addon WHERE guid = 834677;

-- Deletes creature Kezan Citizen (id: 35075, guid: 834725) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834725; DELETE FROM creature_addon WHERE guid = 834725;

-- Deletes creature Kezan Citizen (id: 35075, guid: 834722) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834722; DELETE FROM creature_addon WHERE guid = 834722;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834674) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834674; DELETE FROM creature_addon WHERE guid = 834674;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834671) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834671; DELETE FROM creature_addon WHERE guid = 834671;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834672) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834672; DELETE FROM creature_addon WHERE guid = 834672;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834691) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834691; DELETE FROM creature_addon WHERE guid = 834691;

-- Deletes creature Kezan Citizen (id: 35075, guid: 834707) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834707; DELETE FROM creature_addon WHERE guid = 834707;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834689) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834689; DELETE FROM creature_addon WHERE guid = 834689;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834675) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834675; DELETE FROM creature_addon WHERE guid = 834675;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834680) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834680; DELETE FROM creature_addon WHERE guid = 834680;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834670) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834670; DELETE FROM creature_addon WHERE guid = 834670;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834687) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834687; DELETE FROM creature_addon WHERE guid = 834687;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834663) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834663; DELETE FROM creature_addon WHERE guid = 834663;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834666) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834666; DELETE FROM creature_addon WHERE guid = 834666;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834690) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834690; DELETE FROM creature_addon WHERE guid = 834690;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834686) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834686; DELETE FROM creature_addon WHERE guid = 834686;

-- Deletes creature Kezan Citizen (id: 35075, guid: 834704) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834704; DELETE FROM creature_addon WHERE guid = 834704;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834667) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834667; DELETE FROM creature_addon WHERE guid = 834667;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834665) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834665; DELETE FROM creature_addon WHERE guid = 834665;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834676) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834676; DELETE FROM creature_addon WHERE guid = 834676;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834685) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834685; DELETE FROM creature_addon WHERE guid = 834685;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834669) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834669; DELETE FROM creature_addon WHERE guid = 834669;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834688) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834688; DELETE FROM creature_addon WHERE guid = 834688;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834678) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834678; DELETE FROM creature_addon WHERE guid = 834678;

-- Deletes creature Kezan Citizen (id: 35075, guid: 834708) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834708; DELETE FROM creature_addon WHERE guid = 834708;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834673) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834673; DELETE FROM creature_addon WHERE guid = 834673;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834661) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834661; DELETE FROM creature_addon WHERE guid = 834661;

-- Deletes creature Kezan Citizen (id: 35075, guid: 834727) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834727; DELETE FROM creature_addon WHERE guid = 834727;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834664) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834664; DELETE FROM creature_addon WHERE guid = 834664;

-- Deletes creature Kezan Citizen (id: 35063, guid: 834668) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834668; DELETE FROM creature_addon WHERE guid = 834668;

-- Deletes creature Kezan Citizen (id: 35075, guid: 834705) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834705; DELETE FROM creature_addon WHERE guid = 834705;

-- Deletes creature Kezan Citizen (id: 35075, guid: 834706) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834706; DELETE FROM creature_addon WHERE guid = 834706;

-- Deletes creature Kezan Citizen (id: 35075, guid: 834723) in zone: 4737, area: 4822
DELETE FROM `creature` WHERE `guid` = 834723; DELETE FROM creature_addon WHERE guid = 834723;

-- Steamwheedle Shark
SET @ENTRY := 37114;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,8,0,100,0,69993,1,0,0,37,0,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Die"),
(@ENTRY,@SOURCETYPE,1,0,8,0,100,0,69993,1,0,0,33,37114,0,0,0,0,0,23,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit"),
(@ENTRY,@SOURCETYPE,2,0,8,0,100,0,69993,1,0,0,41,3000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Death - Despawn"),
(@ENTRY,@SOURCETYPE,3,0,54,0,100,0,0,0,0,0,69,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Move To Owner"),
(@ENTRY,@SOURCETYPE,4,0,34,0,100,0,8,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Movement Inform - Force Despawn"),
(@ENTRY,@SOURCETYPE,5,0,34,0,100,0,8,0,0,0,51,0,0,0,0,0,0,11,37179,5,0,0.0,0.0,0.0,0.0,"On Movement Inform - Kill Buccaneer");

DELETE FROM `spell_script_names` WHERE `spell_id` = '69987';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(69987, 'spell_despawn_steamwheedle_sharks');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '70015' AND `spell_effect` = '84940';
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES
(70015, 84940, 'Despawn Summons (Friends)');

DELETE FROM `creature_template_addon` WHERE `entry` = '37114';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(37114, 1, '60191');

DELETE FROM `creature_template_addon` WHERE `entry` = '37179';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(37179, 1, '60191');

UPDATE `creature_template` SET `speed_walk`=0.85, `speed_run`=0.85 WHERE `entry`=37114;

DELETE FROM `creature_involvedrelation` WHERE `id` = '37106' AND `quest` = '24502';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(37106, 24502);

UPDATE `creature_template` SET `VehicleId`=579 WHERE `entry`=37213;

DELETE FROM `spell_target_position` WHERE `id` = '70075';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(70075, 648, -8252.96, 1484.39, 41.60, 3.09);

UPDATE `quest_template` SET `Flags`=0, `SourceSpellId`=70075 WHERE `Id`=28414;
UPDATE `creature_template_addon` SET `auras`='81355 89476 49414' WHERE `entry`=37203;

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '28414';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(49416, 4822, 28414, 28414, 1, 8);

UPDATE `creature_template` SET `ScriptName`='npc_deathwing_goal', `minlevel`=88, `maxlevel`=88, `speed_walk`=7, `speed_run`=7, `Health_mod`=500, `InhabitType`=4 WHERE `entry`=48572;

DELETE FROM `spell_script_names` WHERE `spell_id` = '70051';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(70051, 'spell_kick_footbomb_goal');

UPDATE `creature_template` SET `ScriptName`='npc_buccaneer_goal' WHERE `entry`=37213;

DELETE FROM `spell_target_position` WHERE `id` = '66322';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(66322, 648, -8244.43, 1483.49, 100.92, 3.09);

DELETE FROM `creature_template_addon` WHERE `entry` = '48572';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(48572, 1, '60191');

DELETE FROM `creature_text` WHERE `entry`=48572;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(48572,0,0,'The sun has set on this mortal world, fools. Make peace with your end, for the hour of twilight falls!',14,0,100,0,0,23228,'Comment');

UPDATE `creature_template` SET `ScriptName`='npc_buccaneer_roughness' WHERE `entry`=37179;

-- Kezan Citizen
SET @ENTRY := 35063;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,15,0,5000,12500,5000,12500,11,75133,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Throw Cola");

DELETE FROM `script_waypoint` WHERE `entry` = '48572';
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `point_comment`) VALUES
(48572, 1, -8359.96, 1484.56, 227.87, 'Deathwing WP (Goal)'),
(48572, 2, -8562.08, 1487.82, 244.05, 'Deathwing WP (Goal)'),
(48572, 3, -8474.77, 1615.19, 223.93, 'Deathwing WP (Goal)'),
(48572, 4, -8268.77, 1486.66, 71.71, 'Deathwing WP (Goal)'),
(48572, 5, -8249.79, 1381.05, 67.23, 'Deathwing WP (Goal)');

DELETE FROM `spell_script_names` WHERE `spell_id` = '66908';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(66908, 'spell_awesome_party_ensemble');

DELETE FROM `creature_text` WHERE `entry`=35054;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(35054,0,0,'Look at you! I\'m the luckiest boyfriend on the island!!!',12,0,100,0,0,0,'Comment');

DELETE FROM `creature_text` WHERE `entry`=35186;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(35186,0,0,'I could really use a refill on my drink here.',12,0,100,0,0,0,'Drink (Need)'),
(35186,1,0,'Thanks for the refill, sir!',12,0,100,0,0,0,'Drink (Thanks)'),
(35186,2,0,'This is delicious! Are there more hors d\'oeuvres',12,0,100,0,0,0,'Eat (Need)'),
(35186,3,0,'Thanks. I was almost out. So hungry!',12,0,100,7,0,0,'Eat (Thanks)'),
(35186,4,0,'Oh, my head urtsh',12,0,100,0,0,0,'Drunk (Need)'),
(35186,5,0,'Shorry about your shoes.',12,0,100,0,0,0,'Drunk (Thanks)'),
(35186,5,1,'I feel much better now...hic!',12,0,100,0,0,0,'Drunk (Thanks)'),
(35186,4,1,'Ugh... I need a bucket!',12,0,100,0,0,0,'Drunk (Need)'),
(35186,6,0,'I love fireworks!',12,0,100,21,0,0,'Firework (Thanks)'),
(35186,6,1,'Best... Party... Evar!',12,0,100,4,0,0,'Firework (Thanks)'),
(35186,7,0,'If only I had someone to dance with.',12,0,100,0,0,0,'Dance (Need)'),
(35186,8,0,'We should totally have a pants-off dance-off!',12,0,100,94,0,0,'Dance (Thanks)'),
(35186,8,1,'A disco ball?! Groovy!',12,0,100,94,0,0,'Dance (Thanks)');

DELETE FROM `creature_text` WHERE `entry`=35175;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(35175,0,0,'I could really use a refill on my drink here.',12,0,100,0,0,0,'Drink (Need)'),
(35175,1,0,'Thanks for the refill, sir!',12,0,100,0,0,0,'Drink (Thanks)'),
(35175,2,0,'This is delicious! Are there more hors d\'oeuvres',12,0,100,0,0,0,'Eat (Need)'),
(35175,3,0,'Thanks. I was almost out. So hungry!',12,0,100,7,0,0,'Eat (Thanks)'),
(35175,4,0,'Oh, my head urtsh',12,0,100,0,0,0,'Drunk (Need)'),
(35175,5,0,'Shorry about your shoes.',12,0,100,0,0,0,'Drunk (Thanks)'),
(35175,5,1,'I feel much better now...hic!',12,0,100,0,0,0,'Drunk (Thanks)'),
(35175,4,1,'Ugh... I need a bucket!',12,0,100,0,0,0,'Drunk (Need)'),
(35175,6,0,'I love fireworks!',12,0,100,21,0,0,'Firework (Thanks)'),
(35175,7,0,'Best... Party... Evar!',12,0,100,4,0,0,'Firework (Thanks)'),
(35175,8,0,'If only I had someone to dance with.',12,0,100,0,0,0,'Dance (Need)'),
(35175,9,0,'We should totally have a pants-off dance-off!',12,0,100,94,0,0,'Dance (Thanks)'),
(35175,9,1,'A disco ball?! Groovy!',12,0,100,94,0,0,'Dance (Thanks)');

UPDATE `creature_template` SET `unit_flags`=0, `ScriptName`='npc_frightened_partygoer' WHERE `entry` IN (35235, 35202);
UPDATE `creature` SET `spawntimesecs`=60 WHERE `id` IN (35237, 35200, 35235, 35202);
UPDATE `creature` SET `spawndist`=10, `MovementType`=1 WHERE `guid`=835470;

-- ELM General Purpose Bunny Infinite Hide Body
SET @ENTRY := 43359;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,20000,60000,20000,60000,11,74070,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Volcano: South"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,20000,60000,20000,60000,11,74072,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Volcano: West"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,20000,60000,20000,60000,11,74076,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Volcano: North"),
(@ENTRY,@SOURCETYPE,3,0,1,0,100,0,20000,60000,20000,60000,11,74085,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Volcano: East");

UPDATE `creature` SET `spawndist`=10, `MovementType`=1 WHERE `guid`=835352;

-- Hired Looter
SET @ENTRY := 35234;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,5000,11000,7800,21300,11,6257,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Torch Toss"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,500,500,5000,5000,8,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Set Defensive");

DELETE FROM `spell_script_names` WHERE `spell_id` = '67435';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(67435, 'spell_hobart_ingenious_cap');

-- Mook Disguise
SET @ENTRY := 48925;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,11,46598,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Ride Invoker"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,2000,2000,2000,2000,45,0,1,0,0,0,0,11,35609,6,0,0.0,0.0,0.0,0.0,"OOC - Set Data 1 to Mook");

-- Villa Mook
SET @ENTRY := 35609;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,85,0,0,1,0,0,10,66,11,66,11,66,11,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Emote"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,5000,5000,5000,5000,11,76136,32,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Add Buff");

UPDATE `gameobject_template` SET `ScriptName`='go_first_bank_of_kezan' WHERE `entry`=195449;
UPDATE `creature` SET `phaseMask`=32768 WHERE `guid` IN (834867,834868,834872,834876,834875,834871,834869,834870,834873,834773);
UPDATE `creature_template` SET `speed_walk`=0.0001, `speed_run`=0.0001 WHERE `entry`=43562;

DELETE FROM `creature_text` WHERE `entry`=36600;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36600,0,0,'That\'s $n?! Sorry, Doc. I thought he was dead!',12,0,100,0,0,0,'Comment');