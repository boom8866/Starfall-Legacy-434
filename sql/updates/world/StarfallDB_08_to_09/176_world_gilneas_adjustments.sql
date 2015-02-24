UPDATE `creature` SET `spawndist`=8, `MovementType`=1 WHERE `id`=36293;
UPDATE `creature_template` SET `DamageModifier`=3.5 WHERE `entry`=36294;
UPDATE `creature_template` SET `ScriptName`='npc_gilneas_swamp_crocolisk' WHERE `entry`=36882;

-- Swamp Crocolisk
SET @ENTRY := 36882;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

DELETE FROM `creature_text` WHERE `entry`=37067;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(37067,0,0,'Thank you!',12,0,100,0,0,0,'Comment'),
(37067,0,1,'Thanks!',12,0,100,0,0,0,'Comment'),
(37067,0,2,'Finally, I am safe...',12,0,100,0,0,0,'Comment'),
(37067,0,3,'I was... exhausted, thank you!',12,0,100,0,0,0,'Comment');