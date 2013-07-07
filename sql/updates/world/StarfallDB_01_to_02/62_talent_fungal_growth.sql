-- Fungal Growth II
SET @ENTRY := 43484;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE `creature_template` SET `AIName`='' WHERE  `entry`=@ENTRY;
UPDATE `creature_template` SET `ScriptName`='npc_fungal_growth' WHERE  `entry`=@ENTRY;

-- Fungal Growth II
SET @ENTRY2 := 43497;
SET @SOURCETYPE2 := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY2 AND `source_type`=@SOURCETYPE2;
UPDATE `creature_template` SET `AIName`='' WHERE  `entry`=@ENTRY2;
UPDATE `creature_template` SET `ScriptName`='npc_fungal_growth' WHERE  `entry`=@ENTRY2;
