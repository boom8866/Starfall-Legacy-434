-- Captured Totem
SET @ENTRY := 23811;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,54,0,100,0,0,0,0,0,85,42454,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Captured Totem"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,41,10000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Set Passive");

-- Mottled Drywallow Crocolisk
SET @ENTRY := 4344;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,2000,4500,12000,20000,11,90171,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Jagged Tooth Snap"),
(@ENTRY,@SOURCETYPE,1,2,8,0,100,0,42454,1,0,0,33,23811,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,41,3500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

-- Drywallow Daggermaw
SET @ENTRY := 4345;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,3000,3000,45000,50000,11,6016,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Pierce Armor"),
(@ENTRY,@SOURCETYPE,1,2,8,0,100,0,42454,1,0,0,33,23811,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Quest Credit"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,41,3500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Force Despawn");

DELETE FROM `conditions` WHERE `SourceEntry` = '42454';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 42454, 0, 0, 31, 0, 3, 4344, 0, 0, 0, '', 'Targeting -> Crocolisk 1'),
(13, 1, 42454, 0, 1, 31, 0, 3, 4345, 0, 0, 0, '', 'Targeting -> Crocolisk 2');

UPDATE `creature_template` SET `speed_run`=0.001, `unit_class`=8, `unit_flags`=768 WHERE `entry`=23811;

DELETE FROM `conditions` WHERE `SourceEntry` = '42356';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 42356, 0, 0, 31, 0, 3, 23751, 0, 0, 0, '', 'Targeting -> North Tent'),
(13, 1, 42356, 0, 1, 31, 0, 3, 23752, 0, 0, 0, '', 'Targeting -> Northeast Tent'),
(13, 1, 42356, 0, 2, 31, 0, 3, 23753, 0, 0, 0, '', 'Targeting -> East Tent');

-- North Tent
SET @ENTRY := 23751;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,2,8,0,100,0,42356,1,0,0,75,84788,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Add Fire Aura"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,60000,60000,60000,60000,28,84788,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Remove Fire"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,33,23751,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit");

-- Northeast Tent
SET @ENTRY := 23752;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,2,8,0,100,0,42356,1,0,0,75,84788,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Add Fire Aura"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,60000,60000,60000,60000,28,84788,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Remove Fire"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,33,23752,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit");

-- East Tent
SET @ENTRY := 23753;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,2,8,0,100,0,42356,1,0,0,75,84788,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Add Fire Aura"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,60000,60000,60000,60000,28,84788,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Remove Fire"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,33,23753,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit");

UPDATE `creature_template` SET `scale`=7 WHERE `entry` IN (23751, 23752, 23753);

DELETE FROM `spell_script_names` WHERE `spell_id` = '42356';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(42356, 'spell_burn_direhorn_post');

-- Restless Apparition
SET @ENTRY := 23861;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,25,0,100,0,0,0,0,0,80,2386100,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Restless Apparition - On spawn - Run script"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,33,23861,0,0,0,0,0,18,25,0,0,0.0,0.0,0.0,0.0,"Link - Quest Credit");

UPDATE `creature_template` SET `npcflag`=0 WHERE `entry`=23861;
UPDATE `gossip_menu_option` SET `option_id`=4, `npc_option_npcflag`=8192 WHERE `menu_id`=11372 AND `id`=0;

DELETE FROM `spell_script_names` WHERE `spell_id` = '42418';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(42418, 'spell_redeem_remains');

DELETE FROM `creature_text` WHERE `entry`=23786;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(23786,0,0,'You leave Stonemaul lands now!',12,0,100,0,0,0,'Comment'),
(23786,0,1,'Me crush puny friend of dragons!',12,0,100,0,0,0,'Comment'),
(23786,0,2,'I\'ll crush you!',12,0,100,0,0,0,'Comment'),
(23786,0,3,'Why you wake ghost? Where other Stonemauls?!',12,0,100,0,0,0,'Comment');

-- Stonemaul Spirit
SET @ENTRY := 23786;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,54,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Talk 0"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Attack Invoker"),
(@ENTRY,@SOURCETYPE,2,0,54,0,100,0,0,0,0,0,11,95750,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Just Summoned - Cast Soulstone Effect");

UPDATE `quest_template` SET `PrevQuestId`='27239' WHERE `Id`=27240;
UPDATE `gossip_menu_option` SET `option_id`=3, `npc_option_npcflag`=5 WHERE `menu_id`=8826 AND `id`=0;
UPDATE `gossip_menu_option` SET `option_text`='You look like an intelligent person. Why don\'t you read one of these leaflets and give it some thought?' WHERE `menu_id`=8851 AND `id`=0;

DELETE FROM `conditions` WHERE `SourceGroup`=8851 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 8851, 0, 0, 0, 9, 0, 27212, 0, 0, 0, 0, 0, '', 'Theramore Guard - Show gossip only if quest 27212 is active');

