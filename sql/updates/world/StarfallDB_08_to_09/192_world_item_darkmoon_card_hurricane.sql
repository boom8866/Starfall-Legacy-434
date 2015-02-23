DELETE FROM `spell_bonus_data` WHERE `entry` = '89087';
INSERT INTO `spell_bonus_data` (`entry`, `comments`) VALUES
(89087, 'Darkmoon Card: Hurricane');

UPDATE `spell_proc_event` SET `CustomChance`=4.5, `Cooldown`=0 WHERE `entry`=89086;