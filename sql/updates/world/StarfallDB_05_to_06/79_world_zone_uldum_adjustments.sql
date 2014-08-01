UPDATE `quest_template` SET `PrevQuestId`='27628' WHERE `Id` IN (27630,27629,27631);
UPDATE `quest_template` SET `Flags`=0 WHERE `Id`=27187;
UPDATE `quest_template` SET `PrevQuestId`='27431' WHERE `Id`=27627;
UPDATE `creature` SET `phaseMask`=8 WHERE `id` IN (46129, 46128, 46126, 46127);
UPDATE `spell_area` SET `quest_start`=28198 WHERE `spell`=89298 AND `area`=5665 AND `quest_start`=28210 AND `aura_spell`=0 AND `racemask`=0 AND `gender`=2;

-- Totally Generic Bunny (JSB)
SET @ENTRY := 28960;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="" WHERE entry=@ENTRY LIMIT 1;

UPDATE `creature` SET `phaseMask`=32 WHERE `guid`=184208;
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=100 WHERE `entry`=46993 AND `item`=62768;

UPDATE `creature` SET `phaseMask`=1 WHERE `guid` IN 
(181258,181257,181261,181259,181255,181254,181256);

DELETE FROM `creature_addon` WHERE `guid` IN (181258,181257,181261,181259,181255,181254,181256);
INSERT INTO `creature_addon` (`guid`, `bytes2`, `auras`) VALUES
(181258, 1, '49414'),
(181257, 1, '49414'),
(181261, 1, '49414'),
(181259, 1, '49414'),
(181255, 1, '49414'),
(181254, 1, '49414'),
(181256, 1, '49414');

DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '28132';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(49416, 5602, 28132, 27990, 1, 66);

UPDATE `creature` SET `phaseMask`=32768 WHERE `id`=49281;
UPDATE `spell_area` SET `quest_start_status`=66 WHERE `spell`=94566 AND `area`=5602 AND `quest_start`=28267 AND `aura_spell`=0 AND `racemask`=0 AND `gender`=2;

DELETE FROM `creature_loot_template` WHERE `item` = '65660';
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(43879, 65660, -100, 1, 0, 1, 1),
(43878, 65660, -100, 1, 0, 1, 1);

DELETE FROM `conditions` WHERE `SourceEntry` = '93996';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ScriptName`, `Comment`) VALUES
(13, 1, 93996, 0, 0, 31, 0, 3, 50629, 0, 0, 0, '', 'Targeting -> Mirror Image'),
(13, 1, 93996, 0, 1, 31, 0, 3, 49110, 0, 0, 0, '', 'Targeting -> Mirror Image'),
(13, 1, 93996, 0, 2, 31, 0, 3, 50626, 0, 0, 0, '', 'Targeting -> Mirror Image'),
(13, 1, 93996, 0, 3, 31, 0, 3, 50625, 0, 0, 0, '', 'Targeting -> Mirror Image'),
(13, 1, 93996, 0, 4, 31, 0, 3, 50623, 0, 0, 0, '', 'Targeting -> Mirror Image');

DELETE FROM `creature_template_addon` WHERE `entry` = '50661';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(50661, 1, '60191');

DELETE FROM `creature_template_addon` WHERE `entry` = '50629';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(50629, 1, '60191');

DELETE FROM `creature_template_addon` WHERE `entry` = '50407';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(50407, 1, '60191');

DELETE FROM `creature_template_addon` WHERE `entry` = '50673';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(50673, 1, '60191');

DELETE FROM `creature_template_addon` WHERE `entry` = '51134';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(51134, 1, '60191');

DELETE FROM `creature_template_addon` WHERE `entry` = '50629';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(50629, 1, '60191');

DELETE FROM `creature_template_addon` WHERE `entry` = '50664';
INSERT INTO `creature_template_addon` (`entry`, `bytes2`, `auras`) VALUES
(50664, 1, '60191');

UPDATE `creature` SET `phaseMask`=385 WHERE `guid`=735887;