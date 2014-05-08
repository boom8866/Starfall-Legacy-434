DELETE FROM `spell_area` WHERE `spell` = '80695' AND `quest_start` = '26229';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`, `quest_end_status`) VALUES
(80695, 109, 26229, 26232,  1, 10, 11);

DELETE FROM `creature_involvedrelation` WHERE `id` = '234' AND `quest` = '166';
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
(234, 166);

UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=42693;

DELETE FROM `areatrigger_scripts` WHERE `entry` = '6361';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6361, 'at_deadmines_votp');

UPDATE `creature_template` SET `unit_flags`=768 WHERE `entry`=42693;

-- Vision of the Past
SET @ENTRY := 42693;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,27,0,100,0,0,0,0,0,53,0,42693,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - WP Start"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,1,0,1000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,4,0,0,0,45,0,1,0,0,0,0,11,42699,80,0,0.0,0.0,0.0,0.0,"On WP Reached 4 - Set Data 1 to Alliance Warrior"),
(@ENTRY,@SOURCETYPE,3,0,38,0,100,0,0,3,0,0,28,79587,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Remove Vehicle"),
(@ENTRY,@SOURCETYPE,4,0,28,0,100,0,0,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Removed - Force Despawn");

-- Edwin VanCleef
SET @ENTRY := 42697;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,8,54,0,100,0,0,0,0,0,49,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Attack Summoner"),
(@ENTRY,@SOURCETYPE,1,0,4,0,100,1,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Talk 0"),
(@ENTRY,@SOURCETYPE,2,0,2,0,100,1,74,75,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On 75% HP - Talk 1"),
(@ENTRY,@SOURCETYPE,3,3,2,0,100,1,49,50,0,0,1,4,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On 50% HP - Talk 4"),
(@ENTRY,@SOURCETYPE,4,0,2,0,100,1,24,25,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On 25% HP - Talk 2"),
(@ENTRY,@SOURCETYPE,5,0,2,0,100,1,9,10,0,0,1,3,10000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On 10% HP - Talk 3"),
(@ENTRY,@SOURCETYPE,6,0,52,0,100,0,3,42697,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Die"),
(@ENTRY,@SOURCETYPE,7,0,6,0,100,0,0,0,0,0,45,0,2,0,0,0,0,11,42699,80,0,0.0,0.0,0.0,0.0,"On Death - Set Data 2 to Alliance Warrior"),
(@ENTRY,@SOURCETYPE,8,0,61,0,100,0,0,0,0,0,12,42698,4,60000,0,0,0,8,0,0,0,0.0,0.0,0.0,0.0,"Link - Summon Guard");

DELETE FROM `creature_text` WHERE `entry` IN (42492, 42662);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(42492,0,0,'What little humie want? Why you call Glubtok?',12,0,100,0,0,0,'Comment'),
(42492,1,0,'Glubtok crush you!',12,0,100,0,0,0,'Comment'),
(42492,2,0,'What option two?',12,0,100,0,0,0,'Comment'),
(42492,3,0,'So Glubtok have two choices: die or be rich and powerful?',12,0,100,0,0,0,'Comment'),
(42492,4,0,'Glubtok take choice two.',12,0,100,0,0,0,'Comment'),
(42662,0,0,'Sad... Is this the life you had hoped for, Glubtok? Running two-bit extortion operations out of a cave?',12,0,100,0,0,0,'Comment'),
(42662,1,0,'Oh will you? Do you dare cross that line and risk your life?',12,0,100,0,0,0,'Comment'),
(42662,2,0,'You may attempt to kill me - and fail - or you may take option two.',12,0,100,0,0,0,'Comment'),
(42662,3,0,'You join me and I shower wealth and power upon you.',12,0,100,0,0,0,'Comment'),
(42662,4,0,'I thought you\'d see it my way.',12,0,100,0,0,0,'Comment'),
(42662,5,0,'I will call for you when the dawning is upon us.',12,0,100,0,0,0,'Comment'),
(42662,6,0,'They provided the distraction I required. We continue as planned.',12,0,100,0,0,0,'Comment'),
(42662,7,0,'We will free the admiral during the dawning.',12,0,100,0,0,0,'Comment'),
(42662,8,0,'Judgment day is soon upon us, Helix.',12,0,100,0,0,0,'Comment'),
(42662,9,0,'Call of the people. I wish to speak to them one last time before the dawning.',12,0,100,0,0,0,'Comment'),
(42662,10,0,'Aye. Tonight.',12,0,100,0,0,0,'Comment');