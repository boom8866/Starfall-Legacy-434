DELETE FROM `spell_area` WHERE `spell` = '49416' AND `quest_start` = '26827';
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_end`, `autocast`, `quest_start_status`) VALUES
(49416, 5395, 26827, 26827, 1, 10);

UPDATE `creature_template_addon` SET `auras`='49414' WHERE `entry` IN (44634, 44646, 45034, 43836);