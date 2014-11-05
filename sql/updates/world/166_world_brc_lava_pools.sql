DELETE FROM `creature_template_addon` WHERE `entry` = '50423';
INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES
(50423, '90391');

UPDATE `creature_template` SET `minlevel`=85, `maxlevel`=85, `faction_A`=16, `faction_H`=16, `ScriptName`='npc_brc_lava_pool' WHERE `entry`=50423;

-- Lava Pool
SET @ENTRY := 50423;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;