-- Theramore Guard
SET @ENTRY := 4979;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,4,0,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving on Aggro"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,1,0,0,0,0,11,95826,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shoot on Aggro"),
(@ENTRY,@SOURCETYPE,2,3,61,0,100,1,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Melee Attack on Aggro"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 on Aggro"),
(@ENTRY,@SOURCETYPE,4,5,9,1,100,0,5,30,2300,3900,11,95826,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Shoot"),
(@ENTRY,@SOURCETYPE,5,0,61,1,100,0,0,0,0,0,40,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Ranged Weapon Model"),
(@ENTRY,@SOURCETYPE,6,7,9,1,100,0,30,80,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,7,0,61,1,100,0,0,0,0,0,20,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Melee Attack when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,8,9,9,1,100,0,0,10,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,9,10,61,1,100,0,0,0,0,0,40,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Melee Weapon Model when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,10,0,61,1,100,0,0,0,0,0,20,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Melee Attack when not in Shoot Range"),
(@ENTRY,@SOURCETYPE,11,12,9,1,100,0,11,25,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving at 25 Yards"),
(@ENTRY,@SOURCETYPE,12,13,61,1,100,0,0,0,0,0,20,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Melee Attack at 25 Yards"),
(@ENTRY,@SOURCETYPE,13,0,61,1,100,0,0,0,0,0,40,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Ranged Weapon Model at 25 Yards"),
(@ENTRY,@SOURCETYPE,14,15,7,1,100,1,0,0,0,0,40,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Melee Weapon Model on Evade"),
(@ENTRY,@SOURCETYPE,15,0,61,1,100,1,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Reset on Evade"),
(@ENTRY,@SOURCETYPE,16,0,2,1,100,0,0,50,12000,13000,11,12169,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Shield Block at 50% HP"),
(@ENTRY,@SOURCETYPE,17,0,0,1,100,0,3000,4000,12000,15000,11,12170,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Revenge"),
(@ENTRY,@SOURCETYPE,18,0,62,0,100,0,8851,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,19,20,62,0,100,0,8851,0,0,0,33,4979,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit"),
(@ENTRY,@SOURCETYPE,20,0,61,0,100,0,0,0,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Talk 0"),
(@ENTRY,@SOURCETYPE,21,0,52,0,100,0,0,4979,0,0,1,3,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 3"),
(@ENTRY,@SOURCETYPE,22,0,52,0,100,0,3,4979,0,0,1,1,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 3 - Talk 1"),
(@ENTRY,@SOURCETYPE,23,0,52,0,100,0,1,4979,0,0,1,2,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Talk 2"),
(@ENTRY,@SOURCETYPE,24,19,62,0,100,0,8851,0,0,0,83,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Remove Flags"),
(@ENTRY,@SOURCETYPE,25,0,52,0,100,0,2,4979,0,0,81,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 2 - Reset Flags");

DELETE FROM `creature_text` WHERE `entry`=4979;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(4979,0,0,'Hey, thanks.',12,0,100,0,0,0,'theramore guard SAY_QUEST1'),
(4979,1,0,'...receive 50 percent off deserter undergarments? What is this garbage?',12,0,100,0,0,0,'theramore guard SAY_QUEST2'),
(4979,1,1,'...to establish a fund for the purchase of hair gel? I like my hair the way it is, thanks!',12,0,100,0,0,0,'theramore guard SAY_QUEST2'),
(4979,1,2,'...the deserters seek a Theramore where citizens will be free to juggle at all hours of the day? What is this nonsense?',12,0,100,0,0,0,'theramore guard SAY_QUEST2'),
(4979,1,3,'...to establish the chicken as the official symbol of Theramore?! These guys are nuts!',12,0,100,0,0,0,'theramore guard SAY_QUEST2'),
(4979,1,4,'...as a deserter, you\'ll enjoy activities like tethered swimming and dog grooming? How ridiculous!',12,0,100,0,0,0,'theramore guard SAY_QUEST2'),
(4979,2,0,'This... this is a joke, right?',12,0,100,0,0,0,'theramore guard SAY_QUEST3'),
(4979,2,1,'I\'d never join anything like this. Better keep this, though. It\'ll come in handy in the privy...',12,0,100,0,0,0,'theramore guard SAY_QUEST3'),
(4979,2,2,'What a bunch of lunatics! You actually believe this stuff?',12,0,100,0,0,0,'theramore guard SAY_QUEST3'),
(4979,3,0,'Theramore Guard reads the leaflet.',16,0,100,0,0,0,'Comment');

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=734592;

-- Bloodfen Screecher
SET @ENTRY := 4352;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,2,0,100,1,0,20,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Bloodfen Screecher - At 20% HP - Say Line 0");

UPDATE `gameobject` SET `phaseMask`=1 WHERE `guid`=721637;

DELETE FROM `spell_script_names` WHERE `spell_id` = '42338';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(42338, 'spell_unleash_captured_raptor');

UPDATE `quest_template` SET `PrevQuestId`='27242' WHERE `Id`=27243;

-- Captured Raptor
SET @ENTRY := 23741;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,54,0,100,0,0,0,0,0,89,35,0,0,0,0,0,8,0,0,0,-2459.62,-3167.15,35.42,0.82,"On Just Summoned - Move Random");

UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=23928;
UPDATE `gameobject` SET `phaseMask`=1 WHERE `guid`=722616;

DELETE FROM `event_scripts` WHERE `id` = '15452';
INSERT INTO `event_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`) VALUES
(15452, 2, 10, 23864, 3000000, 0, -2966.47, -3872.82, 31.17, 5.34);

UPDATE `gameobject` SET `phaseMask`=1 WHERE `guid`=725456;
UPDATE `gameobject` SET `phaseMask`=32768 WHERE `guid`=933;
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=23789;

-- Smolderwing
SET @ENTRY := 23789;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,0,0,0,0,0,11,42433,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Cast Fire Breath"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,4000,4000,6500,6500,11,42433,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Fire Breath");

DELETE FROM `gameobject_loot_template` WHERE `entry` = '39335';
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(39335, 774, 0.4528, 1, 0, 1, 1),
(39335, 818, 3.4929, 1, 0, 1, 1),
(39335, 858, 1.3907, 1, 0, 1, 1),
(39335, 1206, 0.7115, 1, 0, 1, 1),
(39335, 1210, 3.4605, 1, 0, 1, 1),
(39335, 2073, 0.7115, 1, 0, 1, 1),
(39335, 2075, 0.5821, 1, 0, 1, 1),
(39335, 2078, 0.9379, 1, 0, 1, 1),
(39335, 2079, 0.8085, 1, 0, 1, 1),
(39335, 2140, 1.0349, 1, 0, 1, 1),
(39335, 2455, 1.0673, 1, 0, 1, 1),
(39335, 2456, 1.326, 1, 0, 1, 1),
(39335, 2459, 1.5847, 1, 0, 1, 1),
(39335, 2632, 0.3881, 1, 0, 1, 1),
(39335, 2957, 0.2, 1, 0, 1, 1),
(39335, 2961, 0.194, 1, 0, 1, 1),
(39335, 2965, 0.194, 1, 0, 1, 1),
(39335, 2970, 0.4204, 1, 0, 1, 1),
(39335, 2972, 0.2587, 1, 0, 1, 1),
(39335, 2973, 0.3234, 1, 0, 1, 1),
(39335, 2974, 0.2587, 1, 0, 1, 1),
(39335, 2975, 0.3234, 1, 0, 1, 1),
(39335, 2976, 0.2587, 1, 0, 1, 1),
(39335, 2977, 0.2911, 1, 0, 1, 1),
(39335, 2978, 0.1617, 1, 0, 1, 1),
(39335, 2979, 0.2911, 1, 0, 1, 1),
(39335, 2980, 0.2911, 1, 0, 1, 1),
(39335, 2982, 0.3234, 1, 0, 1, 1),
(39335, 2983, 0.3, 1, 0, 1, 1),
(39335, 2984, 0.2911, 1, 0, 1, 1),
(39335, 2986, 0.1, 1, 0, 1, 1),
(39335, 2987, 0.4528, 1, 0, 1, 1),
(39335, 2988, 0.4851, 1, 0, 1, 1),
(39335, 2992, 0.2587, 1, 0, 1, 1),
(39335, 3036, 0.6468, 1, 0, 1, 1),
(39335, 3040, 0.5498, 1, 0, 1, 1),
(39335, 3184, 0.6792, 1, 0, 1, 1),
(39335, 3192, 0.6468, 1, 0, 1, 1),
(39335, 3195, 0.6792, 1, 0, 1, 1),
(39335, 3196, 1.132, 1, 0, 1, 1),
(39335, 3205, 0.2, 1, 0, 1, 1),
(39335, 3207, 0.4204, 1, 0, 1, 1),
(39335, 3211, 0.1617, 1, 0, 1, 1),
(39335, 3213, 0.3881, 1, 0, 1, 1),
(39335, 3279, 0.3881, 1, 0, 1, 1),
(39335, 3281, 0.2911, 1, 0, 1, 1),
(39335, 3282, 0.3234, 1, 0, 1, 1),
(39335, 3283, 0.3881, 1, 0, 1, 1),
(39335, 3284, 0.8409, 1, 0, 1, 1),
(39335, 3286, 0.3234, 1, 0, 1, 1),
(39335, 3287, 0.4851, 1, 0, 1, 1),
(39335, 3288, 0.3234, 1, 0, 1, 1),
(39335, 3289, 0.4528, 1, 0, 1, 1),
(39335, 3290, 0.3234, 1, 0, 1, 1),
(39335, 3291, 0.2587, 1, 0, 1, 1),
(39335, 3292, 0.3234, 1, 0, 1, 1),
(39335, 3302, 0.3234, 1, 0, 1, 1),
(39335, 3303, 0.1, 1, 0, 1, 1),
(39335, 3304, 0.2, 1, 0, 1, 1),
(39335, 3307, 0.3881, 1, 0, 1, 1),
(39335, 3308, 0.2587, 1, 0, 1, 1),
(39335, 3309, 0.3234, 1, 0, 1, 1),
(39335, 3310, 0.3234, 1, 0, 1, 1),
(39335, 3311, 0.3881, 1, 0, 1, 1),
(39335, 3312, 0.2587, 1, 0, 1, 1),
(39335, 3313, 0.2, 1, 0, 1, 1),
(39335, 3314, 0.3234, 1, 0, 1, 1),
(39335, 3643, 0.2587, 1, 0, 1, 1),
(39335, 3644, 0.2911, 1, 0, 1, 1),
(39335, 3645, 0.4528, 1, 0, 1, 1),
(39335, 3649, 0.1, 1, 0, 1, 1),
(39335, 3651, 0.2, 1, 0, 1, 1),
(39335, 3652, 0.194, 1, 0, 1, 1),
(39335, 3653, 0.4204, 1, 0, 1, 1),
(39335, 3654, 0.2, 1, 0, 1, 1),
(39335, 3655, 0.1, 1, 0, 1, 1),
(39335, 4561, 0.9379, 1, 0, 1, 1),
(39335, 4564, 1.132, 1, 0, 1, 1),
(39335, 4566, 0.7762, 1, 0, 1, 1),
(39335, 4567, 0.4851, 1, 0, 1, 1),
(39335, 4569, 0.7115, 1, 0, 1, 1),
(39335, 4570, 0.5821, 1, 0, 1, 1),
(39335, 4571, 1.326, 1, 0, 1, 1),
(39335, 4575, 0.5498, 1, 0, 1, 1),
(39335, 4577, 1.0026, 1, 0, 1, 1),
(39335, 4596, 1.0026, 1, 0, 1, 1),
(39335, 4677, 0.2, 1, 0, 1, 1),
(39335, 4678, 0.6468, 1, 0, 1, 1),
(39335, 4680, 0.2264, 1, 0, 1, 1),
(39335, 4681, 0.194, 1, 0, 1, 1),
(39335, 4684, 0.2, 1, 0, 1, 1),
(39335, 4686, 0.2264, 1, 0, 1, 1),
(39335, 4687, 0.4204, 1, 0, 1, 1),
(39335, 4689, 0.2264, 1, 0, 1, 1),
(39335, 4690, 0.5175, 1, 0, 1, 1),
(39335, 4692, 0.4851, 1, 0, 1, 1),
(39335, 4693, 0.3, 1, 0, 1, 1),
(39335, 4695, 0.2587, 1, 0, 1, 1),
(39335, 4697, 0.3558, 1, 0, 1, 1),
(39335, 4699, 0.3234, 1, 0, 1, 1),
(39335, 4701, 0.4204, 1, 0, 1, 1),
(39335, 5069, 1.0026, 1, 0, 1, 1),
(39335, 5071, 0.6145, 1, 0, 1, 1),
(39335, 5207, 0.3558, 1, 0, 1, 1),
(39335, 5212, 0.7439, 1, 0, 1, 1),
(39335, 5631, 1.2937, 1, 0, 1, 1),
(39335, 6051, 1.326, 1, 0, 1, 1),
(39335, 6266, 0.2264, 1, 0, 1, 1),
(39335, 6267, 0.3558, 1, 0, 1, 1),
(39335, 6268, 0.1617, 1, 0, 1, 1),
(39335, 6269, 0.1617, 1, 0, 1, 1),
(39335, 6336, 0.1617, 1, 0, 1, 1),
(39335, 6337, 0.4851, 1, 0, 1, 1),
(39335, 6372, 1.4554, 1, 0, 1, 1),
(39335, 6378, 0.2911, 1, 0, 1, 1),
(39335, 6379, 0.194, 1, 0, 1, 1),
(39335, 6380, 0.4204, 1, 0, 1, 1),
(39335, 6506, 0.2, 1, 0, 1, 1),
(39335, 6510, 0.194, 1, 0, 1, 1),
(39335, 6511, 0.1617, 1, 0, 1, 1),
(39335, 6512, 0.3558, 1, 0, 1, 1),
(39335, 6515, 0.3234, 1, 0, 1, 1),
(39335, 6518, 0.4204, 1, 0, 1, 1),
(39335, 6527, 0.1294, 1, 0, 1, 1),
(39335, 6531, 0.3234, 1, 0, 1, 1),
(39335, 6536, 0.2, 1, 0, 1, 1),
(39335, 6537, 0.5175, 1, 0, 1, 1),
(39335, 6538, 0.2, 1, 0, 1, 1),
(39335, 6539, 0.2911, 1, 0, 1, 1),
(39335, 6540, 0.5821, 1, 0, 1, 1),
(39335, 6541, 0.4528, 1, 0, 1, 1),
(39335, 6542, 0.3234, 1, 0, 1, 1),
(39335, 6543, 0.3881, 1, 0, 1, 1),
(39335, 6545, 0.2911, 1, 0, 1, 1),
(39335, 6546, 0.1, 1, 0, 1, 1),
(39335, 6547, 0.2, 1, 0, 1, 1),
(39335, 6548, 0.4851, 1, 0, 1, 1),
(39335, 6549, 0.1617, 1, 0, 1, 1),
(39335, 6550, 0.3, 1, 0, 1, 1),
(39335, 6551, 0.1294, 1, 0, 1, 1),
(39335, 6553, 0.3234, 1, 0, 1, 1),
(39335, 6554, 0.3234, 1, 0, 1, 1),
(39335, 6555, 0.4851, 1, 0, 1, 1),
(39335, 6556, 0.3558, 1, 0, 1, 1),
(39335, 6557, 0.3234, 1, 0, 1, 1),
(39335, 6558, 0.2911, 1, 0, 1, 1),
(39335, 6560, 0.2264, 1, 0, 1, 1),
(39335, 6563, 0.2264, 1, 0, 1, 1),
(39335, 6575, 0.2587, 1, 0, 1, 1),
(39335, 6585, 0.4851, 1, 0, 1, 1),
(39335, 7351, 0.4204, 1, 0, 1, 1),
(39335, 7554, 0.194, 1, 0, 1, 1),
(39335, 8180, 0.4204, 1, 0, 1, 1),
(39335, 9742, 0.6145, 1, 0, 1, 1),
(39335, 9743, 0.3881, 1, 0, 1, 1),
(39335, 9744, 0.4851, 1, 0, 1, 1),
(39335, 9745, 0.5175, 1, 0, 1, 1),
(39335, 9746, 0.3234, 1, 0, 1, 1),
(39335, 9747, 0.2264, 1, 0, 1, 1),
(39335, 9749, 0.1617, 1, 0, 1, 1),
(39335, 9750, 0.2911, 1, 0, 1, 1),
(39335, 9751, 0.5175, 1, 0, 1, 1),
(39335, 9752, 0.3881, 1, 0, 1, 1),
(39335, 9753, 0.2, 1, 0, 1, 1),
(39335, 9754, 0.2264, 1, 0, 1, 1),
(39335, 9755, 0.194, 1, 0, 1, 1),
(39335, 9756, 0.2, 1, 0, 1, 1),
(39335, 9757, 0.2911, 1, 0, 1, 1),
(39335, 9758, 0.2, 1, 0, 1, 1),
(39335, 9759, 0.2, 1, 0, 1, 1),
(39335, 9760, 0.3234, 1, 0, 1, 1),
(39335, 9761, 0.2264, 1, 0, 1, 1),
(39335, 9763, 0.3234, 1, 0, 1, 1),
(39335, 9764, 0.1, 1, 0, 1, 1),
(39335, 9765, 0.2587, 1, 0, 1, 1),
(39335, 9770, 0.3234, 1, 0, 1, 1),
(39335, 9775, 0.3234, 1, 0, 1, 1),
(39335, 9776, 0.6468, 1, 0, 1, 1),
(39335, 9777, 0.2587, 1, 0, 1, 1),
(39335, 9778, 0.1617, 1, 0, 1, 1),
(39335, 9779, 0.2587, 1, 0, 1, 1),
(39335, 9780, 0.2911, 1, 0, 1, 1),
(39335, 9783, 0.6468, 1, 0, 1, 1),
(39335, 9784, 0.2, 1, 0, 1, 1),
(39335, 9786, 0.2911, 1, 0, 1, 1),
(39335, 9787, 0.1617, 1, 0, 1, 1),
(39335, 9788, 0.2587, 1, 0, 1, 1),
(39335, 9789, 0.2, 1, 0, 1, 1),
(39335, 11965, 1.0349, 1, 0, 1, 1),
(39335, 14025, 0.3234, 1, 0, 1, 1),
(39335, 14090, 0.3234, 1, 0, 1, 1),
(39335, 14091, 0.2911, 1, 0, 1, 1),
(39335, 14094, 0.2911, 1, 0, 1, 1),
(39335, 14095, 0.2, 1, 0, 1, 1),
(39335, 14096, 0.2264, 1, 0, 1, 1),
(39335, 14099, 0.4204, 1, 0, 1, 1),
(39335, 14102, 0.4528, 1, 0, 1, 1),
(39335, 14109, 0.2, 1, 0, 1, 1),
(39335, 14110, 0.3234, 1, 0, 1, 1),
(39335, 14113, 0.3881, 1, 0, 1, 1),
(39335, 14114, 0.5498, 1, 0, 1, 1),
(39335, 14115, 0.2911, 1, 0, 1, 1),
(39335, 14117, 0.4204, 1, 0, 1, 1),
(39335, 14119, 0.3558, 1, 0, 1, 1),
(39335, 14120, 0.2, 1, 0, 1, 1),
(39335, 14122, 0.2264, 1, 0, 1, 1),
(39335, 14123, 0.2264, 1, 0, 1, 1),
(39335, 14124, 0.3234, 1, 0, 1, 1),
(39335, 14129, 0.4204, 1, 0, 1, 1),
(39335, 14131, 0.2587, 1, 0, 1, 1),
(39335, 14160, 0.3234, 1, 0, 1, 1),
(39335, 14161, 0.8085, 1, 0, 1, 1),
(39335, 14166, 0.2264, 1, 0, 1, 1),
(39335, 14167, 0.4204, 1, 0, 1, 1),
(39335, 14168, 0.2264, 1, 0, 1, 1),
(39335, 14173, 0.5498, 1, 0, 1, 1),
(39335, 14174, 0.2587, 1, 0, 1, 1),
(39335, 14364, 0.4528, 1, 0, 1, 1),
(39335, 14365, 0.2911, 1, 0, 1, 1),
(39335, 14366, 0.3234, 1, 0, 1, 1),
(39335, 14367, 0.2587, 1, 0, 1, 1),
(39335, 14370, 0.4851, 1, 0, 1, 1),
(39335, 14559, 0.4851, 1, 0, 1, 1),
(39335, 14560, 0.2587, 1, 0, 1, 1),
(39335, 14561, 0.6468, 1, 0, 1, 1),
(39335, 14563, 1.0996, 1, 0, 1, 1),
(39335, 14722, 0.2911, 1, 0, 1, 1),
(39335, 14723, 0.2587, 1, 0, 1, 1),
(39335, 14724, 0.2, 1, 0, 1, 1),
(39335, 14725, 0.4851, 1, 0, 1, 1),
(39335, 14726, 0.2587, 1, 0, 1, 1),
(39335, 14727, 0.5175, 1, 0, 1, 1),
(39335, 14729, 0.4204, 1, 0, 1, 1),
(39335, 15009, 0.2, 1, 0, 1, 1),
(39335, 15010, 0.8085, 1, 0, 1, 1),
(39335, 15011, 0.3881, 1, 0, 1, 1),
(39335, 15013, 0.2587, 1, 0, 1, 1),
(39335, 15015, 0.2911, 1, 0, 1, 1),
(39335, 15016, 0.2264, 1, 0, 1, 1),
(39335, 15017, 0.1294, 1, 0, 1, 1),
(39335, 15018, 0.3881, 1, 0, 1, 1),
(39335, 15110, 0.2264, 1, 0, 1, 1),
(39335, 15112, 0.2, 1, 0, 1, 1),
(39335, 15114, 0.2264, 1, 0, 1, 1),
(39335, 15210, 0.7115, 1, 0, 1, 1),
(39335, 15222, 1.3583, 1, 0, 1, 1),
(39335, 15248, 0.6468, 1, 0, 1, 1),
(39335, 15268, 0.7439, 1, 0, 1, 1),
(39335, 15297, 0.194, 1, 0, 1, 1),
(39335, 15298, 0.1294, 1, 0, 1, 1),
(39335, 15300, 0.2911, 1, 0, 1, 1),
(39335, 15301, 0.3234, 1, 0, 1, 1),
(39335, 15302, 0.2, 1, 0, 1, 1),
(39335, 15303, 0.2911, 1, 0, 1, 1),
(39335, 15304, 0.2264, 1, 0, 1, 1),
(39335, 15305, 0.2911, 1, 0, 1, 1),
(39335, 15306, 0.2587, 1, 0, 1, 1),
(39335, 15309, 0.2264, 1, 0, 1, 1),
(39335, 15310, 0.3558, 1, 0, 1, 1),
(39335, 15312, 0.194, 1, 0, 1, 1),
(39335, 15477, 0.2, 1, 0, 1, 1),
(39335, 15479, 0.4204, 1, 0, 1, 1),
(39335, 15480, 0.2, 1, 0, 1, 1),
(39335, 15484, 0.2587, 1, 0, 1, 1),
(39335, 15485, 0.2587, 1, 0, 1, 1),
(39335, 15487, 0.1617, 1, 0, 1, 1),
(39335, 15489, 0.1, 1, 0, 1, 1),
(39335, 15490, 0.3558, 1, 0, 1, 1),
(39335, 15491, 0.3234, 1, 0, 1, 1),
(39335, 15492, 0.2264, 1, 0, 1, 1),
(39335, 15493, 0.2264, 1, 0, 1, 1),
(39335, 15494, 0.2587, 1, 0, 1, 1),
(39335, 15495, 0.2264, 1, 0, 1, 1),
(39335, 15497, 0.1, 1, 0, 1, 1),
(39335, 15498, 0.3558, 1, 0, 1, 1),
(39335, 15499, 0.2911, 1, 0, 1, 1),
(39335, 15502, 0.3234, 1, 0, 1, 1),
(39335, 15507, 0.2911, 1, 0, 1, 1),
(39335, 15508, 0.3558, 1, 0, 1, 1),
(39335, 15510, 0.2, 1, 0, 1, 1),
(39335, 15893, 0.1, 1, 0, 1, 1),
(39335, 15926, 0.4851, 1, 0, 1, 1),
(39335, 15932, 0.3881, 1, 0, 1, 1),
(39335, 15933, 0.1, 1, 0, 1, 1),
(39335, 15944, 0.4851, 1, 0, 1, 1),
(39335, 15945, 0.1617, 1, 0, 1, 1),
(39335, 15969, 0.1, 1, 0, 1, 1),
(39335, 15970, 0.4528, 1, 0, 1, 1);

UPDATE `gameobject_template` SET `data1`=39335 WHERE `entry`=207475;

-- Balos Jacken
SET @ENTRY := 5089;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,2,0,100,0,0,20,0,0,2,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 20% - Set Friendly"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,24,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Evade"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,60000,60000,60000,60000,2,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"OOC - Set Enemy Faction"),
(@ENTRY,@SOURCETYPE,3,0,4,0,100,0,0,0,0,0,42,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Aggro - Set Invincible");

UPDATE `gossip_menu_option` SET `option_id`=1, `npc_option_npcflag`=1 WHERE `menu_id`=11372 AND `id`=1;

DELETE FROM `conditions` WHERE `SourceGroup`=11372 AND `SourceEntry` IN (1, 2);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 11372, 1, 0, 0, 9, 0, 25479, 0, 0, 0, 0, 0, '', 'Dyslix Silvergrub - Show gossip only if quest 25479 is active'),
(15, 11372, 2, 0, 0, 9, 0, 25481, 0, 0, 0, 0, 0, '', 'Seyala Nightwisp - Show gossip only if quest 25479 is active');

UPDATE `creature_template` SET `VehicleId`=108 WHERE  `entry`=24489;
UPDATE `gameobject` SET `phaseMask`=1 WHERE `guid` IN (727813, 727814);
UPDATE `quest_template` SET `PrevQuestId`='27237' WHERE `Id`=27238;
UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=739446;

DELETE FROM `creature_text` WHERE `entry`=23941;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(23941,0,0,'I surrender! Stay your blade! ',12,0,100,0,0,0,'Comment'),
(23941,1,0,'I will go with you. Just spare my men. They\'re good lads who\'ve only made a mistake...',12,0,100,0,0,0,'Comment');

-- Gavis Greyshield
SET @ENTRY := 23941;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,2,2,0,100,1,0,20,0,0,1,0,5000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 20% - Talk 0"),
(@ENTRY,@SOURCETYPE,1,6,2,0,100,1,0,20,0,0,2,35,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Health 20% - Set Friendly"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,29,2,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Follow Invoker"),
(@ENTRY,@SOURCETYPE,3,5,52,0,100,0,0,23941,0,0,1,0,20000,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 0 - Talk 1"),
(@ENTRY,@SOURCETYPE,4,0,52,0,100,0,1,23941,0,0,41,2500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"After Talk 1 - Force Despawn"),
(@ENTRY,@SOURCETYPE,5,0,61,0,100,0,0,0,0,0,33,23941,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete"),
(@ENTRY,@SOURCETYPE,6,0,61,0,100,0,0,0,0,0,5,20,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Link - Play Emote");

UPDATE `creature` SET `spawntimesecs`=60 WHERE `guid`=739446;
UPDATE `gameobject` SET `phaseMask`=1 WHERE `guid`=722599;

DELETE FROM `spell_script_names` WHERE `spell_id` = '42390';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(42390, 'spell_lay_wreath');

UPDATE `gameobject` SET `position_z`=-20.7516 WHERE `guid`=724032;
UPDATE `gameobject` SET `position_z`=-20.122 WHERE `guid`=724031;
UPDATE `gameobject` SET `position_z`=-12.1825 WHERE `guid`=724030;
UPDATE `gameobject` SET `position_z`=-21.0353 WHERE `guid`=724029;
UPDATE `gameobject` SET `position_z`=-10.34198 WHERE `guid`=724028;
UPDATE `gameobject` SET `position_z`=-16.2234 WHERE `guid`=724027;
UPDATE `gameobject` SET `position_z`=-19.7568 WHERE `guid`=724026;
UPDATE `gameobject` SET `position_z`=-11.131 WHERE `guid`=724025;

DELETE FROM `gameobject_loot_template` WHERE `entry` = '11';
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`) VALUES
(11, 33041, -100);

UPDATE `gameobject` SET `phaseMask`=1 WHERE `id`=11;

DELETE FROM `spell_script_names` WHERE `spell_id` = '42287';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(42287, 'spell_salvage_wreckage');

UPDATE `gameobject_template` SET `data4`=27237 WHERE `entry`=11;
UPDATE `quest_template` SET `Flags`=0, `SpecialFlags`=2 WHERE `Id`=27222;
UPDATE `creature` SET `phaseMask`=32768 WHERE `guid`=736465;

-- Theramore Cannon
SET @ENTRY := 23907;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,0,1,0,0,11,42576,0,0,0,0,0,11,23899,500,0,0.0,0.0,0.0,0.0,"On Get Data 1 - Cast Cannon Blast");

-- Cove Cannon
SET @ENTRY := 186432;
SET @SOURCETYPE := 1;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE gameobject_template SET AIName="SmartGameObjectAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,64,0,100,0,0,0,0,0,45,0,1,0,0,0,0,11,23907,3,0,0.0,0.0,0.0,0.0,"On Gossip Hello - Set Data 1 to Trigger");

DELETE FROM `conditions` WHERE `SourceEntry` = '42574';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 42574, 0, 0, 31, 0, 3, 23899, 0, 0, 0, '', 'Targeting -> Tethyr');

-- Tethyr
SET @ENTRY := 23899;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,5000,5000,5000,5000,49,0,0,0,0,0,0,11,23900,100,0,0.0,0.0,0.0,0.0,"OOC - Attack Marksman"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,1000,1000,10000,10000,11,42574,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"IC - Cast Water Bolt"),
(@ENTRY,@SOURCETYPE,2,3,8,0,100,0,42576,4,0,0,37,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Spellhit - Die"),
(@ENTRY,@SOURCETYPE,3,0,61,0,100,0,0,0,0,0,15,27222,0,0,0,0,0,18,150,0,0,0.0,0.0,0.0,0.0,"Link - Quest Complete");

-- Major Mills
SET @ENTRY := 23905;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,1,100,0,11198,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Major Mills - On Quest Accept - Say text"),
(@ENTRY,@SOURCETYPE,1,0,19,1,100,0,11198,0,0,0,80,2390500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Major Mills: On quest accept call main script");

-- Major Mills
SET @ENTRY := 23905;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,19,1,100,0,27222,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"Major Mills - On Quest Accept - Say text"),
(@ENTRY,@SOURCETYPE,1,0,19,1,100,0,27222,0,0,0,80,2390500,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Major Mills: On quest accept call main script");

-- Major Mills
SET @ENTRY := 2390500;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,5000,5000,0,0,12,23900,1,900000,0,0,0,8,0,0,0,-3904.77,-4635.09,9.62735,5.49334,"Take Down Tethyr: Summon Theramore Marksman"),
(@ENTRY,@SOURCETYPE,1,0,1,0,100,0,5000,5000,0,0,12,23900,1,900000,0,0,0,8,0,0,0,-3856.59,-4622.45,9.24753,3.87856,"Take Down Tethyr: Summon Theramore Marksman"),
(@ENTRY,@SOURCETYPE,2,0,1,0,100,0,5000,5000,0,0,12,23900,1,900000,0,0,0,8,0,0,0,-3917.6,-4648.53,9.32604,5.56795,"Take Down Tethyr: Summon Theramore Marksman"),
(@ENTRY,@SOURCETYPE,3,0,1,0,100,0,5000,5000,0,0,12,23900,1,900000,0,0,0,8,0,0,0,-3890.48,-4620.7,9.55527,4.99383,"Take Down Tethyr: Summon Theramore Marksman"),
(@ENTRY,@SOURCETYPE,4,0,1,0,100,0,5000,5000,0,0,12,23900,1,900000,0,0,0,8,0,0,0,-3865.94,-4617.2,9.26262,4.16523,"Take Down Tethyr: Summon Theramore Marksman"),
(@ENTRY,@SOURCETYPE,5,0,1,0,100,0,5000,5000,0,0,12,23900,1,900000,0,0,0,8,0,0,0,-3834.8,-4645.41,9.25827,3.61152,"Take Down Tethyr: Summon Theramore Marksman"),
(@ENTRY,@SOURCETYPE,6,0,1,0,100,0,5000,5000,0,0,12,23900,1,900000,0,0,0,8,0,0,0,-3826.61,-4655.32,9.21484,3.13243,"Take Down Tethyr: Summon Theramore Marksman"),
(@ENTRY,@SOURCETYPE,7,0,1,0,100,0,5000,5000,0,0,12,23900,1,900000,0,0,0,8,0,0,0,-3830.76,-4673.74,9.50962,2.70832,"Take Down Tethyr: Summon Theramore Marksman"),
(@ENTRY,@SOURCETYPE,8,0,1,0,100,0,5000,5000,0,0,12,23900,1,900000,0,0,0,8,0,0,0,-3843.65,-4687.59,9.6436,2.43735,"Take Down Tethyr: Summon Theramore Marksman"),
(@ENTRY,@SOURCETYPE,9,0,1,0,100,0,5000,5000,0,0,12,23900,1,900000,0,0,0,8,0,0,0,-3858.49,-4703.49,9.17411,2.33525,"Take Down Tethyr: Summon Theramore Marksman"),
(@ENTRY,@SOURCETYPE,10,0,1,0,100,0,5000,5000,0,0,12,23900,1,900000,0,0,0,8,0,0,0,-3851.97,-4697.24,9.36834,2.33525,"Take Down Tethyr: Summon Theramore Marksman"),
(@ENTRY,@SOURCETYPE,11,0,1,0,100,0,5000,5000,0,0,12,23900,1,900000,0,0,0,8,0,0,0,-3924.35,-4656.55,9.15409,5.80749,"Take Down Tethyr: Summon Theramore Marksman"),
(@ENTRY,@SOURCETYPE,12,0,1,0,100,0,8000,8000,0,0,12,23899,1,900000,0,0,0,8,0,0,0,-3891.03,-4671.17,-1.52,0.74,"Take Down Tethyr: Summon Tethyr");

-- Theramore Marksman
SET @ENTRY := 23900;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,2500,2500,2500,2500,49,0,0,0,0,0,0,11,23899,200,0,0.0,0.0,0.0,0.0,"OOC - Attack Tethyr"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,500,500,2000,2000,11,42580,0,0,0,0,0,11,23899,200,0,0.0,0.0,0.0,0.0,"IC - Shoot at Tethyr");

UPDATE `creature_template` SET `speed_walk`=0.001, `speed_run`=0.001 WHERE `entry`=23900;

DELETE FROM `conditions` WHERE `SourceGroup`=8782 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 8782, 0, 0, 0, 9, 0, 27239, 0, 0, 0, 0, 0, '', 'Cassa Crimsonwing - Show gossip only if quest 27239 is active');

-- Cassa Crimsonwing
SET @ENTRY := 23704;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,8782,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,8782,0,0,0,85,42295,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Start Taxi"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,8782,0,0,0,15,27239,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Complete");

UPDATE `creature_template` SET `speed_walk`=5, `speed_run`=5.14286, `InhabitType`=4 WHERE `entry`=24489;

DELETE FROM `waypoints` WHERE `entry` = '24489';
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(24489, 1, -4766.86, -3184.24, 149.78, 'Thalanaar Hippogryph WP'),
(24489, 2, -5174.92, -3413.56, 264.74, 'Thalanaar Hippogryph WP'),
(24489, 3, -5553.60, -3623.37, 70.46, 'Thalanaar Hippogryph WP'),
(24489, 4, -5462.67, -3298.77, 54.69, 'Thalanaar Hippogryph WP'),
(24489, 5, -5334.41, -3127.14, 42.83, 'Thalanaar Hippogryph WP'),
(24489, 6, -5317.68, -2901.10, 33.53, 'Thalanaar Hippogryph WP'),
(24489, 7, -5234.99, -2654.83, 11.44, 'Thalanaar Hippogryph WP'),
(24489, 8, -5011.50, -2205.89, 112.62, 'Thalanaar Hippogryph WP'),
(24489, 9, -4346.33, -869.73, 135.61, 'Thalanaar Hippogryph WP'),
(24489, 10, -4302.19, -558.28, 148.99, 'Thalanaar Hippogryph WP'),
(24489, 11, -4466.79, -535.64, 6.57, 'Thalanaar Hippogryph WP');

-- White Armored Hippogryph
SET @ENTRY := 24489;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,60,0,100,1,100,100,0,0,86,46598,0,18,10,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Update - Ride Player"),
(@ENTRY,@SOURCETYPE,1,0,27,0,100,0,0,0,0,0,53,1,24489,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On Passenger Boarded - Start WP"),
(@ENTRY,@SOURCETYPE,2,0,40,0,100,0,11,0,0,0,28,46598,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Remove Passenger"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,11,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"On WP Reached - Force Despawn"),
(@ENTRY,@SOURCETYPE,4,0,40,0,100,0,10,0,0,0,33,39897,0,0,0,0,0,18,15,0,0,0.0,0.0,0.0,0.0,"On WP Reached- Quest Complete");

-- Dyslix Silvergrub
SET @ENTRY := 40358;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,1,4,0,100,0,0,0,0,0,12,9526,4,30000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dyslix Silvergrub - On Aggro - Summon Enraged Gryphon"),
(@ENTRY,@SOURCETYPE,1,0,61,0,100,0,0,0,0,0,12,9297,4,30000,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Dyslix Silvergrub - On Aggro - Summon Enraged Wyvern"),
(@ENTRY,@SOURCETYPE,2,0,62,0,100,0,11372,1,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,3,0,62,0,100,0,11372,1,0,0,12,24489,3,300000,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Summon Hippogryph"),
(@ENTRY,@SOURCETYPE,4,0,62,0,100,0,11372,0,0,0,33,39897,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Quest Credit");

DELETE FROM `creature_template_addon` WHERE `entry` IN (24489, 24488);
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(24489, '83412'),
(24488, '83412');

UPDATE `creature` SET `phaseMask`=1 WHERE `guid`=734734;
UPDATE `gossip_menu_option` SET `option_id`=0, `npc_option_npcflag`=0 WHERE `menu_id`=2465 AND `id`=1;

DELETE FROM `conditions` WHERE `SourceGroup`=2465 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 2465, 0, 0, 0, 28, 0, 27240, 0, 0, 0, 0, 0, '', 'Lady Jaina Proudmoore - Show gossip only if quest 27240 is active');

DELETE FROM `spell_target_position` WHERE `id` = '42710';
INSERT INTO `spell_target_position` (`id`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(42710, -8386.66, 261.90, 155.34, 5.39);

DELETE FROM `spell_target_position` WHERE `id` = '42711';
INSERT INTO `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(42711, 1, -3751.97, -4456.14, 64.96, 0.83);

-- Lady Jaina Proudmoore
SET @ENTRY := 4968;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,4,0,100,1,0,0,0,0,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 on Aggro"),
(@ENTRY,@SOURCETYPE,1,0,4,1,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving on Aggro"),
(@ENTRY,@SOURCETYPE,2,0,4,1,100,1,0,0,0,0,11,20692,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast bolt on Aggro"),
(@ENTRY,@SOURCETYPE,3,0,9,1,100,0,0,40,3400,4700,11,20692,0,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast bolt"),
(@ENTRY,@SOURCETYPE,4,0,9,1,100,0,40,100,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving when not in bolt Range"),
(@ENTRY,@SOURCETYPE,5,0,9,1,100,0,10,15,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving at 15 Yards"),
(@ENTRY,@SOURCETYPE,6,0,9,1,100,0,0,40,0,0,21,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Stop Moving when in bolt Range"),
(@ENTRY,@SOURCETYPE,7,0,3,1,100,0,0,15,0,0,22,2,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 2 at 15% Mana"),
(@ENTRY,@SOURCETYPE,8,0,3,2,100,0,0,15,0,0,21,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Start Moving at 15% Mana"),
(@ENTRY,@SOURCETYPE,9,0,3,2,100,0,30,100,100,100,22,1,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Set Phase 1 When Mana is above 30%"),
(@ENTRY,@SOURCETYPE,10,0,0,1,100,0,4000,5000,45000,55000,11,20681,1,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Cast Summon Water Elementals"),
(@ENTRY,@SOURCETYPE,11,0,0,1,100,0,5000,9000,15000,17000,11,20679,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Fire Blast"),
(@ENTRY,@SOURCETYPE,12,0,0,1,100,0,8000,12000,25000,28000,11,20680,1,0,0,0,0,4,0,0,0,0.0,0.0,0.0,0.0,"Cast Blizzard"),
(@ENTRY,@SOURCETYPE,13,0,2,1,100,0,0,50,14000,21000,11,20682,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Cast Teleport at 50% HP"),
(@ENTRY,@SOURCETYPE,14,0,62,0,100,0,2465,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,15,0,62,0,100,0,2465,0,0,0,11,42710,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Teleport to Stormwind");

-- Archmage Malin
SET @ENTRY := 2708;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,62,0,100,0,8846,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Close Gossip"),
(@ENTRY,@SOURCETYPE,1,0,62,0,100,0,8846,0,0,0,11,42711,0,0,0,0,0,7,0,0,0,0.0,0.0,0.0,0.0,"On Gossip Select - Teleport to Theramore");

DELETE FROM `conditions` WHERE `SourceGroup`=8846 AND `SourceEntry` = '0';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15, 8846, 0, 0, 0, 28, 0, 27241, 0, 0, 0, 0, 0, '', 'Archmage Malin - Show gossip only if quest 27241 is active');

DELETE FROM `npc_trainer` WHERE `entry` = '23896';
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES
(23896, -200302, 0, 0, 0, 0);

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '8826';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(8826, 2, 1, 'Show me what you have for sale.', 3, 128, 0, 0, 0, 0, ''),
(8826, 1, 3, 'Train me.', 5, 64, 0, 0, 0, 0, '');

UPDATE `creature_template` SET `trainer_type`=2 WHERE `entry`=23896;
UPDATE `creature` SET `phaseMask`=32768 WHERE `guid`=183654;
UPDATE `creature_template` SET `InhabitType`=3, `flags_extra`=0 WHERE `entry`=11739;

DELETE FROM `gossip_menu_option` WHERE  `menu_id`=6525 AND `id`=0;
DELETE FROM `gossip_menu_option` WHERE  `menu_id`=6525 AND `id`=1;

DELETE FROM `gossip_menu_option` WHERE `menu_id` = '6525';
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES
(6525, 2, 1, 'I wish to browse your wares, Calandrath.', 3, 128, 0, 0, 0, 0, ''),
(6525, 3, 5, 'Make this inn your home.', 8, 65536, 0, 0, 0, 0, '');

DELETE FROM `spell_target_position` WHERE `id` = '93726';
INSERT INTO `spell_target_position` (`id`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(93726, -10932.72, -3395.09, 80.42, 5.99);

UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=8304;

DELETE FROM `creature` WHERE `guid` = '154349';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(154349, 40358, 1, 1, 1, 0, 0, -4567.27, -3226.31, 34.83, 5.38, 120, 0, 0, 1, 0, 0, 0, 0, 0);