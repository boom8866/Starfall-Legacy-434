UPDATE `spell_proc_event` SET `procFlags`=327680 WHERE `entry` IN (14523, 81749);

DELETE FROM `spell_bonus_data` WHERE `entry` = '94472';
INSERT INTO `spell_bonus_data` (`entry`, `comments`) VALUES
(94472, 'Priest - Atonement');